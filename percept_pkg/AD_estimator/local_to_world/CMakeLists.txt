cmake_minimum_required(VERSION 3.0.2)
project(local_to_world)


find_package(GeographicLib REQUIRED)

find_package(PCL REQUIRED)
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
  pcl_conversions
  pcl_ros
)

catkin_package(
  CATKIN_DEPENDS nav_msgs roscpp sensor_msgs geometry_msgs std_msgs tf  
  LIBRARIES
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

SET(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

add_executable(local_to_world src/local_to_world.cpp)
target_link_libraries(local_to_world ${catkin_LIBRARIES} ${GeographicLib_LIBRARY_DIRS}/libGeographic.so)
add_dependencies(local_to_world ${catkin_EXPORTED_TARGETS})


install(
  TARGETS
    local_to_world    
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


