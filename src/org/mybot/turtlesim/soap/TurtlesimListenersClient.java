package org.mybot.turtlesim.soap;

import java.net.URL;

import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import org.mybot.turtlesim.rosjava.TurtleSim;

import org.mybot.pubsub.soap.webservice.TalkerInterface;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;


public class TurtlesimListenersClient extends AbstractNodeMain{

	@Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlesim_listeners_client_node");
	}


	@Override
	public void onStart(final ConnectedNode connectedNode) {

		try{
			URL url = new URL("http://"+TurtleSim.IPAddress+":1234/talkerws?wsdl");

			//qualified name of the service
			QName qname = new QName ("http://webservice.soap.pubsub.mybot.org/","TalkerWebServiceService");
			System.out.println("qname: " +qname);

			//create a factory for the service
			Service service = Service.create(url, qname);


			//extract the endpoint interface, the service "port"
			TalkerInterface sei = service.getPort(TalkerInterface.class);

			for (int i=0; i<10; i++){
				System.out.println("\n********START CALLING THE SERVICE*********\n");
				System.out.println(sei.setMessage("Anis " + i));
				Thread.sleep(2000);
			}

		}
		catch (Exception e){

			System.out.println("BIG ERROR!! ***************************"+e);

		}
	}
}
