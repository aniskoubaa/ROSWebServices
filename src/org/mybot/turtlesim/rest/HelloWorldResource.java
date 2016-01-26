package org.mybot.turtlesim.rest;



import javax.ws.rs.core.Context;
import javax.ws.rs.core.UriInfo;
import javax.ws.rs.PathParam;
import javax.ws.rs.Consumes;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.GET;
import javax.ws.rs.Produces;

/**
 * REST Web Service
 *
 * @author akoubaa
 */

@Path("helloworld")
public class HelloWorldResource {

	@Context
	private UriInfo context;

	/**
	 * Creates a new instance of HelloWorldResource
	 */
	public HelloWorldResource() {
	}

	/**
	 * Retrieves representation of an instance of org.coins.rest.HelloWorldResource
	 * @return an instance of java.lang.String
	 */
	@GET
	@Path("{name}")
	@Produces("text/plain")
	public String getXml(@PathParam("name") String name) {
		return "Hello World"+name;
	}

	/**
	 * PUT method for updating or creating an instance of HelloWorldResource
	 * @param content representation for the resource
	 * @return an HTTP response with content of the updated or created resource.
	 */
	@PUT
	@Consumes("application/xml")
	public void putXml(String content) {
	}
}
