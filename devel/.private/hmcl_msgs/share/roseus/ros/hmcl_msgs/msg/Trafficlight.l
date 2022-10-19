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
  :slots (_header _id _pose _valid_stop_line _stop_line ))

(defmethod hmcl_msgs::Trafficlight
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:id __id) 0)
    ((:pose __pose) (instance geometry_msgs::Point32 :init))
    ((:valid_stop_line __valid_stop_line) nil)
    ((:stop_line __stop_line) (instance geometry_msgs::Point32 :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _id (round __id))
   (setq _pose __pose)
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
  (:pose
   (&rest __pose)
   (if (keywordp (car __pose))
       (send* _pose __pose)
     (progn
       (if __pose (setq _pose (car __pose)))
       _pose)))
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
    ;; geometry_msgs/Point32 _pose
    (send _pose :serialization-length)
    ;; bool _valid_stop_line
    1
    ;; geometry_msgs/Point32 _stop_line
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
     ;; geometry_msgs/Point32 _pose
       (send _pose :serialize s)
     ;; bool _valid_stop_line
       (if _valid_stop_line (write-byte -1 s) (write-byte 0 s))
     ;; geometry_msgs/Point32 _stop_line
       (send _stop_line :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/Point32 _pose
     (send _pose :deserialize buf ptr-) (incf ptr- (send _pose :serialization-length))
   ;; bool _valid_stop_line
     (setq _valid_stop_line (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; geometry_msgs/Point32 _stop_line
     (send _stop_line :deserialize buf ptr-) (incf ptr- (send _stop_line :serialization-length))
   ;;
   self)
  )

(setf (get hmcl_msgs::Trafficlight :md5sum-) "fcbbb59b45f60bd6eaff4eb294691b13")
(setf (get hmcl_msgs::Trafficlight :datatype-) "hmcl_msgs/Trafficlight")
(setf (get hmcl_msgs::Trafficlight :definition-)
      "Header header
int32 id
geometry_msgs/Point32 pose
bool valid_stop_line
geometry_msgs/Point32 stop_line
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
MSG: geometry_msgs/Point32
# This contains the position of a point in free space(with 32 bits of precision).
# It is recommeded to use Point wherever possible instead of Point32.  
# 
# This recommendation is to promote interoperability.  
#
# This message is designed to take up less space when sending
# lots of points at once, as in the case of a PointCloud.  

float32 x
float32 y
float32 z
")



(provide :hmcl_msgs/Trafficlight "fcbbb59b45f60bd6eaff4eb294691b13")


