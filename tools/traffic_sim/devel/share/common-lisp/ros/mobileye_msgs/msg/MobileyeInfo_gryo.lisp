; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_gryo.msg.html

(cl:defclass <MobileyeInfo_gryo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (gyro
    :reader gyro
    :initarg :gyro
    :type mobileye_msgs-msg:Gyro
    :initform (cl:make-instance 'mobileye_msgs-msg:Gyro)))
)

(cl:defclass MobileyeInfo_gryo (<MobileyeInfo_gryo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_gryo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_gryo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_gryo> is deprecated: use mobileye_msgs-msg:MobileyeInfo_gryo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_gryo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'gyro-val :lambda-list '(m))
(cl:defmethod gyro-val ((m <MobileyeInfo_gryo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:gyro-val is deprecated.  Use mobileye_msgs-msg:gyro instead.")
  (gyro m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_gryo>) ostream)
  "Serializes a message object of type '<MobileyeInfo_gryo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gyro) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_gryo>) istream)
  "Deserializes a message object of type '<MobileyeInfo_gryo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gyro) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_gryo>)))
  "Returns string type for a message object of type '<MobileyeInfo_gryo>"
  "mobileye_msgs/MobileyeInfo_gryo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_gryo)))
  "Returns string type for a message object of type 'MobileyeInfo_gryo"
  "mobileye_msgs/MobileyeInfo_gryo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_gryo>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_gryo>"
  "bd2f1742b1504f840215de76070ae32a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_gryo)))
  "Returns md5sum for a message object of type 'MobileyeInfo_gryo"
  "bd2f1742b1504f840215de76070ae32a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_gryo>)))
  "Returns full string definition for message of type '<MobileyeInfo_gryo>"
  (cl:format cl:nil "Header header~%~%Gyro gyro~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/Gyro~%bool gyro_sensor_data_available~%float32 x_axis_data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_gryo)))
  "Returns full string definition for message of type 'MobileyeInfo_gryo"
  (cl:format cl:nil "Header header~%~%Gyro gyro~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/Gyro~%bool gyro_sensor_data_available~%float32 x_axis_data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_gryo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gyro))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_gryo>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_gryo
    (cl:cons ':header (header msg))
    (cl:cons ':gyro (gyro msg))
))
