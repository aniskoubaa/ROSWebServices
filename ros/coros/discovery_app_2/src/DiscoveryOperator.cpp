#include <ros/ros.h>
#include "coros_common/string_lib.h"
#include "coros_common/globals.h"

#include "coros_messages/HelloMessage.h"
#include "coros_messages/NeighborhoodMsg.h"
#include "discovery_app_2/DiscoveryOperator.h"

#include "discovery_app_2/DiscoveryConfiguration.h"




DiscoveryOperator::DiscoveryOperator(const std::string& nodeName) : SimpleOperator(nodeName)
{
  //myAgentId = agentId;

  //robotLocalIP is input by user in command line (avoid difficulty of getting local IP address from socket
  //hello_AgentLocalIPAddress = agentLocalIP;
  //hello_frequency=freqInSeconds;

  myLocalConfig = DiscoveryConfiguration::getInstance();

  myNeighborsConfig = NeighborsConfiguration::getInstance();

  init();
  
}

void DiscoveryOperator::init()
{
  ROS_INFO("\n[Discovery Operator]\n\tSubscribing to topics...");
  
  //createSubscriber("hello_sub", "agent"+itos(myLocalConfig->getAgentId())+"/hello_topic", &DiscoveryOperator::helloCallback, this); // Connection Subscriber
  createSubscriber("from_json", "HelloMsg/from_json", &DiscoveryOperator::helloCallback, this); // Connection Subscriber

  createSubscriber("local_ip_address", "local_ip_address", &DiscoveryOperator::IPAddressCallback, this); // IP Address Subscriber

  createService(std::string("neighbor_service"), std::string("agent"+itos(myLocalConfig->getAgentId())+"/neighbor_service"), &DiscoveryOperator::neighborServiceCallback, this);
 
  createPublisher<coros_messages::NeighborhoodMsg>("neighborhood_pub", "agent"+itos(myLocalConfig->getAgentId())+"/neighborhood_list"); // Neighborhood Publisher

  createPublisher<coros_messages::HelloMsg>("to_json", "HelloMsg/to_json"); // To JSON Publisher
  
  ROS_INFO("\n[Discovery Operator]\n\tSubscription to topics completed.\n\t\t[Action]: Start broadcasting HELLO messages.\n");

  ros::AsyncSpinner spinner (2);
  spinner.start();
  broadcast_hello_message(myLocalConfig->getBroadcastFrequency());
  spinner.stop();

}

void DiscoveryOperator::broadcast_hello_message(double freqInSeconds){
  //impose frequency to be larger than 5 seconds
  //freqInSeconds = ((freqInSeconds>5.0)?freqInSeconds:5.0);

  if( myLocalConfig->getAgentRunningMode() == AgentConfiguration::SIMULATION_RUN_MODE )
  {
	  ROS_INFO("[Discovery Operator]: broadcast the first HELLO message to initialize simulation...");
	 // HelloMessage hello_message(HELLO_FROM_ROBOT, myLocalConfig->getAgentId(), myLocalConfig->getAgentAddress(), myLocalConfig->getAgentPort(), ros::Time::now().toSec(), myLocalConfig->getAgentRole(), myLocalConfig->getAgentStatus());

	   coros_messages::HelloMsg hello_message;
	   hello_message.message_code = HELLO_FROM_ROBOT;
	   hello_message.id = myLocalConfig->getAgentId();
	   hello_message.ip = myLocalConfig->getAgentAddress();
	   hello_message.name = myLocalConfig->getAgentName();
	   hello_message.port = myLocalConfig->getAgentPort();
	   hello_message.timestamp = ros::Time::now().toSec();
	   hello_message.role = myLocalConfig->getAgentRole();
	   hello_message.status = myLocalConfig->getAgentStatus();

	  //old boost serialization
          //std::string msg_str = serializeMessage(hello_message);
	  //send(msg_str, myLocalConfig->getAgentAddress(), myLocalConfig->getInitSimulationPort());

          //new json serialization
	  //publishMessage("to_json", hello_message);
  }
  
  // TODO: Check in the loop that if a robot did not sent any hello message from a long time (30 seconds for example), its entry will be dropped from the neighbors table

  while (ros::ok()){
    ROS_INFO("[Discovery Operator]: broadcast a new HELLO message ...");
    //HelloMessage hello_message(HELLO_FROM_ROBOT, myLocalConfig->getAgentId(), myLocalConfig->getAgentAddress(), myLocalConfig->getAgentPort(), ros::Time::now().toSec(), myLocalConfig->getAgentRole(), myLocalConfig->getAgentStatus());
    //std::string msg_str = serializeMessage(hello_message);

   coros_messages::HelloMsg hello_message;
   hello_message.message_code = HELLO_FROM_ROBOT;
   hello_message.id = myLocalConfig->getAgentId();
   hello_message.name = myLocalConfig->getAgentName();
   hello_message.ip = myLocalConfig->getAgentAddress();
   hello_message.port = myLocalConfig->getAgentPort();
   hello_message.timestamp = ros::Time::now().toSec();
   hello_message.role = myLocalConfig->getAgentRole();
   hello_message.status = myLocalConfig->getAgentStatus();
        
   if (myLocalConfig->getAgentRunningMode() == AgentConfiguration::SIMULATION_RUN_MODE)
    {
    	vector<std::string> destinations;
    	vector<int> ports;
    	int size = 0;

    	std::vector<AgentState*> neighborAgents = myNeighborsConfig->getNeighbors();
    	size = neighborAgents.size();
		for (unsigned i=0; i<size; i++){
	      destinations.push_back(neighborAgents.at(i)->getIpAddress());
    	  ports.push_back(neighborAgents.at(i)->getPort());
    	}
	hello_message.header.distribution_mode="multicast";
	hello_message.header.ip_addresses=destinations;
	hello_message.header.ports=ports;	
       //multicast(msg_str, &destinations[0], &ports[0], size);
    }
    else {  //if(myLocalConfig->getAgentRunningMode() == AgentConfiguration::EXPERIMENTAL_RUN_MODE)
        hello_message.header.distribution_mode="broadcast";
	hello_message.header.ports.push_back(myLocalConfig->getAgentPort());
        //broadcast(msg_str, myLocalConfig->getAgentPort());
    }
    
    publishMessage("to_json", hello_message);
    
    usleep(freqInSeconds*1000*1000); 
  }
  
}

