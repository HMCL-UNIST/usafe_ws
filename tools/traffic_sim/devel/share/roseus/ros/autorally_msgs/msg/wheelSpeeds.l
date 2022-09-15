;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::wheelSpeeds)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'wheelSpeeds (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::WHEELSPEEDS")
  (make-package "AUTORALLY_MSGS::WHEELSPEEDS"))

(in-package "ROS")
;;//! \htmlinclude wheelSpeeds.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass autorally_msgs::wheelSpeeds
  :super ros::object
  :slots (_header _lfSpeed _rfSpeed _lbSpeed _rbSpeed ))

(defmethod autorally_msgs::wheelSpeeds
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:lfSpeed __lfSpeed) 0.0)
    ((:rfSpeed __rfSpeed) 0.0)
    ((:lbSpeed __lbSpeed) 0.0)
    ((:rbSpeed __rbSpeed) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _lfSpeed (float __lfSpeed))
   (setq _rfSpeed (float __rfSpeed))
   (setq _lbSpeed (float __lbSpeed))
   (setq _rbSpeed (float __rbSpeed))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:lfSpeed
   (&optional __lfSpeed)
   (if __lfSpeed (setq _lfSpeed __lfSpeed)) _lfSpeed)
  (:rfSpeed
   (&optional __rfSpeed)
   (if __rfSpeed (setq _rfSpeed __rfSpeed)) _rfSpeed)
  (:lbSpeed
   (&optional __lbSpeed)
   (if __lbSpeed (setq _lbSpeed __lbSpeed)) _lbSpeed)
  (:rbSpeed
   (&optional __rbSpeed)
   (if __rbSpeed (setq _rbSpeed __rbSpeed)) _rbSpeed)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _lfSpeed
    8
    ;; float64 _rfSpeed
    8
    ;; float64 _lbSpeed
    8
    ;; float64 _rbSpeed
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _lfSpeed
       (sys::poke _lfSpeed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rfSpeed
       (sys::poke _rfSpeed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _lbSpeed
       (sys::poke _lbSpeed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rbSpeed
       (sys::poke _rbSpeed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _lfSpeed
     (setq _lfSpeed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rfSpeed
     (setq _rfSpeed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _lbSpeed
     (setq _lbSpeed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rbSpeed
     (setq _rbSpeed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autorally_msgs::wheelSpeeds :md5sum-) "c5c4a96a4e17d91e72a2f7397af4d720")
(setf (get autorally_msgs::wheelSpeeds :datatype-) "autorally_msgs/wheelSpeeds")
(setf (get autorally_msgs::wheelSpeeds :definition-)
      "Header header
float64 lfSpeed
float64 rfSpeed
float64 lbSpeed
float64 rbSpeed

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



(provide :autorally_msgs/wheelSpeeds "c5c4a96a4e17d91e72a2f7397af4d720")


