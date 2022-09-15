; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude TSR.msg.html

(cl:defclass <TSR> (roslisp-msg-protocol:ros-message)
  ((vision_only_sign_type
    :reader vision_only_sign_type
    :initarg :vision_only_sign_type
    :type cl:fixnum
    :initform 0)
   (supplementary_sign_type
    :reader supplementary_sign_type
    :initarg :supplementary_sign_type
    :type cl:fixnum
    :initform 0)
   (sign_position_x
    :reader sign_position_x
    :initarg :sign_position_x
    :type cl:float
    :initform 0.0)
   (sign_position_y
    :reader sign_position_y
    :initarg :sign_position_y
    :type cl:float
    :initform 0.0)
   (sign_position_z
    :reader sign_position_z
    :initarg :sign_position_z
    :type cl:float
    :initform 0.0)
   (filter_type
    :reader filter_type
    :initarg :filter_type
    :type cl:fixnum
    :initform 0))
)

(cl:defclass TSR (<TSR>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TSR>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TSR)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<TSR> is deprecated: use mobileye_msgs-msg:TSR instead.")))

(cl:ensure-generic-function 'vision_only_sign_type-val :lambda-list '(m))
(cl:defmethod vision_only_sign_type-val ((m <TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:vision_only_sign_type-val is deprecated.  Use mobileye_msgs-msg:vision_only_sign_type instead.")
  (vision_only_sign_type m))

(cl:ensure-generic-function 'supplementary_sign_type-val :lambda-list '(m))
(cl:defmethod supplementary_sign_type-val ((m <TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:supplementary_sign_type-val is deprecated.  Use mobileye_msgs-msg:supplementary_sign_type instead.")
  (supplementary_sign_type m))

(cl:ensure-generic-function 'sign_position_x-val :lambda-list '(m))
(cl:defmethod sign_position_x-val ((m <TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sign_position_x-val is deprecated.  Use mobileye_msgs-msg:sign_position_x instead.")
  (sign_position_x m))

(cl:ensure-generic-function 'sign_position_y-val :lambda-list '(m))
(cl:defmethod sign_position_y-val ((m <TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sign_position_y-val is deprecated.  Use mobileye_msgs-msg:sign_position_y instead.")
  (sign_position_y m))

(cl:ensure-generic-function 'sign_position_z-val :lambda-list '(m))
(cl:defmethod sign_position_z-val ((m <TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sign_position_z-val is deprecated.  Use mobileye_msgs-msg:sign_position_z instead.")
  (sign_position_z m))

(cl:ensure-generic-function 'filter_type-val :lambda-list '(m))
(cl:defmethod filter_type-val ((m <TSR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:filter_type-val is deprecated.  Use mobileye_msgs-msg:filter_type instead.")
  (filter_type m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TSR>) ostream)
  "Serializes a message object of type '<TSR>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sign_position_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sign_position_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sign_position_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'filter_type)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TSR>) istream)
  "Deserializes a message object of type '<TSR>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sign_position_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sign_position_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sign_position_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'filter_type)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TSR>)))
  "Returns string type for a message object of type '<TSR>"
  "mobileye_msgs/TSR")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TSR)))
  "Returns string type for a message object of type 'TSR"
  "mobileye_msgs/TSR")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TSR>)))
  "Returns md5sum for a message object of type '<TSR>"
  "3b21293c7f6ed978e4a364de1d436a9c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TSR)))
  "Returns md5sum for a message object of type 'TSR"
  "3b21293c7f6ed978e4a364de1d436a9c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TSR>)))
  "Returns full string definition for message of type '<TSR>"
  (cl:format cl:nil "uint8 vision_only_sign_type~%uint8 supplementary_sign_type~%float32 sign_position_x~%float32 sign_position_y~%float32 sign_position_z~%uint8 filter_type~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TSR)))
  "Returns full string definition for message of type 'TSR"
  (cl:format cl:nil "uint8 vision_only_sign_type~%uint8 supplementary_sign_type~%float32 sign_position_x~%float32 sign_position_y~%float32 sign_position_z~%uint8 filter_type~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TSR>))
  (cl:+ 0
     1
     1
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TSR>))
  "Converts a ROS message object to a list"
  (cl:list 'TSR
    (cl:cons ':vision_only_sign_type (vision_only_sign_type msg))
    (cl:cons ':supplementary_sign_type (supplementary_sign_type msg))
    (cl:cons ':sign_position_x (sign_position_x msg))
    (cl:cons ':sign_position_y (sign_position_y msg))
    (cl:cons ':sign_position_z (sign_position_z msg))
    (cl:cons ':filter_type (filter_type msg))
))
