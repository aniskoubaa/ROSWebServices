#include "robot_control/TurtlebotRobot.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;


TurtlebotRobot::TurtlebotRobot (ros::NodeHandle & nh,POSE Xr, POSE Yr, POSE Angle, string IPaddress, string rName, unsigned short ROSPortNbr, unsigned short ServerPortNbr)
:Robot (nh, Xr, Yr, Angle, IPaddress, rName, ROSPortNbr, ServerPortNbr)
{
  setType("Turtlebot::v02");
  SetPublishers ();
  SetSubscribers ();
  SetNavigationStackSubscribers();
  SetNavigationStackPublishers();
  
}

TurtlebotRobot::TurtlebotRobot(const ros::NodeHandle &nh, string rName)
:Robot (nh, rName)
{
  setType("Turtlebot::v02");
  SetPublishers ();
  SetSubscribers ();
  SetNavigationStackSubscribers();
  SetNavigationStackPublishers();
  
  
}

/** this function sets all publishers for the robot **/
void TurtlebotRobot::SetPublishers (){
  VelocityPublisher=ROSNodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
  Led1Publisher = ROSNodeHandle.advertise< kobuki_msgs::Led >("/mobile_base/commands/led1", 10);
  Led2Publisher = ROSNodeHandle.advertise< kobuki_msgs::Led >("/mobile_base/commands/led2", 10);
}

/** this function sets all subscribers for the robot **/
void TurtlebotRobot::SetSubscribers (){
  OdometerySubscriber    = ROSNodeHandle.subscribe<nav_msgs::Odometry>("/odom", 1,  &TurtlebotRobot::OdometryCallback, this);
  OdomCombinedSubscriber = ROSNodeHandle.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/robot_pose_ekf/odom_combined", 1,  &TurtlebotRobot::OdometryCombinedCallback, this);
  CliffSubscriber = ROSNodeHandle.subscribe<kobuki_msgs::CliffEvent>("/mobile_base/events/cliff", 1,  &TurtlebotRobot::CliffCallback, this);
  BumperSubscriber = ROSNodeHandle.subscribe<kobuki_msgs::BumperEvent>("/mobile_base/events/bumper", 1,  &TurtlebotRobot::BumperCallback, this);
  LaserScanSubscriber = ROSNodeHandle.subscribe<sensor_msgs::LaserScan>("/scan", 1,  &TurtlebotRobot::LaserScanCallback, this);
  WheelDropSubscriber = ROSNodeHandle.subscribe<kobuki_msgs::WheelDropEvent>("/mobile_base/events/wheel_drop", 1,  &TurtlebotRobot::WheelDropCallback, this);
  PowerSystemSubscriber = ROSNodeHandle.subscribe<kobuki_msgs::PowerSystemEvent>("/mobile_base/events/power_system", 1,  &TurtlebotRobot::PowerSystemCallback, this);
  ButtonSubscriber = ROSNodeHandle.subscribe<kobuki_msgs::ButtonEvent>("/mobile_base/events/button", 1,  &TurtlebotRobot::ButtonCallback, this);
}


void TurtlebotRobot::SetNavigationStackSubscribers (){
  //cout<<"[TurtlebotRobot::SetNavigationStackSubscribers ()]"<<endl;
  MoveBaseActionGoalSubscriber = ROSNodeHandle.subscribe<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 1,  &TurtlebotRobot::MoveBaseActionGoalCallback, this);
  PoseStampedGoalSubscriber = ROSNodeHandle.subscribe<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1,  &TurtlebotRobot::PoseStampedGoalCallback, this);
  InitialPoseSubscriber = ROSNodeHandle.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 1,  &TurtlebotRobot::InitialPoseCallback, this);
  MapSubscriber = ROSNodeHandle.subscribe<nav_msgs::OccupancyGrid>("/map", 1,  &TurtlebotRobot::MapCallback, this);
  AmclPoseSubscriber = ROSNodeHandle.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/amcl_pose", 1,  &TurtlebotRobot::AmclPoseCallback, this);
  
}

void TurtlebotRobot::SetNavigationStackPublishers (){
  //cout<<"[TurtlebotRobot::SetNavigationStackPublishers ()]"<<endl;
  GlobalPlanPublisher = ROSNodeHandle.advertise< nav_msgs::Path >("/move_base/TrajectoryPlannerROS/global_plan", 10);
  //for sending initial pose
  InitialPosePublisher = ROSNodeHandle.advertise< geometry_msgs::PoseWithCovarianceStamped >("/initialpose", 10);
  //for sending 2D Nav Goal (like in rviz)
  PoseStampedGoalPublisher = ROSNodeHandle.advertise< geometry_msgs::PoseStamped >("/move_base_simple/goal", 10);
  //PoseStampedGoalPublisher = ROSNodeHandle.advertise< geometry_msgs::PoseWithCovarianceStamped >("/move_base_simple/goal", 10);
  
}

void TurtlebotRobot::MoveBaseActionGoalCallback(const move_base_msgs::MoveBaseActionGoal::ConstPtr& msg){
  cout<<"[Move Base Goal Callback]"<<endl;
  MoveBaseActionGoalMessage = *msg;
  Pose2D goalPose (MoveBaseActionGoalMessage.goal.target_pose.pose.position.x, MoveBaseActionGoalMessage.goal.target_pose.pose.position.y, tf::getYaw(MoveBaseActionGoalMessage.goal.target_pose.pose.orientation));
  cout<<"   --> Move Base Goal Received Pose: "<<goalPose<<endl<<endl;
}


/** /move_base_simple/goal **/
void TurtlebotRobot::PoseStampedGoalCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
  cout<<"[Pose Stamped Goal Callback]"<<endl;
  PoseStampedGoalMessage = *msg;
  Pose2D goalPose (PoseStampedGoalMessage.pose.position.x, PoseStampedGoalMessage.pose.position.y, tf::getYaw(PoseStampedGoalMessage.pose.orientation));
  cout<<"   --> Pose Stamped Goal Received Pose: "<<goalPose<<endl<<endl;
}


