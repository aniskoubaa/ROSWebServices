#include "coros_node/Node.h"
#include <ros/ros.h>

Node::Node(const std::string& name) : myNH(), myName(name), SubscribersManager(), 	PublishersManager()
{
	SubscribersManager::myNH = &myNH;
	PublishersManager::myNH = &myNH;
	ROS_INFO("Node created successfully: %s", myName.c_str());
}

bool Node::isOK()
{
	return myNH.ok();
}
