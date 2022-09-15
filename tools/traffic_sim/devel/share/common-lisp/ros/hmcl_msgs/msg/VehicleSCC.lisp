; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude VehicleSCC.msg.html

(cl:defclass <VehicleSCC> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (scc_mode
    :reader scc_mode
    :initarg :scc_mode
    :type cl:fixnum
    :initform 0)
   (scc_takeover
    :reader scc_takeover
    :initarg :scc_takeover
    :type cl:fixnum
    :initform 0)
   (acceleration
    :reader acceleration
    :initarg :acceleration
    :type cl:float
    :initform 0.0))
)

(cl:defclass VehicleSCC (<VehicleSCC>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleSCC>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleSCC)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<VehicleSCC> is deprecated: use hmcl_msgs-msg:VehicleSCC instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleSCC>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:header-val is deprecated.  Use hmcl_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'scc_mode-val :lambda-list '(m))
(cl:defmethod scc_mode-val ((m <VehicleSCC>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:scc_mode-val is deprecated.  Use hmcl_msgs-msg:scc_mode instead.")
  (scc_mode m))

(cl:ensure-generic-function 'scc_takeover-val :lambda-list '(m))
(cl:defmethod scc_takeover-val ((m <VehicleSCC>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:scc_takeover-val is deprecated.  Use hmcl_msgs-msg:scc_takeover instead.")
  (scc_takeover m))

(cl:ensure-generic-function 'acceleration-val :lambda-list '(m))
(cl:defmethod acceleration-val ((m <VehicleSCC>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:acceleration-val is deprecated.  Use hmcl_msgs-msg:acceleration instead.")
  (acceleration m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleSCC>) ostream)
  "Serializes a message object of type '<VehicleSCC>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'scc_mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'scc_takeover)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'acceleration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleSCC>) istream)
  "Deserializes a message object of type '<VehicleSCC>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'scc_mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'scc_takeover)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acceleration) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleSCC>)))
  "Returns string type for a message object of type '<VehicleSCC>"
  "hmcl_msgs/VehicleSCC")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleSCC)))
  "Returns string type for a message object of type 'VehicleSCC"
  "hmcl_msgs/VehicleSCC")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleSCC>)))
  "Returns md5sum for a message object of type '<VehicleSCC>"
  "0471adfa682d3742aa9adb20fb1e2600")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleSCC)))
  "Returns md5sum for a message object of type 'VehicleSCC"
  "0471adfa682d3742aa9adb20fb1e2600")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleSCC>)))
  "Returns full string definition for message of type '<VehicleSCC>"
  (cl:format cl:nil "Header header~%# sccmode -> off       = 0~%# sccmode -> ready       = 1~%# sccmode -> on       = 2~%uint8 scc_mode~%# scc takeover -> off       = 0~%# scc takeover -> n      = 1~%uint8 scc_takeover~%float64 acceleration~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleSCC)))
  "Returns full string definition for message of type 'VehicleSCC"
  (cl:format cl:nil "Header header~%# sccmode -> off       = 0~%# sccmode -> ready       = 1~%# sccmode -> on       = 2~%uint8 scc_mode~%# scc takeover -> off       = 0~%# scc takeover -> n      = 1~%uint8 scc_takeover~%float64 acceleration~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleSCC>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleSCC>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleSCC
    (cl:cons ':header (header msg))
    (cl:cons ':scc_mode (scc_mode msg))
    (cl:cons ':scc_takeover (scc_takeover msg))
    (cl:cons ':acceleration (acceleration msg))
))