void TurtlebotRobot::InitialPoseCallback (const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
  InitialPoseMessage = *msg;
  cout<<"[TurtlebotRobot::InitialPoseCallback]"<<endl;
  Pose2D initPose (InitialPoseMessage.pose.pose.position.x, InitialPoseMessage.pose.pose.position.y, tf::getYaw(InitialPoseMessage.pose.pose.orientation));
  cout<<"   --> Initial Pose Received: "<<initPose<<endl<<endl;
  
}
void TurtlebotRobot::MapCallback (const nav_msgs::OccupancyGrid::ConstPtr& msg){
  
  cout <<"\n[TurtlebotRobot::MapCallback] copying map into OGM under progress. waiting ..."<<endl;
  MapMessage = *msg;
  setprecision(6);
  //cout<<"    Resolution: " << msg->info.resolution <<endl;
  OGM = new OccupancyGridMap (MapMessage.info.width, MapMessage.info.height, MapMessage.info.resolution);
  //cout<<"Map Info" <<endl;
  //cout<<"    Width     : " << MapMessage.info.width <<endl;
  //cout<<"    Height    : " << MapMessage.info.height <<endl;
  //cout<<"    Resolution: " << setw(6)<< setprecision(6)<< MapMessage.info.resolution <<endl;
  //cout<<"    Origin X  : " << MapMessage.info.origin.position.x <<endl;
  //cout<<"    Origin Y  : " << MapMessage.info.origin.position.y <<endl;
  //cout<<"    Origin Yaw: " << tf::getYaw(MapMessage.info.origin.orientation)<<endl;
  
  /** copying the map from MapMessage to OGM map object **/
  for (int i=0;i<MapMessage.info.height;i++)
    for (int j=0;j<MapMessage.info.width;j++){
      //cout<<"map["<<i<<"]: " << static_cast <int>(MapMessage.data[i]) <<"index: "<<static_cast <int> (OGM->getCellIndex(i,j)])<<"    Width     : " << MapMessage.info.width <<"    Height    : " << MapMessage.info.height <<endl;
      OGM->getMapLayout()[i][j]=static_cast <int>(MapMessage.data[OGM->getCellIndex(i,j)]); 
    }
    
    //uncomment if you want to export the map. it was tested with success.
    //OGM->exportMapLayout("turtlebot_map.pgm", OGM->getMapLayout());
  cout <<"[TurtlebotRobot::MapCallback]  copying map into OGM completed\n"<<endl;
  /*
   *  cout<<"Map Info" <<endl;
   *  cout<<"    Width     : " << MapMessage.info.width <<endl;
   *  cout<<"    Height    : " << MapMessage.info.height <<endl;
   *  cout<<"    Origin X  : " << MapMessage.info.origin.position.x <<endl;
   *  cout<<"    Origin Y  : " << MapMessage.info.origin.position.y <<endl;
   *  cout<<"    Origin Yaw: " << tf::getYaw(MapMessage.info.origin.orientation)<<endl;
   */
}



/** Odometry callback function **/
void  TurtlebotRobot::OdometryCallback(nav_msgs::Odometry msg)
{
  //cout<<"odom callback"<<endl;
  //xyz coordinates
  OdometryMessage.pose.pose.position.x=msg.pose.pose.position.x;
  OdometryMessage.pose.pose.position.x=msg.pose.pose.position.x;
  OdometryMessage.pose.pose.position.y=msg.pose.pose.position.y;
  OdometryMessage.pose.pose.position.z=msg.pose.pose.position.z;
  
  //put Quaternions in Odometry message
  OdometryMessage.pose.pose.orientation.x=msg.pose.pose.orientation.x;
  OdometryMessage.pose.pose.orientation.y=msg.pose.pose.orientation.y; 
  OdometryMessage.pose.pose.orientation.z=msg.pose.pose.orientation.z;
  OdometryMessage.pose.pose.orientation.w=msg.pose.pose.orientation.w; 
  
  //put Quaternions in QuaternionMessage
  QuaternionMessage.x=msg.pose.pose.orientation.x;
  QuaternionMessage.y=msg.pose.pose.orientation.y;
  QuaternionMessage.z=msg.pose.pose.orientation.z;
  QuaternionMessage.w=msg.pose.pose.orientation.w;
  
  /** Important: setPose() should be added OdomCallback() OR in OdomCombinedCallback() 
   * but NOT in BOTH to avoid duplicated updates */
  //update Pose attributes. 
  //This will simplify access the robot pose in main program
  setPose(msg.pose.pose.position.x, msg.pose.pose.position.y, tf::getYaw(QuaternionMessage));
  /*setX(msg.pose.pose.position.x); setY(msg.pose.pose.position.y); setYaw(tf::getYaw(QuaternionMessage));*/
  //cout<<"[odom callback] x:"<<getX()<<", y: "<<getY()<<", yaw: "<<getYaw()<<endl;
  
}

/** Combined odometry callback function from robot_ekf_pose **/
void  TurtlebotRobot::OdometryCombinedCallback(geometry_msgs::PoseWithCovarianceStamped msg)
{
  //cout<<"odom combined callback"<<endl;
  //xyz coordinates
  OdomCombinedMessage.pose.pose.position.x=msg.pose.pose.position.x;
  OdometryMessage.pose.pose.position.x=msg.pose.pose.position.x;
  OdometryMessage.pose.pose.position.y=msg.pose.pose.position.y;
  OdometryMessage.pose.pose.position.z=msg.pose.pose.position.z;
  
  //put Quaternions in Odometry message
  OdometryMessage.pose.pose.orientation.x=msg.pose.pose.orientation.x;
  OdometryMessage.pose.pose.orientation.y=msg.pose.pose.orientation.y; 
  OdometryMessage.pose.pose.orientation.z=msg.pose.pose.orientation.z;
  OdometryMessage.pose.pose.orientation.w=msg.pose.pose.orientation.w; 
  
  //put Quaternions in QuaternionMessage
  QuaternionCombinedMessage.x=msg.pose.pose.orientation.x;
  QuaternionCombinedMessage.y=msg.pose.pose.orientation.y;
  QuaternionCombinedMessage.z=msg.pose.pose.orientation.z;
  QuaternionCombinedMessage.w=msg.pose.pose.orientation.w;
  
  /** Important: setPose() should be added OdomCallback() OR in OdomCombinedCallback() 
   * but NOT in BOTH to avoid duplicated updates */
  //update Pose attributes. 
  //This will simplify access the robot pose in main program
  setPoseCombined(msg.pose.pose.position.x, msg.pose.pose.position.y, tf::getYaw(QuaternionCombinedMessage));
  /*setX(msg.pose.pose.position.x); setY(msg.pose.pose.position.y); setYaw(tf::getYaw(QuaternionMessage));*/
  //cout<<"[odom callback] x:"<<getX()<<", y: "<<getY()<<", yaw: "<<getYaw()<<endl;
  
}

