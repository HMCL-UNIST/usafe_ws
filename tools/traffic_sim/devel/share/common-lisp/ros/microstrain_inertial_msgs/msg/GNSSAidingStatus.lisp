; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude GNSSAidingStatus.msg.html

(cl:defclass <GNSSAidingStatus> (roslisp-msg-protocol:ros-message)
  ((gps_tow
    :reader gps_tow
    :initarg :gps_tow
    :type cl:float
    :initform 0.0)
   (has_position_fix
    :reader has_position_fix
    :initarg :has_position_fix
    :type cl:boolean
    :initform cl:nil)
   (tight_coupling
    :reader tight_coupling
    :initarg :tight_coupling
    :type cl:boolean
    :initform cl:nil)
   (differential_corrections
    :reader differential_corrections
    :initarg :differential_corrections
    :type cl:boolean
    :initform cl:nil)
   (integer_fix
    :reader integer_fix
    :initarg :integer_fix
    :type cl:boolean
    :initform cl:nil)
   (using_gps
    :reader using_gps
    :initarg :using_gps
    :type cl:boolean
    :initform cl:nil)
   (using_glonass
    :reader using_glonass
    :initarg :using_glonass
    :type cl:boolean
    :initform cl:nil)
   (using_galileo
    :reader using_galileo
    :initarg :using_galileo
    :type cl:boolean
    :initform cl:nil)
   (using_beidou
    :reader using_beidou
    :initarg :using_beidou
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GNSSAidingStatus (<GNSSAidingStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GNSSAidingStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GNSSAidingStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<GNSSAidingStatus> is deprecated: use microstrain_inertial_msgs-msg:GNSSAidingStatus instead.")))

(cl:ensure-generic-function 'gps_tow-val :lambda-list '(m))
(cl:defmethod gps_tow-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_tow-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_tow instead.")
  (gps_tow m))

(cl:ensure-generic-function 'has_position_fix-val :lambda-list '(m))
(cl:defmethod has_position_fix-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:has_position_fix-val is deprecated.  Use microstrain_inertial_msgs-msg:has_position_fix instead.")
  (has_position_fix m))

(cl:ensure-generic-function 'tight_coupling-val :lambda-list '(m))
(cl:defmethod tight_coupling-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:tight_coupling-val is deprecated.  Use microstrain_inertial_msgs-msg:tight_coupling instead.")
  (tight_coupling m))

(cl:ensure-generic-function 'differential_corrections-val :lambda-list '(m))
(cl:defmethod differential_corrections-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:differential_corrections-val is deprecated.  Use microstrain_inertial_msgs-msg:differential_corrections instead.")
  (differential_corrections m))

(cl:ensure-generic-function 'integer_fix-val :lambda-list '(m))
(cl:defmethod integer_fix-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:integer_fix-val is deprecated.  Use microstrain_inertial_msgs-msg:integer_fix instead.")
  (integer_fix m))

(cl:ensure-generic-function 'using_gps-val :lambda-list '(m))
(cl:defmethod using_gps-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:using_gps-val is deprecated.  Use microstrain_inertial_msgs-msg:using_gps instead.")
  (using_gps m))

(cl:ensure-generic-function 'using_glonass-val :lambda-list '(m))
(cl:defmethod using_glonass-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:using_glonass-val is deprecated.  Use microstrain_inertial_msgs-msg:using_glonass instead.")
  (using_glonass m))

(cl:ensure-generic-function 'using_galileo-val :lambda-list '(m))
(cl:defmethod using_galileo-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:using_galileo-val is deprecated.  Use microstrain_inertial_msgs-msg:using_galileo instead.")
  (using_galileo m))

(cl:ensure-generic-function 'using_beidou-val :lambda-list '(m))
(cl:defmethod using_beidou-val ((m <GNSSAidingStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:using_beidou-val is deprecated.  Use microstrain_inertial_msgs-msg:using_beidou instead.")
  (using_beidou m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GNSSAidingStatus>) ostream)
  "Serializes a message object of type '<GNSSAidingStatus>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gps_tow))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'has_position_fix) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'tight_coupling) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'differential_corrections) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'integer_fix) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'using_gps) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'using_glonass) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'using_galileo) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'using_beidou) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GNSSAidingStatus>) istream)
  "Deserializes a message object of type '<GNSSAidingStatus>"
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
    (cl:setf (cl:slot-value msg 'has_position_fix) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'tight_coupling) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'differential_corrections) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'integer_fix) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'using_gps) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'using_glonass) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'using_galileo) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'using_beidou) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GNSSAidingStatus>)))
  "Returns string type for a message object of type '<GNSSAidingStatus>"
  "microstrain_inertial_msgs/GNSSAidingStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GNSSAidingStatus)))
  "Returns string type for a message object of type 'GNSSAidingStatus"
  "microstrain_inertial_msgs/GNSSAidingStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GNSSAidingStatus>)))
  "Returns md5sum for a message object of type '<GNSSAidingStatus>"
  "93a07537312a9e616123b06cec1efdf6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GNSSAidingStatus)))
  "Returns md5sum for a message object of type 'GNSSAidingStatus"
  "93a07537312a9e616123b06cec1efdf6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GNSSAidingStatus>)))
  "Returns full string definition for message of type '<GNSSAidingStatus>"
  (cl:format cl:nil "float64 gps_tow~%bool    has_position_fix~%bool    tight_coupling~%bool    differential_corrections~%bool    integer_fix~%bool    using_gps ~%bool    using_glonass~%bool    using_galileo~%bool    using_beidou~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GNSSAidingStatus)))
  "Returns full string definition for message of type 'GNSSAidingStatus"
  (cl:format cl:nil "float64 gps_tow~%bool    has_position_fix~%bool    tight_coupling~%bool    differential_corrections~%bool    integer_fix~%bool    using_gps ~%bool    using_glonass~%bool    using_galileo~%bool    using_beidou~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GNSSAidingStatus>))
  (cl:+ 0
     8
     1
     1
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GNSSAidingStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'GNSSAidingStatus
    (cl:cons ':gps_tow (gps_tow msg))
    (cl:cons ':has_position_fix (has_position_fix msg))
    (cl:cons ':tight_coupling (tight_coupling msg))
    (cl:cons ':differential_corrections (differential_corrections msg))
    (cl:cons ':integer_fix (integer_fix msg))
    (cl:cons ':using_gps (using_gps msg))
    (cl:cons ':using_glonass (using_glonass msg))
    (cl:cons ':using_galileo (using_galileo msg))
    (cl:cons ':using_beidou (using_beidou msg))
))
