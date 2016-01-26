/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlesim.rosjava;

import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Publisher;

/**
 *
 * @author akoubaa
 */
public class TurtlesimPublishers extends AbstractNodeMain {
    
    public Publisher<geometry_msgs.Twist> velocity_publisher ; 
    
    public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlesim_publisher_node");
	}
	public void onStart(final ConnectedNode connectedNode) {
		 Publisher<geometry_msgs.Twist> velocity_publisher = connectedNode.newPublisher("/turtle1/cmd_vel", geometry_msgs.Twist._TYPE);
		this.velocity_publisher = velocity_publisher;
                
                
                /*connectedNode.executeCancellableLoop(new CancellableLoop() {
			private int sequenceNumber;
			protected void setup() {
				sequenceNumber = 0;
			}
			protected void loop() throws InterruptedException {
				std_msgs.String str = velocity_publisher.newMessage();
				str.setData("Hello world! " + sequenceNumber);
				velocity_publisher.publish(str);
				sequenceNumber++;
				Thread.sleep(1000);
			}
		});*/
	}
    
}
