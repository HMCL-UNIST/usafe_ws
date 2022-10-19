; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude BehaviorFactor.msg.html

(cl:defclass <BehaviorFactor> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (transition_condition
    :reader transition_condition
    :initarg :transition_condition
    :type hmcl_msgs-msg:TransitionCondition
    :initform (cl:make-instance 'hmcl_msgs-msg:TransitionCondition))
   (front_id
    :reader front_id
    :initarg :front_id
    :type cl:fixnum
    :initform 0)
   (stop_line_stop
    :reader stop_line_stop
    :initarg :stop_line_stop
    :type cl:boolean
    :initform cl:nil)
   (front_dist
    :reader front_dist
    :initarg :front_dist
    :type cl:float
    :initform 0.0))
)

(cl:defclass BehaviorFactor (<BehaviorFactor>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BehaviorFactor>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BehaviorFactor)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<BehaviorFactor> is deprecated: use hmcl_msgs-msg:BehaviorFactor instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <BehaviorFactor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:header-val is deprecated.  Use hmcl_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'transition_condition-val :lambda-list '(m))
(cl:defmethod transition_condition-val ((m <BehaviorFactor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:transition_condition-val is deprecated.  Use hmcl_msgs-msg:transition_condition instead.")
  (transition_condition m))

(cl:ensure-generic-function 'front_id-val :lambda-list '(m))
(cl:defmethod front_id-val ((m <BehaviorFactor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:front_id-val is deprecated.  Use hmcl_msgs-msg:front_id instead.")
  (front_id m))

(cl:ensure-generic-function 'stop_line_stop-val :lambda-list '(m))
(cl:defmethod stop_line_stop-val ((m <BehaviorFactor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:stop_line_stop-val is deprecated.  Use hmcl_msgs-msg:stop_line_stop instead.")
  (stop_line_stop m))

(cl:ensure-generic-function 'front_dist-val :lambda-list '(m))
(cl:defmethod front_dist-val ((m <BehaviorFactor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:front_dist-val is deprecated.  Use hmcl_msgs-msg:front_dist instead.")
  (front_dist m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BehaviorFactor>) ostream)
  "Serializes a message object of type '<BehaviorFactor>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'transition_condition) ostream)
  (cl:let* ((signed (cl:slot-value msg 'front_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stop_line_stop) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_dist))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BehaviorFactor>) istream)
  "Deserializes a message object of type '<BehaviorFactor>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'transition_condition) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'front_id) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:slot-value msg 'stop_line_stop) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_dist) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BehaviorFactor>)))
  "Returns string type for a message object of type '<BehaviorFactor>"
  "hmcl_msgs/BehaviorFactor")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BehaviorFactor)))
  "Returns string type for a message object of type 'BehaviorFactor"
  "hmcl_msgs/BehaviorFactor")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BehaviorFactor>)))
  "Returns md5sum for a message object of type '<BehaviorFactor>"
  "007955b848a31590079e09deb110b6e6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BehaviorFactor)))
  "Returns md5sum for a message object of type 'BehaviorFactor"
  "007955b848a31590079e09deb110b6e6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BehaviorFactor>)))
  "Returns full string definition for message of type '<BehaviorFactor>"
  (cl:format cl:nil "Header header~%hmcl_msgs/TransitionCondition transition_condition~%int16 front_id~%bool stop_line_stop~%float32 front_dist~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hmcl_msgs/TransitionCondition~%bool missionStart~%bool approachToStartPos~%bool startArrivalCheck~%bool startArrivalSuccess~%bool frontCar~%bool stationaryFrontCar~%bool approachToCrosswalk~%bool crosswalkPass~%bool pedestrianOnCrosswalk~%bool leftTurn~%bool rightTurn~%bool turn~%bool trafficLightStop~%bool stopCheck~%bool luggageDrop~%bool brokenFrontCar~%bool laneChangeDone~%bool essentialLaneChange~%bool speedBumpSign~%bool speedBumpPass~%bool approachToGoalPos~%bool goalArrivalCheck~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BehaviorFactor)))
  "Returns full string definition for message of type 'BehaviorFactor"
  (cl:format cl:nil "Header header~%hmcl_msgs/TransitionCondition transition_condition~%int16 front_id~%bool stop_line_stop~%float32 front_dist~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: hmcl_msgs/TransitionCondition~%bool missionStart~%bool approachToStartPos~%bool startArrivalCheck~%bool startArrivalSuccess~%bool frontCar~%bool stationaryFrontCar~%bool approachToCrosswalk~%bool crosswalkPass~%bool pedestrianOnCrosswalk~%bool leftTurn~%bool rightTurn~%bool turn~%bool trafficLightStop~%bool stopCheck~%bool luggageDrop~%bool brokenFrontCar~%bool laneChangeDone~%bool essentialLaneChange~%bool speedBumpSign~%bool speedBumpPass~%bool approachToGoalPos~%bool goalArrivalCheck~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BehaviorFactor>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'transition_condition))
     2
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BehaviorFactor>))
  "Converts a ROS message object to a list"
  (cl:list 'BehaviorFactor
    (cl:cons ':header (header msg))
    (cl:cons ':transition_condition (transition_condition msg))
    (cl:cons ':front_id (front_id msg))
    (cl:cons ':stop_line_stop (stop_line_stop msg))
    (cl:cons ':front_dist (front_dist msg))
))
