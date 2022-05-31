#!/bin/bash
echo hmc2020 | sudo -S modprobe can
echo hmc2020 | sudo -S modprobe kvaser_usb
echo hmc2020 | sudo -S ip link set can0 type can bitrate 500000
echo hmc2020 | sudo -S ip link set can1 type can bitrate 500000
echo hmc2020 | sudo -S ifconfig can0 up
echo hmc2020 | sudo -S ifconfig can1 up

sleep 1;
source ~/.bashrc;

gnome-terminal -- bash -c "source ~/.bashrc; roscore; exec bash"
sleep 1;

terminator -l usafe
sleep 1;
gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; cd ~/usafe/src/tools/path_debug/launch; roslaunch path_debug.launch; exec bash"

# github token : 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
# rostopic echo --filter "m.id==771"  /a_can_h2l 
# rosbag record /bias_gyro /bias_acc /wheel_info /wheel_odom /pose_estimate /scc_info /imu/data /vehicle_status /fix /gnss_h_pose /heading_ned 

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; cd ~/usafe/src/tools/canopen/socketcan_bridge/launch; roslaunch socketcan_bridge.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; cd ~/usafe/src/tools/canopen/socketcan_bridge/launch; roslaunch socketcan_bridge2.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; cd ~/usafe/src/tools/vehicle_bridge/launch; roslaunch vehicle_bridge.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/KonaCurvefit; source ~/.bashrc; rosrun curvefitting_2020b curvefiing_2020b_node; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch tdr3000_driver main.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source ~/.bashrc; docker run -it --rm --net=host --device=/dev/ttyACM0 -v /home/hmcl/usafe/src/tools/configs/microstrain_param.yaml:/home/user/microstrain_param.yaml microstrain/ros-microstrain_inertial_driver:ros params_file:=/home/user/microstrain_param.yaml; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch fix2pose fix2pose.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch state_estimator WheelOdometry.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch map_loader map_loader.launch; exec bash"

# sleep 5;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch state_estimator stateEstimator.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "rosrun rviz rviz -d /home/hmcl/usafe/src/tools/configs/gnss_viz.rviz; exec bash"
