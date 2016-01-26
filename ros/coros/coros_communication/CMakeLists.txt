cmake_minimum_required(VERSION 2.8.3)
project(coros_communication)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  coros_node REQUIRED
  message_generation REQUIRED
)

###################################
## catkin specific configuration ##
###################################

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES coros_communication
  CATKIN_DEPENDS roscpp coros_node message_runtime
)

###########
## Build ##
###########

include_directories( include
  ${catkin_INCLUDE_DIRS}
  ${coros_node_INCLUDE_DIRS}
)

## Declare coros_communication library: coros communication library
add_library(coros_communication 
				      src/AbstractClient.cpp
                      src/AbstractServer.cpp 
                      src/NodeClient.cpp
                      src/NodeServer.cpp)



#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS coros_communication 
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

