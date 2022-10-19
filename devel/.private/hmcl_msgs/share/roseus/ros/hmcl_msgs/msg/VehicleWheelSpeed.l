;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::VehicleWheelSpeed)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'VehicleWheelSpeed (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::VEHICLEWHEELSPEED")
  (make-package "HMCL_MSGS::VEHICLEWHEELSPEED"))

(in-package "ROS")
;;//! \htmlinclude VehicleWheelSpeed.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::VehicleWheelSpeed
  :super ros::object
  :slots (_header _wheel_speed _fr _fl _rr _rl ))

(defmethod hmcl_msgs::VehicleWheelSpeed
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:wheel_speed __wheel_speed) 0.0)
    ((:fr __fr) 0.0)
    ((:fl __fl) 0.0)
    ((:rr __rr) 0.0)
    ((:rl __rl) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _wheel_speed (float __wheel_speed))
   (setq _fr (float __fr))
   (setq _fl (float __fl))
   (setq _rr (float __rr))
   (setq _rl (float __rl))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:wheel_speed
   (&optional __wheel_speed)
   (if __wheel_speed (setq _wheel_speed __wheel_speed)) _wheel_speed)
  (:fr
   (&optional __fr)
   (if __fr (setq _fr __fr)) _fr)
  (:fl
   (&optional __fl)
   (if __fl (setq _fl __fl)) _fl)
  (:rr
   (&optional __rr)
   (if __rr (setq _rr __rr)) _rr)
  (:rl
   (&optional __rl)
   (if __rl (setq _rl __rl)) _rl)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _wheel_speed
    8
    ;; float64 _fr
    8
    ;; float64 _fl
    8
    ;; float64 _rr
    8
    ;; float64 _rl
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _wheel_speed
       (sys::poke _wheel_speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fr
       (sys::poke _fr (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fl
       (sys::poke _fl (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rr
       (sys::poke _rr (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rl
       (sys::poke _rl (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _wheel_speed
     (setq _wheel_speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fr
     (setq _fr (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fl
     (setq _fl (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rr
     (setq _rr (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rl
     (setq _rl (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get hmcl_msgs::VehicleWheelSpeed :md5sum-) "dd9bfec439fcf31963b917a79106fa20")
(setf (get hmcl_msgs::VehicleWheelSpeed :datatype-) "hmcl_msgs/VehicleWheelSpeed")
(setf (get hmcl_msgs::VehicleWheelSpeed :definition-)
      "Header header
float64 wheel_speed
float64 fr
float64 fl
float64 rr
float64 rl
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



(provide :hmcl_msgs/VehicleWheelSpeed "dd9bfec439fcf31963b917a79106fa20")


