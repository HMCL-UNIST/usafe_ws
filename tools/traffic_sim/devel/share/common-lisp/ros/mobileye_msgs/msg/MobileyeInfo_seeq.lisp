; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_seeq.msg.html

(cl:defclass <MobileyeInfo_seeq> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (seeq
    :reader seeq
    :initarg :seeq
    :type mobileye_msgs-msg:SeeQ
    :initform (cl:make-instance 'mobileye_msgs-msg:SeeQ)))
)

(cl:defclass MobileyeInfo_seeq (<MobileyeInfo_seeq>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_seeq>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_seeq)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_seeq> is deprecated: use mobileye_msgs-msg:MobileyeInfo_seeq instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_seeq>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'seeq-val :lambda-list '(m))
(cl:defmethod seeq-val ((m <MobileyeInfo_seeq>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:seeq-val is deprecated.  Use mobileye_msgs-msg:seeq instead.")
  (seeq m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_seeq>) ostream)
  "Serializes a message object of type '<MobileyeInfo_seeq>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'seeq) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_seeq>) istream)
  "Deserializes a message object of type '<MobileyeInfo_seeq>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'seeq) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_seeq>)))
  "Returns string type for a message object of type '<MobileyeInfo_seeq>"
  "mobileye_msgs/MobileyeInfo_seeq")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_seeq)))
  "Returns string type for a message object of type 'MobileyeInfo_seeq"
  "mobileye_msgs/MobileyeInfo_seeq")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_seeq>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_seeq>"
  "44adbcbb0282c17f8d689edcb40bf0ce")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_seeq)))
  "Returns md5sum for a message object of type 'MobileyeInfo_seeq"
  "44adbcbb0282c17f8d689edcb40bf0ce")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_seeq>)))
  "Returns full string definition for message of type '<MobileyeInfo_seeq>"
  (cl:format cl:nil "Header header~%~%SeeQ seeq~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/SeeQ~%uint32 serial_number~%uint64 production_date~%~%uint8 brain_version_major~%uint8 brain_version_minor~%uint8 mest_version_major~%uint8 mest_version_minor~%uint8 mest_version_subminor~%uint8 mest_version_patch_number~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_seeq)))
  "Returns full string definition for message of type 'MobileyeInfo_seeq"
  (cl:format cl:nil "Header header~%~%SeeQ seeq~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/SeeQ~%uint32 serial_number~%uint64 production_date~%~%uint8 brain_version_major~%uint8 brain_version_minor~%uint8 mest_version_major~%uint8 mest_version_minor~%uint8 mest_version_subminor~%uint8 mest_version_patch_number~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_seeq>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'seeq))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_seeq>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_seeq
    (cl:cons ':header (header msg))
    (cl:cons ':seeq (seeq msg))
))
