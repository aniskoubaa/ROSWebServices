cmake_minimum_required(VERSION 2.8.3)
project(coros_processing)

find_package(catkin REQUIRED COMPONENTS
  coros_actions
  coros_messages
  coros_tasks
  roscpp
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS coros_actions coros_messages coros_tasks roscpp
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${coros_tasks_INCLUDE_DIRS}
  ${coros_messages_INCLUDE_DIRS}
  ${coros_tasks_INCLUDE_DIRS}
)

## No library to declare, since coros_tasks is headers only package

#############
## Install ##
#############

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
