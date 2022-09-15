; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude TrafficlightBulb.msg.html

(cl:defclass <TrafficlightBulb> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (light_status
    :reader light_status
    :initarg :light_status
    :type cl:integer
    :initform 0))
)

(cl:defclass TrafficlightBulb (<TrafficlightBulb>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TrafficlightBulb>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TrafficlightBulb)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<TrafficlightBulb> is deprecated: use hmcl_msgs-msg:TrafficlightBulb instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <TrafficlightBulb>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:id-val is deprecated.  Use hmcl_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'light_status-val :lambda-list '(m))
(cl:defmethod light_status-val ((m <TrafficlightBulb>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:light_status-val is deprecated.  Use hmcl_msgs-msg:light_status instead.")
  (light_status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TrafficlightBulb>) ostream)
  "Serializes a message object of type '<TrafficlightBulb>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'light_status)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TrafficlightBulb>) istream)
  "Deserializes a message object of type '<TrafficlightBulb>"
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
      (cl:setf (cl:slot-value msg 'light_status) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TrafficlightBulb>)))
  "Returns string type for a message object of type '<TrafficlightBulb>"
  "hmcl_msgs/TrafficlightBulb")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TrafficlightBulb)))
  "Returns string type for a message object of type 'TrafficlightBulb"
  "hmcl_msgs/TrafficlightBulb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TrafficlightBulb>)))
  "Returns md5sum for a message object of type '<TrafficlightBulb>"
  "29a65252a3c7d022a599aef3b93bd92c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TrafficlightBulb)))
  "Returns md5sum for a message object of type 'TrafficlightBulb"
  "29a65252a3c7d022a599aef3b93bd92c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TrafficlightBulb>)))
  "Returns full string definition for message of type '<TrafficlightBulb>"
  (cl:format cl:nil "int32 id~%int32 light_status # 0 red, 1 green, 2 yellow ~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TrafficlightBulb)))
  "Returns full string definition for message of type 'TrafficlightBulb"
  (cl:format cl:nil "int32 id~%int32 light_status # 0 red, 1 green, 2 yellow ~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TrafficlightBulb>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TrafficlightBulb>))
  "Converts a ROS message object to a list"
  (cl:list 'TrafficlightBulb
    (cl:cons ':id (id msg))
    (cl:cons ':light_status (light_status msg))
))
