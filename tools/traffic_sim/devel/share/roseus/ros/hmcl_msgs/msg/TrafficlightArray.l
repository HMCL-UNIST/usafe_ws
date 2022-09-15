;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::TrafficlightArray)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'TrafficlightArray (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::TRAFFICLIGHTARRAY")
  (make-package "HMCL_MSGS::TRAFFICLIGHTARRAY"))

(in-package "ROS")
;;//! \htmlinclude TrafficlightArray.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::TrafficlightArray
  :super ros::object
  :slots (_header _trafficlights ))

(defmethod hmcl_msgs::TrafficlightArray
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:trafficlights __trafficlights) (let (r) (dotimes (i 0) (push (instance hmcl_msgs::Trafficlight :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _trafficlights __trafficlights)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:trafficlights
   (&rest __trafficlights)
   (if (keywordp (car __trafficlights))
       (send* _trafficlights __trafficlights)
     (progn
       (if __trafficlights (setq _trafficlights (car __trafficlights)))
       _trafficlights)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; hmcl_msgs/Trafficlight[] _trafficlights
    (apply #'+ (send-all _trafficlights :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; hmcl_msgs/Trafficlight[] _trafficlights
     (write-long (length _trafficlights) s)
     (dolist (elem _trafficlights)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; hmcl_msgs/Trafficlight[] _trafficlights
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _trafficlights (let (r) (dotimes (i n) (push (instance hmcl_msgs::Trafficlight :init) r)) r))
     (dolist (elem- _trafficlights)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get hmcl_msgs::TrafficlightArray :md5sum-) "06a8e2673b5b387a7023181a4c767949")
(setf (get hmcl_msgs::TrafficlightArray :datatype-) "hmcl_msgs/TrafficlightArray")
(setf (get hmcl_msgs::TrafficlightArray :definition-)
      "Header header
Trafficlight[] trafficlights
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: hmcl_msgs/Trafficlight
Header header
int32 id
int32 lanelet_id
geometry_msgs/Pose pose
TrafficlightBulb left_light
TrafficlightBulb straight_light
TrafficlightBulb right_light
bool valid_stop_line
geometry_msgs/Pose stop_line
================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: hmcl_msgs/TrafficlightBulb
int32 id
int32 light_status # 0 red, 1 green, 2 yellow 
")



(provide :hmcl_msgs/TrafficlightArray "06a8e2673b5b387a7023181a4c767949")


