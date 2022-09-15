; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude ExtLogData.msg.html

(cl:defclass <ExtLogData> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (lane
    :reader lane
    :initarg :lane
    :type mobileye_msgs-msg:Lane
    :initform (cl:make-instance 'mobileye_msgs-msg:Lane))
   (obstacle_status
    :reader obstacle_status
    :initarg :obstacle_status
    :type mobileye_msgs-msg:ObstacleStatus
    :initform (cl:make-instance 'mobileye_msgs-msg:ObstacleStatus))
   (obstacle_data
    :reader obstacle_data
    :initarg :obstacle_data
    :type (cl:vector mobileye_msgs-msg:ObstacleData)
   :initform (cl:make-array 0 :element-type 'mobileye_msgs-msg:ObstacleData :initial-element (cl:make-instance 'mobileye_msgs-msg:ObstacleData))))
)

(cl:defclass ExtLogData (<ExtLogData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ExtLogData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ExtLogData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<ExtLogData> is deprecated: use mobileye_msgs-msg:ExtLogData instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ExtLogData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'lane-val :lambda-list '(m))
(cl:defmethod lane-val ((m <ExtLogData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:lane-val is deprecated.  Use mobileye_msgs-msg:lane instead.")
  (lane m))

(cl:ensure-generic-function 'obstacle_status-val :lambda-list '(m))
(cl:defmethod obstacle_status-val ((m <ExtLogData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_status-val is deprecated.  Use mobileye_msgs-msg:obstacle_status instead.")
  (obstacle_status m))

(cl:ensure-generic-function 'obstacle_data-val :lambda-list '(m))
(cl:defmethod obstacle_data-val ((m <ExtLogData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_data-val is deprecated.  Use mobileye_msgs-msg:obstacle_data instead.")
  (obstacle_data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ExtLogData>) ostream)
  "Serializes a message object of type '<ExtLogData>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'lane) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'obstacle_status) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'obstacle_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'obstacle_data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ExtLogData>) istream)
  "Deserializes a message object of type '<ExtLogData>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'lane) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'obstacle_status) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'obstacle_data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'obstacle_data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'mobileye_msgs-msg:ObstacleData))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ExtLogData>)))
  "Returns string type for a message object of type '<ExtLogData>"
  "mobileye_msgs/ExtLogData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ExtLogData)))
  "Returns string type for a message object of type 'ExtLogData"
  "mobileye_msgs/ExtLogData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ExtLogData>)))
  "Returns md5sum for a message object of type '<ExtLogData>"
  "bd5a83cb9f73511e0698020e5d37d36e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ExtLogData)))
  "Returns md5sum for a message object of type 'ExtLogData"
  "bd5a83cb9f73511e0698020e5d37d36e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ExtLogData>)))
  "Returns full string definition for message of type '<ExtLogData>"
  (cl:format cl:nil "Header header~%~%Lane lane~%~%ObstacleStatus obstacle_status~%ObstacleData[] obstacle_data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/Lane~%float32 lane_curvature~%float32 lane_heading~%~%bool ca~%float32 pitch_angle~%float32 yaw_angle~%~%bool right_ldw_availability~%bool left_ldw_availability~%~%================================================================================~%MSG: mobileye_msgs/ObstacleStatus~%uint8 number_of_obstacles~%uint8 timestamp~%~%bool left_close_rang_cut_in~%bool right_close_rang_cut_in~%~%uint8 go~%bool close_car~%uint8 failsafe~%~%================================================================================~%MSG: mobileye_msgs/ObstacleData~%uint8 obstacle_id~%float32 obstacle_position_x~%float32 obstacle_position_y~%float32 obstacle_relative_velocity_x~%~%uint8 obstacle_type~%uint8 obstacle_status~%bool obstacle_brake_lights~%uint8 cut_in_and_out~%uint8 blinker_info~%uint8 obstacle_valid~%~%float32 obstacle_length~%float32 obstacle_width~%uint8 obstacle_age~%uint8 obstacle_lane~%uint8 cipv_flag~%~%float32 radar_position_x~%float32 radar_velocity_x~%uint8 radar_match_confidence~%uint8 matched_radar_id~%~%float32 obstacle_angle_rate~%float32 obstacle_scale_change~%float32 obstacle_object_accel_x~%bool obstacle_replaced~%float32 obstacle_angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ExtLogData)))
  "Returns full string definition for message of type 'ExtLogData"
  (cl:format cl:nil "Header header~%~%Lane lane~%~%ObstacleStatus obstacle_status~%ObstacleData[] obstacle_data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/Lane~%float32 lane_curvature~%float32 lane_heading~%~%bool ca~%float32 pitch_angle~%float32 yaw_angle~%~%bool right_ldw_availability~%bool left_ldw_availability~%~%================================================================================~%MSG: mobileye_msgs/ObstacleStatus~%uint8 number_of_obstacles~%uint8 timestamp~%~%bool left_close_rang_cut_in~%bool right_close_rang_cut_in~%~%uint8 go~%bool close_car~%uint8 failsafe~%~%================================================================================~%MSG: mobileye_msgs/ObstacleData~%uint8 obstacle_id~%float32 obstacle_position_x~%float32 obstacle_position_y~%float32 obstacle_relative_velocity_x~%~%uint8 obstacle_type~%uint8 obstacle_status~%bool obstacle_brake_lights~%uint8 cut_in_and_out~%uint8 blinker_info~%uint8 obstacle_valid~%~%float32 obstacle_length~%float32 obstacle_width~%uint8 obstacle_age~%uint8 obstacle_lane~%uint8 cipv_flag~%~%float32 radar_position_x~%float32 radar_velocity_x~%uint8 radar_match_confidence~%uint8 matched_radar_id~%~%float32 obstacle_angle_rate~%float32 obstacle_scale_change~%float32 obstacle_object_accel_x~%bool obstacle_replaced~%float32 obstacle_angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ExtLogData>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'lane))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'obstacle_status))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'obstacle_data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ExtLogData>))
  "Converts a ROS message object to a list"
  (cl:list 'ExtLogData
    (cl:cons ':header (header msg))
    (cl:cons ':lane (lane msg))
    (cl:cons ':obstacle_status (obstacle_status msg))
    (cl:cons ':obstacle_data (obstacle_data msg))
))
