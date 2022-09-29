set -e
export ROS_MASTER_URI="http://192.168.10.118:11311/" 
export ROS_IP=192.168.10.118
export ROS_HOSTNAME=$ROS_IP
# setup ros environment
export ROS_MASTER_URI="http://192.168.10.118:11311/" 
export ROS_IP=192.168.10.118
export ROS_HOSTNAME=$ROS_IP
source "/opt/ros/$ROS_DISTRO/setup.bash"
export ROS_MASTER_URI="http://192.168.10.118:11311/" 
export ROS_IP=192.168.10.118
export ROS_HOSTNAME=$ROS_IP
exec "$@"
export ROS_MASTER_URI="http://192.168.10.118:11311/" 
export ROS_IP=192.168.10.118
export ROS_HOSTNAME=$ROS_IP
