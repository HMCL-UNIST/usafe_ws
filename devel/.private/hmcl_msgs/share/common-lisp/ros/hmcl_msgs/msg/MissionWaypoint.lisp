; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude MissionWaypoint.msg.html

(cl:defclass <MissionWaypoint> (roslisp-msg-protocol:ros-message)
  ((start
    :reader start
    :initarg :start
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (end
    :reader end
    :initarg :end
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (remain
    :reader remain
    :initarg :remain
    :type cl:integer
    :initform 0))
)

(cl:defclass MissionWaypoint (<MissionWaypoint>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MissionWaypoint>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MissionWaypoint)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<MissionWaypoint> is deprecated: use hmcl_msgs-msg:MissionWaypoint instead.")))

(cl:ensure-generic-function 'start-val :lambda-list '(m))
(cl:defmethod start-val ((m <MissionWaypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:start-val is deprecated.  Use hmcl_msgs-msg:start instead.")
  (start m))

(cl:ensure-generic-function 'end-val :lambda-list '(m))
(cl:defmethod end-val ((m <MissionWaypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:end-val is deprecated.  Use hmcl_msgs-msg:end instead.")
  (end m))

(cl:ensure-generic-function 'remain-val :lambda-list '(m))
(cl:defmethod remain-val ((m <MissionWaypoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:remain-val is deprecated.  Use hmcl_msgs-msg:remain instead.")
  (remain m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MissionWaypoint>) ostream)
  "Serializes a message object of type '<MissionWaypoint>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'start) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'end) ostream)
  (cl:let* ((signed (cl:slot-value msg 'remain)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MissionWaypoint>) istream)
  "Deserializes a message object of type '<MissionWaypoint>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'start) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'end) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'remain) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MissionWaypoint>)))
  "Returns string type for a message object of type '<MissionWaypoint>"
  "hmcl_msgs/MissionWaypoint")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MissionWaypoint)))
  "Returns string type for a message object of type 'MissionWaypoint"
  "hmcl_msgs/MissionWaypoint")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MissionWaypoint>)))
  "Returns md5sum for a message object of type '<MissionWaypoint>"
  "787e74dd4a3e0df7f1ef38d7abe84225")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MissionWaypoint)))
  "Returns md5sum for a message object of type 'MissionWaypoint"
  "787e74dd4a3e0df7f1ef38d7abe84225")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MissionWaypoint>)))
  "Returns full string definition for message of type '<MissionWaypoint>"
  (cl:format cl:nil "# global id~%geometry_msgs/Point start~%geometry_msgs/Point end~%int32 remain~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MissionWaypoint)))
  "Returns full string definition for message of type 'MissionWaypoint"
  (cl:format cl:nil "# global id~%geometry_msgs/Point start~%geometry_msgs/Point end~%int32 remain~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MissionWaypoint>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'start))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'end))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MissionWaypoint>))
  "Converts a ROS message object to a list"
  (cl:list 'MissionWaypoint
    (cl:cons ':start (start msg))
    (cl:cons ':end (end msg))
    (cl:cons ':remain (remain msg))
))
