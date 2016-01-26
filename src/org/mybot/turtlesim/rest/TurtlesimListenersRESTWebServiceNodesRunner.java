package org.mybot.turtlesim.rest;

import java.net.URI;

import org.mybot.turtlesim.rosjava.TurtleSim;
import org.mybot.turtlesim.soap.TurtlsimListernersWebServiceEndpointPublisherNode;
import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

import com.google.common.base.Preconditions;

public class TurtlesimListenersRESTWebServiceNodesRunner {
	
	public static void main(String[] args) {
        
		TurtlsimListernersRESTWebServiceEndpointPublisherNode endpointPublisher  = new TurtlsimListernersRESTWebServiceEndpointPublisherNode();    
	        NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
	        URI masteruri = URI.create("http://"+TurtleSim.IPAddress+":11311");
	        String host = TurtleSim.IPAddress;
	        NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
	        Preconditions.checkState(endpointPublisher != null);
	        nodeMainExecutor.execute(endpointPublisher, pubNodeConfiguration);
	    }
	

}
