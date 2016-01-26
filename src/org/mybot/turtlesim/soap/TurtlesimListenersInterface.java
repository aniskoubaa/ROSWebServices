package org.mybot.turtlesim.soap;

import javax.jws.WebMethod;
import javax.jws.WebService;

@WebService
public interface TurtlesimListenersInterface {
	
	@WebMethod
	public String getPose();
	
	@WebMethod
	public String getX();
	
	@WebMethod
	public String getY();
	

}
