;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::stateEstimatorStatus)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'stateEstimatorStatus (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::STATEESTIMATORSTATUS")
  (make-package "AUTORALLY_MSGS::STATEESTIMATORSTATUS"))

(in-package "ROS")
;;//! \htmlinclude stateEstimatorStatus.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(intern "*OK*" (find-package "AUTORALLY_MSGS::STATEESTIMATORSTATUS"))
(shadow '*OK* (find-package "AUTORALLY_MSGS::STATEESTIMATORSTATUS"))
(defconstant autorally_msgs::stateEstimatorStatus::*OK* 0)
(intern "*WARN*" (find-package "AUTORALLY_MSGS::STATEESTIMATORSTATUS"))
(shadow '*WARN* (find-package "AUTORALLY_MSGS::STATEESTIMATORSTATUS"))
(defconstant autorally_msgs::stateEstimatorStatus::*WARN* 1)
(intern "*ERROR*" (find-package "AUTORALLY_MSGS::STATEESTIMATORSTATUS"))
(shadow '*ERROR* (find-package "AUTORALLY_MSGS::STATEESTIMATORSTATUS"))
(defconstant autorally_msgs::stateEstimatorStatus::*ERROR* 2)
(defclass autorally_msgs::stateEstimatorStatus
  :super ros::object
  :slots (_header _status ))

(defmethod autorally_msgs::stateEstimatorStatus
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:status __status) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _status (round __status))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; byte _status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; byte _status
       (write-byte _status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; byte _status
     (setq _status (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _status 127) (setq _status (- _status 256)))
   ;;
   self)
  )

(setf (get autorally_msgs::stateEstimatorStatus :md5sum-) "35699761f8100be9b6c52444c8cfff99")
(setf (get autorally_msgs::stateEstimatorStatus :datatype-) "autorally_msgs/stateEstimatorStatus")
(setf (get autorally_msgs::stateEstimatorStatus :definition-)
      "# message for communicating the status of the state estimator
Header header

# possible statuses
byte OK=0     # standard operation
byte WARN=1   # state estimator is not currently trustworthy
byte ERROR=2  # state estimator has encountered an unrecoverable error

byte status # status types enumerated above

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



(provide :autorally_msgs/stateEstimatorStatus "35699761f8100be9b6c52444c8cfff99")


