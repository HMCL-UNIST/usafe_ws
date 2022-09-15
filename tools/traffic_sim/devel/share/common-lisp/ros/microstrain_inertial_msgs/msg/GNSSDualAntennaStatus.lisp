; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude GNSSDualAntennaStatus.msg.html

(cl:defclass <GNSSDualAntennaStatus> (roslisp-msg-protocol:ros-message)
  ((gps_tow
    :reader gps_tow
    :initarg :gps_tow
    :type cl:float
    :initform 0.0)
   (heading
    :reader heading
    :initarg :heading
    :type cl:float
    :initform 0.0)
   (heading_uncertainty
    :reader heading_uncertainty
    :initarg :heading_uncertainty
    :type cl:float
    :initform 0.0)
   (fix_type
    :reader fix_type
    :initarg :fix_type
    :type cl:fixnum
    :initform 0)
   (rcv_1_valid
    :reader rcv_1_valid
    :initarg :rcv_1_valid
    :type cl:fixnum
    :initform 0)
   (rcv_2_valid
    :reader rcv_2_valid
    :initarg :rcv_2_valid
    :type cl:fixnum
    :initform 0)
   (antenna_offsets_valid
    :reader antenna_offsets_valid
    :initarg :antenna_offsets_valid
    :type cl:fixnum
    :initform 0))
)

(cl:defclass GNSSDualAntennaStatus (<GNSSDualAntennaStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GNSSDualAntennaStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GNSSDualAntennaStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<GNSSDualAntennaStatus> is deprecated: use microstrain_inertial_msgs-msg:GNSSDualAntennaStatus instead.")))

(cl:ensure-generic-function 'gps_tow-val :lambda-list '(m))
(cl:defmethod gps_tow-val ((m <GNSSDualAntennaStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:gps_tow-val is deprecated.  Use microstrain_inertial_msgs-msg:gps_tow instead.")
  (gps_tow m))

(cl:ensure-generic-function 'heading-val :lambda-list '(m))
(cl:defmethod heading-val ((m <GNSSDualAntennaStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:heading-val is deprecated.  Use microstrain_inertial_msgs-msg:heading instead.")
  (heading m))

(cl:ensure-generic-function 'heading_uncertainty-val :lambda-list '(m))
(cl:defmethod heading_uncertainty-val ((m <GNSSDualAntennaStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:heading_uncertainty-val is deprecated.  Use microstrain_inertial_msgs-msg:heading_uncertainty instead.")
  (heading_uncertainty m))

(cl:ensure-generic-function 'fix_type-val :lambda-list '(m))
(cl:defmethod fix_type-val ((m <GNSSDualAntennaStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:fix_type-val is deprecated.  Use microstrain_inertial_msgs-msg:fix_type instead.")
  (fix_type m))

(cl:ensure-generic-function 'rcv_1_valid-val :lambda-list '(m))
(cl:defmethod rcv_1_valid-val ((m <GNSSDualAntennaStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:rcv_1_valid-val is deprecated.  Use microstrain_inertial_msgs-msg:rcv_1_valid instead.")
  (rcv_1_valid m))

(cl:ensure-generic-function 'rcv_2_valid-val :lambda-list '(m))
(cl:defmethod rcv_2_valid-val ((m <GNSSDualAntennaStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:rcv_2_valid-val is deprecated.  Use microstrain_inertial_msgs-msg:rcv_2_valid instead.")
  (rcv_2_valid m))

(cl:ensure-generic-function 'antenna_offsets_valid-val :lambda-list '(m))
(cl:defmethod antenna_offsets_valid-val ((m <GNSSDualAntennaStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:antenna_offsets_valid-val is deprecated.  Use microstrain_inertial_msgs-msg:antenna_offsets_valid instead.")
  (antenna_offsets_valid m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GNSSDualAntennaStatus>) ostream)
  "Serializes a message object of type '<GNSSDualAntennaStatus>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gps_tow))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_uncertainty))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'fix_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rcv_1_valid)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rcv_2_valid)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'antenna_offsets_valid)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GNSSDualAntennaStatus>) istream)
  "Deserializes a message object of type '<GNSSDualAntennaStatus>"
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
    (cl:setf (cl:slot-value msg 'heading) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_uncertainty) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'fix_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rcv_1_valid)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rcv_2_valid)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'antenna_offsets_valid)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GNSSDualAntennaStatus>)))
  "Returns string type for a message object of type '<GNSSDualAntennaStatus>"
  "microstrain_inertial_msgs/GNSSDualAntennaStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GNSSDualAntennaStatus)))
  "Returns string type for a message object of type 'GNSSDualAntennaStatus"
  "microstrain_inertial_msgs/GNSSDualAntennaStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GNSSDualAntennaStatus>)))
  "Returns md5sum for a message object of type '<GNSSDualAntennaStatus>"
  "efecf4f9bdf572f04f6f06ccc9c1095a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GNSSDualAntennaStatus)))
  "Returns md5sum for a message object of type 'GNSSDualAntennaStatus"
  "efecf4f9bdf572f04f6f06ccc9c1095a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GNSSDualAntennaStatus>)))
  "Returns full string definition for message of type '<GNSSDualAntennaStatus>"
  (cl:format cl:nil "float32 gps_tow~%float32 heading~%float32 heading_uncertainty~%uint8   fix_type~%uint8   rcv_1_valid~%uint8   rcv_2_valid~%uint8   antenna_offsets_valid~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GNSSDualAntennaStatus)))
  "Returns full string definition for message of type 'GNSSDualAntennaStatus"
  (cl:format cl:nil "float32 gps_tow~%float32 heading~%float32 heading_uncertainty~%uint8   fix_type~%uint8   rcv_1_valid~%uint8   rcv_2_valid~%uint8   antenna_offsets_valid~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GNSSDualAntennaStatus>))
  (cl:+ 0
     4
     4
     4
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GNSSDualAntennaStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'GNSSDualAntennaStatus
    (cl:cons ':gps_tow (gps_tow msg))
    (cl:cons ':heading (heading msg))
    (cl:cons ':heading_uncertainty (heading_uncertainty msg))
    (cl:cons ':fix_type (fix_type msg))
    (cl:cons ':rcv_1_valid (rcv_1_valid msg))
    (cl:cons ':rcv_2_valid (rcv_2_valid msg))
    (cl:cons ':antenna_offsets_valid (antenna_offsets_valid msg))
))
