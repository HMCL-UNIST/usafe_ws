;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_smart_adas)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_smart_adas (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_SMART_ADAS")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_SMART_ADAS"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_smart_adas.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_smart_adas
  :super ros::object
  :slots (_header _smart_adas ))

(defmethod mobileye_msgs::MobileyeInfo_smart_adas
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:smart_adas __smart_adas) (instance mobileye_msgs::SmartADAS :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _smart_adas __smart_adas)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:smart_adas
   (&rest __smart_adas)
   (if (keywordp (car __smart_adas))
       (send* _smart_adas __smart_adas)
     (progn
       (if __smart_adas (setq _smart_adas (car __smart_adas)))
       _smart_adas)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/SmartADAS _smart_adas
    (send _smart_adas :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/SmartADAS _smart_adas
       (send _smart_adas :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/SmartADAS _smart_adas
     (send _smart_adas :deserialize buf ptr-) (incf ptr- (send _smart_adas :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_smart_adas :md5sum-) "1b63fad4adb86b289d19be4eadb354a3")
(setf (get mobileye_msgs::MobileyeInfo_smart_adas :datatype-) "mobileye_msgs/MobileyeInfo_smart_adas")
(setf (get mobileye_msgs::MobileyeInfo_smart_adas :definition-)
      "Header header

SmartADAS smart_adas

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
MSG: mobileye_msgs/SmartADAS
uint8 persistent_on_off
uint8 volume_level
uint8 hmw_level
uint8 ldw_volume_level
uint8 hmw_volume_level
uint8 ldw_level
uint8 pedestrian_warning_level
uint8 sli_warning_level
uint8 blinker_reminder_level
uint8 virtual_bumper_level
uint8 hw_repeatable_level

uint8 buzzer_min_volume
uint8 buzzer_max_volume
uint8 buzzer_hmw_min_volume
uint8 buzzer_hmw_max_volume
uint8 buzzer_ldw_min_volume
uint8 buzzer_ldw_max_volume
uint8 ewiii_speed_indication
uint8 disable_system_off
uint8 calibration_source
uint8 ldw_min_value
uint8 ldw_max_value
uint8 ldw_speed
uint8 ped_min_value
uint8 ped_max_value
uint8 speed_for_high_low_beam_control
uint8 virtual_bumper_min_value
uint8 virtual_bumper_max_value
uint8 blinker_reminder_min_value
uint8 blinker_reminder_max_value

uint8 hmw_min_value
uint8 hmw_max_value
uint8 hmw_repeatable_min_value
uint8 hmw_repeatable_max_value
uint8 sli_min_value
uint8 sli_max_value
uint8 sli_delta_round_step
uint8 sli_delta_round_upwards
uint8 country_code
uint8 sli_unit_speed
uint8 tamper_alert_on_frames
uint8 tamper_alert_off_frames
uint8 tamper_alert_enable_j1939

bool[16] menu_ticks

bool[16] advanced_menu_ticks
")



(provide :mobileye_msgs/MobileyeInfo_smart_adas "1b63fad4adb86b289d19be4eadb354a3")


