cmake_minimum_required(VERSION 2.8.3)
project(path_planner)


find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  geometry_msgs
  message_generation
  roscpp
  std_msgs
  
  coros_common REQUIRED
)

find_package(PCL REQUIRED)

add_action_files(
  DIRECTORY action
  FILES GlobalPathPlannerActionMessage.action
)

generate_messages(
  DEPENDENCIES actionlib_msgs geometry_msgs std_msgs 
)

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES occupancyGridMap_lib map_lib
   CATKIN_DEPENDS actionlib_msgs actionlib roscpp geometry_msgs message_runtime std_msgs coros_common 
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${coros_common_INCLUDE_DIRS}
)

include_directories(
  ${PCL_INCLUDE_DIRS}
)

include_directories(include ${catkin_INCLUDE_DIRS})

#Occupancy Grid Map
add_library(occupancyGridMap_lib src/map/OccupancyGridMap.cpp)

#Map
add_library(map_lib src/map/Map.cpp)


################### global_planner_action_server_node ##################
add_executable(global_planner_action_server_node src/global_planner/global_planner_action/global_planner_action_server.cpp)
add_dependencies(global_planner_action_server_node path_planner_generate_messages_cpp)
target_link_libraries(global_planner_action_server_node ${catkin_LIBRARIES} ${coros_common_LIBRARIES})
add_dependencies(global_planner_action_server_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(global_planner_action_server_node occupancyGridMap_lib map_lib)


