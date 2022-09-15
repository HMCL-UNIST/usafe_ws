; Auto-generated. Do not edit!


(cl:in-package autorally_msgs-msg)


;//! \htmlinclude imageMask.msg.html

(cl:defclass <imageMask> (roslisp-msg-protocol:ros-message)
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
   (points
    :reader points
    :initarg :points
    :type (cl:vector autorally_msgs-msg:point2D)
   :initform (cl:make-array 0 :element-type 'autorally_msgs-msg:point2D :initial-element (cl:make-instance 'autorally_msgs-msg:point2D)))
   (lines
    :reader lines
    :initarg :lines
    :type (cl:vector autorally_msgs-msg:line2D)
   :initform (cl:make-array 0 :element-type 'autorally_msgs-msg:line2D :initial-element (cl:make-instance 'autorally_msgs-msg:line2D)))
   (rois
    :reader rois
    :initarg :rois
    :type (cl:vector sensor_msgs-msg:RegionOfInterest)
   :initform (cl:make-array 0 :element-type 'sensor_msgs-msg:RegionOfInterest :initial-element (cl:make-instance 'sensor_msgs-msg:RegionOfInterest))))
)

(cl:defclass imageMask (<imageMask>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <imageMask>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'imageMask)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autorally_msgs-msg:<imageMask> is deprecated: use autorally_msgs-msg:imageMask instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <imageMask>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:header-val is deprecated.  Use autorally_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'sender-val :lambda-list '(m))
(cl:defmethod sender-val ((m <imageMask>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:sender-val is deprecated.  Use autorally_msgs-msg:sender instead.")
  (sender m))

(cl:ensure-generic-function 'points-val :lambda-list '(m))
(cl:defmethod points-val ((m <imageMask>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:points-val is deprecated.  Use autorally_msgs-msg:points instead.")
  (points m))

(cl:ensure-generic-function 'lines-val :lambda-list '(m))
(cl:defmethod lines-val ((m <imageMask>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:lines-val is deprecated.  Use autorally_msgs-msg:lines instead.")
  (lines m))

(cl:ensure-generic-function 'rois-val :lambda-list '(m))
(cl:defmethod rois-val ((m <imageMask>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autorally_msgs-msg:rois-val is deprecated.  Use autorally_msgs-msg:rois instead.")
  (rois m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <imageMask>) ostream)
  "Serializes a message object of type '<imageMask>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'sender))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'sender))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'points))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'points))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'lines))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'lines))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'rois))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'rois))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <imageMask>) istream)
  "Deserializes a message object of type '<imageMask>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sender) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'sender) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'points) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'points)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'autorally_msgs-msg:point2D))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'lines) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'lines)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'autorally_msgs-msg:line2D))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'rois) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'rois)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'sensor_msgs-msg:RegionOfInterest))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<imageMask>)))
  "Returns string type for a message object of type '<imageMask>"
  "autorally_msgs/imageMask")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'imageMask)))
  "Returns string type for a message object of type 'imageMask"
  "autorally_msgs/imageMask")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<imageMask>)))
  "Returns md5sum for a message object of type '<imageMask>"
  "da71ef8be852ae3b57ef13c4fd86dd46")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'imageMask)))
  "Returns md5sum for a message object of type 'imageMask"
  "da71ef8be852ae3b57ef13c4fd86dd46")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<imageMask>)))
  "Returns full string definition for message of type '<imageMask>"
  (cl:format cl:nil "Header header~%~%string sender~%point2D[] points~%line2D[] lines~%sensor_msgs/RegionOfInterest[] rois~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: autorally_msgs/point2D~%uint16 x~%uint16 y~%~%================================================================================~%MSG: autorally_msgs/line2D~%point2D start~%point2D end~%~%================================================================================~%MSG: sensor_msgs/RegionOfInterest~%# This message is used to specify a region of interest within an image.~%#~%# When used to specify the ROI setting of the camera when the image was~%# taken, the height and width fields should either match the height and~%# width fields for the associated image; or height = width = 0~%# indicates that the full resolution image was captured.~%~%uint32 x_offset  # Leftmost pixel of the ROI~%                 # (0 if the ROI includes the left edge of the image)~%uint32 y_offset  # Topmost pixel of the ROI~%                 # (0 if the ROI includes the top edge of the image)~%uint32 height    # Height of ROI~%uint32 width     # Width of ROI~%~%# True if a distinct rectified ROI should be calculated from the \"raw\"~%# ROI in this message. Typically this should be False if the full image~%# is captured (ROI not used), and True if a subwindow is captured (ROI~%# used).~%bool do_rectify~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'imageMask)))
  "Returns full string definition for message of type 'imageMask"
  (cl:format cl:nil "Header header~%~%string sender~%point2D[] points~%line2D[] lines~%sensor_msgs/RegionOfInterest[] rois~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: autorally_msgs/point2D~%uint16 x~%uint16 y~%~%================================================================================~%MSG: autorally_msgs/line2D~%point2D start~%point2D end~%~%================================================================================~%MSG: sensor_msgs/RegionOfInterest~%# This message is used to specify a region of interest within an image.~%#~%# When used to specify the ROI setting of the camera when the image was~%# taken, the height and width fields should either match the height and~%# width fields for the associated image; or height = width = 0~%# indicates that the full resolution image was captured.~%~%uint32 x_offset  # Leftmost pixel of the ROI~%                 # (0 if the ROI includes the left edge of the image)~%uint32 y_offset  # Topmost pixel of the ROI~%                 # (0 if the ROI includes the top edge of the image)~%uint32 height    # Height of ROI~%uint32 width     # Width of ROI~%~%# True if a distinct rectified ROI should be calculated from the \"raw\"~%# ROI in this message. Typically this should be False if the full image~%# is captured (ROI not used), and True if a subwindow is captured (ROI~%# used).~%bool do_rectify~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <imageMask>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:length (cl:slot-value msg 'sender))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'points) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'lines) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'rois) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <imageMask>))
  "Converts a ROS message object to a list"
  (cl:list 'imageMask
    (cl:cons ':header (header msg))
    (cl:cons ':sender (sender msg))
    (cl:cons ':points (points msg))
    (cl:cons ':lines (lines msg))
    (cl:cons ':rois (rois msg))
))
