#include "discovery_app_2/DiscoveryOperator.h"
#include "discovery_app_2/DiscoveryConfiguration.h"
#include "coros_common/string_lib.h"
#include <coros_messages/IPAddressService.h>
#include <std_msgs/String.h>

std::string ip_address ="127.0.0.1";
DiscoveryConfiguration* config;



int main(int argc, char *argv[])
{

  if (argc<4)
  {
    ROS_ERROR("Usage: rosrun discovery_app_2 discovery_operator_app_2_node [node_name] [running_mode] [agent_id]");
    return 0;
  }
  
  std::string nodeName = argv[1];
  int runningMode      = atoi(argv[2]);
  int agentId 		   = atoi(argv[3]);

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
  



  std::string agent_role ="";
  std::string agent_name ="robot_with_no_name";
  double helloFreq = 6.0;
  int port_number =-1;
  int init_port =-1;

  nh.getParam("ip_address",ip_address);
  nh.getParam("agent_name",agent_name);
  nh.getParam("agent_role",agent_role);
  nh.getParam("hello_frequency",helloFreq);
  nh.getParam("port_number",port_number);
  nh.getParam("init_port",init_port);
  if (runningMode == AgentConfiguration::SIMULATION_RUN_MODE)
	  port_number += agentId; // also, to have different port number in the simulation machine

  config = DiscoveryConfiguration::getInstance();

  ros::ServiceClient client = nh.serviceClient<coros_messages::IPAddressService>("/ip_address_service");
  ros::service::waitForService("ip_address_service", 10);
  coros_messages::IPAddressService service;
  service.request.ip_address_request="local_ip";
    //srv.request. = atoll(argv[1]);
    //srv.request.b = atoll(argv[2]);

    if (client.call(service))
    {
    	ip_address = service.response.ip_address_response;
      ROS_INFO("\n\n\nIP: %s\n\n\n", service.response.ip_address_response.c_str());
    }
    else
    {
      ROS_ERROR("Failed to call service ip_address_service. \nMake sure to start the service ip_address_service defined in coros_communication package");
      return 1;
    }


  //agent related config.
  config->setAgentId(agentId);
  config->setAgentAddress(ip_address);
  config->setAgentTimestamp(ros::Time::now().toSec());
  config->setAgentPort(port_number);
  config->setAgentRole(agent_role);
  config->setAgentName(agent_name);

  //running related config.
  config->setRunningMode(runningMode);
  config->setInitSimulationPort(init_port);

  //discovery related config.
  config->setBroadcastFrequency(helloFreq);

  if (agentId!=-1){
	  DiscoveryOperator disop(nodeName);
  }
  //ros::spin();
  return 0;
}
 
