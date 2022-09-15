; Auto-generated. Do not edit!


(cl:in-package autorally_msgs-msg)


;//! \htmlinclude stateEstimatorStatus.msg.html

(cl:defclass <stateEstimatorStatus> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (status
    :reader status
    :initarg :status
    :type cl:integer
    :initform 0))
)

(cl:defclass stateEstimatorStatus (<stateEstimatorStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <stateEstimatorStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'stateEstimatorStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autorally_msgs-msg:<stateEstimatorStatus> is deprecated: use autorally_msgs-msg:stateEstimatorStatus instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <stateEstimatorStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:header-val is deprecated.  Use autorally_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <stateEstimatorStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:status-val is deprecated.  Use autorally_msgs-msg:status instead.")
  (status m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<stateEstimatorStatus>)))
    "Constants for message type '<stateEstimatorStatus>"
  '((:OK . 0)
    (:WARN . 1)
    (:ERROR . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'stateEstimatorStatus)))
    "Constants for message type 'stateEstimatorStatus"
  '((:OK . 0)
    (:WARN . 1)
    (:ERROR . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <stateEstimatorStatus>) ostream)
  "Serializes a message object of type '<stateEstimatorStatus>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <stateEstimatorStatus>) istream)
  "Deserializes a message object of type '<stateEstimatorStatus>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<stateEstimatorStatus>)))
  "Returns string type for a message object of type '<stateEstimatorStatus>"
  "autorally_msgs/stateEstimatorStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'stateEstimatorStatus)))
  "Returns string type for a message object of type 'stateEstimatorStatus"
  "autorally_msgs/stateEstimatorStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<stateEstimatorStatus>)))
  "Returns md5sum for a message object of type '<stateEstimatorStatus>"
  "35699761f8100be9b6c52444c8cfff99")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'stateEstimatorStatus)))
  "Returns md5sum for a message object of type 'stateEstimatorStatus"
  "35699761f8100be9b6c52444c8cfff99")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<stateEstimatorStatus>)))
  "Returns full string definition for message of type '<stateEstimatorStatus>"
  (cl:format cl:nil "# message for communicating the status of the state estimator~%Header header~%~%# possible statuses~%byte OK=0     # standard operation~%byte WARN=1   # state estimator is not currently trustworthy~%byte ERROR=2  # state estimator has encountered an unrecoverable error~%~%byte status # status types enumerated above~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'stateEstimatorStatus)))
  "Returns full string definition for message of type 'stateEstimatorStatus"
  (cl:format cl:nil "# message for communicating the status of the state estimator~%Header header~%~%# possible statuses~%byte OK=0     # standard operation~%byte WARN=1   # state estimator is not currently trustworthy~%byte ERROR=2  # state estimator has encountered an unrecoverable error~%~%byte status # status types enumerated above~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <stateEstimatorStatus>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <stateEstimatorStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'stateEstimatorStatus
    (cl:cons ':header (header msg))
    (cl:cons ':status (status msg))
))
