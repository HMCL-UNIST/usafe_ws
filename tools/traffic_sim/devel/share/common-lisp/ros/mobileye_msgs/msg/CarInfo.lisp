; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude CarInfo.msg.html

(cl:defclass <CarInfo> (roslisp-msg-protocol:ros-message)
  ((high_beam
    :reader high_beam
    :initarg :high_beam
    :type cl:boolean
    :initform cl:nil)
   (low_beam
    :reader low_beam
    :initarg :low_beam
    :type cl:boolean
    :initform cl:nil)
   (wipers
    :reader wipers
    :initarg :wipers
    :type cl:boolean
    :initform cl:nil)
   (right_signal
    :reader right_signal
    :initarg :right_signal
    :type cl:boolean
    :initform cl:nil)
   (left_signal
    :reader left_signal
    :initarg :left_signal
    :type cl:boolean
    :initform cl:nil)
   (brake_signal
    :reader brake_signal
    :initarg :brake_signal
    :type cl:boolean
    :initform cl:nil)
   (wipers_available
    :reader wipers_available
    :initarg :wipers_available
    :type cl:boolean
    :initform cl:nil)
   (low_beam_available
    :reader low_beam_available
    :initarg :low_beam_available
    :type cl:boolean
    :initform cl:nil)
   (high_beam_available
    :reader high_beam_available
    :initarg :high_beam_available
    :type cl:boolean
    :initform cl:nil)
   (right_blink_available
    :reader right_blink_available
    :initarg :right_blink_available
    :type cl:boolean
    :initform cl:nil)
   (left_blink_available
    :reader left_blink_available
    :initarg :left_blink_available
    :type cl:boolean
    :initform cl:nil)
   (brake_available
    :reader brake_available
    :initarg :brake_available
    :type cl:boolean
    :initform cl:nil)
   (speed_available
    :reader speed_available
    :initarg :speed_available
    :type cl:boolean
    :initform cl:nil)
   (speed
    :reader speed
    :initarg :speed
    :type cl:fixnum
    :initform 0)
   (shield_plus_settings
    :reader shield_plus_settings
    :initarg :shield_plus_settings
    :type cl:fixnum
    :initform 0))
)

