package org.mybot.turtlesim.soap;

import org.mybot.turtlesim.rosjava.TurtlesimListeners;
import javax.jws.WebService;
import org.ros.node.ConnectedNode;



@WebService(endpointInterface = "org.mybot.turtlesim.soap.TurtlesimListenersInterface")
public class TurtlesimListenersWebService implements TurtlesimListenersInterface {


	static ConnectedNode connectedNode;
	public static TurtlesimListeners turtlesimListeners = new TurtlesimListeners();

	public TurtlesimListenersWebService (ConnectedNode cn){
		System.out.println("\n\n---------> TurtlesimListenersWebService Constructor\n\n\n");
		connectedNode = cn;
		turtlesimListeners.onStart(cn);
	}

	//@WebMethod
	public String getPose(){
		return String.format("(%.2f, %.2f, %.2f)",
				turtlesimListeners.getTurtlesimPose().getX(),
				turtlesimListeners.getTurtlesimPose().getY(),
				turtlesimListeners.getTurtlesimPose().getTheta());
	}
	
	//@WebMethod
	public String getX(){
		return String.format("%.2f",turtlesimListeners.getTurtlesimPose().getX());
	}
	
	//@WebMethod
	public String getY(){
		return String.format("%.2f",turtlesimListeners.getTurtlesimPose().getY());
	}
}
