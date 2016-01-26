/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.rest;

import com.sun.jersey.api.client.Client;
import com.sun.jersey.api.client.WebResource;
import java.util.Scanner;





public class MyRestClient {
 
  public static void main(String[] args) {
      Client c = Client.create();
      WebResource resource = c.resource("http://localhost:7003/robot/app/delivery/code/3/depot_x/76.02/depot_y/45.35/dest_x/76.02/dest_y/41.35/source_x/73.25/source_y/4135");
      System.out.println("Send command");
      
      Scanner sc = new Scanner(System.in);
      String s="";
      do{
      s = sc.next();
      long t0= System.currentTimeMillis();
      String response = resource.get(String.class);
      long t1= System.currentTimeMillis();
      System.out.println("Execution Time: "+ (t1-t0) );
      } while(!s.equals("q"));
      
      
  }
}
