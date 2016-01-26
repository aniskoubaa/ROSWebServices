cmake_minimum_required(VERSION 2.8.3)
project(robot_control)

find_package(catkin REQUIRED COMPONENTS
  actionlib_msgs 
  actionlib
  geometry_msgs
  move_base_msgs
  nav_msgs
  roscpp
  std_msgs
  tf
  message_generation
  coros_common REQUIRED
  coros_communication REQUIRED
  path_planner REQUIRED
)

#generate_messages(
  #DEPENDENCIES actionlib_msgs std_msgs geometry_msgs move_base_msgs nav_msgs
#)

###################################
## catkin specific configuration ##
###################################

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES robot_control laser_scan
  CATKIN_DEPENDS roscpp std_msgs  coros_common coros_communication path_planner actionlib_msgs actionlib geometry_msgs move_base_msgs nav_msgs tf message_runtime
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories( include
  ${catkin_INCLUDE_DIRS}
  ${coros_communication_INCLUDE_DIRS}  
  ${coros_common_INCLUDE_DIRS}
  ${path_planner_INCLUDE_DIRS}
)

#laser_scan library
add_library(laser_scan src/sensors/laserscan/LaserScan.cpp)

#robot_control library
add_library(robot_control src/robot/Robot.cpp 
                          src/robot/TurtlebotRobot.cpp)
add_dependencies(robot_control robot_control_generate_messages_cpp)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS robot_control laser_scan
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
