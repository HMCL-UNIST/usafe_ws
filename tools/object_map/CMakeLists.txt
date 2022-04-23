cmake_minimum_required(VERSION 2.8.12)

project(object_map)


find_package(catkin REQUIRED COMPONENTS
  autoware_msgs
  grid_map_cv
  grid_map_msgs
  grid_map_ros
  lanelet2_extension
  nav_msgs
  pcl_conversions
  pcl_ros
  roscpp
  roslint
  sensor_msgs
  tf
)

# TODO add other files into roslint
set(ROSLINT_CPP_OPTS "--filter=-build/c++14")

find_package(Qt5Core REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)
find_package(OpenMP)

if (OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES object_map_utils_lib
  CATKIN_DEPENDS
    pcl_ros
    pcl_conversions
    tf
    sensor_msgs
    nav_msgs
    autoware_msgs
    grid_map_msgs
    lanelet2_extension
)

set(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
### object_map_utils ###
add_library(object_map_utils_lib
  include/object_map/object_map_utils.cpp
  include/object_map/object_map_utils.hpp
)
target_link_libraries(object_map_utils_lib
  ${catkin_LIBRARIES}
)

install(
  TARGETS
    object_map_utils_lib
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)
        
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.hpp"
)

install(DIRECTORY config/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
)

if (CATKIN_ENABLE_TESTING)
  roslint_add_test()
endif()
