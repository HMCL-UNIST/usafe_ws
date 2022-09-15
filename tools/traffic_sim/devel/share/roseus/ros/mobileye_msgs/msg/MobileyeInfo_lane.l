;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_lane)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_lane (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_LANE")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_LANE"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_lane.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_lane
  :super ros::object
  :slots (_header _lane ))

(defmethod mobileye_msgs::MobileyeInfo_lane
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:lane __lane) (instance mobileye_msgs::Lane :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _lane __lane)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:lane
   (&rest __lane)
   (if (keywordp (car __lane))
       (send* _lane __lane)
     (progn
       (if __lane (setq _lane (car __lane)))
       _lane)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/Lane _lane
    (send _lane :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/Lane _lane
       (send _lane :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/Lane _lane
     (send _lane :deserialize buf ptr-) (incf ptr- (send _lane :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_lane :md5sum-) "2167664513fbefa299d496bdde8fbd05")
(setf (get mobileye_msgs::MobileyeInfo_lane :datatype-) "mobileye_msgs/MobileyeInfo_lane")
(setf (get mobileye_msgs::MobileyeInfo_lane :definition-)
      "Header header

Lane lane


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
MSG: mobileye_msgs/Lane
float32 lane_curvature
float32 lane_heading

bool ca
float32 pitch_angle
float32 yaw_angle

bool right_ldw_availability
bool left_ldw_availability

")



(provide :mobileye_msgs/MobileyeInfo_lane "2167664513fbefa299d496bdde8fbd05")


