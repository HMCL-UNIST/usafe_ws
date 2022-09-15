;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::SmartADAS)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'SmartADAS (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::SMARTADAS")
  (make-package "MOBILEYE_MSGS::SMARTADAS"))

(in-package "ROS")
;;//! \htmlinclude SmartADAS.msg.html


(defclass mobileye_msgs::SmartADAS
  :super ros::object
  :slots (_persistent_on_off _volume_level _hmw_level _ldw_volume_level _hmw_volume_level _ldw_level _pedestrian_warning_level _sli_warning_level _blinker_reminder_level _virtual_bumper_level _hw_repeatable_level _buzzer_min_volume _buzzer_max_volume _buzzer_hmw_min_volume _buzzer_hmw_max_volume _buzzer_ldw_min_volume _buzzer_ldw_max_volume _ewiii_speed_indication _disable_system_off _calibration_source _ldw_min_value _ldw_max_value _ldw_speed _ped_min_value _ped_max_value _speed_for_high_low_beam_control _virtual_bumper_min_value _virtual_bumper_max_value _blinker_reminder_min_value _blinker_reminder_max_value _hmw_min_value _hmw_max_value _hmw_repeatable_min_value _hmw_repeatable_max_value _sli_min_value _sli_max_value _sli_delta_round_step _sli_delta_round_upwards _country_code _sli_unit_speed _tamper_alert_on_frames _tamper_alert_off_frames _tamper_alert_enable_j1939 _menu_ticks _advanced_menu_ticks ))

