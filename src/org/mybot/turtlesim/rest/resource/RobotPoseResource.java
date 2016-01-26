/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlesim.rest.resource;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import org.mybot.turtlesim.rosjava.TurtlesimListeners;
import org.mybot.turtlesim.rosjava.TurtlesimPublishers;
import org.ros.node.ConnectedNode;

@Path("robot/pose/")
public class RobotPoseResource {
    
    public static TurtlesimListeners turtlesimListeners;
    public static TurtlesimPublishers turtlesimPublishers;
    static ConnectedNode connectedNode ;
    public int keep_loop = 0;

    public RobotPoseResource() {
    }
    
    public RobotPoseResource(ConnectedNode connectedNode) throws InterruptedException{
        System.out.println("\n\n---------> TurtlesimListenersWebService Constructor\n\n\n");
	//connectedNode = new ConnectedNode();
        turtlesimListeners = new TurtlesimListeners();
        turtlesimPublishers = new TurtlesimPublishers();
        //Thread.sleep(2000);
	turtlesimListeners.onStart(connectedNode);
        turtlesimPublishers.onStart(connectedNode); 
        
    }
    
    @GET //Handle HTTP Get requests
    @Path("pose/")
    //@Path("{linear}") //URI components containing the parameter
    @Produces ("text/plain")
    public String getPose(){
        return String.format("(%.2f, %.2f, %.2f)",
				turtlesimListeners.getTurtlesimPose().getX(),
				turtlesimListeners.getTurtlesimPose().getY(),
				turtlesimListeners.getTurtlesimPose().getTheta());          
    }
    
    @GET //Handle HTTP Get requests
    @Path("pose/xml/")
    //@Path("{linear}") //URI components containing the parameter
    @Produces ("text/xml")
    public String getPoseXML(){
        String xml = String.format("<pose>\n" +"\t<x>%.2f</x> "+"\t<y>%.2f</y> "+"\t<theta>%.2f</theta> "+"</pose>", 
                turtlesimListeners.getTurtlesimPose().getX(),
                turtlesimListeners.getTurtlesimPose().getY(),
		turtlesimListeners.getTurtlesimPose().getTheta()
        );
        
        return xml;          
    }
    
    
    
    
}
