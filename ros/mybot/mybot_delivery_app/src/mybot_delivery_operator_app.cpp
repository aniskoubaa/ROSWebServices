/*
 * mybot_delivery_operator_app.cpp
 *
 *  Created on: May 17, 2015
 *      Author: mfsriti
 */


#include "mybot_delivery_app/MybotDeliveryOperator.h"

int main(int argc, char *argv[])
{

  if (argc<3){
     ROS_ERROR("Usage: rosrun mybot_delivery_all mybot_delivery_operator_app_node [node_name] [agent_id]");
    return 0;
  }

  std::string nodeName = argv[1];
  int agentId 	       = atoi(argv[3]);


  ros::init(argc, argv, nodeName);
  ros::NodeHandle nh ("~");



  if (agentId!=-1){
	  MybotDeliveryOperator mybotDeliveryOperator(agentId, nodeName);
  }

  return 0;
}

