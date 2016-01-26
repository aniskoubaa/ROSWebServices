#include "path_planner/global_planner_action_server.h"

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


using namespace std;




namespace global_planner {

/** Default Constructor **/
GlobalPlannerActionServer::GlobalPlannerActionServer (ros::NodeHandle &nh, string action_server_name): 
GPActionServer(nh, action_server_name, boost::bind(&GlobalPlannerActionServer::executeCB, this, _1), false) /** constructor for the action server **/
{
  ROSNodeHandle = nh;
  SetNavigationStackSubscribers ();
  SetNavigationStackPublishers ();
  ActionServerName = action_server_name;
  
  /** starting the action server **/
  ROS_INFO("\n[GlobalPlannerActionServer::GlobalPlannerActionServer] \nStarting GPActionServer [%s]\n\n", ActionServerName.c_str());
  GPActionServer.start();
  ROS_INFO("\n[GlobalPlannerActionServer::GlobalPlannerActionServer] \nGPActionServer [%s] has started and waiting for action requests\n\n", ActionServerName.c_str());
}

/** Server Callback function **/
void GlobalPlannerActionServer::executeCB(const path_planner::GlobalPathPlannerActionMessageGoalConstPtr &goal)
  {
    //initializing the plan to an empty array of poses
    FeedbackMessage.plan.clear();
    //add the initial location to the plan
    ROS_INFO("[executeCB] start: (%f, %f), target: (%f, %f)\n\n", goal->start.pose.position.x, goal->start.pose.position.y, goal->target.pose.position.x,goal->target.pose.position.y);
    FeedbackMessage.plan.push_back(goal->start);
    FeedbackMessage.plan.push_back(goal->start);
    FeedbackMessage.plan.push_back(goal->target);
    
    // publish info to the console for the user
    ROS_INFO("\n[GlobalPlannerActionServer::executeCB] \n[%s]: Executing, creating path plan for from (%f,%f) to (%f,%f)\n\n", ActionServerName.c_str(), goal->start.pose.position.x, FeedbackMessage.plan[0].pose.position.y, goal->target.pose.position.x,goal->target.pose.position.y);
    
    GPActionServer.publishFeedback(FeedbackMessage);
    ResultMessage.plan = FeedbackMessage.plan;
    ROS_INFO("\n[GlobalPlannerActionServer::executeCB] \n[%s]: Action Succeeded. Send results to client\n\n", ActionServerName.c_str());
    GPActionServer.setSucceeded(ResultMessage);
  }

void GlobalPlannerActionServer::SetNavigationStackSubscribers (){
  //cout<<"[GlobalPlannerActionServer::SetNavigationStackSubscribers ()]"<<endl;
  MoveBaseSimpleGoalPoseStampedSubscriber = ROSNodeHandle.subscribe<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1,  &GlobalPlannerActionServer::MoveBaseSimpleGoalPoseStampedCallback, this);
  InitialPoseSubscriber = ROSNodeHandle.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 1,  &GlobalPlannerActionServer::InitialPoseCallback, this);
  MapSubscriber = ROSNodeHandle.subscribe<nav_msgs::OccupancyGrid>("/map", 1,  &GlobalPlannerActionServer::MapCallback, this);
}

void GlobalPlannerActionServer::SetNavigationStackPublishers (){
  //cout<<"[GlobalPlannerActionServer::SetNavigationStackPublishers ()]"<<endl;
  GlobalPlanPublisher = ROSNodeHandle.advertise< nav_msgs::Path >("/move_base/TrajectoryPlannerROS/global_plan", 10);
  //for sending Navfn Plan
  NavfnROSPublisher = ROSNodeHandle.advertise< nav_msgs::Path >("/move_base/NavfnROS/plan", 10);
  //for sending initial pose
  InitialPosePublisher = ROSNodeHandle.advertise< geometry_msgs::PoseWithCovarianceStamped >("/initialpose", 10);
  //for sending 2D Nav Goal (like in rviz)
  MoveBaseSimpleGoalPoseStampedPublisher = ROSNodeHandle.advertise< geometry_msgs::PoseStamped >("/move_base_simple/goal", 10);
  //PoseStampedGoalPublisher = ROSNodeHandle.advertise< geometry_msgs::PoseWithCovarianceStamped >("/move_base_simple/goal", 10);
}