/** Combined odometry callback function from robot_ekf_pose **/
void  TurtlebotRobot::AmclPoseCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
  AmclPoseMessage = * msg;
  
  setAmclPose(AmclPoseMessage.pose.pose.position.x, AmclPoseMessage.pose.pose.position.y, tf::getYaw(AmclPoseMessage.pose.pose.orientation));
  
  //cout<<"[odom callback] x:"<<getX()<<", y: "<<getY()<<", yaw: "<<getYaw()<<endl;
  
}



//Odometry callback function
void TurtlebotRobot::LaserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  LaserScanMessage = *msg; 
  //cout<<"LaserScanCallback "<<endl;
}

// Bumper callback function
void TurtlebotRobot::BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
{
  
  BumperMessage = *msg;
  //led_msg_ptr.reset(new kobuki_msgs::Led()); 
  /** *****************************************************************************/
  if (BumperMessage.state == kobuki_msgs::BumperEvent::PRESSED){ // 1: if pressed
    VelocityMessage.linear.x = 0; //set velocities to zero to stop the robot
    VelocityMessage.angular.z = 0;//set velocities to zero to stop the robot
    ALLOW_MOVE_F = false; //set flag to false. This will prevent robot to move in move_robot function
    Led1Message.value = kobuki_msgs::Led::RED;
    Led1Publisher.publish(Led1Message);//turn led1 red when bumper is pressed
  }
  else{
    Led1Message.value = kobuki_msgs::Led::BLACK;
    Led1Publisher.publish(Led1Message);//turn led1 black when bumper is released
  }
  /** *****************************************************************************/
  cout<<endl;
  ROS_INFO("Bumper value: [%s]", ((BumperMessage.bumper)==0?"0: LEFT":((BumperMessage.bumper==1)?"1: CENTER":"2: RIGHT"))); // LEFT   = 0, CENTER = 1, RIGHT  = 2
  ROS_INFO("Bumper state: [%s]", (BumperMessage.state==0?"0: RELEASED":"1: PRESSED")); //RELEASED = 0, PRESSED = 1
  cout<<endl;
} 

// Wheel drop callback function
void TurtlebotRobot::WheelDropCallback(const kobuki_msgs::WheelDropEvent::ConstPtr& msg)
{
  
  WheelDropMessage = *msg;
  /** *****************************************************************************/
  if (WheelDropMessage.state==1){ // if dropped
    VelocityMessage.linear.x = 0; //set velocities to zero to stop the robot
    VelocityMessage.angular.z = 0;//set velocities to zero to stop the robot
    ALLOW_MOVE_F = false; //set flag to false. This will prevent robot to move in move_robot function
  }
  /** *****************************************************************************/
  cout<<endl;
  ROS_INFO("Wheel drop value: [%s]", (WheelDropMessage.wheel==0?"0: LEFT":"1: RIGHT")); // LEFT   = 0, RIGHT  = 1
  ROS_INFO("Wheel drop state: [%s]", (WheelDropMessage.state==0?"0: RAISED":"1: DROPPED")); //RAISED = 0, DROPPED = 1
  cout<<endl;
} 


/** ************* Cliff callback function **************************************/
/** Provides a cliff sensor event.
 * This message is generated whenever a particular cliff sensor signals that the
 * robot approaches or moves away from a cliff.
 * Note that, despite cliff field on SensorState messages, state field is not a
 * bitmask, but the new state of a single sensor.
 */

void TurtlebotRobot::CliffCallback(const kobuki_msgs::CliffEvent::ConstPtr& msg)
{
  CliffMessage = *msg;
  cout<<endl;
  ROS_INFO("Cliff bottom: [%d]", CliffMessage.bottom);// distance to floor when cliff was detected
  ROS_INFO("Cliff sensor: [%s]", ((CliffMessage.sensor)==0?"0: LEFT":((CliffMessage.sensor==1)?"1: CENTER":"2: RIGHT"))); // LEFT   = 0, CENTER = 1, RIGHT  = 2
  ROS_INFO("Cliff state : [%s]", (CliffMessage.state ==0?"0: FLOOR":"1: CLIFF")); //FLOOR = 0, CLIFF = 1
  cout<<endl;
}


void TurtlebotRobot::PowerSystemCallback(const kobuki_msgs::PowerSystemEvent::ConstPtr& msg){
  
  PowerSystemMessage = *msg;
  
  if (PowerSystemMessage.event == kobuki_msgs::PowerSystemEvent::UNPLUGGED){ //uint8  = 0
    ROS_INFO("[PowerSystem CallBack]: The docking base is unplugged");
  } else
    if (PowerSystemMessage.event == kobuki_msgs::PowerSystemEvent::PLUGGED_TO_ADAPTER){ //uint8  = 1
    ROS_INFO("[PowerSystem CallBack]: The docking base is plugged to adapter");
    }else
      if (PowerSystemMessage.event == kobuki_msgs::PowerSystemEvent::PLUGGED_TO_DOCKBASE){ //uint8  = 2
    ROS_INFO("[PowerSystem CallBack]: The docking base is plugged to dock base");
      }else
	if (PowerSystemMessage.event == kobuki_msgs::PowerSystemEvent::CHARGE_COMPLETED){ //uint8  = 3
    Led2Message.value = kobuki_msgs::Led::GREEN;
  Led2Publisher.publish(Led2Message);
  ROS_INFO("[PowerSystem CallBack]: The charge is completed");
	}else
	  if (PowerSystemMessage.event == kobuki_msgs::PowerSystemEvent::BATTERY_LOW){ //uint8  = 4
    Led2Message.value = kobuki_msgs::Led::ORANGE;
    Led2Publisher.publish(Led2Message);
    ROS_INFO("[PowerSystem CallBack]: The battery low. Time to recharge.");
	  }else 
	    if (PowerSystemMessage.event == kobuki_msgs::PowerSystemEvent::BATTERY_CRITICAL){ //uint8  = 4
    Led2Message.value = kobuki_msgs::Led::RED;
    Led2Publisher.publish(Led2Message);
    ROS_INFO("[PowerSystem CallBack]: The battery is CRITICALLY LOW. You must recharge it.");
	    }
	    
	    
}

