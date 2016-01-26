/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.rest;

import javax.ws.rs.GET;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import mybot_delivery_app.DeliveryRequestMsg;
import org.mybot.turtlebot.rosjava.TurtlebotPublishers;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Publisher;

/**
 *
 * @author ros
 */
@Path("robot/app/delivery/")
public class DeliveryTopicResource {
    
    public static TurtlebotPublishers turtlebotPublishers;
    static ConnectedNode connectedNode ;
    
    public DeliveryTopicResource(){  
    }
    
    public DeliveryTopicResource(ConnectedNode connectedNode){    
        turtlebotPublishers = new TurtlebotPublishers();
        //Thread.sleep(2000);
	turtlebotPublishers.onStart(connectedNode);
    }
    
    @GET //Handle HTTP Get requests
    @Path("code/{code}/depot_x/{depot_x}/depot_y/{depot_y}/dest_x/{dest_x}/dest_y/{dest_y}/source_x/{source_x}/source_y/{source_y}")
    public String executeDelivery (@PathParam("code") int code, 
            @PathParam("depot_x") double depot_x, 
            @PathParam("depot_y") double depot_y, 
            @PathParam("dest_x") double dest_x, 
            @PathParam("dest_y") double dest_y, 
            @PathParam("source_x") double source_x, 
            @PathParam("source_y") double source_y){
        DeliveryRequestMsg rosMessage =  TurtlebotPublishers.delivery_message_publisher.newMessage();
           System.out.println("\n\n\nReceived Get Request\n\n\n\n\n");
            rosMessage.setDepotX(depot_x);
            rosMessage.setDepotY(depot_y);
            rosMessage.setDestinationX(dest_x);
            rosMessage.setDestinationY(dest_y);
            rosMessage.setSourceX(source_x);
            rosMessage.setSourceY(source_y);
            rosMessage.setMessageCode(code);
            System.out.println("\n\n\n\n\n\n Message received \n\n\n\n");
            TurtlebotPublishers.delivery_message_publisher.publish(rosMessage);
            
            return "done";
    }
    
}
