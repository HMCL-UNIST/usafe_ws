; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude TrafficlightArray.msg.html

(cl:defclass <TrafficlightArray> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (trafficlights
    :reader trafficlights
    :initarg :trafficlights
    :type (cl:vector hmcl_msgs-msg:Trafficlight)
   :initform (cl:make-array 0 :element-type 'hmcl_msgs-msg:Trafficlight :initial-element (cl:make-instance 'hmcl_msgs-msg:Trafficlight))))
)

(cl:defclass TrafficlightArray (<TrafficlightArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TrafficlightArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TrafficlightArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<TrafficlightArray> is deprecated: use hmcl_msgs-msg:TrafficlightArray instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <TrafficlightArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:header-val is deprecated.  Use hmcl_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'trafficlights-val :lambda-list '(m))
(cl:defmethod trafficlights-val ((m <TrafficlightArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:trafficlights-val is deprecated.  Use hmcl_msgs-msg:trafficlights instead.")
  (trafficlights m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TrafficlightArray>) ostream)
  "Serializes a message object of type '<TrafficlightArray>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'trafficlights))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'trafficlights))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TrafficlightArray>) istream)
  "Deserializes a message object of type '<TrafficlightArray>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'trafficlights) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'trafficlights)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'hmcl_msgs-msg:Trafficlight))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TrafficlightArray>)))
  "Returns string type for a message object of type '<TrafficlightArray>"
  "hmcl_msgs/TrafficlightArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TrafficlightArray)))
  "Returns string type for a message object of type 'TrafficlightArray"
  "hmcl_msgs/TrafficlightArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TrafficlightArray>)))
  "Returns md5sum for a message object of type '<TrafficlightArray>"
  "06a8e2673b5b387a7023181a4c767949")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TrafficlightArray)))
  "Returns md5sum for a message object of type 'TrafficlightArray"
  "06a8e2673b5b387a7023181a4c767949")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TrafficlightArray>)))
  "Returns full string definition for message of type '<TrafficlightArray>"
  (cl:format cl:nil "Header header~%Trafficlight[] trafficlights~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hmcl_msgs/Trafficlight~%Header header~%int32 id~%int32 lanelet_id~%geometry_msgs/Pose pose~%TrafficlightBulb left_light~%TrafficlightBulb straight_light~%TrafficlightBulb right_light~%bool valid_stop_line~%geometry_msgs/Pose stop_line~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: hmcl_msgs/TrafficlightBulb~%int32 id~%int32 light_status # 0 red, 1 green, 2 yellow ~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TrafficlightArray)))
  "Returns full string definition for message of type 'TrafficlightArray"
  (cl:format cl:nil "Header header~%Trafficlight[] trafficlights~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hmcl_msgs/Trafficlight~%Header header~%int32 id~%int32 lanelet_id~%geometry_msgs/Pose pose~%TrafficlightBulb left_light~%TrafficlightBulb straight_light~%TrafficlightBulb right_light~%bool valid_stop_line~%geometry_msgs/Pose stop_line~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: hmcl_msgs/TrafficlightBulb~%int32 id~%int32 light_status # 0 red, 1 green, 2 yellow ~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TrafficlightArray>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'trafficlights) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TrafficlightArray>))
  "Converts a ROS message object to a list"
  (cl:list 'TrafficlightArray
    (cl:cons ':header (header msg))
    (cl:cons ':trafficlights (trafficlights msg))
))
