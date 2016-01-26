package org.mybot.pubsub.soap.endpoint;


import javax.xml.ws.Endpoint;

import org.mybot.pubsub.soap.webservice.TalkerWebService;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;


public class TalkerWebServiceEndpointPublisherNode extends AbstractNodeMain {

	@Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/soappub");
	}

	@Override
	public void onStart(final ConnectedNode connectedNode) {
		Endpoint sei = Endpoint.publish("http://192.168.100.10:1234/talkerws", new TalkerWebService(connectedNode));
	}
}