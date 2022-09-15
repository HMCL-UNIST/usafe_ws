; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_referencepoints.msg.html

(cl:defclass <MobileyeInfo_referencepoints> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (reference_points
    :reader reference_points
    :initarg :reference_points
    :type mobileye_msgs-msg:ReferencePoints
    :initform (cl:make-instance 'mobileye_msgs-msg:ReferencePoints)))
)

(cl:defclass MobileyeInfo_referencepoints (<MobileyeInfo_referencepoints>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_referencepoints>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_referencepoints)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_referencepoints> is deprecated: use mobileye_msgs-msg:MobileyeInfo_referencepoints instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_referencepoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'reference_points-val :lambda-list '(m))
(cl:defmethod reference_points-val ((m <MobileyeInfo_referencepoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:reference_points-val is deprecated.  Use mobileye_msgs-msg:reference_points instead.")
  (reference_points m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_referencepoints>) ostream)
  "Serializes a message object of type '<MobileyeInfo_referencepoints>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'reference_points) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_referencepoints>) istream)
  "Deserializes a message object of type '<MobileyeInfo_referencepoints>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'reference_points) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_referencepoints>)))
  "Returns string type for a message object of type '<MobileyeInfo_referencepoints>"
  "mobileye_msgs/MobileyeInfo_referencepoints")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_referencepoints)))
  "Returns string type for a message object of type 'MobileyeInfo_referencepoints"
  "mobileye_msgs/MobileyeInfo_referencepoints")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_referencepoints>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_referencepoints>"
  "cb5549c03c083f3d1a2ac1fe68010326")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_referencepoints)))
  "Returns md5sum for a message object of type 'MobileyeInfo_referencepoints"
  "cb5549c03c083f3d1a2ac1fe68010326")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_referencepoints>)))
  "Returns full string definition for message of type '<MobileyeInfo_referencepoints>"
  (cl:format cl:nil "Header header~%~%ReferencePoints reference_points~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/ReferencePoints~%float32 ref_point1_position~%float32 ref_point1_distance~%bool ref_point1_validity~%float32 ref_point2_position~%float32 ref_point2_distance~%bool ref_point2_validity~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_referencepoints)))
  "Returns full string definition for message of type 'MobileyeInfo_referencepoints"
  (cl:format cl:nil "Header header~%~%ReferencePoints reference_points~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/ReferencePoints~%float32 ref_point1_position~%float32 ref_point1_distance~%bool ref_point1_validity~%float32 ref_point2_position~%float32 ref_point2_distance~%bool ref_point2_validity~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_referencepoints>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'reference_points))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_referencepoints>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_referencepoints
    (cl:cons ':header (header msg))
    (cl:cons ':reference_points (reference_points msg))
))
