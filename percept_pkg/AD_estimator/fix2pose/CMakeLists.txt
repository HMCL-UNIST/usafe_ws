cmake_minimum_required(VERSION 3.0.2)
project(fix2pose)


find_package(GeographicLib REQUIRED)

# find_package(PCL REQUIRED)
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
  microstrain_inertial_msgs
  lanelet2_projection
)

catkin_package(
  CATKIN_DEPENDS lanelet2_projection nav_msgs roscpp sensor_msgs geometry_msgs std_msgs tf  
  LIBRARIES
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

SET(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

add_executable(fix2pose src/fix2pose.cpp)
target_link_libraries(fix2pose ${catkin_LIBRARIES} ${GeographicLib_LIBRARY_DIRS}/libGeographic.so)
add_dependencies(fix2pose ${catkin_EXPORTED_TARGETS})


install(
  TARGETS
  fix2pose    
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)

install(DIRECTORY maps/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/maps
)