void TurtlebotRobot::ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg){
	ButtonMessage = *msg;

	ROS_INFO("Button value: [%s]", ((ButtonMessage.button==ButtonMessage.Button0)?"0: BUTTON0":((ButtonMessage.button==ButtonMessage.Button1)?"1: BUTTON1":"2: BUTTON2")));
	ROS_INFO("Button state: [%s]", (ButtonMessage.state==0?"0: RELEASED":"1: PRESSED")); //RELEASED = 0, PRESSED = 1

}




/***********************************************************************************************************************************/
/** This function prints the internal status of Turtlebot  **************************************/
/***********************************************************************************************************************************/
int TurtlebotRobot::printStatus (){
  
  //cout << "----------------------------------------------------" <<endl;
  cout <<endl << "Turtlebot Robot Status Report " <<endl;
  cout << left << setw(16) <<"Name: "<< left << setw(5) << getName() <<endl;
  cout << left << setw(16) <<"Type: "<< left << setw(5) << getType() <<endl;
  cout << left << setw(16) <<"Pose: "<< left << setw(5) << getPose()<<endl;
  cout << left << setw(16) <<"Pose Combined: "<< left << setw(5) << getPoseCombined()<<endl;
  cout << left << setw(16) <<"Pose AMCL: "<< left << setw(5) << getAmclPose()<<endl;
  cout << left << setw(16) <<"IP Address: "<< left << setw(5) << getIPAddress()<<endl;
  cout << left << setw(16) <<"ROS Port Number: "<< left << setw(5) << getROSPortNumber()<<endl;
  cout << left << setw(16) <<"Server Port Number: "<< left << setw(5) << getServerPortNumber()<<endl<<endl;
}

/***********************************************************************************************************************************/
/** This function moves the robot forward. ************************/
/***********************************************************************************************************************************/

double TurtlebotRobot::move (double distance, double linear_velocity, bool forward)
{
  double dist_moved = 0; //estimate of the moved distance
  bool done = false; // flag. set to true when the robot moves all specified distance;
  
  //wait for the listener to get the first message.
  TFListener.waitForTransform("base_footprint", "odom", ros::Time(0), ros::Duration(1.0));
  
  //we will record transforms here
  tf::StampedTransform start_transform;
  tf::StampedTransform current_transform;
  
  //record the starting transform from the odometry to the base frame
  TFListener.lookupTransform("base_footprint", "odom", ros::Time(0), start_transform);
  
  //the command will be to go forward at specified speed in m/s
  VelocityMessage.linear.y = VelocityMessage.angular.z = 0;
  VelocityMessage.linear.x = ((forward==true)?fabs(linear_velocity):-fabs(linear_velocity));
  
  
  //create a timer that fires once each 0.1 sec
  ros::Rate rate(10.0);
  
  //keep publishing velocity command until distance is traveled
  ALLOW_MOVE_F = true; //it will attempt to move
  while (!done )
  {
    
    //send the drive command
    VelocityPublisher.publish(VelocityMessage);
    rate.sleep();
    //get the current transform
    try
    {
      TFListener.waitForTransform("base_footprint", "odom", ros::Time(0), ros::Duration(1.0));
      TFListener.lookupTransform("base_footprint", "odom", ros::Time(0), current_transform);
    }
    catch (tf::TransformException ex)
    {
      ROS_ERROR("%s",ex.what());
      break;
    }
    //see how far we've traveled 
    //following equation CurrentTransform = RelativeMatrix*StartTransform
    tf::Transform relative_transform = start_transform.inverse() * current_transform;
    dist_moved= relative_transform.getOrigin().length();
    
    //std::cout<<"dist_moved: "<<dist_moved<<std::endl;
    
    if(dist_moved > distance) done = true;
    
    if(isObstacleTooClose() && forward) {
      done = true;
      ALLOW_MOVE_F = false;
      cout<<endl;
      cout<<"[Stop Robot]: Reason: getting too close to an obstacle. \nMinimum distance to obstacle: "<<LaserScan::getMinimumRange(LaserScanMessage)<<endl;
      cout<<"Minimum distance to front obstacle: "<<LaserScan::getMinimumRange (LaserScanMessage, 260, 380)<<endl;
      cout<<endl;
      return dist_moved;
    }
    /** *****************************************************************************/
    if (!ALLOW_MOVE_F){ //pressed
      cout<<"[Stop Robot] Possible reasons: \n(1) Bumper hit -> Solution: Take the robot from the obstacle. \n(2) Wheel dropped -> Solution: make sure that wheels are both on the ground "<<endl;
      
      ALLOW_MOVE_F = true;
      return dist_moved;
    }
    /** *****************************************************************************/
    
  }
  
  return dist_moved;
}

/***********************************************************************************************************************************/
/** This function checks whether the robot is too close to obstacle ************************/
/***********************************************************************************************************************************/


bool TurtlebotRobot::isObstacleTooClose(){
  
  bool result=false;
  
  //cout<<"[isObstacleTooClose() function] Minimum distance to front obstacle: "<<LaserScan::getMinimumRange (LaserScanMessage, 260, 380)<<endl;
  if (LaserScan::getMinimumRange (LaserScanMessage, 260, 380)< SAFE_DISTANCE_TO_OBSTACLES)
    result=true;
  
  return result;
}

