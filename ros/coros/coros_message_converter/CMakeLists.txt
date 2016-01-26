cmake_minimum_required(VERSION 2.8.3)
project(coros_message_converter)

find_package(catkin REQUIRED COMPONENTS roscpp rospy rostest rospy_message_converter coros_messages)

catkin_package(CATKIN_DEPENDS roscpp rospy rostest rospy_message_converter coros_messages)

add_rostest(test/test_all.test)

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_coros_message_converter.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

###########
## Build ##
###########

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS coros_messages roscpp
)

include_directories(include
  ${catkin_INCLUDE_DIRS} 
)

