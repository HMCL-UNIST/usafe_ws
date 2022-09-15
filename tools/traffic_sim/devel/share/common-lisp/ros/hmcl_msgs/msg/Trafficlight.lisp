; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude Trafficlight.msg.html

(cl:defclass <Trafficlight> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (lanelet_id
    :reader lanelet_id
    :initarg :lanelet_id
    :type cl:integer
    :initform 0)
   (pose
    :reader pose
    :initarg :pose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (left_light
    :reader left_light
    :initarg :left_light
    :type hmcl_msgs-msg:TrafficlightBulb
    :initform (cl:make-instance 'hmcl_msgs-msg:TrafficlightBulb))
   (straight_light
    :reader straight_light
    :initarg :straight_light
    :type hmcl_msgs-msg:TrafficlightBulb
    :initform (cl:make-instance 'hmcl_msgs-msg:TrafficlightBulb))
   (right_light
    :reader right_light
    :initarg :right_light
    :type hmcl_msgs-msg:TrafficlightBulb
    :initform (cl:make-instance 'hmcl_msgs-msg:TrafficlightBulb))
   (valid_stop_line
    :reader valid_stop_line
    :initarg :valid_stop_line
    :type cl:boolean
    :initform cl:nil)
   (stop_line
    :reader stop_line
    :initarg :stop_line
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose)))
)

(cl:defclass Trafficlight (<Trafficlight>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Trafficlight>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Trafficlight)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<Trafficlight> is deprecated: use hmcl_msgs-msg:Trafficlight instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:header-val is deprecated.  Use hmcl_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:id-val is deprecated.  Use hmcl_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'lanelet_id-val :lambda-list '(m))
(cl:defmethod lanelet_id-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:lanelet_id-val is deprecated.  Use hmcl_msgs-msg:lanelet_id instead.")
  (lanelet_id m))

(cl:ensure-generic-function 'pose-val :lambda-list '(m))
(cl:defmethod pose-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:pose-val is deprecated.  Use hmcl_msgs-msg:pose instead.")
  (pose m))

(cl:ensure-generic-function 'left_light-val :lambda-list '(m))
(cl:defmethod left_light-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:left_light-val is deprecated.  Use hmcl_msgs-msg:left_light instead.")
  (left_light m))

(cl:ensure-generic-function 'straight_light-val :lambda-list '(m))
(cl:defmethod straight_light-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:straight_light-val is deprecated.  Use hmcl_msgs-msg:straight_light instead.")
  (straight_light m))

(cl:ensure-generic-function 'right_light-val :lambda-list '(m))
(cl:defmethod right_light-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:right_light-val is deprecated.  Use hmcl_msgs-msg:right_light instead.")
  (right_light m))

(cl:ensure-generic-function 'valid_stop_line-val :lambda-list '(m))
(cl:defmethod valid_stop_line-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:valid_stop_line-val is deprecated.  Use hmcl_msgs-msg:valid_stop_line instead.")
  (valid_stop_line m))

(cl:ensure-generic-function 'stop_line-val :lambda-list '(m))
(cl:defmethod stop_line-val ((m <Trafficlight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:stop_line-val is deprecated.  Use hmcl_msgs-msg:stop_line instead.")
  (stop_line m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Trafficlight>) ostream)
  "Serializes a message object of type '<Trafficlight>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'lanelet_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'left_light) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'straight_light) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'right_light) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'valid_stop_line) 1 0)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'stop_line) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Trafficlight>) istream)
  "Deserializes a message object of type '<Trafficlight>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'lanelet_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'left_light) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'straight_light) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'right_light) istream)
    (cl:setf (cl:slot-value msg 'valid_stop_line) (cl:not (cl:zerop (cl:read-byte istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'stop_line) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Trafficlight>)))
  "Returns string type for a message object of type '<Trafficlight>"
  "hmcl_msgs/Trafficlight")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Trafficlight)))
  "Returns string type for a message object of type 'Trafficlight"
  "hmcl_msgs/Trafficlight")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Trafficlight>)))
  "Returns md5sum for a message object of type '<Trafficlight>"
  "a8bcc1bd70d49e0e7bdd9aa331d45dc1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Trafficlight)))
  "Returns md5sum for a message object of type 'Trafficlight"
  "a8bcc1bd70d49e0e7bdd9aa331d45dc1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Trafficlight>)))
  "Returns full string definition for message of type '<Trafficlight>"
  (cl:format cl:nil "Header header~%int32 id~%int32 lanelet_id~%geometry_msgs/Pose pose~%TrafficlightBulb left_light~%TrafficlightBulb straight_light~%TrafficlightBulb right_light~%bool valid_stop_line~%geometry_msgs/Pose stop_line~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: hmcl_msgs/TrafficlightBulb~%int32 id~%int32 light_status # 0 red, 1 green, 2 yellow ~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Trafficlight)))
  "Returns full string definition for message of type 'Trafficlight"
  (cl:format cl:nil "Header header~%int32 id~%int32 lanelet_id~%geometry_msgs/Pose pose~%TrafficlightBulb left_light~%TrafficlightBulb straight_light~%TrafficlightBulb right_light~%bool valid_stop_line~%geometry_msgs/Pose stop_line~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: hmcl_msgs/TrafficlightBulb~%int32 id~%int32 light_status # 0 red, 1 green, 2 yellow ~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Trafficlight>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'left_light))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'straight_light))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'right_light))
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'stop_line))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Trafficlight>))
  "Converts a ROS message object to a list"
  (cl:list 'Trafficlight
    (cl:cons ':header (header msg))
    (cl:cons ':id (id msg))
    (cl:cons ':lanelet_id (lanelet_id msg))
    (cl:cons ':pose (pose msg))
    (cl:cons ':left_light (left_light msg))
    (cl:cons ':straight_light (straight_light msg))
    (cl:cons ':right_light (right_light msg))
    (cl:cons ':valid_stop_line (valid_stop_line msg))
    (cl:cons ':stop_line (stop_line msg))
))
