; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude SystemWarnings.msg.html

(cl:defclass <SystemWarnings> (roslisp-msg-protocol:ros-message)
  ((sound_type
    :reader sound_type
    :initarg :sound_type
    :type cl:fixnum
    :initform 0)
   (peds_in_dz
    :reader peds_in_dz
    :initarg :peds_in_dz
    :type cl:boolean
    :initform cl:nil)
   (peds_fcw
    :reader peds_fcw
    :initarg :peds_fcw
    :type cl:boolean
    :initform cl:nil)
   (time_indicator
    :reader time_indicator
    :initarg :time_indicator
    :type cl:fixnum
    :initform 0)
   (error_valid
    :reader error_valid
    :initarg :error_valid
    :type cl:boolean
    :initform cl:nil)
   (error_code
    :reader error_code
    :initarg :error_code
    :type cl:fixnum
    :initform 0)
   (zero_speed
    :reader zero_speed
    :initarg :zero_speed
    :type cl:boolean
    :initform cl:nil)
   (headway_valid
    :reader headway_valid
    :initarg :headway_valid
    :type cl:boolean
    :initform cl:nil)
   (headway_measurement
    :reader headway_measurement
    :initarg :headway_measurement
    :type cl:float
    :initform 0.0)
   (ldw_off
    :reader ldw_off
    :initarg :ldw_off
    :type cl:boolean
    :initform cl:nil)
   (left_ldw_on
    :reader left_ldw_on
    :initarg :left_ldw_on
    :type cl:boolean
    :initform cl:nil)
   (right_ldw_on
    :reader right_ldw_on
    :initarg :right_ldw_on
    :type cl:boolean
    :initform cl:nil)
   (fcw_on
    :reader fcw_on
    :initarg :fcw_on
    :type cl:boolean
    :initform cl:nil)
   (maintenance
    :reader maintenance
    :initarg :maintenance
    :type cl:boolean
    :initform cl:nil)
   (failsafe
    :reader failsafe
    :initarg :failsafe
    :type cl:boolean
    :initform cl:nil)
   (tsr_enabled
    :reader tsr_enabled
    :initarg :tsr_enabled
    :type cl:boolean
    :initform cl:nil)
   (hw_repeatable_enabled
    :reader hw_repeatable_enabled
    :initarg :hw_repeatable_enabled
    :type cl:boolean
    :initform cl:nil)
   (headway_warning_level
    :reader headway_warning_level
    :initarg :headway_warning_level
    :type cl:fixnum
    :initform 0)
   (tsr_warning_level
    :reader tsr_warning_level
    :initarg :tsr_warning_level
    :type cl:fixnum
    :initform 0)
   (tamper_alert
    :reader tamper_alert
    :initarg :tamper_alert
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SystemWarnings (<SystemWarnings>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SystemWarnings>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SystemWarnings)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<SystemWarnings> is deprecated: use mobileye_msgs-msg:SystemWarnings instead.")))

(cl:ensure-generic-function 'sound_type-val :lambda-list '(m))
(cl:defmethod sound_type-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sound_type-val is deprecated.  Use mobileye_msgs-msg:sound_type instead.")
  (sound_type m))

(cl:ensure-generic-function 'peds_in_dz-val :lambda-list '(m))
(cl:defmethod peds_in_dz-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:peds_in_dz-val is deprecated.  Use mobileye_msgs-msg:peds_in_dz instead.")
  (peds_in_dz m))

(cl:ensure-generic-function 'peds_fcw-val :lambda-list '(m))
(cl:defmethod peds_fcw-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:peds_fcw-val is deprecated.  Use mobileye_msgs-msg:peds_fcw instead.")
  (peds_fcw m))

(cl:ensure-generic-function 'time_indicator-val :lambda-list '(m))
(cl:defmethod time_indicator-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:time_indicator-val is deprecated.  Use mobileye_msgs-msg:time_indicator instead.")
  (time_indicator m))

(cl:ensure-generic-function 'error_valid-val :lambda-list '(m))
(cl:defmethod error_valid-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:error_valid-val is deprecated.  Use mobileye_msgs-msg:error_valid instead.")
  (error_valid m))

(cl:ensure-generic-function 'error_code-val :lambda-list '(m))
(cl:defmethod error_code-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:error_code-val is deprecated.  Use mobileye_msgs-msg:error_code instead.")
  (error_code m))

(cl:ensure-generic-function 'zero_speed-val :lambda-list '(m))
(cl:defmethod zero_speed-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:zero_speed-val is deprecated.  Use mobileye_msgs-msg:zero_speed instead.")
  (zero_speed m))

(cl:ensure-generic-function 'headway_valid-val :lambda-list '(m))
(cl:defmethod headway_valid-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:headway_valid-val is deprecated.  Use mobileye_msgs-msg:headway_valid instead.")
  (headway_valid m))

(cl:ensure-generic-function 'headway_measurement-val :lambda-list '(m))
(cl:defmethod headway_measurement-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:headway_measurement-val is deprecated.  Use mobileye_msgs-msg:headway_measurement instead.")
  (headway_measurement m))

(cl:ensure-generic-function 'ldw_off-val :lambda-list '(m))
(cl:defmethod ldw_off-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ldw_off-val is deprecated.  Use mobileye_msgs-msg:ldw_off instead.")
  (ldw_off m))

(cl:ensure-generic-function 'left_ldw_on-val :lambda-list '(m))
(cl:defmethod left_ldw_on-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:left_ldw_on-val is deprecated.  Use mobileye_msgs-msg:left_ldw_on instead.")
  (left_ldw_on m))

(cl:ensure-generic-function 'right_ldw_on-val :lambda-list '(m))
(cl:defmethod right_ldw_on-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:right_ldw_on-val is deprecated.  Use mobileye_msgs-msg:right_ldw_on instead.")
  (right_ldw_on m))

(cl:ensure-generic-function 'fcw_on-val :lambda-list '(m))
(cl:defmethod fcw_on-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:fcw_on-val is deprecated.  Use mobileye_msgs-msg:fcw_on instead.")
  (fcw_on m))

(cl:ensure-generic-function 'maintenance-val :lambda-list '(m))
(cl:defmethod maintenance-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:maintenance-val is deprecated.  Use mobileye_msgs-msg:maintenance instead.")
  (maintenance m))

(cl:ensure-generic-function 'failsafe-val :lambda-list '(m))
(cl:defmethod failsafe-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:failsafe-val is deprecated.  Use mobileye_msgs-msg:failsafe instead.")
  (failsafe m))

(cl:ensure-generic-function 'tsr_enabled-val :lambda-list '(m))
(cl:defmethod tsr_enabled-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tsr_enabled-val is deprecated.  Use mobileye_msgs-msg:tsr_enabled instead.")
  (tsr_enabled m))

(cl:ensure-generic-function 'hw_repeatable_enabled-val :lambda-list '(m))
(cl:defmethod hw_repeatable_enabled-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:hw_repeatable_enabled-val is deprecated.  Use mobileye_msgs-msg:hw_repeatable_enabled instead.")
  (hw_repeatable_enabled m))

(cl:ensure-generic-function 'headway_warning_level-val :lambda-list '(m))
(cl:defmethod headway_warning_level-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:headway_warning_level-val is deprecated.  Use mobileye_msgs-msg:headway_warning_level instead.")
  (headway_warning_level m))

(cl:ensure-generic-function 'tsr_warning_level-val :lambda-list '(m))
(cl:defmethod tsr_warning_level-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tsr_warning_level-val is deprecated.  Use mobileye_msgs-msg:tsr_warning_level instead.")
  (tsr_warning_level m))

(cl:ensure-generic-function 'tamper_alert-val :lambda-list '(m))
(cl:defmethod tamper_alert-val ((m <SystemWarnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tamper_alert-val is deprecated.  Use mobileye_msgs-msg:tamper_alert instead.")
  (tamper_alert m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SystemWarnings>) ostream)
  "Serializes a message object of type '<SystemWarnings>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sound_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'peds_in_dz) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'peds_fcw) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'time_indicator)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'error_valid) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'error_code)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'zero_speed) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'headway_valid) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'headway_measurement))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ldw_off) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'left_ldw_on) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'right_ldw_on) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'fcw_on) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'maintenance) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'failsafe) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'tsr_enabled) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'hw_repeatable_enabled) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'headway_warning_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'tsr_warning_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'tamper_alert) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SystemWarnings>) istream)
  "Deserializes a message object of type '<SystemWarnings>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sound_type)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'peds_in_dz) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'peds_fcw) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'time_indicator)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'error_valid) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'error_code)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zero_speed) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'headway_valid) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'headway_measurement) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'ldw_off) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'left_ldw_on) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'right_ldw_on) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'fcw_on) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'maintenance) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'failsafe) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'tsr_enabled) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'hw_repeatable_enabled) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'headway_warning_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'tsr_warning_level)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tamper_alert) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SystemWarnings>)))
  "Returns string type for a message object of type '<SystemWarnings>"
  "mobileye_msgs/SystemWarnings")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SystemWarnings)))
  "Returns string type for a message object of type 'SystemWarnings"
  "mobileye_msgs/SystemWarnings")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SystemWarnings>)))
  "Returns md5sum for a message object of type '<SystemWarnings>"
  "13b6bac628f7b8055c48f3c1bf2dfa99")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SystemWarnings)))
  "Returns md5sum for a message object of type 'SystemWarnings"
  "13b6bac628f7b8055c48f3c1bf2dfa99")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SystemWarnings>)))
  "Returns full string definition for message of type '<SystemWarnings>"
  (cl:format cl:nil "uint8 sound_type~%bool peds_in_dz~%bool peds_fcw~%uint8 time_indicator~%~%bool error_valid~%uint8 error_code~%bool zero_speed~%bool headway_valid~%float32 headway_measurement~%~%bool ldw_off~%bool left_ldw_on~%bool right_ldw_on~%bool fcw_on~%bool maintenance~%bool failsafe~%~%bool tsr_enabled~%bool hw_repeatable_enabled~%uint8 headway_warning_level~%uint8 tsr_warning_level~%bool tamper_alert~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SystemWarnings)))
  "Returns full string definition for message of type 'SystemWarnings"
  (cl:format cl:nil "uint8 sound_type~%bool peds_in_dz~%bool peds_fcw~%uint8 time_indicator~%~%bool error_valid~%uint8 error_code~%bool zero_speed~%bool headway_valid~%float32 headway_measurement~%~%bool ldw_off~%bool left_ldw_on~%bool right_ldw_on~%bool fcw_on~%bool maintenance~%bool failsafe~%~%bool tsr_enabled~%bool hw_repeatable_enabled~%uint8 headway_warning_level~%uint8 tsr_warning_level~%bool tamper_alert~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SystemWarnings>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
     1
     4
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
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SystemWarnings>))
  "Converts a ROS message object to a list"
  (cl:list 'SystemWarnings
    (cl:cons ':sound_type (sound_type msg))
    (cl:cons ':peds_in_dz (peds_in_dz msg))
    (cl:cons ':peds_fcw (peds_fcw msg))
    (cl:cons ':time_indicator (time_indicator msg))
    (cl:cons ':error_valid (error_valid msg))
    (cl:cons ':error_code (error_code msg))
    (cl:cons ':zero_speed (zero_speed msg))
    (cl:cons ':headway_valid (headway_valid msg))
    (cl:cons ':headway_measurement (headway_measurement msg))
    (cl:cons ':ldw_off (ldw_off msg))
    (cl:cons ':left_ldw_on (left_ldw_on msg))
    (cl:cons ':right_ldw_on (right_ldw_on msg))
    (cl:cons ':fcw_on (fcw_on msg))
    (cl:cons ':maintenance (maintenance msg))
    (cl:cons ':failsafe (failsafe msg))
    (cl:cons ':tsr_enabled (tsr_enabled msg))
    (cl:cons ':hw_repeatable_enabled (hw_repeatable_enabled msg))
    (cl:cons ':headway_warning_level (headway_warning_level msg))
    (cl:cons ':tsr_warning_level (tsr_warning_level msg))
    (cl:cons ':tamper_alert (tamper_alert msg))
))
