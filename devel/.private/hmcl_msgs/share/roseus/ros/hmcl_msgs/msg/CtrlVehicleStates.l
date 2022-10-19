;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::CtrlVehicleStates)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'CtrlVehicleStates (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::CTRLVEHICLESTATES")
  (make-package "HMCL_MSGS::CTRLVEHICLESTATES"))

(in-package "ROS")
;;//! \htmlinclude CtrlVehicleStates.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::CtrlVehicleStates
  :super ros::object
  :slots (_header _delta _ey _epsi _dt _curvature ))

(defmethod hmcl_msgs::CtrlVehicleStates
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:delta __delta) 0.0)
    ((:ey __ey) 0.0)
    ((:epsi __epsi) 0.0)
    ((:dt __dt) 0.0)
    ((:curvature __curvature) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _delta (float __delta))
   (setq _ey (float __ey))
   (setq _epsi (float __epsi))
   (setq _dt (float __dt))
   (setq _curvature __curvature)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:delta
   (&optional __delta)
   (if __delta (setq _delta __delta)) _delta)
  (:ey
   (&optional __ey)
   (if __ey (setq _ey __ey)) _ey)
  (:epsi
   (&optional __epsi)
   (if __epsi (setq _epsi __epsi)) _epsi)
  (:dt
   (&optional __dt)
   (if __dt (setq _dt __dt)) _dt)
  (:curvature
   (&optional __curvature)
   (if __curvature (setq _curvature __curvature)) _curvature)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _delta
    8
    ;; float64 _ey
    8
    ;; float64 _epsi
    8
    ;; float64 _dt
    8
    ;; float64[] _curvature
    (* 8    (length _curvature)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _delta
       (sys::poke _delta (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ey
       (sys::poke _ey (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _epsi
       (sys::poke _epsi (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dt
       (sys::poke _dt (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64[] _curvature
     (write-long (length _curvature) s)
     (dotimes (i (length _curvature))
       (sys::poke (elt _curvature i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _delta
     (setq _delta (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ey
     (setq _ey (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _epsi
     (setq _epsi (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dt
     (setq _dt (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64[] _curvature
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _curvature (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _curvature i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get hmcl_msgs::CtrlVehicleStates :md5sum-) "050afb3606d23886eff6dc2145e85984")
(setf (get hmcl_msgs::CtrlVehicleStates :datatype-) "hmcl_msgs/CtrlVehicleStates")
(setf (get hmcl_msgs::CtrlVehicleStates :definition-)
      "Header header
float64 delta
float64 ey
float64 epsi
float64 dt
float64[] curvature
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



(provide :hmcl_msgs/CtrlVehicleStates "050afb3606d23886eff6dc2145e85984")


