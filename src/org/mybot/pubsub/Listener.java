package org.mybot.pubsub;

import org.apache.commons.logging.Log;
import org.ros.message.MessageListener;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
//import org.ros.node.NodeMain;
import org.ros.node.topic.Subscriber;

public class Listener extends AbstractNodeMain {
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/listener");
	}
	public void onStart(ConnectedNode connectedNode) {
		final Log log = connectedNode.getLog();
		Subscriber<std_msgs.String> subscriber = connectedNode.newSubscriber("chatter", std_msgs.String._TYPE);
		subscriber.addMessageListener(new MessageListener<std_msgs.String>() {
			public void onNewMessage(std_msgs.String message) {
				log.info("I heard: \"" + message.getData() + "\"");
			}
		});
	}
}
