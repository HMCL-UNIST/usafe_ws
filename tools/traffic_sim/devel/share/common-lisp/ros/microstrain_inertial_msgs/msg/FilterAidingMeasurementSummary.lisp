; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude FilterAidingMeasurementSummary.msg.html

(cl:defclass <FilterAidingMeasurementSummary> (roslisp-msg-protocol:ros-message)
  ((gps_tow
    :reader gps_tow
    :initarg :gps_tow
    :type cl:float
    :initform 0.0)
   (gnss1
    :reader gnss1
    :initarg :gnss1
    :type microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator
    :initform (cl:make-instance 'microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator))
   (gnss2
    :reader gnss2
    :initarg :gnss2
    :type microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator
    :initform (cl:make-instance 'microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator))
   (dual_antenna
    :reader dual_antenna
    :initarg :dual_antenna
    :type microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator
    :initform (cl:make-instance 'microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator))
   (heading
    :reader heading
    :initarg :heading
    :type microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator
    :initform (cl:make-instance 'microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator))
   (pressure
    :reader pressure
    :initarg :pressure
    :type microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator
    :initform (cl:make-instance 'microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator))
   (magnetometer
    :reader magnetometer
    :initarg :magnetometer
    :type microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator
    :initform (cl:make-instance 'microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator))
   (speed
    :reader speed
    :initarg :speed
    :type microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator
    :initform (cl:make-instance 'microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator)))
)

(cl:defclass FilterAidingMeasurementSummary (<FilterAidingMeasurementSummary>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FilterAidingMeasurementSummary>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FilterAidingMeasurementSummary)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<FilterAidingMeasurementSummary> is deprecated: use microstrain_inertial_msgs-msg:FilterAidingMeasurementSummary instead.")))

(cl:ensure-generic-function 'gps_tow-val :lambda-list '(m))
(cl:defmethod gps_tow-val ((m <FilterAidingMeasurementSummary>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_tow-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_tow instead.")
  (gps_tow m))

(cl:ensure-generic-function 'gnss1-val :lambda-list '(m))
(cl:defmethod gnss1-val ((m <FilterAidingMeasurementSummary>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gnss1-val is deprecated.  Use microstrain_inertial_msgs-msg:gnss1 instead.")
  (gnss1 m))

(cl:ensure-generic-function 'gnss2-val :lambda-list '(m))
(cl:defmethod gnss2-val ((m <FilterAidingMeasurementSummary>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gnss2-val is deprecated.  Use microstrain_inertial_msgs-msg:gnss2 instead.")
  (gnss2 m))

(cl:ensure-generic-function 'dual_antenna-val :lambda-list '(m))
(cl:defmethod dual_antenna-val ((m <FilterAidingMeasurementSummary>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dual_antenna-val is deprecated.  Use microstrain_inertial_msgs-msg:dual_antenna instead.")
  (dual_antenna m))

(cl:ensure-generic-function 'heading-val :lambda-list '(m))
(cl:defmethod heading-val ((m <FilterAidingMeasurementSummary>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:heading-val is deprecated.  Use microstrain_inertial_msgs-msg:heading instead.")
  (heading m))

(cl:ensure-generic-function 'pressure-val :lambda-list '(m))
(cl:defmethod pressure-val ((m <FilterAidingMeasurementSummary>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:pressure-val is deprecated.  Use microstrain_inertial_msgs-msg:pressure instead.")
  (pressure m))

(cl:ensure-generic-function 'magnetometer-val :lambda-list '(m))
(cl:defmethod magnetometer-val ((m <FilterAidingMeasurementSummary>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:magnetometer-val is deprecated.  Use microstrain_inertial_msgs-msg:magnetometer instead.")
  (magnetometer m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <FilterAidingMeasurementSummary>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:speed-val is deprecated.  Use microstrain_inertial_msgs-msg:speed instead.")
  (speed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FilterAidingMeasurementSummary>) ostream)
  "Serializes a message object of type '<FilterAidingMeasurementSummary>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gps_tow))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gnss1) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gnss2) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'dual_antenna) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'heading) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pressure) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'magnetometer) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'speed) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FilterAidingMeasurementSummary>) istream)
  "Deserializes a message object of type '<FilterAidingMeasurementSummary>"
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
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gnss1) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gnss2) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'dual_antenna) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'heading) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pressure) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'magnetometer) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'speed) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FilterAidingMeasurementSummary>)))
  "Returns string type for a message object of type '<FilterAidingMeasurementSummary>"
  "microstrain_inertial_msgs/FilterAidingMeasurementSummary")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FilterAidingMeasurementSummary)))
  "Returns string type for a message object of type 'FilterAidingMeasurementSummary"
  "microstrain_inertial_msgs/FilterAidingMeasurementSummary")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FilterAidingMeasurementSummary>)))
  "Returns md5sum for a message object of type '<FilterAidingMeasurementSummary>"
  "150119d26260add7097bcac810af3fdb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FilterAidingMeasurementSummary)))
  "Returns md5sum for a message object of type 'FilterAidingMeasurementSummary"
  "150119d26260add7097bcac810af3fdb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FilterAidingMeasurementSummary>)))
  "Returns full string definition for message of type '<FilterAidingMeasurementSummary>"
  (cl:format cl:nil "float64 gps_tow~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator gnss1~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator gnss2~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator dual_antenna~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator heading~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator pressure~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator magnetometer~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator speed~%================================================================================~%MSG: microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator~%bool enabled~%bool used~%bool residual_high_warning~%bool sample_time_warning~%bool configuration_error~%bool max_num_meas_exceeded~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FilterAidingMeasurementSummary)))
  "Returns full string definition for message of type 'FilterAidingMeasurementSummary"
  (cl:format cl:nil "float64 gps_tow~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator gnss1~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator gnss2~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator dual_antenna~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator heading~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator pressure~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator magnetometer~%microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator speed~%================================================================================~%MSG: microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator~%bool enabled~%bool used~%bool residual_high_warning~%bool sample_time_warning~%bool configuration_error~%bool max_num_meas_exceeded~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FilterAidingMeasurementSummary>))
  (cl:+ 0
     8
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gnss1))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gnss2))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'dual_antenna))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'heading))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pressure))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'magnetometer))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'speed))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FilterAidingMeasurementSummary>))
  "Converts a ROS message object to a list"
  (cl:list 'FilterAidingMeasurementSummary
    (cl:cons ':gps_tow (gps_tow msg))
    (cl:cons ':gnss1 (gnss1 msg))
    (cl:cons ':gnss2 (gnss2 msg))
    (cl:cons ':dual_antenna (dual_antenna msg))
    (cl:cons ':heading (heading msg))
    (cl:cons ':pressure (pressure msg))
    (cl:cons ':magnetometer (magnetometer msg))
    (cl:cons ':speed (speed msg))
))
