package org.mybot.turtlesim.soap;

import org.mybot.turtlesim.rosjava.TurtleSim;
import javax.xml.ws.Endpoint;

import org.mybot.pubsub.soap.webservice.TalkerWebService;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;

public class TurtlsimListernersWebServiceEndpointPublisherNode extends AbstractNodeMain {

	@Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlesim_listerners/endpoint_publisher");
	}

	@Override
	public void onStart(final ConnectedNode connectedNode) {
		Endpoint sei = Endpoint.publish("http://"+TurtleSim.IPAddress+":1239/turtlesim_listerners_ws", new TurtlesimListenersWebService(connectedNode));
	}

}
