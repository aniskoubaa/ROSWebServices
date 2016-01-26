package org.mybot.turtlesim.rest;


import com.sun.jersey.api.container.httpserver.HttpServerFactory;
import com.sun.jersey.api.core.ClassNamesResourceConfig;
import java.io.IOException;
import java.net.URI;

import javax.xml.ws.Endpoint;

import org.mybot.turtlesim.rosjava.TurtleSim;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;


//import com.sun.jersey.api.container.httpserver.HttpServerFactory;
//import com.sun.jersey.api.core.ClassNamesResourceConfig;
import com.sun.net.httpserver.HttpServer;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.mybot.turtlesim.rosjava.TurtlesimListeners;

//import org.glassfish.jersey.jdkhttp.JdkHttpServerFactory;
//import org.glassfish.jersey.server.ResourceConfig;

public class TurtlsimListernersRESTWebServiceEndpointPublisherNode extends AbstractNodeMain {
    
    

	@Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlesim_listerners/endpoint_rest_publisher");
	}

	@Override
	public void onStart(final ConnectedNode connectedNode){
		/*HttpServer d = JdkHttpServerFactory.createHttpServer(
	            URI.create("http://localhost:9012"), 
	           new ResourceConfig().register(new TurtlesimListenerRESTWebService()));
	           */  
		 
		try {
                    TurtlesimListenerRESTWebService turtlesimListenerRESTWebService = new TurtlesimListenerRESTWebService(connectedNode);
			HttpServer create = HttpServerFactory.create(
					"http://"+TurtleSim.IPAddress+":7001/",new ClassNamesResourceConfig(TurtlesimListenerRESTWebService.class));
			create.start();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException ex) {
                Logger.getLogger(TurtlsimListernersRESTWebServiceEndpointPublisherNode.class.getName()).log(Level.SEVERE, null, ex);
            } catch (InterruptedException ex) {
                Logger.getLogger(TurtlsimListernersRESTWebServiceEndpointPublisherNode.class.getName()).log(Level.SEVERE, null, ex);
            }

		//Endpoint sei = Endpoint.publish("http://"+TurtleSim.IPAddress+":1238/turtlesim_listerners_ws", new TurtlesimListenersWebService(connectedNode));
	}

}
