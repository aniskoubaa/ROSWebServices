package org.mybot.pubsub;

import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
//import org.ros.node.NodeMain;
import org.ros.node.topic.Publisher;

public class Talker extends AbstractNodeMain {
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/talker");
	}
	public void onStart(final ConnectedNode connectedNode) {
		final Publisher<std_msgs.String> publisher = connectedNode.newPublisher("chatter", std_msgs.String._TYPE);
		connectedNode.executeCancellableLoop(new CancellableLoop() {
			private int sequenceNumber;
			protected void setup() {
				sequenceNumber = 0;
			}
			protected void loop() throws InterruptedException {
				std_msgs.String str = publisher.newMessage();
				str.setData("Hello world! " + sequenceNumber);
				publisher.publish(str);
				sequenceNumber++;
				Thread.sleep(1000);
			}
		});
	}
}