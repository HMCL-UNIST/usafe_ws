;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GNSSAidingStatus)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GNSSAidingStatus (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSAIDINGSTATUS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GNSSAIDINGSTATUS"))

(in-package "ROS")
;;//! \htmlinclude GNSSAidingStatus.msg.html


(defclass microstrain_inertial_msgs::GNSSAidingStatus
  :super ros::object
  :slots (_gps_tow _has_position_fix _tight_coupling _differential_corrections _integer_fix _using_gps _using_glonass _using_galileo _using_beidou ))

(defmethod microstrain_inertial_msgs::GNSSAidingStatus
  (:init
   (&key
    ((:gps_tow __gps_tow) 0.0)
    ((:has_position_fix __has_position_fix) nil)
    ((:tight_coupling __tight_coupling) nil)
    ((:differential_corrections __differential_corrections) nil)
    ((:integer_fix __integer_fix) nil)
    ((:using_gps __using_gps) nil)
    ((:using_glonass __using_glonass) nil)
    ((:using_galileo __using_galileo) nil)
    ((:using_beidou __using_beidou) nil)
    )
   (send-super :init)
   (setq _gps_tow (float __gps_tow))
   (setq _has_position_fix __has_position_fix)
   (setq _tight_coupling __tight_coupling)
   (setq _differential_corrections __differential_corrections)
   (setq _integer_fix __integer_fix)
   (setq _using_gps __using_gps)
   (setq _using_glonass __using_glonass)
   (setq _using_galileo __using_galileo)
   (setq _using_beidou __using_beidou)
   self)
  (:gps_tow
   (&optional __gps_tow)
   (if __gps_tow (setq _gps_tow __gps_tow)) _gps_tow)
  (:has_position_fix
   (&optional __has_position_fix)
   (if __has_position_fix (setq _has_position_fix __has_position_fix)) _has_position_fix)
  (:tight_coupling
   (&optional __tight_coupling)
   (if __tight_coupling (setq _tight_coupling __tight_coupling)) _tight_coupling)
  (:differential_corrections
   (&optional __differential_corrections)
   (if __differential_corrections (setq _differential_corrections __differential_corrections)) _differential_corrections)
  (:integer_fix
   (&optional __integer_fix)
   (if __integer_fix (setq _integer_fix __integer_fix)) _integer_fix)
  (:using_gps
   (&optional __using_gps)
   (if __using_gps (setq _using_gps __using_gps)) _using_gps)
  (:using_glonass
   (&optional __using_glonass)
   (if __using_glonass (setq _using_glonass __using_glonass)) _using_glonass)
  (:using_galileo
   (&optional __using_galileo)
   (if __using_galileo (setq _using_galileo __using_galileo)) _using_galileo)
  (:using_beidou
   (&optional __using_beidou)
   (if __using_beidou (setq _using_beidou __using_beidou)) _using_beidou)
  (:serialization-length
   ()
   (+
    ;; float64 _gps_tow
    8
    ;; bool _has_position_fix
    1
    ;; bool _tight_coupling
    1
    ;; bool _differential_corrections
    1
    ;; bool _integer_fix
    1
    ;; bool _using_gps
    1
    ;; bool _using_glonass
    1
    ;; bool _using_galileo
    1
    ;; bool _using_beidou
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _gps_tow
       (sys::poke _gps_tow (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; bool _has_position_fix
       (if _has_position_fix (write-byte -1 s) (write-byte 0 s))
     ;; bool _tight_coupling
       (if _tight_coupling (write-byte -1 s) (write-byte 0 s))
     ;; bool _differential_corrections
       (if _differential_corrections (write-byte -1 s) (write-byte 0 s))
     ;; bool _integer_fix
       (if _integer_fix (write-byte -1 s) (write-byte 0 s))
     ;; bool _using_gps
       (if _using_gps (write-byte -1 s) (write-byte 0 s))
     ;; bool _using_glonass
       (if _using_glonass (write-byte -1 s) (write-byte 0 s))
     ;; bool _using_galileo
       (if _using_galileo (write-byte -1 s) (write-byte 0 s))
     ;; bool _using_beidou
       (if _using_beidou (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _gps_tow
     (setq _gps_tow (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; bool _has_position_fix
     (setq _has_position_fix (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _tight_coupling
     (setq _tight_coupling (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _differential_corrections
     (setq _differential_corrections (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _integer_fix
     (setq _integer_fix (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _using_gps
     (setq _using_gps (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _using_glonass
     (setq _using_glonass (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _using_galileo
     (setq _using_galileo (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _using_beidou
     (setq _using_beidou (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::GNSSAidingStatus :md5sum-) "93a07537312a9e616123b06cec1efdf6")
(setf (get microstrain_inertial_msgs::GNSSAidingStatus :datatype-) "microstrain_inertial_msgs/GNSSAidingStatus")
(setf (get microstrain_inertial_msgs::GNSSAidingStatus :definition-)
      "float64 gps_tow
bool    has_position_fix
bool    tight_coupling
bool    differential_corrections
bool    integer_fix
bool    using_gps 
bool    using_glonass
bool    using_galileo
bool    using_beidou
")



(provide :microstrain_inertial_msgs/GNSSAidingStatus "93a07537312a9e616123b06cec1efdf6")


