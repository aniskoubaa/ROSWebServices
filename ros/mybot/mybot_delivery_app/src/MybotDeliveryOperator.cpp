/*
 * MybotDeliveryOperator.cpp
 *
 *  Created on: May 17, 2015
 *      Author: mfsriti
 */
#include <ros/ros.h>
#include "mybot_delivery_app/DeliveryRequestMsg.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "mybot_delivery_app/MybotDeliveryOperator.h"
#include <std_msgs/String.h>


const  int MybotDeliveryOperator::HELLO_MESSAGE_CODE=0;
const  int MybotDeliveryOperator::GO_TO_GOAL_MESSAGE_CODE=1;
const  int MybotDeliveryOperator::COURIER_DELIVERY_MESSAGE_CODE=3;
const  int MybotDeliveryOperator::COFFEE_DELIVERY_MESSAGE_CODE=4;

MybotDeliveryOperator::MybotDeliveryOperator(int robotId, const std::string& nodeName) : RobotOperator(robotId, nodeName)
{
	init();

}

void MybotDeliveryOperator::init()
{
	ROS_INFO("Mybot Delivery Operator intiliazing topics subscription and publication...");

	createSubscriber("req_from_json", "DeliveryRequestMsg/from_json", &MybotDeliveryOperator::requestCallback, this);

	createPublisher<std_msgs::String>("arm_position", "/arbotixArmController/arm_position_topic");
	//createPublisher<delivery_app::DeliveryResultMsg>("res_to_json", "DeliveryResultMsg/to_json");

	ROS_INFO("Mybot Delivery Operator finished topics initialization.");

	path_to_voices = "/home/ros/Dropbox/mybot_ws/src/mybot/mybot_delivery_app/voices/";
	path_to_sounds = "/home/ros/Dropbox/mybot_ws/src/mybot/mybot_delivery_app/sounds/";
	sc.playWave(path_to_voices+"assalam.wav");
	ros::spin();
}


void MybotDeliveryOperator::requestCallback(const mybot_delivery_app::DeliveryRequestMsg::ConstPtr& msg)
{
	if (msg->message_code == COURIER_DELIVERY_MESSAGE_CODE){
		ROS_INFO("Processing Delivery Request");
		processDeliveryRequest(msg);
	}else if (msg->message_code == COFFEE_DELIVERY_MESSAGE_CODE){
		ROS_INFO("Processing Coffee Request");
		processCoffeeRequest(msg);
	}

}

bool MybotDeliveryOperator::moveTo(double x, double y)
{
	static actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> actionClient ("move_base", true);

	//wait for the action server to come up
	while(!actionClient.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}


	move_base_msgs::MoveBaseGoal goal;

	//we'll send a goal to the robot to move 1 meter forward
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = x;
	goal.target_pose.pose.position.y = y;
	goal.target_pose.pose.position.z = 1.0;
	goal.target_pose.pose.orientation.x = 0.0;
	goal.target_pose.pose.orientation.y = 0.0;
	goal.target_pose.pose.orientation.z = 0.0;
	goal.target_pose.pose.orientation.w = 1.0;

	ROS_INFO("Sending goal");
	actionClient.sendGoal(goal);

	actionClient.waitForResult();

	if(actionClient.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
		ROS_INFO("mybot reached its destination");
		//change this to relative path, see this code http://ros-by-example.googlecode.com/svn/trunk/rbx_vol_1/rbx1_speech/nodes/talkback.py
		sc.playWave(path_to_sounds+"PhoneBellRingingSound.wav");
		sleep(1);
		//sc.say("mybot reached its destination");
		sc.playWave(path_to_voices+"robotreacheditsdestination.wav");
		sleep(6);
		return true;
	}
	else{
		ROS_INFO("mybot failed to reach its destination for some reasons");
		sc.playWave(path_to_sounds+"short_buzzer2.wav");
		sleep(1);
		//sc.say("mybot could not reach its destination. Navigation aborted");
		sc.playWave(path_to_voices+"robotcannotreachitsdestination.wav");
		sleep(5);
		return false;

	}

}

