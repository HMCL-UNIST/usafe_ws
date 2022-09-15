;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::StandardCAN)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'StandardCAN (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::STANDARDCAN")
  (make-package "MOBILEYE_MSGS::STANDARDCAN"))

(in-package "ROS")
;;//! \htmlinclude StandardCAN.msg.html


(defclass mobileye_msgs::StandardCAN
  :super ros::object
  :slots (_system_warnings _car_info _tsr _tsr_vision_only _gyro _smart_adas _seeq ))

(defmethod mobileye_msgs::StandardCAN
  (:init
   (&key
    ((:system_warnings __system_warnings) (instance mobileye_msgs::SystemWarnings :init))
    ((:car_info __car_info) (instance mobileye_msgs::CarInfo :init))
    ((:tsr __tsr) (let (r) (dotimes (i 0) (push (instance mobileye_msgs::TSR :init) r)) r))
    ((:tsr_vision_only __tsr_vision_only) (instance mobileye_msgs::TSRVisionOnlySign :init))
    ((:gyro __gyro) (instance mobileye_msgs::Gyro :init))
    ((:smart_adas __smart_adas) (instance mobileye_msgs::SmartADAS :init))
    ((:seeq __seeq) (instance mobileye_msgs::SeeQ :init))
    )
   (send-super :init)
   (setq _system_warnings __system_warnings)
   (setq _car_info __car_info)
   (setq _tsr __tsr)
   (setq _tsr_vision_only __tsr_vision_only)
   (setq _gyro __gyro)
   (setq _smart_adas __smart_adas)
   (setq _seeq __seeq)
   self)
  (:system_warnings
   (&rest __system_warnings)
   (if (keywordp (car __system_warnings))
       (send* _system_warnings __system_warnings)
     (progn
       (if __system_warnings (setq _system_warnings (car __system_warnings)))
       _system_warnings)))
  (:car_info
   (&rest __car_info)
   (if (keywordp (car __car_info))
       (send* _car_info __car_info)
     (progn
       (if __car_info (setq _car_info (car __car_info)))
       _car_info)))
  (:tsr
   (&rest __tsr)
   (if (keywordp (car __tsr))
       (send* _tsr __tsr)
     (progn
       (if __tsr (setq _tsr (car __tsr)))
       _tsr)))
  (:tsr_vision_only
   (&rest __tsr_vision_only)
   (if (keywordp (car __tsr_vision_only))
       (send* _tsr_vision_only __tsr_vision_only)
     (progn
       (if __tsr_vision_only (setq _tsr_vision_only (car __tsr_vision_only)))
       _tsr_vision_only)))
  (:gyro
   (&rest __gyro)
   (if (keywordp (car __gyro))
       (send* _gyro __gyro)
     (progn
       (if __gyro (setq _gyro (car __gyro)))
       _gyro)))
  (:smart_adas
   (&rest __smart_adas)
   (if (keywordp (car __smart_adas))
       (send* _smart_adas __smart_adas)
     (progn
       (if __smart_adas (setq _smart_adas (car __smart_adas)))
       _smart_adas)))
  (:seeq
   (&rest __seeq)
   (if (keywordp (car __seeq))
       (send* _seeq __seeq)
     (progn
       (if __seeq (setq _seeq (car __seeq)))
       _seeq)))
  (:serialization-length
   ()
   (+
    ;; mobileye_msgs/SystemWarnings _system_warnings
    (send _system_warnings :serialization-length)
    ;; mobileye_msgs/CarInfo _car_info
    (send _car_info :serialization-length)
    ;; mobileye_msgs/TSR[] _tsr
    (apply #'+ (send-all _tsr :serialization-length)) 4
    ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
    (send _tsr_vision_only :serialization-length)
    ;; mobileye_msgs/Gyro _gyro
    (send _gyro :serialization-length)
    ;; mobileye_msgs/SmartADAS _smart_adas
    (send _smart_adas :serialization-length)
    ;; mobileye_msgs/SeeQ _seeq
    (send _seeq :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; mobileye_msgs/SystemWarnings _system_warnings
       (send _system_warnings :serialize s)
     ;; mobileye_msgs/CarInfo _car_info
       (send _car_info :serialize s)
     ;; mobileye_msgs/TSR[] _tsr
     (write-long (length _tsr) s)
     (dolist (elem _tsr)
       (send elem :serialize s)
       )
     ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
       (send _tsr_vision_only :serialize s)
     ;; mobileye_msgs/Gyro _gyro
       (send _gyro :serialize s)
     ;; mobileye_msgs/SmartADAS _smart_adas
       (send _smart_adas :serialize s)
     ;; mobileye_msgs/SeeQ _seeq
       (send _seeq :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; mobileye_msgs/SystemWarnings _system_warnings
     (send _system_warnings :deserialize buf ptr-) (incf ptr- (send _system_warnings :serialization-length))
   ;; mobileye_msgs/CarInfo _car_info
     (send _car_info :deserialize buf ptr-) (incf ptr- (send _car_info :serialization-length))
   ;; mobileye_msgs/TSR[] _tsr
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _tsr (let (r) (dotimes (i n) (push (instance mobileye_msgs::TSR :init) r)) r))
     (dolist (elem- _tsr)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
     (send _tsr_vision_only :deserialize buf ptr-) (incf ptr- (send _tsr_vision_only :serialization-length))
   ;; mobileye_msgs/Gyro _gyro
     (send _gyro :deserialize buf ptr-) (incf ptr- (send _gyro :serialization-length))
   ;; mobileye_msgs/SmartADAS _smart_adas
     (send _smart_adas :deserialize buf ptr-) (incf ptr- (send _smart_adas :serialization-length))
   ;; mobileye_msgs/SeeQ _seeq
     (send _seeq :deserialize buf ptr-) (incf ptr- (send _seeq :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::StandardCAN :md5sum-) "54e4cfc9bd8b43c069770d7bbb9295cd")
(setf (get mobileye_msgs::StandardCAN :datatype-) "mobileye_msgs/StandardCAN")
(setf (get mobileye_msgs::StandardCAN :definition-)
      "SystemWarnings system_warnings
CarInfo car_info
TSR[] tsr
TSRVisionOnlySign tsr_vision_only
Gyro gyro
SmartADAS smart_adas
SeeQ seeq
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
================================================================================
MSG: mobileye_msgs/CarInfo
bool high_beam
bool low_beam
bool wipers
bool right_signal
bool left_signal
bool brake_signal
bool wipers_available
bool low_beam_available
bool high_beam_available
bool right_blink_available
bool left_blink_available
bool brake_available
bool speed_available
uint8 speed
uint8 shield_plus_settings
================================================================================
MSG: mobileye_msgs/TSR
uint8 vision_only_sign_type
uint8 supplementary_sign_type
float32 sign_position_x
float32 sign_position_y
float32 sign_position_z
uint8 filter_type
================================================================================
MSG: mobileye_msgs/TSRVisionOnlySign
uint8 vision_only_sign_type_display_1
uint8 vision_only_sign_type_display_2
uint8 vision_only_sign_type_display_3
uint8 vision_only_sign_type_display_4

uint8 supplementary_sign_type_display_1
uint8 supplementary_sign_type_display_2
uint8 supplementary_sign_type_display_3
uint8 supplementary_sign_type_display_4
================================================================================
MSG: mobileye_msgs/Gyro
bool gyro_sensor_data_available
float32 x_axis_data
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
================================================================================
MSG: mobileye_msgs/SeeQ
uint32 serial_number
uint64 production_date

uint8 brain_version_major
uint8 brain_version_minor
uint8 mest_version_major
uint8 mest_version_minor
uint8 mest_version_subminor
uint8 mest_version_patch_number
")



(provide :mobileye_msgs/StandardCAN "54e4cfc9bd8b43c069770d7bbb9295cd")


