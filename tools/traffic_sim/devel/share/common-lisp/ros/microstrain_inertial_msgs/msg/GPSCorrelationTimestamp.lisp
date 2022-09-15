; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude GPSCorrelationTimestamp.msg.html

(cl:defclass <GPSCorrelationTimestamp> (roslisp-msg-protocol:ros-message)
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
   (timestamp_flags
    :reader timestamp_flags
    :initarg :timestamp_flags
    :type cl:fixnum
    :initform 0))
)

(cl:defclass GPSCorrelationTimestamp (<GPSCorrelationTimestamp>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GPSCorrelationTimestamp>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GPSCorrelationTimestamp)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<GPSCorrelationTimestamp> is deprecated: use microstrain_inertial_msgs-msg:GPSCorrelationTimestamp instead.")))

(cl:ensure-generic-function 'gps_tow-val :lambda-list '(m))
(cl:defmethod gps_tow-val ((m <GPSCorrelationTimestamp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_tow-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_tow instead.")
  (gps_tow m))

(cl:ensure-generic-function 'gps_week_number-val :lambda-list '(m))
(cl:defmethod gps_week_number-val ((m <GPSCorrelationTimestamp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_week_number-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_week_number instead.")
  (gps_week_number m))

(cl:ensure-generic-function 'timestamp_flags-val :lambda-list '(m))
(cl:defmethod timestamp_flags-val ((m <GPSCorrelationTimestamp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:timestamp_flags-val is deprecated.  Use microstrain_inertial_msgs-msg:timestamp_flags instead.")
  (timestamp_flags m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<GPSCorrelationTimestamp>)))
    "Constants for message type '<GPSCorrelationTimestamp>"
  '((:TIMESTAMP_FLAG_PPS_GOOD . 1)
    (:TIMESTAMP_FLAG_GPS_REFRESH . 2)
    (:TIMESTAMP_FLAG_GPS_INITALIZED . 4))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'GPSCorrelationTimestamp)))
    "Constants for message type 'GPSCorrelationTimestamp"
  '((:TIMESTAMP_FLAG_PPS_GOOD . 1)
    (:TIMESTAMP_FLAG_GPS_REFRESH . 2)
    (:TIMESTAMP_FLAG_GPS_INITALIZED . 4))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GPSCorrelationTimestamp>) ostream)
  "Serializes a message object of type '<GPSCorrelationTimestamp>"
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timestamp_flags)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GPSCorrelationTimestamp>) istream)
  "Deserializes a message object of type '<GPSCorrelationTimestamp>"
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
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timestamp_flags)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GPSCorrelationTimestamp>)))
  "Returns string type for a message object of type '<GPSCorrelationTimestamp>"
  "microstrain_inertial_msgs/GPSCorrelationTimestamp")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GPSCorrelationTimestamp)))
  "Returns string type for a message object of type 'GPSCorrelationTimestamp"
  "microstrain_inertial_msgs/GPSCorrelationTimestamp")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GPSCorrelationTimestamp>)))
  "Returns md5sum for a message object of type '<GPSCorrelationTimestamp>"
  "e4273ef053cace34fe47537c314897d4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GPSCorrelationTimestamp)))
  "Returns md5sum for a message object of type 'GPSCorrelationTimestamp"
  "e4273ef053cace34fe47537c314897d4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GPSCorrelationTimestamp>)))
  "Returns full string definition for message of type '<GPSCorrelationTimestamp>"
  (cl:format cl:nil "float64 gps_tow~%uint16 gps_week_number~%uint16 timestamp_flags~%uint16 TIMESTAMP_FLAG_PPS_GOOD      = 1  #0b001~%uint16 TIMESTAMP_FLAG_GPS_REFRESH   = 2  #0b010~%uint16 TIMESTAMP_FLAG_GPS_INITALIZED= 4  #0b100~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GPSCorrelationTimestamp)))
  "Returns full string definition for message of type 'GPSCorrelationTimestamp"
  (cl:format cl:nil "float64 gps_tow~%uint16 gps_week_number~%uint16 timestamp_flags~%uint16 TIMESTAMP_FLAG_PPS_GOOD      = 1  #0b001~%uint16 TIMESTAMP_FLAG_GPS_REFRESH   = 2  #0b010~%uint16 TIMESTAMP_FLAG_GPS_INITALIZED= 4  #0b100~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GPSCorrelationTimestamp>))
  (cl:+ 0
     8
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GPSCorrelationTimestamp>))
  "Converts a ROS message object to a list"
  (cl:list 'GPSCorrelationTimestamp
    (cl:cons ':gps_tow (gps_tow msg))
    (cl:cons ':gps_week_number (gps_week_number msg))
    (cl:cons ':timestamp_flags (timestamp_flags msg))
))
