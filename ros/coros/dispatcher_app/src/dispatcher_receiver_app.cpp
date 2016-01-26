#include "dispatcher_app/DispatcherReceiver.h"
#include "dispatcher_app/DispatcherConfiguration.h"
#include "coros_common/string_lib.h"

int main(int argc, char *argv[])
{
  
  if (argc<5)
  {
    ROS_ERROR("Usage: rosrun dispatcher_app dispatcher_receiver_app_node [node_name] [running_mode] [agent_id] [port_number] ");
    return 0;
  }

  std::string nodeName = argv[1];
  int runningMode      = atoi(argv[2]);
  int agentId 	       = atoi(argv[3]);
  int portNumber       = atoi(argv[4]);
  
  switch (runningMode)
  {
        case AgentConfiguration::SIMULATION_RUN_MODE:
          portNumber += agentId; // also, to have different port number in the simulation machine
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

  std::vector<std::string> topics_list;
  nh.getParam("inbox_topics_list", topics_list);

  DispatcherConfiguration* config = DispatcherConfiguration::getInstance();
  config->setAgentId(agentId);
  config->setAgentTimestamp(ros::Time::now().toSec());
  config->setAgentPort(portNumber);

  //dipatcher app. related config.
  config->setTopics(topics_list);

  if (agentId!=-1){
    DispatcherReceiver receiver(nodeName, portNumber);
    if (receiver.bind()){
      receiver.listen();
    }
  }

  return 0;
}
