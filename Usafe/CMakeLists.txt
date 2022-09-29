cmake_minimum_required(VERSION 3.0.2)
project(usafe)

find_package(GeographicLib REQUIRED)

# find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)

if(NOT EIGEN3_FOUND)
  # Fallback to cmake_modules
  find_package(cmake_modules REQUIRED)
  find_package(Eigen3 REQUIRED)
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
  v2x_msgs
  std_msgs
  hmcl_msgs
  tf  
  pcl_conversions
  pcl_ros
  lanelet2_core
  lanelet2_io
  lanelet2_maps
  lanelet2_projection
  lanelet2_routing
  lanelet2_traffic_rules
  lanelet2_validation
  mobileye_msgs
  dynamic_reconfigure
)
generate_dynamic_reconfigure_options(
     cfg/test.cfg
)
catkin_package( 
  CATKIN_DEPENDS 
  nav_msgs 
  roscpp 
  sensor_msgs 
  geometry_msgs 
  hmcl_msgs
  v2x_msgs
  std_msgs 
  tf  
  lanelet2_core
  lanelet2_io
  lanelet2_maps
  lanelet2_projection
  lanelet2_routing
  lanelet2_traffic_rules
  lanelet2_validation
  mobileye_msgs
  dynamic_reconfigure
  LIBRARIES
)

include_directories(
  include
  maps  
  ${dynamic_reconfigure_PACKAGE_PATH}/cmake/cfgbuild.cmake
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

add_executable(dynamic_reconfigure_node src/usafe.cpp
            src/tools/Amathutils.cpp             
            src/tools/debugger.cpp             
            src/tools/healthmonitoring.cpp             
            src/planner/route_planner.cpp
            src/planner/behaviour_planner.cpp
            src/planner/mission_state_machine.cpp
            src/planner/path_planner.cpp
            src/planner/planner_common.cpp
            src/planner/velocity_planner.cpp
            src/planner/racing_planner.cpp            
            src/planner/vehicle_model.cpp            
            src/controller/lat_ctrl.cpp            
            src/controller/lon_ctrl.cpp      
            src/perception/surrounding_environment.cpp                        
            src/perception/v2x.cpp
            src/perception/vehicle_state.cpp
            )
add_dependencies(dynamic_reconfigure_node ${PROJECT_NAME}_gencfg)
target_link_libraries(dynamic_reconfigure_node ${catkin_LIBRARIES})

SET(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

# add_library(${PROJECT_NAME}_lib 
#             src/Amathutils.cpp             
#             src/route_planner.cpp
#             src/mission_state_machine.cpp)

add_executable(usafe src/usafe.cpp
            src/tools/Amathutils.cpp             
            src/tools/debugger.cpp             
            src/tools/healthmonitoring.cpp             
            src/planner/route_planner.cpp
            src/planner/behaviour_planner.cpp
            src/planner/mission_state_machine.cpp
            src/planner/path_planner.cpp
            src/planner/planner_common.cpp
            src/planner/velocity_planner.cpp
            src/planner/racing_planner.cpp  
            src/planner/vehicle_model.cpp              
            src/controller/lat_ctrl.cpp            
            src/controller/lon_ctrl.cpp      
            src/perception/surrounding_environment.cpp                        
            src/perception/v2x.cpp
            src/perception/vehicle_state.cpp
            )
target_link_libraries(usafe ${catkin_LIBRARIES} ${GeographicLib_LIBRARY_DIRS}/libGeographic.so)
add_dependencies(usafe ${catkin_EXPORTED_TARGETS})






install(
  TARGETS
  usafe    
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