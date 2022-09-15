;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::CarInfo)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'CarInfo (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::CARINFO")
  (make-package "MOBILEYE_MSGS::CARINFO"))

(in-package "ROS")
;;//! \htmlinclude CarInfo.msg.html


(defclass mobileye_msgs::CarInfo
  :super ros::object
  :slots (_high_beam _low_beam _wipers _right_signal _left_signal _brake_signal _wipers_available _low_beam_available _high_beam_available _right_blink_available _left_blink_available _brake_available _speed_available _speed _shield_plus_settings ))

(defmethod mobileye_msgs::CarInfo
  (:init
   (&key
    ((:high_beam __high_beam) nil)
    ((:low_beam __low_beam) nil)
    ((:wipers __wipers) nil)
    ((:right_signal __right_signal) nil)
    ((:left_signal __left_signal) nil)
    ((:brake_signal __brake_signal) nil)
    ((:wipers_available __wipers_available) nil)
    ((:low_beam_available __low_beam_available) nil)
    ((:high_beam_available __high_beam_available) nil)
    ((:right_blink_available __right_blink_available) nil)
    ((:left_blink_available __left_blink_available) nil)
    ((:brake_available __brake_available) nil)
    ((:speed_available __speed_available) nil)
    ((:speed __speed) 0)
    ((:shield_plus_settings __shield_plus_settings) 0)
    )
   (send-super :init)
   (setq _high_beam __high_beam)
   (setq _low_beam __low_beam)
   (setq _wipers __wipers)
   (setq _right_signal __right_signal)
   (setq _left_signal __left_signal)
   (setq _brake_signal __brake_signal)
   (setq _wipers_available __wipers_available)
   (setq _low_beam_available __low_beam_available)
   (setq _high_beam_available __high_beam_available)
   (setq _right_blink_available __right_blink_available)
   (setq _left_blink_available __left_blink_available)
   (setq _brake_available __brake_available)
   (setq _speed_available __speed_available)
   (setq _speed (round __speed))
   (setq _shield_plus_settings (round __shield_plus_settings))
   self)
  (:high_beam
   (&optional __high_beam)
   (if __high_beam (setq _high_beam __high_beam)) _high_beam)
  (:low_beam
   (&optional __low_beam)
   (if __low_beam (setq _low_beam __low_beam)) _low_beam)
  (:wipers
   (&optional __wipers)
   (if __wipers (setq _wipers __wipers)) _wipers)
  (:right_signal
   (&optional __right_signal)
   (if __right_signal (setq _right_signal __right_signal)) _right_signal)
  (:left_signal
   (&optional __left_signal)
   (if __left_signal (setq _left_signal __left_signal)) _left_signal)
  (:brake_signal
   (&optional __brake_signal)
   (if __brake_signal (setq _brake_signal __brake_signal)) _brake_signal)
  (:wipers_available
   (&optional __wipers_available)
   (if __wipers_available (setq _wipers_available __wipers_available)) _wipers_available)
  (:low_beam_available
   (&optional __low_beam_available)
   (if __low_beam_available (setq _low_beam_available __low_beam_available)) _low_beam_available)
  (:high_beam_available
   (&optional __high_beam_available)
   (if __high_beam_available (setq _high_beam_available __high_beam_available)) _high_beam_available)
  (:right_blink_available
   (&optional __right_blink_available)
   (if __right_blink_available (setq _right_blink_available __right_blink_available)) _right_blink_available)
  (:left_blink_available
   (&optional __left_blink_available)
   (if __left_blink_available (setq _left_blink_available __left_blink_available)) _left_blink_available)
  (:brake_available
   (&optional __brake_available)
   (if __brake_available (setq _brake_available __brake_available)) _brake_available)
  (:speed_available
   (&optional __speed_available)
   (if __speed_available (setq _speed_available __speed_available)) _speed_available)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:shield_plus_settings
   (&optional __shield_plus_settings)
   (if __shield_plus_settings (setq _shield_plus_settings __shield_plus_settings)) _shield_plus_settings)
  (:serialization-length
   ()
   (+
    ;; bool _high_beam
    1
    ;; bool _low_beam
    1
    ;; bool _wipers
    1
    ;; bool _right_signal
    1
    ;; bool _left_signal
    1
    ;; bool _brake_signal
    1
    ;; bool _wipers_available
    1
    ;; bool _low_beam_available
    1
    ;; bool _high_beam_available
    1
    ;; bool _right_blink_available
    1
    ;; bool _left_blink_available
    1
    ;; bool _brake_available
    1
    ;; bool _speed_available
    1
    ;; uint8 _speed
    1
    ;; uint8 _shield_plus_settings
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _high_beam
       (if _high_beam (write-byte -1 s) (write-byte 0 s))
     ;; bool _low_beam
       (if _low_beam (write-byte -1 s) (write-byte 0 s))
     ;; bool _wipers
       (if _wipers (write-byte -1 s) (write-byte 0 s))
     ;; bool _right_signal
       (if _right_signal (write-byte -1 s) (write-byte 0 s))
     ;; bool _left_signal
       (if _left_signal (write-byte -1 s) (write-byte 0 s))
     ;; bool _brake_signal
       (if _brake_signal (write-byte -1 s) (write-byte 0 s))
     ;; bool _wipers_available
       (if _wipers_available (write-byte -1 s) (write-byte 0 s))
     ;; bool _low_beam_available
       (if _low_beam_available (write-byte -1 s) (write-byte 0 s))
     ;; bool _high_beam_available
       (if _high_beam_available (write-byte -1 s) (write-byte 0 s))
     ;; bool _right_blink_available
       (if _right_blink_available (write-byte -1 s) (write-byte 0 s))
     ;; bool _left_blink_available
       (if _left_blink_available (write-byte -1 s) (write-byte 0 s))
     ;; bool _brake_available
       (if _brake_available (write-byte -1 s) (write-byte 0 s))
     ;; bool _speed_available
       (if _speed_available (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _speed
       (write-byte _speed s)
     ;; uint8 _shield_plus_settings
       (write-byte _shield_plus_settings s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _high_beam
     (setq _high_beam (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _low_beam
     (setq _low_beam (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _wipers
     (setq _wipers (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _right_signal
     (setq _right_signal (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _left_signal
     (setq _left_signal (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _brake_signal
     (setq _brake_signal (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _wipers_available
     (setq _wipers_available (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _low_beam_available
     (setq _low_beam_available (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _high_beam_available
     (setq _high_beam_available (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _right_blink_available
     (setq _right_blink_available (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _left_blink_available
     (setq _left_blink_available (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _brake_available
     (setq _brake_available (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _speed_available
     (setq _speed_available (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _speed
     (setq _speed (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _shield_plus_settings
     (setq _shield_plus_settings (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::CarInfo :md5sum-) "50aff2fafecf310fa3fc9bcf4c9a5c85")
(setf (get mobileye_msgs::CarInfo :datatype-) "mobileye_msgs/CarInfo")
(setf (get mobileye_msgs::CarInfo :definition-)
      "bool high_beam
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
")



(provide :mobileye_msgs/CarInfo "50aff2fafecf310fa3fc9bcf4c9a5c85")


