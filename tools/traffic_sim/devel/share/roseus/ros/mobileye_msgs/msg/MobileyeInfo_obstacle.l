;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_obstacle)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_obstacle (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_OBSTACLE")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_OBSTACLE"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_obstacle.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_obstacle
  :super ros::object
  :slots (_header _obstacle_status _obstacle_data ))

(defmethod mobileye_msgs::MobileyeInfo_obstacle
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:obstacle_status __obstacle_status) (instance mobileye_msgs::ObstacleStatus :init))
    ((:obstacle_data __obstacle_data) (let (r) (dotimes (i 0) (push (instance mobileye_msgs::ObstacleData :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _obstacle_status __obstacle_status)
   (setq _obstacle_data __obstacle_data)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:obstacle_status
   (&rest __obstacle_status)
   (if (keywordp (car __obstacle_status))
       (send* _obstacle_status __obstacle_status)
     (progn
       (if __obstacle_status (setq _obstacle_status (car __obstacle_status)))
       _obstacle_status)))
  (:obstacle_data
   (&rest __obstacle_data)
   (if (keywordp (car __obstacle_data))
       (send* _obstacle_data __obstacle_data)
     (progn
       (if __obstacle_data (setq _obstacle_data (car __obstacle_data)))
       _obstacle_data)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/ObstacleStatus _obstacle_status
    (send _obstacle_status :serialization-length)
    ;; mobileye_msgs/ObstacleData[] _obstacle_data
    (apply #'+ (send-all _obstacle_data :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/ObstacleStatus _obstacle_status
       (send _obstacle_status :serialize s)
     ;; mobileye_msgs/ObstacleData[] _obstacle_data
     (write-long (length _obstacle_data) s)
     (dolist (elem _obstacle_data)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/ObstacleStatus _obstacle_status
     (send _obstacle_status :deserialize buf ptr-) (incf ptr- (send _obstacle_status :serialization-length))
   ;; mobileye_msgs/ObstacleData[] _obstacle_data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _obstacle_data (let (r) (dotimes (i n) (push (instance mobileye_msgs::ObstacleData :init) r)) r))
     (dolist (elem- _obstacle_data)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_obstacle :md5sum-) "121aed0c94d2bb3256eb91e8d451839e")
(setf (get mobileye_msgs::MobileyeInfo_obstacle :datatype-) "mobileye_msgs/MobileyeInfo_obstacle")
(setf (get mobileye_msgs::MobileyeInfo_obstacle :definition-)
      "Header header

ObstacleStatus obstacle_status
ObstacleData[] obstacle_data

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: mobileye_msgs/ObstacleStatus
uint8 number_of_obstacles
uint8 timestamp

bool left_close_rang_cut_in
bool right_close_rang_cut_in

uint8 go
bool close_car
uint8 failsafe

================================================================================
MSG: mobileye_msgs/ObstacleData
uint8 obstacle_id
float32 obstacle_position_x
float32 obstacle_position_y
float32 obstacle_relative_velocity_x

uint8 obstacle_type
uint8 obstacle_status
bool obstacle_brake_lights
uint8 cut_in_and_out
uint8 blinker_info
uint8 obstacle_valid

float32 obstacle_length
float32 obstacle_width
uint8 obstacle_age
uint8 obstacle_lane
uint8 cipv_flag

float32 radar_position_x
float32 radar_velocity_x
uint8 radar_match_confidence
uint8 matched_radar_id

float32 obstacle_angle_rate
float32 obstacle_scale_change
float32 obstacle_object_accel_x
bool obstacle_replaced
float32 obstacle_angle

")



(provide :mobileye_msgs/MobileyeInfo_obstacle "121aed0c94d2bb3256eb91e8d451839e")