/** *********************************************************************
 * Function: rotate(double radians, double angular_velocity,bool clockwise)
 * Input: 
 * Output: angle turned
 * Description: This function will make the robot turn to a certain angle
 * and with a certain speed. the command will be published through
 * the VelocityMessage attribute using the VelocityPublisher attribute
 * for turning right, set clockwise to true
 * *********************************************************************/
double TurtlebotRobot::rotate(double radians, double angular_velocity, bool clockwise)
{
  
  double angle_turned =0.0;
  
  //validate angular velocity; ANGULAR_VELOCITY_MINIMUM_THRESHOLD is the minimum allowed
  angular_velocity=((angular_velocity>0.4)?angular_velocity:ANGULAR_VELOCITY_MINIMUM_THRESHOLD);
  
  while(radians < 0) radians += 2*M_PI;
  while(radians > 2*M_PI) radians -= 2*M_PI;
  
  //wait for the listener to get the first message
  TFListener.waitForTransform("base_footprint", "odom", ros::Time(0), ros::Duration(1.0));
  
  //we will record transforms here
  tf::StampedTransform start_transform;
  tf::StampedTransform current_transform;
  
  //record the starting transform from the odometry to the base frame
  TFListener.lookupTransform("base_footprint", "odom", ros::Time(0), start_transform);
  
  
  //the command will be to turn at 0.75 rad/s
  VelocityMessage.linear.x = VelocityMessage.linear.y = 0.0;
  VelocityMessage.angular.z = angular_velocity;
  if (clockwise) VelocityMessage.angular.z = -VelocityMessage.angular.z;
  
  //the axis we want to be rotating by
  tf::Vector3 desired_turn_axis(0,0,1);
  if (!clockwise) desired_turn_axis = -desired_turn_axis;
  
  ros::Rate rate(10.0);
  bool done = false;
  while (!done )
  {
    //send the drive command
    VelocityPublisher.publish(VelocityMessage);
    rate.sleep();
    //get the current transform
    try
    {
      TFListener.waitForTransform("base_footprint", "odom", ros::Time(0), ros::Duration(1.0));
      TFListener.lookupTransform("base_footprint", "odom", ros::Time(0), current_transform);
    }
    catch (tf::TransformException ex)
    {
      ROS_ERROR("%s",ex.what());
      break;
    }
    tf::Transform relative_transform = start_transform.inverse() * current_transform;
    tf::Vector3 actual_turn_axis = relative_transform.getRotation().getAxis();
    angle_turned = relative_transform.getRotation().getAngle();
    
    //std::cout<<"angle_turned: "<<radian2degree(angle_turned)<<std::endl;
    //std::cout<<"radians: "<<radian2degree(radians)<<std::endl;
    
    if (fabs(angle_turned) < 1.0e-2) continue;
    if (actual_turn_axis.dot(desired_turn_axis ) < 0 ) 
      angle_turned = 2 * M_PI - angle_turned;
    
    if (!clockwise)
      VelocityMessage.angular.z = (angular_velocity-ANGULAR_VELOCITY_MINIMUM_THRESHOLD) * (fabs(radian2degree(radians-angle_turned)/radian2degree(radians)))+ANGULAR_VELOCITY_MINIMUM_THRESHOLD;
    else 
      if (clockwise) 
	VelocityMessage.angular.z = (-angular_velocity+ANGULAR_VELOCITY_MINIMUM_THRESHOLD) * (fabs(radian2degree(radians-angle_turned)/radian2degree(radians)))-ANGULAR_VELOCITY_MINIMUM_THRESHOLD;
      
      //std::cout<<"VelocityMessage.angular.z: "<<VelocityMessage.angular.z<<std::endl;
    if (angle_turned > radians) {
      done = true;
      VelocityMessage.linear.x = VelocityMessage.linear.y = VelocityMessage.angular.z = 0;
      VelocityPublisher.publish(VelocityMessage);
    }
    
    /** *****************************************************************************/
    if (!ALLOW_MOVE_F){ //this flag is set to false in bumper callack and wheel drop callback
      cout<<"[Stop Robot] Possible reasons: \n(1) Bumper hit -> Solution: Take the robot from the obstacle. \n(2) Wheel dropped -> Solution: make sure that wheels are both on the ground "<<endl;
      ALLOW_MOVE_F = true;
      return angle_turned;
    }
    /** *****************************************************************************/
    
  }
  if (done) return angle_turned;
  return angle_turned;
}


bool TurtlebotRobot::moveGoal(double TargetX, double TargetY, string frameName, bool blockingMode){
  
  // this is action client that is looking for a service in a server called "move_base"
  //MoveBaseActionClient ac("move_base",true);
  
  int count=1;
  while(!MoveBaseActionClient->waitForServer(ros::Duration(5.0))){
    ROS_INFO("[Attempt %d] I am waiting for move_base server to come up ... ", count);
    if (count++ == 3) {
      ROS_INFO("[Error] move_base server not found after %d attempts. \nYou need to launch move_base server in the robot . \nClose mission.", count);  
      return false;
    }
  }
  move_base_msgs::MoveBaseGoal goal;
  
  // setting the values for target
  
  goal.target_pose.header.frame_id = frameName; //"base_footprint" or "map"; // setting the robot frame
  goal.target_pose.header.stamp = ros::Time::now();// the time stamp
  
  goal.target_pose.pose.position.x = TargetX;
  goal.target_pose.pose.position.y = TargetY;
  
  goal.target_pose.pose.orientation.w = 1.0;
  ROS_INFO("Sending goal to move_base server");
  ROS_INFO_STREAM("Moving to position x:"<<goal.target_pose.pose.position.x<<" y:"<<goal.target_pose.pose.position.y);
  
  Robot::MoveBaseActionClient->sendGoal(goal);
  
  if (blockingMode){
    ROS_INFO("Goal sent, waiting for response from the server ...");
    MoveBaseActionClient->waitForResult();
    if(MoveBaseActionClient->getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Hooray, the base moved to target");
      ROS_INFO_STREAM("Robot moved to position x:"<< goal.target_pose.pose.position.x<<" y:"<<goal.target_pose.pose.position.y);
    }
    else{
      ROS_INFO("The base failed to move forward to target for some reason");
      return false;
    }
  }
  
  return true;
  
}

