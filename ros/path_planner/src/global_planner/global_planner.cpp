#include "path_planner/global_planner.h"

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
#include <string>

#include <pluginlib/class_list_macros.h>
//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(global_planner::GlobalPlanner, nav_core::BaseGlobalPlanner)

using namespace std;



//Default Constructor
namespace global_planner {

GlobalPlanner::GlobalPlanner (ros::NodeHandle &nh){
  ROSNodeHandle = nh;

}

GlobalPlanner::GlobalPlanner (){

}

GlobalPlanner::GlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
  initialize(name, costmap_ros);
}


void GlobalPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
  
}

bool GlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start, 
		const geometry_msgs::PoseStamped& goal, 
		std::vector<geometry_msgs::PoseStamped>& plan
	       ){
  
  for (int i=0; i<20; i++){
    geometry_msgs::PoseStamped new_goal = goal;
    tf::Quaternion goal_quat = tf::createQuaternionFromYaw(1.54);

     new_goal.pose.position.x = -2.5+(0.05*i);
     new_goal.pose.position.y = -3.5+(0.05*i);

     new_goal.pose.orientation.x = goal_quat.x();
     new_goal.pose.orientation.y = goal_quat.y();
     new_goal.pose.orientation.z = goal_quat.z();
     new_goal.pose.orientation.w = goal_quat.w();
  
  plan.push_back(new_goal);
  }
  
 return true; 
}


};



























/*




void GlobalPlanner::SetNavigationStackSubscribers (){
  //cout<<"[GlobalPlanner::SetNavigationStackSubscribers ()]"<<endl;
  
  MoveBaseSimpleGoalPoseStampedSubscriber = ROSNodeHandle.subscribe<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1,  &GlobalPlanner::MoveBaseSimpleGoalPoseStampedCallback, this);
  InitialPoseSubscriber = ROSNodeHandle.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 1,  &GlobalPlanner::InitialPoseCallback, this);
  MapSubscriber = ROSNodeHandle.subscribe<nav_msgs::OccupancyGrid>("/map", 1,  &GlobalPlanner::MapCallback, this);
  
  
}

void GlobalPlanner::SetNavigationStackPublishers (){
  //cout<<"[GlobalPlanner::SetNavigationStackPublishers ()]"<<endl;
  GlobalPlanPublisher = ROSNodeHandle.advertise< nav_msgs::Path >("/move_base/TrajectoryPlannerROS/global_plan", 10);
  //for sending initial pose
  InitialPosePublisher = ROSNodeHandle.advertise< geometry_msgs::PoseWithCovarianceStamped >("/initialpose", 10);
  //for sending 2D Nav Goal (like in rviz)
  MoveBaseSimpleGoalPoseStampedPublisher = ROSNodeHandle.advertise< geometry_msgs::PoseStamped >("/move_base_simple/goal", 10);
  //PoseStampedGoalPublisher = ROSNodeHandle.advertise< geometry_msgs::PoseWithCovarianceStamped >("/move_base_simple/goal", 10);
  
}


void GlobalPlanner::MoveBaseSimpleGoalPoseStampedCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
  cout<<"[Pose Stamped Goal Callback]"<<endl;
  MoveBaseSimpleGoalPoseStampedMessage = *msg;
  Pose2D goalPose (MoveBaseSimpleGoalPoseStampedMessage.pose.position.x, MoveBaseSimpleGoalPoseStampedMessage.pose.position.y, tf::getYaw(MoveBaseSimpleGoalPoseStampedMessage.pose.orientation));
  cout<<"   --> Pose Stamped Goal Received Pose: "<<goalPose<<endl<<endl;
}


void GlobalPlanner::InitialPoseCallback (const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
  InitialPoseMessage = *msg;
  cout<<"[GlobalPlanner::InitialPoseCallback]"<<endl;
  Pose2D initPose (InitialPoseMessage.pose.pose.position.x, InitialPoseMessage.pose.pose.position.y, tf::getYaw(InitialPoseMessage.pose.pose.orientation));
  cout<<"   --> Initial Pose Received: "<<initPose<<endl<<endl;
  
}
void GlobalPlanner::MapCallback (const nav_msgs::OccupancyGrid::ConstPtr& msg){
  
  cout <<"[GlobalPlanner::MapCallback] copying map into OGM under progress. waiting ..."<<endl;
  MapMessage = *msg;
  setprecision(6);
  cout<<"    Resolution: " << msg->info.resolution <<endl;
  OGM = new OccupancyGridMap (MapMessage.info.width, MapMessage.info.height, MapMessage.info.resolution);
  cout<<"Map Info" <<endl;
  cout<<"    Width     : " << MapMessage.info.width <<endl;
  cout<<"    Height    : " << MapMessage.info.height <<endl;
  cout<<"    Resolution: " << setw(6)<< setprecision(6)<< MapMessage.info.resolution <<endl;
  cout<<"    Origin X  : " << MapMessage.info.origin.position.x <<endl;
  cout<<"    Origin Y  : " << MapMessage.info.origin.position.y <<endl;
  cout<<"    Origin Yaw: " << tf::getYaw(MapMessage.info.origin.orientation)<<endl;
  
  // copying the map from MapMessage to OGM map object 
  for (int i=0;i<MapMessage.info.height;i++)
    for (int j=0;j<MapMessage.info.width;j++){
      //cout<<"map["<<i<<"]: " << static_cast <int>(MapMessage.data[i]) <<"index: "<<static_cast <int> (OGM->getCellIndex(i,j)])<<"    Width     : " << MapMessage.info.width <<"    Height    : " << MapMessage.info.height <<endl;
      OGM->getMapLayout()[i][j]=static_cast <int>(MapMessage.data[OGM->getCellIndex(i,j)]); 
    }
    
    //uncomment if you want to export the map. it was tested with success.
    //OGM->exportMapLayout("turtlebot_map.pgm", OGM->getMapLayout());
  cout <<"[GlobalPlanner::MapCallback]  copying map into OGM completed"<<endl;
  
    cout<<"Map Info" <<endl;
    cout<<"    Width     : " << MapMessage.info.width <<endl;
    cout<<"    Height    : " << MapMessage.info.height <<endl;
    cout<<"    Origin X  : " << MapMessage.info.origin.position.x <<endl;
   cout<<"    Origin Y  : " << MapMessage.info.origin.position.y <<endl;
    cout<<"    Origin Yaw: " << tf::getYaw(MapMessage.info.origin.orientation)<<endl;
  
}

*/
  
/*
int main(int argc, char *argv[]){
  
  /** Initialize ROS node. 
   * It must be declared in the begining of the program because of TF Listener
   *This specifies the name of the node **/
  /*
  ros::init(argc, argv, "global_planner_node");
  //create a node handle
  ros::NodeHandle nh;
  
  
 GlobalPlanner GP (nh);
 cout<<"Global Planner"<<endl; 
 
 ros::spin();
 return 1;
}
*/
