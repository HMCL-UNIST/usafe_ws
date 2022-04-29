cmake_minimum_required(VERSION 3.5)
project(hmcl_msgs)
set(CMAKE_VERBOSE_MAKEFILE ON)
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  geometry_msgs
  sensor_msgs
  std_msgs
)
## System dependencies are found with CMake''s conventions
################################################
## Declare ROS messages, services and actions ##
################################################
add_message_files(
    FILES
    Lane.msg
    LaneArray.msg
    RemoteButton.msg
    Trafficlight.msg
    VehicleGear.msg
    VehicleLight.msg
    VehicleSCC.msg
    VehicleStatus.msg
    VehicleSteering.msg
    VehicleWheelSpeed.msg
    Waypoint.msg
)
add_service_files(
    FILES
    RecognizeLightState.srv
)
find_package( geometry_msgs REQUIRED)
find_package( roscpp REQUIRED)
find_package( sensor_msgs REQUIRED)
find_package( std_msgs REQUIRED)
## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  sensor_msgs
  std_msgs
)
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  CATKIN_DEPENDS
  "message_runtime"
  "geometry_msgs"
  "roscpp"
  "sensor_msgs"
  "std_msgs"
)
###########
## Build ##
###########
## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  include
  ${PROJECT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
 "/usr/local/MATLAB/R2020b/extern/include"
 "/usr/local/MATLAB/R2020b/extern/include/MatlabDataArray"
 "/usr/local/MATLAB/R2020b/toolbox/ros/include/ros1"
 "/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/include"
 "/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/console_bridge/include"
 "/usr/local/MATLAB/R2020b/toolbox/ros/mlroscpp/custom_messages/include"
 "/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/boost/include"
  "include/hmcl_msgs"
)
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
## Get list of .c files in project source directory
file(GLOB ${PROJECT_NAME}_C_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/*.c)
## Get list of .cpp files in project source directory
file(GLOB ${PROJECT_NAME}_CPP_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/*.cpp)
link_directories("/usr/local/MATLAB/R2020b/extern/bin/glnxa64")
link_directories("/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/console_bridge/lib")
link_directories("/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/lib")
link_directories("/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/boost/lib")
# Declare library
add_library(
    hmcl_msgs_matlab 
    SHARED
    src/hmcl_msgs_Lane_common.cpp
    src/hmcl_msgs_msg_Lane_publisher.cpp
    src/hmcl_msgs_msg_Lane_subscriber.cpp
    src/hmcl_msgs_LaneArray_common.cpp
    src/hmcl_msgs_msg_LaneArray_publisher.cpp
    src/hmcl_msgs_msg_LaneArray_subscriber.cpp
    src/hmcl_msgs_RemoteButton_common.cpp
    src/hmcl_msgs_msg_RemoteButton_publisher.cpp
    src/hmcl_msgs_msg_RemoteButton_subscriber.cpp
    src/hmcl_msgs_Trafficlight_common.cpp
    src/hmcl_msgs_msg_Trafficlight_publisher.cpp
    src/hmcl_msgs_msg_Trafficlight_subscriber.cpp
    src/hmcl_msgs_VehicleGear_common.cpp
    src/hmcl_msgs_msg_VehicleGear_publisher.cpp
    src/hmcl_msgs_msg_VehicleGear_subscriber.cpp
    src/hmcl_msgs_VehicleLight_common.cpp
    src/hmcl_msgs_msg_VehicleLight_publisher.cpp
    src/hmcl_msgs_msg_VehicleLight_subscriber.cpp
    src/hmcl_msgs_VehicleSCC_common.cpp
    src/hmcl_msgs_msg_VehicleSCC_publisher.cpp
    src/hmcl_msgs_msg_VehicleSCC_subscriber.cpp
    src/hmcl_msgs_VehicleStatus_common.cpp
    src/hmcl_msgs_msg_VehicleStatus_publisher.cpp
    src/hmcl_msgs_msg_VehicleStatus_subscriber.cpp
    src/hmcl_msgs_VehicleSteering_common.cpp
    src/hmcl_msgs_msg_VehicleSteering_publisher.cpp
    src/hmcl_msgs_msg_VehicleSteering_subscriber.cpp
    src/hmcl_msgs_VehicleWheelSpeed_common.cpp
    src/hmcl_msgs_msg_VehicleWheelSpeed_publisher.cpp
    src/hmcl_msgs_msg_VehicleWheelSpeed_subscriber.cpp
    src/hmcl_msgs_Waypoint_common.cpp
    src/hmcl_msgs_msg_Waypoint_publisher.cpp
    src/hmcl_msgs_msg_Waypoint_subscriber.cpp
    src/hmcl_msgs_RecognizeLightState_request_common.cpp
    src/hmcl_msgs_RecognizeLightState_response_common.cpp
    src/hmcl_msgs_srv_RecognizeLightState_client.cpp
    src/hmcl_msgs_srv_RecognizeLightState_server.cpp
    src/hmcl_msgs_msg_RecognizeLightStateRequest_publisher.cpp
    src/hmcl_msgs_msg_RecognizeLightStateRequest_subscriber.cpp
    src/hmcl_msgs_msg_RecognizeLightStateResponse_publisher.cpp
    src/hmcl_msgs_msg_RecognizeLightStateResponse_subscriber.cpp
    src/hmcl_msgs_RecognizeLightStateRequest_common.cpp
    src/hmcl_msgs_RecognizeLightStateResponse_common.cpp
)
target_include_directories(hmcl_msgs_matlab PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries( hmcl_msgs_matlab
	"/usr/local/MATLAB/R2020b/extern/bin/glnxa64/libMatlabDataArray.so"
	"/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/console_bridge/lib/libconsole_bridge.so"
	"/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/lib/libclass_loader.so"
	"/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/lib/librosconsole.so"
	"/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/lib/libroscpp.so"
	"/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/lib/libroscpp_serialization.so"
	"/usr/local/MATLAB/R2020b/sys/ros1/glnxa64/ros1/lib/librostime.so"
	${Boost_LIBRARIES}
	${CMAKE_DL_LIBS}
	)
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
add_dependencies(
  hmcl_msgs_matlab
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(hmcl_msgs_matlab PRIVATE "HMCL_MSGS_BUILDING_LIBRARY")
install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS hmcl_msgs_matlab
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install (DIRECTORY m/ DESTINATION m/ FILES_MATCHING PATTERN "*.m")
# Generated 28-Apr-2022 23:53:04
# Copyright 2019-2020 The MathWorks, Inc.
