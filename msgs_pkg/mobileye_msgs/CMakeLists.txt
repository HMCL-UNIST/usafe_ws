cmake_minimum_required(VERSION 2.8.3)
project(mobileye_msgs)

find_package(catkin REQUIRED COMPONENTS std_msgs message_generation)

add_message_files(
  FILES
  first_msg.msg
  LKAlane.msg
  ReferencePoints.msg
  LKA.msg
  Lane.msg
  ObstacleStatus.msg
  ObstacleData.msg
  CarInfo.msg
  Gyro.msg
  SystemWarnings.msg
  TSR.msg
  TSRVisionOnlySign.msg
  ExtLogData.msg
  SmartADAS.msg
  SeeQ.msg
  StandardCAN.msg
  MobileyeInfo.msg
  MobileyeInfo_left.msg
  MobileyeInfo_right.msg
  MobileyeInfo_referencepoints.msg
  MobileyeInfo_number_of_next_lane_markers.msg
  MobileyeInfo_lane.msg
  MobileyeInfo_obstacle.msg
  MobileyeInfo_system_warnings.msg
  MobileyeInfo_car_info.msg
  MobileyeInfo_tsr.msg
  MobileyeInfo_gryo.msg
  MobileyeInfo_smart_adas.msg
  MobileyeInfo_seeq.msg
  
#   Message1.msg
#   Message2.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(CATKIN_DEPENDS std_msgs message_runtime)

install(FILES LICENSE.txt
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