/** ************************************************************************************ 
 * Function: bool planPath(double targetX, double targetY);
 * planPath(double targetX, double targetY) is a function that send a request to the service
 * make_plan of the node move_base on the topic "move_base/make_plan" to find a path
 * between the current pose (obtained through "/initial_pose" topic and the target pose
 * specified as parameter
 * *************************************************************************************/

bool TurtlebotRobot::planPath(double targetX, double targetY){
  
  /** STEP 1: fill  in the request to send **/
  //nav_msgs::GetPlan::Request request;
  nav_msgs::GetPlan PathPlanningRequestService; 
  
  PathPlanningRequestService.request.start.header.frame_id = "map";
  PathPlanningRequestService.request.start.pose.position.x = getAmclX();
  PathPlanningRequestService.request.start.pose.position.y = getAmclY();
  //may be we need to set to current values
  tf::Quaternion quat = tf::createQuaternionFromYaw(getAmclYaw());
  tf::quaternionTFToMsg(quat, PathPlanningRequestService.request.start.pose.orientation);
  //request.start.pose.orientation.w = 1.0;
  
  PathPlanningRequestService.request.goal.header.frame_id = "map";
  PathPlanningRequestService.request.goal.pose.position.x = targetX;
  PathPlanningRequestService.request.goal.pose.position.y = targetY;
  PathPlanningRequestService.request.goal.pose.orientation.w = 1.0;
  
  /** STEP 2: wait for the service to be ready **/
  int count=1;
  while (!ros::service::waitForService("move_base/make_plan", ros::Duration(4.0))) {
    ROS_INFO("[Attempt %d] Waiting for service move_base/make_plan to become available ... ", count);
    if (count++ == 3) {
      ROS_INFO("[Error] move_base/make_plan service is not activated and not found after %d attempts. \nYou need to launch move_base server in the robot . \nClose mission.", count);  
      return false;
      //return path;
    }
  }
  
  /** STEP 3: Create service client object to send the request **/
  ros::ServiceClient planPathServiceClient = ROSNodeHandle.serviceClient<nav_msgs::GetPlan>("move_base/make_plan", true);
  if (!planPathServiceClient) {
    ROS_FATAL("Could not initialize get plan service from %s", planPathServiceClient.getService().c_str()); //Returns the name of the service this ServiceClient connects to. 
    return false;
    //return path;
  }
  
  /** STEP 3: call service and get plan **/
  if (planPathServiceClient.call(PathPlanningRequestService)) {
    if (!PathPlanningRequestService.response.plan.poses.empty()) {
      int count=1;
      // BOOST_FOREACH http://www.boost.org/doc/libs/1_53_0_beta1/doc/html/foreach.html
      //ROS_WARN("Got the path plan through the topic /move_base/NavfnROS/plan/plan from move_base action server");
      BOOST_FOREACH(const geometry_msgs::PoseStamped &p, PathPlanningRequestService.response.plan.poses) {
	count++;
	//ROS_INFO("x = %d, y = %d. count: %d", static_cast<int>(p.pose.position.x/MapMessage.info.resolution), static_cast<int>(p.pose.position.y/MapMessage.info.resolution), count);
	//ROS_INFO("x = %f, y = %f. count: %d\n", p.pose.position.x, p.pose.position.y, count);
      }
      ROS_INFO("[TurtlebotRobot::planPath] Path Length %d", PathPlanningRequestService.response.plan.poses.size());
      return true;
      //return PathPlanningRequestService.response.plan;
    }
    else {
      ROS_WARN("Got empty plan");
      return false;
      //return path;
    }
  }
  else {
    ROS_ERROR("Failed to call service %s - is the robot moving?", planPathServiceClient.getService().c_str());
    return false;
    //return path;
  }
  return false;
  //return path;
  
}

/** ************************************************************************************ 
 * Function: static bool planPath(double startX, double startY, double targetX, double targetY);
 * planPath(double startX, double startY, double targetX, double targetY) is a function 
 * that sends a request to the service make_plan of the node move_base on the 
 * topic "move_base/make_plan" to find a path
 * between the current pose (obtained through "/initial_pose" topic and the target pose
 * specified as parameter
 * *************************************************************************************/

bool TurtlebotRobot::planPath(ros::NodeHandle ROSNodeHandle, double startX, double startY, double targetX, double targetY){
  
  /** STEP 1: fill  in the request to send **/
  //nav_msgs::GetPlan::Request request;
  nav_msgs::GetPlan PathPlanningRequestService; 
  
  PathPlanningRequestService.request.start.header.frame_id = "map";
  PathPlanningRequestService.request.start.pose.position.x = startX;
  PathPlanningRequestService.request.start.pose.position.y = startY;
  //may be we need to set to current values
  tf::Quaternion quat = tf::createQuaternionFromYaw(0.0);
  tf::quaternionTFToMsg(quat, PathPlanningRequestService.request.start.pose.orientation);
  //request.start.pose.orientation.w = 1.0;
  
  PathPlanningRequestService.request.goal.header.frame_id = "map";
  PathPlanningRequestService.request.goal.pose.position.x = targetX;
  PathPlanningRequestService.request.goal.pose.position.y = targetY;
  PathPlanningRequestService.request.goal.pose.orientation.w = 1.0;
  
  /** STEP 2: wait for the service to be ready **/
  int count=1;
  while (!ros::service::waitForService("move_base/make_plan", ros::Duration(4.0))) {
    ROS_INFO("[Attempt %d] Waiting for service move_base/make_plan to become available ... ", count);
    if (count++ == 3) {
      ROS_INFO("[Error] move_base/make_plan service is not activated and not found after %d attempts. \nYou need to launch move_base server in the robot . \nClose mission.", count);  
      return false;
      //return path;
    }
  }
  
  /** STEP 3: Create service client object to send the request **/
  ros::ServiceClient planPathServiceClient = ROSNodeHandle.serviceClient<nav_msgs::GetPlan>("move_base/make_plan", true);
  if (!planPathServiceClient) {
    ROS_FATAL("Could not initialize get plan service from %s", planPathServiceClient.getService().c_str()); //Returns the name of the service this ServiceClient connects to. 
    return false;
    //return path;
  }
  
  /** STEP 3: call service and get plan **/
  if (planPathServiceClient.call(PathPlanningRequestService)) {
    if (!PathPlanningRequestService.response.plan.poses.empty()) {
      int count=1;
      // BOOST_FOREACH http://www.boost.org/doc/libs/1_53_0_beta1/doc/html/foreach.html
      //ROS_WARN("Got the path plan through the topic /move_base/NavfnROS/plan/plan from move_base action server");
      BOOST_FOREACH(const geometry_msgs::PoseStamped &p, PathPlanningRequestService.response.plan.poses) {
	count++;
	//ROS_INFO("x = %d, y = %d. count: %d", static_cast<int>(p.pose.position.x/MapMessage.info.resolution), static_cast<int>(p.pose.position.y/MapMessage.info.resolution), count);
	//ROS_INFO("x = %f, y = %f. count: %d\n", p.pose.position.x, p.pose.position.y, count);
      }
      ROS_INFO("[TurtlebotRobot::planPath] Path Length %d", PathPlanningRequestService.response.plan.poses.size());
      return true;
      //return PathPlanningRequestService.response.plan;
    }
    else {
      ROS_WARN("Got empty plan");
      return false;
      //return path;
    }
  }
  else {
    ROS_ERROR("Failed to call service %s - is the robot moving?", planPathServiceClient.getService().c_str());
    return false;
    //return path;
  }
  return false;
  //return path;
  
}


