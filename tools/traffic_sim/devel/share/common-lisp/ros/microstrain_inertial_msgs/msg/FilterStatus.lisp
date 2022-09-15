; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude FilterStatus.msg.html

(cl:defclass <FilterStatus> (roslisp-msg-protocol:ros-message)
  ((filter_state
    :reader filter_state
    :initarg :filter_state
    :type cl:fixnum
    :initform 0)
   (dynamics_mode
    :reader dynamics_mode
    :initarg :dynamics_mode
    :type cl:fixnum
    :initform 0)
   (status_flags
    :reader status_flags
    :initarg :status_flags
    :type cl:fixnum
    :initform 0))
)

(cl:defclass FilterStatus (<FilterStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FilterStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FilterStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<FilterStatus> is deprecated: use microstrain_inertial_msgs-msg:FilterStatus instead.")))

(cl:ensure-generic-function 'filter_state-val :lambda-list '(m))
(cl:defmethod filter_state-val ((m <FilterStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:filter_state-val is deprecated.  Use microstrain_inertial_msgs-msg:filter_state instead.")
  (filter_state m))

(cl:ensure-generic-function 'dynamics_mode-val :lambda-list '(m))
(cl:defmethod dynamics_mode-val ((m <FilterStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:dynamics_mode-val is deprecated.  Use microstrain_inertial_msgs-msg:dynamics_mode instead.")
  (dynamics_mode m))

(cl:ensure-generic-function 'status_flags-val :lambda-list '(m))
(cl:defmethod status_flags-val ((m <FilterStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:status_flags-val is deprecated.  Use microstrain_inertial_msgs-msg:status_flags instead.")
  (status_flags m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FilterStatus>) ostream)
  "Serializes a message object of type '<FilterStatus>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'filter_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'filter_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dynamics_mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'dynamics_mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_flags)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'status_flags)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FilterStatus>) istream)
  "Deserializes a message object of type '<FilterStatus>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'filter_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'filter_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dynamics_mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'dynamics_mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'status_flags)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FilterStatus>)))
  "Returns string type for a message object of type '<FilterStatus>"
  "microstrain_inertial_msgs/FilterStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FilterStatus)))
  "Returns string type for a message object of type 'FilterStatus"
  "microstrain_inertial_msgs/FilterStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FilterStatus>)))
  "Returns md5sum for a message object of type '<FilterStatus>"
  "44b6cdd5e336c9a880e785b76ea6be97")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FilterStatus)))
  "Returns md5sum for a message object of type 'FilterStatus"
  "44b6cdd5e336c9a880e785b76ea6be97")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FilterStatus>)))
  "Returns full string definition for message of type '<FilterStatus>"
  (cl:format cl:nil "uint16 filter_state~%~%uint16 dynamics_mode~%~%uint16 status_flags~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FilterStatus)))
  "Returns full string definition for message of type 'FilterStatus"
  (cl:format cl:nil "uint16 filter_state~%~%uint16 dynamics_mode~%~%uint16 status_flags~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FilterStatus>))
  (cl:+ 0
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FilterStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'FilterStatus
    (cl:cons ':filter_state (filter_state msg))
    (cl:cons ':dynamics_mode (dynamics_mode msg))
    (cl:cons ':status_flags (status_flags msg))
))
