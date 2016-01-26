/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlesim.rest;

import geometry_msgs.Vector3;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import org.mybot.turtlesim.rosjava.TurtlesimListeners;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Publisher;

/**
 *
 * @author akoubaa
 */
@Path("turtlesim/velocity")
public class TurtlesimVelocityPublisherResource {
    
    //public static TurtlesimListeners turtlesimListeners;
    static ConnectedNode connectedNode ;
    //must be public static
    public static Publisher<geometry_msgs.Twist> velocity_publisher;
    
    public TurtlesimVelocityPublisherResource (){
        
    }
            
    public TurtlesimVelocityPublisherResource (ConnectedNode connectedNode) throws InterruptedException{
		System.out.println("\n\n---------> TurtlesimVelocityPublisherResource Constructor\n\n\n");
		velocity_publisher = connectedNode.newPublisher("/turtle1/cmd_vel", geometry_msgs.Twist._TYPE);
                System.out.printf("\n\n---------> velocity_publisher  %s\n\n\n", velocity_publisher);
                 geometry_msgs.Twist cmd_vel = velocity_publisher.newMessage();
                 System.out.printf("\n\n---------> cmd_vel %s\n\n\n", cmd_vel);
                 
	}
	
	@GET //Handle HTTP Get requests
	@Path("{linear}") //URI components containing the parameter
	@Produces ("text/plain")
	public String setLinearVelocity(@PathParam("linear") double linear){
            System.out.printf("\n\n---------> velocity_publisher  %s\n\n\n", velocity_publisher);
            geometry_msgs.Twist cmd_vel = velocity_publisher.newMessage();
            System.out.printf("\n\n---------> cmd_vel %s\n\n\n", cmd_vel);
            cmd_vel.getLinear().setX(linear);
            
            velocity_publisher.publish(cmd_vel);

        return "done!";
            
	}
        @GET //Handle HTTP Get requests
	@Path("test") //URI components containing the parameter
	@Produces ("text/plain")
        public String getXml(){
            return "Hello";
        }
            
}
