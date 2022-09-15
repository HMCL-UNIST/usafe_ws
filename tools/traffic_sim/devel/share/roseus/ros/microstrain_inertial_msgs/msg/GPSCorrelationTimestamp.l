;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GPSCorrelationTimestamp)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GPSCorrelationTimestamp (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GPSCORRELATIONTIMESTAMP")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GPSCORRELATIONTIMESTAMP"))

(in-package "ROS")
;;//! \htmlinclude GPSCorrelationTimestamp.msg.html


(intern "*TIMESTAMP_FLAG_PPS_GOOD*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GPSCORRELATIONTIMESTAMP"))
(shadow '*TIMESTAMP_FLAG_PPS_GOOD* (find-package "MICROSTRAIN_INERTIAL_MSGS::GPSCORRELATIONTIMESTAMP"))
(defconstant microstrain_inertial_msgs::GPSCorrelationTimestamp::*TIMESTAMP_FLAG_PPS_GOOD* 1)
(intern "*TIMESTAMP_FLAG_GPS_REFRESH*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GPSCORRELATIONTIMESTAMP"))
(shadow '*TIMESTAMP_FLAG_GPS_REFRESH* (find-package "MICROSTRAIN_INERTIAL_MSGS::GPSCORRELATIONTIMESTAMP"))
(defconstant microstrain_inertial_msgs::GPSCorrelationTimestamp::*TIMESTAMP_FLAG_GPS_REFRESH* 2)
(intern "*TIMESTAMP_FLAG_GPS_INITALIZED*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GPSCORRELATIONTIMESTAMP"))
(shadow '*TIMESTAMP_FLAG_GPS_INITALIZED* (find-package "MICROSTRAIN_INERTIAL_MSGS::GPSCORRELATIONTIMESTAMP"))
(defconstant microstrain_inertial_msgs::GPSCorrelationTimestamp::*TIMESTAMP_FLAG_GPS_INITALIZED* 4)
(defclass microstrain_inertial_msgs::GPSCorrelationTimestamp
  :super ros::object
  :slots (_gps_tow _gps_week_number _timestamp_flags ))

(defmethod microstrain_inertial_msgs::GPSCorrelationTimestamp
  (:init
   (&key
    ((:gps_tow __gps_tow) 0.0)
    ((:gps_week_number __gps_week_number) 0)
    ((:timestamp_flags __timestamp_flags) 0)
    )
   (send-super :init)
   (setq _gps_tow (float __gps_tow))
   (setq _gps_week_number (round __gps_week_number))
   (setq _timestamp_flags (round __timestamp_flags))
   self)
  (:gps_tow
   (&optional __gps_tow)
   (if __gps_tow (setq _gps_tow __gps_tow)) _gps_tow)
  (:gps_week_number
   (&optional __gps_week_number)
   (if __gps_week_number (setq _gps_week_number __gps_week_number)) _gps_week_number)
  (:timestamp_flags
   (&optional __timestamp_flags)
   (if __timestamp_flags (setq _timestamp_flags __timestamp_flags)) _timestamp_flags)
  (:serialization-length
   ()
   (+
    ;; float64 _gps_tow
    8
    ;; uint16 _gps_week_number
    2
    ;; uint16 _timestamp_flags
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _gps_tow
       (sys::poke _gps_tow (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint16 _gps_week_number
       (write-word _gps_week_number s)
     ;; uint16 _timestamp_flags
       (write-word _timestamp_flags s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _gps_tow
     (setq _gps_tow (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint16 _gps_week_number
     (setq _gps_week_number (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _timestamp_flags
     (setq _timestamp_flags (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::GPSCorrelationTimestamp :md5sum-) "e4273ef053cace34fe47537c314897d4")
(setf (get microstrain_inertial_msgs::GPSCorrelationTimestamp :datatype-) "microstrain_inertial_msgs/GPSCorrelationTimestamp")
(setf (get microstrain_inertial_msgs::GPSCorrelationTimestamp :definition-)
      "float64 gps_tow
uint16 gps_week_number
uint16 timestamp_flags
uint16 TIMESTAMP_FLAG_PPS_GOOD      = 1  #0b001
uint16 TIMESTAMP_FLAG_GPS_REFRESH   = 2  #0b010
uint16 TIMESTAMP_FLAG_GPS_INITALIZED= 4  #0b100

")



(provide :microstrain_inertial_msgs/GPSCorrelationTimestamp "e4273ef053cace34fe47537c314897d4")


