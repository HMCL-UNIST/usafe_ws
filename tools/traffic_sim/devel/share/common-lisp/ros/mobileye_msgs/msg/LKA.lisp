; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude LKA.msg.html

(cl:defclass <LKA> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (left_lane
    :reader left_lane
    :initarg :left_lane
    :type mobileye_msgs-msg:LKAlane
    :initform (cl:make-instance 'mobileye_msgs-msg:LKAlane))
   (right_lane
    :reader right_lane
    :initarg :right_lane
    :type mobileye_msgs-msg:LKAlane
    :initform (cl:make-instance 'mobileye_msgs-msg:LKAlane))
   (reference_points
    :reader reference_points
    :initarg :reference_points
    :type mobileye_msgs-msg:ReferencePoints
    :initform (cl:make-instance 'mobileye_msgs-msg:ReferencePoints))
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

(cl:defclass LKA (<LKA>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LKA>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LKA)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<LKA> is deprecated: use mobileye_msgs-msg:LKA instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <LKA>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'left_lane-val :lambda-list '(m))
(cl:defmethod left_lane-val ((m <LKA>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:left_lane-val is deprecated.  Use mobileye_msgs-msg:left_lane instead.")
  (left_lane m))

(cl:ensure-generic-function 'right_lane-val :lambda-list '(m))
(cl:defmethod right_lane-val ((m <LKA>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:right_lane-val is deprecated.  Use mobileye_msgs-msg:right_lane instead.")
  (right_lane m))

(cl:ensure-generic-function 'reference_points-val :lambda-list '(m))
(cl:defmethod reference_points-val ((m <LKA>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:reference_points-val is deprecated.  Use mobileye_msgs-msg:reference_points instead.")
  (reference_points m))

(cl:ensure-generic-function 'number_of_next_lane_markers-val :lambda-list '(m))
(cl:defmethod number_of_next_lane_markers-val ((m <LKA>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:number_of_next_lane_markers-val is deprecated.  Use mobileye_msgs-msg:number_of_next_lane_markers instead.")
  (number_of_next_lane_markers m))

(cl:ensure-generic-function 'next_lane-val :lambda-list '(m))
(cl:defmethod next_lane-val ((m <LKA>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:next_lane-val is deprecated.  Use mobileye_msgs-msg:next_lane instead.")
  (next_lane m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LKA>) ostream)
  "Serializes a message object of type '<LKA>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'left_lane) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'right_lane) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'reference_points) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'number_of_next_lane_markers)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'next_lane))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'next_lane))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LKA>) istream)
  "Deserializes a message object of type '<LKA>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'left_lane) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'right_lane) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'reference_points) istream)
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LKA>)))
  "Returns string type for a message object of type '<LKA>"
  "mobileye_msgs/LKA")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LKA)))
  "Returns string type for a message object of type 'LKA"
  "mobileye_msgs/LKA")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LKA>)))
  "Returns md5sum for a message object of type '<LKA>"
  "b5e3ba1f4afa652894372b06e4e02639")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LKA)))
  "Returns md5sum for a message object of type 'LKA"
  "b5e3ba1f4afa652894372b06e4e02639")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LKA>)))
  "Returns full string definition for message of type '<LKA>"
  (cl:format cl:nil "Header header~%~%LKAlane left_lane~%LKAlane right_lane~%~%ReferencePoints reference_points~%~%uint8 number_of_next_lane_markers~%~%LKAlane[] next_lane~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%================================================================================~%MSG: mobileye_msgs/ReferencePoints~%float32 ref_point1_position~%float32 ref_point1_distance~%bool ref_point1_validity~%float32 ref_point2_position~%float32 ref_point2_distance~%bool ref_point2_validity~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LKA)))
  "Returns full string definition for message of type 'LKA"
  (cl:format cl:nil "Header header~%~%LKAlane left_lane~%LKAlane right_lane~%~%ReferencePoints reference_points~%~%uint8 number_of_next_lane_markers~%~%LKAlane[] next_lane~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%================================================================================~%MSG: mobileye_msgs/ReferencePoints~%float32 ref_point1_position~%float32 ref_point1_distance~%bool ref_point1_validity~%float32 ref_point2_position~%float32 ref_point2_distance~%bool ref_point2_validity~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LKA>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'left_lane))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'right_lane))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'reference_points))
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'next_lane) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LKA>))
  "Converts a ROS message object to a list"
  (cl:list 'LKA
    (cl:cons ':header (header msg))
    (cl:cons ':left_lane (left_lane msg))
    (cl:cons ':right_lane (right_lane msg))
    (cl:cons ':reference_points (reference_points msg))
    (cl:cons ':number_of_next_lane_markers (number_of_next_lane_markers msg))
    (cl:cons ':next_lane (next_lane msg))
))
