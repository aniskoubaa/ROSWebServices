package org.mybot.turtlesim.rest;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import org.mybot.turtlesim.rosjava.TurtlesimListeners;
import static org.mybot.turtlesim.soap.TurtlesimListenersWebService.turtlesimListeners;
import org.ros.node.ConnectedNode;

@Path("turtlesim")//URI used to access the resource
public class TurtlesimListenerRESTWebService {
    
    public static TurtlesimListeners turtlesimListeners;
    static ConnectedNode connectedNode ;
    
    public TurtlesimListenerRESTWebService (){
        
    }
            
    public TurtlesimListenerRESTWebService (ConnectedNode connectedNode) throws InterruptedException{
		System.out.println("\n\n---------> TurtlesimListenersWebService Constructor\n\n\n");
		//connectedNode = new ConnectedNode();
                turtlesimListeners = new TurtlesimListeners();
                //Thread.sleep(2000);
		turtlesimListeners.onStart(connectedNode);
	}
	
	@GET //Handle HTTP Get requests
	@Path("{pose}") //URI components containing the parameter
	@Produces ("text/plain")
	public String getXml(){
            return String.format("(%.2f, %.2f, %.2f)",
				turtlesimListeners.getTurtlesimPose().getX(),
				turtlesimListeners.getTurtlesimPose().getY(),
				turtlesimListeners.getTurtlesimPose().getTheta());
		//String message = "Hello";
		//return message;
	}
}
