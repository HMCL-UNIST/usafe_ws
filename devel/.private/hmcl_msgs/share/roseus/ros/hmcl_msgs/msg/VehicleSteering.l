;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::VehicleSteering)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'VehicleSteering (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::VEHICLESTEERING")
  (make-package "HMCL_MSGS::VEHICLESTEERING"))

(in-package "ROS")
;;//! \htmlinclude VehicleSteering.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::VehicleSteering
  :super ros::object
  :slots (_header _takeover _mode _steering_angle ))

(defmethod hmcl_msgs::VehicleSteering
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:takeover __takeover) 0)
    ((:mode __mode) 0)
    ((:steering_angle __steering_angle) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _takeover (round __takeover))
   (setq _mode (round __mode))
   (setq _steering_angle (float __steering_angle))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:takeover
   (&optional __takeover)
   (if __takeover (setq _takeover __takeover)) _takeover)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:steering_angle
   (&optional __steering_angle)
   (if __steering_angle (setq _steering_angle __steering_angle)) _steering_angle)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint8 _takeover
    1
    ;; uint8 _mode
    1
    ;; float32 _steering_angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint8 _takeover
       (write-byte _takeover s)
     ;; uint8 _mode
       (write-byte _mode s)
     ;; float32 _steering_angle
       (sys::poke _steering_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint8 _takeover
     (setq _takeover (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _steering_angle
     (setq _steering_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get hmcl_msgs::VehicleSteering :md5sum-) "5fb428b383c979ad23048575d907b4bf")
(setf (get hmcl_msgs::VehicleSteering :datatype-) "hmcl_msgs/VehicleSteering")
(setf (get hmcl_msgs::VehicleSteering :definition-)
      "Header header
# steering takeover -> off       = 0
# steering takeover -> on      = 1
uint8 takeover
# steering mode -> off       = 0
# steering mode -> on      = 1
uint8 mode
float32 steering_angle
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

")



(provide :hmcl_msgs/VehicleSteering "5fb428b383c979ad23048575d907b4bf")


