package org.mybot.turtlesim.soap.client;


import java.net.URI;

import org.mybot.turtlesim.rosjava.TurtleSim;
import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

import com.google.common.base.Preconditions;

public class TurtlesimListenersWebServiceClientRunner {

	public static void main(String[] args) {

		TurtlesimListenersWebServiceClient talkerWebServiceClient  = new TurtlesimListenersWebServiceClient();    
		NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
		URI masteruri = URI.create("http://"+TurtleSim.IPAddress+":11311");
		String host = TurtleSim.IPAddress;
		NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
		Preconditions.checkState(talkerWebServiceClient != null);
		nodeMainExecutor.execute(talkerWebServiceClient, pubNodeConfiguration);
	}

}

