; Auto-generated. Do not edit!


(cl:in-package autorally_msgs-msg)


;//! \htmlinclude pathIntegralTiming.msg.html

(cl:defclass <pathIntegralTiming> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (averageTimeBetweenPoses
    :reader averageTimeBetweenPoses
    :initarg :averageTimeBetweenPoses
    :type cl:float
    :initform 0.0)
   (averageOptimizationCycleTime
    :reader averageOptimizationCycleTime
    :initarg :averageOptimizationCycleTime
    :type cl:float
    :initform 0.0)
   (averageSleepTime
    :reader averageSleepTime
    :initarg :averageSleepTime
    :type cl:float
    :initform 0.0))
)

(cl:defclass pathIntegralTiming (<pathIntegralTiming>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pathIntegralTiming>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pathIntegralTiming)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autorally_msgs-msg:<pathIntegralTiming> is deprecated: use autorally_msgs-msg:pathIntegralTiming instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <pathIntegralTiming>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:header-val is deprecated.  Use autorally_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'averageTimeBetweenPoses-val :lambda-list '(m))
(cl:defmethod averageTimeBetweenPoses-val ((m <pathIntegralTiming>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:averageTimeBetweenPoses-val is deprecated.  Use autorally_msgs-msg:averageTimeBetweenPoses instead.")
  (averageTimeBetweenPoses m))

(cl:ensure-generic-function 'averageOptimizationCycleTime-val :lambda-list '(m))
(cl:defmethod averageOptimizationCycleTime-val ((m <pathIntegralTiming>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:averageOptimizationCycleTime-val is deprecated.  Use autorally_msgs-msg:averageOptimizationCycleTime instead.")
  (averageOptimizationCycleTime m))

(cl:ensure-generic-function 'averageSleepTime-val :lambda-list '(m))
(cl:defmethod averageSleepTime-val ((m <pathIntegralTiming>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:averageSleepTime-val is deprecated.  Use autorally_msgs-msg:averageSleepTime instead.")
  (averageSleepTime m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pathIntegralTiming>) ostream)
  "Serializes a message object of type '<pathIntegralTiming>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'averageTimeBetweenPoses))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'averageOptimizationCycleTime))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'averageSleepTime))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pathIntegralTiming>) istream)
  "Deserializes a message object of type '<pathIntegralTiming>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'averageTimeBetweenPoses) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'averageOptimizationCycleTime) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'averageSleepTime) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pathIntegralTiming>)))
  "Returns string type for a message object of type '<pathIntegralTiming>"
  "autorally_msgs/pathIntegralTiming")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pathIntegralTiming)))
  "Returns string type for a message object of type 'pathIntegralTiming"
  "autorally_msgs/pathIntegralTiming")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pathIntegralTiming>)))
  "Returns md5sum for a message object of type '<pathIntegralTiming>"
  "3b1cf4994787687384fe2dcbe9c92b69")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pathIntegralTiming)))
  "Returns md5sum for a message object of type 'pathIntegralTiming"
  "3b1cf4994787687384fe2dcbe9c92b69")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pathIntegralTiming>)))
  "Returns full string definition for message of type '<pathIntegralTiming>"
  (cl:format cl:nil "Header header~%~%float64 averageTimeBetweenPoses~%float64 averageOptimizationCycleTime~%float64 averageSleepTime~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pathIntegralTiming)))
  "Returns full string definition for message of type 'pathIntegralTiming"
  (cl:format cl:nil "Header header~%~%float64 averageTimeBetweenPoses~%float64 averageOptimizationCycleTime~%float64 averageSleepTime~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pathIntegralTiming>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pathIntegralTiming>))
  "Converts a ROS message object to a list"
  (cl:list 'pathIntegralTiming
    (cl:cons ':header (header msg))
    (cl:cons ':averageTimeBetweenPoses (averageTimeBetweenPoses msg))
    (cl:cons ':averageOptimizationCycleTime (averageOptimizationCycleTime msg))
    (cl:cons ':averageSleepTime (averageSleepTime msg))
))
