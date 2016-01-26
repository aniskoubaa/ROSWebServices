package org.mybot.turtlesim.rosjava;

//import org.apache.commons.logging.Log;
import org.ros.message.MessageListener;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Subscriber;
import org.ros.node.topic.*;
import turtlesim.Pose;

public class TurtlesimListeners extends AbstractNodeMain {
	
	turtlesim.Pose turtlesimPose;
        public ConnectedNode connectedNode;
	
	public TurtlesimListeners (){
		
	}
	
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlesim_listeners");
	}
	public void onStart(ConnectedNode connectedNode) {
		//final Log log = connectedNode.getLog();
		this.connectedNode = connectedNode;
		Subscriber<turtlesim.Pose> poseSubscriber = connectedNode.newSubscriber("/turtle1/pose", turtlesim.Pose._TYPE);
		poseSubscriber.addMessageListener(new MessageListener<turtlesim.Pose>() {
			public void onNewMessage(turtlesim.Pose poseMessage) {
				turtlesimPose = poseMessage;
				//System.out.printf("Pose: (%.2f, %.2f, %s)\n", poseMessage.getX(), poseMessage.getY(), poseMessage.getTheta());
			}
		});
	}
	
	public turtlesim.Pose getTurtlesimPose(){
		return turtlesimPose;
	}
}
