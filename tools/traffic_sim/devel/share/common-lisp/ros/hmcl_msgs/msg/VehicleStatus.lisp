; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude VehicleStatus.msg.html

(cl:defclass <VehicleStatus> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (steering_info
    :reader steering_info
    :initarg :steering_info
    :type hmcl_msgs-msg:VehicleSteering
    :initform (cl:make-instance 'hmcl_msgs-msg:VehicleSteering))
   (scc_info
    :reader scc_info
    :initarg :scc_info
    :type hmcl_msgs-msg:VehicleSCC
    :initform (cl:make-instance 'hmcl_msgs-msg:VehicleSCC))
   (wheelspeed
    :reader wheelspeed
    :initarg :wheelspeed
    :type hmcl_msgs-msg:VehicleWheelSpeed
    :initform (cl:make-instance 'hmcl_msgs-msg:VehicleWheelSpeed))
   (gear_info
    :reader gear_info
    :initarg :gear_info
    :type hmcl_msgs-msg:VehicleGear
    :initform (cl:make-instance 'hmcl_msgs-msg:VehicleGear))
   (light_info
    :reader light_info
    :initarg :light_info
    :type hmcl_msgs-msg:VehicleLight
    :initform (cl:make-instance 'hmcl_msgs-msg:VehicleLight))
   (remote_button_info
    :reader remote_button_info
    :initarg :remote_button_info
    :type hmcl_msgs-msg:RemoteButton
    :initform (cl:make-instance 'hmcl_msgs-msg:RemoteButton))
   (auto_mode
    :reader auto_mode
    :initarg :auto_mode
    :type cl:fixnum
    :initform 0)
   (ems_mode
    :reader ems_mode
    :initarg :ems_mode
    :type cl:fixnum
    :initform 0)
   (x_acceleration
    :reader x_acceleration
    :initarg :x_acceleration
    :type cl:float
    :initform 0.0)
   (y_acceleration
    :reader y_acceleration
    :initarg :y_acceleration
    :type cl:float
    :initform 0.0)
   (yaw_rate
    :reader yaw_rate
    :initarg :yaw_rate
    :type cl:float
    :initform 0.0))
)

(cl:defclass VehicleStatus (<VehicleStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<VehicleStatus> is deprecated: use hmcl_msgs-msg:VehicleStatus instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:header-val is deprecated.  Use hmcl_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'steering_info-val :lambda-list '(m))
(cl:defmethod steering_info-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:steering_info-val is deprecated.  Use hmcl_msgs-msg:steering_info instead.")
  (steering_info m))

(cl:ensure-generic-function 'scc_info-val :lambda-list '(m))
(cl:defmethod scc_info-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:scc_info-val is deprecated.  Use hmcl_msgs-msg:scc_info instead.")
  (scc_info m))

(cl:ensure-generic-function 'wheelspeed-val :lambda-list '(m))
(cl:defmethod wheelspeed-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:wheelspeed-val is deprecated.  Use hmcl_msgs-msg:wheelspeed instead.")
  (wheelspeed m))

(cl:ensure-generic-function 'gear_info-val :lambda-list '(m))
(cl:defmethod gear_info-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:gear_info-val is deprecated.  Use hmcl_msgs-msg:gear_info instead.")
  (gear_info m))

(cl:ensure-generic-function 'light_info-val :lambda-list '(m))
(cl:defmethod light_info-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:light_info-val is deprecated.  Use hmcl_msgs-msg:light_info instead.")
  (light_info m))

(cl:ensure-generic-function 'remote_button_info-val :lambda-list '(m))
(cl:defmethod remote_button_info-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:remote_button_info-val is deprecated.  Use hmcl_msgs-msg:remote_button_info instead.")
  (remote_button_info m))

(cl:ensure-generic-function 'auto_mode-val :lambda-list '(m))
(cl:defmethod auto_mode-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:auto_mode-val is deprecated.  Use hmcl_msgs-msg:auto_mode instead.")
  (auto_mode m))

(cl:ensure-generic-function 'ems_mode-val :lambda-list '(m))
(cl:defmethod ems_mode-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:ems_mode-val is deprecated.  Use hmcl_msgs-msg:ems_mode instead.")
  (ems_mode m))

(cl:ensure-generic-function 'x_acceleration-val :lambda-list '(m))
(cl:defmethod x_acceleration-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:x_acceleration-val is deprecated.  Use hmcl_msgs-msg:x_acceleration instead.")
  (x_acceleration m))

(cl:ensure-generic-function 'y_acceleration-val :lambda-list '(m))
(cl:defmethod y_acceleration-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:y_acceleration-val is deprecated.  Use hmcl_msgs-msg:y_acceleration instead.")
  (y_acceleration m))

(cl:ensure-generic-function 'yaw_rate-val :lambda-list '(m))
(cl:defmethod yaw_rate-val ((m <VehicleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:yaw_rate-val is deprecated.  Use hmcl_msgs-msg:yaw_rate instead.")
  (yaw_rate m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleStatus>) ostream)
  "Serializes a message object of type '<VehicleStatus>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'steering_info) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'scc_info) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'wheelspeed) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gear_info) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'light_info) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'remote_button_info) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ems_mode)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x_acceleration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y_acceleration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'yaw_rate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleStatus>) istream)
  "Deserializes a message object of type '<VehicleStatus>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'steering_info) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'scc_info) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'wheelspeed) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gear_info) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'light_info) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'remote_button_info) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ems_mode)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x_acceleration) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y_acceleration) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_rate) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleStatus>)))
  "Returns string type for a message object of type '<VehicleStatus>"
  "hmcl_msgs/VehicleStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleStatus)))
  "Returns string type for a message object of type 'VehicleStatus"
  "hmcl_msgs/VehicleStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleStatus>)))
  "Returns md5sum for a message object of type '<VehicleStatus>"
  "257eaa74ca2595e01127664962d58d27")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleStatus)))
  "Returns md5sum for a message object of type 'VehicleStatus"
  "257eaa74ca2595e01127664962d58d27")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleStatus>)))
  "Returns full string definition for message of type '<VehicleStatus>"
  (cl:format cl:nil "Header header~%hmcl_msgs/VehicleSteering steering_info~%hmcl_msgs/VehicleSCC scc_info~%hmcl_msgs/VehicleWheelSpeed wheelspeed~%hmcl_msgs/VehicleGear gear_info~%hmcl_msgs/VehicleLight light_info~%hmcl_msgs/RemoteButton remote_button_info~%# auto mode -> 0  off~%# auto mode -> 1  on~%uint8 auto_mode ~%# ems mode -> 0  off~%# ems mode -> 1  on~%uint8 ems_mode ~%float64 x_acceleration~%float64 y_acceleration~%float64 yaw_rate~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hmcl_msgs/VehicleSteering~%Header header~%# steering takeover -> off       = 0~%# steering takeover -> on      = 1~%uint8 takeover~%# steering mode -> off       = 0~%# steering mode -> on      = 1~%uint8 mode~%float32 steering_angle~%================================================================================~%MSG: hmcl_msgs/VehicleSCC~%Header header~%# sccmode -> off       = 0~%# sccmode -> ready       = 1~%# sccmode -> on       = 2~%uint8 scc_mode~%# scc takeover -> off       = 0~%# scc takeover -> n      = 1~%uint8 scc_takeover~%float64 acceleration~%================================================================================~%MSG: hmcl_msgs/VehicleWheelSpeed~%Header header~%float64 wheel_speed~%float64 fr~%float64 fl~%float64 rr~%float64 rl~%================================================================================~%MSG: hmcl_msgs/VehicleGear~%# Gear -> P       = 1~%# Gear -> D       = 2~%# Gear -> N       = 3~%# Gear -> R       = 4~%uint8 gear~%~%================================================================================~%MSG: hmcl_msgs/VehicleLight~%# 0 off, 1 on ~%uint8 left_light~%uint8 right_light~%uint8 hazard_light~%================================================================================~%MSG: hmcl_msgs/RemoteButton~%# wirelessbutton -> 0 push off, 1 -> push on~%uint8 button1~%uint8 button2~%uint8 button3~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleStatus)))
  "Returns full string definition for message of type 'VehicleStatus"
  (cl:format cl:nil "Header header~%hmcl_msgs/VehicleSteering steering_info~%hmcl_msgs/VehicleSCC scc_info~%hmcl_msgs/VehicleWheelSpeed wheelspeed~%hmcl_msgs/VehicleGear gear_info~%hmcl_msgs/VehicleLight light_info~%hmcl_msgs/RemoteButton remote_button_info~%# auto mode -> 0  off~%# auto mode -> 1  on~%uint8 auto_mode ~%# ems mode -> 0  off~%# ems mode -> 1  on~%uint8 ems_mode ~%float64 x_acceleration~%float64 y_acceleration~%float64 yaw_rate~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hmcl_msgs/VehicleSteering~%Header header~%# steering takeover -> off       = 0~%# steering takeover -> on      = 1~%uint8 takeover~%# steering mode -> off       = 0~%# steering mode -> on      = 1~%uint8 mode~%float32 steering_angle~%================================================================================~%MSG: hmcl_msgs/VehicleSCC~%Header header~%# sccmode -> off       = 0~%# sccmode -> ready       = 1~%# sccmode -> on       = 2~%uint8 scc_mode~%# scc takeover -> off       = 0~%# scc takeover -> n      = 1~%uint8 scc_takeover~%float64 acceleration~%================================================================================~%MSG: hmcl_msgs/VehicleWheelSpeed~%Header header~%float64 wheel_speed~%float64 fr~%float64 fl~%float64 rr~%float64 rl~%================================================================================~%MSG: hmcl_msgs/VehicleGear~%# Gear -> P       = 1~%# Gear -> D       = 2~%# Gear -> N       = 3~%# Gear -> R       = 4~%uint8 gear~%~%================================================================================~%MSG: hmcl_msgs/VehicleLight~%# 0 off, 1 on ~%uint8 left_light~%uint8 right_light~%uint8 hazard_light~%================================================================================~%MSG: hmcl_msgs/RemoteButton~%# wirelessbutton -> 0 push off, 1 -> push on~%uint8 button1~%uint8 button2~%uint8 button3~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleStatus>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'steering_info))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'scc_info))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'wheelspeed))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gear_info))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'light_info))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'remote_button_info))
     1
     1
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleStatus
    (cl:cons ':header (header msg))
    (cl:cons ':steering_info (steering_info msg))
    (cl:cons ':scc_info (scc_info msg))
    (cl:cons ':wheelspeed (wheelspeed msg))
    (cl:cons ':gear_info (gear_info msg))
    (cl:cons ':light_info (light_info msg))
    (cl:cons ':remote_button_info (remote_button_info msg))
    (cl:cons ':auto_mode (auto_mode msg))
    (cl:cons ':ems_mode (ems_mode msg))
    (cl:cons ':x_acceleration (x_acceleration msg))
    (cl:cons ':y_acceleration (y_acceleration msg))
    (cl:cons ':yaw_rate (yaw_rate msg))
))
