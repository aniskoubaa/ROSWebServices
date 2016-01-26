package org.mybot.pubsub.soap.webservice;

import org.mybot.pubsub.soap.ros.Talker;
import org.ros.node.ConnectedNode;

import javax.jws.WebMethod;
import javax.jws.WebService;


/**
 * Created by akoubaa on 11/4/14.
 */
@WebService(endpointInterface = "org.mybot.pubsub.soap.webservice.TalkerInterface")
public class TalkerWebService implements TalkerInterface {


	public static String talkermsg = "*********** test ***********\n\n\n";
	public static int count =0;
	static ConnectedNode connectedNode;
	public static Talker talker = new Talker();

	public TalkerWebService (ConnectedNode cn){
		System.out.println("\n\n---------> TalkerWebService Constructor\n\n\n");
		connectedNode = cn;
		talker.onStart(cn);
	}

	@WebMethod(operationName = "getTalkTopic")
	public String setMessage(String s) {
		talker.talkermsg=s;
		count++;
		return "Hello " + talker.talkermsg;
	}

	@WebMethod(operationName = "getData")
	public boolean getData(String name) {
		talker.talkermsg = name;
		return true;
	}
}
