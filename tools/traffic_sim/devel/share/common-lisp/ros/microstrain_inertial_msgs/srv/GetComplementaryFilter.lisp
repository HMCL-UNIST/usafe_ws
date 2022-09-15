; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetComplementaryFilter-request.msg.html

(cl:defclass <GetComplementaryFilter-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetComplementaryFilter-request (<GetComplementaryFilter-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetComplementaryFilter-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetComplementaryFilter-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetComplementaryFilter-request> is deprecated: use microstrain_inertial_msgs-srv:GetComplementaryFilter-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetComplementaryFilter-request>) ostream)
  "Serializes a message object of type '<GetComplementaryFilter-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetComplementaryFilter-request>) istream)
  "Deserializes a message object of type '<GetComplementaryFilter-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetComplementaryFilter-request>)))
  "Returns string type for a service object of type '<GetComplementaryFilter-request>"
  "microstrain_inertial_msgs/GetComplementaryFilterRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetComplementaryFilter-request)))
  "Returns string type for a service object of type 'GetComplementaryFilter-request"
  "microstrain_inertial_msgs/GetComplementaryFilterRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetComplementaryFilter-request>)))
  "Returns md5sum for a message object of type '<GetComplementaryFilter-request>"
  "182da770aa33d31e1eeca2d1e7ed5c19")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetComplementaryFilter-request)))
  "Returns md5sum for a message object of type 'GetComplementaryFilter-request"
  "182da770aa33d31e1eeca2d1e7ed5c19")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetComplementaryFilter-request>)))
  "Returns full string definition for message of type '<GetComplementaryFilter-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetComplementaryFilter-request)))
  "Returns full string definition for message of type 'GetComplementaryFilter-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetComplementaryFilter-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetComplementaryFilter-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetComplementaryFilter-request
))
;//! \htmlinclude GetComplementaryFilter-response.msg.html

(cl:defclass <GetComplementaryFilter-response> (roslisp-msg-protocol:ros-message)
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
    :initform 0.0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetComplementaryFilter-response (<GetComplementaryFilter-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetComplementaryFilter-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetComplementaryFilter-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetComplementaryFilter-response> is deprecated: use microstrain_inertial_msgs-srv:GetComplementaryFilter-response instead.")))

(cl:ensure-generic-function 'north_comp_enable-val :lambda-list '(m))
(cl:defmethod north_comp_enable-val ((m <GetComplementaryFilter-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:north_comp_enable-val is deprecated.  Use microstrain_inertial_msgs-srv:north_comp_enable instead.")
  (north_comp_enable m))

(cl:ensure-generic-function 'up_comp_enable-val :lambda-list '(m))
(cl:defmethod up_comp_enable-val ((m <GetComplementaryFilter-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:up_comp_enable-val is deprecated.  Use microstrain_inertial_msgs-srv:up_comp_enable instead.")
  (up_comp_enable m))

(cl:ensure-generic-function 'north_comp_time_const-val :lambda-list '(m))
(cl:defmethod north_comp_time_const-val ((m <GetComplementaryFilter-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:north_comp_time_const-val is deprecated.  Use microstrain_inertial_msgs-srv:north_comp_time_const instead.")
  (north_comp_time_const m))

(cl:ensure-generic-function 'up_comp_time_const-val :lambda-list '(m))
(cl:defmethod up_comp_time_const-val ((m <GetComplementaryFilter-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:up_comp_time_const-val is deprecated.  Use microstrain_inertial_msgs-srv:up_comp_time_const instead.")
  (up_comp_time_const m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetComplementaryFilter-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetComplementaryFilter-response>) ostream)
  "Serializes a message object of type '<GetComplementaryFilter-response>"
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetComplementaryFilter-response>) istream)
  "Deserializes a message object of type '<GetComplementaryFilter-response>"
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
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetComplementaryFilter-response>)))
  "Returns string type for a service object of type '<GetComplementaryFilter-response>"
  "microstrain_inertial_msgs/GetComplementaryFilterResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetComplementaryFilter-response)))
  "Returns string type for a service object of type 'GetComplementaryFilter-response"
  "microstrain_inertial_msgs/GetComplementaryFilterResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetComplementaryFilter-response>)))
  "Returns md5sum for a message object of type '<GetComplementaryFilter-response>"
  "182da770aa33d31e1eeca2d1e7ed5c19")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetComplementaryFilter-response)))
  "Returns md5sum for a message object of type 'GetComplementaryFilter-response"
  "182da770aa33d31e1eeca2d1e7ed5c19")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetComplementaryFilter-response>)))
  "Returns full string definition for message of type '<GetComplementaryFilter-response>"
  (cl:format cl:nil "int8 north_comp_enable~%int8 up_comp_enable~%float32 north_comp_time_const~%float32 up_comp_time_const~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetComplementaryFilter-response)))
  "Returns full string definition for message of type 'GetComplementaryFilter-response"
  (cl:format cl:nil "int8 north_comp_enable~%int8 up_comp_enable~%float32 north_comp_time_const~%float32 up_comp_time_const~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetComplementaryFilter-response>))
  (cl:+ 0
     1
     1
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetComplementaryFilter-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetComplementaryFilter-response
    (cl:cons ':north_comp_enable (north_comp_enable msg))
    (cl:cons ':up_comp_enable (up_comp_enable msg))
    (cl:cons ':north_comp_time_const (north_comp_time_const msg))
    (cl:cons ':up_comp_time_const (up_comp_time_const msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetComplementaryFilter)))
  'GetComplementaryFilter-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetComplementaryFilter)))
  'GetComplementaryFilter-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetComplementaryFilter)))
  "Returns string type for a service object of type '<GetComplementaryFilter>"
  "microstrain_inertial_msgs/GetComplementaryFilter")