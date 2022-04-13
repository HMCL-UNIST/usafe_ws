cmake_minimum_required(VERSION 3.0.2)
project(vehicle_bridge)

find_package(Eigen3 REQUIRED)

if(NOT EIGEN3_FOUND)
  # Fallback to cmake_modules
  find_package(cmake_modules REQUIRED)
  find_package(Eigen REQUIRED)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
  set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})  # Not strictly necessary as Eigen is head only
  # Possibly map additional variables to the EIGEN3_ prefix.
else()
  set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif()

find_package(catkin REQUIRED COMPONENTS  
  nav_msgs  
  roscpp
  sensor_msgs
  geometry_msgs
  std_msgs
  tf  
  hmcl_msgs
  can_msgs
)

catkin_package(
  CATKIN_DEPENDS nav_msgs roscpp sensor_msgs geometry_msgs std_msgs hmcl_msgs tf  
  LIBRARIES
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

SET(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

add_executable(vehicle_bridge src/vehicle_bridge.cpp)
target_link_libraries(vehicle_bridge ${catkin_LIBRARIES})
add_dependencies(vehicle_bridge ${catkin_EXPORTED_TARGETS})


install(
  TARGETS
  vehicle_bridge    
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


