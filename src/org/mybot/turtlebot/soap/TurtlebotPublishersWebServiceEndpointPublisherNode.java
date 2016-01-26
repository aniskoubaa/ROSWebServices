/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.soap;

import javax.xml.ws.Endpoint;
import org.mybot.turtlebot.rosjava.Turtlebot;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;

/**
 *
 * @author ros
 */
public class TurtlebotPublishersWebServiceEndpointPublisherNode extends AbstractNodeMain {

	@Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlesim_publishers/endpoint_publisher");
	}

	@Override
	public void onStart(final ConnectedNode connectedNode) {
            System.out.println("Turtlebot.IPAddress: "+Turtlebot.IPAddress);
		Endpoint sei = Endpoint.publish("http://"+Turtlebot.IPAddress+":5555/turtlesim_publisher_ws", new TurtlebotPublishersWebService(connectedNode));
	}

}
