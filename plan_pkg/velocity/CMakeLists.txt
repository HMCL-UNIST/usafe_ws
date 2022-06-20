cmake_minimum_required(VERSION 3.0.2)
project(velocity)

# find_package(PCL REQUIRED)


find_package(catkin REQUIRED COMPONENTS  
  nav_msgs  
  roscpp
  sensor_msgs
  geometry_msgs
  std_msgs
  hmcl_msgs
  autoware_msgs
  tf  
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
  tf 
  LIBRARIES
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

SET(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

add_executable(velocity_generator src/velocity_generator.cpp)
target_link_libraries(velocity_generator ${catkin_LIBRARIES})
add_dependencies(velocity_generator ${catkin_EXPORTED_TARGETS})

add_executable(acc_node src/acc_node.cpp)
target_link_libraries(acc_node ${catkin_LIBRARIES})
add_dependencies(acc_node ${catkin_EXPORTED_TARGETS})


install(
  TARGETS    
  acc_node 
  velocity_generator
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)