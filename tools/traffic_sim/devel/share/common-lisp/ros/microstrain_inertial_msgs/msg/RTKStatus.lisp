; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude RTKStatus.msg.html

(cl:defclass <RTKStatus> (roslisp-msg-protocol:ros-message)
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
   (dongle_modem_state
    :reader dongle_modem_state
    :initarg :dongle_modem_state
    :type cl:fixnum
    :initform 0)
   (dongle_connection_type
    :reader dongle_connection_type
    :initarg :dongle_connection_type
    :type cl:fixnum
    :initform 0)
   (dongle_rssi
    :reader dongle_rssi
    :initarg :dongle_rssi
    :type cl:fixnum
    :initform 0)
   (dongle_signal_quality
    :reader dongle_signal_quality
    :initarg :dongle_signal_quality
    :type cl:fixnum
    :initform 0)
   (dongle_tower_change_indicator
    :reader dongle_tower_change_indicator
    :initarg :dongle_tower_change_indicator
    :type cl:fixnum
    :initform 0)
   (dongle_nmea_timeout
    :reader dongle_nmea_timeout
    :initarg :dongle_nmea_timeout
    :type cl:boolean
    :initform cl:nil)
   (dongle_server_timeout
    :reader dongle_server_timeout
    :initarg :dongle_server_timeout
    :type cl:boolean
    :initform cl:nil)
   (dongle_rtcm_timeout
    :reader dongle_rtcm_timeout
    :initarg :dongle_rtcm_timeout
    :type cl:boolean
    :initform cl:nil)
   (dongle_out_of_range
    :reader dongle_out_of_range
    :initarg :dongle_out_of_range
    :type cl:boolean
    :initform cl:nil)
   (dongle_corrections_unavailable
    :reader dongle_corrections_unavailable
    :initarg :dongle_corrections_unavailable
    :type cl:boolean
    :initform cl:nil)
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

(cl:defclass RTKStatus (<RTKStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTKStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTKStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<RTKStatus> is deprecated: use microstrain_inertial_msgs-msg:RTKStatus instead.")))

(cl:ensure-generic-function 'gps_tow-val :lambda-list '(m))
(cl:defmethod gps_tow-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_tow-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_tow instead.")
  (gps_tow m))

(cl:ensure-generic-function 'gps_week-val :lambda-list '(m))
(cl:defmethod gps_week-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_week-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_week instead.")
  (gps_week m))

(cl:ensure-generic-function 'epoch_status-val :lambda-list '(m))
(cl:defmethod epoch_status-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:epoch_status-val is deprecated.  Use microstrain_inertial_msgs-msg:epoch_status instead.")
  (epoch_status m))

(cl:ensure-generic-function 'dongle_version-val :lambda-list '(m))
(cl:defmethod dongle_version-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_version-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_version instead.")
  (dongle_version m))

(cl:ensure-generic-function 'dongle_modem_state-val :lambda-list '(m))
(cl:defmethod dongle_modem_state-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_modem_state-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_modem_state instead.")
  (dongle_modem_state m))

(cl:ensure-generic-function 'dongle_connection_type-val :lambda-list '(m))
(cl:defmethod dongle_connection_type-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_connection_type-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_connection_type instead.")
  (dongle_connection_type m))

(cl:ensure-generic-function 'dongle_rssi-val :lambda-list '(m))
(cl:defmethod dongle_rssi-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_rssi-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_rssi instead.")
  (dongle_rssi m))

(cl:ensure-generic-function 'dongle_signal_quality-val :lambda-list '(m))
(cl:defmethod dongle_signal_quality-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_signal_quality-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_signal_quality instead.")
  (dongle_signal_quality m))

(cl:ensure-generic-function 'dongle_tower_change_indicator-val :lambda-list '(m))
(cl:defmethod dongle_tower_change_indicator-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_tower_change_indicator-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_tower_change_indicator instead.")
  (dongle_tower_change_indicator m))

(cl:ensure-generic-function 'dongle_nmea_timeout-val :lambda-list '(m))
(cl:defmethod dongle_nmea_timeout-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_nmea_timeout-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_nmea_timeout instead.")
  (dongle_nmea_timeout m))

(cl:ensure-generic-function 'dongle_server_timeout-val :lambda-list '(m))
(cl:defmethod dongle_server_timeout-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_server_timeout-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_server_timeout instead.")
  (dongle_server_timeout m))

(cl:ensure-generic-function 'dongle_rtcm_timeout-val :lambda-list '(m))
(cl:defmethod dongle_rtcm_timeout-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_rtcm_timeout-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_rtcm_timeout instead.")
  (dongle_rtcm_timeout m))

(cl:ensure-generic-function 'dongle_out_of_range-val :lambda-list '(m))
(cl:defmethod dongle_out_of_range-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_out_of_range-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_out_of_range instead.")
  (dongle_out_of_range m))

(cl:ensure-generic-function 'dongle_corrections_unavailable-val :lambda-list '(m))
(cl:defmethod dongle_corrections_unavailable-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dongle_corrections_unavailable-val is deprecated.  Use microstrain_inertial_msgs-msg:dongle_corrections_unavailable instead.")
  (dongle_corrections_unavailable m))

(cl:ensure-generic-function 'gps_correction_latency-val :lambda-list '(m))
(cl:defmethod gps_correction_latency-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_correction_latency-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_correction_latency instead.")
  (gps_correction_latency m))

(cl:ensure-generic-function 'glonass_correction_latency-val :lambda-list '(m))
(cl:defmethod glonass_correction_latency-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:glonass_correction_latency-val is deprecated.  Use microstrain_inertial_msgs-msg:glonass_correction_latency instead.")
  (glonass_correction_latency m))

(cl:ensure-generic-function 'galileo_correction_latency-val :lambda-list '(m))
(cl:defmethod galileo_correction_latency-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:galileo_correction_latency-val is deprecated.  Use microstrain_inertial_msgs-msg:galileo_correction_latency instead.")
  (galileo_correction_latency m))

(cl:ensure-generic-function 'beidou_correction_latency-val :lambda-list '(m))
(cl:defmethod beidou_correction_latency-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:beidou_correction_latency-val is deprecated.  Use microstrain_inertial_msgs-msg:beidou_correction_latency instead.")
  (beidou_correction_latency m))

(cl:ensure-generic-function 'raw_status_flags-val :lambda-list '(m))
(cl:defmethod raw_status_flags-val ((m <RTKStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:raw_status_flags-val is deprecated.  Use microstrain_inertial_msgs-msg:raw_status_flags instead.")
  (raw_status_flags m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<RTKStatus>)))
    "Constants for message type '<RTKStatus>"
  '((:MODEM_STATE_OFF . 0)
    (:MODEM_STATE_NO_NETWORK . 1)
    (:MODEM_STATE_NETWORK_CONNECTED . 2)
    (:MODEM_STATE_CONFIGURING_DATA_CONTEXT . 3)
    (:MODEM_STATE_ACTIVATING_DATA_CONTEXT . 4)
    (:MODEM_STATE_CONFIGURING_SOCKET . 5)
    (:MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE . 6)
    (:MODEM_STATE_CONNECTED_AND_IDLE . 7)
    (:MODEM_STATE_CONNECTED_AND_STREAMING . 8)
    (:CONNECTION_TYPE_NO_CONNECTION . 0)
    (:CONNECTION_TYPE_CONNECTION_2G . 2)
    (:CONNECTION_TYPE_CONNECTION_3G . 3)
    (:CONNECTION_TYPE_CONNECTION_4G . 4)
    (:CONNECTION_TYPE_CONNECTION_5G . 5))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'RTKStatus)))
    "Constants for message type 'RTKStatus"
  '((:MODEM_STATE_OFF . 0)
    (:MODEM_STATE_NO_NETWORK . 1)
    (:MODEM_STATE_NETWORK_CONNECTED . 2)
    (:MODEM_STATE_CONFIGURING_DATA_CONTEXT . 3)
    (:MODEM_STATE_ACTIVATING_DATA_CONTEXT . 4)
    (:MODEM_STATE_CONFIGURING_SOCKET . 5)
    (:MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE . 6)
    (:MODEM_STATE_CONNECTED_AND_IDLE . 7)
    (:MODEM_STATE_CONNECTED_AND_STREAMING . 8)
    (:CONNECTION_TYPE_NO_CONNECTION . 0)
    (:CONNECTION_TYPE_CONNECTION_2G . 2)
    (:CONNECTION_TYPE_CONNECTION_3G . 3)
    (:CONNECTION_TYPE_CONNECTION_4G . 4)
    (:CONNECTION_TYPE_CONNECTION_5G . 5))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTKStatus>) ostream)
  "Serializes a message object of type '<RTKStatus>"
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_modem_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_connection_type)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'dongle_rssi)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_signal_quality)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_tower_change_indicator)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'dongle_nmea_timeout) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'dongle_server_timeout) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'dongle_rtcm_timeout) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'dongle_out_of_range) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'dongle_corrections_unavailable) 1 0)) ostream)
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTKStatus>) istream)
  "Deserializes a message object of type '<RTKStatus>"
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
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_modem_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_connection_type)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'dongle_rssi) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_signal_quality)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dongle_tower_change_indicator)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dongle_nmea_timeout) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'dongle_server_timeout) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'dongle_rtcm_timeout) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'dongle_out_of_range) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'dongle_corrections_unavailable) (cl:not (cl:zerop (cl:read-byte istream))))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTKStatus>)))
  "Returns string type for a message object of type '<RTKStatus>"
  "microstrain_inertial_msgs/RTKStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTKStatus)))
  "Returns string type for a message object of type 'RTKStatus"
  "microstrain_inertial_msgs/RTKStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTKStatus>)))
  "Returns md5sum for a message object of type '<RTKStatus>"
  "da5543a2118eca78b75d2cf97686be1d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTKStatus)))
  "Returns md5sum for a message object of type 'RTKStatus"
  "da5543a2118eca78b75d2cf97686be1d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTKStatus>)))
  "Returns full string definition for message of type '<RTKStatus>"
  (cl:format cl:nil "# Possible values for dongle_modem_state~%uint8   MODEM_STATE_OFF = 0~%uint8   MODEM_STATE_NO_NETWORK = 1~%uint8   MODEM_STATE_NETWORK_CONNECTED = 2~%uint8   MODEM_STATE_CONFIGURING_DATA_CONTEXT = 3~%uint8   MODEM_STATE_ACTIVATING_DATA_CONTEXT = 4~%uint8   MODEM_STATE_CONFIGURING_SOCKET = 5~%uint8   MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE = 6~%uint8   MODEM_STATE_CONNECTED_AND_IDLE = 7~%uint8   MODEM_STATE_CONNECTED_AND_STREAMING = 8~%~%# Possible values for dongle_connection_type~%uint8   CONNECTION_TYPE_NO_CONNECTION = 0~%uint8   CONNECTION_TYPE_CONNECTION_2G = 2~%uint8   CONNECTION_TYPE_CONNECTION_3G = 3~%uint8   CONNECTION_TYPE_CONNECTION_4G = 4~%uint8   CONNECTION_TYPE_CONNECTION_5G = 5~%~%float64 gps_tow~%uint16  gps_week~%uint16  epoch_status~%~%uint8   dongle_version~%uint8   dongle_modem_state      # Use in conjunction with MODEM_STATE_* values~%uint8   dongle_connection_type  # Use in conjunction with CONNECTION_TYPE_* values~%int8    dongle_rssi             # RSSI values are negative~%uint8   dongle_signal_quality~%uint8   dongle_tower_change_indicator~%bool    dongle_nmea_timeout~%bool    dongle_server_timeout~%bool    dongle_rtcm_timeout~%bool    dongle_out_of_range~%bool    dongle_corrections_unavailable~%~%float32 gps_correction_latency~%float32 glonass_correction_latency~%float32 galileo_correction_latency~%float32 beidou_correction_latency~%~%~%uint32  raw_status_flags        # Raw status flags value~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTKStatus)))
  "Returns full string definition for message of type 'RTKStatus"
  (cl:format cl:nil "# Possible values for dongle_modem_state~%uint8   MODEM_STATE_OFF = 0~%uint8   MODEM_STATE_NO_NETWORK = 1~%uint8   MODEM_STATE_NETWORK_CONNECTED = 2~%uint8   MODEM_STATE_CONFIGURING_DATA_CONTEXT = 3~%uint8   MODEM_STATE_ACTIVATING_DATA_CONTEXT = 4~%uint8   MODEM_STATE_CONFIGURING_SOCKET = 5~%uint8   MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE = 6~%uint8   MODEM_STATE_CONNECTED_AND_IDLE = 7~%uint8   MODEM_STATE_CONNECTED_AND_STREAMING = 8~%~%# Possible values for dongle_connection_type~%uint8   CONNECTION_TYPE_NO_CONNECTION = 0~%uint8   CONNECTION_TYPE_CONNECTION_2G = 2~%uint8   CONNECTION_TYPE_CONNECTION_3G = 3~%uint8   CONNECTION_TYPE_CONNECTION_4G = 4~%uint8   CONNECTION_TYPE_CONNECTION_5G = 5~%~%float64 gps_tow~%uint16  gps_week~%uint16  epoch_status~%~%uint8   dongle_version~%uint8   dongle_modem_state      # Use in conjunction with MODEM_STATE_* values~%uint8   dongle_connection_type  # Use in conjunction with CONNECTION_TYPE_* values~%int8    dongle_rssi             # RSSI values are negative~%uint8   dongle_signal_quality~%uint8   dongle_tower_change_indicator~%bool    dongle_nmea_timeout~%bool    dongle_server_timeout~%bool    dongle_rtcm_timeout~%bool    dongle_out_of_range~%bool    dongle_corrections_unavailable~%~%float32 gps_correction_latency~%float32 glonass_correction_latency~%float32 galileo_correction_latency~%float32 beidou_correction_latency~%~%~%uint32  raw_status_flags        # Raw status flags value~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTKStatus>))
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
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTKStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'RTKStatus
    (cl:cons ':gps_tow (gps_tow msg))
    (cl:cons ':gps_week (gps_week msg))
    (cl:cons ':epoch_status (epoch_status msg))
    (cl:cons ':dongle_version (dongle_version msg))
    (cl:cons ':dongle_modem_state (dongle_modem_state msg))
    (cl:cons ':dongle_connection_type (dongle_connection_type msg))
    (cl:cons ':dongle_rssi (dongle_rssi msg))
    (cl:cons ':dongle_signal_quality (dongle_signal_quality msg))
    (cl:cons ':dongle_tower_change_indicator (dongle_tower_change_indicator msg))
    (cl:cons ':dongle_nmea_timeout (dongle_nmea_timeout msg))
    (cl:cons ':dongle_server_timeout (dongle_server_timeout msg))
    (cl:cons ':dongle_rtcm_timeout (dongle_rtcm_timeout msg))
    (cl:cons ':dongle_out_of_range (dongle_out_of_range msg))
    (cl:cons ':dongle_corrections_unavailable (dongle_corrections_unavailable msg))
    (cl:cons ':gps_correction_latency (gps_correction_latency msg))
    (cl:cons ':glonass_correction_latency (glonass_correction_latency msg))
    (cl:cons ':galileo_correction_latency (galileo_correction_latency msg))
    (cl:cons ':beidou_correction_latency (beidou_correction_latency msg))
    (cl:cons ':raw_status_flags (raw_status_flags msg))
))
