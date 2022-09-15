; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_car_info.msg.html

(cl:defclass <MobileyeInfo_car_info> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (car_info
    :reader car_info
    :initarg :car_info
    :type mobileye_msgs-msg:CarInfo
    :initform (cl:make-instance 'mobileye_msgs-msg:CarInfo)))
)

(cl:defclass MobileyeInfo_car_info (<MobileyeInfo_car_info>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_car_info>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_car_info)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_car_info> is deprecated: use mobileye_msgs-msg:MobileyeInfo_car_info instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_car_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'car_info-val :lambda-list '(m))
(cl:defmethod car_info-val ((m <MobileyeInfo_car_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:car_info-val is deprecated.  Use mobileye_msgs-msg:car_info instead.")
  (car_info m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_car_info>) ostream)
  "Serializes a message object of type '<MobileyeInfo_car_info>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'car_info) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_car_info>) istream)
  "Deserializes a message object of type '<MobileyeInfo_car_info>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'car_info) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_car_info>)))
  "Returns string type for a message object of type '<MobileyeInfo_car_info>"
  "mobileye_msgs/MobileyeInfo_car_info")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_car_info)))
  "Returns string type for a message object of type 'MobileyeInfo_car_info"
  "mobileye_msgs/MobileyeInfo_car_info")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_car_info>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_car_info>"
  "9dfc1f88c8be2e512dbe7a4b8cea7bad")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_car_info)))
  "Returns md5sum for a message object of type 'MobileyeInfo_car_info"
  "9dfc1f88c8be2e512dbe7a4b8cea7bad")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_car_info>)))
  "Returns full string definition for message of type '<MobileyeInfo_car_info>"
  (cl:format cl:nil "Header header~%~%CarInfo car_info~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/CarInfo~%bool high_beam~%bool low_beam~%bool wipers~%bool right_signal~%bool left_signal~%bool brake_signal~%bool wipers_available~%bool low_beam_available~%bool high_beam_available~%bool right_blink_available~%bool left_blink_available~%bool brake_available~%bool speed_available~%uint8 speed~%uint8 shield_plus_settings~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_car_info)))
  "Returns full string definition for message of type 'MobileyeInfo_car_info"
  (cl:format cl:nil "Header header~%~%CarInfo car_info~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/CarInfo~%bool high_beam~%bool low_beam~%bool wipers~%bool right_signal~%bool left_signal~%bool brake_signal~%bool wipers_available~%bool low_beam_available~%bool high_beam_available~%bool right_blink_available~%bool left_blink_available~%bool brake_available~%bool speed_available~%uint8 speed~%uint8 shield_plus_settings~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_car_info>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'car_info))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_car_info>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_car_info
    (cl:cons ':header (header msg))
    (cl:cons ':car_info (car_info msg))
))
