; Auto-generated. Do not edit!


(cl:in-package autorally_msgs-msg)


;//! \htmlinclude point2D.msg.html

(cl:defclass <point2D> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:fixnum
    :initform 0)
   (y
    :reader y
    :initarg :y
    :type cl:fixnum
    :initform 0))
)

(cl:defclass point2D (<point2D>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <point2D>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'point2D)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autorally_msgs-msg:<point2D> is deprecated: use autorally_msgs-msg:point2D instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <point2D>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:x-val is deprecated.  Use autorally_msgs-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <point2D>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:y-val is deprecated.  Use autorally_msgs-msg:y instead.")
  (y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <point2D>) ostream)
  "Serializes a message object of type '<point2D>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'x)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'x)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'y)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'y)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <point2D>) istream)
  "Deserializes a message object of type '<point2D>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'x)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'x)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'y)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'y)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<point2D>)))
  "Returns string type for a message object of type '<point2D>"
  "autorally_msgs/point2D")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'point2D)))
  "Returns string type for a message object of type 'point2D"
  "autorally_msgs/point2D")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<point2D>)))
  "Returns md5sum for a message object of type '<point2D>"
  "2b80853b9dd76da1c3efb4dbc2426fe9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'point2D)))
  "Returns md5sum for a message object of type 'point2D"
  "2b80853b9dd76da1c3efb4dbc2426fe9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<point2D>)))
  "Returns full string definition for message of type '<point2D>"
  (cl:format cl:nil "uint16 x~%uint16 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'point2D)))
  "Returns full string definition for message of type 'point2D"
  (cl:format cl:nil "uint16 x~%uint16 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <point2D>))
  (cl:+ 0
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <point2D>))
  "Converts a ROS message object to a list"
  (cl:list 'point2D
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
))
