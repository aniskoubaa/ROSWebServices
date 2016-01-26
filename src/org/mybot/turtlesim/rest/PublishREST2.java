package org.mybot.turtlesim.rest;

import com.sun.jersey.api.container.httpserver.HttpServerFactory;
import com.sun.jersey.api.core.ClassNamesResourceConfig;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;


public class PublishREST2 {
    
    public static void main(String[] args) throws IllegalArgumentException, IOException {
    	/*HttpServer create = HttpServerFactory.create(
                "http://192.168.100.17:9015/",new ClassNamesResourceConfig(HelloWorldResource.class));
        create.start();*/

        HttpServer create;
        try {
            create = HttpServerFactory.create(
                    "http://192.168.1.112:9016/",new ClassNamesResourceConfig(HelloWorldResource.class));
            create.start();
        } catch (IllegalArgumentException ex) {
            Logger.getLogger(PublishREST2.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
}
