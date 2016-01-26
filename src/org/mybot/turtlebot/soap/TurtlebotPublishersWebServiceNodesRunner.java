/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.soap;

import com.google.common.base.Preconditions;
import java.net.URI;
import org.mybot.turtlebot.rosjava.Turtlebot;
import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

/**
 *
 * @author ros
 */
public class TurtlebotPublishersWebServiceNodesRunner {
    public static void main(String[] args) {
        
	TurtlebotPublishersWebServiceEndpointPublisherNode endpointPublisher  = new TurtlebotPublishersWebServiceEndpointPublisherNode();    
        NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
        URI masteruri = URI.create("http://"+Turtlebot.IPAddress+":11311");
        String host = Turtlebot.IPAddress;
        NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
        Preconditions.checkState(endpointPublisher != null);
        nodeMainExecutor.execute(endpointPublisher, pubNodeConfiguration);
    }
    
    
}
