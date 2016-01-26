cmake_minimum_required(VERSION 2.8.3)
project(delivery_app)

find_package(catkin REQUIRED COMPONENTS
  coros_common
  coros_communication
  coros_kb
  coros_messages
  coros_node
  coros_operator
  coros_processing
  coros_tasks
  roscpp
  std_msgs
  message_generation
)


################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  CorosHeader.msg
  DeliveryRequestMsg.msg
  DeliveryStatusMsg.msg
  DeliveryResultMsg.msg
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
  CATKIN_DEPENDS coros_actions coros_common coros_communication coros_kb coros_messages coros_node coros_operator coros_processing coros_tasks roscpp std_msgs message_runtime
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

#Delivery User Library
add_library(delivery_user src/DeliveryUser.cpp src/DeliveryConfiguration.cpp)
target_link_libraries(delivery_user ${catkin_LIBRARIES} 
                                                  ${coros_communication_LIBRARIES})

#Delivery User App
add_executable(delivery_user_app_node src/delivery_user_app.cpp)
target_link_libraries(delivery_user_app_node ${catkin_LIBRARIES}
                                                  ${coros_common_LIBRARIES}
                                                  ${coros_messages_LIBRARIES}
                                                  ${coros_communication_LIBRARIES}
                                                  ${coros_operator_LIBRARIES}
                                                  delivery_user)
add_dependencies(delivery_user_app_node ${catkin_EXPORTED_TARGETS})

#Delivery Operator Library
add_library(delivery_operator src/DeliveryOperator.cpp src/DeliveryConfiguration.cpp)
target_link_libraries(delivery_operator ${catkin_LIBRARIES} 
                                                  ${coros_communication_LIBRARIES})

#Delivery Operator App
add_executable(delivery_operator_app_node src/delivery_operator_app.cpp)
target_link_libraries(delivery_operator_app_node ${catkin_LIBRARIES}
                                                  ${coros_common_LIBRARIES}
                                                  ${coros_messages_LIBRARIES}
                                                  ${coros_communication_LIBRARIES}
                                                  ${coros_operator_LIBRARIES}
                                                  delivery_operator)
add_dependencies(delivery_operator_app_node ${catkin_EXPORTED_TARGETS})

