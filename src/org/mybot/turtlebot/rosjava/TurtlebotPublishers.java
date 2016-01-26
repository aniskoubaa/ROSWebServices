/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.rosjava;

import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;

import org.ros.node.topic.Publisher;

/**
 *
 * @author ros
 */
public class TurtlebotPublishers extends AbstractNodeMain{
    
    public static Publisher<mybot_delivery_app.DeliveryRequestMsg> delivery_message_publisher;
    public static Publisher<geometry_msgs.PoseWithCovarianceStamped> initial_pose_publisher;
    
    public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlebot_publisher_node");
	}
	public void onStart(final ConnectedNode connectedNode) {
		delivery_message_publisher = connectedNode.newPublisher("/DeliveryRequestMsg/from_json", mybot_delivery_app.DeliveryRequestMsg._TYPE);
                initial_pose_publisher = connectedNode.newPublisher("/initial_pose", geometry_msgs.PoseWithCovarianceStamped._TYPE);
		          System.out.println("TurtlebotPublishers onStart");
             
	}
    
            
}
