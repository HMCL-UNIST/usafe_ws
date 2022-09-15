; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude FilterHeading.msg.html

(cl:defclass <FilterHeading> (roslisp-msg-protocol:ros-message)
  ((heading_deg
    :reader heading_deg
    :initarg :heading_deg
    :type cl:float
    :initform 0.0)
   (heading_rad
    :reader heading_rad
    :initarg :heading_rad
    :type cl:float
    :initform 0.0)
   (status_flags
    :reader status_flags
    :initarg :status_flags
    :type cl:fixnum
    :initform 0))
)

(cl:defclass FilterHeading (<FilterHeading>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FilterHeading>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FilterHeading)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<FilterHeading> is deprecated: use microstrain_inertial_msgs-msg:FilterHeading instead.")))

(cl:ensure-generic-function 'heading_deg-val :lambda-list '(m))
(cl:defmethod heading_deg-val ((m <FilterHeading>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:heading_deg-val is deprecated.  Use microstrain_inertial_msgs-msg:heading_deg instead.")
  (heading_deg m))

(cl:ensure-generic-function 'heading_rad-val :lambda-list '(m))
(cl:defmethod heading_rad-val ((m <FilterHeading>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:heading_rad-val is deprecated.  Use microstrain_inertial_msgs-msg:heading_rad instead.")
  (heading_rad m))

(cl:ensure-generic-function 'status_flags-val :lambda-list '(m))
(cl:defmethod status_flags-val ((m <FilterHeading>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:status_flags-val is deprecated.  Use microstrain_inertial_msgs-msg:status_flags instead.")
  (status_flags m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FilterHeading>) ostream)
  "Serializes a message object of type '<FilterHeading>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_deg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_rad))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'status_flags)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FilterHeading>) istream)
  "Deserializes a message object of type '<FilterHeading>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_deg) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_rad) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FilterHeading>)))
  "Returns string type for a message object of type '<FilterHeading>"
  "microstrain_inertial_msgs/FilterHeading")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FilterHeading)))
  "Returns string type for a message object of type 'FilterHeading"
  "microstrain_inertial_msgs/FilterHeading")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FilterHeading>)))
  "Returns md5sum for a message object of type '<FilterHeading>"
  "b90b446055a9cca548055d2a70764344")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FilterHeading)))
  "Returns md5sum for a message object of type 'FilterHeading"
  "b90b446055a9cca548055d2a70764344")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FilterHeading>)))
  "Returns full string definition for message of type '<FilterHeading>"
  (cl:format cl:nil "float32 heading_deg~%~%float32 heading_rad~%~%uint16 status_flags~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FilterHeading)))
  "Returns full string definition for message of type 'FilterHeading"
  (cl:format cl:nil "float32 heading_deg~%~%float32 heading_rad~%~%uint16 status_flags~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FilterHeading>))
  (cl:+ 0
     4
     4
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FilterHeading>))
  "Converts a ROS message object to a list"
  (cl:list 'FilterHeading
    (cl:cons ':heading_deg (heading_deg msg))
    (cl:cons ':heading_rad (heading_rad msg))
    (cl:cons ':status_flags (status_flags msg))
))