(cl:defclass CarInfo (<CarInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CarInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CarInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<CarInfo> is deprecated: use mobileye_msgs-msg:CarInfo instead.")))

(cl:ensure-generic-function 'high_beam-val :lambda-list '(m))
(cl:defmethod high_beam-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:high_beam-val is deprecated.  Use mobileye_msgs-msg:high_beam instead.")
  (high_beam m))

(cl:ensure-generic-function 'low_beam-val :lambda-list '(m))
(cl:defmethod low_beam-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:low_beam-val is deprecated.  Use mobileye_msgs-msg:low_beam instead.")
  (low_beam m))

(cl:ensure-generic-function 'wipers-val :lambda-list '(m))
(cl:defmethod wipers-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:wipers-val is deprecated.  Use mobileye_msgs-msg:wipers instead.")
  (wipers m))

(cl:ensure-generic-function 'right_signal-val :lambda-list '(m))
(cl:defmethod right_signal-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:right_signal-val is deprecated.  Use mobileye_msgs-msg:right_signal instead.")
  (right_signal m))

(cl:ensure-generic-function 'left_signal-val :lambda-list '(m))
(cl:defmethod left_signal-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:left_signal-val is deprecated.  Use mobileye_msgs-msg:left_signal instead.")
  (left_signal m))

(cl:ensure-generic-function 'brake_signal-val :lambda-list '(m))
(cl:defmethod brake_signal-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:brake_signal-val is deprecated.  Use mobileye_msgs-msg:brake_signal instead.")
  (brake_signal m))

(cl:ensure-generic-function 'wipers_available-val :lambda-list '(m))
(cl:defmethod wipers_available-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:wipers_available-val is deprecated.  Use mobileye_msgs-msg:wipers_available instead.")
  (wipers_available m))

(cl:ensure-generic-function 'low_beam_available-val :lambda-list '(m))
(cl:defmethod low_beam_available-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:low_beam_available-val is deprecated.  Use mobileye_msgs-msg:low_beam_available instead.")
  (low_beam_available m))

(cl:ensure-generic-function 'high_beam_available-val :lambda-list '(m))
(cl:defmethod high_beam_available-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:high_beam_available-val is deprecated.  Use mobileye_msgs-msg:high_beam_available instead.")
  (high_beam_available m))

(cl:ensure-generic-function 'right_blink_available-val :lambda-list '(m))
(cl:defmethod right_blink_available-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:right_blink_available-val is deprecated.  Use mobileye_msgs-msg:right_blink_available instead.")
  (right_blink_available m))

(cl:ensure-generic-function 'left_blink_available-val :lambda-list '(m))
(cl:defmethod left_blink_available-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:left_blink_available-val is deprecated.  Use mobileye_msgs-msg:left_blink_available instead.")
  (left_blink_available m))

(cl:ensure-generic-function 'brake_available-val :lambda-list '(m))
(cl:defmethod brake_available-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:brake_available-val is deprecated.  Use mobileye_msgs-msg:brake_available instead.")
  (brake_available m))

(cl:ensure-generic-function 'speed_available-val :lambda-list '(m))
(cl:defmethod speed_available-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:speed_available-val is deprecated.  Use mobileye_msgs-msg:speed_available instead.")
  (speed_available m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:speed-val is deprecated.  Use mobileye_msgs-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'shield_plus_settings-val :lambda-list '(m))
(cl:defmethod shield_plus_settings-val ((m <CarInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:shield_plus_settings-val is deprecated.  Use mobileye_msgs-msg:shield_plus_settings instead.")
  (shield_plus_settings m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CarInfo>) ostream)
  "Serializes a message object of type '<CarInfo>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'high_beam) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'low_beam) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'wipers) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'right_signal) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'left_signal) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'brake_signal) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'wipers_available) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'low_beam_available) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'high_beam_available) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'right_blink_available) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'left_blink_available) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'brake_available) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'speed_available) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'speed)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'shield_plus_settings)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CarInfo>) istream)
  "Deserializes a message object of type '<CarInfo>"
    (cl:setf (cl:slot-value msg 'high_beam) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'low_beam) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'wipers) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'right_signal) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'left_signal) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'brake_signal) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'wipers_available) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'low_beam_available) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'high_beam_available) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'right_blink_available) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'left_blink_available) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'brake_available) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'speed_available) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'speed)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'shield_plus_settings)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CarInfo>)))
  "Returns string type for a message object of type '<CarInfo>"
  "mobileye_msgs/CarInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CarInfo)))
  "Returns string type for a message object of type 'CarInfo"
  "mobileye_msgs/CarInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CarInfo>)))
  "Returns md5sum for a message object of type '<CarInfo>"
  "50aff2fafecf310fa3fc9bcf4c9a5c85")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CarInfo)))
  "Returns md5sum for a message object of type 'CarInfo"
  "50aff2fafecf310fa3fc9bcf4c9a5c85")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CarInfo>)))
  "Returns full string definition for message of type '<CarInfo>"
  (cl:format cl:nil "bool high_beam~%bool low_beam~%bool wipers~%bool right_signal~%bool left_signal~%bool brake_signal~%bool wipers_available~%bool low_beam_available~%bool high_beam_available~%bool right_blink_available~%bool left_blink_available~%bool brake_available~%bool speed_available~%uint8 speed~%uint8 shield_plus_settings~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CarInfo)))
  "Returns full string definition for message of type 'CarInfo"
  (cl:format cl:nil "bool high_beam~%bool low_beam~%bool wipers~%bool right_signal~%bool left_signal~%bool brake_signal~%bool wipers_available~%bool low_beam_available~%bool high_beam_available~%bool right_blink_available~%bool left_blink_available~%bool brake_available~%bool speed_available~%uint8 speed~%uint8 shield_plus_settings~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CarInfo>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CarInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'CarInfo
    (cl:cons ':high_beam (high_beam msg))
    (cl:cons ':low_beam (low_beam msg))
    (cl:cons ':wipers (wipers msg))
    (cl:cons ':right_signal (right_signal msg))
    (cl:cons ':left_signal (left_signal msg))
    (cl:cons ':brake_signal (brake_signal msg))
    (cl:cons ':wipers_available (wipers_available msg))
    (cl:cons ':low_beam_available (low_beam_available msg))
    (cl:cons ':high_beam_available (high_beam_available msg))
    (cl:cons ':right_blink_available (right_blink_available msg))
    (cl:cons ':left_blink_available (left_blink_available msg))
    (cl:cons ':brake_available (brake_available msg))
    (cl:cons ':speed_available (speed_available msg))
    (cl:cons ':speed (speed msg))
    (cl:cons ':shield_plus_settings (shield_plus_settings msg))
))
