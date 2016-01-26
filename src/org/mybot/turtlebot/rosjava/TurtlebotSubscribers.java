/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.rosjava;

import java.util.Map;
import java.util.TreeMap;
import org.ros.message.MessageListener;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Subscriber;

/**
 *
 * @author ros
 */
public class TurtlebotSubscribers extends AbstractNodeMain{
        
        geometry_msgs.PoseWithCovarianceStamped amcl_pose;
        geometry_msgs.PoseWithCovarianceStamped initial_pose;
        nav_msgs.Odometry odom;
        std_msgs.String local_ip_address;
        
        mybot_delivery_app.DeliveryRequestMsg delivery_message;
        
        public ConnectedNode connectedNode;
        
        Map <String, Class> topicsMap = new TreeMap<String, Class>();
	
	public TurtlebotSubscribers (){
		topicsMap.put("odom", nav_msgs.Odometry.class);
                topicsMap.put("PoseWithCovarianceStamped", geometry_msgs.PoseWithCovarianceStamped.class);
	}
	
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlebot_listeners");
	}
	public void onStart(ConnectedNode connectedNode) {
		//final Log log = connectedNode.getLog();
		this.connectedNode = connectedNode;
                System.out.println("TurtlebotListeners onStart");
                Subscriber<geometry_msgs.PoseWithCovarianceStamped> amclPoseSubscriber = connectedNode.newSubscriber("/amcl_pose", geometry_msgs.PoseWithCovarianceStamped._TYPE);
		amclPoseSubscriber.addMessageListener(new MessageListener<geometry_msgs.PoseWithCovarianceStamped>() {
			public void onNewMessage(geometry_msgs.PoseWithCovarianceStamped poseMessage) {
				amcl_pose = poseMessage;
				//System.out.printf("Pose: (%.2f, %.2f, %s)\n", poseMessage.getX(), poseMessage.getY(), poseMessage.getTheta());
			}
		});
                
                Subscriber<geometry_msgs.PoseWithCovarianceStamped> initialPoseSubscriber = connectedNode.newSubscriber("/initial_pose", geometry_msgs.PoseWithCovarianceStamped._TYPE);
		amclPoseSubscriber.addMessageListener(new MessageListener<geometry_msgs.PoseWithCovarianceStamped>() {
			public void onNewMessage(geometry_msgs.PoseWithCovarianceStamped poseMessage) {
				initial_pose = poseMessage;
				//System.out.printf("Pose: (%.2f, %.2f, %s)\n", poseMessage.getX(), poseMessage.getY(), poseMessage.getTheta());
			}
		});
                
                
                Subscriber<nav_msgs.Odometry> odomSubscriber = connectedNode.newSubscriber("/odom", nav_msgs.Odometry._TYPE);
		odomSubscriber.addMessageListener(new MessageListener<nav_msgs.Odometry>() {
			public void onNewMessage(nav_msgs.Odometry odomMessage) {
				odom = odomMessage;
				//System.out.printf("Pose: (%.2f, %.2f, %s)\n", poseMessage.getX(), poseMessage.getY(), poseMessage.getTheta());
			}
		});
                
                Subscriber<mybot_delivery_app.DeliveryRequestMsg> deliveryRequestMsgSubscriber = connectedNode.newSubscriber("/DeliveryRequestMsg/from_json", mybot_delivery_app.DeliveryRequestMsg._TYPE);
		deliveryRequestMsgSubscriber.addMessageListener(new MessageListener<mybot_delivery_app.DeliveryRequestMsg>() {
			public void onNewMessage(mybot_delivery_app.DeliveryRequestMsg deliveryMessage) {
				delivery_message = deliveryMessage;
				//System.out.printf("Pose: (%.2f, %.2f, %s)\n", poseMessage.getX(), poseMessage.getY(), poseMessage.getTheta());
			}
		});
                
                Subscriber<std_msgs.String> IPAddressMsgSubscriber = connectedNode.newSubscriber("/local_ip_address", std_msgs.String._TYPE);
		IPAddressMsgSubscriber.addMessageListener(new MessageListener<std_msgs.String>() {
			public void onNewMessage(std_msgs.String localIPAddressMessage) {
				local_ip_address = localIPAddressMessage;
				//System.out.printf("Pose: (%.2f, %.2f, %s)\n", poseMessage.getX(), poseMessage.getY(), poseMessage.getTheta());
			}
		});
                
	}
	
	public geometry_msgs.PoseWithCovarianceStamped getAmclPose(){
		return amcl_pose;
	}
        
        public nav_msgs.Odometry getOdom(){
		return odom;
	}
        
        public geometry_msgs.PoseWithCovarianceStamped getInitialPose(){
		return initial_pose;
	}
        
        public mybot_delivery_app.DeliveryRequestMsg getDeliveryRequestMsg(){
		return delivery_message;
	}
    
}