/** ************************************************************************************ 
 * Function: bool planPath(double targetX, double targetY);
 * planPath(double targetX, double targetY) is a function that send a request to the service
 * make_plan of the node move_base on the topic "move_base/make_plan" to find a path
 * between the current pose (obtained through "/initial_pose" topic and the target pose
 * specified as parameter
 * *************************************************************************************/

bool TurtlebotRobot::planPath(ros::NodeHandle ROSNodeHandle, double startX, double startY, double targetX, double targetY, nav_msgs::Path &path){
  
  /** STEP 1: fill  in the request to send **/
  //nav_msgs::GetPlan::Request request;
  nav_msgs::GetPlan PathPlanningRequestService; 
  
  PathPlanningRequestService.request.start.header.frame_id = "map";
  PathPlanningRequestService.request.start.pose.position.x = startX;
  PathPlanningRequestService.request.start.pose.position.y = startY;
  cout<<"initX, initY "<<PathPlanningRequestService.request.start.pose.position.x<<", "<<PathPlanningRequestService.request.start.pose.position.y<<endl;
  //may be we need to set to current values
  tf::Quaternion quat = tf::createQuaternionFromYaw(0.0);
  tf::quaternionTFToMsg(quat, PathPlanningRequestService.request.start.pose.orientation);
  //request.start.pose.orientation.w = 1.0;
  
  PathPlanningRequestService.request.goal.header.frame_id = "map";
  PathPlanningRequestService.request.goal.pose.position.x = targetX;
  PathPlanningRequestService.request.goal.pose.position.y = targetY;
  PathPlanningRequestService.request.goal.pose.orientation.w = 1.0;
  
  /** STEP 2: wait for the service to be ready **/
  int count=1;
  while (!ros::service::waitForService("move_base/make_plan", ros::Duration(4.0))) {
    ROS_INFO("[Attempt %d] Waiting for service move_base/make_plan to become available ... ", count);
    if (count++ == 3) {
      ROS_INFO("[Error] move_base/make_plan service is not activated and not found after %d attempts. \nYou need to launch move_base server in the robot . \nClose mission.", count);  
      return false;
      //return path;
    }
  }
  
  /** STEP 3: Create service client object to send the request **/
  ros::ServiceClient planPathServiceClient = ROSNodeHandle.serviceClient<nav_msgs::GetPlan>("move_base/make_plan", true);
  if (!planPathServiceClient) {
    ROS_FATAL("Could not initialize get plan service from %s", planPathServiceClient.getService().c_str()); //Returns the name of the service this ServiceClient connects to. 
    return false;
    //return path;
  }
  
  /** STEP 3: call service and get plan **/
  if (planPathServiceClient.call(PathPlanningRequestService)) {
    if (!PathPlanningRequestService.response.plan.poses.empty()) {
      int count=1;
      // BOOST_FOREACH http://www.boost.org/doc/libs/1_53_0_beta1/doc/html/foreach.html
      //ROS_WARN("Got the path plan through the topic /move_base/NavfnROS/plan/plan from move_base action server");
      BOOST_FOREACH(const geometry_msgs::PoseStamped &p, PathPlanningRequestService.response.plan.poses) {
	count++;
	//ROS_INFO("x = %d, y = %d. count: %d", static_cast<int>(p.pose.position.x/MapMessage.info.resolution), static_cast<int>(p.pose.position.y/MapMessage.info.resolution), count);
	//ROS_INFO("x = %f, y = %f. count: %d\n", p.pose.position.x, p.pose.position.y, count);
      }
      ROS_INFO("[TurtlebotRobot::planPath] Path Length %d", PathPlanningRequestService.response.plan.poses.size());
      path = PathPlanningRequestService.response.plan;
      return true;
      //return PathPlanningRequestService.response.plan;
    }
    else {
      ROS_WARN("Got empty plan");
      return false;
      //return path;
    }
  }
  else {
    ROS_ERROR("Failed to call service %s - is the robot moving?", planPathServiceClient.getService().c_str());
    return false;
    //return path;
  }
  return false;
  //return path;
  
}

