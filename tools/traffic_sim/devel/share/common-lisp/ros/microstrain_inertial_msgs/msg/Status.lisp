; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude Status.msg.html

(cl:defclass <Status> (roslisp-msg-protocol:ros-message)
  ((device_model
    :reader device_model
    :initarg :device_model
    :type cl:fixnum
    :initform 0)
   (status_selector
    :reader status_selector
    :initarg :status_selector
    :type cl:fixnum
    :initform 0)
   (status_flags
    :reader status_flags
    :initarg :status_flags
    :type cl:integer
    :initform 0)
   (system_state
    :reader system_state
    :initarg :system_state
    :type cl:fixnum
    :initform 0)
   (system_timer_ms
    :reader system_timer_ms
    :initarg :system_timer_ms
    :type cl:integer
    :initform 0)
   (gps_power_on
    :reader gps_power_on
    :initarg :gps_power_on
    :type cl:fixnum
    :initform 0)
   (num_gps_pps_triggers
    :reader num_gps_pps_triggers
    :initarg :num_gps_pps_triggers
    :type cl:integer
    :initform 0)
   (last_gps_pps_trigger_ms
    :reader last_gps_pps_trigger_ms
    :initarg :last_gps_pps_trigger_ms
    :type cl:integer
    :initform 0)
   (imu_stream_enabled
    :reader imu_stream_enabled
    :initarg :imu_stream_enabled
    :type cl:fixnum
    :initform 0)
   (gps_stream_enabled
    :reader gps_stream_enabled
    :initarg :gps_stream_enabled
    :type cl:fixnum
    :initform 0)
   (filter_stream_enabled
    :reader filter_stream_enabled
    :initarg :filter_stream_enabled
    :type cl:fixnum
    :initform 0)
   (imu_dropped_packets
    :reader imu_dropped_packets
    :initarg :imu_dropped_packets
    :type cl:integer
    :initform 0)
   (gps_dropped_packets
    :reader gps_dropped_packets
    :initarg :gps_dropped_packets
    :type cl:integer
    :initform 0)
   (filter_dropped_packets
    :reader filter_dropped_packets
    :initarg :filter_dropped_packets
    :type cl:integer
    :initform 0)
   (com1_port_bytes_written
    :reader com1_port_bytes_written
    :initarg :com1_port_bytes_written
    :type cl:integer
    :initform 0)
   (com1_port_bytes_read
    :reader com1_port_bytes_read
    :initarg :com1_port_bytes_read
    :type cl:integer
    :initform 0)
   (com1_port_write_overruns
    :reader com1_port_write_overruns
    :initarg :com1_port_write_overruns
    :type cl:integer
    :initform 0)
   (com1_port_read_overruns
    :reader com1_port_read_overruns
    :initarg :com1_port_read_overruns
    :type cl:integer
    :initform 0)
   (imu_parser_errors
    :reader imu_parser_errors
    :initarg :imu_parser_errors
    :type cl:integer
    :initform 0)
   (imu_message_count
    :reader imu_message_count
    :initarg :imu_message_count
    :type cl:integer
    :initform 0)
   (imu_last_message_ms
    :reader imu_last_message_ms
    :initarg :imu_last_message_ms
    :type cl:integer
    :initform 0)
   (gps_parser_errors
    :reader gps_parser_errors
    :initarg :gps_parser_errors
    :type cl:integer
    :initform 0)
   (gps_message_count
    :reader gps_message_count
    :initarg :gps_message_count
    :type cl:integer
    :initform 0)
   (gps_last_message_ms
    :reader gps_last_message_ms
    :initarg :gps_last_message_ms
    :type cl:integer
    :initform 0))
)

