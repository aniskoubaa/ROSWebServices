/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlesim.rest;

import com.sun.jersey.api.container.httpserver.HttpServerFactory;
import com.sun.jersey.api.core.ClassNamesResourceConfig;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.mybot.turtlesim.rosjava.TurtleSim;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;

/**
 *
 * @author akoubaa
 */
public class TurtlsimVelocityPublisherResourceEndpointPublisherNode extends AbstractNodeMain{
    
    @Override
	public GraphName getDefaultNodeName() {
		return GraphName.of("rosjava/turtlesim_velocity_publisher/endpoint_rest_publisher");
	}

	@Override
	public void onStart(final ConnectedNode connectedNode){
		/*HttpServer d = JdkHttpServerFactory.createHttpServer(
	            URI.create("http://localhost:9012"), 
	           new ResourceConfig().register(new TurtlesimListenerRESTWebService()));
	           */  
		 
		try {
                    TurtlesimVelocityPublisherResource turtlesimVelocityPublisherResource = new TurtlesimVelocityPublisherResource(connectedNode);
			HttpServer create = HttpServerFactory.create(
					"http://"+TurtleSim.IPAddress+":7003/",new ClassNamesResourceConfig(TurtlesimVelocityPublisherResource.class));
			create.start();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException ex) {
                Logger.getLogger(TurtlesimVelocityPublisherResource.class.getName()).log(Level.SEVERE, null, ex);
            } catch (InterruptedException ex) {
                Logger.getLogger(TurtlesimVelocityPublisherResource.class.getName()).log(Level.SEVERE, null, ex);
            }

		//Endpoint sei = Endpoint.publish("http://"+TurtleSim.IPAddress+":1238/turtlesim_listerners_ws", new TurtlesimListenersWebService(connectedNode));
	}
    
}
