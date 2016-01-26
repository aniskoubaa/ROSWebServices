package org.mybot.turtlesim.soap;

import org.mybot.turtlesim.rosjava.TurtleSim;
import java.net.URI;

import org.mybot.pubsub.soap.endpoint.TalkerWebServiceEndpointPublisherNode;
import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

import com.google.common.base.Preconditions;

public class TurtlesimListenersWebServiceNodesRunner {
public static void main(String[] args) {
        
	TurtlsimListernersWebServiceEndpointPublisherNode endpointPublisher  = new TurtlsimListernersWebServiceEndpointPublisherNode();    
        NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
        URI masteruri = URI.create("http://"+TurtleSim.IPAddress+":11311");
        String host = TurtleSim.IPAddress;
        NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
        Preconditions.checkState(endpointPublisher != null);
        nodeMainExecutor.execute(endpointPublisher, pubNodeConfiguration);
    }

}
