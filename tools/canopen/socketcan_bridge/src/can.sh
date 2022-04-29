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


# 'cd ~/usafe && source install/setup.bash && cd ~/usafe/src/tools/canopen/socketcan_bridge/launch && roslaunch socketcan_bridge.launch'

# 'cd ~/usafe && source install/setup.bash && cd ~/usafe/src/tools/vehicle_bridge/launch && roslaunch vehicle_bridge.launch'