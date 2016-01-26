/*
 * mybot_call_operator_app.cpp
 *
 *  Created on: May 9, 2015
 *      Author: akoubaa
 */


#include "mybot_call_app/MybotCallOperator.h"

int main(int argc, char *argv[])
{

  if (argc<3){
     ROS_ERROR("Usage: rosrun mybot_call_all mybot_call_operator_app_node [node_name] [agent_id]");
    return 0;
  }

  std::string nodeName = argv[1];
  int agentId 	       = atoi(argv[3]);


  ros::init(argc, argv, nodeName);
  ros::NodeHandle nh ("~");



  if (agentId!=-1){
	  MybotCallOperator mybotCallOperator(agentId, nodeName);
  }

  return 0;
}

