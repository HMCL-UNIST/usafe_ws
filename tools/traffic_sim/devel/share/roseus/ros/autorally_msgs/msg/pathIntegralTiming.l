;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::pathIntegralTiming)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'pathIntegralTiming (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::PATHINTEGRALTIMING")
  (make-package "AUTORALLY_MSGS::PATHINTEGRALTIMING"))

(in-package "ROS")
;;//! \htmlinclude pathIntegralTiming.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass autorally_msgs::pathIntegralTiming
  :super ros::object
  :slots (_header _averageTimeBetweenPoses _averageOptimizationCycleTime _averageSleepTime ))

(defmethod autorally_msgs::pathIntegralTiming
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:averageTimeBetweenPoses __averageTimeBetweenPoses) 0.0)
    ((:averageOptimizationCycleTime __averageOptimizationCycleTime) 0.0)
    ((:averageSleepTime __averageSleepTime) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _averageTimeBetweenPoses (float __averageTimeBetweenPoses))
   (setq _averageOptimizationCycleTime (float __averageOptimizationCycleTime))
   (setq _averageSleepTime (float __averageSleepTime))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:averageTimeBetweenPoses
   (&optional __averageTimeBetweenPoses)
   (if __averageTimeBetweenPoses (setq _averageTimeBetweenPoses __averageTimeBetweenPoses)) _averageTimeBetweenPoses)
  (:averageOptimizationCycleTime
   (&optional __averageOptimizationCycleTime)
   (if __averageOptimizationCycleTime (setq _averageOptimizationCycleTime __averageOptimizationCycleTime)) _averageOptimizationCycleTime)
  (:averageSleepTime
   (&optional __averageSleepTime)
   (if __averageSleepTime (setq _averageSleepTime __averageSleepTime)) _averageSleepTime)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _averageTimeBetweenPoses
    8
    ;; float64 _averageOptimizationCycleTime
    8
    ;; float64 _averageSleepTime
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _averageTimeBetweenPoses
       (sys::poke _averageTimeBetweenPoses (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _averageOptimizationCycleTime
       (sys::poke _averageOptimizationCycleTime (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _averageSleepTime
       (sys::poke _averageSleepTime (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _averageTimeBetweenPoses
     (setq _averageTimeBetweenPoses (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _averageOptimizationCycleTime
     (setq _averageOptimizationCycleTime (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _averageSleepTime
     (setq _averageSleepTime (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autorally_msgs::pathIntegralTiming :md5sum-) "3b1cf4994787687384fe2dcbe9c92b69")
(setf (get autorally_msgs::pathIntegralTiming :datatype-) "autorally_msgs/pathIntegralTiming")
(setf (get autorally_msgs::pathIntegralTiming :definition-)
      "Header header

float64 averageTimeBetweenPoses
float64 averageOptimizationCycleTime
float64 averageSleepTime

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



(provide :autorally_msgs/pathIntegralTiming "3b1cf4994787687384fe2dcbe9c92b69")


