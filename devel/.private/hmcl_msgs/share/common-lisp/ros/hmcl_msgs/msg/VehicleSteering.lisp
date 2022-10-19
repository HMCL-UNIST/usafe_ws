; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude VehicleSteering.msg.html

(cl:defclass <VehicleSteering> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (takeover
    :reader takeover
    :initarg :takeover
    :type cl:fixnum
    :initform 0)
   (mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0)
   (steering_angle
    :reader steering_angle
    :initarg :steering_angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass VehicleSteering (<VehicleSteering>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleSteering>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleSteering)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<VehicleSteering> is deprecated: use hmcl_msgs-msg:VehicleSteering instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleSteering>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:header-val is deprecated.  Use hmcl_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'takeover-val :lambda-list '(m))
(cl:defmethod takeover-val ((m <VehicleSteering>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:takeover-val is deprecated.  Use hmcl_msgs-msg:takeover instead.")
  (takeover m))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <VehicleSteering>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:mode-val is deprecated.  Use hmcl_msgs-msg:mode instead.")
  (mode m))

(cl:ensure-generic-function 'steering_angle-val :lambda-list '(m))
(cl:defmethod steering_angle-val ((m <VehicleSteering>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:steering_angle-val is deprecated.  Use hmcl_msgs-msg:steering_angle instead.")
  (steering_angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleSteering>) ostream)
  "Serializes a message object of type '<VehicleSteering>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'takeover)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steering_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleSteering>) istream)
  "Deserializes a message object of type '<VehicleSteering>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'takeover)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering_angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleSteering>)))
  "Returns string type for a message object of type '<VehicleSteering>"
  "hmcl_msgs/VehicleSteering")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleSteering)))
  "Returns string type for a message object of type 'VehicleSteering"
  "hmcl_msgs/VehicleSteering")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleSteering>)))
  "Returns md5sum for a message object of type '<VehicleSteering>"
  "5fb428b383c979ad23048575d907b4bf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleSteering)))
  "Returns md5sum for a message object of type 'VehicleSteering"
  "5fb428b383c979ad23048575d907b4bf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleSteering>)))
  "Returns full string definition for message of type '<VehicleSteering>"
  (cl:format cl:nil "Header header~%# steering takeover -> off       = 0~%# steering takeover -> on      = 1~%uint8 takeover~%# steering mode -> off       = 0~%# steering mode -> on      = 1~%uint8 mode~%float32 steering_angle~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleSteering)))
  "Returns full string definition for message of type 'VehicleSteering"
  (cl:format cl:nil "Header header~%# steering takeover -> off       = 0~%# steering takeover -> on      = 1~%uint8 takeover~%# steering mode -> off       = 0~%# steering mode -> on      = 1~%uint8 mode~%float32 steering_angle~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleSteering>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleSteering>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleSteering
    (cl:cons ':header (header msg))
    (cl:cons ':takeover (takeover msg))
    (cl:cons ':mode (mode msg))
    (cl:cons ':steering_angle (steering_angle msg))
))
