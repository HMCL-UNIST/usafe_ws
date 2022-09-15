; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_lane.msg.html

(cl:defclass <MobileyeInfo_lane> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (lane
    :reader lane
    :initarg :lane
    :type mobileye_msgs-msg:Lane
    :initform (cl:make-instance 'mobileye_msgs-msg:Lane)))
)

(cl:defclass MobileyeInfo_lane (<MobileyeInfo_lane>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_lane>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_lane)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_lane> is deprecated: use mobileye_msgs-msg:MobileyeInfo_lane instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'lane-val :lambda-list '(m))
(cl:defmethod lane-val ((m <MobileyeInfo_lane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:lane-val is deprecated.  Use mobileye_msgs-msg:lane instead.")
  (lane m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_lane>) ostream)
  "Serializes a message object of type '<MobileyeInfo_lane>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'lane) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_lane>) istream)
  "Deserializes a message object of type '<MobileyeInfo_lane>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'lane) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_lane>)))
  "Returns string type for a message object of type '<MobileyeInfo_lane>"
  "mobileye_msgs/MobileyeInfo_lane")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_lane)))
  "Returns string type for a message object of type 'MobileyeInfo_lane"
  "mobileye_msgs/MobileyeInfo_lane")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_lane>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_lane>"
  "2167664513fbefa299d496bdde8fbd05")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_lane)))
  "Returns md5sum for a message object of type 'MobileyeInfo_lane"
  "2167664513fbefa299d496bdde8fbd05")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_lane>)))
  "Returns full string definition for message of type '<MobileyeInfo_lane>"
  (cl:format cl:nil "Header header~%~%Lane lane~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/Lane~%float32 lane_curvature~%float32 lane_heading~%~%bool ca~%float32 pitch_angle~%float32 yaw_angle~%~%bool right_ldw_availability~%bool left_ldw_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_lane)))
  "Returns full string definition for message of type 'MobileyeInfo_lane"
  (cl:format cl:nil "Header header~%~%Lane lane~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/Lane~%float32 lane_curvature~%float32 lane_heading~%~%bool ca~%float32 pitch_angle~%float32 yaw_angle~%~%bool right_ldw_availability~%bool left_ldw_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_lane>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'lane))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_lane>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_lane
    (cl:cons ':header (header msg))
    (cl:cons ':lane (lane msg))
))
