; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetDynamicsMode-request.msg.html

(cl:defclass <SetDynamicsMode-request> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetDynamicsMode-request (<SetDynamicsMode-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetDynamicsMode-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetDynamicsMode-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetDynamicsMode-request> is deprecated: use microstrain_inertial_msgs-srv:SetDynamicsMode-request instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <SetDynamicsMode-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:mode-val is deprecated.  Use microstrain_inertial_msgs-srv:mode instead.")
  (mode m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<SetDynamicsMode-request>)))
    "Constants for message type '<SetDynamicsMode-request>"
  '((:PORTABLE . 1)
    (:AUTOMOTIVE . 2)
    (:AIRBORNE . 3))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'SetDynamicsMode-request)))
    "Constants for message type 'SetDynamicsMode-request"
  '((:PORTABLE . 1)
    (:AUTOMOTIVE . 2)
    (:AIRBORNE . 3))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetDynamicsMode-request>) ostream)
  "Serializes a message object of type '<SetDynamicsMode-request>"
  (cl:let* ((signed (cl:slot-value msg 'mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetDynamicsMode-request>) istream)
  "Deserializes a message object of type '<SetDynamicsMode-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mode) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetDynamicsMode-request>)))
  "Returns string type for a service object of type '<SetDynamicsMode-request>"
  "microstrain_inertial_msgs/SetDynamicsModeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetDynamicsMode-request)))
  "Returns string type for a service object of type 'SetDynamicsMode-request"
  "microstrain_inertial_msgs/SetDynamicsModeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetDynamicsMode-request>)))
  "Returns md5sum for a message object of type '<SetDynamicsMode-request>"
  "44114e5483e212902c0a057defaa1a3b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetDynamicsMode-request)))
  "Returns md5sum for a message object of type 'SetDynamicsMode-request"
  "44114e5483e212902c0a057defaa1a3b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetDynamicsMode-request>)))
  "Returns full string definition for message of type '<SetDynamicsMode-request>"
  (cl:format cl:nil "int8 PORTABLE=1~%int8 AUTOMOTIVE=2~%int8 AIRBORNE=3~%int8 mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetDynamicsMode-request)))
  "Returns full string definition for message of type 'SetDynamicsMode-request"
  (cl:format cl:nil "int8 PORTABLE=1~%int8 AUTOMOTIVE=2~%int8 AIRBORNE=3~%int8 mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetDynamicsMode-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetDynamicsMode-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetDynamicsMode-request
    (cl:cons ':mode (mode msg))
))
;//! \htmlinclude SetDynamicsMode-response.msg.html

(cl:defclass <SetDynamicsMode-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetDynamicsMode-response (<SetDynamicsMode-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetDynamicsMode-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetDynamicsMode-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetDynamicsMode-response> is deprecated: use microstrain_inertial_msgs-srv:SetDynamicsMode-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetDynamicsMode-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetDynamicsMode-response>) ostream)
  "Serializes a message object of type '<SetDynamicsMode-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetDynamicsMode-response>) istream)
  "Deserializes a message object of type '<SetDynamicsMode-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetDynamicsMode-response>)))
  "Returns string type for a service object of type '<SetDynamicsMode-response>"
  "microstrain_inertial_msgs/SetDynamicsModeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetDynamicsMode-response)))
  "Returns string type for a service object of type 'SetDynamicsMode-response"
  "microstrain_inertial_msgs/SetDynamicsModeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetDynamicsMode-response>)))
  "Returns md5sum for a message object of type '<SetDynamicsMode-response>"
  "44114e5483e212902c0a057defaa1a3b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetDynamicsMode-response)))
  "Returns md5sum for a message object of type 'SetDynamicsMode-response"
  "44114e5483e212902c0a057defaa1a3b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetDynamicsMode-response>)))
  "Returns full string definition for message of type '<SetDynamicsMode-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetDynamicsMode-response)))
  "Returns full string definition for message of type 'SetDynamicsMode-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetDynamicsMode-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetDynamicsMode-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetDynamicsMode-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetDynamicsMode)))
  'SetDynamicsMode-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetDynamicsMode)))
  'SetDynamicsMode-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetDynamicsMode)))
  "Returns string type for a service object of type '<SetDynamicsMode>"
  "microstrain_inertial_msgs/SetDynamicsMode")