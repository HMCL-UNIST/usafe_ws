; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude GNSSFixInfo.msg.html

(cl:defclass <GNSSFixInfo> (roslisp-msg-protocol:ros-message)
  ((fix_type
    :reader fix_type
    :initarg :fix_type
    :type cl:fixnum
    :initform 0)
   (num_sv
    :reader num_sv
    :initarg :num_sv
    :type cl:fixnum
    :initform 0)
   (sbas_used
    :reader sbas_used
    :initarg :sbas_used
    :type cl:boolean
    :initform cl:nil)
   (dngss_used
    :reader dngss_used
    :initarg :dngss_used
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GNSSFixInfo (<GNSSFixInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GNSSFixInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GNSSFixInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<GNSSFixInfo> is deprecated: use microstrain_inertial_msgs-msg:GNSSFixInfo instead.")))

(cl:ensure-generic-function 'fix_type-val :lambda-list '(m))
(cl:defmethod fix_type-val ((m <GNSSFixInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:fix_type-val is deprecated.  Use microstrain_inertial_msgs-msg:fix_type instead.")
  (fix_type m))

(cl:ensure-generic-function 'num_sv-val :lambda-list '(m))
(cl:defmethod num_sv-val ((m <GNSSFixInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:num_sv-val is deprecated.  Use microstrain_inertial_msgs-msg:num_sv instead.")
  (num_sv m))

(cl:ensure-generic-function 'sbas_used-val :lambda-list '(m))
(cl:defmethod sbas_used-val ((m <GNSSFixInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:sbas_used-val is deprecated.  Use microstrain_inertial_msgs-msg:sbas_used instead.")
  (sbas_used m))

(cl:ensure-generic-function 'dngss_used-val :lambda-list '(m))
(cl:defmethod dngss_used-val ((m <GNSSFixInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dngss_used-val is deprecated.  Use microstrain_inertial_msgs-msg:dngss_used instead.")
  (dngss_used m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<GNSSFixInfo>)))
    "Constants for message type '<GNSSFixInfo>"
  '((:FIX_3D . 0)
    (:FIX_2D . 1)
    (:FIX_TIME_ONLY . 2)
    (:FIX_NONE . 3)
    (:FIX_INVALID . 4)
    (:FIX_RTK_FLOAT . 5)
    (:FIX_RTK_FIXED . 6))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'GNSSFixInfo)))
    "Constants for message type 'GNSSFixInfo"
  '((:FIX_3D . 0)
    (:FIX_2D . 1)
    (:FIX_TIME_ONLY . 2)
    (:FIX_NONE . 3)
    (:FIX_INVALID . 4)
    (:FIX_RTK_FLOAT . 5)
    (:FIX_RTK_FIXED . 6))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GNSSFixInfo>) ostream)
  "Serializes a message object of type '<GNSSFixInfo>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'fix_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num_sv)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'sbas_used) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'dngss_used) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GNSSFixInfo>) istream)
  "Deserializes a message object of type '<GNSSFixInfo>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'fix_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'num_sv)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sbas_used) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'dngss_used) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GNSSFixInfo>)))
  "Returns string type for a message object of type '<GNSSFixInfo>"
  "microstrain_inertial_msgs/GNSSFixInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GNSSFixInfo)))
  "Returns string type for a message object of type 'GNSSFixInfo"
  "microstrain_inertial_msgs/GNSSFixInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GNSSFixInfo>)))
  "Returns md5sum for a message object of type '<GNSSFixInfo>"
  "cb3314532886b25255798400e78fc222")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GNSSFixInfo)))
  "Returns md5sum for a message object of type 'GNSSFixInfo"
  "cb3314532886b25255798400e78fc222")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GNSSFixInfo>)))
  "Returns full string definition for message of type '<GNSSFixInfo>"
  (cl:format cl:nil "uint8 fix_type~%uint8 num_sv~%bool sbas_used~%bool dngss_used~%~%uint8 FIX_3D = 0~%uint8 FIX_2D = 1~%uint8 FIX_TIME_ONLY = 2~%uint8 FIX_NONE = 3~%uint8 FIX_INVALID = 4~%uint8 FIX_RTK_FLOAT = 5~%uint8 FIX_RTK_FIXED = 6~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GNSSFixInfo)))
  "Returns full string definition for message of type 'GNSSFixInfo"
  (cl:format cl:nil "uint8 fix_type~%uint8 num_sv~%bool sbas_used~%bool dngss_used~%~%uint8 FIX_3D = 0~%uint8 FIX_2D = 1~%uint8 FIX_TIME_ONLY = 2~%uint8 FIX_NONE = 3~%uint8 FIX_INVALID = 4~%uint8 FIX_RTK_FLOAT = 5~%uint8 FIX_RTK_FIXED = 6~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GNSSFixInfo>))
  (cl:+ 0
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GNSSFixInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'GNSSFixInfo
    (cl:cons ':fix_type (fix_type msg))
    (cl:cons ':num_sv (num_sv msg))
    (cl:cons ':sbas_used (sbas_used msg))
    (cl:cons ':dngss_used (dngss_used msg))
))
