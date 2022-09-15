; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetZeroVelocityUpdateThreshold-request.msg.html

(cl:defclass <SetZeroVelocityUpdateThreshold-request> (roslisp-msg-protocol:ros-message)
  ((enable
    :reader enable
    :initarg :enable
    :type cl:fixnum
    :initform 0)
   (threshold
    :reader threshold
    :initarg :threshold
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetZeroVelocityUpdateThreshold-request (<SetZeroVelocityUpdateThreshold-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetZeroVelocityUpdateThreshold-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetZeroVelocityUpdateThreshold-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetZeroVelocityUpdateThreshold-request> is deprecated: use microstrain_inertial_msgs-srv:SetZeroVelocityUpdateThreshold-request instead.")))

(cl:ensure-generic-function 'enable-val :lambda-list '(m))
(cl:defmethod enable-val ((m <SetZeroVelocityUpdateThreshold-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:enable-val is deprecated.  Use microstrain_inertial_msgs-srv:enable instead.")
  (enable m))

(cl:ensure-generic-function 'threshold-val :lambda-list '(m))
(cl:defmethod threshold-val ((m <SetZeroVelocityUpdateThreshold-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:threshold-val is deprecated.  Use microstrain_inertial_msgs-srv:threshold instead.")
  (threshold m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetZeroVelocityUpdateThreshold-request>) ostream)
  "Serializes a message object of type '<SetZeroVelocityUpdateThreshold-request>"
  (cl:let* ((signed (cl:slot-value msg 'enable)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'threshold))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetZeroVelocityUpdateThreshold-request>) istream)
  "Deserializes a message object of type '<SetZeroVelocityUpdateThreshold-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enable) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'threshold) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetZeroVelocityUpdateThreshold-request>)))
  "Returns string type for a service object of type '<SetZeroVelocityUpdateThreshold-request>"
  "microstrain_inertial_msgs/SetZeroVelocityUpdateThresholdRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetZeroVelocityUpdateThreshold-request)))
  "Returns string type for a service object of type 'SetZeroVelocityUpdateThreshold-request"
  "microstrain_inertial_msgs/SetZeroVelocityUpdateThresholdRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetZeroVelocityUpdateThreshold-request>)))
  "Returns md5sum for a message object of type '<SetZeroVelocityUpdateThreshold-request>"
  "ea1115ed39d8a581530c7c251ee443e6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetZeroVelocityUpdateThreshold-request)))
  "Returns md5sum for a message object of type 'SetZeroVelocityUpdateThreshold-request"
  "ea1115ed39d8a581530c7c251ee443e6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetZeroVelocityUpdateThreshold-request>)))
  "Returns full string definition for message of type '<SetZeroVelocityUpdateThreshold-request>"
  (cl:format cl:nil "int8 enable~%float32 threshold~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetZeroVelocityUpdateThreshold-request)))
  "Returns full string definition for message of type 'SetZeroVelocityUpdateThreshold-request"
  (cl:format cl:nil "int8 enable~%float32 threshold~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetZeroVelocityUpdateThreshold-request>))
  (cl:+ 0
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetZeroVelocityUpdateThreshold-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetZeroVelocityUpdateThreshold-request
    (cl:cons ':enable (enable msg))
    (cl:cons ':threshold (threshold msg))
))
;//! \htmlinclude SetZeroVelocityUpdateThreshold-response.msg.html

(cl:defclass <SetZeroVelocityUpdateThreshold-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetZeroVelocityUpdateThreshold-response (<SetZeroVelocityUpdateThreshold-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetZeroVelocityUpdateThreshold-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetZeroVelocityUpdateThreshold-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetZeroVelocityUpdateThreshold-response> is deprecated: use microstrain_inertial_msgs-srv:SetZeroVelocityUpdateThreshold-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetZeroVelocityUpdateThreshold-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetZeroVelocityUpdateThreshold-response>) ostream)
  "Serializes a message object of type '<SetZeroVelocityUpdateThreshold-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetZeroVelocityUpdateThreshold-response>) istream)
  "Deserializes a message object of type '<SetZeroVelocityUpdateThreshold-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetZeroVelocityUpdateThreshold-response>)))
  "Returns string type for a service object of type '<SetZeroVelocityUpdateThreshold-response>"
  "microstrain_inertial_msgs/SetZeroVelocityUpdateThresholdResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetZeroVelocityUpdateThreshold-response)))
  "Returns string type for a service object of type 'SetZeroVelocityUpdateThreshold-response"
  "microstrain_inertial_msgs/SetZeroVelocityUpdateThresholdResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetZeroVelocityUpdateThreshold-response>)))
  "Returns md5sum for a message object of type '<SetZeroVelocityUpdateThreshold-response>"
  "ea1115ed39d8a581530c7c251ee443e6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetZeroVelocityUpdateThreshold-response)))
  "Returns md5sum for a message object of type 'SetZeroVelocityUpdateThreshold-response"
  "ea1115ed39d8a581530c7c251ee443e6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetZeroVelocityUpdateThreshold-response>)))
  "Returns full string definition for message of type '<SetZeroVelocityUpdateThreshold-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetZeroVelocityUpdateThreshold-response)))
  "Returns full string definition for message of type 'SetZeroVelocityUpdateThreshold-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetZeroVelocityUpdateThreshold-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetZeroVelocityUpdateThreshold-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetZeroVelocityUpdateThreshold-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetZeroVelocityUpdateThreshold)))
  'SetZeroVelocityUpdateThreshold-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetZeroVelocityUpdateThreshold)))
  'SetZeroVelocityUpdateThreshold-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetZeroVelocityUpdateThreshold)))
  "Returns string type for a service object of type '<SetZeroVelocityUpdateThreshold>"
  "microstrain_inertial_msgs/SetZeroVelocityUpdateThreshold")