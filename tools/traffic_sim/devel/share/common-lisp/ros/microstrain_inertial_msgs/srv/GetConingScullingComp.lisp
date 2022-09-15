; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetConingScullingComp-request.msg.html

(cl:defclass <GetConingScullingComp-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetConingScullingComp-request (<GetConingScullingComp-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetConingScullingComp-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetConingScullingComp-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetConingScullingComp-request> is deprecated: use microstrain_inertial_msgs-srv:GetConingScullingComp-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetConingScullingComp-request>) ostream)
  "Serializes a message object of type '<GetConingScullingComp-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetConingScullingComp-request>) istream)
  "Deserializes a message object of type '<GetConingScullingComp-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetConingScullingComp-request>)))
  "Returns string type for a service object of type '<GetConingScullingComp-request>"
  "microstrain_inertial_msgs/GetConingScullingCompRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetConingScullingComp-request)))
  "Returns string type for a service object of type 'GetConingScullingComp-request"
  "microstrain_inertial_msgs/GetConingScullingCompRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetConingScullingComp-request>)))
  "Returns md5sum for a message object of type '<GetConingScullingComp-request>"
  "73ec157fb12f6cbfec05839300a44bb3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetConingScullingComp-request)))
  "Returns md5sum for a message object of type 'GetConingScullingComp-request"
  "73ec157fb12f6cbfec05839300a44bb3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetConingScullingComp-request>)))
  "Returns full string definition for message of type '<GetConingScullingComp-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetConingScullingComp-request)))
  "Returns full string definition for message of type 'GetConingScullingComp-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetConingScullingComp-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetConingScullingComp-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetConingScullingComp-request
))
;//! \htmlinclude GetConingScullingComp-response.msg.html

(cl:defclass <GetConingScullingComp-response> (roslisp-msg-protocol:ros-message)
  ((enable
    :reader enable
    :initarg :enable
    :type cl:fixnum
    :initform 0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetConingScullingComp-response (<GetConingScullingComp-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetConingScullingComp-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetConingScullingComp-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetConingScullingComp-response> is deprecated: use microstrain_inertial_msgs-srv:GetConingScullingComp-response instead.")))

(cl:ensure-generic-function 'enable-val :lambda-list '(m))
(cl:defmethod enable-val ((m <GetConingScullingComp-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:enable-val is deprecated.  Use microstrain_inertial_msgs-srv:enable instead.")
  (enable m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetConingScullingComp-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetConingScullingComp-response>) ostream)
  "Serializes a message object of type '<GetConingScullingComp-response>"
  (cl:let* ((signed (cl:slot-value msg 'enable)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetConingScullingComp-response>) istream)
  "Deserializes a message object of type '<GetConingScullingComp-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enable) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetConingScullingComp-response>)))
  "Returns string type for a service object of type '<GetConingScullingComp-response>"
  "microstrain_inertial_msgs/GetConingScullingCompResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetConingScullingComp-response)))
  "Returns string type for a service object of type 'GetConingScullingComp-response"
  "microstrain_inertial_msgs/GetConingScullingCompResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetConingScullingComp-response>)))
  "Returns md5sum for a message object of type '<GetConingScullingComp-response>"
  "73ec157fb12f6cbfec05839300a44bb3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetConingScullingComp-response)))
  "Returns md5sum for a message object of type 'GetConingScullingComp-response"
  "73ec157fb12f6cbfec05839300a44bb3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetConingScullingComp-response>)))
  "Returns full string definition for message of type '<GetConingScullingComp-response>"
  (cl:format cl:nil "int8 enable~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetConingScullingComp-response)))
  "Returns full string definition for message of type 'GetConingScullingComp-response"
  (cl:format cl:nil "int8 enable~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetConingScullingComp-response>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetConingScullingComp-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetConingScullingComp-response
    (cl:cons ':enable (enable msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetConingScullingComp)))
  'GetConingScullingComp-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetConingScullingComp)))
  'GetConingScullingComp-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetConingScullingComp)))
  "Returns string type for a service object of type '<GetConingScullingComp>"
  "microstrain_inertial_msgs/GetConingScullingComp")