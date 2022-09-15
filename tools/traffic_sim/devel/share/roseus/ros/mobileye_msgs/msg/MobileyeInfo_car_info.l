;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_car_info)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_car_info (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_CAR_INFO")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_CAR_INFO"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_car_info.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_car_info
  :super ros::object
  :slots (_header _car_info ))

(defmethod mobileye_msgs::MobileyeInfo_car_info
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:car_info __car_info) (instance mobileye_msgs::CarInfo :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _car_info __car_info)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:car_info
   (&rest __car_info)
   (if (keywordp (car __car_info))
       (send* _car_info __car_info)
     (progn
       (if __car_info (setq _car_info (car __car_info)))
       _car_info)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/CarInfo _car_info
    (send _car_info :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/CarInfo _car_info
       (send _car_info :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/CarInfo _car_info
     (send _car_info :deserialize buf ptr-) (incf ptr- (send _car_info :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_car_info :md5sum-) "9dfc1f88c8be2e512dbe7a4b8cea7bad")
(setf (get mobileye_msgs::MobileyeInfo_car_info :datatype-) "mobileye_msgs/MobileyeInfo_car_info")
(setf (get mobileye_msgs::MobileyeInfo_car_info :definition-)
      "Header header

CarInfo car_info

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
MSG: mobileye_msgs/CarInfo
bool high_beam
bool low_beam
bool wipers
bool right_signal
bool left_signal
bool brake_signal
bool wipers_available
bool low_beam_available
bool high_beam_available
bool right_blink_available
bool left_blink_available
bool brake_available
bool speed_available
uint8 speed
uint8 shield_plus_settings
")



(provide :mobileye_msgs/MobileyeInfo_car_info "9dfc1f88c8be2e512dbe7a4b8cea7bad")


