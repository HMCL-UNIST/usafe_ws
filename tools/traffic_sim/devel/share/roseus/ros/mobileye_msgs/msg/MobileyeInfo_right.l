;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_right)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_right (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_RIGHT")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_RIGHT"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_right.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_right
  :super ros::object
  :slots (_header _right_lane ))

(defmethod mobileye_msgs::MobileyeInfo_right
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:right_lane __right_lane) (instance mobileye_msgs::LKAlane :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _right_lane __right_lane)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:right_lane
   (&rest __right_lane)
   (if (keywordp (car __right_lane))
       (send* _right_lane __right_lane)
     (progn
       (if __right_lane (setq _right_lane (car __right_lane)))
       _right_lane)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/LKAlane _right_lane
    (send _right_lane :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/LKAlane _right_lane
       (send _right_lane :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/LKAlane _right_lane
     (send _right_lane :deserialize buf ptr-) (incf ptr- (send _right_lane :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_right :md5sum-) "f403053ee52387e5c63c01fd8df420e3")
(setf (get mobileye_msgs::MobileyeInfo_right :datatype-) "mobileye_msgs/MobileyeInfo_right")
(setf (get mobileye_msgs::MobileyeInfo_right :definition-)
      "Header header

LKAlane right_lane


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
MSG: mobileye_msgs/LKAlane
uint8 lane_type
uint8 quality
uint8 model_degree

float32 position_parameter_c0
float32 curvature_parameter_c2
float32 curvature_derivative_c3
float32 width_marking

float32 heading_angle_parameter_c1
float32 view_range
bool view_range_availability

")



(provide :mobileye_msgs/MobileyeInfo_right "f403053ee52387e5c63c01fd8df420e3")