(cl:defclass Status (<Status>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Status>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Status)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<Status> is deprecated: use microstrain_inertial_msgs-msg:Status instead.")))

(cl:ensure-generic-function 'device_model-val :lambda-list '(m))
(cl:defmethod device_model-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:device_model-val is deprecated.  Use microstrain_inertial_msgs-msg:device_model instead.")
  (device_model m))

(cl:ensure-generic-function 'status_selector-val :lambda-list '(m))
(cl:defmethod status_selector-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:status_selector-val is deprecated.  Use microstrain_inertial_msgs-msg:status_selector instead.")
  (status_selector m))

(cl:ensure-generic-function 'status_flags-val :lambda-list '(m))
(cl:defmethod status_flags-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:status_flags-val is deprecated.  Use microstrain_inertial_msgs-msg:status_flags instead.")
  (status_flags m))

(cl:ensure-generic-function 'system_state-val :lambda-list '(m))
(cl:defmethod system_state-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:system_state-val is deprecated.  Use microstrain_inertial_msgs-msg:system_state instead.")
  (system_state m))

(cl:ensure-generic-function 'system_timer_ms-val :lambda-list '(m))
(cl:defmethod system_timer_ms-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:system_timer_ms-val is deprecated.  Use microstrain_inertial_msgs-msg:system_timer_ms instead.")
  (system_timer_ms m))

(cl:ensure-generic-function 'gps_power_on-val :lambda-list '(m))
(cl:defmethod gps_power_on-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_power_on-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_power_on instead.")
  (gps_power_on m))

(cl:ensure-generic-function 'num_gps_pps_triggers-val :lambda-list '(m))
(cl:defmethod num_gps_pps_triggers-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:num_gps_pps_triggers-val is deprecated.  Use microstrain_inertial_msgs-msg:num_gps_pps_triggers instead.")
  (num_gps_pps_triggers m))

(cl:ensure-generic-function 'last_gps_pps_trigger_ms-val :lambda-list '(m))
(cl:defmethod last_gps_pps_trigger_ms-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:last_gps_pps_trigger_ms-val is deprecated.  Use microstrain_inertial_msgs-msg:last_gps_pps_trigger_ms instead.")
  (last_gps_pps_trigger_ms m))

(cl:ensure-generic-function 'imu_stream_enabled-val :lambda-list '(m))
(cl:defmethod imu_stream_enabled-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:imu_stream_enabled-val is deprecated.  Use microstrain_inertial_msgs-msg:imu_stream_enabled instead.")
  (imu_stream_enabled m))

(cl:ensure-generic-function 'gps_stream_enabled-val :lambda-list '(m))
(cl:defmethod gps_stream_enabled-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_stream_enabled-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_stream_enabled instead.")
  (gps_stream_enabled m))

(cl:ensure-generic-function 'filter_stream_enabled-val :lambda-list '(m))
(cl:defmethod filter_stream_enabled-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:filter_stream_enabled-val is deprecated.  Use microstrain_inertial_msgs-msg:filter_stream_enabled instead.")
  (filter_stream_enabled m))

(cl:ensure-generic-function 'imu_dropped_packets-val :lambda-list '(m))
(cl:defmethod imu_dropped_packets-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:imu_dropped_packets-val is deprecated.  Use microstrain_inertial_msgs-msg:imu_dropped_packets instead.")
  (imu_dropped_packets m))

(cl:ensure-generic-function 'gps_dropped_packets-val :lambda-list '(m))
(cl:defmethod gps_dropped_packets-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_dropped_packets-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_dropped_packets instead.")
  (gps_dropped_packets m))

(cl:ensure-generic-function 'filter_dropped_packets-val :lambda-list '(m))
(cl:defmethod filter_dropped_packets-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:filter_dropped_packets-val is deprecated.  Use microstrain_inertial_msgs-msg:filter_dropped_packets instead.")
  (filter_dropped_packets m))

(cl:ensure-generic-function 'com1_port_bytes_written-val :lambda-list '(m))
(cl:defmethod com1_port_bytes_written-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:com1_port_bytes_written-val is deprecated.  Use microstrain_inertial_msgs-msg:com1_port_bytes_written instead.")
  (com1_port_bytes_written m))

(cl:ensure-generic-function 'com1_port_bytes_read-val :lambda-list '(m))
(cl:defmethod com1_port_bytes_read-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:com1_port_bytes_read-val is deprecated.  Use microstrain_inertial_msgs-msg:com1_port_bytes_read instead.")
  (com1_port_bytes_read m))

(cl:ensure-generic-function 'com1_port_write_overruns-val :lambda-list '(m))
(cl:defmethod com1_port_write_overruns-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:com1_port_write_overruns-val is deprecated.  Use microstrain_inertial_msgs-msg:com1_port_write_overruns instead.")
  (com1_port_write_overruns m))

(cl:ensure-generic-function 'com1_port_read_overruns-val :lambda-list '(m))
(cl:defmethod com1_port_read_overruns-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:com1_port_read_overruns-val is deprecated.  Use microstrain_inertial_msgs-msg:com1_port_read_overruns instead.")
  (com1_port_read_overruns m))

(cl:ensure-generic-function 'imu_parser_errors-val :lambda-list '(m))
(cl:defmethod imu_parser_errors-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:imu_parser_errors-val is deprecated.  Use microstrain_inertial_msgs-msg:imu_parser_errors instead.")
  (imu_parser_errors m))

(cl:ensure-generic-function 'imu_message_count-val :lambda-list '(m))
(cl:defmethod imu_message_count-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:imu_message_count-val is deprecated.  Use microstrain_inertial_msgs-msg:imu_message_count instead.")
  (imu_message_count m))

(cl:ensure-generic-function 'imu_last_message_ms-val :lambda-list '(m))
(cl:defmethod imu_last_message_ms-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:imu_last_message_ms-val is deprecated.  Use microstrain_inertial_msgs-msg:imu_last_message_ms instead.")
  (imu_last_message_ms m))

(cl:ensure-generic-function 'gps_parser_errors-val :lambda-list '(m))
(cl:defmethod gps_parser_errors-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_parser_errors-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_parser_errors instead.")
  (gps_parser_errors m))

(cl:ensure-generic-function 'gps_message_count-val :lambda-list '(m))
(cl:defmethod gps_message_count-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_message_count-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_message_count instead.")
  (gps_message_count m))

(cl:ensure-generic-function 'gps_last_message_ms-val :lambda-list '(m))
(cl:defmethod gps_last_message_ms-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_last_message_ms-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_last_message_ms instead.")
  (gps_last_message_ms m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Status>) ostream)
  "Serializes a message object of type '<Status>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'device_model)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'device_model)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_selector)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'system_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'system_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'system_timer_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'system_timer_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'system_timer_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'system_timer_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_power_on)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num_gps_pps_triggers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'num_gps_pps_triggers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'num_gps_pps_triggers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'num_gps_pps_triggers)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'last_gps_pps_trigger_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'last_gps_pps_trigger_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'last_gps_pps_trigger_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'last_gps_pps_trigger_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_stream_enabled)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_stream_enabled)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'filter_stream_enabled)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'imu_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'imu_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'imu_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gps_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gps_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'filter_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'filter_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'filter_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'filter_dropped_packets)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'com1_port_bytes_written)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'com1_port_bytes_written)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'com1_port_bytes_written)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'com1_port_bytes_written)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'com1_port_bytes_read)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'com1_port_bytes_read)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'com1_port_bytes_read)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'com1_port_bytes_read)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'com1_port_write_overruns)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'com1_port_write_overruns)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'com1_port_write_overruns)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'com1_port_write_overruns)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'com1_port_read_overruns)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'com1_port_read_overruns)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'com1_port_read_overruns)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'com1_port_read_overruns)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_parser_errors)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'imu_parser_errors)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'imu_parser_errors)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'imu_parser_errors)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_message_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'imu_message_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'imu_message_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'imu_message_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_last_message_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'imu_last_message_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'imu_last_message_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'imu_last_message_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_parser_errors)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_parser_errors)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gps_parser_errors)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gps_parser_errors)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_message_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_message_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gps_message_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gps_message_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_last_message_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_last_message_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gps_last_message_ms)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gps_last_message_ms)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Status>) istream)
  "Deserializes a message object of type '<Status>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'device_model)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'device_model)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_selector)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'system_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'system_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'system_timer_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'system_timer_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'system_timer_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'system_timer_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_power_on)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num_gps_pps_triggers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'num_gps_pps_triggers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'num_gps_pps_triggers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'num_gps_pps_triggers)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'last_gps_pps_trigger_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'last_gps_pps_trigger_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'last_gps_pps_trigger_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'last_gps_pps_trigger_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_stream_enabled)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_stream_enabled)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'filter_stream_enabled)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'imu_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'imu_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'imu_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gps_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gps_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'filter_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'filter_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'filter_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'filter_dropped_packets)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'com1_port_bytes_written)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'com1_port_bytes_written)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'com1_port_bytes_written)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'com1_port_bytes_written)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'com1_port_bytes_read)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'com1_port_bytes_read)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'com1_port_bytes_read)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'com1_port_bytes_read)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'com1_port_write_overruns)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'com1_port_write_overruns)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'com1_port_write_overruns)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'com1_port_write_overruns)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'com1_port_read_overruns)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'com1_port_read_overruns)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'com1_port_read_overruns)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'com1_port_read_overruns)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_parser_errors)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'imu_parser_errors)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'imu_parser_errors)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'imu_parser_errors)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_message_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'imu_message_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'imu_message_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'imu_message_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'imu_last_message_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'imu_last_message_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'imu_last_message_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'imu_last_message_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_parser_errors)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_parser_errors)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gps_parser_errors)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gps_parser_errors)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_message_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_message_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gps_message_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gps_message_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_last_message_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gps_last_message_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gps_last_message_ms)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gps_last_message_ms)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Status>)))
  "Returns string type for a message object of type '<Status>"
  "microstrain_inertial_msgs/Status")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Status)))
  "Returns string type for a message object of type 'Status"
  "microstrain_inertial_msgs/Status")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Status>)))
  "Returns md5sum for a message object of type '<Status>"
  "b19b8bec6f96c609664c27dbc51ddf60")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Status)))
  "Returns md5sum for a message object of type 'Status"
  "b19b8bec6f96c609664c27dbc51ddf60")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Status>)))
  "Returns full string definition for message of type '<Status>"
  (cl:format cl:nil "uint16 device_model~%uint8  status_selector~%~%uint32 status_flags~%~%uint16 system_state~%uint32 system_timer_ms~%~%uint8 gps_power_on~%~%uint32 num_gps_pps_triggers~%uint32 last_gps_pps_trigger_ms~%~%uint8 imu_stream_enabled~%uint8 gps_stream_enabled~%uint8 filter_stream_enabled~%~%uint32 imu_dropped_packets~%uint32 gps_dropped_packets~%uint32 filter_dropped_packets~%~%uint32 com1_port_bytes_written~%uint32 com1_port_bytes_read~%uint32 com1_port_write_overruns~%uint32 com1_port_read_overruns~%~%uint32 imu_parser_errors~%uint32 imu_message_count~%uint32 imu_last_message_ms~%~%uint32 gps_parser_errors~%uint32 gps_message_count~%uint32 gps_last_message_ms~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Status)))
  "Returns full string definition for message of type 'Status"
  (cl:format cl:nil "uint16 device_model~%uint8  status_selector~%~%uint32 status_flags~%~%uint16 system_state~%uint32 system_timer_ms~%~%uint8 gps_power_on~%~%uint32 num_gps_pps_triggers~%uint32 last_gps_pps_trigger_ms~%~%uint8 imu_stream_enabled~%uint8 gps_stream_enabled~%uint8 filter_stream_enabled~%~%uint32 imu_dropped_packets~%uint32 gps_dropped_packets~%uint32 filter_dropped_packets~%~%uint32 com1_port_bytes_written~%uint32 com1_port_bytes_read~%uint32 com1_port_write_overruns~%uint32 com1_port_read_overruns~%~%uint32 imu_parser_errors~%uint32 imu_message_count~%uint32 imu_last_message_ms~%~%uint32 gps_parser_errors~%uint32 gps_message_count~%uint32 gps_last_message_ms~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Status>))
  (cl:+ 0
     2
     1
     4
     2
     4
     1
     4
     4
     1
     1
     1
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Status>))
  "Converts a ROS message object to a list"
  (cl:list 'Status
    (cl:cons ':device_model (device_model msg))
    (cl:cons ':status_selector (status_selector msg))
    (cl:cons ':status_flags (status_flags msg))
    (cl:cons ':system_state (system_state msg))
    (cl:cons ':system_timer_ms (system_timer_ms msg))
    (cl:cons ':gps_power_on (gps_power_on msg))
    (cl:cons ':num_gps_pps_triggers (num_gps_pps_triggers msg))
    (cl:cons ':last_gps_pps_trigger_ms (last_gps_pps_trigger_ms msg))
    (cl:cons ':imu_stream_enabled (imu_stream_enabled msg))
    (cl:cons ':gps_stream_enabled (gps_stream_enabled msg))
    (cl:cons ':filter_stream_enabled (filter_stream_enabled msg))
    (cl:cons ':imu_dropped_packets (imu_dropped_packets msg))
    (cl:cons ':gps_dropped_packets (gps_dropped_packets msg))
    (cl:cons ':filter_dropped_packets (filter_dropped_packets msg))
    (cl:cons ':com1_port_bytes_written (com1_port_bytes_written msg))
    (cl:cons ':com1_port_bytes_read (com1_port_bytes_read msg))
    (cl:cons ':com1_port_write_overruns (com1_port_write_overruns msg))
    (cl:cons ':com1_port_read_overruns (com1_port_read_overruns msg))
    (cl:cons ':imu_parser_errors (imu_parser_errors msg))
    (cl:cons ':imu_message_count (imu_message_count msg))
    (cl:cons ':imu_last_message_ms (imu_last_message_ms msg))
    (cl:cons ':gps_parser_errors (gps_parser_errors msg))
    (cl:cons ':gps_message_count (gps_message_count msg))
    (cl:cons ':gps_last_message_ms (gps_last_message_ms msg))
))
