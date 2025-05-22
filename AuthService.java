package com.quick.poll.services;

import java.time.LocalDateTime;
import java.util.Collections;
import java.util.Map;

import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

import com.quick.poll.dtos.LoginCredentials;
import com.quick.poll.dtos.RegisterRequest;
import com.quick.poll.dtos.ResetPasswordRequest;
import com.quick.poll.entities.User;
import com.quick.poll.exceptions.ResourceNotFoundException;
import com.quick.poll.jwt.JWTUtil;
import com.quick.poll.repositories.UserRepo;

@Service
public class AuthService {

	private UserRepo userRepo;
	private PasswordEncoder encoder;
	private AuthenticationManager authManager;
	private JWTUtil util;
	
	public AuthService(UserRepo userRepo,PasswordEncoder encoder,JWTUtil util,AuthenticationManager authManager) {
		this.userRepo=userRepo;
		this.encoder=encoder;
		this.util=util;
		this.authManager=authManager;
	}
	public Map<String,Object> register(RegisterRequest request) {
		if(userRepo.existsByUsername(request.getUsername()))
			throw new RuntimeException("This username is taken!");
		if(userRepo.existsByEmail(request.getEmail()))
			throw new RuntimeException("This email is already in use!");
		User user=new User();
		user.setEmail(request.getEmail());
		user.setPassword(encoder.encode(request.getPassword()));
		user.setUsername(request.getUsername());
		user.setRole("ROLE_USER");
		userRepo.save(user);
		String token=util.generateToken(request.getEmail());
		return Collections.singletonMap("jwtToken",token);
	}
	
	public Map<String,Object> login(LoginCredentials credentials){
		try {
			UsernamePasswordAuthenticationToken authToken=
					new UsernamePasswordAuthenticationToken(credentials.getIdentifier(),credentials.getPassword());
			authManager.authenticate(authToken);//daca nu corespund datele,va da eroare
			//si se impiedica astfel trimiterea tokenului
			String token=util.generateToken(credentials.getIdentifier());
			return Collections.singletonMap("jwtToken", token);			
		}catch (AuthenticationException authExc){
            throw new RuntimeException("Invalid Login Credentials");
        }
	}
	
	public boolean verifyCode(User user,String code) {
		if(user.getExpirationTime().isBefore(LocalDateTime.now()))
			return false;
		if(!user.getVerificationCode().equals(code)) 
			return false;
		return true;
	}
	
	public boolean resetPassword(ResetPasswordRequest request) {
		System.out.println("\n\n\n!!!"+request.getEmail()+"!!!!\n\n\n");
		User user=userRepo.findByEmail(request.getEmail()).orElseThrow(()->new ResourceNotFoundException("User not found!"));
		if(!verifyCode(user,request.getVerificationCode())) return false;
		
		user.setPassword(encoder.encode(request.getNewPassword()));
		userRepo.save(user);
		return true;
	}
}
