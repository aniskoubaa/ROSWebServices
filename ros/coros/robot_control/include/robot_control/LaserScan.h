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
#include <kobuki_msgs/BumperEvent.h> 
#include <kobuki_msgs/CliffEvent.h> 
#include <kobuki_msgs/WheelDropEvent.h> 
#include "coros_common/nav_lib.h"
using std::string;

#ifndef LASERSCAN_H
#define LASERSCAN_H

/** This class is defined for processing laser scan data **/

class LaserScan {
  
public:
  
  /** ****************************************************
   * Laser data processing functions
   * ****************************************************/
  
  static int getIndexOfMaximumRange(sensor_msgs::LaserScan & LaserScanMsg);
  static int getIndexOfMinimumRange(sensor_msgs::LaserScan & LaserScanMsg);
  
  static double getRelativeAngleOfMaximumRange(sensor_msgs::LaserScan & msg);
  static double getRelativeAngleOfMinimumRange(sensor_msgs::LaserScan & LaserScanMsg);
  static void printLaserScanRanges(sensor_msgs::LaserScan & LaserScanMsg);
  
  static double getAverageRange (sensor_msgs::LaserScan & laser_scan_msg, int start_index, int end_index);
  static double getAverageRangeLeft(sensor_msgs::LaserScan & laser_scan_msg, double degree);
  static double getAverageRangeRight(sensor_msgs::LaserScan & laser_scan_msg, double degree);
  static double getAverageRangeStraight(sensor_msgs::LaserScan & laser_scan_msg, double degree);
  
  static double getMaximumRange(sensor_msgs::LaserScan & msg);
  static double getFrontRange(sensor_msgs::LaserScan & msg);
  static double getMinimumRange(sensor_msgs::LaserScan & msg);
  
  static double getMinimumRange (sensor_msgs::LaserScan & laser_scan_msg, int start_index, int end_index);
  static double getMinimumRangeLeft(sensor_msgs::LaserScan & laser_scan_msg, double degree);
  static double getMinimumRangeRight(sensor_msgs::LaserScan & laser_scan_msg, double degree);
  
  static double getMaximumRange (sensor_msgs::LaserScan & laser_scan_msg, int start_index, int end_index);
  static double getMaximumRangeLeft(sensor_msgs::LaserScan & laser_scan_msg, double degree);
  static double getMaximumRangeRight(sensor_msgs::LaserScan & laser_scan_msg, double degree);
  
  static bool isObstacleTooClose(sensor_msgs::LaserScan & LaserMsg, int start_index, int end_index, double DistanceThreshold);
  
//private:
  
};

#endif
