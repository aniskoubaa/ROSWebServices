/*
 * call_robot_operator.cpp
 *
 *  Created on: May 9, 2015
 *      Author: akoubaa
 */
#include <ros/ros.h>
#include "mybot_call_app/CallRequestMsg.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "mybot_call_app/MybotCallOperator.h"


MybotCallOperator::MybotCallOperator(int robotId, const std::string& nodeName) : RobotOperator(robotId, nodeName)
{
	init();
}

void MybotCallOperator::init()
{
	ROS_INFO("Mybot Call Operator intiliazing topics subscription and publication...");

	createSubscriber("req_from_json", "CallRequestMsg/from_json", &MybotCallOperator::requestCallback, this);

	//createPublisher<delivery_app::DeliveryStatusMsg>("sta_to_json", "DeliveryStatusMsg/to_json");
	//createPublisher<delivery_app::DeliveryResultMsg>("res_to_json", "DeliveryResultMsg/to_json");

	ROS_INFO("Mybot Call Operator finished topics initialization.");

	ros::spin();
}


void MybotCallOperator::requestCallback(const mybot_call_app::CallRequestMsg::ConstPtr& msg)
{
	ROS_INFO("Mybot Call Operator received Request message.");

	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> actionClient ("move_base", true);

	//wait for the action server to come up
	while(!actionClient.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}


	move_base_msgs::MoveBaseGoal goal;

	//we'll send a goal to the robot to move 1 meter forward
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = msg->x;
	goal.target_pose.pose.position.y = msg->y;
	goal.target_pose.pose.position.z = 1.0;
	goal.target_pose.pose.orientation.x = 0.0;
	goal.target_pose.pose.orientation.y = 0.0;
	goal.target_pose.pose.orientation.z = 0.0;
	goal.target_pose.pose.orientation.w = 1.0;

	ROS_INFO("Sending goal");
	actionClient.sendGoal(goal);

	actionClient.waitForResult();

	if(actionClient.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO("mybot reached its destination");
	else
		ROS_INFO("mybot failed to reach its destination for some reasons");





}


std::string MybotCallOperator::process(BaseMessage* m)
{
	std::string str = "";
	return str;
}


