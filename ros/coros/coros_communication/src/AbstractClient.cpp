#include "coros_communication/AbstractClient.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <ros/ros.h>

void AbstractClient::send(const std::string& msg, std::string ip, int port)
{
  ROS_INFO("Client sending message:\n%s... to [%s:%d]", msg.c_str(), ip.c_str(), port); // //TODO: DEBUG VERSION MESSAGE
  
  if ( ip == "" || port == 0)
  {
      ROS_WARN("... message cannot be sent: either the destination IP address or port is not correct.");
      return; 
  }
  int socketID, result;
  struct sockaddr_in toAddr;
  struct hostent *hostInfo;
  
  // Create the socket
  socketID= socket(AF_INET, SOCK_DGRAM, 0);
  if (socketID < 0) 
  {
    ROS_ERROR("... socket creation failed.");
    return;
  }

  // Construct local address structure 
  memset(&toAddr, 0, sizeof(toAddr));
  toAddr.sin_family = AF_INET; 
  toAddr.sin_addr.s_addr = inet_addr(ip.c_str());   
  toAddr.sin_port = htons(port); 
  
  //ROS_INFO("... message size = %d.", msg.length());  //TODO: DEBUG VERSION MESSAGE

  // Send the message
  result = sendto(socketID,(char*) msg.c_str(), msg.length(),0,(const struct sockaddr *)&toAddr, sizeof(struct sockaddr_in));

  if (result < 0) 
  {
    close(socketID);
    ROS_ERROR("... message cannot be sent.");
    return;
  }
  else
  {
    //ROS_INFO("... message sent.");  //TODO: DEBUG VERSION MESSAGE
  }
  
  close(socketID);
}


void AbstractClient::multicast(const std::string& message, std::string destinations[], int ports[], int size)
{
  
  ROS_INFO("Client multicasting message .");
  
  for (int i = 0; i < size; i++)
  {
    //ROS_INFO("[AbstractClient::broadcast] Send message to %s on port %d.",destinations[i].c_str(),ports[i]);
    send(message, destinations[i], ports[i]);
  }
  
}


void AbstractClient::broadcast(const std::string& msg, int destinationBroadcastPort)
{
  ROS_INFO("Client broadcasting a message:\n%s... to [255.255.255.255:%d]", msg.c_str(), destinationBroadcastPort);
  
  int socketID, result;
  unsigned int length;
  struct sockaddr_in broadcastAddress, comingFromAddress;
  int broadcastPermission;   
  struct hostent *hostInfo;
  
  //open a new socket
  socketID= socket(AF_INET, SOCK_DGRAM, 0);
  if (socketID < 0) {
    ROS_ERROR("... socket creation failed.");
    return;
  }
  
  /* Set socket to allow broadcast */
  broadcastPermission = 1;
  if (setsockopt(socketID, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, 
    sizeof(broadcastPermission)) < 0){
    ROS_ERROR("... setsockopt() failed.");
    return;
  }
   
  
  /* Construct local address structure */
  memset(&broadcastAddress, 0, sizeof(broadcastAddress));   /* Zero out structure */
  broadcastAddress.sin_family = AF_INET;                 /* Internet address family */
  const char* broadcastIPAddress = "255.255.255.255";
  broadcastAddress.sin_addr.s_addr = inet_addr(broadcastIPAddress);   /* must be set to Broadcast IP address */
  broadcastAddress.sin_port = htons(destinationBroadcastPort);      /* Broadcast port */
  
  
  ROS_INFO("... message size = %d.", msg.length());
  result = sendto(socketID,(char*) msg.c_str(), msg.length(),0,(const struct sockaddr *)&broadcastAddress, sizeof(struct sockaddr_in));
  
    
  if (result < 0) 
  {
    close(socketID);
    ROS_ERROR("... message cannot be sent.");
    return;
  }
  else
  {
	//ROS_INFO("... message sent.");  //TODO: DEBUG VERSION MESSAGE
  }
  
  close(socketID);
}

