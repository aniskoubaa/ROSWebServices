/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.rosjava;

import com.google.common.base.Preconditions;
import java.net.URI;
import org.mybot.turtlebot.rosjava.Turtlebot;
import org.mybot.turtlebot.rosjava.TurtlebotPublishers;
import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

/**
 *
 * @author ros
 */
public class TurtlebotPublishersRunner {
    
    public static void main(String[] args) {

		TurtlebotPublishers turtlebotPublishers  = new TurtlebotPublishers();    
		NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
		URI masteruri = URI.create("http://"+Turtlebot.IPAddress+":11311");
		String host = Turtlebot.IPAddress;
		NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
		Preconditions.checkState(turtlebotPublishers != null);
		nodeMainExecutor.execute(turtlebotPublishers, pubNodeConfiguration);
	}
    
}
