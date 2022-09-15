; Auto-generated. Do not edit!


(cl:in-package autorally_msgs-msg)


;//! \htmlinclude neuralNetModel.msg.html

(cl:defclass <neuralNetModel> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (network
    :reader network
    :initarg :network
    :type (cl:vector autorally_msgs-msg:neuralNetLayer)
   :initform (cl:make-array 0 :element-type 'autorally_msgs-msg:neuralNetLayer :initial-element (cl:make-instance 'autorally_msgs-msg:neuralNetLayer)))
   (numLayers
    :reader numLayers
    :initarg :numLayers
    :type cl:integer
    :initform 0)
   (structure
    :reader structure
    :initarg :structure
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass neuralNetModel (<neuralNetModel>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <neuralNetModel>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'neuralNetModel)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autorally_msgs-msg:<neuralNetModel> is deprecated: use autorally_msgs-msg:neuralNetModel instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <neuralNetModel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:header-val is deprecated.  Use autorally_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'network-val :lambda-list '(m))
(cl:defmethod network-val ((m <neuralNetModel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:network-val is deprecated.  Use autorally_msgs-msg:network instead.")
  (network m))

(cl:ensure-generic-function 'numLayers-val :lambda-list '(m))
(cl:defmethod numLayers-val ((m <neuralNetModel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:numLayers-val is deprecated.  Use autorally_msgs-msg:numLayers instead.")
  (numLayers m))

(cl:ensure-generic-function 'structure-val :lambda-list '(m))
(cl:defmethod structure-val ((m <neuralNetModel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:structure-val is deprecated.  Use autorally_msgs-msg:structure instead.")
  (structure m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <neuralNetModel>) ostream)
  "Serializes a message object of type '<neuralNetModel>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'network))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'network))
  (cl:let* ((signed (cl:slot-value msg 'numLayers)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'structure))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'structure))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <neuralNetModel>) istream)
  "Deserializes a message object of type '<neuralNetModel>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'network) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'network)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'autorally_msgs-msg:neuralNetLayer))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'numLayers) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'structure) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'structure)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<neuralNetModel>)))
  "Returns string type for a message object of type '<neuralNetModel>"
  "autorally_msgs/neuralNetModel")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'neuralNetModel)))
  "Returns string type for a message object of type 'neuralNetModel"
  "autorally_msgs/neuralNetModel")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<neuralNetModel>)))
  "Returns md5sum for a message object of type '<neuralNetModel>"
  "3c8c8380b1c9bb122f00005291fff0d0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'neuralNetModel)))
  "Returns md5sum for a message object of type 'neuralNetModel"
  "3c8c8380b1c9bb122f00005291fff0d0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<neuralNetModel>)))
  "Returns full string definition for message of type '<neuralNetModel>"
  (cl:format cl:nil "Header header~%~%neuralNetLayer[] network~%int32 numLayers~%int32[] structure~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: autorally_msgs/neuralNetLayer~%string name~%float32[] weight~%float32[] bias~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'neuralNetModel)))
  "Returns full string definition for message of type 'neuralNetModel"
  (cl:format cl:nil "Header header~%~%neuralNetLayer[] network~%int32 numLayers~%int32[] structure~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: autorally_msgs/neuralNetLayer~%string name~%float32[] weight~%float32[] bias~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <neuralNetModel>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'network) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'structure) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <neuralNetModel>))
  "Converts a ROS message object to a list"
  (cl:list 'neuralNetModel
    (cl:cons ':header (header msg))
    (cl:cons ':network (network msg))
    (cl:cons ':numLayers (numLayers msg))
    (cl:cons ':structure (structure msg))
))
