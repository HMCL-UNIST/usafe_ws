cmake_minimum_required(VERSION 3.0.2)
project(pcl_loader)

## Compile as C++17, supported in ROS Kinetic and newer
add_compile_options(-std=c++17 -O2)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  # dynamic_reconfigure
  pcl_conversions
  pcl_ros
  roscpp
  rospy
  sensor_msgs
)

# generate_dynamic_reconfigure_options(
#   cfg/LidarFilters.cfg
# )


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  # LIBRARIES lidar_lane_detector
#  CATKIN_DEPENDS nav_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  include
  ${catkin_INCLUDE_DIRS}
)

# add_executable(lidar_lane_detector src/lidar_segmentation.cpp src/main.cpp src/star_shaped_search.cpp 
#                           src/x_zero_method.cpp src/z_zero_method.cpp src/blind_spots.cpp)
add_executable(pcl_loader src/pcl_loader.cpp)
# add_dependencies(pcl_loader ${catkin_LIBRARIES})
target_link_libraries(pcl_loader ${catkin_LIBRARIES})


install(
  TARGETS
  pcl_loader  
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