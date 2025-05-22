package com.quick.poll.configurations;

import java.util.List;
import java.util.Optional;

import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

import com.quick.poll.entities.User;
import com.quick.poll.repositories.UserRepo;

@Service
public class CustomUserDetailsService  implements UserDetailsService{
	
	private UserRepo userRepo;
	
	public CustomUserDetailsService (UserRepo userRepo) {
		this.userRepo=userRepo;
	}
	
	@Override
	public UserDetails loadUserByUsername(String identifier) {
		Optional<User> user=userRepo.findByUsername(identifier);
		if(user.isEmpty()) user=userRepo.findByEmail(identifier);
		User foundUser=user.orElseThrow(()->new UsernameNotFoundException("The user "+identifier+ " does not exist!"));
		
		return new org.springframework.security.core.userdetails.User(foundUser.getUsername(),foundUser.getPassword(),
				List.of(new SimpleGrantedAuthority(foundUser.getRole())));
	}
}
