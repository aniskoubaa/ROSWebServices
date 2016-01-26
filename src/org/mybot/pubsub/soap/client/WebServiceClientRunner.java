package org.mybot.pubsub.soap.client;

import java.net.URI;

import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

import com.google.common.base.Preconditions;

public class WebServiceClientRunner {
	
public static void main(String[] args) {
        
		TalkerWebServiceClient talkerWebServiceClient  = new TalkerWebServiceClient();    
        NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
        URI masteruri = URI.create("http://192.168.100.10:11311");
        String host = "192.168.100.10";
        NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
        Preconditions.checkState(talkerWebServiceClient != null);
        nodeMainExecutor.execute(talkerWebServiceClient, pubNodeConfiguration);
    }

}
