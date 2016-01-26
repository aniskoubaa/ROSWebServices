/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlesim.rest;

import com.google.common.base.Preconditions;
import java.net.URI;
import javax.ws.rs.Path;
import org.mybot.turtlesim.rosjava.TurtleSim;
import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

/**
 *
 * @author akoubaa
 */

public class TurtlesimVelocityPublisherResourceNodesRunner {
    public static void main(String[] args) {
        
		TurtlsimVelocityPublisherResourceEndpointPublisherNode endpointPublisher  = new TurtlsimVelocityPublisherResourceEndpointPublisherNode();    
	        NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
	        URI masteruri = URI.create("http://"+TurtleSim.IPAddress+":11311");
	        String host = TurtleSim.IPAddress;
	        NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
	        Preconditions.checkState(endpointPublisher != null);
	        nodeMainExecutor.execute(endpointPublisher, pubNodeConfiguration);
	    }
}