bool TurtlebotRobot::planPath(double targetX, double targetY, nav_msgs::Path &path){
  
  /** STEP 1: fill  in the request to send **/
  //nav_msgs::GetPlan::Request request;
  nav_msgs::GetPlan PathPlanningRequestService; 
  
  PathPlanningRequestService.request.start.header.frame_id = "map";
  PathPlanningRequestService.request.start.pose.position.x = getAmclX();
  PathPlanningRequestService.request.start.pose.position.y = getAmclY();
  cout<<"initX, initY "<<PathPlanningRequestService.request.start.pose.position.x<<", "<<PathPlanningRequestService.request.start.pose.position.y<<endl;
  //may be we need to set to current values
  tf::Quaternion quat = tf::createQuaternionFromYaw(getAmclYaw());
  tf::quaternionTFToMsg(quat, PathPlanningRequestService.request.start.pose.orientation);
  //request.start.pose.orientation.w = 1.0;
  
  PathPlanningRequestService.request.goal.header.frame_id = "map";
  PathPlanningRequestService.request.goal.pose.position.x = targetX;
  PathPlanningRequestService.request.goal.pose.position.y = targetY;
  PathPlanningRequestService.request.goal.pose.orientation.w = 1.0;
  
  /** STEP 2: wait for the service to be ready **/
  int count=1;
  while (!ros::service::waitForService("move_base/make_plan", ros::Duration(4.0))) {
    ROS_INFO("[Attempt %d] Waiting for service move_base/make_plan to become available ... ", count);
    if (count++ == 3) {
      ROS_INFO("[Error] move_base/make_plan service is not activated and not found after %d attempts. \nYou need to launch move_base server in the robot . \nClose mission.", count);  
      return false;
      //return path;
    }
  }
  
  /** STEP 3: Create service client object to send the request **/
  ros::ServiceClient planPathServiceClient = ROSNodeHandle.serviceClient<nav_msgs::GetPlan>("move_base/make_plan", true);
  if (!planPathServiceClient) {
    ROS_FATAL("Could not initialize get plan service from %s", planPathServiceClient.getService().c_str()); //Returns the name of the service this ServiceClient connects to. 
    return false;
    //return path;
  }
  
  /** STEP 3: call service and get plan **/
  if (planPathServiceClient.call(PathPlanningRequestService)) {
    if (!PathPlanningRequestService.response.plan.poses.empty()) {
      int count=1;
      // BOOST_FOREACH http://www.boost.org/doc/libs/1_53_0_beta1/doc/html/foreach.html
      //ROS_WARN("Got the path plan through the topic /move_base/NavfnROS/plan/plan from move_base action server");
      BOOST_FOREACH(const geometry_msgs::PoseStamped &p, PathPlanningRequestService.response.plan.poses) {
	count++;
	//ROS_INFO("x = %d, y = %d. count: %d", static_cast<int>(p.pose.position.x/MapMessage.info.resolution), static_cast<int>(p.pose.position.y/MapMessage.info.resolution), count);
	//ROS_INFO("x = %f, y = %f. count: %d\n", p.pose.position.x, p.pose.position.y, count);
      }
      ROS_INFO("[TurtlebotRobot::planPath] Path Length %d", PathPlanningRequestService.response.plan.poses.size());
      path = PathPlanningRequestService.response.plan;
      return true;
      //return PathPlanningRequestService.response.plan;
    }
    else {
      ROS_WARN("Got empty plan");
      return false;
      //return path;
    }
  }
  else {
    ROS_ERROR("Failed to call service %s - is the robot moving?", planPathServiceClient.getService().c_str());
    return false;
    //return path;
  }
  return false;
  //return path;
  
}

/** ******************************************************************************************************** 
 * Function: bool planPathGlobalPlanActionClient(path_planner::GlobalPathPlannerActionMessageGoal goal);
 * planPathGlobalPlanActionClient function is an action client that allows the robot
 * to send a request to the path_planner::PathGlobalPlanActionServer for finding
 * a plan between a start pose and a target pose sent in the parameter goal
 * *********************************************************************************************************/

bool TurtlebotRobot::planPath(path_planner::GlobalPathPlannerActionMessageGoal goal, bool publish_plan){
  
  actionlib::SimpleActionClient<path_planner::GlobalPathPlannerActionMessageAction> GPActionClient("global_planner_action_server", true);
  ROS_INFO("Waiting for action server [global_planner_action_server] to start.");
  bool service_found = GPActionClient.waitForServer(ros::Duration(5.0));
  if (!service_found){
    ROS_ERROR("[global_planner_action_server] action server not found exit.");
    return false;
  }
  
  ROS_INFO("[global_planner_action_server] action server started, sending goal request.");
  
  //send goal to the global_planner_action_server
  GPActionClient.sendGoal(goal);
  
  //wait for the action to return for 30 seconds. 
  bool finished_before_timeout = GPActionClient.waitForResult(ros::Duration(5.0));
  
  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = GPActionClient.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
    int count=0;
    BOOST_FOREACH(const geometry_msgs::PoseStamped &p, GPActionClient.getResult()->plan) {
      count++;
      //ROS_INFO("x = %d, y = %d. count: %d", static_cast<int>(p.pose.position.x/MapMessage.info.resolution), static_cast<int>(p.pose.position.y/MapMessage.info.resolution), count);
      ROS_INFO("x = %f, y = %f. count: %d\n", p.pose.position.x, p.pose.position.y, count);
    }
    
    /** publish the plan to /move_base/TrajectoryPlannerROS/global_plan. This allows the show the path in rivz */
    if (publish_plan){
      nav_msgs::Path plan;
      plan.poses=GPActionClient.getResult()->plan;
      plan.header.frame_id="map";
      GlobalPlanPublisher.publish(plan);
    }
  }
  else
    ROS_INFO("Action did not finish before the time out.");
  
  
  
  return true;
}

/***********************************************************************************************************************************/
/** This function send a command with all speeds set to "0" to receive the most recent status of the robot. ************************/
/***********************************************************************************************************************************/
/*
 * int TurtlebotRobot::getStatus (){
 *  
 *  unsigned char speed_buffer[2];
 *  int res;
 *  
 *  bzero(speed_buffer,2);
 *  speed_buffer[0]=0;
 *  speed_buffer[1]=0;
 *  //cout << "start writing ... ";
 *  res = write(getSocketID(), speed_buffer,2);
 *  //cout << "finish writing ... ";
 *  if (res < 0) { 
 *    cout<<"ERROR writing to socket";
 *    return res;
 * }
 * //get robot data
 * bzero(RobotDataBuffer,15);
 *  res = read(getSocketID(), RobotDataBuffer,15);
 * i f (*res < 0){ 
 *   cout<<"ERROR reading from socket";
 *   return res;
 * } *
 * return res;
 * }
 */








