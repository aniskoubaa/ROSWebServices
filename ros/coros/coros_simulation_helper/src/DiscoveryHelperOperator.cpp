#include <ros/ros.h>
#include "coros_common/string_lib.h"
#include "coros_common/serial_lib.h"
#include "coros_common/globals.h"

#include "coros_messages/HelloMessage.h"
#include "coros_messages/NeighborhoodMsg.h"
#include "coros_simulation_helper/DiscoveryHelperOperator.h"


DiscoveryHelperOperator::DiscoveryHelperOperator(const std::string& nodeName) : SimpleOperator(nodeName)
{
	init();
}


void DiscoveryHelperOperator::init()
{
  ROS_INFO("[Simulation Operator] Subscribing to topics...");
  createSubscriber("hello_sub", "agent_simulation/hello_topic", &DiscoveryHelperOperator::helloCallback, this); // Connection Subscriber
  ROS_INFO("[Simulation Operator] Subscription to topics completed.");
  ros::spin();
}


void DiscoveryHelperOperator::helloCallback(const coros_messages::HelloMsg::ConstPtr& msg)
{
  ROS_INFO("\n[Simulation Operator] [Event]: received HELLO message: \n%s.", mtos(*msg).c_str());
  int message_code = msg->message_code;
  
  if (message_code == HELLO_FROM_CONTROL_STATION)
  {
	  ROS_INFO("[Simulation Operator] [Event]: received HELLO message from a Control Station: \n%s. \n\t[Action]: Update Control Station information", mtos(*msg).c_str());
  }
  else if (message_code == HELLO_FROM_ROBOT)
  {
    ROS_INFO("[Simulation Operator]: [Event]: Received HELLO message from an agent: \n%s" , mtos(*msg).c_str());
	ROS_INFO("[Simulation Operator]: [Action]: Add robot to robot neighbor list.");

	AgentState* newNeighborAgent = new AgentState(msg->id, msg->ip, msg->timestamp, msg->port, msg->role, msg->status);
	HelloMessage hello_from_new(HELLO_FROM_ROBOT, msg->id, msg->ip, msg->port, msg->timestamp, msg->role, msg->status);
    std::string new_msg_str = serializeMessage(hello_from_new);


   	int size = myNeighbors.size();
	for (unsigned i=0; i<size; i++)
	{
	   // send new agent info to old agent
       send(new_msg_str, myNeighbors.at(i)->getIpAddress(), myNeighbors.at(i)->getPort());

	   // send old agent info to new agent
	   HelloMessage hello_from_old(HELLO_FROM_ROBOT, myNeighbors.at(i)->getId(), myNeighbors.at(i)->getIpAddress(), myNeighbors.at(i)->getPort(), myNeighbors.at(i)->getTimestamp(), myNeighbors.at(i)->getRole(), myNeighbors.at(i)->getStatus());
	   std::string old_msg_str = serializeMessage(hello_from_old);
	   send(new_msg_str, newNeighborAgent->getIpAddress(), newNeighborAgent->getPort());

	}

	myNeighbors.push_back(newNeighborAgent);

  }
  else{
    ROS_WARN("\n[Simulation Operator]\n\t\t[WARNING]: received an unknown HELLO message type.\n\t\t[Action]: Check issue in Discovery Robot Operator\n");
  }
}
