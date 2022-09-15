; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude GPSCorrelationTimestampStamped.msg.html

(cl:defclass <GPSCorrelationTimestampStamped> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (gps_cor
    :reader gps_cor
    :initarg :gps_cor
    :type microstrain_inertial_msgs-msg:GPSCorrelationTimestamp
    :initform (cl:make-instance 'microstrain_inertial_msgs-msg:GPSCorrelationTimestamp)))
)

(cl:defclass GPSCorrelationTimestampStamped (<GPSCorrelationTimestampStamped>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GPSCorrelationTimestampStamped>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GPSCorrelationTimestampStamped)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<GPSCorrelationTimestampStamped> is deprecated: use microstrain_inertial_msgs-msg:GPSCorrelationTimestampStamped instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <GPSCorrelationTimestampStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:header-val is deprecated.  Use microstrain_inertial_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'gps_cor-val :lambda-list '(m))
(cl:defmethod gps_cor-val ((m <GPSCorrelationTimestampStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_cor-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_cor instead.")
  (gps_cor m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GPSCorrelationTimestampStamped>) ostream)
  "Serializes a message object of type '<GPSCorrelationTimestampStamped>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gps_cor) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GPSCorrelationTimestampStamped>) istream)
  "Deserializes a message object of type '<GPSCorrelationTimestampStamped>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gps_cor) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GPSCorrelationTimestampStamped>)))
  "Returns string type for a message object of type '<GPSCorrelationTimestampStamped>"
  "microstrain_inertial_msgs/GPSCorrelationTimestampStamped")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GPSCorrelationTimestampStamped)))
  "Returns string type for a message object of type 'GPSCorrelationTimestampStamped"
  "microstrain_inertial_msgs/GPSCorrelationTimestampStamped")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GPSCorrelationTimestampStamped>)))
  "Returns md5sum for a message object of type '<GPSCorrelationTimestampStamped>"
  "879558b5dd82252329a1da11593c6fee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GPSCorrelationTimestampStamped)))
  "Returns md5sum for a message object of type 'GPSCorrelationTimestampStamped"
  "879558b5dd82252329a1da11593c6fee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GPSCorrelationTimestampStamped>)))
  "Returns full string definition for message of type '<GPSCorrelationTimestampStamped>"
  (cl:format cl:nil "std_msgs/Header header~%GPSCorrelationTimestamp gps_cor~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: microstrain_inertial_msgs/GPSCorrelationTimestamp~%float64 gps_tow~%uint16 gps_week_number~%uint16 timestamp_flags~%uint16 TIMESTAMP_FLAG_PPS_GOOD      = 1  #0b001~%uint16 TIMESTAMP_FLAG_GPS_REFRESH   = 2  #0b010~%uint16 TIMESTAMP_FLAG_GPS_INITALIZED= 4  #0b100~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GPSCorrelationTimestampStamped)))
  "Returns full string definition for message of type 'GPSCorrelationTimestampStamped"
  (cl:format cl:nil "std_msgs/Header header~%GPSCorrelationTimestamp gps_cor~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: microstrain_inertial_msgs/GPSCorrelationTimestamp~%float64 gps_tow~%uint16 gps_week_number~%uint16 timestamp_flags~%uint16 TIMESTAMP_FLAG_PPS_GOOD      = 1  #0b001~%uint16 TIMESTAMP_FLAG_GPS_REFRESH   = 2  #0b010~%uint16 TIMESTAMP_FLAG_GPS_INITALIZED= 4  #0b100~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GPSCorrelationTimestampStamped>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gps_cor))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GPSCorrelationTimestampStamped>))
  "Converts a ROS message object to a list"
  (cl:list 'GPSCorrelationTimestampStamped
    (cl:cons ':header (header msg))
    (cl:cons ':gps_cor (gps_cor msg))
))
