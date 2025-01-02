cmake_minimum_required(VERSION 2.8.12)
project(yolo_lidar_fusion)

#find_package(autoware_build_flags REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  pcl_conversions
  pcl_ros
  roscpp
  tf
  autoware_msgs
  image_geometry
)

find_package(Qt5Core REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)
find_package(OpenMP)
find_package(Eigen3 QUIET)

set(UTILS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


if(NOT EIGEN3_FOUND)
  # Fallback to cmake_modules
  find_package(cmake_modules REQUIRED)
  find_package(Eigen REQUIRED)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
  set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})  # Not strictly necessary as Eigen is head only
else()
  set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif()

catkin_package(CATKIN_DEPENDS
  cv_bridge
  image_transport
  pcl_conversions
  pcl_ros
  # image_geometry
)

set(CMAKE_CXX_FLAGS "-O3 -g -Wall ${CMAKE_CXX_FLAGS}")

# Create the utils library
add_library(utils src/utils.cpp)

# Include directories for utils library
target_include_directories(utils PRIVATE
  include
  ${OpenCV_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

# Fusion node (yolo_lidar_fusion node)
add_executable(yolo_lidar_fusion
  # src/yolo_lidar_fusion_node.cpp 
  src/yolo_lidar_fusion.cpp
)

# Include directories for yolo_lidar_fusion
target_include_directories(yolo_lidar_fusion PRIVATE
  include
  ${OpenCV_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${UTILS_INCLUDE_DIR}
)

# Link libraries for yolo_lidar_fusion
target_link_libraries(yolo_lidar_fusion
  ${OpenCV_LIBRARIES}
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${Qt5Core_LIBRARIES}
  utils  # Link with utils library
)

# New yolo_lidar_fusion_rlb node configuration
add_executable(yolo_lidar_fusion_rlb
  # src/yolo_lidar_fusion_rlb_node.cpp
  src/yolo_lidar_fusion_rlb.cpp
)

# Include directories for yolo_lidar_fusion_rlb
target_include_directories(yolo_lidar_fusion_rlb PRIVATE
  include
  ${OpenCV_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${UTILS_INCLUDE_DIR}
)

# Link libraries for yolo_lidar_fusion_rlb
target_link_libraries(yolo_lidar_fusion_rlb
  ${OpenCV_LIBRARIES}
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${Qt5Core_LIBRARIES}
  utils  # Link with utils library
)

# New yolo_lidar_fusion_f node configuration
add_executable(yolo_lidar_fusion_f
  # src/yolo_lidar_fusion_f_node.cpp
  src/yolo_lidar_fusion_f.cpp
)

# Include directories for yolo_lidar_fusion_f
target_include_directories(yolo_lidar_fusion_f PRIVATE
  include
  ${OpenCV_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${UTILS_INCLUDE_DIR}
)

# Link libraries for yolo_lidar_fusion_f
target_link_libraries(yolo_lidar_fusion_f
  ${OpenCV_LIBRARIES}
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${Qt5Core_LIBRARIES}
  utils  # Link with utils library
)

# New yolo_lidar_fusion_rlbf node configuration
add_executable(yolo_lidar_fusion_rlbf
  # src/yolo_lidar_fusion_rlbf_node.cpp
  src/yolo_lidar_fusion_rlbf.cpp
)

# Include directories for yolo_lidar_fusion_rlbf
target_include_directories(yolo_lidar_fusion_rlbf PRIVATE
  include
  ${OpenCV_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${UTILS_INCLUDE_DIR}
)

# Link libraries for yolo_lidar_fusion_rlbf
target_link_libraries(yolo_lidar_fusion_rlbf
  ${OpenCV_LIBRARIES}
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${Qt5Core_LIBRARIES}
  utils  # Link with utils library
)
