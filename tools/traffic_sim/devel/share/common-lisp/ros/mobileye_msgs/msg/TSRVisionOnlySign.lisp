; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude TSRVisionOnlySign.msg.html

(cl:defclass <TSRVisionOnlySign> (roslisp-msg-protocol:ros-message)
  ((vision_only_sign_type_display_1
    :reader vision_only_sign_type_display_1
    :initarg :vision_only_sign_type_display_1
    :type cl:fixnum
    :initform 0)
   (vision_only_sign_type_display_2
    :reader vision_only_sign_type_display_2
    :initarg :vision_only_sign_type_display_2
    :type cl:fixnum
    :initform 0)
   (vision_only_sign_type_display_3
    :reader vision_only_sign_type_display_3
    :initarg :vision_only_sign_type_display_3
    :type cl:fixnum
    :initform 0)
   (vision_only_sign_type_display_4
    :reader vision_only_sign_type_display_4
    :initarg :vision_only_sign_type_display_4
    :type cl:fixnum
    :initform 0)
   (supplementary_sign_type_display_1
    :reader supplementary_sign_type_display_1
    :initarg :supplementary_sign_type_display_1
    :type cl:fixnum
    :initform 0)
   (supplementary_sign_type_display_2
    :reader supplementary_sign_type_display_2
    :initarg :supplementary_sign_type_display_2
    :type cl:fixnum
    :initform 0)
   (supplementary_sign_type_display_3
    :reader supplementary_sign_type_display_3
    :initarg :supplementary_sign_type_display_3
    :type cl:fixnum
    :initform 0)
   (supplementary_sign_type_display_4
    :reader supplementary_sign_type_display_4
    :initarg :supplementary_sign_type_display_4
    :type cl:fixnum
    :initform 0))
)

