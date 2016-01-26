package org.mybot.turtlesim.soap.client;

import java.net.URL;
import java.util.Scanner;

import javax.xml.namespace.QName;
import javax.xml.ws.Service;

import org.mybot.turtlesim.rosjava.TurtleSim;
import org.mybot.turtlesim.soap.TurtlesimListenersInterface;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;

public class TurtlesimListenersWebServiceClient extends AbstractNodeMain{

	@Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlesim_listeners/ws_client_node");
	}


	@Override
	public void onStart(final ConnectedNode connectedNode) {

		try{
			URL url = new URL("http://"+TurtleSim.IPAddress+":1239/turtlesim_listerners_ws?wsdl");

			//qualified name of the service
			QName qname = new QName ("http://soap.turtlesim.mybot.org/","TurtlesimListenersWebServiceService");
			System.out.println("qname: " +qname);

			//create a factory for the service
			Service service = Service.create(url, qname);


			//extract the endpoint interface, the service "port"
			TurtlesimListenersInterface sei = service.getPort(TurtlesimListenersInterface.class);

			for (int i=0; i<10; i++){
				Scanner scanner = new Scanner(System.in);
				System.out.println("\nPress a key to call the services \n");
				scanner.next();
				System.out.println("\n********START CALLING THE SERVICE*********\n");
				System.out.printf("Pose: %s\n", sei.getPose());
				System.out.printf("X   : %s\n", sei.getX());
				System.out.printf("Y   : %s\n", sei.getY());
				//Thread.sleep(2000);
			}

		}
		catch (Exception e){

			System.out.println("BIG ERROR!! ***************************"+e);

		}
	}
}