#include "dispatcher_app/DispatcherSender.h"
#include "dispatcher_app/DispatcherConfiguration.h"
#include "coros_common/string_lib.h"

int main(int argc, char *argv[])
{

  if (argc<4)
  {
    ROS_ERROR("Usage: rosrun dispatcher_app dispatcher_sender_app_node [node_name] [running_mode] [agent_id]");
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
  	  return 0; // finish the program
  }
  
  ros::init(argc, argv, nodeName);
  ros::NodeHandle nh ("~");

  std::string ip_address ="127.0.0.1";
  int port_number =-1;
  std::vector<std::string> topics_list;

  nh.getParam("ip_address", ip_address);
  nh.getParam("port_number", port_number);
  nh.getParam("outbox_topics_list", topics_list);
  
  if (runningMode == AgentConfiguration::SIMULATION_RUN_MODE)
	  port_number += agentId; // also, to have different port number in the simulation machine

  DispatcherConfiguration* config = DispatcherConfiguration::getInstance();

  //agent related config.
  config->setAgentId(agentId);
  config->setAgentAddress(ip_address);
  config->setAgentTimestamp(ros::Time::now().toSec());
  config->setAgentPort(port_number);

  //running related config.
  config->setRunningMode(runningMode);

  //dipatcher app. related config.
  config->setTopics(topics_list);

  if (agentId!=-1){
	  DispatcherSender sender(nodeName);
  }

  return 0;
}
 
