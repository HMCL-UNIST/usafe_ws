cmake_minimum_required(VERSION 2.8.3)
project(points_preprocessor)

find_package(autoware_build_flags REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  autoware_config_msgs
  autoware_health_checker
  pcl_conversions
  pcl_ros
  roscpp
  roslint
  sensor_msgs
  std_msgs
  tf
  tf2
  tf2_eigen
  tf2_ros
  velodyne_pointcloud
)

catkin_package()

find_package(Qt5Core REQUIRED)
find_package(PCL 1.7 REQUIRED)
find_package(OpenMP)

# Resolve system dependency on yaml-cpp, which apparently does not
# provide a CMake find_package() module.
find_package(PkgConfig REQUIRED)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)
find_path(YAML_CPP_INCLUDE_DIR NAMES yaml_cpp.h PATHS ${YAML_CPP_INCLUDE_DIRS})
find_library(YAML_CPP_LIBRARY NAMES YAML_CPP PATHS ${YAML_CPP_LIBRARY_DIRS})
link_directories(${YAML_CPP_LIBRARY_DIRS})

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

SET(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

link_directories(${PCL_LIBRARY_DIRS})

#Cloud Transformer
add_executable(cloud_transformer
  nodes/cloud_transformer/cloud_transformer_node.cpp
)

target_include_directories(cloud_transformer PRIVATE
  ${PCL_INCLUDE_DIRS}
)

target_link_libraries(cloud_transformer
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${Qt5Core_LIBRARIES}
)
add_dependencies(cloud_transformer ${catkin_EXPORTED_TARGETS})

#Compare Map Filter
add_executable(compare_map_filter
  nodes/compare_map_filter/compare_map_filter.cpp
)

target_include_directories(compare_map_filter PRIVATE
  ${PCL_INCLUDE_DIRS}
)

target_link_libraries(compare_map_filter
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${Qt5Core_LIBRARIES}
)
add_dependencies(compare_map_filter ${catkin_EXPORTED_TARGETS})

install(
  TARGETS
    cloud_transformer
    compare_map_filter
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  PATTERN ".svn" EXCLUDE
)

