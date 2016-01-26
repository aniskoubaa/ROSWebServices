/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.soap.client;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.Scanner;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import org.mybot.turtlebot.messages.DeliveryRequestMessage;
import org.mybot.turtlebot.rosjava.Turtlebot;
import org.mybot.turtlebot.soap.TurtlebotPublishersInterface;


/**
 *
 * @author ros
 */
public class TurtlebotPublishersWebServiceClient {
    
static final  int HELLO_MESSAGE_CODE=0;
static final  int GO_TO_GOAL_MESSAGE_CODE=1;
static final  int COURIER_DELIVERY_MESSAGE_CODE=3;
static final  int COFFEE_DELIVERY_MESSAGE_CODE=4;
    
    public static void main(String []args) throws MalformedURLException{
    
    URL url = new URL("http://"+Turtlebot.IPAddress+":5555/turtlesim_publisher_ws?wsdl");

        //qualified name of the service
        QName qname = new QName ("http://soap.turtlebot.mybot.org/","TurtlebotPublishersWebServiceService");
        System.out.println("qname: " +qname);

        //create a factory for the service
        Service service = Service.create(url, qname);


        //extract the endpoint interface, the service "port"
        TurtlebotPublishersInterface sei = service.getPort(TurtlebotPublishersInterface.class);
        int x =0;
        do{
            System.out.println("Press one of these options ...");
            System.out.println("1- Coffee Request");
            System.out.println("2- Delivery Request");
            System.out.println("0- Exit");
            Scanner input = new Scanner (System.in);
            x = input.nextInt();
            
            if (x==1){
                 
                DeliveryRequestMessage deliveryRequestMessage = new DeliveryRequestMessage();
                deliveryRequestMessage.setMessage_code(COFFEE_DELIVERY_MESSAGE_CODE);
                deliveryRequestMessage.setSource_x(76.02);//Anis
                deliveryRequestMessage.setSource_y(41.35);
                deliveryRequestMessage.setDestination_x(60.508); //Coffee 60.508, y: 37.973
                deliveryRequestMessage.setDestination_y(37.973);
                deliveryRequestMessage.setDepot_x(72.497); // Water Dispenser 72.497, y: 50.632
                deliveryRequestMessage.setDepot_y(50.632);
                long t0= System.currentTimeMillis();
                sei.ExecuteCoffeeRequest(deliveryRequestMessage);
                long t1= System.currentTimeMillis();
                System.out.println("Execution Time: "+ (t1-t0) );
            }else
                if (x==2){
                    DeliveryRequestMessage deliveryRequestMessage = new DeliveryRequestMessage();
                deliveryRequestMessage.setMessage_code(COURIER_DELIVERY_MESSAGE_CODE);
                deliveryRequestMessage.setSource_x(76.02); //Anis
                deliveryRequestMessage.setSource_y(41.35);
                deliveryRequestMessage.setDestination_x(73.259); //Inyat
                deliveryRequestMessage.setDestination_y(41.35);
                deliveryRequestMessage.setDepot_x(68.269);  // Water Dispenser
                deliveryRequestMessage.setDepot_y(38.718);
                long t0= System.currentTimeMillis();
                sei.ExecuteDeliveryRequest(deliveryRequestMessage);
                long t1= System.currentTimeMillis();
                System.out.println("Execution Time: "+ (t1-t0) );
            }
                else {
                    x=0;
                    System.out.println("Exit");
            }
            
        
        }while (x!=0);
        

}
		
    
    
}
