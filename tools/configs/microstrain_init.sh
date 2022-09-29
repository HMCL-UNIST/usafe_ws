#!/bin/bash

set -e


docker run -it --rm --net=host --device=/dev/ttyACM0 -v /home/hmcl/hj_ws/usafe_integrated_ws/src/tools/configs/ros_entrypoint.sh:/ros_entrypoint.sh -v /home/hmcl/hj_ws/usafe_integrated_ws/src/tools/configs/.bashrc:/home/.bashrc -v /home/hmcl/usafe/src/tools/configs/microstrain_param.yaml:/home/user/microstrain_param.yaml microstrain/ros-microstrain_inertial_driver:ros params_file:=/home/user/microstrain_param.yaml

# docker run -it --rm --net=host --device=/dev/ttyACM0 -v /home/hmcl/usafe/src/tools/configs/microstrain_param.yaml:/home/user/microstrain_param.yaml microstrain/ros-microstrain_inertial_driver:ros params_file:=/home/user/microstrain_param.yaml

-v /home/hmcl/hj_ws/usafe_integrated_ws/src/tools/configs/ros_entrypoint.sh:/ros_entrypoint.sh
