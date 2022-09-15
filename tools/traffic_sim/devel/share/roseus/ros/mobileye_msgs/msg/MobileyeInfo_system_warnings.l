;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_system_warnings)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_system_warnings (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_SYSTEM_WARNINGS")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_SYSTEM_WARNINGS"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_system_warnings.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_system_warnings
  :super ros::object
  :slots (_header _system_warnings ))

(defmethod mobileye_msgs::MobileyeInfo_system_warnings
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:system_warnings __system_warnings) (instance mobileye_msgs::SystemWarnings :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _system_warnings __system_warnings)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:system_warnings
   (&rest __system_warnings)
   (if (keywordp (car __system_warnings))
       (send* _system_warnings __system_warnings)
     (progn
       (if __system_warnings (setq _system_warnings (car __system_warnings)))
       _system_warnings)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/SystemWarnings _system_warnings
    (send _system_warnings :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/SystemWarnings _system_warnings
       (send _system_warnings :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/SystemWarnings _system_warnings
     (send _system_warnings :deserialize buf ptr-) (incf ptr- (send _system_warnings :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_system_warnings :md5sum-) "e70b067bf40c41c403fb3be0e8758d41")
(setf (get mobileye_msgs::MobileyeInfo_system_warnings :datatype-) "mobileye_msgs/MobileyeInfo_system_warnings")
(setf (get mobileye_msgs::MobileyeInfo_system_warnings :definition-)
      "Header header

SystemWarnings system_warnings

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
MSG: mobileye_msgs/SystemWarnings
uint8 sound_type
bool peds_in_dz
bool peds_fcw
uint8 time_indicator

bool error_valid
uint8 error_code
bool zero_speed
bool headway_valid
float32 headway_measurement

bool ldw_off
bool left_ldw_on
bool right_ldw_on
bool fcw_on
bool maintenance
bool failsafe

bool tsr_enabled
bool hw_repeatable_enabled
uint8 headway_warning_level
uint8 tsr_warning_level
bool tamper_alert
")



(provide :mobileye_msgs/MobileyeInfo_system_warnings "e70b067bf40c41c403fb3be0e8758d41")


