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
#include <actionlib/server/simple_action_server.h>
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

#include <tf/tf.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
/** ********************************************/ 
#include <coros_common/Pose2D.h>
#include "coros_common/nav_lib.h"

#include <boost/foreach.hpp>
//#define forEach BOOST_FOREACH

/** for global path planner interface */
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>
#include <nav_core/base_global_planner.h>

#include <geometry_msgs/PoseStamped.h>
#include <angles/angles.h>

//#include <pcl_conversions/pcl_conversions.h>
#include <base_local_planner/world_model.h>
#include <base_local_planner/costmap_model.h>


#include <path_planner/GlobalPathPlannerActionMessageAction.h>
#include "OccupancyGridMap.h"


using std::string;

#ifndef GLOBAL_PLANNER_CPP
#define GLOBAL_PLANNER_CPP


namespace global_planner {
  
class GlobalPlannerActionServer {
public:
  GlobalPlannerActionServer (ros::NodeHandle &, string);
  ros::NodeHandle ROSNodeHandle;
  
  string ActionServerName;
  
  /** define the action server and its callback function **/
  actionlib::SimpleActionServer<path_planner::GlobalPathPlannerActionMessageAction> GPActionServer; 
  void executeCB(const path_planner::GlobalPathPlannerActionMessageGoalConstPtr &goal);
  
  /** define that are used to published feedback/result **/
  path_planner::GlobalPathPlannerActionMessageFeedback FeedbackMessage;
  path_planner::GlobalPathPlannerActionMessageResult ResultMessage;
   
  
  /** ROS Navigation Stack Parameters **/
  
  void SetNavigationStackSubscribers ();
  void SetNavigationStackPublishers ();
  
  
  /** Parameters for Global Path Planning **/
  void MoveBaseSimpleGoalPoseStampedCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void InitialPoseCallback (const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
  void MapCallback (const nav_msgs::OccupancyGrid::ConstPtr& msg);
  
  /** Subscribers and Publishers **/
  
  ros::Subscriber MoveBaseSimpleGoalPoseStampedSubscriber; //move_base_simple/goal (geometry_msgs/PoseStamped)
  geometry_msgs::PoseStamped MoveBaseSimpleGoalPoseStampedMessage; //(geometry_msgs/PoseStamped)
  ros::Publisher MoveBaseSimpleGoalPoseStampedPublisher;
   
  ros::Subscriber InitialPoseSubscriber; //initialpose (geometry_msgs/PoseWithCovarianceStamped)
  geometry_msgs::PoseWithCovarianceStamped InitialPoseMessage; //(geometry_msgs/PoseWithCovarianceStamped)
  ros::Publisher InitialPosePublisher;
    
  ros::Subscriber MapSubscriber; //map (nav_msgs/OccupancyGrid)
  nav_msgs::OccupancyGrid MapMessage; //(nav_msgs/OccupancyGrid)
  
  ros::Publisher GlobalPlanPublisher; // topic: /move_base/TrajectoryPlannerROS/global_plan (nav_msgs/Path)
  nav_msgs::Path GloblaPathMessage; //(nav_msgs/Path)
  
    ros::Publisher NavfnROSPublisher;// topic: /move_base/NavfnROS/plan (nav_msgs/Path)s
  nav_msgs::Path NavfnROSPlanMessage;//(nav_msgs/Path)
  
  /** define a map object **/
  OccupancyGridMap *OGM;
 
};

};
#endif
