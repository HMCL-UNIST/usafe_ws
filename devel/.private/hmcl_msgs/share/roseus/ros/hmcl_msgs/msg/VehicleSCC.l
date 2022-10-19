;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::VehicleSCC)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'VehicleSCC (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::VEHICLESCC")
  (make-package "HMCL_MSGS::VEHICLESCC"))

(in-package "ROS")
;;//! \htmlinclude VehicleSCC.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::VehicleSCC
  :super ros::object
  :slots (_header _scc_mode _scc_takeover _acceleration ))

(defmethod hmcl_msgs::VehicleSCC
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:scc_mode __scc_mode) 0)
    ((:scc_takeover __scc_takeover) 0)
    ((:acceleration __acceleration) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _scc_mode (round __scc_mode))
   (setq _scc_takeover (round __scc_takeover))
   (setq _acceleration (float __acceleration))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:scc_mode
   (&optional __scc_mode)
   (if __scc_mode (setq _scc_mode __scc_mode)) _scc_mode)
  (:scc_takeover
   (&optional __scc_takeover)
   (if __scc_takeover (setq _scc_takeover __scc_takeover)) _scc_takeover)
  (:acceleration
   (&optional __acceleration)
   (if __acceleration (setq _acceleration __acceleration)) _acceleration)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint8 _scc_mode
    1
    ;; uint8 _scc_takeover
    1
    ;; float64 _acceleration
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint8 _scc_mode
       (write-byte _scc_mode s)
     ;; uint8 _scc_takeover
       (write-byte _scc_takeover s)
     ;; float64 _acceleration
       (sys::poke _acceleration (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint8 _scc_mode
     (setq _scc_mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _scc_takeover
     (setq _scc_takeover (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _acceleration
     (setq _acceleration (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get hmcl_msgs::VehicleSCC :md5sum-) "0471adfa682d3742aa9adb20fb1e2600")
(setf (get hmcl_msgs::VehicleSCC :datatype-) "hmcl_msgs/VehicleSCC")
(setf (get hmcl_msgs::VehicleSCC :definition-)
      "Header header
# sccmode -> off       = 0
# sccmode -> ready       = 1
# sccmode -> on       = 2
uint8 scc_mode
# scc takeover -> off       = 0
# scc takeover -> n      = 1
uint8 scc_takeover
float64 acceleration
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



(provide :hmcl_msgs/VehicleSCC "0471adfa682d3742aa9adb20fb1e2600")


