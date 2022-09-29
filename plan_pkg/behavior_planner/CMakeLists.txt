cmake_minimum_required(VERSION 3.0.2)
project(behavior_planner)

# find_package(PCL REQUIRED)


find_package(catkin REQUIRED COMPONENTS  
  nav_msgs  
  roscpp
  sensor_msgs
  geometry_msgs
  std_msgs
  hmcl_msgs
  autoware_msgs
  v2x_msgs
)

catkin_package(
  CATKIN_DEPENDS 
  nav_msgs 
  roscpp 
  sensor_msgs 
  geometry_msgs 
  hmcl_msgs
  std_msgs
  autoware_msgs
  v2x_msgs
  LIBRARIES
)


include_directories(
  include
  # ${dynamic_reconfigure_PACKAGE_PATH}/cmake/cfgbuild.cmake
  ${catkin_INCLUDE_DIRS}
  # ${EIGEN3_INCLUDE_DIRS}
)



#add_executable(dynamic_reconfigure_node src/acc_node.cpp)
#add_dependencies(dynamic_reconfigure_node ${PROJECT_NAME}_gencfg)
#target_link_libraries(dynamic_reconfigure_node ${catkin_LIBRARIES})
#SET(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

add_executable(behavior_planner src/behavior_planner.cpp)
target_link_libraries(behavior_planner ${catkin_LIBRARIES})
add_dependencies(behavior_planner ${catkin_EXPORTED_TARGETS})



install(
  TARGETS    
  behavior_planner
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)
