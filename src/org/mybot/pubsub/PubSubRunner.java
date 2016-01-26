package org.mybot.pubsub;

import org.ros.node.DefaultNodeMainExecutor;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;
import com.google.common.base.Preconditions;
import java.net.URI;

public class PubSubRunner{ 
    
    public static void main(String[] args) {
        Talker pubNodeMain = new Talker();
        Listener subNodeMain = new Listener();    
        NodeMainExecutor nodeMainExecutor = DefaultNodeMainExecutor.newDefault();        
        URI masteruri = URI.create("http://127.0.0.1:11311");
        String host = "127.0.0.1";
        NodeConfiguration pubNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);
        Preconditions.checkState(pubNodeMain != null);
        nodeMainExecutor.execute(pubNodeMain, pubNodeConfiguration);
        NodeConfiguration subNodeConfiguration = NodeConfiguration.newPublic(host, masteruri);   
        Preconditions.checkState(subNodeMain != null);
        nodeMainExecutor.execute(subNodeMain, subNodeConfiguration);
    }
}

