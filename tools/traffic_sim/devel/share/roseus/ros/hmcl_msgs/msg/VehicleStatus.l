;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::VehicleStatus)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'VehicleStatus (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::VEHICLESTATUS")
  (make-package "HMCL_MSGS::VEHICLESTATUS"))

(in-package "ROS")
;;//! \htmlinclude VehicleStatus.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::VehicleStatus
  :super ros::object
  :slots (_header _steering_info _scc_info _wheelspeed _gear_info _light_info _remote_button_info _auto_mode _ems_mode _x_acceleration _y_acceleration _yaw_rate ))

(defmethod hmcl_msgs::VehicleStatus
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:steering_info __steering_info) (instance hmcl_msgs::VehicleSteering :init))
    ((:scc_info __scc_info) (instance hmcl_msgs::VehicleSCC :init))
    ((:wheelspeed __wheelspeed) (instance hmcl_msgs::VehicleWheelSpeed :init))
    ((:gear_info __gear_info) (instance hmcl_msgs::VehicleGear :init))
    ((:light_info __light_info) (instance hmcl_msgs::VehicleLight :init))
    ((:remote_button_info __remote_button_info) (instance hmcl_msgs::RemoteButton :init))
    ((:auto_mode __auto_mode) 0)
    ((:ems_mode __ems_mode) 0)
    ((:x_acceleration __x_acceleration) 0.0)
    ((:y_acceleration __y_acceleration) 0.0)
    ((:yaw_rate __yaw_rate) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _steering_info __steering_info)
   (setq _scc_info __scc_info)
   (setq _wheelspeed __wheelspeed)
   (setq _gear_info __gear_info)
   (setq _light_info __light_info)
   (setq _remote_button_info __remote_button_info)
   (setq _auto_mode (round __auto_mode))
   (setq _ems_mode (round __ems_mode))
   (setq _x_acceleration (float __x_acceleration))
   (setq _y_acceleration (float __y_acceleration))
   (setq _yaw_rate (float __yaw_rate))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:steering_info
   (&rest __steering_info)
   (if (keywordp (car __steering_info))
       (send* _steering_info __steering_info)
     (progn
       (if __steering_info (setq _steering_info (car __steering_info)))
       _steering_info)))
  (:scc_info
   (&rest __scc_info)
   (if (keywordp (car __scc_info))
       (send* _scc_info __scc_info)
     (progn
       (if __scc_info (setq _scc_info (car __scc_info)))
       _scc_info)))
  (:wheelspeed
   (&rest __wheelspeed)
   (if (keywordp (car __wheelspeed))
       (send* _wheelspeed __wheelspeed)
     (progn
       (if __wheelspeed (setq _wheelspeed (car __wheelspeed)))
       _wheelspeed)))
  (:gear_info
   (&rest __gear_info)
   (if (keywordp (car __gear_info))
       (send* _gear_info __gear_info)
     (progn
       (if __gear_info (setq _gear_info (car __gear_info)))
       _gear_info)))
  (:light_info
   (&rest __light_info)
   (if (keywordp (car __light_info))
       (send* _light_info __light_info)
     (progn
       (if __light_info (setq _light_info (car __light_info)))
       _light_info)))
  (:remote_button_info
   (&rest __remote_button_info)
   (if (keywordp (car __remote_button_info))
       (send* _remote_button_info __remote_button_info)
     (progn
       (if __remote_button_info (setq _remote_button_info (car __remote_button_info)))
       _remote_button_info)))
  (:auto_mode
   (&optional __auto_mode)
   (if __auto_mode (setq _auto_mode __auto_mode)) _auto_mode)
  (:ems_mode
   (&optional __ems_mode)
   (if __ems_mode (setq _ems_mode __ems_mode)) _ems_mode)
  (:x_acceleration
   (&optional __x_acceleration)
   (if __x_acceleration (setq _x_acceleration __x_acceleration)) _x_acceleration)
  (:y_acceleration
   (&optional __y_acceleration)
   (if __y_acceleration (setq _y_acceleration __y_acceleration)) _y_acceleration)
  (:yaw_rate
   (&optional __yaw_rate)
   (if __yaw_rate (setq _yaw_rate __yaw_rate)) _yaw_rate)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; hmcl_msgs/VehicleSteering _steering_info
    (send _steering_info :serialization-length)
    ;; hmcl_msgs/VehicleSCC _scc_info
    (send _scc_info :serialization-length)
    ;; hmcl_msgs/VehicleWheelSpeed _wheelspeed
    (send _wheelspeed :serialization-length)
    ;; hmcl_msgs/VehicleGear _gear_info
    (send _gear_info :serialization-length)
    ;; hmcl_msgs/VehicleLight _light_info
    (send _light_info :serialization-length)
    ;; hmcl_msgs/RemoteButton _remote_button_info
    (send _remote_button_info :serialization-length)
    ;; uint8 _auto_mode
    1
    ;; uint8 _ems_mode
    1
    ;; float64 _x_acceleration
    8
    ;; float64 _y_acceleration
    8
    ;; float64 _yaw_rate
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; hmcl_msgs/VehicleSteering _steering_info
       (send _steering_info :serialize s)
     ;; hmcl_msgs/VehicleSCC _scc_info
       (send _scc_info :serialize s)
     ;; hmcl_msgs/VehicleWheelSpeed _wheelspeed
       (send _wheelspeed :serialize s)
     ;; hmcl_msgs/VehicleGear _gear_info
       (send _gear_info :serialize s)
     ;; hmcl_msgs/VehicleLight _light_info
       (send _light_info :serialize s)
     ;; hmcl_msgs/RemoteButton _remote_button_info
       (send _remote_button_info :serialize s)
     ;; uint8 _auto_mode
       (write-byte _auto_mode s)
     ;; uint8 _ems_mode
       (write-byte _ems_mode s)
     ;; float64 _x_acceleration
       (sys::poke _x_acceleration (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y_acceleration
       (sys::poke _y_acceleration (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _yaw_rate
       (sys::poke _yaw_rate (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; hmcl_msgs/VehicleSteering _steering_info
     (send _steering_info :deserialize buf ptr-) (incf ptr- (send _steering_info :serialization-length))
   ;; hmcl_msgs/VehicleSCC _scc_info
     (send _scc_info :deserialize buf ptr-) (incf ptr- (send _scc_info :serialization-length))
   ;; hmcl_msgs/VehicleWheelSpeed _wheelspeed
     (send _wheelspeed :deserialize buf ptr-) (incf ptr- (send _wheelspeed :serialization-length))
   ;; hmcl_msgs/VehicleGear _gear_info
     (send _gear_info :deserialize buf ptr-) (incf ptr- (send _gear_info :serialization-length))
   ;; hmcl_msgs/VehicleLight _light_info
     (send _light_info :deserialize buf ptr-) (incf ptr- (send _light_info :serialization-length))
   ;; hmcl_msgs/RemoteButton _remote_button_info
     (send _remote_button_info :deserialize buf ptr-) (incf ptr- (send _remote_button_info :serialization-length))
   ;; uint8 _auto_mode
     (setq _auto_mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ems_mode
     (setq _ems_mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _x_acceleration
     (setq _x_acceleration (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y_acceleration
     (setq _y_acceleration (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _yaw_rate
     (setq _yaw_rate (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get hmcl_msgs::VehicleStatus :md5sum-) "257eaa74ca2595e01127664962d58d27")
(setf (get hmcl_msgs::VehicleStatus :datatype-) "hmcl_msgs/VehicleStatus")
(setf (get hmcl_msgs::VehicleStatus :definition-)
      "Header header
hmcl_msgs/VehicleSteering steering_info
hmcl_msgs/VehicleSCC scc_info
hmcl_msgs/VehicleWheelSpeed wheelspeed
hmcl_msgs/VehicleGear gear_info
hmcl_msgs/VehicleLight light_info
hmcl_msgs/RemoteButton remote_button_info
# auto mode -> 0  off
# auto mode -> 1  on
uint8 auto_mode 
# ems mode -> 0  off
# ems mode -> 1  on
uint8 ems_mode 
float64 x_acceleration
float64 y_acceleration
float64 yaw_rate

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
MSG: hmcl_msgs/VehicleSteering
Header header
# steering takeover -> off       = 0
# steering takeover -> on      = 1
uint8 takeover
# steering mode -> off       = 0
# steering mode -> on      = 1
uint8 mode
float32 steering_angle
================================================================================
MSG: hmcl_msgs/VehicleSCC
Header header
# sccmode -> off       = 0
# sccmode -> ready       = 1
# sccmode -> on       = 2
uint8 scc_mode
# scc takeover -> off       = 0
# scc takeover -> n      = 1
uint8 scc_takeover
float64 acceleration
================================================================================
MSG: hmcl_msgs/VehicleWheelSpeed
Header header
float64 wheel_speed
float64 fr
float64 fl
float64 rr
float64 rl
================================================================================
MSG: hmcl_msgs/VehicleGear
# Gear -> P       = 1
# Gear -> D       = 2
# Gear -> N       = 3
# Gear -> R       = 4
uint8 gear

================================================================================
MSG: hmcl_msgs/VehicleLight
# 0 off, 1 on 
uint8 left_light
uint8 right_light
uint8 hazard_light
================================================================================
MSG: hmcl_msgs/RemoteButton
# wirelessbutton -> 0 push off, 1 -> push on
uint8 button1
uint8 button2
uint8 button3
")



(provide :hmcl_msgs/VehicleStatus "257eaa74ca2595e01127664962d58d27")


