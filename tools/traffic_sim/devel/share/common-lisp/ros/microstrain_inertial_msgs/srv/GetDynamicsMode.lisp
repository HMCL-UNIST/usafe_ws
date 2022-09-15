; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetDynamicsMode-request.msg.html

(cl:defclass <GetDynamicsMode-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetDynamicsMode-request (<GetDynamicsMode-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetDynamicsMode-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetDynamicsMode-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetDynamicsMode-request> is deprecated: use microstrain_inertial_msgs-srv:GetDynamicsMode-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetDynamicsMode-request>) ostream)
  "Serializes a message object of type '<GetDynamicsMode-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetDynamicsMode-request>) istream)
  "Deserializes a message object of type '<GetDynamicsMode-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetDynamicsMode-request>)))
  "Returns string type for a service object of type '<GetDynamicsMode-request>"
  "microstrain_inertial_msgs/GetDynamicsModeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetDynamicsMode-request)))
  "Returns string type for a service object of type 'GetDynamicsMode-request"
  "microstrain_inertial_msgs/GetDynamicsModeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetDynamicsMode-request>)))
  "Returns md5sum for a message object of type '<GetDynamicsMode-request>"
  "4315dfa070d15c7ffc8d87836f8ad09c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetDynamicsMode-request)))
  "Returns md5sum for a message object of type 'GetDynamicsMode-request"
  "4315dfa070d15c7ffc8d87836f8ad09c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetDynamicsMode-request>)))
  "Returns full string definition for message of type '<GetDynamicsMode-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetDynamicsMode-request)))
  "Returns full string definition for message of type 'GetDynamicsMode-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetDynamicsMode-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetDynamicsMode-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetDynamicsMode-request
))
;//! \htmlinclude GetDynamicsMode-response.msg.html

(cl:defclass <GetDynamicsMode-response> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetDynamicsMode-response (<GetDynamicsMode-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetDynamicsMode-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetDynamicsMode-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetDynamicsMode-response> is deprecated: use microstrain_inertial_msgs-srv:GetDynamicsMode-response instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <GetDynamicsMode-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:mode-val is deprecated.  Use microstrain_inertial_msgs-srv:mode instead.")
  (mode m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetDynamicsMode-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetDynamicsMode-response>) ostream)
  "Serializes a message object of type '<GetDynamicsMode-response>"
  (cl:let* ((signed (cl:slot-value msg 'mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetDynamicsMode-response>) istream)
  "Deserializes a message object of type '<GetDynamicsMode-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mode) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetDynamicsMode-response>)))
  "Returns string type for a service object of type '<GetDynamicsMode-response>"
  "microstrain_inertial_msgs/GetDynamicsModeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetDynamicsMode-response)))
  "Returns string type for a service object of type 'GetDynamicsMode-response"
  "microstrain_inertial_msgs/GetDynamicsModeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetDynamicsMode-response>)))
  "Returns md5sum for a message object of type '<GetDynamicsMode-response>"
  "4315dfa070d15c7ffc8d87836f8ad09c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetDynamicsMode-response)))
  "Returns md5sum for a message object of type 'GetDynamicsMode-response"
  "4315dfa070d15c7ffc8d87836f8ad09c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetDynamicsMode-response>)))
  "Returns full string definition for message of type '<GetDynamicsMode-response>"
  (cl:format cl:nil "int8 mode~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetDynamicsMode-response)))
  "Returns full string definition for message of type 'GetDynamicsMode-response"
  (cl:format cl:nil "int8 mode~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetDynamicsMode-response>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetDynamicsMode-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetDynamicsMode-response
    (cl:cons ':mode (mode msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetDynamicsMode)))
  'GetDynamicsMode-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetDynamicsMode)))
  'GetDynamicsMode-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetDynamicsMode)))
  "Returns string type for a service object of type '<GetDynamicsMode>"
  "microstrain_inertial_msgs/GetDynamicsMode")