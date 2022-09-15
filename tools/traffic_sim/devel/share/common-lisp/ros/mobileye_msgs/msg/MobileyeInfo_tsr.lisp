; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_tsr.msg.html

(cl:defclass <MobileyeInfo_tsr> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (tsr
    :reader tsr
    :initarg :tsr
    :type (cl:vector mobileye_msgs-msg:TSR)
   :initform (cl:make-array 0 :element-type 'mobileye_msgs-msg:TSR :initial-element (cl:make-instance 'mobileye_msgs-msg:TSR)))
   (tsr_vision_only
    :reader tsr_vision_only
    :initarg :tsr_vision_only
    :type mobileye_msgs-msg:TSRVisionOnlySign
    :initform (cl:make-instance 'mobileye_msgs-msg:TSRVisionOnlySign)))
)

(cl:defclass MobileyeInfo_tsr (<MobileyeInfo_tsr>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_tsr>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_tsr)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_tsr> is deprecated: use mobileye_msgs-msg:MobileyeInfo_tsr instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_tsr>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'tsr-val :lambda-list '(m))
(cl:defmethod tsr-val ((m <MobileyeInfo_tsr>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tsr-val is deprecated.  Use mobileye_msgs-msg:tsr instead.")
  (tsr m))

(cl:ensure-generic-function 'tsr_vision_only-val :lambda-list '(m))
(cl:defmethod tsr_vision_only-val ((m <MobileyeInfo_tsr>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tsr_vision_only-val is deprecated.  Use mobileye_msgs-msg:tsr_vision_only instead.")
  (tsr_vision_only m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_tsr>) ostream)
  "Serializes a message object of type '<MobileyeInfo_tsr>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'tsr))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'tsr))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'tsr_vision_only) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_tsr>) istream)
  "Deserializes a message object of type '<MobileyeInfo_tsr>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'tsr) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'tsr)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'mobileye_msgs-msg:TSR))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'tsr_vision_only) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_tsr>)))
  "Returns string type for a message object of type '<MobileyeInfo_tsr>"
  "mobileye_msgs/MobileyeInfo_tsr")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_tsr)))
  "Returns string type for a message object of type 'MobileyeInfo_tsr"
  "mobileye_msgs/MobileyeInfo_tsr")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_tsr>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_tsr>"
  "12ef6ff06090fe03856140fe8fe950f9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_tsr)))
  "Returns md5sum for a message object of type 'MobileyeInfo_tsr"
  "12ef6ff06090fe03856140fe8fe950f9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_tsr>)))
  "Returns full string definition for message of type '<MobileyeInfo_tsr>"
  (cl:format cl:nil "Header header~%~%TSR[] tsr~%TSRVisionOnlySign tsr_vision_only~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/TSR~%uint8 vision_only_sign_type~%uint8 supplementary_sign_type~%float32 sign_position_x~%float32 sign_position_y~%float32 sign_position_z~%uint8 filter_type~%================================================================================~%MSG: mobileye_msgs/TSRVisionOnlySign~%uint8 vision_only_sign_type_display_1~%uint8 vision_only_sign_type_display_2~%uint8 vision_only_sign_type_display_3~%uint8 vision_only_sign_type_display_4~%~%uint8 supplementary_sign_type_display_1~%uint8 supplementary_sign_type_display_2~%uint8 supplementary_sign_type_display_3~%uint8 supplementary_sign_type_display_4~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_tsr)))
  "Returns full string definition for message of type 'MobileyeInfo_tsr"
  (cl:format cl:nil "Header header~%~%TSR[] tsr~%TSRVisionOnlySign tsr_vision_only~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/TSR~%uint8 vision_only_sign_type~%uint8 supplementary_sign_type~%float32 sign_position_x~%float32 sign_position_y~%float32 sign_position_z~%uint8 filter_type~%================================================================================~%MSG: mobileye_msgs/TSRVisionOnlySign~%uint8 vision_only_sign_type_display_1~%uint8 vision_only_sign_type_display_2~%uint8 vision_only_sign_type_display_3~%uint8 vision_only_sign_type_display_4~%~%uint8 supplementary_sign_type_display_1~%uint8 supplementary_sign_type_display_2~%uint8 supplementary_sign_type_display_3~%uint8 supplementary_sign_type_display_4~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_tsr>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'tsr) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'tsr_vision_only))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_tsr>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_tsr
    (cl:cons ':header (header msg))
    (cl:cons ':tsr (tsr msg))
    (cl:cons ':tsr_vision_only (tsr_vision_only msg))
))
