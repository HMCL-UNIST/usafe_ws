; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude RTKStatusV1.msg.html

(cl:defclass <RTKStatusV1> (roslisp-msg-protocol:ros-message)
  ((gps_tow
    :reader gps_tow
    :initarg :gps_tow
    :type cl:float
    :initform 0.0)
   (gps_week
    :reader gps_week
    :initarg :gps_week
    :type cl:fixnum
    :initform 0)
   (epoch_status
    :reader epoch_status
    :initarg :epoch_status
    :type cl:fixnum
    :initform 0)
   (dongle_version
    :reader dongle_version
    :initarg :dongle_version
    :type cl:fixnum
    :initform 0)
   (dongle_controller_state
    :reader dongle_controller_state
    :initarg :dongle_controller_state
    :type cl:fixnum
    :initform 0)
   (dongle_platform_state
    :reader dongle_platform_state
    :initarg :dongle_platform_state
    :type cl:fixnum
    :initform 0)
   (dongle_controller_status
    :reader dongle_controller_status
    :initarg :dongle_controller_status
    :type cl:fixnum
    :initform 0)
   (dongle_platform_status
    :reader dongle_platform_status
    :initarg :dongle_platform_status
    :type cl:fixnum
    :initform 0)
   (dongle_reset_reason
    :reader dongle_reset_reason
    :initarg :dongle_reset_reason
    :type cl:fixnum
    :initform 0)
   (dongle_signal_quality
    :reader dongle_signal_quality
    :initarg :dongle_signal_quality
    :type cl:fixnum
    :initform 0)
   (gps_correction_latency
    :reader gps_correction_latency
    :initarg :gps_correction_latency
    :type cl:float
    :initform 0.0)
   (glonass_correction_latency
    :reader glonass_correction_latency
    :initarg :glonass_correction_latency
    :type cl:float
    :initform 0.0)
   (galileo_correction_latency
    :reader galileo_correction_latency
    :initarg :galileo_correction_latency
    :type cl:float
    :initform 0.0)
   (beidou_correction_latency
    :reader beidou_correction_latency
    :initarg :beidou_correction_latency
    :type cl:float
    :initform 0.0)
   (raw_status_flags
    :reader raw_status_flags
    :initarg :raw_status_flags
    :type cl:integer
    :initform 0))
)

