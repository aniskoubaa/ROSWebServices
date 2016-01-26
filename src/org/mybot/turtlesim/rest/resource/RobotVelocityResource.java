/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlesim.rest.resource;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import org.mybot.turtlesim.rosjava.TurtlesimListeners;
import org.mybot.turtlesim.rosjava.TurtlesimPublishers;
import org.ros.node.ConnectedNode;

/**
 *
 * @author ros
 */
@Path("robot/velocity")
public class RobotVelocityResource {
    
    public static TurtlesimListeners turtlesimListeners;
    public static TurtlesimPublishers turtlesimPublishers;
    static ConnectedNode connectedNode ;
    public int keep_loop = 0;
    
    public RobotVelocityResource(){
        
    }
    
    public RobotVelocityResource(ConnectedNode connectedNode) throws InterruptedException{
        System.out.println("\n\n---------> TurtlesimListenersWebService Constructor\n\n\n");
	//connectedNode = new ConnectedNode();
        turtlesimListeners = new TurtlesimListeners();
        turtlesimPublishers = new TurtlesimPublishers();
        //Thread.sleep(2000);
	turtlesimListeners.onStart(connectedNode);
        turtlesimPublishers.onStart(connectedNode);        
    }
    
    @GET //Handle HTTP Get requests
    @Path("velocity/linear/{linear}")
    //@Path("{linear}") //URI components containing the parameter
    @Produces ("text/plain")
    public boolean setLinearVelocity(@PathParam("linear") double linear){
        System.out.printf("\n\n---------> velocity_publisher  %s\n\n\n", turtlesimPublishers.velocity_publisher);
        geometry_msgs.Twist cmd_vel = turtlesimPublishers.velocity_publisher.newMessage();
        System.out.printf("\n\n---------> cmd_vel %s\n\n\n", cmd_vel);
        cmd_vel.getLinear().setX(linear);
        turtlesimPublishers.velocity_publisher.publish(cmd_vel);
        return true;            
    }
   
    @GET //Handle HTTP Get requests
    @Path("velocity/{linear}/{angular}/{loop}") //URI components containing the parameter
    @Produces ("text/plain")
    public boolean setVelocity(@PathParam("linear") double linear, @PathParam("angular") double angular, @PathParam("loop") int loop){
        System.out.printf("\n\n---------> velocity_publisher  %s\n\n\n", turtlesimPublishers.velocity_publisher);
        geometry_msgs.Twist cmd_vel = turtlesimPublishers.velocity_publisher.newMessage();
        System.out.printf("\n\n---------> cmd_vel %s\n\n\n", cmd_vel);
        cmd_vel.getLinear().setX(linear);
        cmd_vel.getAngular().setZ(angular);
        keep_loop = loop;
        turtlesimPublishers.velocity_publisher.publish(cmd_vel);  
        try {
            Thread.sleep(1000);
        } catch (InterruptedException ex) {
            Logger.getLogger(RobotVelocityResource.class.getName()).log(Level.SEVERE, null, ex);
        }
        turtlesimPublishers.velocity_publisher.publish(cmd_vel); 
        return true;            
    }

    @GET //Handle HTTP Get requests
    @Path("velocity") //URI components containing the parameter
    @Produces ("text/plain")
    public String getText(){
        System.out.printf("\n\n---------> velocity_publisher  %s\n\n\n", turtlesimPublishers.velocity_publisher);
        geometry_msgs.Twist cmd_vel = turtlesimPublishers.velocity_publisher.newMessage();
        System.out.printf("\n\n---------> cmd_vel %s\n\n\n", cmd_vel);
        
        ;
        turtlesimPublishers.velocity_publisher.publish(cmd_vel);
        return String.format("linear = %.2f, angular = %.2f", cmd_vel.getLinear().getX(), cmd_vel.getAngular().getZ());            
    }
    
    

    
    
}
