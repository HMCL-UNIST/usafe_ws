cmake_minimum_required(VERSION 3.0.2)
project(hmcl_v2x)

find_package(catkin REQUIRED COMPONENTS 
  roscpp
  std_msgs
  nav_msgs
  sensor_msgs
  autoware_msgs
  hmcl_msgs
  v2x_msgs
)

catkin_package(
  CATKIN_DEPENDS 
  roscpp
  std_msgs
  nav_msgs
  sensor_msgs
  autoware_msgs
  hmcl_msgs
  v2x_msgs
  LIBRARIES
)

include_directories(
 include
 src/asn
 src/j2735
 ${catkin_INCLUDE_DIRS}
)

set(EXCLUDE_PATHS
    "CMakeFiles"
    include
    /opt/ros/melodic
)

file(GLOB_RECURSE SRC "*.c")
foreach(TMP_PATH ${SRC})
    foreach(EXCLUDE_PATH ${EXCLUDE_PATHS})
        string(FIND ${TMP_PATH} ${EXCLUDE_PATH} RESULT)
        if(NOT ${RESULT} EQUAL -1)
            list(REMOVE_ITEM SRC ${TMP_PATH})
        endif()
    endforeach(EXCLUDE_PATH)
endforeach(TMP_PATH)

message("${SRC}")


#target_link_libraries(tmp ${catkin_LIBRARIES}) # Libraries Link: 

INCLUDE_DIRECTORIES(v2x include)

add_executable(spat_pub 
${SRC}
src/v2x_info.cpp
src/pvd.cpp
)
target_link_libraries(spat_pub ${catkin_LIBRARIES})

add_executable(spat_pubs
${SRC}
src/v2x_spat.cpp
)
target_link_libraries(spat_pubs ${catkin_LIBRARIES})

add_executable(pvd_pubs
${SRC}
src/v2x_pvd_test.cpp
src/pvd.cpp
)
target_link_libraries(pvd_pubs ${catkin_LIBRARIES})

add_executable(pvd_pub 
${SRC}
src/v2x_pvd.cpp
)
target_link_libraries(pvd_pub ${catkin_LIBRARIES})

add_executable(mission_pub 
${SRC}
src/v2x_mission.cpp
)
target_link_libraries(mission_pub ${catkin_LIBRARIES})


add_executable(viz_pub 
${SRC}
src/v2x_viz.cpp
)
target_link_libraries(mission_pub ${catkin_LIBRARIES})


install(
  TARGETS    
  mission_pub
  spat_pub
  pvd_pub
  spat_pubs
  pvd_pubs
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)