std::string MybotDeliveryOperator::process(BaseMessage* m)
{
	std::string str = "";
	return str;
}
void MybotDeliveryOperator::processCoffeeRequest(const mybot_delivery_app::DeliveryRequestMsg::ConstPtr& msg){

	static double x0;
	static double y0;
	char c;

	x0 = myRobot.getAmclX();
	y0 = myRobot.getAmclY();

	myRobot.Led2Message.value = kobuki_msgs::Led::RED;
	myRobot.Led2Publisher.publish(myRobot.Led2Message);//turn led2 red when starting the mission

	ROS_INFO("Mybot Delivery Operator received Request message.");
	sc.playWave(path_to_voices+"happytoserveyou.wav");
	sleep(4);
	std_msgs::String position_message;
	position_message.data = "HIDE";
	publishMessage("arm_position", position_message);

	/**** MOVE TO SOURCE **/
	ROS_INFO("Moving to the customer location (%.2f, %.2f)", msg->source_x, msg->source_y);
	//sc.say("Moving to the customer location");
	sc.playWave(path_to_voices+"movingtothecustomerlocation.wav");
	sleep(6);
	//cin>>c;
	bool navigationToCustomerSucceeded = moveTo(msg->source_x, msg->source_y);
	sleep(5);
	int x=2;
	if (navigationToCustomerSucceeded){
		/**** ARM IN TAKE POSITION WHEN REACHING **/
		ROS_INFO("Put the money in the gripper and your request on top of the robot on a paper and press a key");
		position_message.data = "TAKE";
		publishMessage("arm_position", position_message);
		sc.say("Put the money in the gripper and your request on top of the robot on a paper");
		sc.playWave(path_to_voices+"putthemoneyinthegripperandpressakey.wav");
		sleep(6);

		cin>>c;

		/**** CLOSE GRIPPER AFTER PRESSING A KEY **/
		ROS_INFO("Closing gripper");
		position_message.data = "GRIP";
		publishMessage("arm_position", position_message);
		//sc.say("Closing gripper ...");
		sc.playWave(path_to_voices+"closingthegripper.wav");
		sleep(5);

		/**** HIDE ITEM BEFORE GOIND TO DESTINATION **/
		ROS_INFO("Hiding the gripper");
		position_message.data = "HIDE";
		publishMessage("arm_position", position_message);
		//sc.say("Hiding the item ...");
		sc.playWave(path_to_voices+"hidingthegripper.wav");
		sleep(5);

		/**** MOVING TO DESTINATION **/
		ROS_INFO("Moving to the cafe location (%.2f, %.2f)", msg->destination_x, msg->destination_y);
		//sc.say("Moving to destination location");
		sc.playWave(path_to_voices+"movingtothecafe.wav");
		sleep(5);
		bool navigationToRecipientSucceeded = moveTo(msg->destination_x, msg->destination_y);


		if (navigationToRecipientSucceeded){
			/**** ARM IN RETURN POSITION WHEN REACHING **/
			ROS_INFO("Taking arm in return position");
			position_message.data = "RETURN";
			publishMessage("arm_position", position_message);
			/** NOTE ****************************/
			//sc.say("Taking arm in return position");
			sc.playWave(path_to_voices+"movingthearmtodeliveryposition.wav");
			sleep(10);



			/**** CLOSE GRIPPER AFTER PRESSING A KEY **/

			ROS_INFO("Press a key to take the money and take the request paper from top");
			//sc.say("Press a key to take the money and take the request paper from top");
			sc.playWave(path_to_voices+"pressakeytotakethemoneyandputtheorderontherobot.wav");
			sleep(5);
			cin>>c;
			/*
			 * USING A BUTTON B0
					bool button_pressed=false;
					do{
						button_pressed = (myRobot.ButtonMessage.button==myRobot.ButtonMessage.Button0) && (myRobot.ButtonMessage.state==myRobot.ButtonMessage.PRESSED);
						sleep(0.5);
					}while(!button_pressed);
			 */
			ROS_INFO("Releasing item");
			position_message.data = "RELEASE";
			publishMessage("arm_position", position_message);
			/** NOTE ****************************/
			sc.say("Take the money and put the coffee and cake on the robot top plate. Press a key when this is done");
			//sc.playWave(path_to_voices+"takeyouritemthankyou.wav");
			sleep(11);

			/**** HIDE ITEM BEFORE GOIND TO DESTINATION **/
			ROS_INFO("Hiding the item");
			position_message.data = "HIDE";
			publishMessage("arm_position", position_message);
			//sc.say("Hiding the item ...");
			sc.playWave(path_to_voices+"hidingthegripper.wav");
			sleep(5);


			cin>>c;
			/*
			 * USING A BUTTON B0
				bool button_pressed=false;
				do{
					button_pressed = (myRobot.ButtonMessage.button==myRobot.ButtonMessage.Button0) && (myRobot.ButtonMessage.state==myRobot.ButtonMessage.PRESSED);
					sleep(0.5);
				}while(!button_pressed);
			 */


			/**** Go back to customer for delivery ***/
			ROS_INFO("Going back to customer location (%.2f, %.2f)", msg->source_x, msg->source_y);
			//sc.say("Moving to customer");
			sc.playWave(path_to_voices+"goingbacktocustomerlocation.wav");
			sleep(5);
			moveTo(msg->source_x, msg->source_y);
			sleep(5);
			//sc.say("Delivery mission completed");
			ROS_INFO("Take your coffee and cake and press a button");
			sc.say("Take your coffee and cake and press a button");
			//sc.playWave(path_to_voices+"missioncompleted.wav");
			sleep(6);
			cin>>c;
			/*
			 * USING A BUTTON B0
				bool button_pressed=false;
				do{
					button_pressed = (myRobot.ButtonMessage.button==myRobot.ButtonMessage.Button0) && (myRobot.ButtonMessage.state==myRobot.ButtonMessage.PRESSED);
					sleep(0.5);
				}while(!button_pressed);
			 */

			/**** Going back to depot location ***/
			ROS_INFO("Going back to depot location (%.2f, %.2f)", msg->depot_x, msg->depot_y);
			//sc.say("Moving to depot location");
			sc.playWave(path_to_voices+"goingbacktodepot.wav");
			sleep(5);
			moveTo(msg->depot_x, msg->depot_y);
			sleep(5);
			//sc.say("Delivery mission completed");
			ROS_INFO("Mission completed");
			sc.playWave(path_to_voices+"missioncompletedsuccess.wav");
			sleep(6);
		}//navigationToRecipientSucceeded
		else{

			/**** HIDE ITEM BEFORE GOIND TO DESTINATION **/
			ROS_INFO("Hiding the item");
			position_message.data = "HIDE";
			publishMessage("arm_position", position_message);
			//sc.say("Hiding the item ...");
			sc.playWave(path_to_voices+"hidingthegripper.wav");
			sleep(5);
			sc.playWave(path_to_voices+"missionfailed.wav");
		}
	}//end navigationToSenderSucceeded
	else{
		/**** HIDE ITEM BEFORE GOIND TO DESTINATION **/
		ROS_INFO("Hiding the item");
		position_message.data = "HIDE";
		publishMessage("arm_position", position_message);
		//sc.say("Hiding the item ...");
		sc.playWave(path_to_voices+"hidingthegripper.wav");
		sleep(5);
		sc.playWave(path_to_voices+"missionfailed.wav");

	}

	myRobot.Led2Message.value = kobuki_msgs::Led::BLACK;
	myRobot.Led2Publisher.publish(myRobot.Led2Message);//turn led2 black when completing the mission

}



