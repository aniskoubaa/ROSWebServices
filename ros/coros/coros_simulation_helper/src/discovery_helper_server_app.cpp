#include "coros_simulation_helper/DiscoveryHelperServer.h"

int main(int argc, char *argv[])
{
  
  if (argc<5)
  {
    ROS_ERROR("Usage: rosrun coros_simulation_helper discovery_helper_server_app_node [node_name] [port_number] ");
    return 0;
  }

  std::string nodeName = argv[1];
  int portNumber       = atoi(argv[2]);
  
  ROS_INFO("[%s] ALWAYS RUNING IN SIMULATION MODE.", nodeName.c_str());

  ros::init(argc, argv, nodeName);
  ros::NodeHandle nh ("~");

  DiscoveryHelperServer server(nodeName, portNumber);
  if (server.bind()){
     server.listen();
  }

  return 0;
}
