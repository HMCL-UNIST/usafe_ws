; Auto-generated. Do not edit!


(cl:in-package autorally_msgs-msg)


;//! \htmlinclude runstop.msg.html

(cl:defclass <runstop> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (sender
    :reader sender
    :initarg :sender
    :type cl:string
    :initform "")
   (motionEnabled
    :reader motionEnabled
    :initarg :motionEnabled
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass runstop (<runstop>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <runstop>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'runstop)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autorally_msgs-msg:<runstop> is deprecated: use autorally_msgs-msg:runstop instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <runstop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:header-val is deprecated.  Use autorally_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'sender-val :lambda-list '(m))
(cl:defmethod sender-val ((m <runstop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:sender-val is deprecated.  Use autorally_msgs-msg:sender instead.")
  (sender m))

(cl:ensure-generic-function 'motionEnabled-val :lambda-list '(m))
(cl:defmethod motionEnabled-val ((m <runstop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:motionEnabled-val is deprecated.  Use autorally_msgs-msg:motionEnabled instead.")
  (motionEnabled m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <runstop>) ostream)
  "Serializes a message object of type '<runstop>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'sender))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'sender))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'motionEnabled) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <runstop>) istream)
  "Deserializes a message object of type '<runstop>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sender) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'sender) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:slot-value msg 'motionEnabled) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<runstop>)))
  "Returns string type for a message object of type '<runstop>"
  "autorally_msgs/runstop")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'runstop)))
  "Returns string type for a message object of type 'runstop"
  "autorally_msgs/runstop")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<runstop>)))
  "Returns md5sum for a message object of type '<runstop>"
  "996dff250e70bc8cde0b272375a5684d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'runstop)))
  "Returns md5sum for a message object of type 'runstop"
  "996dff250e70bc8cde0b272375a5684d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<runstop>)))
  "Returns full string definition for message of type '<runstop>"
  (cl:format cl:nil "Header header~%~%string sender~%bool motionEnabled~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'runstop)))
  "Returns full string definition for message of type 'runstop"
  (cl:format cl:nil "Header header~%~%string sender~%bool motionEnabled~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <runstop>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:length (cl:slot-value msg 'sender))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <runstop>))
  "Converts a ROS message object to a list"
  (cl:list 'runstop
    (cl:cons ':header (header msg))
    (cl:cons ':sender (sender msg))
    (cl:cons ':motionEnabled (motionEnabled msg))
))