(cl:defclass RTKStatusV1 (<RTKStatusV1>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTKStatusV1>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTKStatusV1)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<RTKStatusV1> is deprecated: use microstrain_inertial_msgs-msg:RTKStatusV1 instead.")))

(cl:ensure-generic-function 'gps_tow-val :lambda-list '(m))
(cl:defmethod gps_tow-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_tow-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_tow instead.")
  (gps_tow m))

(cl:ensure-generic-function 'gps_week-val :lambda-list '(m))
(cl:defmethod gps_week-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_week-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_week instead.")
  (gps_week m))

(cl:ensure-generic-function 'epoch_status-val :lambda-list '(m))
(cl:defmethod epoch_status-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:epoch_status-val is deprecated.  Use microstrain_inertial_msgs-msg:epoch_status instead.")
  (epoch_status m))

(cl:ensure-generic-function 'dongle_version-val :lambda-list '(m))
(cl:defmethod dongle_version-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_version-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_version instead.")
  (dongle_version m))

(cl:ensure-generic-function 'dongle_controller_state-val :lambda-list '(m))
(cl:defmethod dongle_controller_state-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_controller_state-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_controller_state instead.")
  (dongle_controller_state m))

(cl:ensure-generic-function 'dongle_platform_state-val :lambda-list '(m))
(cl:defmethod dongle_platform_state-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_platform_state-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_platform_state instead.")
  (dongle_platform_state m))

(cl:ensure-generic-function 'dongle_controller_status-val :lambda-list '(m))
(cl:defmethod dongle_controller_status-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_controller_status-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_controller_status instead.")
  (dongle_controller_status m))

(cl:ensure-generic-function 'dongle_platform_status-val :lambda-list '(m))
(cl:defmethod dongle_platform_status-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_platform_status-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_platform_status instead.")
  (dongle_platform_status m))

(cl:ensure-generic-function 'dongle_reset_reason-val :lambda-list '(m))
(cl:defmethod dongle_reset_reason-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_reset_reason-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_reset_reason instead.")
  (dongle_reset_reason m))

(cl:ensure-generic-function 'dongle_signal_quality-val :lambda-list '(m))
(cl:defmethod dongle_signal_quality-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_signal_quality-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_signal_quality instead.")
  (dongle_signal_quality m))

(cl:ensure-generic-function 'gps_correction_latency-val :lambda-list '(m))
(cl:defmethod gps_correction_latency-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_correction_latency-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_correction_latency instead.")
  (gps_correction_latency m))

(cl:ensure-generic-function 'glonass_correction_latency-val :lambda-list '(m))
(cl:defmethod glonass_correction_latency-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:glonass_correction_latency-val is deprecated.  Use microstrain_inertial_msgs-msg:glonass_correction_latency instead.")
  (glonass_correction_latency m))

(cl:ensure-generic-function 'galileo_correction_latency-val :lambda-list '(m))
(cl:defmethod galileo_correction_latency-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:galileo_correction_latency-val is deprecated.  Use microstrain_inertial_msgs-msg:galileo_correction_latency instead.")
  (galileo_correction_latency m))

(cl:ensure-generic-function 'beidou_correction_latency-val :lambda-list '(m))
(cl:defmethod beidou_correction_latency-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:beidou_correction_latency-val is deprecated.  Use microstrain_inertial_msgs-msg:beidou_correction_latency instead.")
  (beidou_correction_latency m))

(cl:ensure-generic-function 'raw_status_flags-val :lambda-list '(m))
(cl:defmethod raw_status_flags-val ((m <RTKStatusV1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:raw_status_flags-val is deprecated.  Use microstrain_inertial_msgs-msg:raw_status_flags instead.")
  (raw_status_flags m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTKStatusV1>) ostream)
  "Serializes a message object of type '<RTKStatusV1>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gps_tow))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_week)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_week)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'epoch_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'epoch_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_version)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_controller_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_platform_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_controller_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_platform_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_reset_reason)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_signal_quality)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gps_correction_latency))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'glonass_correction_latency))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'galileo_correction_latency))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'beidou_correction_latency))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'raw_status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'raw_status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'raw_status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'raw_status_flags)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTKStatusV1>) istream)
  "Deserializes a message object of type '<RTKStatusV1>"
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
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_week)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_week)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'epoch_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'epoch_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_version)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_controller_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_platform_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_controller_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_platform_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_reset_reason)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_signal_quality)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gps_correction_latency) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'glonass_correction_latency) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'galileo_correction_latency) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'beidou_correction_latency) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'raw_status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'raw_status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'raw_status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'raw_status_flags)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTKStatusV1>)))
  "Returns string type for a message object of type '<RTKStatusV1>"
  "microstrain_inertial_msgs/RTKStatusV1")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTKStatusV1)))
  "Returns string type for a message object of type 'RTKStatusV1"
  "microstrain_inertial_msgs/RTKStatusV1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTKStatusV1>)))
  "Returns md5sum for a message object of type '<RTKStatusV1>"
  "5892d8d3cacc1b4c1666dd4bc1af9236")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTKStatusV1)))
  "Returns md5sum for a message object of type 'RTKStatusV1"
  "5892d8d3cacc1b4c1666dd4bc1af9236")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTKStatusV1>)))
  "Returns full string definition for message of type '<RTKStatusV1>"
  (cl:format cl:nil "float64 gps_tow~%uint16  gps_week~%uint16  epoch_status~%~%uint8   dongle_version~%uint8   dongle_controller_state~%uint8   dongle_platform_state~%uint8   dongle_controller_status~%uint8   dongle_platform_status~%uint8   dongle_reset_reason~%uint8   dongle_signal_quality~%~%float32 gps_correction_latency~%float32 glonass_correction_latency~%float32 galileo_correction_latency~%float32 beidou_correction_latency~%~%~%uint32  raw_status_flags        # Raw status flags value~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTKStatusV1)))
  "Returns full string definition for message of type 'RTKStatusV1"
  (cl:format cl:nil "float64 gps_tow~%uint16  gps_week~%uint16  epoch_status~%~%uint8   dongle_version~%uint8   dongle_controller_state~%uint8   dongle_platform_state~%uint8   dongle_controller_status~%uint8   dongle_platform_status~%uint8   dongle_reset_reason~%uint8   dongle_signal_quality~%~%float32 gps_correction_latency~%float32 glonass_correction_latency~%float32 galileo_correction_latency~%float32 beidou_correction_latency~%~%~%uint32  raw_status_flags        # Raw status flags value~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTKStatusV1>))
  (cl:+ 0
     8
     2
     2
     1
     1
     1
     1
     1
     1
     1
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTKStatusV1>))
  "Converts a ROS message object to a list"
  (cl:list 'RTKStatusV1
    (cl:cons ':gps_tow (gps_tow msg))
    (cl:cons ':gps_week (gps_week msg))
    (cl:cons ':epoch_status (epoch_status msg))
    (cl:cons ':dongle_version (dongle_version msg))
    (cl:cons ':dongle_controller_state (dongle_controller_state msg))
    (cl:cons ':dongle_platform_state (dongle_platform_state msg))
    (cl:cons ':dongle_controller_status (dongle_controller_status msg))
    (cl:cons ':dongle_platform_status (dongle_platform_status msg))
    (cl:cons ':dongle_reset_reason (dongle_reset_reason msg))
    (cl:cons ':dongle_signal_quality (dongle_signal_quality msg))
    (cl:cons ':gps_correction_latency (gps_correction_latency msg))
    (cl:cons ':glonass_correction_latency (glonass_correction_latency msg))
    (cl:cons ':galileo_correction_latency (galileo_correction_latency msg))
    (cl:cons ':beidou_correction_latency (beidou_correction_latency msg))
    (cl:cons ':raw_status_flags (raw_status_flags msg))
))
