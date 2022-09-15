; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude ExternalHeadingUpdate-request.msg.html

(cl:defclass <ExternalHeadingUpdate-request> (roslisp-msg-protocol:ros-message)
  ((gps_tow
    :reader gps_tow
    :initarg :gps_tow
    :type cl:float
    :initform 0.0)
   (gps_week_number
    :reader gps_week_number
    :initarg :gps_week_number
    :type cl:fixnum
    :initform 0)
   (heading_rad
    :reader heading_rad
    :initarg :heading_rad
    :type cl:float
    :initform 0.0)
   (heading_1sigma_rad
    :reader heading_1sigma_rad
    :initarg :heading_1sigma_rad
    :type cl:float
    :initform 0.0)
   (heading_type
    :reader heading_type
    :initarg :heading_type
    :type cl:fixnum
    :initform 0)
   (use_time
    :reader use_time
    :initarg :use_time
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass ExternalHeadingUpdate-request (<ExternalHeadingUpdate-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ExternalHeadingUpdate-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ExternalHeadingUpdate-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<ExternalHeadingUpdate-request> is deprecated: use microstrain_inertial_msgs-srv:ExternalHeadingUpdate-request instead.")))

(cl:ensure-generic-function 'gps_tow-val :lambda-list '(m))
(cl:defmethod gps_tow-val ((m <ExternalHeadingUpdate-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:gps_tow-val is deprecated.  Use microstrain_inertial_msgs-srv:gps_tow instead.")
  (gps_tow m))

(cl:ensure-generic-function 'gps_week_number-val :lambda-list '(m))
(cl:defmethod gps_week_number-val ((m <ExternalHeadingUpdate-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:gps_week_number-val is deprecated.  Use microstrain_inertial_msgs-srv:gps_week_number instead.")
  (gps_week_number m))

(cl:ensure-generic-function 'heading_rad-val :lambda-list '(m))
(cl:defmethod heading_rad-val ((m <ExternalHeadingUpdate-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:heading_rad-val is deprecated.  Use microstrain_inertial_msgs-srv:heading_rad instead.")
  (heading_rad m))

(cl:ensure-generic-function 'heading_1sigma_rad-val :lambda-list '(m))
(cl:defmethod heading_1sigma_rad-val ((m <ExternalHeadingUpdate-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:heading_1sigma_rad-val is deprecated.  Use microstrain_inertial_msgs-srv:heading_1sigma_rad instead.")
  (heading_1sigma_rad m))

(cl:ensure-generic-function 'heading_type-val :lambda-list '(m))
(cl:defmethod heading_type-val ((m <ExternalHeadingUpdate-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:heading_type-val is deprecated.  Use microstrain_inertial_msgs-srv:heading_type instead.")
  (heading_type m))

(cl:ensure-generic-function 'use_time-val :lambda-list '(m))
(cl:defmethod use_time-val ((m <ExternalHeadingUpdate-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:use_time-val is deprecated.  Use microstrain_inertial_msgs-srv:use_time instead.")
  (use_time m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<ExternalHeadingUpdate-request>)))
    "Constants for message type '<ExternalHeadingUpdate-request>"
  '((:HEADING_TYPE_TRUE . 1)
    (:HEADING_TYPE_MAGNETIC . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'ExternalHeadingUpdate-request)))
    "Constants for message type 'ExternalHeadingUpdate-request"
  '((:HEADING_TYPE_TRUE . 1)
    (:HEADING_TYPE_MAGNETIC . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ExternalHeadingUpdate-request>) ostream)
  "Serializes a message object of type '<ExternalHeadingUpdate-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gps_tow))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_week_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_week_number)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_rad))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_1sigma_rad))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'heading_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'heading_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'use_time) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ExternalHeadingUpdate-request>) istream)
  "Deserializes a message object of type '<ExternalHeadingUpdate-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gps_tow) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_week_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_week_number)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_rad) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_1sigma_rad) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'heading_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'heading_type)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'use_time) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ExternalHeadingUpdate-request>)))
  "Returns string type for a service object of type '<ExternalHeadingUpdate-request>"
  "microstrain_inertial_msgs/ExternalHeadingUpdateRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ExternalHeadingUpdate-request)))
  "Returns string type for a service object of type 'ExternalHeadingUpdate-request"
  "microstrain_inertial_msgs/ExternalHeadingUpdateRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ExternalHeadingUpdate-request>)))
  "Returns md5sum for a message object of type '<ExternalHeadingUpdate-request>"
  "c947f180cef8662c7c56b8c41afcba62")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ExternalHeadingUpdate-request)))
  "Returns md5sum for a message object of type 'ExternalHeadingUpdate-request"
  "c947f180cef8662c7c56b8c41afcba62")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ExternalHeadingUpdate-request>)))
  "Returns full string definition for message of type '<ExternalHeadingUpdate-request>"
  (cl:format cl:nil "float64 gps_tow~%uint16  gps_week_number~%float32 heading_rad~%float32 heading_1sigma_rad~%uint16  heading_type~%bool    use_time~%uint16 HEADING_TYPE_TRUE      = 1  ~%uint16 HEADING_TYPE_MAGNETIC  = 2  ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ExternalHeadingUpdate-request)))
  "Returns full string definition for message of type 'ExternalHeadingUpdate-request"
  (cl:format cl:nil "float64 gps_tow~%uint16  gps_week_number~%float32 heading_rad~%float32 heading_1sigma_rad~%uint16  heading_type~%bool    use_time~%uint16 HEADING_TYPE_TRUE      = 1  ~%uint16 HEADING_TYPE_MAGNETIC  = 2  ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ExternalHeadingUpdate-request>))
  (cl:+ 0
     8
     2
     4
     4
     2
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ExternalHeadingUpdate-request>))
  "Converts a ROS message object to a list"
  (cl:list 'ExternalHeadingUpdate-request
    (cl:cons ':gps_tow (gps_tow msg))
    (cl:cons ':gps_week_number (gps_week_number msg))
    (cl:cons ':heading_rad (heading_rad msg))
    (cl:cons ':heading_1sigma_rad (heading_1sigma_rad msg))
    (cl:cons ':heading_type (heading_type msg))
    (cl:cons ':use_time (use_time msg))
))
;//! \htmlinclude ExternalHeadingUpdate-response.msg.html

(cl:defclass <ExternalHeadingUpdate-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass ExternalHeadingUpdate-response (<ExternalHeadingUpdate-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ExternalHeadingUpdate-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ExternalHeadingUpdate-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<ExternalHeadingUpdate-response> is deprecated: use microstrain_inertial_msgs-srv:ExternalHeadingUpdate-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <ExternalHeadingUpdate-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ExternalHeadingUpdate-response>) ostream)
  "Serializes a message object of type '<ExternalHeadingUpdate-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ExternalHeadingUpdate-response>) istream)
  "Deserializes a message object of type '<ExternalHeadingUpdate-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ExternalHeadingUpdate-response>)))
  "Returns string type for a service object of type '<ExternalHeadingUpdate-response>"
  "microstrain_inertial_msgs/ExternalHeadingUpdateResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ExternalHeadingUpdate-response)))
  "Returns string type for a service object of type 'ExternalHeadingUpdate-response"
  "microstrain_inertial_msgs/ExternalHeadingUpdateResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ExternalHeadingUpdate-response>)))
  "Returns md5sum for a message object of type '<ExternalHeadingUpdate-response>"
  "c947f180cef8662c7c56b8c41afcba62")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ExternalHeadingUpdate-response)))
  "Returns md5sum for a message object of type 'ExternalHeadingUpdate-response"
  "c947f180cef8662c7c56b8c41afcba62")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ExternalHeadingUpdate-response>)))
  "Returns full string definition for message of type '<ExternalHeadingUpdate-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ExternalHeadingUpdate-response)))
  "Returns full string definition for message of type 'ExternalHeadingUpdate-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ExternalHeadingUpdate-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ExternalHeadingUpdate-response>))
  "Converts a ROS message object to a list"
  (cl:list 'ExternalHeadingUpdate-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'ExternalHeadingUpdate)))
  'ExternalHeadingUpdate-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'ExternalHeadingUpdate)))
  'ExternalHeadingUpdate-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ExternalHeadingUpdate)))
  "Returns string type for a service object of type '<ExternalHeadingUpdate>"
  "microstrain_inertial_msgs/ExternalHeadingUpdate")