# 2024 Competition - Autonomous Racing in KIAPI


Clone the repository and make workspace

```bash
cd ~
git clone --branch 2024_racing https://github.com/HMCL-UNIST/usafe_ws.git
cd ~/usafe_ws/
mkdir -p msg_ws/src ctrl_ws/src can_ws/src plan_ws/src mobileye_ws/src
mv msgs_pkg msg_ws/src
mv ctrl_pkg ctrl_ws/src
mv can_pkg/ can_ws/src
mv plan_pkg/ plan_ws/src
mv mobileye_pkg/ mobileye_ws/src

```

Build ROS messages

```bash
cd ~/usafe_ws/msg_ws/
catkin_make
source devel/setup.bash
```

Build Control Workspace

```bash
cd ~/usafe_ws/ctrl_ws/
catkin_make
source devel/setup.bash
```

Build CAN Workspace

```bash
cd ~/usafe_ws/can_ws/
catkin_make
source devel/setup.bash
```

Build Mobileye CAN Workspace

```bash
cd ~/usafe_ws/mobileye_ws/
catkin_make
source devel/setup.bash
```

Build Planner Workspace

```bash
cd ~/usafe_ws/plan_ws/
catkin_make
source devel/setup.bash
```

Build Localization Workspace

```bash
cd ~/usafe_ws/localization_pkg/
catkin_make
source devel/setup.bash
```

Build Detection Workspace

```bash
cd ~/usafe_ws/detection_pkg/
catkin_make
source devel/setup.bash
```

Launch CAN Bridge
```bash
cd ~/usafe_ws/can_ws/
source devel/setup.bash
roslaunch socketcan_bridge socketcan_bridge.launch 
```

Launch Mobileye CAN Bridge & Mobileye Module
```bash
cd ~/usafe_ws/mobileye_ws/
source devel/setup.bash
roslaunch socketcan_bridge socketcan_bridge.launch 
roslaunch mobileye mobileye.launch
```

Launch Planner Modules
```bash
cd ~/usafe_ws/plan_ws/
source devel/setup.bash
roslaunch map_loader map_loader.launch
roslaunch mission_planner mission_planner.launch 
roslaunch behavior_planner behavior_planner.launch 
roslaunch local_planner2 locals.launch 
roslaunch velocity_planner velocity_planner.launch 
```
Launch Controller Modules
```bash
cd ~/usafe_ws/ctrl_ws/
source devel/setup.bash
roslaunch pid servo_sim.launch 
roslaunch preview_ctrl preview_ctrl.launch 
```
Launch Localization Modules
```bash
cd ~/usafe_ws/localization_ws/
source devel/setup.bash
roslaunch fast_lio_localization localization_ouster64.launch 
```

Launch Detection Modules
```bash
cd ~/usafe_ws/detection_ws/
source devel/setup.bash
python3 test_ros.py --pt ../pt/livox_model_1.pt
roslaunch ultralytics_ros tracker.launch 
roslaunch yolo_lidar_fusion yolo_lidar_fusion.launch 
roslaunch imm_ukf_pda_track imm_ukf_pda_track.launch 
```

