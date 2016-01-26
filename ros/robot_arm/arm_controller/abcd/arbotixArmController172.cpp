#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include "ros/console.h"
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "boost/thread/mutex.hpp"
#include "boost/thread/thread.hpp"
#include <vector>
#include <string>
#include "trajectory_msgs/JointTrajectory.h"
#include <sensor_msgs/JointState.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <iostream>
#include <tf/transform_listener.h>
#include "geometry_msgs/Pose.h"
#include "control_msgs/FollowJointTrajectoryActionGoal.h" // for the goal message
#include "trajectory_msgs/JointTrajectory.h" // for the command message
#include "actionlib_msgs/GoalID.h" // for cancelling the goal message
#include "actionlib_msgs/GoalStatusArray.h" //for goal status message
#include "diagnostic_msgs/DiagnosticArray.h" //for diagonostic messages
#include "control_msgs/FollowJointTrajectoryActionFeedback.h" //for feedback messages


#include <fstream>

#include "sensor_msgs/JointState.h"

// defining the namespace
using namespace std;

// keycodes for moving arm
#define KEYCODE_R 0x43 
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71

//Global Publisher and Subscriber
ros::Publisher gripper_pub;
ros::Publisher elbow_pub;
ros::Publisher joint_pub;
ros::Publisher shoulderPan_pub;
ros::Publisher wrist_pub;
//subscriber for Arbotix arm
ros::Subscriber jointStatesSubsriber ; // subscribing for joint states
	//	ros::Subscriber armCommandsSubscriber 

ros::Subscriber commandReceiver; //commands subscriber
//Global Variables
sensor_msgs::JointState joint_states_sub; //for storing the joint states from subscriber
std_msgs::Float64 armVelocityPublisher;
 ros::Duration d(2);
/*----------------------------------------------- MENU FUNCTION ------------------------

About : This Function is Just Used to Provide Menu For the Program

*/
void menu(){

  std::cout<<"-------- Please Enter ONE of The Number To MOVE the ARM Parts -----------\n";
  std::cout<<" 1 : To Move The Gripper\n";
  std::cout<<" 2 : To Move The Elbow\n";
  std::cout<<" 3 : To Move The Shoulder Joint\n";
  std::cout<<" 4 : To Move The Shoulder PAN\n";
  std::cout<<" 5 : To Move The Wrist\n";
  std::cout<<" 6 : Take the Item & Print Joint States\n";
  std::cout<<" 7 : Hold the Item &  Print Joint States\n";
  std::cout<<" 9 : To Quit the ARBOTIX ARM Controller\n";
  std::cout<<"-------- -------------------------------------------------   -----------\n";

  
}

// -------------------------    Joint state vectors for planning and moving the arm ----------------
vector <string> armJointStateNames; //arm joint names, published by state_publisher from urdf model
vector <double> currentArmJointValues; //arm joint value
vector <string> gripperJointStateNames; //gripper joint names, published by state_publisher from urdf model
double currentGripperJointValue; //gripper joint value
vector <string> armCommandNames; //arm command names, published by the user
string gripperCommandName; //gripper command name, published by the user



/*----------------------------------------------- Joint State Call FUNCTION ------------------------

About : This Function takes the values of Joint States and store it in Global Varaible "sensor_msgs::JointState joint_states_sub"

*/
void jointStatesCallBack(const sensor_msgs::JointState & joint_states_handler)
{
  joint_states_sub=joint_states_handler;
}

/*----------------------------------------------- Print Joint State FUNCTION ------------------------

About : This Function takes the values stored in Global Variable "sensor_msgs::JointState joint_states_sub"
and then Print the Joint States

*/
void printJointStates(){
cout<< "------------------   Arbotix Joint States  ---------------------------"<<endl;
  cout<< "Header SEQUENCE: "<< joint_states_sub.header.seq<<endl;
  cout<< "Arm elbow flex joint State: " <<joint_states_sub.position[0]<<endl;
  cout<< "Arm wrist flex joint State: " <<joint_states_sub.position[1]<<endl;
  cout<< "Gripper joint State: " <<joint_states_sub.position[2]<<endl;
  cout<< "Arm shoulder Pan joint State: " <<joint_states_sub.position[3]<<endl;
  cout<< "Arm shoulder Lift joint State: " <<joint_states_sub.position[4]<<endl;
  cout<< "------------------              ---------------------------"<<endl;
}


