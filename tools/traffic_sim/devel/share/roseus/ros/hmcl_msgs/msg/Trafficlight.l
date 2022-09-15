;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::Trafficlight)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'Trafficlight (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::TRAFFICLIGHT")
  (make-package "HMCL_MSGS::TRAFFICLIGHT"))

(in-package "ROS")
;;//! \htmlinclude Trafficlight.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::Trafficlight
  :super ros::object
  :slots (_header _id _lanelet_id _pose _left_light _straight_light _right_light _valid_stop_line _stop_line ))

(defmethod hmcl_msgs::Trafficlight
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:id __id) 0)
    ((:lanelet_id __lanelet_id) 0)
    ((:pose __pose) (instance geometry_msgs::Pose :init))
    ((:left_light __left_light) (instance hmcl_msgs::TrafficlightBulb :init))
    ((:straight_light __straight_light) (instance hmcl_msgs::TrafficlightBulb :init))
    ((:right_light __right_light) (instance hmcl_msgs::TrafficlightBulb :init))
    ((:valid_stop_line __valid_stop_line) nil)
    ((:stop_line __stop_line) (instance geometry_msgs::Pose :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _id (round __id))
   (setq _lanelet_id (round __lanelet_id))
   (setq _pose __pose)
   (setq _left_light __left_light)
   (setq _straight_light __straight_light)
   (setq _right_light __right_light)
   (setq _valid_stop_line __valid_stop_line)
   (setq _stop_line __stop_line)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:lanelet_id
   (&optional __lanelet_id)
   (if __lanelet_id (setq _lanelet_id __lanelet_id)) _lanelet_id)
  (:pose
   (&rest __pose)
   (if (keywordp (car __pose))
       (send* _pose __pose)
     (progn
       (if __pose (setq _pose (car __pose)))
       _pose)))
  (:left_light
   (&rest __left_light)
   (if (keywordp (car __left_light))
       (send* _left_light __left_light)
     (progn
       (if __left_light (setq _left_light (car __left_light)))
       _left_light)))
  (:straight_light
   (&rest __straight_light)
   (if (keywordp (car __straight_light))
       (send* _straight_light __straight_light)
     (progn
       (if __straight_light (setq _straight_light (car __straight_light)))
       _straight_light)))
  (:right_light
   (&rest __right_light)
   (if (keywordp (car __right_light))
       (send* _right_light __right_light)
     (progn
       (if __right_light (setq _right_light (car __right_light)))
       _right_light)))
  (:valid_stop_line
   (&optional __valid_stop_line)
   (if __valid_stop_line (setq _valid_stop_line __valid_stop_line)) _valid_stop_line)
  (:stop_line
   (&rest __stop_line)
   (if (keywordp (car __stop_line))
       (send* _stop_line __stop_line)
     (progn
       (if __stop_line (setq _stop_line (car __stop_line)))
       _stop_line)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _id
    4
    ;; int32 _lanelet_id
    4
    ;; geometry_msgs/Pose _pose
    (send _pose :serialization-length)
    ;; hmcl_msgs/TrafficlightBulb _left_light
    (send _left_light :serialization-length)
    ;; hmcl_msgs/TrafficlightBulb _straight_light
    (send _straight_light :serialization-length)
    ;; hmcl_msgs/TrafficlightBulb _right_light
    (send _right_light :serialization-length)
    ;; bool _valid_stop_line
    1
    ;; geometry_msgs/Pose _stop_line
    (send _stop_line :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _id
       (write-long _id s)
     ;; int32 _lanelet_id
       (write-long _lanelet_id s)
     ;; geometry_msgs/Pose _pose
       (send _pose :serialize s)
     ;; hmcl_msgs/TrafficlightBulb _left_light
       (send _left_light :serialize s)
     ;; hmcl_msgs/TrafficlightBulb _straight_light
       (send _straight_light :serialize s)
     ;; hmcl_msgs/TrafficlightBulb _right_light
       (send _right_light :serialize s)
     ;; bool _valid_stop_line
       (if _valid_stop_line (write-byte -1 s) (write-byte 0 s))
     ;; geometry_msgs/Pose _stop_line
       (send _stop_line :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _lanelet_id
     (setq _lanelet_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/Pose _pose
     (send _pose :deserialize buf ptr-) (incf ptr- (send _pose :serialization-length))
   ;; hmcl_msgs/TrafficlightBulb _left_light
     (send _left_light :deserialize buf ptr-) (incf ptr- (send _left_light :serialization-length))
   ;; hmcl_msgs/TrafficlightBulb _straight_light
     (send _straight_light :deserialize buf ptr-) (incf ptr- (send _straight_light :serialization-length))
   ;; hmcl_msgs/TrafficlightBulb _right_light
     (send _right_light :deserialize buf ptr-) (incf ptr- (send _right_light :serialization-length))
   ;; bool _valid_stop_line
     (setq _valid_stop_line (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; geometry_msgs/Pose _stop_line
     (send _stop_line :deserialize buf ptr-) (incf ptr- (send _stop_line :serialization-length))
   ;;
   self)
  )

(setf (get hmcl_msgs::Trafficlight :md5sum-) "a8bcc1bd70d49e0e7bdd9aa331d45dc1")
(setf (get hmcl_msgs::Trafficlight :datatype-) "hmcl_msgs/Trafficlight")
(setf (get hmcl_msgs::Trafficlight :definition-)
      "Header header
int32 id
int32 lanelet_id
geometry_msgs/Pose pose
TrafficlightBulb left_light
TrafficlightBulb straight_light
TrafficlightBulb right_light
bool valid_stop_line
geometry_msgs/Pose stop_line
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
MSG: hmcl_msgs/TrafficlightBulb
int32 id
int32 light_status # 0 red, 1 green, 2 yellow 
")



(provide :hmcl_msgs/Trafficlight "a8bcc1bd70d49e0e7bdd9aa331d45dc1")


