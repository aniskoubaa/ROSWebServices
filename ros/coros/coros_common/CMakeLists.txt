cmake_minimum_required(VERSION 2.8.3)
project(coros_common)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

###################################
## catkin specific configuration ##
###################################

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES coros_common
   CATKIN_DEPENDS roscpp
)

###########
## Build ##
###########

include_directories( include 
  ${catkin_INCLUDE_DIRS}
)

## Declare coros_common library
add_library(coros_common src/nav_lib.cpp
                          src/Pose2D.cpp) 

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS coros_common
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