/*----------------------------------------------- Check Input Ranges FUNCTION ------------------------

About : This Function takes the values input by user, verifies the input is with in range and then returns the values

*/

double checkInputRanges(int selector,double inpData){
if(selector ==1){
//practical ranges may vary due to problems
	if(inpData < -1.51){
	cout << "Less than input Range"<<endl;
	inpData = -1.51;}
	else if(inpData >1.51){
	//cout<<"Greater than range"<<endl;
	inpData = 1.51;
	}
}else if(selector == 2){
	if(inpData < -1.51){
	//cout << "Less than Range"<<endl;
	inpData = -1.51;}
	else if(inpData >1.51){
	//cout<<"Greater than range"<<endl;
	inpData = 1.51;
	}
} else if(selector == 3){
	if(inpData < -1.51){
	//cout << "Less than Range"<<endl;
	inpData = -1.51;}
	else if(inpData >1.51){
	//cout<<"Greater than range"<<endl;
	inpData = 1.51;
	}
} else if(selector == 4){
	if(inpData < -1.04){
	//cout << "Less than Range"<<endl;
	inpData = -1.04;}
	else if(inpData >3.14){
	//cout<<"Greater than range"<<endl;
	inpData = 2.01;
	}
} else if(selector == 5){
	if(inpData < -1.51){
	//cout << "Less than Range"<<endl;
	inpData = -1.51;}
	else if(inpData >1.51){
	//cout<<"Greater than range"<<endl;
	inpData = 1.51;
	}
} 
cout << "Data Value :" <<inpData <<" --- "<<endl;
return inpData;
}

/*----------------------------------------------- Relax FUNCTION ------------------------

About : This Function will make the Arbotix Arm Straight

*/
void straightArm(){
//for Gripper to Open State
	cout<< "Setting the Gripper to Open Position" << endl;
	armVelocityPublisher.data = 1.0;
	gripper_pub.publish(armVelocityPublisher);
	d.sleep();
//for Wrist to Straight State
        cout<< "Setting the Wrist to Open Position" << endl;
	armVelocityPublisher.data = 0.0;
	wrist_pub.publish(armVelocityPublisher);
	d.sleep();
//for Elbow to Straight State
        cout<< "Setting the Elbow to Open Position" << endl;
	armVelocityPublisher.data = 0.0;
	elbow_pub.publish(armVelocityPublisher);
	d.sleep();
//for Shoulder to Straight State
        cout<< "Setting the Shoulder Lift to Open Position" << endl;
	armVelocityPublisher.data = 0.0;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
//for Pan to Straight State
        cout<< "Setting the Shoulder PAN to Open Position" << endl;
	armVelocityPublisher.data = 0.0;
	shoulderPan_pub.publish(armVelocityPublisher);
	//ros:sleep(3);
}

/*----------------------------------------------- Shake Hand FUNCTION ------------------------

About : This Function will allow the arm to shake hand
*/
void shakeHand(){
//for Gripper to Open State
	armVelocityPublisher.data = 0.5;
	gripper_pub.publish(armVelocityPublisher);
//for Wrist to Straight State
	armVelocityPublisher.data = 0.0;
	wrist_pub.publish(armVelocityPublisher);
//for Elbow to Straight State
	armVelocityPublisher.data = 0.0;
	elbow_pub.publish(armVelocityPublisher);
//for Shoulder to Straight State
	armVelocityPublisher.data = 0.0;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
//for Pan to Straight State
	armVelocityPublisher.data = 0.0;
	shoulderPan_pub.publish(armVelocityPublisher);
	//ros:sleep(3);

for(int i=0; i<=4; i++){
//for Elbow to shake State
	armVelocityPublisher.data = 1.4;
	elbow_pub.publish(armVelocityPublisher);
	d.sleep();
//for Elbow to shaking State
	armVelocityPublisher.data = 1.0;
	elbow_pub.publish(armVelocityPublisher);
	d.sleep();

}//for bracket
	
}
/*----------------------------------------------- Hold the Item FUNCTION ------------------------

About : This Function will allow the arm to Hold the Item
*/
void TakeItem(){
//for Gripper to Open State
	armVelocityPublisher.data = -1.0;
	gripper_pub.publish(armVelocityPublisher);
	d.sleep();
//for Wrist to Straight State
	armVelocityPublisher.data = -0.2;
	wrist_pub.publish(armVelocityPublisher);
	d.sleep();
//for Elbow to Straight State
	armVelocityPublisher.data = 0.7;
	elbow_pub.publish(armVelocityPublisher);
	d.sleep();
//for Shoulder to Straight State
	armVelocityPublisher.data = 0.0;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
//for Pan to Straight State
	armVelocityPublisher.data = 0.0;
	shoulderPan_pub.publish(armVelocityPublisher);
	//ros:sleep(3);


	
}

