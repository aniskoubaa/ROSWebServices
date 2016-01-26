/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlesim.rest.resource;

import com.google.common.base.Preconditions;
import com.sun.jersey.api.container.httpserver.HttpServerFactory;
import com.sun.jersey.api.core.ClassNamesResourceConfig;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.net.URI;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.mybot.turtlesim.rosjava.TurtleSim;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

/**
 *
 * @author ros
 */
public class RobotResourcesEndpointPublisherNode extends AbstractNodeMain{
    
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
                    RobotVelocityResource robotVelocityResource = new RobotVelocityResource(connectedNode);
                    RobotPoseResource robotPoseResource = new RobotPoseResource(connectedNode);
			HttpServer httpServer = HttpServerFactory.create(
					"http://"+TurtleSim.IPAddress+":7003/",new ClassNamesResourceConfig(RobotVelocityResource.class, RobotPoseResource.class ));
			httpServer.start();
                        
                        
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException ex) {
                Logger.getLogger(RobotVelocityResource.class.getName()).log(Level.SEVERE, null, ex);
            } catch (InterruptedException ex) {
                Logger.getLogger(RobotVelocityResource.class.getName()).log(Level.SEVERE, null, ex);
            }

		//Endpoint sei = Endpoint.publish("http://"+TurtleSim.IPAddress+":1238/turtlesim_listerners_ws", new TurtlesimListenersWebService(connectedNode));
	}
        
        
        
    
}
