cmake_minimum_required(VERSION 2.8.3)
project(mybot_delivery_app)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
  geometry_msgs
  roscpp
  rospy
  std_msgs
  tf
  coros_common
  coros_communication
  coros_kb
  coros_messages
  coros_node
  coros_operator
  coros_processing
  coros_tasks
  message_generation
  move_base_msgs 
  actionlib
)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  DeliveryRequestMsg.msg
)


# Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS tf rospy move_base_msgs actionlib coros_actions coros_common coros_communication coros_kb coros_messages coros_node coros_operator coros_processing coros_tasks roscpp std_msgs message_runtime
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
  ${coros_node_INCLUDE_DIRS} 
  ${coros_operator_INCLUDE_DIRS}
)

#Mybot Delivery Operator Library
add_library(mybot_delivery_operator_lib src/MybotDeliveryOperator.cpp)
target_link_libraries(mybot_delivery_operator_lib ${catkin_LIBRARIES} 
                                                  ${coros_communication_LIBRARIES})

#Mybot Delivery Operator App
add_executable(mybot_delivery_operator_app_node src/mybot_delivery_operator_app.cpp)
target_link_libraries(mybot_delivery_operator_app_node ${catkin_LIBRARIES}
                                                  ${coros_common_LIBRARIES}
                                                  ${coros_messages_LIBRARIES}
                                                  ${coros_communication_LIBRARIES}
                                                  ${coros_operator_LIBRARIES}
                                                  mybot_delivery_operator_lib)
add_dependencies(mybot_delivery_operator_app_node ${catkin_EXPORTED_TARGETS})