/*----------------------------------------------- Hold the Item FUNCTION ------------------------

About : This Function will allow the arm to Hold the Item
*/
void HoldItem(){
//for Gripper to Open State
	armVelocityPublisher.data = 1.5;
	gripper_pub.publish(armVelocityPublisher);
	d.sleep();
//for Wrist to Straight State
	armVelocityPublisher.data = -0.2;
	wrist_pub.publish(armVelocityPublisher);
	d.sleep();
//for Elbow to Straight State
	armVelocityPublisher.data = 0.7;
	elbow_pub.publish(armVelocityPublisher);
	d.sleep();
//for Shoulder to Straight State
	armVelocityPublisher.data = 1.0;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
//for Pan to Straight State
	armVelocityPublisher.data = 0.0;
	shoulderPan_pub.publish(armVelocityPublisher);
	//ros:sleep(3);


	
}
/*----------------------------------------------- Pick FUNCTION ------------------------

About : This Function will make the Arbotix Arm Straight
For this we work with negative values that means the power and blue cable are on back side of bottle
LED is Facing the Bottle
Bottle is Aqua Fina
It will pick the bottle for someone

*/
void PickLoad(){
//for Shoulder to Near State
        cout<< "Setting the Shoulder Joint to Near PICK Position" << endl;
	armVelocityPublisher.data = -1.0;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
//for Shoulder to Nearer State
        cout<< "Setting the Shoulder Joint to Near PICK Position" << endl;
	armVelocityPublisher.data = -1.1;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
//for Shoulder to Nearest State
        cout<< "Setting the Shoulder Joint to Near PICK Position" << endl;
	armVelocityPublisher.data = -1.2;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
//for Shoulder to Final State
        cout<< "Setting the Shoulder Joint to Near PICK Position" << endl;
	armVelocityPublisher.data = -1.3;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
//for Gripper to Open State
	cout<< "Setting the Gripper to Open Position" << endl;
	armVelocityPublisher.data = 1.5;
	gripper_pub.publish(armVelocityPublisher);
	d.sleep();
//for Wrist to Straight State
        cout<< "Setting the Wrist to Open Position" << endl;
	armVelocityPublisher.data = -0.2;
	wrist_pub.publish(armVelocityPublisher);
	d.sleep();
//for Gripper to Close State
	cout<< "Setting the Gripper to Open Position" << endl;
	armVelocityPublisher.data = 0.9;
	gripper_pub.publish(armVelocityPublisher);
	d.sleep();
//for Shoulder to Straight State
        cout<< "Setting the Shoulder Lift to Open Position" << endl;
	armVelocityPublisher.data = 0.0;
	joint_pub.publish(armVelocityPublisher);
	d.sleep();
}

/*----------------------------------------------- Joint State Call FUNCTION ------------------------

About : This Function takes the values of Joint States and store it in Global Varaible "sensor_msgs::JointState joint_states_sub"

*/
void armCallBack(const std_msgs::String::ConstPtr& msg)
{
 cout <<" Hello :Welcome to Shake hand "<< msg->data.c_str();
 if(msg->data.c_str() == "Shake"){
shakeHand(); 
}
else if(msg->data.c_str() == "Straight"){
  straightArm();
}
else if(msg->data.c_str() == "Pick"){
  PickLoad();
}

}

