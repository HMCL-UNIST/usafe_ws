;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::runstop)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'runstop (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::RUNSTOP")
  (make-package "AUTORALLY_MSGS::RUNSTOP"))

(in-package "ROS")
;;//! \htmlinclude runstop.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass autorally_msgs::runstop
  :super ros::object
  :slots (_header _sender _motionEnabled ))

(defmethod autorally_msgs::runstop
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:sender __sender) "")
    ((:motionEnabled __motionEnabled) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _sender (string __sender))
   (setq _motionEnabled __motionEnabled)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:sender
   (&optional __sender)
   (if __sender (setq _sender __sender)) _sender)
  (:motionEnabled
   (&optional __motionEnabled)
   (if __motionEnabled (setq _motionEnabled __motionEnabled)) _motionEnabled)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _sender
    4 (length _sender)
    ;; bool _motionEnabled
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _sender
       (write-long (length _sender) s) (princ _sender s)
     ;; bool _motionEnabled
       (if _motionEnabled (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _sender
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _sender (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; bool _motionEnabled
     (setq _motionEnabled (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get autorally_msgs::runstop :md5sum-) "996dff250e70bc8cde0b272375a5684d")
(setf (get autorally_msgs::runstop :datatype-) "autorally_msgs/runstop")
(setf (get autorally_msgs::runstop :definition-)
      "Header header

string sender
bool motionEnabled
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



(provide :autorally_msgs/runstop "996dff250e70bc8cde0b272375a5684d")


