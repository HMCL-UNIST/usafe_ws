; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetMagDipAdaptiveVals-request.msg.html

(cl:defclass <SetMagDipAdaptiveVals-request> (roslisp-msg-protocol:ros-message)
  ((enable
    :reader enable
    :initarg :enable
    :type cl:float
    :initform 0.0)
   (low_pass_cutoff
    :reader low_pass_cutoff
    :initarg :low_pass_cutoff
    :type cl:float
    :initform 0.0)
   (min_1sigma
    :reader min_1sigma
    :initarg :min_1sigma
    :type cl:float
    :initform 0.0)
   (high_limit
    :reader high_limit
    :initarg :high_limit
    :type cl:float
    :initform 0.0)
   (high_limit_1sigma
    :reader high_limit_1sigma
    :initarg :high_limit_1sigma
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetMagDipAdaptiveVals-request (<SetMagDipAdaptiveVals-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetMagDipAdaptiveVals-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetMagDipAdaptiveVals-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetMagDipAdaptiveVals-request> is deprecated: use microstrain_inertial_msgs-srv:SetMagDipAdaptiveVals-request instead.")))

(cl:ensure-generic-function 'enable-val :lambda-list '(m))
(cl:defmethod enable-val ((m <SetMagDipAdaptiveVals-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:enable-val is deprecated.  Use microstrain_inertial_msgs-srv:enable instead.")
  (enable m))

(cl:ensure-generic-function 'low_pass_cutoff-val :lambda-list '(m))
(cl:defmethod low_pass_cutoff-val ((m <SetMagDipAdaptiveVals-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:low_pass_cutoff-val is deprecated.  Use microstrain_inertial_msgs-srv:low_pass_cutoff instead.")
  (low_pass_cutoff m))

(cl:ensure-generic-function 'min_1sigma-val :lambda-list '(m))
(cl:defmethod min_1sigma-val ((m <SetMagDipAdaptiveVals-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:min_1sigma-val is deprecated.  Use microstrain_inertial_msgs-srv:min_1sigma instead.")
  (min_1sigma m))

(cl:ensure-generic-function 'high_limit-val :lambda-list '(m))
(cl:defmethod high_limit-val ((m <SetMagDipAdaptiveVals-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:high_limit-val is deprecated.  Use microstrain_inertial_msgs-srv:high_limit instead.")
  (high_limit m))

(cl:ensure-generic-function 'high_limit_1sigma-val :lambda-list '(m))
(cl:defmethod high_limit_1sigma-val ((m <SetMagDipAdaptiveVals-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:high_limit_1sigma-val is deprecated.  Use microstrain_inertial_msgs-srv:high_limit_1sigma instead.")
  (high_limit_1sigma m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetMagDipAdaptiveVals-request>) ostream)
  "Serializes a message object of type '<SetMagDipAdaptiveVals-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'enable))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'low_pass_cutoff))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'min_1sigma))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'high_limit))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'high_limit_1sigma))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetMagDipAdaptiveVals-request>) istream)
  "Deserializes a message object of type '<SetMagDipAdaptiveVals-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'enable) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'low_pass_cutoff) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'min_1sigma) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'high_limit) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'high_limit_1sigma) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetMagDipAdaptiveVals-request>)))
  "Returns string type for a service object of type '<SetMagDipAdaptiveVals-request>"
  "microstrain_inertial_msgs/SetMagDipAdaptiveValsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetMagDipAdaptiveVals-request)))
  "Returns string type for a service object of type 'SetMagDipAdaptiveVals-request"
  "microstrain_inertial_msgs/SetMagDipAdaptiveValsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetMagDipAdaptiveVals-request>)))
  "Returns md5sum for a message object of type '<SetMagDipAdaptiveVals-request>"
  "c71450f947e543c107e6e7b633ac2f16")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetMagDipAdaptiveVals-request)))
  "Returns md5sum for a message object of type 'SetMagDipAdaptiveVals-request"
  "c71450f947e543c107e6e7b633ac2f16")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetMagDipAdaptiveVals-request>)))
  "Returns full string definition for message of type '<SetMagDipAdaptiveVals-request>"
  (cl:format cl:nil "float32 enable~%float32 low_pass_cutoff~%float32 min_1sigma~%float32 high_limit~%float32 high_limit_1sigma~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetMagDipAdaptiveVals-request)))
  "Returns full string definition for message of type 'SetMagDipAdaptiveVals-request"
  (cl:format cl:nil "float32 enable~%float32 low_pass_cutoff~%float32 min_1sigma~%float32 high_limit~%float32 high_limit_1sigma~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetMagDipAdaptiveVals-request>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetMagDipAdaptiveVals-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetMagDipAdaptiveVals-request
    (cl:cons ':enable (enable msg))
    (cl:cons ':low_pass_cutoff (low_pass_cutoff msg))
    (cl:cons ':min_1sigma (min_1sigma msg))
    (cl:cons ':high_limit (high_limit msg))
    (cl:cons ':high_limit_1sigma (high_limit_1sigma msg))
))
;//! \htmlinclude SetMagDipAdaptiveVals-response.msg.html

(cl:defclass <SetMagDipAdaptiveVals-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetMagDipAdaptiveVals-response (<SetMagDipAdaptiveVals-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetMagDipAdaptiveVals-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetMagDipAdaptiveVals-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetMagDipAdaptiveVals-response> is deprecated: use microstrain_inertial_msgs-srv:SetMagDipAdaptiveVals-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetMagDipAdaptiveVals-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetMagDipAdaptiveVals-response>) ostream)
  "Serializes a message object of type '<SetMagDipAdaptiveVals-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetMagDipAdaptiveVals-response>) istream)
  "Deserializes a message object of type '<SetMagDipAdaptiveVals-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetMagDipAdaptiveVals-response>)))
  "Returns string type for a service object of type '<SetMagDipAdaptiveVals-response>"
  "microstrain_inertial_msgs/SetMagDipAdaptiveValsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetMagDipAdaptiveVals-response)))
  "Returns string type for a service object of type 'SetMagDipAdaptiveVals-response"
  "microstrain_inertial_msgs/SetMagDipAdaptiveValsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetMagDipAdaptiveVals-response>)))
  "Returns md5sum for a message object of type '<SetMagDipAdaptiveVals-response>"
  "c71450f947e543c107e6e7b633ac2f16")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetMagDipAdaptiveVals-response)))
  "Returns md5sum for a message object of type 'SetMagDipAdaptiveVals-response"
  "c71450f947e543c107e6e7b633ac2f16")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetMagDipAdaptiveVals-response>)))
  "Returns full string definition for message of type '<SetMagDipAdaptiveVals-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetMagDipAdaptiveVals-response)))
  "Returns full string definition for message of type 'SetMagDipAdaptiveVals-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetMagDipAdaptiveVals-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetMagDipAdaptiveVals-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetMagDipAdaptiveVals-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetMagDipAdaptiveVals)))
  'SetMagDipAdaptiveVals-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetMagDipAdaptiveVals)))
  'SetMagDipAdaptiveVals-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetMagDipAdaptiveVals)))
  "Returns string type for a service object of type '<SetMagDipAdaptiveVals>"
  "microstrain_inertial_msgs/SetMagDipAdaptiveVals")