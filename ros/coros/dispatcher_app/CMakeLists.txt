cmake_minimum_required(VERSION 2.8.3)
project(dispatcher_app)

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
  LIBRARIES dispatcher_receiver dispatcher_receiver_app_node dispatcher_sender dispatcher_sender_app_node
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

#Dispatcher Receiver Library
add_library(dispatcher_receiver src/DispatcherReceiver.cpp src/DispatcherConfiguration.cpp )
target_link_libraries(dispatcher_receiver ${catkin_LIBRARIES} 
                                                  ${coros_kb_LIBRARIES})


#Dispatcher Receiver App
add_executable(dispatcher_receiver_app_node src/dispatcher_receiver_app.cpp)
target_link_libraries(dispatcher_receiver_app_node ${catkin_LIBRARIES}
                                                ${coros_common_LIBRARIES}
                                                ${coros_messages_LIBRARIES}
                                                ${coros_communication_LIBRARIES}
                                                ${coros_kb_LIBRARIES}
                                                dispatcher_receiver)

add_dependencies(dispatcher_receiver_app_node ${catkin_EXPORTED_TARGETS})


#Dispatcher Sender Library
add_library(dispatcher_sender  src/DispatcherSender.cpp src/DispatcherConfiguration.cpp)
target_link_libraries(dispatcher_sender ${catkin_LIBRARIES} 
                                                  ${coros_communication_LIBRARIES})

#Discovery Operator App
add_executable(dispatcher_sender_app_node src/dispatcher_sender_app.cpp)
target_link_libraries(dispatcher_sender_app_node ${catkin_LIBRARIES}
                                                  ${coros_common_LIBRARIES}
                                                  ${coros_messages_LIBRARIES}
                                                  ${coros_communication_LIBRARIES}
                                                  ${coros_operator_LIBRARIES}
                                                  dispatcher_sender)

add_dependencies(dispatcher_sender_app_node ${catkin_EXPORTED_TARGETS})

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS dispatcher_receiver dispatcher_receiver_app_node dispatcher_sender dispatcher_sender_app_node
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

