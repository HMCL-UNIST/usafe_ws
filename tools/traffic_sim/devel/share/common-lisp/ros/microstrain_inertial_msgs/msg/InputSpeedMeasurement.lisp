; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude InputSpeedMeasurement.msg.html

(cl:defclass <InputSpeedMeasurement> (roslisp-msg-protocol:ros-message)
  ((gps_tow
    :reader gps_tow
    :initarg :gps_tow
    :type cl:float
    :initform 0.0)
   (speed
    :reader speed
    :initarg :speed
    :type cl:float
    :initform 0.0)
   (speed_uncertainty
    :reader speed_uncertainty
    :initarg :speed_uncertainty
    :type cl:float
    :initform 0.0))
)

(cl:defclass InputSpeedMeasurement (<InputSpeedMeasurement>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InputSpeedMeasurement>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InputSpeedMeasurement)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<InputSpeedMeasurement> is deprecated: use microstrain_inertial_msgs-msg:InputSpeedMeasurement instead.")))

(cl:ensure-generic-function 'gps_tow-val :lambda-list '(m))
(cl:defmethod gps_tow-val ((m <InputSpeedMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_tow-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_tow instead.")
  (gps_tow m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <InputSpeedMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:speed-val is deprecated.  Use microstrain_inertial_msgs-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'speed_uncertainty-val :lambda-list '(m))
(cl:defmethod speed_uncertainty-val ((m <InputSpeedMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:speed_uncertainty-val is deprecated.  Use microstrain_inertial_msgs-msg:speed_uncertainty instead.")
  (speed_uncertainty m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InputSpeedMeasurement>) ostream)
  "Serializes a message object of type '<InputSpeedMeasurement>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gps_tow))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'speed_uncertainty))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InputSpeedMeasurement>) istream)
  "Deserializes a message object of type '<InputSpeedMeasurement>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gps_tow) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'speed_uncertainty) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InputSpeedMeasurement>)))
  "Returns string type for a message object of type '<InputSpeedMeasurement>"
  "microstrain_inertial_msgs/InputSpeedMeasurement")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InputSpeedMeasurement)))
  "Returns string type for a message object of type 'InputSpeedMeasurement"
  "microstrain_inertial_msgs/InputSpeedMeasurement")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InputSpeedMeasurement>)))
  "Returns md5sum for a message object of type '<InputSpeedMeasurement>"
  "c23013e9b4813b23fc2611c8b2e2b2c8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InputSpeedMeasurement)))
  "Returns md5sum for a message object of type 'InputSpeedMeasurement"
  "c23013e9b4813b23fc2611c8b2e2b2c8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InputSpeedMeasurement>)))
  "Returns full string definition for message of type '<InputSpeedMeasurement>"
  (cl:format cl:nil "float32 gps_tow  # GPS time of week when speed was sampled~%float32 speed  # Estimated speed along vehicle's x-axis (may be positive or negative) (m/s)~%float32 speed_uncertainty  # Estimated uncertainty in the speed measurement (1-sigma value) (m/s)~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InputSpeedMeasurement)))
  "Returns full string definition for message of type 'InputSpeedMeasurement"
  (cl:format cl:nil "float32 gps_tow  # GPS time of week when speed was sampled~%float32 speed  # Estimated speed along vehicle's x-axis (may be positive or negative) (m/s)~%float32 speed_uncertainty  # Estimated uncertainty in the speed measurement (1-sigma value) (m/s)~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InputSpeedMeasurement>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InputSpeedMeasurement>))
  "Converts a ROS message object to a list"
  (cl:list 'InputSpeedMeasurement
    (cl:cons ':gps_tow (gps_tow msg))
    (cl:cons ':speed (speed msg))
    (cl:cons ':speed_uncertainty (speed_uncertainty msg))
))
