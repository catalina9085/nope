package com.quick.poll.jwt;

import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.server.ServerHttpRequest;
import org.springframework.http.server.ServerHttpResponse;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.WebSocketHandler;
import org.springframework.web.socket.server.HandshakeInterceptor;

import com.auth0.jwt.exceptions.JWTVerificationException;


@Component
public class AuthHandshakeInterceptor implements HandshakeInterceptor {
	@Autowired
	private JWTUtil jwtUtil;
	
    @Override
    public boolean beforeHandshake(ServerHttpRequest request, ServerHttpResponse response, 
                                   WebSocketHandler wsHandler, Map<String, Object> attributes) {
    	String token = request.getHeaders().getFirst("Authorization");

        if (token != null && token.startsWith("Bearer ")) {
            // Extrage token-ul și validează-l
            token = token.substring(7);
            System.out.println("\n\n\n!!!!!!!!!!"+token+"\n\n\n\n");

            try {
            	String email=jwtUtil.validateToken(token);
            	attributes.put("email", email);
                return true; 
            }catch(JWTVerificationException e) {
            	response.setStatusCode(HttpStatus.FORBIDDEN);
            	return false;
            }
        }
        
        return false; // Blochează conexiunea dacă token-ul nu e valid
    }

    @Override
    public void afterHandshake(ServerHttpRequest request, ServerHttpResponse response, 
                               WebSocketHandler wsHandler, Exception exception) {
        // Aici poți adăuga logare sau alte operațiuni (dacă e necesar)
        System.out.println("Handshake complet!");
    }
}