; Auto-generated. Do not edit!


(cl:in-package autorally_msgs-msg)


;//! \htmlinclude line2D.msg.html

(cl:defclass <line2D> (roslisp-msg-protocol:ros-message)
  ((start
    :reader start
    :initarg :start
    :type autorally_msgs-msg:point2D
    :initform (cl:make-instance 'autorally_msgs-msg:point2D))
   (end
    :reader end
    :initarg :end
    :type autorally_msgs-msg:point2D
    :initform (cl:make-instance 'autorally_msgs-msg:point2D)))
)

(cl:defclass line2D (<line2D>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <line2D>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'line2D)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autorally_msgs-msg:<line2D> is deprecated: use autorally_msgs-msg:line2D instead.")))

(cl:ensure-generic-function 'start-val :lambda-list '(m))
(cl:defmethod start-val ((m <line2D>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:start-val is deprecated.  Use autorally_msgs-msg:start instead.")
  (start m))

(cl:ensure-generic-function 'end-val :lambda-list '(m))
(cl:defmethod end-val ((m <line2D>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:end-val is deprecated.  Use autorally_msgs-msg:end instead.")
  (end m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <line2D>) ostream)
  "Serializes a message object of type '<line2D>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'start) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'end) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <line2D>) istream)
  "Deserializes a message object of type '<line2D>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'start) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'end) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<line2D>)))
  "Returns string type for a message object of type '<line2D>"
  "autorally_msgs/line2D")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'line2D)))
  "Returns string type for a message object of type 'line2D"
  "autorally_msgs/line2D")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<line2D>)))
  "Returns md5sum for a message object of type '<line2D>"
  "7a338da65a86a1f736887760a0feaccd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'line2D)))
  "Returns md5sum for a message object of type 'line2D"
  "7a338da65a86a1f736887760a0feaccd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<line2D>)))
  "Returns full string definition for message of type '<line2D>"
  (cl:format cl:nil "point2D start~%point2D end~%~%================================================================================~%MSG: autorally_msgs/point2D~%uint16 x~%uint16 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'line2D)))
  "Returns full string definition for message of type 'line2D"
  (cl:format cl:nil "point2D start~%point2D end~%~%================================================================================~%MSG: autorally_msgs/point2D~%uint16 x~%uint16 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <line2D>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'start))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'end))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <line2D>))
  "Converts a ROS message object to a list"
  (cl:list 'line2D
    (cl:cons ':start (start msg))
    (cl:cons ':end (end msg))
))
