#include "delivery_app/DeliveryUser.h"
#include "delivery_app/DeliveryConfiguration.h"

using namespace std;

int main(int argc, char *argv[])
{  
 if (argc<4){
     ROS_ERROR("Usage: rosrun delivery_app delivery_user_app_node [node_name] [running_mode] [agent_id]");
    return 0;
  }
  
  std::string nodeName = argv[1];
  int runningMode      = atoi(argv[2]);
  int agentId 	       = atoi(argv[3]);
  
  switch (runningMode)
  {
    case AgentConfiguration::SIMULATION_RUN_MODE:
  	  ROS_INFO("[%s] RUNING IN SIMULATION MODE.", nodeName.c_str());
  	  break;
  	case AgentConfiguration::EXPERIMENTAL_RUN_MODE:
  	  ROS_INFO("[%s] RUNING IN EXPERIMENTAL MODE.", nodeName.c_str());
  	  break;
  	default:
  	  ROS_INFO("[%s] UNKNOWN RUNING MODE.", nodeName.c_str());
  	  return 0; 
  }
   
  ros::init(argc, argv, nodeName);
  ros::NodeHandle nh ("~");

  std::string ip_address ="127.0.0.1";
  std::string agent_role ="";
  int port_number =-1;

  nh.getParam("ip_address",ip_address);
  nh.getParam("agent_role",agent_role);
  nh.getParam("port_number",port_number);

  if (runningMode == AgentConfiguration::SIMULATION_RUN_MODE)
	  port_number += agentId; // also, to have different port number in the simulation machine

  DeliveryConfiguration* config = DeliveryConfiguration::getInstance();

  //agent related config.
  config->setAgentId(agentId);
  config->setAgentAddress(ip_address);
  config->setAgentTimestamp(ros::Time::now().toSec());
  config->setAgentPort(port_number);
  config->setAgentRole(agent_role);
 
  //running related config.
  config->setRunningMode(runningMode);
  
  if (agentId != -1) {
    DeliveryUser delus(nodeName);
  }
  
  return 0;
}
