/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.rest;

import com.sun.jersey.api.container.httpserver.HttpServerFactory;
import com.sun.jersey.api.core.ClassNamesResourceConfig;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.mybot.turtlesim.rest.resource.RobotPoseResource;
import org.mybot.turtlesim.rest.resource.RobotVelocityResource;
import org.mybot.turtlesim.rosjava.TurtleSim;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;

/**
 *
 * @author ros
 */
public class TurtlebotResourcesEndpointPublisherNode extends AbstractNodeMain{
    @Override
    public GraphName getDefaultNodeName() {
            return GraphName.of("rosjava/resources_publisher/rest_endpoint_publisher_node");
    }

    @Override
    public void onStart(final ConnectedNode connectedNode){		 
            try {
                DeliveryTopicResource deliveryTopicResource = new DeliveryTopicResource(connectedNode);
                    HttpServer httpServer = 
                            HttpServerFactory.create(
                                    "http://"+TurtleSim.IPAddress+":7003/",
                                    new ClassNamesResourceConfig(DeliveryTopicResource.class )
                            );
                    httpServer.start();         
            } catch (Exception e) {
                    e.printStackTrace();
            } 
    }
}
