cmake_minimum_required(VERSION 2.8.12)

project(costmap_generator)


find_package(catkin REQUIRED COMPONENTS
  autoware_msgs
  grid_map_ros
  object_map
  pcl_ros
  roscpp
  tf  
  lanelet2_extension
)

catkin_package()

set(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(
  costmap_generator_lanelet2
  nodes/costmap_generator/costmap_generator_lanelet2_node.cpp
  nodes/costmap_generator/costmap_generator_lanelet2.cpp
  nodes/costmap_generator/points_to_costmap.cpp
  nodes/costmap_generator/objects_to_costmap.cpp
)

target_link_libraries(
  costmap_generator_lanelet2
  ${catkin_LIBRARIES}
)

add_dependencies(
  costmap_generator_lanelet2
  ${catkin_EXPORTED_TARGETS}
)

install(
  TARGETS 
    costmap_generator_lanelet2
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
