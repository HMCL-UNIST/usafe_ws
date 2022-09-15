; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_left.msg.html

(cl:defclass <MobileyeInfo_left> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (left_lane
    :reader left_lane
    :initarg :left_lane
    :type mobileye_msgs-msg:LKAlane
    :initform (cl:make-instance 'mobileye_msgs-msg:LKAlane)))
)

(cl:defclass MobileyeInfo_left (<MobileyeInfo_left>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_left>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_left)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_left> is deprecated: use mobileye_msgs-msg:MobileyeInfo_left instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_left>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'left_lane-val :lambda-list '(m))
(cl:defmethod left_lane-val ((m <MobileyeInfo_left>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:left_lane-val is deprecated.  Use mobileye_msgs-msg:left_lane instead.")
  (left_lane m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_left>) ostream)
  "Serializes a message object of type '<MobileyeInfo_left>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'left_lane) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_left>) istream)
  "Deserializes a message object of type '<MobileyeInfo_left>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'left_lane) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_left>)))
  "Returns string type for a message object of type '<MobileyeInfo_left>"
  "mobileye_msgs/MobileyeInfo_left")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_left)))
  "Returns string type for a message object of type 'MobileyeInfo_left"
  "mobileye_msgs/MobileyeInfo_left")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_left>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_left>"
  "c217d2eb54c3d76dac77bb6f21d5971d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_left)))
  "Returns md5sum for a message object of type 'MobileyeInfo_left"
  "c217d2eb54c3d76dac77bb6f21d5971d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_left>)))
  "Returns full string definition for message of type '<MobileyeInfo_left>"
  (cl:format cl:nil "Header header~%~%LKAlane left_lane~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_left)))
  "Returns full string definition for message of type 'MobileyeInfo_left"
  (cl:format cl:nil "Header header~%~%LKAlane left_lane~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_left>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'left_lane))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_left>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_left
    (cl:cons ':header (header msg))
    (cl:cons ':left_lane (left_lane msg))
))
