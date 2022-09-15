;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::ExternalHeadingUpdate)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'ExternalHeadingUpdate (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATERESPONSE"))

(in-package "ROS")





(intern "*HEADING_TYPE_TRUE*" (find-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATEREQUEST"))
(shadow '*HEADING_TYPE_TRUE* (find-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATEREQUEST"))
(defconstant microstrain_inertial_msgs::ExternalHeadingUpdateRequest::*HEADING_TYPE_TRUE* 1)
(intern "*HEADING_TYPE_MAGNETIC*" (find-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATEREQUEST"))
(shadow '*HEADING_TYPE_MAGNETIC* (find-package "MICROSTRAIN_INERTIAL_MSGS::EXTERNALHEADINGUPDATEREQUEST"))
(defconstant microstrain_inertial_msgs::ExternalHeadingUpdateRequest::*HEADING_TYPE_MAGNETIC* 2)
(defclass microstrain_inertial_msgs::ExternalHeadingUpdateRequest
  :super ros::object
  :slots (_gps_tow _gps_week_number _heading_rad _heading_1sigma_rad _heading_type _use_time ))

(defmethod microstrain_inertial_msgs::ExternalHeadingUpdateRequest
  (:init
   (&key
    ((:gps_tow __gps_tow) 0.0)
    ((:gps_week_number __gps_week_number) 0)
    ((:heading_rad __heading_rad) 0.0)
    ((:heading_1sigma_rad __heading_1sigma_rad) 0.0)
    ((:heading_type __heading_type) 0)
    ((:use_time __use_time) nil)
    )
   (send-super :init)
   (setq _gps_tow (float __gps_tow))
   (setq _gps_week_number (round __gps_week_number))
   (setq _heading_rad (float __heading_rad))
   (setq _heading_1sigma_rad (float __heading_1sigma_rad))
   (setq _heading_type (round __heading_type))
   (setq _use_time __use_time)
   self)
  (:gps_tow
   (&optional __gps_tow)
   (if __gps_tow (setq _gps_tow __gps_tow)) _gps_tow)
  (:gps_week_number
   (&optional __gps_week_number)
   (if __gps_week_number (setq _gps_week_number __gps_week_number)) _gps_week_number)
  (:heading_rad
   (&optional __heading_rad)
   (if __heading_rad (setq _heading_rad __heading_rad)) _heading_rad)
  (:heading_1sigma_rad
   (&optional __heading_1sigma_rad)
   (if __heading_1sigma_rad (setq _heading_1sigma_rad __heading_1sigma_rad)) _heading_1sigma_rad)
  (:heading_type
   (&optional __heading_type)
   (if __heading_type (setq _heading_type __heading_type)) _heading_type)
  (:use_time
   (&optional __use_time)
   (if __use_time (setq _use_time __use_time)) _use_time)
  (:serialization-length
   ()
   (+
    ;; float64 _gps_tow
    8
    ;; uint16 _gps_week_number
    2
    ;; float32 _heading_rad
    4
    ;; float32 _heading_1sigma_rad
    4
    ;; uint16 _heading_type
    2
    ;; bool _use_time
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _gps_tow
       (sys::poke _gps_tow (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint16 _gps_week_number
       (write-word _gps_week_number s)
     ;; float32 _heading_rad
       (sys::poke _heading_rad (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading_1sigma_rad
       (sys::poke _heading_1sigma_rad (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint16 _heading_type
       (write-word _heading_type s)
     ;; bool _use_time
       (if _use_time (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _gps_tow
     (setq _gps_tow (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint16 _gps_week_number
     (setq _gps_week_number (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float32 _heading_rad
     (setq _heading_rad (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading_1sigma_rad
     (setq _heading_1sigma_rad (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint16 _heading_type
     (setq _heading_type (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; bool _use_time
     (setq _use_time (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::ExternalHeadingUpdateResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::ExternalHeadingUpdateResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::ExternalHeadingUpdate
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::ExternalHeadingUpdate :md5sum-) "c947f180cef8662c7c56b8c41afcba62")
(setf (get microstrain_inertial_msgs::ExternalHeadingUpdate :datatype-) "microstrain_inertial_msgs/ExternalHeadingUpdate")
(setf (get microstrain_inertial_msgs::ExternalHeadingUpdate :request) microstrain_inertial_msgs::ExternalHeadingUpdateRequest)
(setf (get microstrain_inertial_msgs::ExternalHeadingUpdate :response) microstrain_inertial_msgs::ExternalHeadingUpdateResponse)

(defmethod microstrain_inertial_msgs::ExternalHeadingUpdateRequest
  (:response () (instance microstrain_inertial_msgs::ExternalHeadingUpdateResponse :init)))

(setf (get microstrain_inertial_msgs::ExternalHeadingUpdateRequest :md5sum-) "c947f180cef8662c7c56b8c41afcba62")
(setf (get microstrain_inertial_msgs::ExternalHeadingUpdateRequest :datatype-) "microstrain_inertial_msgs/ExternalHeadingUpdateRequest")
(setf (get microstrain_inertial_msgs::ExternalHeadingUpdateRequest :definition-)
      "float64 gps_tow
uint16  gps_week_number
float32 heading_rad
float32 heading_1sigma_rad
uint16  heading_type
bool    use_time
uint16 HEADING_TYPE_TRUE      = 1  
uint16 HEADING_TYPE_MAGNETIC  = 2  
---
bool success

")

(setf (get microstrain_inertial_msgs::ExternalHeadingUpdateResponse :md5sum-) "c947f180cef8662c7c56b8c41afcba62")
(setf (get microstrain_inertial_msgs::ExternalHeadingUpdateResponse :datatype-) "microstrain_inertial_msgs/ExternalHeadingUpdateResponse")
(setf (get microstrain_inertial_msgs::ExternalHeadingUpdateResponse :definition-)
      "float64 gps_tow
uint16  gps_week_number
float32 heading_rad
float32 heading_1sigma_rad
uint16  heading_type
bool    use_time
uint16 HEADING_TYPE_TRUE      = 1  
uint16 HEADING_TYPE_MAGNETIC  = 2  
---
bool success

")



(provide :microstrain_inertial_msgs/ExternalHeadingUpdate "c947f180cef8662c7c56b8c41afcba62")


