cmake_minimum_required(VERSION 2.8.3)
project(coros_kb)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

###################################
## catkin specific configuration ##
###################################

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES coros_kb
  CATKIN_DEPENDS roscpp
)

###########
## Build ##
###########

include_directories( include
  ${catkin_INCLUDE_DIRS}
)

## Declare coros_kb library: Knowledge Base Manipulation Layer
add_library(coros_kb 
	src/AgentConfiguration.cpp
	src/NeighborsConfiguration.cpp
	src/AgentState.cpp
)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS coros_kb 
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
