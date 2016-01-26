/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.soap;

import javax.jws.WebService;
import mybot_delivery_app.DeliveryRequestMsg;
import org.mybot.turtlebot.messages.DeliveryRequestMessage;
import org.mybot.turtlebot.rosjava.TurtlebotPublishers;
import org.ros.node.ConnectedNode;

/**
 *
 * @author ros
 */
@WebService(endpointInterface = "org.mybot.turtlebot.soap.TurtlebotPublishersInterface")
public class TurtlebotPublishersWebService implements TurtlebotPublishersInterface{
    
    static ConnectedNode connectedNode;
  public static TurtlebotPublishers turtlebotPublishers = new TurtlebotPublishers();

    public TurtlebotPublishersWebService(ConnectedNode cn) {
        System.out.println("\n\n---------> TurtlesimListenersWebService Constructor\n\n\n");
	connectedNode = cn;
	turtlebotPublishers.onStart(cn);
    }
  

    public String ExecuteCoffeeRequest(DeliveryRequestMessage deliveryRequestMessage) {
        /*if (msg.getMessageCode()!=4)
            msg.setMessageCode(4);//enfore the message code to be correct
        */
        
        
         DeliveryRequestMsg rosMessage =  TurtlebotPublishers.delivery_message_publisher.newMessage();
           
            rosMessage.setDepotY(deliveryRequestMessage.getDepot_y());
            rosMessage.setDepotX(deliveryRequestMessage.getDepot_x());
            rosMessage.setDestinationX(deliveryRequestMessage.getDestination_x());
            rosMessage.setDestinationY(deliveryRequestMessage.getDestination_y());
            rosMessage.setSourceX(deliveryRequestMessage.getSource_x());
            rosMessage.setSourceY(deliveryRequestMessage.getSource_y());
            rosMessage.setMessageCode(4);
            
        TurtlebotPublishers.delivery_message_publisher.publish(rosMessage);
        
        return "done";
    }


    public String ExecuteDeliveryRequest(DeliveryRequestMessage deliveryRequestMessage) {
        DeliveryRequestMsg rosMessage =  TurtlebotPublishers.delivery_message_publisher.newMessage();
           
            rosMessage.setDepotY(deliveryRequestMessage.getDepot_y());
            rosMessage.setDepotX(deliveryRequestMessage.getDepot_x());
            rosMessage.setDestinationX(deliveryRequestMessage.getDestination_x());
            rosMessage.setDestinationY(deliveryRequestMessage.getDestination_y());
            rosMessage.setSourceX(deliveryRequestMessage.getSource_x());
            rosMessage.setSourceY(deliveryRequestMessage.getSource_y());
            rosMessage.setMessageCode(3);
            
        TurtlebotPublishers.delivery_message_publisher.publish(rosMessage);
        
        return "done";
        
    }
    
    
    
}
