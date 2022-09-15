; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_system_warnings.msg.html

(cl:defclass <MobileyeInfo_system_warnings> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (system_warnings
    :reader system_warnings
    :initarg :system_warnings
    :type mobileye_msgs-msg:SystemWarnings
    :initform (cl:make-instance 'mobileye_msgs-msg:SystemWarnings)))
)

(cl:defclass MobileyeInfo_system_warnings (<MobileyeInfo_system_warnings>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_system_warnings>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_system_warnings)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_system_warnings> is deprecated: use mobileye_msgs-msg:MobileyeInfo_system_warnings instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_system_warnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'system_warnings-val :lambda-list '(m))
(cl:defmethod system_warnings-val ((m <MobileyeInfo_system_warnings>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:system_warnings-val is deprecated.  Use mobileye_msgs-msg:system_warnings instead.")
  (system_warnings m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_system_warnings>) ostream)
  "Serializes a message object of type '<MobileyeInfo_system_warnings>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'system_warnings) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_system_warnings>) istream)
  "Deserializes a message object of type '<MobileyeInfo_system_warnings>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'system_warnings) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_system_warnings>)))
  "Returns string type for a message object of type '<MobileyeInfo_system_warnings>"
  "mobileye_msgs/MobileyeInfo_system_warnings")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_system_warnings)))
  "Returns string type for a message object of type 'MobileyeInfo_system_warnings"
  "mobileye_msgs/MobileyeInfo_system_warnings")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_system_warnings>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_system_warnings>"
  "e70b067bf40c41c403fb3be0e8758d41")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_system_warnings)))
  "Returns md5sum for a message object of type 'MobileyeInfo_system_warnings"
  "e70b067bf40c41c403fb3be0e8758d41")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_system_warnings>)))
  "Returns full string definition for message of type '<MobileyeInfo_system_warnings>"
  (cl:format cl:nil "Header header~%~%SystemWarnings system_warnings~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/SystemWarnings~%uint8 sound_type~%bool peds_in_dz~%bool peds_fcw~%uint8 time_indicator~%~%bool error_valid~%uint8 error_code~%bool zero_speed~%bool headway_valid~%float32 headway_measurement~%~%bool ldw_off~%bool left_ldw_on~%bool right_ldw_on~%bool fcw_on~%bool maintenance~%bool failsafe~%~%bool tsr_enabled~%bool hw_repeatable_enabled~%uint8 headway_warning_level~%uint8 tsr_warning_level~%bool tamper_alert~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_system_warnings)))
  "Returns full string definition for message of type 'MobileyeInfo_system_warnings"
  (cl:format cl:nil "Header header~%~%SystemWarnings system_warnings~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/SystemWarnings~%uint8 sound_type~%bool peds_in_dz~%bool peds_fcw~%uint8 time_indicator~%~%bool error_valid~%uint8 error_code~%bool zero_speed~%bool headway_valid~%float32 headway_measurement~%~%bool ldw_off~%bool left_ldw_on~%bool right_ldw_on~%bool fcw_on~%bool maintenance~%bool failsafe~%~%bool tsr_enabled~%bool hw_repeatable_enabled~%uint8 headway_warning_level~%uint8 tsr_warning_level~%bool tamper_alert~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_system_warnings>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'system_warnings))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_system_warnings>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_system_warnings
    (cl:cons ':header (header msg))
    (cl:cons ':system_warnings (system_warnings msg))
))
