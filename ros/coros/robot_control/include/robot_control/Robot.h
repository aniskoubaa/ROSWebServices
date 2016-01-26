#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string>

/** include ros libraries**********************/
#include <ros/ros.h>

#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>

#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseActionGoal.h>

#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/PointCloud2.h"

#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/GetPlan.h>

#include <kobuki_msgs/BumperEvent.h> 
#include <kobuki_msgs/CliffEvent.h> 
#include <kobuki_msgs/WheelDropEvent.h> 
#include <kobuki_msgs/PowerSystemEvent.h> 
#include <kobuki_msgs/Led.h>
#include <kobuki_msgs/ButtonEvent.h>

#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
/** ********************************************/ 
#include "path_planner/OccupancyGridMap.h"
#include "coros_common/Pose2D.h"

#include <boost/foreach.hpp>

#include "coros_common/nav_lib.h"
//#define forEach BOOST_FOREACH


using std::string;

#ifndef ROBOT_H
#define ROBOT_H

#define BUFFER_SIZE 15
#define ROS_PORT_NUMBER 11311
#define SERVER_PORT_NUMBER 12345
#define LOCALHOST_IP "127.0.0.1"

//typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//Abstract Class Robot: some functions are pure virtual
class Robot {
  
public:
  Robot (ros::NodeHandle &, POSE = 0, POSE = 0, POSE = 0, string =LOCALHOST_IP, string = "robot_name", unsigned short = 11311, unsigned short = 12345);
  Robot (const ros::NodeHandle &, string = "robot_name");
  
  /** Public methods **/
  
  //Getters
  Pose2D getPose();
  POSE getX();
  POSE getY();
  POSE getYaw();
  
  Pose2D getPoseCombined();
  POSE getXCombined();
  POSE getYCombined();
  POSE getYawCombined();
  
  Pose2D getAmclPose();
  POSE getAmclX();
  POSE getAmclY();
  POSE getAmclYaw();
  
  string getType();
  string getName();
  string getIPAddress();
  short getROSPortNumber();
  short getServerPortNumber();
  VELOCITY getLinearVelocity();
  VELOCITY getAngularVelocity();
  
  //Setters
  void setPose(Pose2D);
  void setPose(POSE, POSE, POSE);
  void setX(POSE);
  void setY(POSE);
  void setYaw(POSE);
  
  void setPoseCombined(Pose2D);
  void setPoseCombined(POSE, POSE, POSE);
  void setXCombined(POSE);
  void setYCombined(POSE);
  void setYawCombined(POSE);
  
  void setAmclPose(Pose2D);
  void setAmclPose(POSE, POSE, POSE);
  void setAmclX(POSE);
  void setAmclY(POSE);
  void setAmclYaw(POSE);
  
  void setType(string);
  void setName(string);
  void setIPAddress(string);
  void setROSPortNumber(short);
  void setServerPortNumber(short);
  void setLinearVelocity(VELOCITY);
  void setAngularVelocity(VELOCITY);
  
  
  void printPose();
  
  /** ***** ROS publishers and subscribers ****** **/
  
  /** Create a global variable for odometry publisher message  **/
  nav_msgs::Odometry OdometryMessage;
  ros::Subscriber OdometerySubscriber;
  geometry_msgs::Quaternion QuaternionMessage;
  
  /** Create a global variable for combined odometry (robot_pose_ekf) publisher message  **/
  geometry_msgs::PoseWithCovarianceStamped OdomCombinedMessage;
  ros::Subscriber OdomCombinedSubscriber;
  geometry_msgs::Quaternion QuaternionCombinedMessage;
  
  /** Create a global variable for AMCL pose (amcl node) publisher message  **/
  geometry_msgs::PoseWithCovarianceStamped AmclPoseMessage;
  ros::Subscriber AmclPoseSubscriber;
  
  
  /** Create a global variable for Laser Scan Message and Publisher **/
  sensor_msgs::LaserScan LaserScanMessage;
  ros::Subscriber LaserScanSubscriber;
  
  /** Create a global variable for Bumper Message **/
  //kobuki_msgs::BumperEvent BumperMessage; 
  ros::Subscriber BumperSubscriber;
  
  /** Create a global variable for Cliff Subscriber. 
   * Cliff message is defined in conrete robot class (e.g. TurtlebotRobot)**/
  ros::Subscriber CliffSubscriber;
  
  /** Create a global variable for velocity publihser and message **/
  ros::Publisher VelocityPublisher; //used to publish velocity to turtlebot
  geometry_msgs::Twist VelocityMessage; //Create a Twist message structure
  
