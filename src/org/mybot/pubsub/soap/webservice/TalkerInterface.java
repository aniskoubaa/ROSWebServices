package org.mybot.pubsub.soap.webservice;

import javax.jws.WebService;
import javax.jws.WebMethod;


@WebService
public interface TalkerInterface {

	@WebMethod
	public String setMessage(String s);


}