(defmethod mobileye_msgs::SmartADAS
  (:init
   (&key
    ((:persistent_on_off __persistent_on_off) 0)
    ((:volume_level __volume_level) 0)
    ((:hmw_level __hmw_level) 0)
    ((:ldw_volume_level __ldw_volume_level) 0)
    ((:hmw_volume_level __hmw_volume_level) 0)
    ((:ldw_level __ldw_level) 0)
    ((:pedestrian_warning_level __pedestrian_warning_level) 0)
    ((:sli_warning_level __sli_warning_level) 0)
    ((:blinker_reminder_level __blinker_reminder_level) 0)
    ((:virtual_bumper_level __virtual_bumper_level) 0)
    ((:hw_repeatable_level __hw_repeatable_level) 0)
    ((:buzzer_min_volume __buzzer_min_volume) 0)
    ((:buzzer_max_volume __buzzer_max_volume) 0)
    ((:buzzer_hmw_min_volume __buzzer_hmw_min_volume) 0)
    ((:buzzer_hmw_max_volume __buzzer_hmw_max_volume) 0)
    ((:buzzer_ldw_min_volume __buzzer_ldw_min_volume) 0)
    ((:buzzer_ldw_max_volume __buzzer_ldw_max_volume) 0)
    ((:ewiii_speed_indication __ewiii_speed_indication) 0)
    ((:disable_system_off __disable_system_off) 0)
    ((:calibration_source __calibration_source) 0)
    ((:ldw_min_value __ldw_min_value) 0)
    ((:ldw_max_value __ldw_max_value) 0)
    ((:ldw_speed __ldw_speed) 0)
    ((:ped_min_value __ped_min_value) 0)
    ((:ped_max_value __ped_max_value) 0)
    ((:speed_for_high_low_beam_control __speed_for_high_low_beam_control) 0)
    ((:virtual_bumper_min_value __virtual_bumper_min_value) 0)
    ((:virtual_bumper_max_value __virtual_bumper_max_value) 0)
    ((:blinker_reminder_min_value __blinker_reminder_min_value) 0)
    ((:blinker_reminder_max_value __blinker_reminder_max_value) 0)
    ((:hmw_min_value __hmw_min_value) 0)
    ((:hmw_max_value __hmw_max_value) 0)
    ((:hmw_repeatable_min_value __hmw_repeatable_min_value) 0)
    ((:hmw_repeatable_max_value __hmw_repeatable_max_value) 0)
    ((:sli_min_value __sli_min_value) 0)
    ((:sli_max_value __sli_max_value) 0)
    ((:sli_delta_round_step __sli_delta_round_step) 0)
    ((:sli_delta_round_upwards __sli_delta_round_upwards) 0)
    ((:country_code __country_code) 0)
    ((:sli_unit_speed __sli_unit_speed) 0)
    ((:tamper_alert_on_frames __tamper_alert_on_frames) 0)
    ((:tamper_alert_off_frames __tamper_alert_off_frames) 0)
    ((:tamper_alert_enable_j1939 __tamper_alert_enable_j1939) 0)
    ((:menu_ticks __menu_ticks) (let (r) (dotimes (i 16) (push nil r)) r))
    ((:advanced_menu_ticks __advanced_menu_ticks) (let (r) (dotimes (i 16) (push nil r)) r))
    )
   (send-super :init)
   (setq _persistent_on_off (round __persistent_on_off))
   (setq _volume_level (round __volume_level))
   (setq _hmw_level (round __hmw_level))
   (setq _ldw_volume_level (round __ldw_volume_level))
   (setq _hmw_volume_level (round __hmw_volume_level))
   (setq _ldw_level (round __ldw_level))
   (setq _pedestrian_warning_level (round __pedestrian_warning_level))
   (setq _sli_warning_level (round __sli_warning_level))
   (setq _blinker_reminder_level (round __blinker_reminder_level))
   (setq _virtual_bumper_level (round __virtual_bumper_level))
   (setq _hw_repeatable_level (round __hw_repeatable_level))
   (setq _buzzer_min_volume (round __buzzer_min_volume))
   (setq _buzzer_max_volume (round __buzzer_max_volume))
   (setq _buzzer_hmw_min_volume (round __buzzer_hmw_min_volume))
   (setq _buzzer_hmw_max_volume (round __buzzer_hmw_max_volume))
   (setq _buzzer_ldw_min_volume (round __buzzer_ldw_min_volume))
   (setq _buzzer_ldw_max_volume (round __buzzer_ldw_max_volume))
   (setq _ewiii_speed_indication (round __ewiii_speed_indication))
   (setq _disable_system_off (round __disable_system_off))
   (setq _calibration_source (round __calibration_source))
   (setq _ldw_min_value (round __ldw_min_value))
   (setq _ldw_max_value (round __ldw_max_value))
   (setq _ldw_speed (round __ldw_speed))
   (setq _ped_min_value (round __ped_min_value))
   (setq _ped_max_value (round __ped_max_value))
   (setq _speed_for_high_low_beam_control (round __speed_for_high_low_beam_control))
   (setq _virtual_bumper_min_value (round __virtual_bumper_min_value))
   (setq _virtual_bumper_max_value (round __virtual_bumper_max_value))
   (setq _blinker_reminder_min_value (round __blinker_reminder_min_value))
   (setq _blinker_reminder_max_value (round __blinker_reminder_max_value))
   (setq _hmw_min_value (round __hmw_min_value))
   (setq _hmw_max_value (round __hmw_max_value))
   (setq _hmw_repeatable_min_value (round __hmw_repeatable_min_value))
   (setq _hmw_repeatable_max_value (round __hmw_repeatable_max_value))
   (setq _sli_min_value (round __sli_min_value))
   (setq _sli_max_value (round __sli_max_value))
   (setq _sli_delta_round_step (round __sli_delta_round_step))
   (setq _sli_delta_round_upwards (round __sli_delta_round_upwards))
   (setq _country_code (round __country_code))
   (setq _sli_unit_speed (round __sli_unit_speed))
   (setq _tamper_alert_on_frames (round __tamper_alert_on_frames))
   (setq _tamper_alert_off_frames (round __tamper_alert_off_frames))
   (setq _tamper_alert_enable_j1939 (round __tamper_alert_enable_j1939))
   (setq _menu_ticks __menu_ticks)
   (setq _advanced_menu_ticks __advanced_menu_ticks)
   self)
  (:persistent_on_off
   (&optional __persistent_on_off)
   (if __persistent_on_off (setq _persistent_on_off __persistent_on_off)) _persistent_on_off)
  (:volume_level
   (&optional __volume_level)
   (if __volume_level (setq _volume_level __volume_level)) _volume_level)
  (:hmw_level
   (&optional __hmw_level)
   (if __hmw_level (setq _hmw_level __hmw_level)) _hmw_level)
  (:ldw_volume_level
   (&optional __ldw_volume_level)
   (if __ldw_volume_level (setq _ldw_volume_level __ldw_volume_level)) _ldw_volume_level)
  (:hmw_volume_level
   (&optional __hmw_volume_level)
   (if __hmw_volume_level (setq _hmw_volume_level __hmw_volume_level)) _hmw_volume_level)
  (:ldw_level
   (&optional __ldw_level)
   (if __ldw_level (setq _ldw_level __ldw_level)) _ldw_level)
  (:pedestrian_warning_level
   (&optional __pedestrian_warning_level)
   (if __pedestrian_warning_level (setq _pedestrian_warning_level __pedestrian_warning_level)) _pedestrian_warning_level)
  (:sli_warning_level
   (&optional __sli_warning_level)
   (if __sli_warning_level (setq _sli_warning_level __sli_warning_level)) _sli_warning_level)
  (:blinker_reminder_level
   (&optional __blinker_reminder_level)
   (if __blinker_reminder_level (setq _blinker_reminder_level __blinker_reminder_level)) _blinker_reminder_level)
  (:virtual_bumper_level
   (&optional __virtual_bumper_level)
   (if __virtual_bumper_level (setq _virtual_bumper_level __virtual_bumper_level)) _virtual_bumper_level)
  (:hw_repeatable_level
   (&optional __hw_repeatable_level)
   (if __hw_repeatable_level (setq _hw_repeatable_level __hw_repeatable_level)) _hw_repeatable_level)
  (:buzzer_min_volume
   (&optional __buzzer_min_volume)
   (if __buzzer_min_volume (setq _buzzer_min_volume __buzzer_min_volume)) _buzzer_min_volume)
  (:buzzer_max_volume
   (&optional __buzzer_max_volume)
   (if __buzzer_max_volume (setq _buzzer_max_volume __buzzer_max_volume)) _buzzer_max_volume)
  (:buzzer_hmw_min_volume
   (&optional __buzzer_hmw_min_volume)
   (if __buzzer_hmw_min_volume (setq _buzzer_hmw_min_volume __buzzer_hmw_min_volume)) _buzzer_hmw_min_volume)
  (:buzzer_hmw_max_volume
   (&optional __buzzer_hmw_max_volume)
   (if __buzzer_hmw_max_volume (setq _buzzer_hmw_max_volume __buzzer_hmw_max_volume)) _buzzer_hmw_max_volume)
  (:buzzer_ldw_min_volume
   (&optional __buzzer_ldw_min_volume)
   (if __buzzer_ldw_min_volume (setq _buzzer_ldw_min_volume __buzzer_ldw_min_volume)) _buzzer_ldw_min_volume)
  (:buzzer_ldw_max_volume
   (&optional __buzzer_ldw_max_volume)
   (if __buzzer_ldw_max_volume (setq _buzzer_ldw_max_volume __buzzer_ldw_max_volume)) _buzzer_ldw_max_volume)
  (:ewiii_speed_indication
   (&optional __ewiii_speed_indication)
   (if __ewiii_speed_indication (setq _ewiii_speed_indication __ewiii_speed_indication)) _ewiii_speed_indication)
  (:disable_system_off
   (&optional __disable_system_off)
   (if __disable_system_off (setq _disable_system_off __disable_system_off)) _disable_system_off)
  (:calibration_source
   (&optional __calibration_source)
   (if __calibration_source (setq _calibration_source __calibration_source)) _calibration_source)
  (:ldw_min_value
   (&optional __ldw_min_value)
   (if __ldw_min_value (setq _ldw_min_value __ldw_min_value)) _ldw_min_value)
  (:ldw_max_value
   (&optional __ldw_max_value)
   (if __ldw_max_value (setq _ldw_max_value __ldw_max_value)) _ldw_max_value)
  (:ldw_speed
   (&optional __ldw_speed)
   (if __ldw_speed (setq _ldw_speed __ldw_speed)) _ldw_speed)
  (:ped_min_value
   (&optional __ped_min_value)
   (if __ped_min_value (setq _ped_min_value __ped_min_value)) _ped_min_value)
  (:ped_max_value
   (&optional __ped_max_value)
   (if __ped_max_value (setq _ped_max_value __ped_max_value)) _ped_max_value)
  (:speed_for_high_low_beam_control
   (&optional __speed_for_high_low_beam_control)
   (if __speed_for_high_low_beam_control (setq _speed_for_high_low_beam_control __speed_for_high_low_beam_control)) _speed_for_high_low_beam_control)
  (:virtual_bumper_min_value
   (&optional __virtual_bumper_min_value)
   (if __virtual_bumper_min_value (setq _virtual_bumper_min_value __virtual_bumper_min_value)) _virtual_bumper_min_value)
  (:virtual_bumper_max_value
   (&optional __virtual_bumper_max_value)
   (if __virtual_bumper_max_value (setq _virtual_bumper_max_value __virtual_bumper_max_value)) _virtual_bumper_max_value)
  (:blinker_reminder_min_value
   (&optional __blinker_reminder_min_value)
   (if __blinker_reminder_min_value (setq _blinker_reminder_min_value __blinker_reminder_min_value)) _blinker_reminder_min_value)
  (:blinker_reminder_max_value
   (&optional __blinker_reminder_max_value)
   (if __blinker_reminder_max_value (setq _blinker_reminder_max_value __blinker_reminder_max_value)) _blinker_reminder_max_value)
  (:hmw_min_value
   (&optional __hmw_min_value)
   (if __hmw_min_value (setq _hmw_min_value __hmw_min_value)) _hmw_min_value)
  (:hmw_max_value
   (&optional __hmw_max_value)
   (if __hmw_max_value (setq _hmw_max_value __hmw_max_value)) _hmw_max_value)
  (:hmw_repeatable_min_value
   (&optional __hmw_repeatable_min_value)
   (if __hmw_repeatable_min_value (setq _hmw_repeatable_min_value __hmw_repeatable_min_value)) _hmw_repeatable_min_value)
  (:hmw_repeatable_max_value
   (&optional __hmw_repeatable_max_value)
   (if __hmw_repeatable_max_value (setq _hmw_repeatable_max_value __hmw_repeatable_max_value)) _hmw_repeatable_max_value)
  (:sli_min_value
   (&optional __sli_min_value)
   (if __sli_min_value (setq _sli_min_value __sli_min_value)) _sli_min_value)
  (:sli_max_value
   (&optional __sli_max_value)
   (if __sli_max_value (setq _sli_max_value __sli_max_value)) _sli_max_value)
  (:sli_delta_round_step
   (&optional __sli_delta_round_step)
   (if __sli_delta_round_step (setq _sli_delta_round_step __sli_delta_round_step)) _sli_delta_round_step)
  (:sli_delta_round_upwards
   (&optional __sli_delta_round_upwards)
   (if __sli_delta_round_upwards (setq _sli_delta_round_upwards __sli_delta_round_upwards)) _sli_delta_round_upwards)
  (:country_code
   (&optional __country_code)
   (if __country_code (setq _country_code __country_code)) _country_code)
  (:sli_unit_speed
   (&optional __sli_unit_speed)
   (if __sli_unit_speed (setq _sli_unit_speed __sli_unit_speed)) _sli_unit_speed)
  (:tamper_alert_on_frames
   (&optional __tamper_alert_on_frames)
   (if __tamper_alert_on_frames (setq _tamper_alert_on_frames __tamper_alert_on_frames)) _tamper_alert_on_frames)
  (:tamper_alert_off_frames
   (&optional __tamper_alert_off_frames)
   (if __tamper_alert_off_frames (setq _tamper_alert_off_frames __tamper_alert_off_frames)) _tamper_alert_off_frames)
  (:tamper_alert_enable_j1939
   (&optional __tamper_alert_enable_j1939)
   (if __tamper_alert_enable_j1939 (setq _tamper_alert_enable_j1939 __tamper_alert_enable_j1939)) _tamper_alert_enable_j1939)
  (:menu_ticks
   (&optional __menu_ticks)
   (if __menu_ticks (setq _menu_ticks __menu_ticks)) _menu_ticks)
  (:advanced_menu_ticks
   (&optional __advanced_menu_ticks)
   (if __advanced_menu_ticks (setq _advanced_menu_ticks __advanced_menu_ticks)) _advanced_menu_ticks)
  (:serialization-length
   ()
   (+
    ;; uint8 _persistent_on_off
    1
    ;; uint8 _volume_level
    1
    ;; uint8 _hmw_level
    1
    ;; uint8 _ldw_volume_level
    1
    ;; uint8 _hmw_volume_level
    1
    ;; uint8 _ldw_level
    1
    ;; uint8 _pedestrian_warning_level
    1
    ;; uint8 _sli_warning_level
    1
    ;; uint8 _blinker_reminder_level
    1
    ;; uint8 _virtual_bumper_level
    1
    ;; uint8 _hw_repeatable_level
    1
    ;; uint8 _buzzer_min_volume
    1
    ;; uint8 _buzzer_max_volume
    1
    ;; uint8 _buzzer_hmw_min_volume
    1
    ;; uint8 _buzzer_hmw_max_volume
    1
    ;; uint8 _buzzer_ldw_min_volume
    1
    ;; uint8 _buzzer_ldw_max_volume
    1
    ;; uint8 _ewiii_speed_indication
    1
    ;; uint8 _disable_system_off
    1
    ;; uint8 _calibration_source
    1
    ;; uint8 _ldw_min_value
    1
    ;; uint8 _ldw_max_value
    1
    ;; uint8 _ldw_speed
    1
    ;; uint8 _ped_min_value
    1
    ;; uint8 _ped_max_value
    1
    ;; uint8 _speed_for_high_low_beam_control
    1
    ;; uint8 _virtual_bumper_min_value
    1
    ;; uint8 _virtual_bumper_max_value
    1
    ;; uint8 _blinker_reminder_min_value
    1
    ;; uint8 _blinker_reminder_max_value
    1
    ;; uint8 _hmw_min_value
    1
    ;; uint8 _hmw_max_value
    1
    ;; uint8 _hmw_repeatable_min_value
    1
    ;; uint8 _hmw_repeatable_max_value
    1
    ;; uint8 _sli_min_value
    1
    ;; uint8 _sli_max_value
    1
    ;; uint8 _sli_delta_round_step
    1
    ;; uint8 _sli_delta_round_upwards
    1
    ;; uint8 _country_code
    1
    ;; uint8 _sli_unit_speed
    1
    ;; uint8 _tamper_alert_on_frames
    1
    ;; uint8 _tamper_alert_off_frames
    1
    ;; uint8 _tamper_alert_enable_j1939
    1
    ;; bool[16] _menu_ticks
    (* 1    16)
    ;; bool[16] _advanced_menu_ticks
    (* 1    16)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _persistent_on_off
       (write-byte _persistent_on_off s)
     ;; uint8 _volume_level
       (write-byte _volume_level s)
     ;; uint8 _hmw_level
       (write-byte _hmw_level s)
     ;; uint8 _ldw_volume_level
       (write-byte _ldw_volume_level s)
     ;; uint8 _hmw_volume_level
       (write-byte _hmw_volume_level s)
     ;; uint8 _ldw_level
       (write-byte _ldw_level s)
     ;; uint8 _pedestrian_warning_level
       (write-byte _pedestrian_warning_level s)
     ;; uint8 _sli_warning_level
       (write-byte _sli_warning_level s)
     ;; uint8 _blinker_reminder_level
       (write-byte _blinker_reminder_level s)
     ;; uint8 _virtual_bumper_level
       (write-byte _virtual_bumper_level s)
     ;; uint8 _hw_repeatable_level
       (write-byte _hw_repeatable_level s)
     ;; uint8 _buzzer_min_volume
       (write-byte _buzzer_min_volume s)
     ;; uint8 _buzzer_max_volume
       (write-byte _buzzer_max_volume s)
     ;; uint8 _buzzer_hmw_min_volume
       (write-byte _buzzer_hmw_min_volume s)
     ;; uint8 _buzzer_hmw_max_volume
       (write-byte _buzzer_hmw_max_volume s)
     ;; uint8 _buzzer_ldw_min_volume
       (write-byte _buzzer_ldw_min_volume s)
     ;; uint8 _buzzer_ldw_max_volume
       (write-byte _buzzer_ldw_max_volume s)
     ;; uint8 _ewiii_speed_indication
       (write-byte _ewiii_speed_indication s)
     ;; uint8 _disable_system_off
       (write-byte _disable_system_off s)
     ;; uint8 _calibration_source
       (write-byte _calibration_source s)
     ;; uint8 _ldw_min_value
       (write-byte _ldw_min_value s)
     ;; uint8 _ldw_max_value
       (write-byte _ldw_max_value s)
     ;; uint8 _ldw_speed
       (write-byte _ldw_speed s)
     ;; uint8 _ped_min_value
       (write-byte _ped_min_value s)
     ;; uint8 _ped_max_value
       (write-byte _ped_max_value s)
     ;; uint8 _speed_for_high_low_beam_control
       (write-byte _speed_for_high_low_beam_control s)
     ;; uint8 _virtual_bumper_min_value
       (write-byte _virtual_bumper_min_value s)
     ;; uint8 _virtual_bumper_max_value
       (write-byte _virtual_bumper_max_value s)
     ;; uint8 _blinker_reminder_min_value
       (write-byte _blinker_reminder_min_value s)
     ;; uint8 _blinker_reminder_max_value
       (write-byte _blinker_reminder_max_value s)
     ;; uint8 _hmw_min_value
       (write-byte _hmw_min_value s)
     ;; uint8 _hmw_max_value
       (write-byte _hmw_max_value s)
     ;; uint8 _hmw_repeatable_min_value
       (write-byte _hmw_repeatable_min_value s)
     ;; uint8 _hmw_repeatable_max_value
       (write-byte _hmw_repeatable_max_value s)
     ;; uint8 _sli_min_value
       (write-byte _sli_min_value s)
     ;; uint8 _sli_max_value
       (write-byte _sli_max_value s)
     ;; uint8 _sli_delta_round_step
       (write-byte _sli_delta_round_step s)
     ;; uint8 _sli_delta_round_upwards
       (write-byte _sli_delta_round_upwards s)
     ;; uint8 _country_code
       (write-byte _country_code s)
     ;; uint8 _sli_unit_speed
       (write-byte _sli_unit_speed s)
     ;; uint8 _tamper_alert_on_frames
       (write-byte _tamper_alert_on_frames s)
     ;; uint8 _tamper_alert_off_frames
       (write-byte _tamper_alert_off_frames s)
     ;; uint8 _tamper_alert_enable_j1939
       (write-byte _tamper_alert_enable_j1939 s)
     ;; bool[16] _menu_ticks
     (dotimes (i 16)
       (if (elt _menu_ticks i) (write-byte -1 s) (write-byte 0 s))
       )
     ;; bool[16] _advanced_menu_ticks
     (dotimes (i 16)
       (if (elt _advanced_menu_ticks i) (write-byte -1 s) (write-byte 0 s))
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _persistent_on_off
     (setq _persistent_on_off (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _volume_level
     (setq _volume_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hmw_level
     (setq _hmw_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ldw_volume_level
     (setq _ldw_volume_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hmw_volume_level
     (setq _hmw_volume_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ldw_level
     (setq _ldw_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _pedestrian_warning_level
     (setq _pedestrian_warning_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _sli_warning_level
     (setq _sli_warning_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _blinker_reminder_level
     (setq _blinker_reminder_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _virtual_bumper_level
     (setq _virtual_bumper_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hw_repeatable_level
     (setq _hw_repeatable_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _buzzer_min_volume
     (setq _buzzer_min_volume (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _buzzer_max_volume
     (setq _buzzer_max_volume (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _buzzer_hmw_min_volume
     (setq _buzzer_hmw_min_volume (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _buzzer_hmw_max_volume
     (setq _buzzer_hmw_max_volume (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _buzzer_ldw_min_volume
     (setq _buzzer_ldw_min_volume (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _buzzer_ldw_max_volume
     (setq _buzzer_ldw_max_volume (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ewiii_speed_indication
     (setq _ewiii_speed_indication (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _disable_system_off
     (setq _disable_system_off (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _calibration_source
     (setq _calibration_source (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ldw_min_value
     (setq _ldw_min_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ldw_max_value
     (setq _ldw_max_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ldw_speed
     (setq _ldw_speed (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ped_min_value
     (setq _ped_min_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _ped_max_value
     (setq _ped_max_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _speed_for_high_low_beam_control
     (setq _speed_for_high_low_beam_control (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _virtual_bumper_min_value
     (setq _virtual_bumper_min_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _virtual_bumper_max_value
     (setq _virtual_bumper_max_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _blinker_reminder_min_value
     (setq _blinker_reminder_min_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _blinker_reminder_max_value
     (setq _blinker_reminder_max_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hmw_min_value
     (setq _hmw_min_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hmw_max_value
     (setq _hmw_max_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hmw_repeatable_min_value
     (setq _hmw_repeatable_min_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hmw_repeatable_max_value
     (setq _hmw_repeatable_max_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _sli_min_value
     (setq _sli_min_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _sli_max_value
     (setq _sli_max_value (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _sli_delta_round_step
     (setq _sli_delta_round_step (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _sli_delta_round_upwards
     (setq _sli_delta_round_upwards (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _country_code
     (setq _country_code (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _sli_unit_speed
     (setq _sli_unit_speed (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _tamper_alert_on_frames
     (setq _tamper_alert_on_frames (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _tamper_alert_off_frames
     (setq _tamper_alert_off_frames (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _tamper_alert_enable_j1939
     (setq _tamper_alert_enable_j1939 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool[16] _menu_ticks
   (dotimes (i (length _menu_ticks))
     (setf (elt _menu_ticks i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     )
   ;; bool[16] _advanced_menu_ticks
   (dotimes (i (length _advanced_menu_ticks))
     (setf (elt _advanced_menu_ticks i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     )
   ;;
   self)
  )

(setf (get mobileye_msgs::SmartADAS :md5sum-) "2234fe7679b621d841bd2d8b34cf58ad")
(setf (get mobileye_msgs::SmartADAS :datatype-) "mobileye_msgs/SmartADAS")
(setf (get mobileye_msgs::SmartADAS :definition-)
      "uint8 persistent_on_off
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



(provide :mobileye_msgs/SmartADAS "2234fe7679b621d841bd2d8b34cf58ad")