void DiscoveryOperator::IPAddressCallback(std_msgs::String ip_address_msg){
	myLocalConfig->setAgentAddress(ip_address_msg.data);
	//ROS_INFO("\nmyLocalConfig->getAgentAddress(ip_address_msg.data) = %s \n\n\n", myLocalConfig->getAgentAddress().c_str());
}


bool DiscoveryOperator::neighborServiceCallback(coros_messages::neighborhood::Request &req,
		coros_messages::neighborhood::Response &resp){
  
  ROS_INFO("\n[Discovery Operator]\n\t\t[Event]: Neighbor Service Callback Function");
  //int nSize = neighborAgents.size();

  
  resp.robot_ip_addresses.push_back("192.168.1.102");
  resp.robot_ip_addresses.push_back("192.168.1.124");
  resp.robot_ip_addresses.push_back("192.168.1.153");
  //resp.robot_ip_addresses[1]="192.168.1.105";
  
  ROS_INFO("request: code=%ld, ", (long int)req.code);
  ROS_INFO("sending back response");
  return true;
   
   
}

void DiscoveryOperator::helloCallback(const coros_messages::HelloMsg::ConstPtr& msg)
{

  ROS_INFO("\n[Discovery Operator]\n\t\t[Event]: received HELLO message: \n%s.", mtos(*msg).c_str());
  int message_code = msg->message_code;
  
  if (message_code == HELLO_FROM_CONTROL_STATION) {// HELLO MESSAGE COMING FROM CONTROL STATION 
    ROS_INFO("\n[Discovery Operator]\n\t\t[Event]: received HELLO message from a Control Station: \n%s. \n\t\t[Action]: Update Control Station information", mtos(*msg).c_str());
    //myControlStationIP = msg->ip;
    //myControlStationPort = msg->port;
    
  }
  else if (msg->id == myLocalConfig->getAgentId())
  {
    //update the internal agent state
	myLocalConfig->setAgentTimestamp(ros::Time::now().toSec());
	myLocalConfig->setAgentRole(msg->role);
	myLocalConfig->setAgentStatus(msg->status);
  }
  else if (message_code == HELLO_FROM_ROBOT)
  {
    ROS_INFO("[Discovery Operator]: [Event]: Received HELLO message from an agent: \n%s" , mtos(*msg).c_str());
	ROS_INFO("[Discovery Operator]: [Action]: Add robot to robot neighbor list.");

	AgentState* newNeighborAgent = new AgentState(msg->id, msg->ip, msg->timestamp, msg->port, msg->role, msg->status);
	myNeighborsConfig->addNeighbor(newNeighborAgent);
	myNeighborsConfig->printNeighbors();

	/*
	hello_robot_info_type newNeighborRobot;
    newNeighborRobot.id = msg->id;
    newNeighborRobot.ip = msg->ip;
    newNeighborRobot.port = msg->port;
    newNeighborRobot.timestamp = msg->timestamp;
    */

    // check if the robots is already in the neighbor list
    /*bool robotExists = false;
    unsigned int robotIndex=-1;
    for (unsigned int i=0; i<neighborAgents.size(); i++){
      if (neighborAgents.at(i).id == newNeighborRobot.id){
	robotExists = true;
	robotIndex=i;
	break;
      }
    }
    //if the robot exist, delete it to add a new entry with new timestamp
    if (robotExists)
    	neighborAgents.erase(neighborAgents.begin() + robotIndex);
    
    //add the robot to the neighbor list
    neighborAgents.push_back(newNeighborRobot); */
    

   
    /** publish the new neighborhood_list */
	std::vector<AgentState*> neighborAgents = myNeighborsConfig->getNeighbors();
    coros_messages::NeighborhoodMsg m;
    for (unsigned i=0; i<neighborAgents.size(); i++){
      m.ids.push_back(neighborAgents.at(i)->getId());
      m.ip_addresses.push_back(neighborAgents.at(i)->getIpAddress());
      m.ports.push_back(neighborAgents.at(i)->getPort());
      m.timestamps.push_back(ros::Time::now().toSec());
      m.roles.push_back(neighborAgents.at(i)->getRole());
      m.statuses.push_back(neighborAgents.at(i)->getStatus());
    }
   
    publishMessage("neighborhood_pub", m);
  }
  else{
    ROS_WARN("\n[Discovery Operator]\n\t\t[WARNING]: received an unknown HELLO message type.\n\t\t[Action]: Check issue in Discovery Robot Operator\n");
  }
}
