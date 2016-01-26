package org.mybot.turtlesim.rosjava;

import org.mybot.turtlesim.rosjava.TurtlesimListeners;
import java.net.URI;

import org.mybot.turtlesim.soap.client.TurtlesimListenersWebServiceClient;
import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

import com.google.common.base.Preconditions;

public class TurtlesimListenersRunner {

	public static void main(String[] args) {

		TurtlesimListeners turtlesimListeners  = new TurtlesimListeners();    
		NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
		URI masteruri = URI.create("http://"+TurtleSim.IPAddress+":11311");
		String host = TurtleSim.IPAddress;
		NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
		Preconditions.checkState(turtlesimListeners != null);
		nodeMainExecutor.execute(turtlesimListeners, pubNodeConfiguration);
	}

}
