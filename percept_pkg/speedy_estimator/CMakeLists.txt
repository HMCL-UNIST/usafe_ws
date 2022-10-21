cmake_minimum_required(VERSION 3.10)
project(speedy_estimator)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs  
  tf  
)

find_package(cmake_modules REQUIRED)

find_package(catkin REQUIRED)


catkin_package(
    DEPENDS
    CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs sensor_msgs nav_msgs
    INCLUDE_DIRS include
    LIBRARIES  
)

set(BUILD_FLAGS "-std=c++11 -Wuninitialized -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${BUILD_FLAGS}")

include_directories(SYSTEM ${catkin_INCLUDE_DIRS})
include_directories(include)
add_subdirectory(src/StateEstimator)



install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)