; Auto-generated. Do not edit!


(cl:in-package autorally_msgs-msg)


;//! \htmlinclude chassisState.msg.html

(cl:defclass <chassisState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (throttleRelayEnabled
    :reader throttleRelayEnabled
    :initarg :throttleRelayEnabled
    :type cl:boolean
    :initform cl:nil)
   (autonomousEnabled
    :reader autonomousEnabled
    :initarg :autonomousEnabled
    :type cl:boolean
    :initform cl:nil)
   (runstopMotionEnabled
    :reader runstopMotionEnabled
    :initarg :runstopMotionEnabled
    :type cl:boolean
    :initform cl:nil)
   (steeringCommander
    :reader steeringCommander
    :initarg :steeringCommander
    :type cl:string
    :initform "")
   (steering
    :reader steering
    :initarg :steering
    :type cl:float
    :initform 0.0)
   (throttleCommander
    :reader throttleCommander
    :initarg :throttleCommander
    :type cl:string
    :initform "")
   (throttle
    :reader throttle
    :initarg :throttle
    :type cl:float
    :initform 0.0)
   (frontBrakeCommander
    :reader frontBrakeCommander
    :initarg :frontBrakeCommander
    :type cl:string
    :initform "")
   (frontBrake
    :reader frontBrake
    :initarg :frontBrake
    :type cl:float
    :initform 0.0))
)

(cl:defclass chassisState (<chassisState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <chassisState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'chassisState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autorally_msgs-msg:<chassisState> is deprecated: use autorally_msgs-msg:chassisState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:header-val is deprecated.  Use autorally_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'throttleRelayEnabled-val :lambda-list '(m))
(cl:defmethod throttleRelayEnabled-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:throttleRelayEnabled-val is deprecated.  Use autorally_msgs-msg:throttleRelayEnabled instead.")
  (throttleRelayEnabled m))

(cl:ensure-generic-function 'autonomousEnabled-val :lambda-list '(m))
(cl:defmethod autonomousEnabled-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:autonomousEnabled-val is deprecated.  Use autorally_msgs-msg:autonomousEnabled instead.")
  (autonomousEnabled m))

(cl:ensure-generic-function 'runstopMotionEnabled-val :lambda-list '(m))
(cl:defmethod runstopMotionEnabled-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:runstopMotionEnabled-val is deprecated.  Use autorally_msgs-msg:runstopMotionEnabled instead.")
  (runstopMotionEnabled m))

(cl:ensure-generic-function 'steeringCommander-val :lambda-list '(m))
(cl:defmethod steeringCommander-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:steeringCommander-val is deprecated.  Use autorally_msgs-msg:steeringCommander instead.")
  (steeringCommander m))

(cl:ensure-generic-function 'steering-val :lambda-list '(m))
(cl:defmethod steering-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:steering-val is deprecated.  Use autorally_msgs-msg:steering instead.")
  (steering m))

(cl:ensure-generic-function 'throttleCommander-val :lambda-list '(m))
(cl:defmethod throttleCommander-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:throttleCommander-val is deprecated.  Use autorally_msgs-msg:throttleCommander instead.")
  (throttleCommander m))

(cl:ensure-generic-function 'throttle-val :lambda-list '(m))
(cl:defmethod throttle-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:throttle-val is deprecated.  Use autorally_msgs-msg:throttle instead.")
  (throttle m))

(cl:ensure-generic-function 'frontBrakeCommander-val :lambda-list '(m))
(cl:defmethod frontBrakeCommander-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:frontBrakeCommander-val is deprecated.  Use autorally_msgs-msg:frontBrakeCommander instead.")
  (frontBrakeCommander m))

(cl:ensure-generic-function 'frontBrake-val :lambda-list '(m))
(cl:defmethod frontBrake-val ((m <chassisState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:frontBrake-val is deprecated.  Use autorally_msgs-msg:frontBrake instead.")
  (frontBrake m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <chassisState>) ostream)
  "Serializes a message object of type '<chassisState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'throttleRelayEnabled) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'autonomousEnabled) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'runstopMotionEnabled) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'steeringCommander))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'steeringCommander))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'steering))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'throttleCommander))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'throttleCommander))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'throttle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'frontBrakeCommander))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'frontBrakeCommander))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'frontBrake))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <chassisState>) istream)
  "Deserializes a message object of type '<chassisState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:slot-value msg 'throttleRelayEnabled) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'autonomousEnabled) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'runstopMotionEnabled) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'steeringCommander) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'steeringCommander) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'throttleCommander) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'throttleCommander) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'throttle) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frontBrakeCommander) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'frontBrakeCommander) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'frontBrake) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<chassisState>)))
  "Returns string type for a message object of type '<chassisState>"
  "autorally_msgs/chassisState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'chassisState)))
  "Returns string type for a message object of type 'chassisState"
  "autorally_msgs/chassisState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<chassisState>)))
  "Returns md5sum for a message object of type '<chassisState>"
  "cbd23a33a5ec266cc70ab1630ddbccef")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'chassisState)))
  "Returns md5sum for a message object of type 'chassisState"
  "cbd23a33a5ec266cc70ab1630ddbccef")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<chassisState>)))
  "Returns full string definition for message of type '<chassisState>"
  (cl:format cl:nil "Header header~%~%bool throttleRelayEnabled~%bool autonomousEnabled~%bool runstopMotionEnabled~%~%string steeringCommander~%float64 steering~%~%string throttleCommander~%float64 throttle~%~%string frontBrakeCommander~%float64 frontBrake~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'chassisState)))
  "Returns full string definition for message of type 'chassisState"
  (cl:format cl:nil "Header header~%~%bool throttleRelayEnabled~%bool autonomousEnabled~%bool runstopMotionEnabled~%~%string steeringCommander~%float64 steering~%~%string throttleCommander~%float64 throttle~%~%string frontBrakeCommander~%float64 frontBrake~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <chassisState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     1
     4 (cl:length (cl:slot-value msg 'steeringCommander))
     8
     4 (cl:length (cl:slot-value msg 'throttleCommander))
     8
     4 (cl:length (cl:slot-value msg 'frontBrakeCommander))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <chassisState>))
  "Converts a ROS message object to a list"
  (cl:list 'chassisState
    (cl:cons ':header (header msg))
    (cl:cons ':throttleRelayEnabled (throttleRelayEnabled msg))
    (cl:cons ':autonomousEnabled (autonomousEnabled msg))
    (cl:cons ':runstopMotionEnabled (runstopMotionEnabled msg))
    (cl:cons ':steeringCommander (steeringCommander msg))
    (cl:cons ':steering (steering msg))
    (cl:cons ':throttleCommander (throttleCommander msg))
    (cl:cons ':throttle (throttle msg))
    (cl:cons ':frontBrakeCommander (frontBrakeCommander msg))
    (cl:cons ':frontBrake (frontBrake msg))
))
