; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetComplementaryFilter-request.msg.html

(cl:defclass <SetComplementaryFilter-request> (roslisp-msg-protocol:ros-message)
  ((north_comp_enable
    :reader north_comp_enable
    :initarg :north_comp_enable
    :type cl:fixnum
    :initform 0)
   (up_comp_enable
    :reader up_comp_enable
    :initarg :up_comp_enable
    :type cl:fixnum
    :initform 0)
   (north_comp_time_const
    :reader north_comp_time_const
    :initarg :north_comp_time_const
    :type cl:float
    :initform 0.0)
   (up_comp_time_const
    :reader up_comp_time_const
    :initarg :up_comp_time_const
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetComplementaryFilter-request (<SetComplementaryFilter-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetComplementaryFilter-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetComplementaryFilter-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetComplementaryFilter-request> is deprecated: use microstrain_inertial_msgs-srv:SetComplementaryFilter-request instead.")))

(cl:ensure-generic-function 'north_comp_enable-val :lambda-list '(m))
(cl:defmethod north_comp_enable-val ((m <SetComplementaryFilter-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:north_comp_enable-val is deprecated.  Use microstrain_inertial_msgs-srv:north_comp_enable instead.")
  (north_comp_enable m))

(cl:ensure-generic-function 'up_comp_enable-val :lambda-list '(m))
(cl:defmethod up_comp_enable-val ((m <SetComplementaryFilter-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:up_comp_enable-val is deprecated.  Use microstrain_inertial_msgs-srv:up_comp_enable instead.")
  (up_comp_enable m))

(cl:ensure-generic-function 'north_comp_time_const-val :lambda-list '(m))
(cl:defmethod north_comp_time_const-val ((m <SetComplementaryFilter-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:north_comp_time_const-val is deprecated.  Use microstrain_inertial_msgs-srv:north_comp_time_const instead.")
  (north_comp_time_const m))

(cl:ensure-generic-function 'up_comp_time_const-val :lambda-list '(m))
(cl:defmethod up_comp_time_const-val ((m <SetComplementaryFilter-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:up_comp_time_const-val is deprecated.  Use microstrain_inertial_msgs-srv:up_comp_time_const instead.")
  (up_comp_time_const m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetComplementaryFilter-request>) ostream)
  "Serializes a message object of type '<SetComplementaryFilter-request>"
  (cl:let* ((signed (cl:slot-value msg 'north_comp_enable)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'up_comp_enable)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'north_comp_time_const))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'up_comp_time_const))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetComplementaryFilter-request>) istream)
  "Deserializes a message object of type '<SetComplementaryFilter-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'north_comp_enable) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'up_comp_enable) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'north_comp_time_const) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'up_comp_time_const) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetComplementaryFilter-request>)))
  "Returns string type for a service object of type '<SetComplementaryFilter-request>"
  "microstrain_inertial_msgs/SetComplementaryFilterRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetComplementaryFilter-request)))
  "Returns string type for a service object of type 'SetComplementaryFilter-request"
  "microstrain_inertial_msgs/SetComplementaryFilterRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetComplementaryFilter-request>)))
  "Returns md5sum for a message object of type '<SetComplementaryFilter-request>"
  "f2496add5126d026ef6c94d30c11db4c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetComplementaryFilter-request)))
  "Returns md5sum for a message object of type 'SetComplementaryFilter-request"
  "f2496add5126d026ef6c94d30c11db4c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetComplementaryFilter-request>)))
  "Returns full string definition for message of type '<SetComplementaryFilter-request>"
  (cl:format cl:nil "int8 north_comp_enable~%int8 up_comp_enable~%float32 north_comp_time_const~%float32 up_comp_time_const~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetComplementaryFilter-request)))
  "Returns full string definition for message of type 'SetComplementaryFilter-request"
  (cl:format cl:nil "int8 north_comp_enable~%int8 up_comp_enable~%float32 north_comp_time_const~%float32 up_comp_time_const~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetComplementaryFilter-request>))
  (cl:+ 0
     1
     1
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetComplementaryFilter-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetComplementaryFilter-request
    (cl:cons ':north_comp_enable (north_comp_enable msg))
    (cl:cons ':up_comp_enable (up_comp_enable msg))
    (cl:cons ':north_comp_time_const (north_comp_time_const msg))
    (cl:cons ':up_comp_time_const (up_comp_time_const msg))
))
;//! \htmlinclude SetComplementaryFilter-response.msg.html

(cl:defclass <SetComplementaryFilter-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetComplementaryFilter-response (<SetComplementaryFilter-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetComplementaryFilter-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetComplementaryFilter-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetComplementaryFilter-response> is deprecated: use microstrain_inertial_msgs-srv:SetComplementaryFilter-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetComplementaryFilter-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetComplementaryFilter-response>) ostream)
  "Serializes a message object of type '<SetComplementaryFilter-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetComplementaryFilter-response>) istream)
  "Deserializes a message object of type '<SetComplementaryFilter-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetComplementaryFilter-response>)))
  "Returns string type for a service object of type '<SetComplementaryFilter-response>"
  "microstrain_inertial_msgs/SetComplementaryFilterResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetComplementaryFilter-response)))
  "Returns string type for a service object of type 'SetComplementaryFilter-response"
  "microstrain_inertial_msgs/SetComplementaryFilterResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetComplementaryFilter-response>)))
  "Returns md5sum for a message object of type '<SetComplementaryFilter-response>"
  "f2496add5126d026ef6c94d30c11db4c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetComplementaryFilter-response)))
  "Returns md5sum for a message object of type 'SetComplementaryFilter-response"
  "f2496add5126d026ef6c94d30c11db4c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetComplementaryFilter-response>)))
  "Returns full string definition for message of type '<SetComplementaryFilter-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetComplementaryFilter-response)))
  "Returns full string definition for message of type 'SetComplementaryFilter-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetComplementaryFilter-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetComplementaryFilter-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetComplementaryFilter-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetComplementaryFilter)))
  'SetComplementaryFilter-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetComplementaryFilter)))
  'SetComplementaryFilter-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetComplementaryFilter)))
  "Returns string type for a service object of type '<SetComplementaryFilter>"
  "microstrain_inertial_msgs/SetComplementaryFilter")