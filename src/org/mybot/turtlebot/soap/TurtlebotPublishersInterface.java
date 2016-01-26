/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.soap;

import javax.jws.WebMethod;
import javax.jws.WebService;
import mybot_delivery_app.DeliveryRequestMsg;
import org.mybot.turtlebot.messages.DeliveryRequestMessage;

/**
 *
 * @author ros
 */
@WebService
public interface TurtlebotPublishersInterface {
    
    @WebMethod
    public String ExecuteCoffeeRequest(DeliveryRequestMessage msg);
	
    @WebMethod
    public String ExecuteDeliveryRequest(DeliveryRequestMessage deliveryRequestMessage);
	

}
