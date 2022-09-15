; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_number_of_next_lane_markers.msg.html

(cl:defclass <MobileyeInfo_number_of_next_lane_markers> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (number_of_next_lane_markers
    :reader number_of_next_lane_markers
    :initarg :number_of_next_lane_markers
    :type cl:fixnum
    :initform 0)
   (next_lane
    :reader next_lane
    :initarg :next_lane
    :type (cl:vector mobileye_msgs-msg:LKAlane)
   :initform (cl:make-array 0 :element-type 'mobileye_msgs-msg:LKAlane :initial-element (cl:make-instance 'mobileye_msgs-msg:LKAlane))))
)

(cl:defclass MobileyeInfo_number_of_next_lane_markers (<MobileyeInfo_number_of_next_lane_markers>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_number_of_next_lane_markers>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_number_of_next_lane_markers)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_number_of_next_lane_markers> is deprecated: use mobileye_msgs-msg:MobileyeInfo_number_of_next_lane_markers instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_number_of_next_lane_markers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'number_of_next_lane_markers-val :lambda-list '(m))
(cl:defmethod number_of_next_lane_markers-val ((m <MobileyeInfo_number_of_next_lane_markers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:number_of_next_lane_markers-val is deprecated.  Use mobileye_msgs-msg:number_of_next_lane_markers instead.")
  (number_of_next_lane_markers m))

(cl:ensure-generic-function 'next_lane-val :lambda-list '(m))
(cl:defmethod next_lane-val ((m <MobileyeInfo_number_of_next_lane_markers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:next_lane-val is deprecated.  Use mobileye_msgs-msg:next_lane instead.")
  (next_lane m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_number_of_next_lane_markers>) ostream)
  "Serializes a message object of type '<MobileyeInfo_number_of_next_lane_markers>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'number_of_next_lane_markers)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'next_lane))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'next_lane))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_number_of_next_lane_markers>) istream)
  "Deserializes a message object of type '<MobileyeInfo_number_of_next_lane_markers>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'number_of_next_lane_markers)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'next_lane) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'next_lane)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'mobileye_msgs-msg:LKAlane))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_number_of_next_lane_markers>)))
  "Returns string type for a message object of type '<MobileyeInfo_number_of_next_lane_markers>"
  "mobileye_msgs/MobileyeInfo_number_of_next_lane_markers")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_number_of_next_lane_markers)))
  "Returns string type for a message object of type 'MobileyeInfo_number_of_next_lane_markers"
  "mobileye_msgs/MobileyeInfo_number_of_next_lane_markers")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_number_of_next_lane_markers>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_number_of_next_lane_markers>"
  "d32c337c79d434dc5fdbc8145e767dc2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_number_of_next_lane_markers)))
  "Returns md5sum for a message object of type 'MobileyeInfo_number_of_next_lane_markers"
  "d32c337c79d434dc5fdbc8145e767dc2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_number_of_next_lane_markers>)))
  "Returns full string definition for message of type '<MobileyeInfo_number_of_next_lane_markers>"
  (cl:format cl:nil "Header header~%~%uint8 number_of_next_lane_markers~%~%LKAlane[] next_lane~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_number_of_next_lane_markers)))
  "Returns full string definition for message of type 'MobileyeInfo_number_of_next_lane_markers"
  (cl:format cl:nil "Header header~%~%uint8 number_of_next_lane_markers~%~%LKAlane[] next_lane~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_number_of_next_lane_markers>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'next_lane) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_number_of_next_lane_markers>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_number_of_next_lane_markers
    (cl:cons ':header (header msg))
    (cl:cons ':number_of_next_lane_markers (number_of_next_lane_markers msg))
    (cl:cons ':next_lane (next_lane msg))
))
