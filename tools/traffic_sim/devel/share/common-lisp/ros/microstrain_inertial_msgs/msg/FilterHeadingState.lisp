; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude FilterHeadingState.msg.html

(cl:defclass <FilterHeadingState> (roslisp-msg-protocol:ros-message)
  ((heading_rad
    :reader heading_rad
    :initarg :heading_rad
    :type cl:float
    :initform 0.0)
   (heading_uncertainty
    :reader heading_uncertainty
    :initarg :heading_uncertainty
    :type cl:float
    :initform 0.0)
   (source
    :reader source
    :initarg :source
    :type cl:fixnum
    :initform 0)
   (status_flags
    :reader status_flags
    :initarg :status_flags
    :type cl:fixnum
    :initform 0))
)

(cl:defclass FilterHeadingState (<FilterHeadingState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FilterHeadingState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FilterHeadingState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<FilterHeadingState> is deprecated: use microstrain_inertial_msgs-msg:FilterHeadingState instead.")))

(cl:ensure-generic-function 'heading_rad-val :lambda-list '(m))
(cl:defmethod heading_rad-val ((m <FilterHeadingState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:heading_rad-val is deprecated.  Use microstrain_inertial_msgs-msg:heading_rad instead.")
  (heading_rad m))

(cl:ensure-generic-function 'heading_uncertainty-val :lambda-list '(m))
(cl:defmethod heading_uncertainty-val ((m <FilterHeadingState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:heading_uncertainty-val is deprecated.  Use microstrain_inertial_msgs-msg:heading_uncertainty instead.")
  (heading_uncertainty m))

(cl:ensure-generic-function 'source-val :lambda-list '(m))
(cl:defmethod source-val ((m <FilterHeadingState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:source-val is deprecated.  Use microstrain_inertial_msgs-msg:source instead.")
  (source m))

(cl:ensure-generic-function 'status_flags-val :lambda-list '(m))
(cl:defmethod status_flags-val ((m <FilterHeadingState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:status_flags-val is deprecated.  Use microstrain_inertial_msgs-msg:status_flags instead.")
  (status_flags m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FilterHeadingState>) ostream)
  "Serializes a message object of type '<FilterHeadingState>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_rad))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_uncertainty))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'source)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'source)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'status_flags)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FilterHeadingState>) istream)
  "Deserializes a message object of type '<FilterHeadingState>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_rad) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_uncertainty) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'source)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'source)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FilterHeadingState>)))
  "Returns string type for a message object of type '<FilterHeadingState>"
  "microstrain_inertial_msgs/FilterHeadingState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FilterHeadingState)))
  "Returns string type for a message object of type 'FilterHeadingState"
  "microstrain_inertial_msgs/FilterHeadingState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FilterHeadingState>)))
  "Returns md5sum for a message object of type '<FilterHeadingState>"
  "ca75e8c156e8551037af1d0f6d896ef2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FilterHeadingState)))
  "Returns md5sum for a message object of type 'FilterHeadingState"
  "ca75e8c156e8551037af1d0f6d896ef2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FilterHeadingState>)))
  "Returns full string definition for message of type '<FilterHeadingState>"
  (cl:format cl:nil "float32 heading_rad~%~%float32 heading_uncertainty~%~%uint16 source~%~%uint16 status_flags~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FilterHeadingState)))
  "Returns full string definition for message of type 'FilterHeadingState"
  (cl:format cl:nil "float32 heading_rad~%~%float32 heading_uncertainty~%~%uint16 source~%~%uint16 status_flags~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FilterHeadingState>))
  (cl:+ 0
     4
     4
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FilterHeadingState>))
  "Converts a ROS message object to a list"
  (cl:list 'FilterHeadingState
    (cl:cons ':heading_rad (heading_rad msg))
    (cl:cons ':heading_uncertainty (heading_uncertainty msg))
    (cl:cons ':source (source msg))
    (cl:cons ':status_flags (status_flags msg))
))
