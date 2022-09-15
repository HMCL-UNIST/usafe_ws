; Auto-generated. Do not edit!


(cl:in-package nmea_msgs-msg)


;//! \htmlinclude Gpgst.msg.html

(cl:defclass <Gpgst> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (message_id
    :reader message_id
    :initarg :message_id
    :type cl:string
    :initform "")
   (utc_seconds
    :reader utc_seconds
    :initarg :utc_seconds
    :type cl:float
    :initform 0.0)
   (rms
    :reader rms
    :initarg :rms
    :type cl:float
    :initform 0.0)
   (semi_major_dev
    :reader semi_major_dev
    :initarg :semi_major_dev
    :type cl:float
    :initform 0.0)
   (semi_minor_dev
    :reader semi_minor_dev
    :initarg :semi_minor_dev
    :type cl:float
    :initform 0.0)
   (orientation
    :reader orientation
    :initarg :orientation
    :type cl:float
    :initform 0.0)
   (lat_dev
    :reader lat_dev
    :initarg :lat_dev
    :type cl:float
    :initform 0.0)
   (lon_dev
    :reader lon_dev
    :initarg :lon_dev
    :type cl:float
    :initform 0.0)
   (alt_dev
    :reader alt_dev
    :initarg :alt_dev
    :type cl:float
    :initform 0.0))
)

(cl:defclass Gpgst (<Gpgst>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Gpgst>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Gpgst)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nmea_msgs-msg:<Gpgst> is deprecated: use nmea_msgs-msg:Gpgst instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:header-val is deprecated.  Use nmea_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'message_id-val :lambda-list '(m))
(cl:defmethod message_id-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:message_id-val is deprecated.  Use nmea_msgs-msg:message_id instead.")
  (message_id m))

(cl:ensure-generic-function 'utc_seconds-val :lambda-list '(m))
(cl:defmethod utc_seconds-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:utc_seconds-val is deprecated.  Use nmea_msgs-msg:utc_seconds instead.")
  (utc_seconds m))

(cl:ensure-generic-function 'rms-val :lambda-list '(m))
(cl:defmethod rms-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:rms-val is deprecated.  Use nmea_msgs-msg:rms instead.")
  (rms m))

(cl:ensure-generic-function 'semi_major_dev-val :lambda-list '(m))
(cl:defmethod semi_major_dev-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:semi_major_dev-val is deprecated.  Use nmea_msgs-msg:semi_major_dev instead.")
  (semi_major_dev m))

(cl:ensure-generic-function 'semi_minor_dev-val :lambda-list '(m))
(cl:defmethod semi_minor_dev-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:semi_minor_dev-val is deprecated.  Use nmea_msgs-msg:semi_minor_dev instead.")
  (semi_minor_dev m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:orientation-val is deprecated.  Use nmea_msgs-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'lat_dev-val :lambda-list '(m))
(cl:defmethod lat_dev-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:lat_dev-val is deprecated.  Use nmea_msgs-msg:lat_dev instead.")
  (lat_dev m))

(cl:ensure-generic-function 'lon_dev-val :lambda-list '(m))
(cl:defmethod lon_dev-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:lon_dev-val is deprecated.  Use nmea_msgs-msg:lon_dev instead.")
  (lon_dev m))

(cl:ensure-generic-function 'alt_dev-val :lambda-list '(m))
(cl:defmethod alt_dev-val ((m <Gpgst>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nmea_msgs-msg:alt_dev-val is deprecated.  Use nmea_msgs-msg:alt_dev instead.")
  (alt_dev m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Gpgst>) ostream)
  "Serializes a message object of type '<Gpgst>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message_id))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'utc_seconds))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rms))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'semi_major_dev))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'semi_minor_dev))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'orientation))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'lat_dev))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'lon_dev))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'alt_dev))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Gpgst>) istream)
  "Deserializes a message object of type '<Gpgst>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message_id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message_id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'utc_seconds) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rms) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'semi_major_dev) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'semi_minor_dev) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'orientation) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'lat_dev) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'lon_dev) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'alt_dev) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Gpgst>)))
  "Returns string type for a message object of type '<Gpgst>"
  "nmea_msgs/Gpgst")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Gpgst)))
  "Returns string type for a message object of type 'Gpgst"
  "nmea_msgs/Gpgst")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Gpgst>)))
  "Returns md5sum for a message object of type '<Gpgst>"
  "e4b77f6f4c211629ab0307177f71dcee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Gpgst)))
  "Returns md5sum for a message object of type 'Gpgst"
  "e4b77f6f4c211629ab0307177f71dcee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Gpgst>)))
  "Returns full string definition for message of type '<Gpgst>"
  (cl:format cl:nil "# Message from GPGST NMEA String~%Header header~%~%string message_id~%~%# UTC seconds from midnight~%float64 utc_seconds~%~%# Root-Mean-Squared value of standard deviation of range inputs~%float32 rms~%~%# Standard Deviations of semi-major and minor axes of error ellipse~%float32 semi_major_dev~%float32 semi_minor_dev~%~%# Orientation of the semi-major axis of error ellipse with respect to true north~%float32 orientation~%~%# Standard Deviations of latitude, longitude, and altitude measurements~%float32 lat_dev~%float32 lon_dev~%float32 alt_dev~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Gpgst)))
  "Returns full string definition for message of type 'Gpgst"
  (cl:format cl:nil "# Message from GPGST NMEA String~%Header header~%~%string message_id~%~%# UTC seconds from midnight~%float64 utc_seconds~%~%# Root-Mean-Squared value of standard deviation of range inputs~%float32 rms~%~%# Standard Deviations of semi-major and minor axes of error ellipse~%float32 semi_major_dev~%float32 semi_minor_dev~%~%# Orientation of the semi-major axis of error ellipse with respect to true north~%float32 orientation~%~%# Standard Deviations of latitude, longitude, and altitude measurements~%float32 lat_dev~%float32 lon_dev~%float32 alt_dev~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Gpgst>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:length (cl:slot-value msg 'message_id))
     8
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Gpgst>))
  "Converts a ROS message object to a list"
  (cl:list 'Gpgst
    (cl:cons ':header (header msg))
    (cl:cons ':message_id (message_id msg))
    (cl:cons ':utc_seconds (utc_seconds msg))
    (cl:cons ':rms (rms msg))
    (cl:cons ':semi_major_dev (semi_major_dev msg))
    (cl:cons ':semi_minor_dev (semi_minor_dev msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':lat_dev (lat_dev msg))
    (cl:cons ':lon_dev (lon_dev msg))
    (cl:cons ':alt_dev (alt_dev msg))
))
