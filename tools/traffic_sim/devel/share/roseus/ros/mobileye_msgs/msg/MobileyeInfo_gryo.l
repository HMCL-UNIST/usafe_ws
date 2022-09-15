;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_gryo)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_gryo (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_GRYO")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_GRYO"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_gryo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_gryo
  :super ros::object
  :slots (_header _gyro ))

(defmethod mobileye_msgs::MobileyeInfo_gryo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:gyro __gyro) (instance mobileye_msgs::Gyro :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _gyro __gyro)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:gyro
   (&rest __gyro)
   (if (keywordp (car __gyro))
       (send* _gyro __gyro)
     (progn
       (if __gyro (setq _gyro (car __gyro)))
       _gyro)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/Gyro _gyro
    (send _gyro :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/Gyro _gyro
       (send _gyro :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/Gyro _gyro
     (send _gyro :deserialize buf ptr-) (incf ptr- (send _gyro :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_gryo :md5sum-) "bd2f1742b1504f840215de76070ae32a")
(setf (get mobileye_msgs::MobileyeInfo_gryo :datatype-) "mobileye_msgs/MobileyeInfo_gryo")
(setf (get mobileye_msgs::MobileyeInfo_gryo :definition-)
      "Header header

Gyro gyro

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
MSG: mobileye_msgs/Gyro
bool gyro_sensor_data_available
float32 x_axis_data
")



(provide :mobileye_msgs/MobileyeInfo_gryo "bd2f1742b1504f840215de76070ae32a")


