cmake_minimum_required(VERSION 2.8.3)
project(discovery_app_2)

find_package(catkin REQUIRED COMPONENTS
  coros_common
  coros_messages
  coros_communication
  coros_kb
  coros_operator
  roscpp
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES discovery_operator_2 discovery_operator_app_node
  CATKIN_DEPENDS coros_common coros_messages coros_communication coros_kb coros_operator roscpp
)

###########
## Build ##
###########

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${coros_common_INCLUDE_DIRS}
  ${coros_messages_INCLUDE_DIRS}
  ${coros_communication_INCLUDE_DIRS}
  ${coros_kb_INCLUDE_DIRS}
  #${coros_node_INCLUDE_DIRS} 
  ${coros_operator_INCLUDE_DIRS}
)


#Discovery Operator Library
add_library(discovery_operator_2  src/DiscoveryOperator.cpp src/DiscoveryConfiguration.cpp)
target_link_libraries(discovery_operator_2 ${catkin_LIBRARIES} 
                                                  ${coros_communication_LIBRARIES})

#Discovery Operator App
add_executable(discovery_operator_app_2_node src/discovery_operator_app.cpp)
target_link_libraries(discovery_operator_app_2_node ${catkin_LIBRARIES}
                                                  ${coros_common_LIBRARIES}
                                                  ${coros_messages_LIBRARIES}
                                                  ${coros_communication_LIBRARIES}
                                                  ${coros_operator_LIBRARIES}
                                                  discovery_operator_2)
add_dependencies(discovery_operator_app_2_node ${catkin_EXPORTED_TARGETS})

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS discovery_operator_2 discovery_operator_app_2_node
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

