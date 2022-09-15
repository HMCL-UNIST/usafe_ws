; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetConingScullingComp-request.msg.html

(cl:defclass <SetConingScullingComp-request> (roslisp-msg-protocol:ros-message)
  ((enable
    :reader enable
    :initarg :enable
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetConingScullingComp-request (<SetConingScullingComp-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetConingScullingComp-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetConingScullingComp-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetConingScullingComp-request> is deprecated: use microstrain_inertial_msgs-srv:SetConingScullingComp-request instead.")))

(cl:ensure-generic-function 'enable-val :lambda-list '(m))
(cl:defmethod enable-val ((m <SetConingScullingComp-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:enable-val is deprecated.  Use microstrain_inertial_msgs-srv:enable instead.")
  (enable m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetConingScullingComp-request>) ostream)
  "Serializes a message object of type '<SetConingScullingComp-request>"
  (cl:let* ((signed (cl:slot-value msg 'enable)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetConingScullingComp-request>) istream)
  "Deserializes a message object of type '<SetConingScullingComp-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enable) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetConingScullingComp-request>)))
  "Returns string type for a service object of type '<SetConingScullingComp-request>"
  "microstrain_inertial_msgs/SetConingScullingCompRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetConingScullingComp-request)))
  "Returns string type for a service object of type 'SetConingScullingComp-request"
  "microstrain_inertial_msgs/SetConingScullingCompRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetConingScullingComp-request>)))
  "Returns md5sum for a message object of type '<SetConingScullingComp-request>"
  "f7caf6e1618fb8cc640ac244d6c53d7f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetConingScullingComp-request)))
  "Returns md5sum for a message object of type 'SetConingScullingComp-request"
  "f7caf6e1618fb8cc640ac244d6c53d7f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetConingScullingComp-request>)))
  "Returns full string definition for message of type '<SetConingScullingComp-request>"
  (cl:format cl:nil "int8 enable~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetConingScullingComp-request)))
  "Returns full string definition for message of type 'SetConingScullingComp-request"
  (cl:format cl:nil "int8 enable~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetConingScullingComp-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetConingScullingComp-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetConingScullingComp-request
    (cl:cons ':enable (enable msg))
))
;//! \htmlinclude SetConingScullingComp-response.msg.html

(cl:defclass <SetConingScullingComp-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetConingScullingComp-response (<SetConingScullingComp-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetConingScullingComp-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetConingScullingComp-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetConingScullingComp-response> is deprecated: use microstrain_inertial_msgs-srv:SetConingScullingComp-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetConingScullingComp-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetConingScullingComp-response>) ostream)
  "Serializes a message object of type '<SetConingScullingComp-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetConingScullingComp-response>) istream)
  "Deserializes a message object of type '<SetConingScullingComp-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetConingScullingComp-response>)))
  "Returns string type for a service object of type '<SetConingScullingComp-response>"
  "microstrain_inertial_msgs/SetConingScullingCompResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetConingScullingComp-response)))
  "Returns string type for a service object of type 'SetConingScullingComp-response"
  "microstrain_inertial_msgs/SetConingScullingCompResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetConingScullingComp-response>)))
  "Returns md5sum for a message object of type '<SetConingScullingComp-response>"
  "f7caf6e1618fb8cc640ac244d6c53d7f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetConingScullingComp-response)))
  "Returns md5sum for a message object of type 'SetConingScullingComp-response"
  "f7caf6e1618fb8cc640ac244d6c53d7f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetConingScullingComp-response>)))
  "Returns full string definition for message of type '<SetConingScullingComp-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetConingScullingComp-response)))
  "Returns full string definition for message of type 'SetConingScullingComp-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetConingScullingComp-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetConingScullingComp-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetConingScullingComp-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetConingScullingComp)))
  'SetConingScullingComp-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetConingScullingComp)))
  'SetConingScullingComp-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetConingScullingComp)))
  "Returns string type for a service object of type '<SetConingScullingComp>"
  "microstrain_inertial_msgs/SetConingScullingComp")