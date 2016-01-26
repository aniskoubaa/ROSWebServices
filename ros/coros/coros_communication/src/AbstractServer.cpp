#include "coros_communication/AbstractServer.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

#include <ros/ros.h>
#include <string.h>

AbstractServer::AbstractServer(const int& port){
  setPort(port);
}


bool AbstractServer::bind()
{
  ROS_INFO("Server socket binding...");
  
  int length, n;
  socklen_t fromlen;
  struct sockaddr_in server;
  char buf[1024];
  
  mySocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (mySocket < 0)
  { 
    ROS_ERROR("Server fail when creating a socket.");
    return false;
  }
  else
  {
    ROS_INFO("Server socket created...");
  }
  
  length = sizeof(server);
  bzero(&server,length);
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(getPort());
  
  if (::bind(mySocket,(struct sockaddr *)&server,length) < 0)
  {
    ROS_ERROR("Server error in binding the socket on port %d", getPort());
    return false;
  } 
  else
  {
    ROS_INFO("Server socket bound on port %d.", getPort());  
  }
  return true;
}

void AbstractServer::listen()

{
  ROS_INFO("Server started...");

  struct sockaddr_in from;
  socklen_t fromlen = sizeof(struct sockaddr_in);
  
  while (again()) {
	char* buffer_msg = new char[1024];
    ROS_INFO("Server is now listening on port %d.", getPort());
    memset(buffer_msg, '\0', sizeof(1024));
    int n = recvfrom(mySocket, buffer_msg, 1023, 0, (struct sockaddr *)&from, &fromlen);
    
    if (n < 0) 
    {
      ROS_ERROR("Server receives an empty message.");
    } 
    else
    {
      ROS_INFO("Server received %d bytes from: %s - (%s) ", n, inet_ntoa(from.sin_addr), buffer_msg);
      process(buffer_msg, inet_ntoa(from.sin_addr)); // In the most of our cases, forwards the message to the relevant ROS topic/node.
    }
  
  }
  ros::spin();      
}

