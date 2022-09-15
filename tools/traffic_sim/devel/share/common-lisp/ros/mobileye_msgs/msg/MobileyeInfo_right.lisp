; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_right.msg.html

(cl:defclass <MobileyeInfo_right> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (right_lane
    :reader right_lane
    :initarg :right_lane
    :type mobileye_msgs-msg:LKAlane
    :initform (cl:make-instance 'mobileye_msgs-msg:LKAlane)))
)

(cl:defclass MobileyeInfo_right (<MobileyeInfo_right>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_right>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_right)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_right> is deprecated: use mobileye_msgs-msg:MobileyeInfo_right instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_right>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'right_lane-val :lambda-list '(m))
(cl:defmethod right_lane-val ((m <MobileyeInfo_right>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:right_lane-val is deprecated.  Use mobileye_msgs-msg:right_lane instead.")
  (right_lane m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_right>) ostream)
  "Serializes a message object of type '<MobileyeInfo_right>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'right_lane) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_right>) istream)
  "Deserializes a message object of type '<MobileyeInfo_right>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'right_lane) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_right>)))
  "Returns string type for a message object of type '<MobileyeInfo_right>"
  "mobileye_msgs/MobileyeInfo_right")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_right)))
  "Returns string type for a message object of type 'MobileyeInfo_right"
  "mobileye_msgs/MobileyeInfo_right")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_right>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_right>"
  "f403053ee52387e5c63c01fd8df420e3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_right)))
  "Returns md5sum for a message object of type 'MobileyeInfo_right"
  "f403053ee52387e5c63c01fd8df420e3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_right>)))
  "Returns full string definition for message of type '<MobileyeInfo_right>"
  (cl:format cl:nil "Header header~%~%LKAlane right_lane~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_right)))
  "Returns full string definition for message of type 'MobileyeInfo_right"
  (cl:format cl:nil "Header header~%~%LKAlane right_lane~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_right>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'right_lane))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_right>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_right
    (cl:cons ':header (header msg))
    (cl:cons ':right_lane (right_lane msg))
))
