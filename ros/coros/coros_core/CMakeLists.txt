cmake_minimum_required(VERSION 2.8.3)
project(coros_core)

find_package(
  catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES coros_state
   CATKIN_DEPENDS roscpp
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

include_directories(include ${catkin_INCLUDE_DIRS})



# becarefull about: coros_core_generate_messages_cpp
#add_dependencies(coros_node coros_core_generate_messages_cpp)


#LaserScan
#add_library(laserscan_lib src/sensors/laserscan/LaserScan.cpp)
#target_link_libraries(laserscan_lib ${catkin_LIBRARIES})
#add_dependencies(laserscan_lib ${catkin_EXPORTED_TARGETS})
#target_link_libraries(laserscan_lib nav_lib)




############################# robot library ############################
#add_library(robot src/robot/Robot.cpp 
#                  src/robot/RobotClient.h
#                  src/robot/RobotServer.h
#                  src/robot/TurtlebotRobot.cpp)
#add_dependencies(robot robot_controller_generate_messages_cpp)
#target_link_libraries(robot ${catkin_LIBRARIES})
#add_dependencies(robot ${catkin_EXPORTED_TARGETS})
#target_link_libraries(robot core)
#target_link_libraries(robot utils)
#target_link_libraries(robot laserscan_lib)
#target_link_libraries(robot map_lib)
#target_link_libraries(robot occupancyGridMap_lib)

