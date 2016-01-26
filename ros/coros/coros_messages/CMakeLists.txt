cmake_minimum_required(VERSION 2.8.3)
project(coros_messages)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  CorosHeader.msg
  OutBoxMsg.msg
  ResultMsg.msg     # used by the robot to send performed task summary to the control station 
  RobotMsg.msg      # contains robot id
  TaskMsg.msg       # contains robot id, task id
  CostMsg.msg       # contains robot id, task id, cost
  HelloMsg.msg         # contains id, ip and port number. Use to discover neighbors 
  NeighborhoodMsg.msg         # contains id, ip and port number. Use to discover neighbors 
  TargetsMsg.msg         # contains id, targets coordinates. Used to initliaze the app/mission  
  AvailableTargetsMsg.msg # contains id, targets availability array. Used to exchange available targets with neighbors.
)

add_service_files(
  FILES
  neighborhood.srv
  IPAddressService.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES std_msgs 
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs message_runtime
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## No library to declare, since it is headers only package

#############
## Install ##
#############

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