/** /move_base_simple/goal **/
void GlobalPlannerActionServer::MoveBaseSimpleGoalPoseStampedCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
  cout<<"[Pose Stamped Goal Callback]"<<endl;
  MoveBaseSimpleGoalPoseStampedMessage = *msg;
  Pose2D goalPose (MoveBaseSimpleGoalPoseStampedMessage.pose.position.x, MoveBaseSimpleGoalPoseStampedMessage.pose.position.y, tf::getYaw(MoveBaseSimpleGoalPoseStampedMessage.pose.orientation));
  cout<<"   --> Pose Stamped Goal Received Pose: "<<goalPose<<endl<<endl;
}


void GlobalPlannerActionServer::InitialPoseCallback (const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
  InitialPoseMessage = *msg;
  cout<<"[GlobalPlannerActionServer::InitialPoseCallback]"<<endl;
  Pose2D initPose (InitialPoseMessage.pose.pose.position.x, InitialPoseMessage.pose.pose.position.y, tf::getYaw(InitialPoseMessage.pose.pose.orientation));
  cout<<"   --> Initial Pose Received: "<<initPose<<endl<<endl;
  
}
void GlobalPlannerActionServer::MapCallback (const nav_msgs::OccupancyGrid::ConstPtr& msg){
  
  cout <<"[GlobalPlannerActionServer::MapCallback] copying map into OGM under progress. waiting ..."<<endl;
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
  
  /** copying the map from MapMessage to OGM map object **/
  for (int i=0;i<MapMessage.info.height;i++)
    for (int j=0;j<MapMessage.info.width;j++){
      //cout<<"map["<<i<<"]: " << static_cast <int>(MapMessage.data[i]) <<"index: "<<static_cast <int> (OGM->getCellIndex(i,j)])<<"    Width     : " << MapMessage.info.width <<"    Height    : " << MapMessage.info.height <<endl;
      OGM->getMapLayout()[i][j]=static_cast <int>(MapMessage.data[OGM->getCellIndex(i,j)]); 
    }
    
    //uncomment if you want to export the map. it was tested with success.
    //OGM->exportMapLayout("turtlebot_map.pgm", OGM->getMapLayout());
  cout <<"[GlobalPlannerActionServer::MapCallback]  copying map into OGM completed"<<endl;
  /*
   *  cout<<"Map Info" <<endl;
   *  cout<<"    Width     : " << MapMessage.info.width <<endl;
   *  cout<<"    Height    : " << MapMessage.info.height <<endl;
   *  cout<<"    Origin X  : " << MapMessage.info.origin.position.x <<endl;
   *  cout<<"    Origin Y  : " << MapMessage.info.origin.position.y <<endl;
   *  cout<<"    Origin Yaw: " << tf::getYaw(MapMessage.info.origin.orientation)<<endl;
   */
}

};


int main(int argc, char *argv[]){
  
  /** Initialize ROS node. 
   * It must be declared in the begining of the program because of TF Listener
   *This specifies the name of the node **/
  
  ros::init(argc, argv, "global_planner_action_server_node");
  //create a node handle
  ros::NodeHandle nh;
  
 
 /** name of the server "Global Planner Action Server" **/
 //global_planner::GlobalPlannerActionServer GPAS (nh, ros::this_node::getName()); //give the same of the node to the server
 global_planner::GlobalPlannerActionServer GPAS (nh, "global_planner_action_server"); //give the same of the node to the server
 cout<<"[global_planner_action_server] started ... "<<endl; 
 /*
 nav_msgs::Path plan;
 
 
  ros::AsyncSpinner SpinThread(12);
  SpinThread.start();
  ros::Rate threadRate(12);
  char ok='a';
 
 while (ok!='q'){
 cout<<"write q to quit: "<<endl;
 cin>> ok;
 for (int i=0; i<20; i++){
    geometry_msgs::PoseStamped new_goal ;
    tf::Quaternion goal_quat = tf::createQuaternionFromYaw(1.54);

    new_goal.header.frame_id="/map";
    
     new_goal.pose.position.x = -2.0 +(0.05*i);
     new_goal.pose.position.y = -2.7 +(0.05*i);

     new_goal.pose.orientation.x = 0;
     new_goal.pose.orientation.y = 0;
     new_goal.pose.orientation.z = 0;
     new_goal.pose.orientation.w = 1;
     
     
  
  plan.poses.push_back(new_goal);
  }
  
  plan.header.frame_id="/map";
  
  GPAS.GlobalPlanPublisher.publish(plan);
  GPAS.NavfnROSPublisher.publish(plan);
 }
 */
 ros::spin();
 return 1;
}
