package org.mybot.pubsub.soap.ros;

import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Publisher;

public class Talker extends AbstractNodeMain {
	public String talkermsg = "[Talker] no message received so far!";

	@Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/talker");
	}

	@Override
	public void onStart(final ConnectedNode connectedNode) {

		final Publisher<std_msgs.String> publisher =
				connectedNode.newPublisher("chatter", std_msgs.String._TYPE);

		connectedNode.executeCancellableLoop(new CancellableLoop() {
			private int sequenceNumber;

			@Override
			protected void setup() {
				sequenceNumber = 0;
			}

			@Override
			protected void loop() throws InterruptedException {

				std_msgs.String str = publisher.newMessage();
				str.setData("Hello world! " + sequenceNumber + "\n      Talker Message: "+ talkermsg);
				publisher.publish(str);
				sequenceNumber++;
				Thread.sleep(1000);
			}
		});


	}
}

