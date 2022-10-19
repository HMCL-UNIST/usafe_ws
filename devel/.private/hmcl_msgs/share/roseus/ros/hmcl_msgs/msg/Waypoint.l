;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::Waypoint)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'Waypoint (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::WAYPOINT")
  (make-package "HMCL_MSGS::WAYPOINT"))

(in-package "ROS")
;;//! \htmlinclude Waypoint.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass hmcl_msgs::Waypoint
  :super ros::object
  :slots (_gid _lid _pose _twist _lane_id _Junction _Crosswalk _Stop_line ))

(defmethod hmcl_msgs::Waypoint
  (:init
   (&key
    ((:gid __gid) 0)
    ((:lid __lid) 0)
    ((:pose __pose) (instance geometry_msgs::PoseStamped :init))
    ((:twist __twist) (instance geometry_msgs::TwistStamped :init))
    ((:lane_id __lane_id) 0)
    ((:Junction __Junction) nil)
    ((:Crosswalk __Crosswalk) nil)
    ((:Stop_line __Stop_line) nil)
    )
   (send-super :init)
   (setq _gid (round __gid))
   (setq _lid (round __lid))
   (setq _pose __pose)
   (setq _twist __twist)
   (setq _lane_id (round __lane_id))
   (setq _Junction __Junction)
   (setq _Crosswalk __Crosswalk)
   (setq _Stop_line __Stop_line)
   self)
  (:gid
   (&optional __gid)
   (if __gid (setq _gid __gid)) _gid)
  (:lid
   (&optional __lid)
   (if __lid (setq _lid __lid)) _lid)
  (:pose
   (&rest __pose)
   (if (keywordp (car __pose))
       (send* _pose __pose)
     (progn
       (if __pose (setq _pose (car __pose)))
       _pose)))
  (:twist
   (&rest __twist)
   (if (keywordp (car __twist))
       (send* _twist __twist)
     (progn
       (if __twist (setq _twist (car __twist)))
       _twist)))
  (:lane_id
   (&optional __lane_id)
   (if __lane_id (setq _lane_id __lane_id)) _lane_id)
  (:Junction
   (&optional __Junction)
   (if __Junction (setq _Junction __Junction)) _Junction)
  (:Crosswalk
   (&optional __Crosswalk)
   (if __Crosswalk (setq _Crosswalk __Crosswalk)) _Crosswalk)
  (:Stop_line
   (&optional __Stop_line)
   (if __Stop_line (setq _Stop_line __Stop_line)) _Stop_line)
  (:serialization-length
   ()
   (+
    ;; int32 _gid
    4
    ;; int32 _lid
    4
    ;; geometry_msgs/PoseStamped _pose
    (send _pose :serialization-length)
    ;; geometry_msgs/TwistStamped _twist
    (send _twist :serialization-length)
    ;; uint32 _lane_id
    4
    ;; bool _Junction
    1
    ;; bool _Crosswalk
    1
    ;; bool _Stop_line
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _gid
       (write-long _gid s)
     ;; int32 _lid
       (write-long _lid s)
     ;; geometry_msgs/PoseStamped _pose
       (send _pose :serialize s)
     ;; geometry_msgs/TwistStamped _twist
       (send _twist :serialize s)
     ;; uint32 _lane_id
       (write-long _lane_id s)
     ;; bool _Junction
       (if _Junction (write-byte -1 s) (write-byte 0 s))
     ;; bool _Crosswalk
       (if _Crosswalk (write-byte -1 s) (write-byte 0 s))
     ;; bool _Stop_line
       (if _Stop_line (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _gid
     (setq _gid (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _lid
     (setq _lid (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/PoseStamped _pose
     (send _pose :deserialize buf ptr-) (incf ptr- (send _pose :serialization-length))
   ;; geometry_msgs/TwistStamped _twist
     (send _twist :deserialize buf ptr-) (incf ptr- (send _twist :serialization-length))
   ;; uint32 _lane_id
     (setq _lane_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _Junction
     (setq _Junction (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _Crosswalk
     (setq _Crosswalk (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _Stop_line
     (setq _Stop_line (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get hmcl_msgs::Waypoint :md5sum-) "29822e649d55c164f971af3df4646407")
(setf (get hmcl_msgs::Waypoint :datatype-) "hmcl_msgs/Waypoint")
(setf (get hmcl_msgs::Waypoint :definition-)
      "# global id
int32 gid 
# local id
int32 lid
geometry_msgs/PoseStamped pose
geometry_msgs/TwistStamped twist
uint32 lane_id
bool Junction
bool Crosswalk
bool Stop_line
================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

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
")



(provide :hmcl_msgs/Waypoint "29822e649d55c164f971af3df4646407")


