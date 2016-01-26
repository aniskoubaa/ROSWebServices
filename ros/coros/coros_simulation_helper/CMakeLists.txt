cmake_minimum_required(VERSION 2.8.3)
project(coros_simulation_helper)

find_package(catkin REQUIRED COMPONENTS
  coros_common
  coros_communication
  coros_kb
  coros_messages
  coros_operator
  roscpp
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES discovery_helper_server discovery_helper_server_app_node discovery_helper_operator discovery_helper_operator_app_node
  CATKIN_DEPENDS coros_common coros_communication coros_kb coros_messages coros_operator roscpp
)

###########
## Build ##
###########

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${coros_common_INCLUDE_DIRS}
  ${coros_messages_INCLUDE_DIRS}
  ${coros_communication_INCLUDE_DIRS}
  ${coros_kb_INCLUDE_DIRS}
  ${coros_operator_INCLUDE_DIRS}
)

#Discovery Helper Server Library
add_library(discovery_helper_server src/DiscoveryHelperServer.cpp )
target_link_libraries(discovery_helper_server ${catkin_LIBRARIES})


#Discovery Helper Server App
add_executable(discovery_helper_server_app_node src/discovery_helper_server_app.cpp)
target_link_libraries(discovery_helper_server_app_node 
                                                ${catkin_LIBRARIES}
                                                ${coros_common_LIBRARIES}
                                                ${coros_messages_LIBRARIES}
                                                ${coros_communication_LIBRARIES}
                                                ${coros_kb_LIBRARIES}
                                                discovery_helper_server
												libboost_serialization.so)
add_dependencies(discovery_helper_server_app_node ${catkin_EXPORTED_TARGETS})


#Discovery Helper Operator Library
add_library(discovery_helper_operator  src/DiscoveryHelperOperator.cpp)
target_link_libraries(discovery_helper_operator ${catkin_LIBRARIES} )

#Discovery Helper Operator App
add_executable(discovery_helper_operator_app_node src/discovery_helper_operator_app.cpp)
target_link_libraries(discovery_helper_operator_app_node 
                                                  ${catkin_LIBRARIES}
                                                  ${coros_common_LIBRARIES}
                                                  ${coros_messages_LIBRARIES}
                                                  ${coros_communication_LIBRARIES}
                                                  ${coros_operator_LIBRARIES}
                                                  discovery_helper_operator
                                                  libboost_serialization.so)
add_dependencies(discovery_helper_operator_app_node ${catkin_EXPORTED_TARGETS})

