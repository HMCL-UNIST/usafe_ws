;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::Lane)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'Lane (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::LANE")
  (make-package "HMCL_MSGS::LANE"))

(in-package "ROS")
;;//! \htmlinclude Lane.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::Lane
  :super ros::object
  :slots (_header _lane_id _lane_change_flag _speed_limit _waypoints _trafficlights _speedbumps ))

(defmethod hmcl_msgs::Lane
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:lane_id __lane_id) 0)
    ((:lane_change_flag __lane_change_flag) nil)
    ((:speed_limit __speed_limit) 0.0)
    ((:waypoints __waypoints) (let (r) (dotimes (i 0) (push (instance hmcl_msgs::Waypoint :init) r)) r))
    ((:trafficlights __trafficlights) (let (r) (dotimes (i 0) (push (instance hmcl_msgs::Trafficlight :init) r)) r))
    ((:speedbumps __speedbumps) (let (r) (dotimes (i 0) (push (instance hmcl_msgs::Waypoint :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _lane_id (round __lane_id))
   (setq _lane_change_flag __lane_change_flag)
   (setq _speed_limit (float __speed_limit))
   (setq _waypoints __waypoints)
   (setq _trafficlights __trafficlights)
   (setq _speedbumps __speedbumps)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:lane_id
   (&optional __lane_id)
   (if __lane_id (setq _lane_id __lane_id)) _lane_id)
  (:lane_change_flag
   (&optional __lane_change_flag)
   (if __lane_change_flag (setq _lane_change_flag __lane_change_flag)) _lane_change_flag)
  (:speed_limit
   (&optional __speed_limit)
   (if __speed_limit (setq _speed_limit __speed_limit)) _speed_limit)
  (:waypoints
   (&rest __waypoints)
   (if (keywordp (car __waypoints))
       (send* _waypoints __waypoints)
     (progn
       (if __waypoints (setq _waypoints (car __waypoints)))
       _waypoints)))
  (:trafficlights
   (&rest __trafficlights)
   (if (keywordp (car __trafficlights))
       (send* _trafficlights __trafficlights)
     (progn
       (if __trafficlights (setq _trafficlights (car __trafficlights)))
       _trafficlights)))
  (:speedbumps
   (&rest __speedbumps)
   (if (keywordp (car __speedbumps))
       (send* _speedbumps __speedbumps)
     (progn
       (if __speedbumps (setq _speedbumps (car __speedbumps)))
       _speedbumps)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _lane_id
    4
    ;; bool _lane_change_flag
    1
    ;; float32 _speed_limit
    4
    ;; hmcl_msgs/Waypoint[] _waypoints
    (apply #'+ (send-all _waypoints :serialization-length)) 4
    ;; hmcl_msgs/Trafficlight[] _trafficlights
    (apply #'+ (send-all _trafficlights :serialization-length)) 4
    ;; hmcl_msgs/Waypoint[] _speedbumps
    (apply #'+ (send-all _speedbumps :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _lane_id
       (write-long _lane_id s)
     ;; bool _lane_change_flag
       (if _lane_change_flag (write-byte -1 s) (write-byte 0 s))
     ;; float32 _speed_limit
       (sys::poke _speed_limit (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; hmcl_msgs/Waypoint[] _waypoints
     (write-long (length _waypoints) s)
     (dolist (elem _waypoints)
       (send elem :serialize s)
       )
     ;; hmcl_msgs/Trafficlight[] _trafficlights
     (write-long (length _trafficlights) s)
     (dolist (elem _trafficlights)
       (send elem :serialize s)
       )
     ;; hmcl_msgs/Waypoint[] _speedbumps
     (write-long (length _speedbumps) s)
     (dolist (elem _speedbumps)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _lane_id
     (setq _lane_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _lane_change_flag
     (setq _lane_change_flag (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _speed_limit
     (setq _speed_limit (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; hmcl_msgs/Waypoint[] _waypoints
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _waypoints (let (r) (dotimes (i n) (push (instance hmcl_msgs::Waypoint :init) r)) r))
     (dolist (elem- _waypoints)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; hmcl_msgs/Trafficlight[] _trafficlights
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _trafficlights (let (r) (dotimes (i n) (push (instance hmcl_msgs::Trafficlight :init) r)) r))
     (dolist (elem- _trafficlights)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; hmcl_msgs/Waypoint[] _speedbumps
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _speedbumps (let (r) (dotimes (i n) (push (instance hmcl_msgs::Waypoint :init) r)) r))
     (dolist (elem- _speedbumps)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get hmcl_msgs::Lane :md5sum-) "923d2c4fa02093b723f235ff09a4673f")
(setf (get hmcl_msgs::Lane :datatype-) "hmcl_msgs/Lane")
(setf (get hmcl_msgs::Lane :definition-)
      "Header header
int32 lane_id
bool lane_change_flag
float32 speed_limit 
Waypoint[] waypoints
Trafficlight[] trafficlights
Waypoint[] speedbumps
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
MSG: hmcl_msgs/Waypoint
# global id
int32 gid 
# local id
int32 lid
geometry_msgs/PoseStamped pose
geometry_msgs/TwistStamped twist
uint32 lane_id
================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

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
MSG: geometry_msgs/TwistStamped
# A twist with reference coordinate frame and timestamp
Header header
Twist twist

================================================================================
MSG: geometry_msgs/Twist
# This expresses velocity in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
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
MSG: hmcl_msgs/TrafficlightBulb
int32 id
int32 light_status # 0 red, 1 green, 2 yellow 
")



(provide :hmcl_msgs/Lane "923d2c4fa02093b723f235ff09a4673f")


