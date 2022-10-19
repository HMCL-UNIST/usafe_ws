cmake_minimum_required(VERSION 2.8.3)
project(v2x_msgs)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs hmcl_msgs genmsg message_generation)

add_message_files(
  DIRECTORY msg
  FILES 
  Item.msg
  Mission1.msg
  Mission1data.msg
  Mission1state.msg
  Mission2.msg
  Mission2data.msg
  PVD.msg
  Reply.msg
  Request.msg
  Route.msg
  Routedata.msg
  SPAT.msg
  SPATdata.msg
  )

generate_messages(DEPENDENCIES 
  std_msgs
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs message_runtime
)