void MybotDeliveryOperator::processDeliveryRequest(const mybot_delivery_app::DeliveryRequestMsg::ConstPtr& msg){

	static double x0;
	static double y0;

	x0 = myRobot.getAmclX();
	y0 = myRobot.getAmclY();

	myRobot.Led2Message.value = kobuki_msgs::Led::RED;
	myRobot.Led2Publisher.publish(myRobot.Led2Message);//turn led2 red when starting the mission

	ROS_INFO("Mybot Delivery Operator received Request message.");
	sc.playWave(path_to_voices+"happytoserveyou.wav");
	sleep(4);
	std_msgs::String position_message;
	position_message.data = "HIDE";
	publishMessage("arm_position", position_message);

	/**** MOVE TO SOURCE **/
	ROS_INFO("Moving to source location (%.2f, %.2f)", msg->source_x, msg->source_y);
	//sc.say("Moving to source location");
	sc.playWave(path_to_voices+"goingtosenderlocation.wav");
	sleep(6);
	bool navigationToSenderSucceeded = moveTo(msg->source_x, msg->source_y);
	sleep(5);

	if (navigationToSenderSucceeded){
		/**** ARM IN TAKE POSITION WHEN REACHING **/
		ROS_INFO("Put the item to deliver in the gripper and press a key");
		position_message.data = "TAKE";
		publishMessage("arm_position", position_message);
		//sc.say("Put the item to delivery in the gripper and press a key");
		sc.playWave(path_to_voices+"puttheiteminthegripperandpressakey.wav");
		sleep(5);
		char c;
		cin>>c;

		/**** CLOSE GRIPPER AFTER PRESSING A KEY **/
		ROS_INFO("Closing gripper");
		position_message.data = "GRIP";
		publishMessage("arm_position", position_message);
		//sc.say("Closing gripper ...");
		sc.playWave(path_to_voices+"closingthegripper.wav");
		sleep(5);

		/**** HIDE ITEM BEFORE GOIND TO DESTINATION **/
		ROS_INFO("Hiding the item");
		position_message.data = "HIDE";
		publishMessage("arm_position", position_message);
		//sc.say("Hiding the item ...");
		sc.playWave(path_to_voices+"hidingthegripper.wav");
		sleep(5);

		/**** MOVING TO DESTINATION **/
		ROS_INFO("Moving to destination location (%.2f, %.2f)", msg->destination_x, msg->destination_y);
		//sc.say("Moving to destination location");
		sc.playWave(path_to_voices+"goingtorecipient.wav");
		sleep(5);
		bool navigationToRecipientSucceeded = moveTo(msg->destination_x, msg->destination_y);


		if (navigationToRecipientSucceeded){
			/**** ARM IN RETURN POSITION WHEN REACHING **/
			ROS_INFO("Taking arm in return position");
			position_message.data = "RETURN";
			publishMessage("arm_position", position_message);
			/** NOTE ****************************/
			//sc.say("Taking arm in return position");
			sc.playWave(path_to_voices+"movingthearmtodeliveryposition.wav");
			sleep(10);



			/**** CLOSE GRIPPER AFTER PRESSING A KEY **/

			ROS_INFO("Press a key to release the item");
			//sc.say("Press a key to release the item");
			sc.playWave(path_to_voices+"pressakeytoopenthegripperandtaketheitem.wav");
			sleep(5);
			cin>>c;
			/*
			 * USING A BUTTON B0
				bool button_pressed=false;
				do{
					button_pressed = (myRobot.ButtonMessage.button==myRobot.ButtonMessage.Button0) && (myRobot.ButtonMessage.state==myRobot.ButtonMessage.PRESSED);
					sleep(0.5);
				}while(!button_pressed);
			 */
			ROS_INFO("Releasing item");
			position_message.data = "RELEASE";
			publishMessage("arm_position", position_message);
			/** NOTE ****************************/
			//sc.say("Take your item and thank you !, Anything more, just call me from your mobile phone");
			sc.playWave(path_to_voices+"takeyouritemthankyou.wav");
			sleep(11);

			/**** HIDE ITEM BEFORE GOIND TO DESTINATION **/
			ROS_INFO("Hiding the item");
			position_message.data = "HIDE";
			publishMessage("arm_position", position_message);
			//sc.say("Hiding the item ...");
			sc.playWave(path_to_voices+"hidingthegripper.wav");
			sleep(5);

			ROS_INFO("Going back to depot location (%.2f, %.2f)", msg->depot_x, msg->depot_y);
			//sc.say("Moving to depot location");
			sc.playWave(path_to_voices+"goingbacktodepot.wav");
			sleep(5);
			moveTo(msg->depot_x, msg->depot_y);
			sleep(5);
			//sc.say("Delivery mission completed");
			ROS_INFO("Mission completed");
			sc.playWave(path_to_voices+"missioncompletedsuccess.wav");
			sleep(6);
		}//navigationToRecipientSucceeded
		else{

			/**** HIDE ITEM BEFORE GOIND TO DESTINATION **/
			ROS_INFO("Hiding the item");
			position_message.data = "HIDE";
			publishMessage("arm_position", position_message);
			//sc.say("Hiding the item ...");
			sc.playWave(path_to_voices+"hidingthegripper.wav");
			sleep(5);
			sc.playWave(path_to_voices+"missionfailed.wav");
			sleep(5);

			/**** GO TO DOCKING STATION
			 * See http://docs.ros.org/indigo/api/kobuki_auto_docking/html/DockDriveActionClient_8py_source.html
			 * **/
/*			ROS_INFO("Going to docking station");
			sc.say("Going to docking station");
			//actionlib::SimpleActionClient<kobuki_msgs::AutoDockingAction> ac("AutoDockingAction", true);
			actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
			ac.waitForServer();
			//kobuki_msgs::AutoDockingActionGoal goal;

			move_base_msgs::MoveBaseGoal goal;

			  //we'll send a goal to the robot to move 1 meter forward
			  goal.target_pose.header.frame_id = "base_link";
			  goal.target_pose.header.stamp = ros::Time::now();

			  goal.target_pose.pose.position.x = 1.0;
			  goal.target_pose.pose.orientation.w = 1.0;

			  ROS_INFO("Sending goal");
			  ac.sendGoal(goal);

			ac.sendGoal(goal);


			//wait for the action to return
			bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

			if (finished_before_timeout)
			{
				actionlib::SimpleClientGoalState state = ac.getState();
				ROS_INFO("Action finished: %s",state.toString().c_str());
			}
			else
				ROS_INFO("Action did not finish before the time out.");

*/
		}
	}//end navigationToSenderSucceeded
	else{
		/**** HIDE ITEM BEFORE GOIND TO DESTINATION **/
		ROS_INFO("Hiding the item");
		position_message.data = "HIDE";
		publishMessage("arm_position", position_message);
		//sc.say("Hiding the item ...");
		sc.playWave(path_to_voices+"hidingthegripper.wav");
		sleep(5);
		sc.playWave(path_to_voices+"missionfailed.wav");

	}

	myRobot.Led2Message.value = kobuki_msgs::Led::BLACK;
	myRobot.Led2Publisher.publish(myRobot.Led2Message);//turn led2 black when completing the mission




}


