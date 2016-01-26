//include standard and socket libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string>
//include ros libraries
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/PointCloud2.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <nav_msgs/OccupancyGrid.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
//include custom libraries
//#include "../autonav/mathlib.h"
#include "LaserScan.h"

#include <path_planner/GlobalPathPlannerActionMessageAction.h>
#include "Robot.h"

using std::string;

#ifndef TURTLEBOTROBOT_H
#define TURTLEBOTROBOT_H


#define MINIMUM_DISTANCE_THRESHOLD 0.6
#define DISTANCE_THRESHOLD_TO_OBSTACLES 1.0 //used in autoRotateRobot. to be checked
#define SAFE_DISTANCE_TO_OBSTACLES 0.9 //to avoid hitting an obstacle. used in isObstacleTooClose()
#define LINEAR_VELOCITY_MINIMUM_THRESHOLD 0.2 //minium linear vecolity allowed. used to control linear speed when approaching an obstacle
#define ANGULAR_VELOCITY_MINIMUM_THRESHOLD 0.4 //minimum angular vecolity allowed
#define RANGE_DIFFERENCE_MAX_THRESHOLD 0.5 //maximum difference threshold between left and right ranges
#define RANGE_DIFFERENCE_MIN_THRESHOLD 0.2 //minimum difference threshold between left and right ranges
#define MAX_RANGE 4.0

class TurtlebotRobot : public Robot {
  
public: 
  
  TurtlebotRobot (ros::NodeHandle &, POSE = 0, POSE = 0, POSE = 0, string =LOCALHOST_IP, string ="turtlebot_no_name", unsigned short = 11311, unsigned short = 12345);
  TurtlebotRobot (const ros::NodeHandle &, string ="turtlebot_no_name");
  
  //This function prints the internal status of turtlebot  
  int printStatus();
  
  bool isObstacleTooClose();
  
  double move (double distance,double linear_velocity,bool forward);
  double rotate(double radians, double angular_velocity, bool clockwise);
  bool moveGoal(double TargetX, double TargetY, string frameName, bool blockingMode=true);
  
  
  /** ************************************************************************************ 
   * Function: bool planPath(double targetX, double targetY);
   * planPath(double targetX, double targetY) is a function that send a request to the service
   * make_plan of the node move_base on the topic "move_base/make_plan" to find a path
   * between the current pose (obtained through "/initial_pose" topic and the target pose
   * specified as parameter
   * *************************************************************************************/
  bool planPath(double targetX, double targetY, nav_msgs::Path &path);
  bool planPath(double targetX, double targetY);
  /** static version of planPath (double targetX, double targetY);*/
  static bool planPath(ros::NodeHandle, double startX, double startY, double targetX, double targetY);
  static bool planPath(ros::NodeHandle, double startX, double startY, double targetX, double targetY, nav_msgs::Path &path);
  
  /** ******************************************************************************************************** 
   * Function: bool planPathGlobalPlanActionClient(path_planner::GlobalPathPlannerActionMessageGoal goal);
   * planPathGlobalPlanActionClient function is an action client that allows the robot
   * to send a request to the path_planner::PathGlobalPlanActionServer for finding
   * a plan between a start pose and a target pose sent in the parameter goal
   * if publish_plan is set to true, the planned path will be publihsed to topic /move_base/TrajectoryPlannerROS/global_plan
   * and can be vizualized with rviz 
   * *********************************************************************************************************/
  bool planPath(path_planner::GlobalPathPlannerActionMessageGoal goal, bool publish_plan);
  
  
  void SetPublishers ();
  void SetSubscribers ();
  
  void SetNavigationStackPublishers ();
  void SetNavigationStackSubscribers ();
  
  
    /** ***** ROS Callbacks ****** **/
   void OdometryCallback(nav_msgs::Odometry msg);
   void OdometryCombinedCallback(geometry_msgs::PoseWithCovarianceStamped msg);
   void LaserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
   void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg);
   void CliffCallback(const kobuki_msgs::CliffEvent::ConstPtr& msg);
   void WheelDropCallback(const kobuki_msgs::WheelDropEvent::ConstPtr& msg);
   void PowerSystemCallback(const kobuki_msgs::PowerSystemEvent::ConstPtr& msg);
   void ButtonCallback(const kobuki_msgs::ButtonEvent::ConstPtr& msg);
   
   
   /** ***** ROS Navigation Callbacks ****** **/
   
   void PoseStampedGoalCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void MoveBaseActionGoalCallback(const move_base_msgs::MoveBaseActionGoal::ConstPtr& msg);
   void InitialPoseCallback (const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
   void AmclPoseCallback (const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
   void MapCallback (const nav_msgs::OccupancyGrid::ConstPtr& msg);
   
   
   /** ***** Kobuki base messages ****** **/
   kobuki_msgs::BumperEvent BumperMessage; 
   kobuki_msgs::CliffEvent CliffMessage;
   kobuki_msgs::WheelDropEvent WheelDropMessage;
   kobuki_msgs::Led Led1Message;
   kobuki_msgs::Led Led2Message;
   kobuki_msgs::PowerSystemEvent PowerSystemMessage;
   kobuki_msgs::ButtonEvent ButtonMessage;
  
};

#endif