  /** Create a global variable for Wheel Drop Message 
   * Wheel Drop message is defined in conrete robot class (e.g. TurtlebotRobot)**/
  ros::Subscriber WheelDropSubscriber;
  
    /** Create a global variable for Power System Subscriber  
   * Power System message is defined in conrete robot class (e.g. TurtlebotRobot)**/
  ros::Subscriber PowerSystemSubscriber;
  
  /** Create a global variable for Button Subscriber
     * Button message is defined in conrete robot class (e.g. TurtlebotRobot)**/
  ros::Subscriber ButtonSubscriber;

  /** Create a TF Listener **/
  tf::TransformListener TFListener;
  
  /** Create publishers and messages for the LEDs 
   LEDs message is defined in conrete robot class (e.g. TurtlebotRobot)**/
  ros::Publisher Led1Publisher;
  ros::Publisher Led2Publisher; 

  
  /** ROS Node Handle **/
  ros::NodeHandle ROSNodeHandle;
  
  
  /** ROS Navigation Stack Parameters **/
  
  /** Parameters for Global Path Planning **/
  ros::Subscriber PoseStampedGoalSubscriber; //move_base_simple/goal (geometry_msgs/PoseStamped)
  geometry_msgs::PoseStamped PoseStampedGoalMessage; //(geometry_msgs/PoseStamped)
  ros::Publisher PoseStampedGoalPublisher;
  
  ros::Subscriber MoveBaseActionGoalSubscriber; //move_base/goal (move_base_msgs/MoveBaseGoal)
  move_base_msgs::MoveBaseActionGoal MoveBaseActionGoalMessage; //(move_base_msgs/MoveBaseActionGoal)
  
  move_base_msgs::MoveBaseGoal MoveBaseGoalMessage; //(move_base_msgs/MoveBaseActionGoal)
   
  ros::Subscriber InitialPoseSubscriber; //initialpose (geometry_msgs/PoseWithCovarianceStamped)
  geometry_msgs::PoseWithCovarianceStamped InitialPoseMessage; //(geometry_msgs/PoseWithCovarianceStamped)
  ros::Publisher InitialPosePublisher;
  
    
  ros::Subscriber MapSubscriber; //map (nav_msgs/OccupancyGrid)
  nav_msgs::OccupancyGrid MapMessage; //(nav_msgs/OccupancyGrid)
  
  ros::Publisher GlobalPlanPublisher; // topic: /move_base/TrajectoryPlannerROS/global_plan (nav_msgs/Path)
  nav_msgs::Path GloblaPathMessage; //(nav_msgs/Path)
  
  /** define a map object **/
  OccupancyGridMap *OGM;
  
  
  /**  
   *  This line constructs an action client that we'll use to communicate with the action named "move_base" 
   *  that adheres to the MoveBaseAction interface. It also tells the action client to start a thread to call 
   *  ros::spin() so that ROS callbacks will be processed by passing "true" as the second argument of 
   *  the MoveBaseClient constructor. */
  
  // pointer is needed, as it is not possible to create the object in the header file. Creatin of object in constructor
  static actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> * MoveBaseActionClient; 
  
  /** starts the TCP server to accept connections from other clients (robots or users)**/
  int startServer();  
  
  /** This function allows the robot to connect to a remote robot using a TCP connection **/
  int connect2TCPServer (short & , string = "127.0.0.1" , unsigned short = 11311);
  
  /** This function allows the robot to send a request to the TCP server **/
  int sendRequest (short );
  
  
  /** This is PURE VIRTUAL function that prints the internal status of the robot **/
  virtual int printStatus ()=0;
  
  /** Status Flags **/
  bool ALLOW_MOVE_F; //flag. if true the robot is allowed to move. some event can change it to false to prevent robot from moving
  
private:
  
  
  //Robot location
  Pose2D Pose; //taken from the topic /odom
  Pose2D PoseCombined; //taken from the topic robot_pose_ekf/odom_combined
  Pose2D AmclPose; //taken from the topic /amcl_pose
  
  //Robot velocities
  VELOCITY LinearVelocity;
  VELOCITY AngularVelocity;
  
  //Other robot Attributes
  string Type; //Turtlebot, Wifibot, Pioneer
  string Name; 
  
  //Connection information
  string IPAddress;
  short ROSPortNumber;//11311 default to connect through XMLRPC
  short ServerPortNumber;//12345 default
  
  
  
};

#endif
