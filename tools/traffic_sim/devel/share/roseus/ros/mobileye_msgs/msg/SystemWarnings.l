;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::SystemWarnings)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'SystemWarnings (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::SYSTEMWARNINGS")
  (make-package "MOBILEYE_MSGS::SYSTEMWARNINGS"))

(in-package "ROS")
;;//! \htmlinclude SystemWarnings.msg.html


(defclass mobileye_msgs::SystemWarnings
  :super ros::object
  :slots (_sound_type _peds_in_dz _peds_fcw _time_indicator _error_valid _error_code _zero_speed _headway_valid _headway_measurement _ldw_off _left_ldw_on _right_ldw_on _fcw_on _maintenance _failsafe _tsr_enabled _hw_repeatable_enabled _headway_warning_level _tsr_warning_level _tamper_alert ))

(defmethod mobileye_msgs::SystemWarnings
  (:init
   (&key
    ((:sound_type __sound_type) 0)
    ((:peds_in_dz __peds_in_dz) nil)
    ((:peds_fcw __peds_fcw) nil)
    ((:time_indicator __time_indicator) 0)
    ((:error_valid __error_valid) nil)
    ((:error_code __error_code) 0)
    ((:zero_speed __zero_speed) nil)
    ((:headway_valid __headway_valid) nil)
    ((:headway_measurement __headway_measurement) 0.0)
    ((:ldw_off __ldw_off) nil)
    ((:left_ldw_on __left_ldw_on) nil)
    ((:right_ldw_on __right_ldw_on) nil)
    ((:fcw_on __fcw_on) nil)
    ((:maintenance __maintenance) nil)
    ((:failsafe __failsafe) nil)
    ((:tsr_enabled __tsr_enabled) nil)
    ((:hw_repeatable_enabled __hw_repeatable_enabled) nil)
    ((:headway_warning_level __headway_warning_level) 0)
    ((:tsr_warning_level __tsr_warning_level) 0)
    ((:tamper_alert __tamper_alert) nil)
    )
   (send-super :init)
   (setq _sound_type (round __sound_type))
   (setq _peds_in_dz __peds_in_dz)
   (setq _peds_fcw __peds_fcw)
   (setq _time_indicator (round __time_indicator))
   (setq _error_valid __error_valid)
   (setq _error_code (round __error_code))
   (setq _zero_speed __zero_speed)
   (setq _headway_valid __headway_valid)
   (setq _headway_measurement (float __headway_measurement))
   (setq _ldw_off __ldw_off)
   (setq _left_ldw_on __left_ldw_on)
   (setq _right_ldw_on __right_ldw_on)
   (setq _fcw_on __fcw_on)
   (setq _maintenance __maintenance)
   (setq _failsafe __failsafe)
   (setq _tsr_enabled __tsr_enabled)
   (setq _hw_repeatable_enabled __hw_repeatable_enabled)
   (setq _headway_warning_level (round __headway_warning_level))
   (setq _tsr_warning_level (round __tsr_warning_level))
   (setq _tamper_alert __tamper_alert)
   self)
  (:sound_type
   (&optional __sound_type)
   (if __sound_type (setq _sound_type __sound_type)) _sound_type)
  (:peds_in_dz
   (&optional __peds_in_dz)
   (if __peds_in_dz (setq _peds_in_dz __peds_in_dz)) _peds_in_dz)
  (:peds_fcw
   (&optional __peds_fcw)
   (if __peds_fcw (setq _peds_fcw __peds_fcw)) _peds_fcw)
  (:time_indicator
   (&optional __time_indicator)
   (if __time_indicator (setq _time_indicator __time_indicator)) _time_indicator)
  (:error_valid
   (&optional __error_valid)
   (if __error_valid (setq _error_valid __error_valid)) _error_valid)
  (:error_code
   (&optional __error_code)
   (if __error_code (setq _error_code __error_code)) _error_code)
  (:zero_speed
   (&optional __zero_speed)
   (if __zero_speed (setq _zero_speed __zero_speed)) _zero_speed)
  (:headway_valid
   (&optional __headway_valid)
   (if __headway_valid (setq _headway_valid __headway_valid)) _headway_valid)
  (:headway_measurement
   (&optional __headway_measurement)
   (if __headway_measurement (setq _headway_measurement __headway_measurement)) _headway_measurement)
  (:ldw_off
   (&optional __ldw_off)
   (if __ldw_off (setq _ldw_off __ldw_off)) _ldw_off)
  (:left_ldw_on
   (&optional __left_ldw_on)
   (if __left_ldw_on (setq _left_ldw_on __left_ldw_on)) _left_ldw_on)
  (:right_ldw_on
   (&optional __right_ldw_on)
   (if __right_ldw_on (setq _right_ldw_on __right_ldw_on)) _right_ldw_on)
  (:fcw_on
   (&optional __fcw_on)
   (if __fcw_on (setq _fcw_on __fcw_on)) _fcw_on)
  (:maintenance
   (&optional __maintenance)
   (if __maintenance (setq _maintenance __maintenance)) _maintenance)
  (:failsafe
   (&optional __failsafe)
   (if __failsafe (setq _failsafe __failsafe)) _failsafe)
  (:tsr_enabled
   (&optional __tsr_enabled)
   (if __tsr_enabled (setq _tsr_enabled __tsr_enabled)) _tsr_enabled)
  (:hw_repeatable_enabled
   (&optional __hw_repeatable_enabled)
   (if __hw_repeatable_enabled (setq _hw_repeatable_enabled __hw_repeatable_enabled)) _hw_repeatable_enabled)
  (:headway_warning_level
   (&optional __headway_warning_level)
   (if __headway_warning_level (setq _headway_warning_level __headway_warning_level)) _headway_warning_level)
  (:tsr_warning_level
   (&optional __tsr_warning_level)
   (if __tsr_warning_level (setq _tsr_warning_level __tsr_warning_level)) _tsr_warning_level)
  (:tamper_alert
   (&optional __tamper_alert)
   (if __tamper_alert (setq _tamper_alert __tamper_alert)) _tamper_alert)
  (:serialization-length
   ()
   (+
    ;; uint8 _sound_type
    1
    ;; bool _peds_in_dz
    1
    ;; bool _peds_fcw
    1
    ;; uint8 _time_indicator
    1
    ;; bool _error_valid
    1
    ;; uint8 _error_code
    1
    ;; bool _zero_speed
    1
    ;; bool _headway_valid
    1
    ;; float32 _headway_measurement
    4
    ;; bool _ldw_off
    1
    ;; bool _left_ldw_on
    1
    ;; bool _right_ldw_on
    1
    ;; bool _fcw_on
    1
    ;; bool _maintenance
    1
    ;; bool _failsafe
    1
    ;; bool _tsr_enabled
    1
    ;; bool _hw_repeatable_enabled
    1
    ;; uint8 _headway_warning_level
    1
    ;; uint8 _tsr_warning_level
    1
    ;; bool _tamper_alert
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _sound_type
       (write-byte _sound_type s)
     ;; bool _peds_in_dz
       (if _peds_in_dz (write-byte -1 s) (write-byte 0 s))
     ;; bool _peds_fcw
       (if _peds_fcw (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _time_indicator
       (write-byte _time_indicator s)
     ;; bool _error_valid
       (if _error_valid (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _error_code
       (write-byte _error_code s)
     ;; bool _zero_speed
       (if _zero_speed (write-byte -1 s) (write-byte 0 s))
     ;; bool _headway_valid
       (if _headway_valid (write-byte -1 s) (write-byte 0 s))
     ;; float32 _headway_measurement
       (sys::poke _headway_measurement (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _ldw_off
       (if _ldw_off (write-byte -1 s) (write-byte 0 s))
     ;; bool _left_ldw_on
       (if _left_ldw_on (write-byte -1 s) (write-byte 0 s))
     ;; bool _right_ldw_on
       (if _right_ldw_on (write-byte -1 s) (write-byte 0 s))
     ;; bool _fcw_on
       (if _fcw_on (write-byte -1 s) (write-byte 0 s))
     ;; bool _maintenance
       (if _maintenance (write-byte -1 s) (write-byte 0 s))
     ;; bool _failsafe
       (if _failsafe (write-byte -1 s) (write-byte 0 s))
     ;; bool _tsr_enabled
       (if _tsr_enabled (write-byte -1 s) (write-byte 0 s))
     ;; bool _hw_repeatable_enabled
       (if _hw_repeatable_enabled (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _headway_warning_level
       (write-byte _headway_warning_level s)
     ;; uint8 _tsr_warning_level
       (write-byte _tsr_warning_level s)
     ;; bool _tamper_alert
       (if _tamper_alert (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _sound_type
     (setq _sound_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _peds_in_dz
     (setq _peds_in_dz (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _peds_fcw
     (setq _peds_fcw (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _time_indicator
     (setq _time_indicator (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _error_valid
     (setq _error_valid (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _error_code
     (setq _error_code (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _zero_speed
     (setq _zero_speed (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _headway_valid
     (setq _headway_valid (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _headway_measurement
     (setq _headway_measurement (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _ldw_off
     (setq _ldw_off (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _left_ldw_on
     (setq _left_ldw_on (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _right_ldw_on
     (setq _right_ldw_on (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _fcw_on
     (setq _fcw_on (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _maintenance
     (setq _maintenance (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _failsafe
     (setq _failsafe (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _tsr_enabled
     (setq _tsr_enabled (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _hw_repeatable_enabled
     (setq _hw_repeatable_enabled (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _headway_warning_level
     (setq _headway_warning_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _tsr_warning_level
     (setq _tsr_warning_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _tamper_alert
     (setq _tamper_alert (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::SystemWarnings :md5sum-) "13b6bac628f7b8055c48f3c1bf2dfa99")
(setf (get mobileye_msgs::SystemWarnings :datatype-) "mobileye_msgs/SystemWarnings")
(setf (get mobileye_msgs::SystemWarnings :definition-)
      "uint8 sound_type
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



(provide :mobileye_msgs/SystemWarnings "13b6bac628f7b8055c48f3c1bf2dfa99")


