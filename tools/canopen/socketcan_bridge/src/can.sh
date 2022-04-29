#!/bin/sh
echo hmc2020 | sudo -S modprobe can
echo hmc2020 | sudo -S modprobe kvaser_usb
echo hmc2020 | sudo -S ip link set can0 type can bitrate 500000
echo hmc2020 | sudo -S ip link set can1 type can bitrate 500000
echo hmc2020 | sudo -S ifconfig can0 up
echo hmc2020 | sudo -S ifconfig can1 up

gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; cd ~/usafe/src/tools/canopen/socketcan_bridge/launch; roslaunch socketcan_bridge.launch; exec bash"

sleep 1;
gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; cd ~/usafe/src/tools/canopen/socketcan_bridge/launch; roslaunch socketcan_bridge2.launch; exec bash"

sleep 1;
gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; cd ~/usafe/src/tools/vehicle_bridge/launch; roslaunch vehicle_bridge.launch; exec bash"

sleep 1;
gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch tdr3000_driver main.launch; exec bash"

sleep 1;
gnome-terminal -- bash -c "cd ~/usafe; source ~/.bashrc; docker run -it --rm --net=host --device=/dev/ttyACM0 -v /home/hmcl/usafe/src/tools/configs/microstrain_param.yaml:/home/user/microstrain_param.yaml microstrain/ros-microstrain_inertial_driver:ros params_file:=/home/user/microstrain_param.yaml; exec bash"

sleep 1;
gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch fix2pose fix2pose.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch state_estimator state_estimator.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch state_estimator WheelOdometry.launch; exec bash"

# sleep 1;
# gnome-terminal -- bash -c "cd ~/usafe; source install/setup.bash; roslaunch map_loader map_loader.launch; exec bash"