//---------------------------------      MAIN Function ------------------------------
int main(int argc, char **argv)
{
std::cout<< "------------------   Arbotix Arm Controller  ---------------------------\n\n";
ros::init(argc, argv, "armcontroller");
ros::NodeHandle n;

// Publishers for Arbotix Arm

		gripper_pub = n.advertise<std_msgs::Float64>("/gripper_joint/command", 1000);
		elbow_pub = n.advertise<std_msgs::Float64>("/arm_elbow_flex_joint/command", 1000);
		joint_pub = n.advertise<std_msgs::Float64>("/arm_shoulder_lift_joint/command", 1000);
		shoulderPan_pub = n.advertise<std_msgs::Float64>("/arm_shoulder_pan_joint/command", 1000);
		wrist_pub = n.advertise<std_msgs::Float64>("/arm_wrist_flex_joint/command", 1000);
//subscriber for Arbotix arm
		ros::Subscriber jointStatesSubsriber = n.subscribe("/joint_states", 1000, jointStatesCallBack); // subscribing for joint states
	//	ros::Subscriber armCommandsSubscriber = n.subscribe("arm_controller/command", 1, onArmCommand); // subscribing for joint states
		ros::Subscriber commandReceiver = n.subscribe("/ArmCommand_Subscriber", 1000, armCallBack); // CallBack for arm controller

// for ros 
ros::Rate loop_rate(10);
//for handling the call back segmentation fault as it was not getting the real time data and causing the/
/*
enter 6
------------------   Arbotix Joint States  ---------------------------
Header SEQUENCE: 0
Segmentation fault (core dumped)

*/
ros::AsyncSpinner armControlSpinner(4);
armControlSpinner.start();
ros::Rate threadRate(12);
//ros::spin();
//Inputs
     float userInput;
     int selectionValue;
     std_msgs::Float64 inputData; //trying to make common input


  while (ros::ok())
  {
  menu();
  std::cin>>selectionValue;

	if(selectionValue == 1){
                        
			cout<< " Value Ranges from -2.61 to +2.61 Please follow ranges\n";
			std_msgs::Float64 gripperData;
			std::cout<< "Enter the Gripper Value to Move the Gripper\n";
			std::cin>>userInput;
                        gripperData.data =checkInputRanges(selectionValue,userInput);
			cout << " The GripperData " << gripperData ;
			//gripperData.data =userInput;
			gripper_pub.publish(gripperData);
	}else if(selectionValue == 2){
			cout<< " Value Ranges from -2.61 to +2.61 Please follow ranges\n";
			std_msgs::Float64 elbowData;
			std::cout<< "Enter the Float64 Value to Move the Elbow\n";
			std::cin>>userInput;
			elbowData.data =checkInputRanges(selectionValue,userInput);//assisning value taken as input
			elbow_pub.publish(elbowData);
	}else if(selectionValue == 3){
			cout<< " Value Ranges from -2.61 to +2.61 Please follow ranges\n";
			std_msgs::Float64 shoulderjointData;
			std::cout<< "Enter the FLoat Value to Move the shoulder Joint\n";
			std::cin>>userInput;
			shoulderjointData.data =checkInputRanges(selectionValue,userInput);
			joint_pub.publish(shoulderjointData);
	}else if(selectionValue == 4){
			cout<< " Value Ranges from -1.04 to +3.14 Please follow ranges\n";
			std_msgs::Float64 shoulderPanData;
			std::cout<< "Enter the Float Value to Move the Pan\n";
			std::cin>>userInput;
			shoulderPanData.data =userInput;
			shoulderPan_pub.publish(shoulderPanData);
	}else if(selectionValue == 5){
		       cout<< " Value Ranges from -1.74 to +1.74 Please follow ranges\n";
			std_msgs::Float64 wristData;
			std::cout<< "Enter the FLoat Value to Move the Wrist\n";
			std::cin>>userInput;
			wristData.data =userInput;
			wrist_pub.publish(wristData);
	}else if(selectionValue == 6){
			printJointStates(); 
			HoldItem(); 
			printJointStates(); 
	}else if(selectionValue == 7){
			//straightArm();
			//printJointStates();
			//PickLoad();
			//shakeHand();
			TakeItem();
			printJointStates(); 
	}else if(selectionValue == 9){
			std::cout<< "Thanks For Using ARBOTIX ARM CONTROLLER\n";
			exit(0);  
	}else{    
			std::cout<< "Please Enter the Values Between 1-5 or 9 to QUIT\n";
	}
 

loop_rate.sleep();
   
} // While Loop Bracket
ros::spin();
return 0;
}// Main Function Bracket
