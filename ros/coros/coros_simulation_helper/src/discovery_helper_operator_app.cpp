#include "coros_simulation_helper/DiscoveryHelperOperator.h"

int main(int argc, char *argv[])
{

  if (argc<4)
  {
    ROS_ERROR("Usage: rosrun coros_simulation_helper discovery_helper_operator_app_node [node_name]");
    return 0;
  }
  
  std::string nodeName = argv[1];

  ROS_INFO("[%s] ALWAYS RUNING IN SIMULATION MODE.", nodeName.c_str());
  
  ros::init(argc, argv, nodeName);
  ros::NodeHandle nh ("~");
  
  DiscoveryHelperOperator disop(nodeName);

  return 0;
}
 
