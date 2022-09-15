; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetZeroAngleUpdateThreshold-request.msg.html

(cl:defclass <GetZeroAngleUpdateThreshold-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetZeroAngleUpdateThreshold-request (<GetZeroAngleUpdateThreshold-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetZeroAngleUpdateThreshold-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetZeroAngleUpdateThreshold-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetZeroAngleUpdateThreshold-request> is deprecated: use microstrain_inertial_msgs-srv:GetZeroAngleUpdateThreshold-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetZeroAngleUpdateThreshold-request>) ostream)
  "Serializes a message object of type '<GetZeroAngleUpdateThreshold-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetZeroAngleUpdateThreshold-request>) istream)
  "Deserializes a message object of type '<GetZeroAngleUpdateThreshold-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetZeroAngleUpdateThreshold-request>)))
  "Returns string type for a service object of type '<GetZeroAngleUpdateThreshold-request>"
  "microstrain_inertial_msgs/GetZeroAngleUpdateThresholdRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetZeroAngleUpdateThreshold-request)))
  "Returns string type for a service object of type 'GetZeroAngleUpdateThreshold-request"
  "microstrain_inertial_msgs/GetZeroAngleUpdateThresholdRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetZeroAngleUpdateThreshold-request>)))
  "Returns md5sum for a message object of type '<GetZeroAngleUpdateThreshold-request>"
  "1d55bd0c555abfd31bce740efa684526")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetZeroAngleUpdateThreshold-request)))
  "Returns md5sum for a message object of type 'GetZeroAngleUpdateThreshold-request"
  "1d55bd0c555abfd31bce740efa684526")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetZeroAngleUpdateThreshold-request>)))
  "Returns full string definition for message of type '<GetZeroAngleUpdateThreshold-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetZeroAngleUpdateThreshold-request)))
  "Returns full string definition for message of type 'GetZeroAngleUpdateThreshold-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetZeroAngleUpdateThreshold-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetZeroAngleUpdateThreshold-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetZeroAngleUpdateThreshold-request
))
;//! \htmlinclude GetZeroAngleUpdateThreshold-response.msg.html

(cl:defclass <GetZeroAngleUpdateThreshold-response> (roslisp-msg-protocol:ros-message)
  ((enable
    :reader enable
    :initarg :enable
    :type cl:fixnum
    :initform 0)
   (threshold
    :reader threshold
    :initarg :threshold
    :type cl:float
    :initform 0.0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetZeroAngleUpdateThreshold-response (<GetZeroAngleUpdateThreshold-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetZeroAngleUpdateThreshold-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetZeroAngleUpdateThreshold-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetZeroAngleUpdateThreshold-response> is deprecated: use microstrain_inertial_msgs-srv:GetZeroAngleUpdateThreshold-response instead.")))

(cl:ensure-generic-function 'enable-val :lambda-list '(m))
(cl:defmethod enable-val ((m <GetZeroAngleUpdateThreshold-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:enable-val is deprecated.  Use microstrain_inertial_msgs-srv:enable instead.")
  (enable m))

(cl:ensure-generic-function 'threshold-val :lambda-list '(m))
(cl:defmethod threshold-val ((m <GetZeroAngleUpdateThreshold-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:threshold-val is deprecated.  Use microstrain_inertial_msgs-srv:threshold instead.")
  (threshold m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetZeroAngleUpdateThreshold-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetZeroAngleUpdateThreshold-response>) ostream)
  "Serializes a message object of type '<GetZeroAngleUpdateThreshold-response>"
  (cl:let* ((signed (cl:slot-value msg 'enable)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'threshold))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetZeroAngleUpdateThreshold-response>) istream)
  "Deserializes a message object of type '<GetZeroAngleUpdateThreshold-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enable) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'threshold) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetZeroAngleUpdateThreshold-response>)))
  "Returns string type for a service object of type '<GetZeroAngleUpdateThreshold-response>"
  "microstrain_inertial_msgs/GetZeroAngleUpdateThresholdResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetZeroAngleUpdateThreshold-response)))
  "Returns string type for a service object of type 'GetZeroAngleUpdateThreshold-response"
  "microstrain_inertial_msgs/GetZeroAngleUpdateThresholdResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetZeroAngleUpdateThreshold-response>)))
  "Returns md5sum for a message object of type '<GetZeroAngleUpdateThreshold-response>"
  "1d55bd0c555abfd31bce740efa684526")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetZeroAngleUpdateThreshold-response)))
  "Returns md5sum for a message object of type 'GetZeroAngleUpdateThreshold-response"
  "1d55bd0c555abfd31bce740efa684526")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetZeroAngleUpdateThreshold-response>)))
  "Returns full string definition for message of type '<GetZeroAngleUpdateThreshold-response>"
  (cl:format cl:nil "int8 enable~%float32 threshold~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetZeroAngleUpdateThreshold-response)))
  "Returns full string definition for message of type 'GetZeroAngleUpdateThreshold-response"
  (cl:format cl:nil "int8 enable~%float32 threshold~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetZeroAngleUpdateThreshold-response>))
  (cl:+ 0
     1
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetZeroAngleUpdateThreshold-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetZeroAngleUpdateThreshold-response
    (cl:cons ':enable (enable msg))
    (cl:cons ':threshold (threshold msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetZeroAngleUpdateThreshold)))
  'GetZeroAngleUpdateThreshold-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetZeroAngleUpdateThreshold)))
  'GetZeroAngleUpdateThreshold-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetZeroAngleUpdateThreshold)))
  "Returns string type for a service object of type '<GetZeroAngleUpdateThreshold>"
  "microstrain_inertial_msgs/GetZeroAngleUpdateThreshold")