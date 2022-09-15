; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude RemoteButton.msg.html

(cl:defclass <RemoteButton> (roslisp-msg-protocol:ros-message)
  ((button1
    :reader button1
    :initarg :button1
    :type cl:fixnum
    :initform 0)
   (button2
    :reader button2
    :initarg :button2
    :type cl:fixnum
    :initform 0)
   (button3
    :reader button3
    :initarg :button3
    :type cl:fixnum
    :initform 0))
)

(cl:defclass RemoteButton (<RemoteButton>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RemoteButton>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RemoteButton)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<RemoteButton> is deprecated: use hmcl_msgs-msg:RemoteButton instead.")))

(cl:ensure-generic-function 'button1-val :lambda-list '(m))
(cl:defmethod button1-val ((m <RemoteButton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:button1-val is deprecated.  Use hmcl_msgs-msg:button1 instead.")
  (button1 m))

(cl:ensure-generic-function 'button2-val :lambda-list '(m))
(cl:defmethod button2-val ((m <RemoteButton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:button2-val is deprecated.  Use hmcl_msgs-msg:button2 instead.")
  (button2 m))

(cl:ensure-generic-function 'button3-val :lambda-list '(m))
(cl:defmethod button3-val ((m <RemoteButton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:button3-val is deprecated.  Use hmcl_msgs-msg:button3 instead.")
  (button3 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RemoteButton>) ostream)
  "Serializes a message object of type '<RemoteButton>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'button1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'button2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'button3)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RemoteButton>) istream)
  "Deserializes a message object of type '<RemoteButton>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'button1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'button2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'button3)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RemoteButton>)))
  "Returns string type for a message object of type '<RemoteButton>"
  "hmcl_msgs/RemoteButton")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RemoteButton)))
  "Returns string type for a message object of type 'RemoteButton"
  "hmcl_msgs/RemoteButton")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RemoteButton>)))
  "Returns md5sum for a message object of type '<RemoteButton>"
  "e0761a580fd3c116926a0b07701fd25f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RemoteButton)))
  "Returns md5sum for a message object of type 'RemoteButton"
  "e0761a580fd3c116926a0b07701fd25f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RemoteButton>)))
  "Returns full string definition for message of type '<RemoteButton>"
  (cl:format cl:nil "# wirelessbutton -> 0 push off, 1 -> push on~%uint8 button1~%uint8 button2~%uint8 button3~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RemoteButton)))
  "Returns full string definition for message of type 'RemoteButton"
  (cl:format cl:nil "# wirelessbutton -> 0 push off, 1 -> push on~%uint8 button1~%uint8 button2~%uint8 button3~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RemoteButton>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RemoteButton>))
  "Converts a ROS message object to a list"
  (cl:list 'RemoteButton
    (cl:cons ':button1 (button1 msg))
    (cl:cons ':button2 (button2 msg))
    (cl:cons ':button3 (button3 msg))
))