(cl:defclass TSRVisionOnlySign (<TSRVisionOnlySign>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TSRVisionOnlySign>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TSRVisionOnlySign)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<TSRVisionOnlySign> is deprecated: use mobileye_msgs-msg:TSRVisionOnlySign instead.")))

(cl:ensure-generic-function 'vision_only_sign_type_display_1-val :lambda-list '(m))
(cl:defmethod vision_only_sign_type_display_1-val ((m <TSRVisionOnlySign>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:vision_only_sign_type_display_1-val is deprecated.  Use mobileye_msgs-msg:vision_only_sign_type_display_1 instead.")
  (vision_only_sign_type_display_1 m))

(cl:ensure-generic-function 'vision_only_sign_type_display_2-val :lambda-list '(m))
(cl:defmethod vision_only_sign_type_display_2-val ((m <TSRVisionOnlySign>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:vision_only_sign_type_display_2-val is deprecated.  Use mobileye_msgs-msg:vision_only_sign_type_display_2 instead.")
  (vision_only_sign_type_display_2 m))

(cl:ensure-generic-function 'vision_only_sign_type_display_3-val :lambda-list '(m))
(cl:defmethod vision_only_sign_type_display_3-val ((m <TSRVisionOnlySign>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:vision_only_sign_type_display_3-val is deprecated.  Use mobileye_msgs-msg:vision_only_sign_type_display_3 instead.")
  (vision_only_sign_type_display_3 m))

(cl:ensure-generic-function 'vision_only_sign_type_display_4-val :lambda-list '(m))
(cl:defmethod vision_only_sign_type_display_4-val ((m <TSRVisionOnlySign>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:vision_only_sign_type_display_4-val is deprecated.  Use mobileye_msgs-msg:vision_only_sign_type_display_4 instead.")
  (vision_only_sign_type_display_4 m))

(cl:ensure-generic-function 'supplementary_sign_type_display_1-val :lambda-list '(m))
(cl:defmethod supplementary_sign_type_display_1-val ((m <TSRVisionOnlySign>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:supplementary_sign_type_display_1-val is deprecated.  Use mobileye_msgs-msg:supplementary_sign_type_display_1 instead.")
  (supplementary_sign_type_display_1 m))

(cl:ensure-generic-function 'supplementary_sign_type_display_2-val :lambda-list '(m))
(cl:defmethod supplementary_sign_type_display_2-val ((m <TSRVisionOnlySign>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:supplementary_sign_type_display_2-val is deprecated.  Use mobileye_msgs-msg:supplementary_sign_type_display_2 instead.")
  (supplementary_sign_type_display_2 m))

(cl:ensure-generic-function 'supplementary_sign_type_display_3-val :lambda-list '(m))
(cl:defmethod supplementary_sign_type_display_3-val ((m <TSRVisionOnlySign>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:supplementary_sign_type_display_3-val is deprecated.  Use mobileye_msgs-msg:supplementary_sign_type_display_3 instead.")
  (supplementary_sign_type_display_3 m))

(cl:ensure-generic-function 'supplementary_sign_type_display_4-val :lambda-list '(m))
(cl:defmethod supplementary_sign_type_display_4-val ((m <TSRVisionOnlySign>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:supplementary_sign_type_display_4-val is deprecated.  Use mobileye_msgs-msg:supplementary_sign_type_display_4 instead.")
  (supplementary_sign_type_display_4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TSRVisionOnlySign>) ostream)
  "Serializes a message object of type '<TSRVisionOnlySign>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type_display_1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type_display_2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type_display_3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type_display_4)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type_display_1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type_display_2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type_display_3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type_display_4)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TSRVisionOnlySign>) istream)
  "Deserializes a message object of type '<TSRVisionOnlySign>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type_display_1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type_display_2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type_display_3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vision_only_sign_type_display_4)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type_display_1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type_display_2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type_display_3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'supplementary_sign_type_display_4)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TSRVisionOnlySign>)))
  "Returns string type for a message object of type '<TSRVisionOnlySign>"
  "mobileye_msgs/TSRVisionOnlySign")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TSRVisionOnlySign)))
  "Returns string type for a message object of type 'TSRVisionOnlySign"
  "mobileye_msgs/TSRVisionOnlySign")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TSRVisionOnlySign>)))
  "Returns md5sum for a message object of type '<TSRVisionOnlySign>"
  "81ad54807425b67a5be6ad808e97e8ee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TSRVisionOnlySign)))
  "Returns md5sum for a message object of type 'TSRVisionOnlySign"
  "81ad54807425b67a5be6ad808e97e8ee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TSRVisionOnlySign>)))
  "Returns full string definition for message of type '<TSRVisionOnlySign>"
  (cl:format cl:nil "uint8 vision_only_sign_type_display_1~%uint8 vision_only_sign_type_display_2~%uint8 vision_only_sign_type_display_3~%uint8 vision_only_sign_type_display_4~%~%uint8 supplementary_sign_type_display_1~%uint8 supplementary_sign_type_display_2~%uint8 supplementary_sign_type_display_3~%uint8 supplementary_sign_type_display_4~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TSRVisionOnlySign)))
  "Returns full string definition for message of type 'TSRVisionOnlySign"
  (cl:format cl:nil "uint8 vision_only_sign_type_display_1~%uint8 vision_only_sign_type_display_2~%uint8 vision_only_sign_type_display_3~%uint8 vision_only_sign_type_display_4~%~%uint8 supplementary_sign_type_display_1~%uint8 supplementary_sign_type_display_2~%uint8 supplementary_sign_type_display_3~%uint8 supplementary_sign_type_display_4~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TSRVisionOnlySign>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TSRVisionOnlySign>))
  "Converts a ROS message object to a list"
  (cl:list 'TSRVisionOnlySign
    (cl:cons ':vision_only_sign_type_display_1 (vision_only_sign_type_display_1 msg))
    (cl:cons ':vision_only_sign_type_display_2 (vision_only_sign_type_display_2 msg))
    (cl:cons ':vision_only_sign_type_display_3 (vision_only_sign_type_display_3 msg))
    (cl:cons ':vision_only_sign_type_display_4 (vision_only_sign_type_display_4 msg))
    (cl:cons ':supplementary_sign_type_display_1 (supplementary_sign_type_display_1 msg))
    (cl:cons ':supplementary_sign_type_display_2 (supplementary_sign_type_display_2 msg))
    (cl:cons ':supplementary_sign_type_display_3 (supplementary_sign_type_display_3 msg))
    (cl:cons ':supplementary_sign_type_display_4 (supplementary_sign_type_display_4 msg))
))
