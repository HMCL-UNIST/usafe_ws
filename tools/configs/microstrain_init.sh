#!/bin/bash

set -e


docker run -it --rm --net=host --device=/dev/ttyACM0 -v /home/hmcl/usafe/src/tools/configs/microstrain_param.yaml:/home/user/microstrain_param.yaml microstrain/ros-microstrain_inertial_driver:ros params_file:=/home/user/microstrain_param.yaml
