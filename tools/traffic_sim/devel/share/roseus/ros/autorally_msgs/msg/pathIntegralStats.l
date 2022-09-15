;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::pathIntegralStats)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'pathIntegralStats (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::PATHINTEGRALSTATS")
  (make-package "AUTORALLY_MSGS::PATHINTEGRALSTATS"))

(in-package "ROS")
;;//! \htmlinclude pathIntegralStats.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass autorally_msgs::pathIntegralStats
  :super ros::object
  :slots (_header _tag _params _stats ))

(defmethod autorally_msgs::pathIntegralStats
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:tag __tag) "")
    ((:params __params) (instance autorally_msgs::pathIntegralParams :init))
    ((:stats __stats) (instance autorally_msgs::lapStats :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _tag (string __tag))
   (setq _params __params)
   (setq _stats __stats)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:tag
   (&optional __tag)
   (if __tag (setq _tag __tag)) _tag)
  (:params
   (&rest __params)
   (if (keywordp (car __params))
       (send* _params __params)
     (progn
       (if __params (setq _params (car __params)))
       _params)))
  (:stats
   (&rest __stats)
   (if (keywordp (car __stats))
       (send* _stats __stats)
     (progn
       (if __stats (setq _stats (car __stats)))
       _stats)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _tag
    4 (length _tag)
    ;; autorally_msgs/pathIntegralParams _params
    (send _params :serialization-length)
    ;; autorally_msgs/lapStats _stats
    (send _stats :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _tag
       (write-long (length _tag) s) (princ _tag s)
     ;; autorally_msgs/pathIntegralParams _params
       (send _params :serialize s)
     ;; autorally_msgs/lapStats _stats
       (send _stats :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _tag
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _tag (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; autorally_msgs/pathIntegralParams _params
     (send _params :deserialize buf ptr-) (incf ptr- (send _params :serialization-length))
   ;; autorally_msgs/lapStats _stats
     (send _stats :deserialize buf ptr-) (incf ptr- (send _stats :serialization-length))
   ;;
   self)
  )

(setf (get autorally_msgs::pathIntegralStats :md5sum-) "cfb6f9017ebb92f4695492c3201de3c3")
(setf (get autorally_msgs::pathIntegralStats :datatype-) "autorally_msgs/pathIntegralStats")
(setf (get autorally_msgs::pathIntegralStats :definition-)
      "Header header
string tag

pathIntegralParams params
lapStats stats

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
MSG: autorally_msgs/pathIntegralParams
int64 hz
int64 num_timesteps
int64 num_iters
float64 gamma
float64 init_steering
float64 init_throttle
float64 steering_var
float64 throttle_var
float64 max_throttle
float64 speed_coefficient
float64 track_coefficient
float64 max_slip_angle
float64 track_slop
float64 crash_coeff
string map_path
float64 desired_speed
================================================================================
MSG: autorally_msgs/lapStats
int64 lap_number
float64 lap_time
float64 max_speed
float64 max_slip

")



(provide :autorally_msgs/pathIntegralStats "cfb6f9017ebb92f4695492c3201de3c3")


