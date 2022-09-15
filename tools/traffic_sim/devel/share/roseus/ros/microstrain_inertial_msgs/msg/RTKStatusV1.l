;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::RTKStatusV1)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'RTKStatusV1 (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUSV1")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::RTKSTATUSV1"))

(in-package "ROS")
;;//! \htmlinclude RTKStatusV1.msg.html


(defclass microstrain_inertial_msgs::RTKStatusV1
  :super ros::object
  :slots (_gps_tow _gps_week _epoch_status _dongle_version _dongle_controller_state _dongle_platform_state _dongle_controller_status _dongle_platform_status _dongle_reset_reason _dongle_signal_quality _gps_correction_latency _glonass_correction_latency _galileo_correction_latency _beidou_correction_latency _raw_status_flags ))

(defmethod microstrain_inertial_msgs::RTKStatusV1
  (:init
   (&key
    ((:gps_tow __gps_tow) 0.0)
    ((:gps_week __gps_week) 0)
    ((:epoch_status __epoch_status) 0)
    ((:dongle_version __dongle_version) 0)
    ((:dongle_controller_state __dongle_controller_state) 0)
    ((:dongle_platform_state __dongle_platform_state) 0)
    ((:dongle_controller_status __dongle_controller_status) 0)
    ((:dongle_platform_status __dongle_platform_status) 0)
    ((:dongle_reset_reason __dongle_reset_reason) 0)
    ((:dongle_signal_quality __dongle_signal_quality) 0)
    ((:gps_correction_latency __gps_correction_latency) 0.0)
    ((:glonass_correction_latency __glonass_correction_latency) 0.0)
    ((:galileo_correction_latency __galileo_correction_latency) 0.0)
    ((:beidou_correction_latency __beidou_correction_latency) 0.0)
    ((:raw_status_flags __raw_status_flags) 0)
    )
   (send-super :init)
   (setq _gps_tow (float __gps_tow))
   (setq _gps_week (round __gps_week))
   (setq _epoch_status (round __epoch_status))
   (setq _dongle_version (round __dongle_version))
   (setq _dongle_controller_state (round __dongle_controller_state))
   (setq _dongle_platform_state (round __dongle_platform_state))
   (setq _dongle_controller_status (round __dongle_controller_status))
   (setq _dongle_platform_status (round __dongle_platform_status))
   (setq _dongle_reset_reason (round __dongle_reset_reason))
   (setq _dongle_signal_quality (round __dongle_signal_quality))
   (setq _gps_correction_latency (float __gps_correction_latency))
   (setq _glonass_correction_latency (float __glonass_correction_latency))
   (setq _galileo_correction_latency (float __galileo_correction_latency))
   (setq _beidou_correction_latency (float __beidou_correction_latency))
   (setq _raw_status_flags (round __raw_status_flags))
   self)
  (:gps_tow
   (&optional __gps_tow)
   (if __gps_tow (setq _gps_tow __gps_tow)) _gps_tow)
  (:gps_week
   (&optional __gps_week)
   (if __gps_week (setq _gps_week __gps_week)) _gps_week)
  (:epoch_status
   (&optional __epoch_status)
   (if __epoch_status (setq _epoch_status __epoch_status)) _epoch_status)
  (:dongle_version
   (&optional __dongle_version)
   (if __dongle_version (setq _dongle_version __dongle_version)) _dongle_version)
  (:dongle_controller_state
   (&optional __dongle_controller_state)
   (if __dongle_controller_state (setq _dongle_controller_state __dongle_controller_state)) _dongle_controller_state)
  (:dongle_platform_state
   (&optional __dongle_platform_state)
   (if __dongle_platform_state (setq _dongle_platform_state __dongle_platform_state)) _dongle_platform_state)
  (:dongle_controller_status
   (&optional __dongle_controller_status)
   (if __dongle_controller_status (setq _dongle_controller_status __dongle_controller_status)) _dongle_controller_status)
  (:dongle_platform_status
   (&optional __dongle_platform_status)
   (if __dongle_platform_status (setq _dongle_platform_status __dongle_platform_status)) _dongle_platform_status)
  (:dongle_reset_reason
   (&optional __dongle_reset_reason)
   (if __dongle_reset_reason (setq _dongle_reset_reason __dongle_reset_reason)) _dongle_reset_reason)
  (:dongle_signal_quality
   (&optional __dongle_signal_quality)
   (if __dongle_signal_quality (setq _dongle_signal_quality __dongle_signal_quality)) _dongle_signal_quality)
  (:gps_correction_latency
   (&optional __gps_correction_latency)
   (if __gps_correction_latency (setq _gps_correction_latency __gps_correction_latency)) _gps_correction_latency)
  (:glonass_correction_latency
   (&optional __glonass_correction_latency)
   (if __glonass_correction_latency (setq _glonass_correction_latency __glonass_correction_latency)) _glonass_correction_latency)
  (:galileo_correction_latency
   (&optional __galileo_correction_latency)
   (if __galileo_correction_latency (setq _galileo_correction_latency __galileo_correction_latency)) _galileo_correction_latency)
  (:beidou_correction_latency
   (&optional __beidou_correction_latency)
   (if __beidou_correction_latency (setq _beidou_correction_latency __beidou_correction_latency)) _beidou_correction_latency)
  (:raw_status_flags
   (&optional __raw_status_flags)
   (if __raw_status_flags (setq _raw_status_flags __raw_status_flags)) _raw_status_flags)
  (:serialization-length
   ()
   (+
    ;; float64 _gps_tow
    8
    ;; uint16 _gps_week
    2
    ;; uint16 _epoch_status
    2
    ;; uint8 _dongle_version
    1
    ;; uint8 _dongle_controller_state
    1
    ;; uint8 _dongle_platform_state
    1
    ;; uint8 _dongle_controller_status
    1
    ;; uint8 _dongle_platform_status
    1
    ;; uint8 _dongle_reset_reason
    1
    ;; uint8 _dongle_signal_quality
    1
    ;; float32 _gps_correction_latency
    4
    ;; float32 _glonass_correction_latency
    4
    ;; float32 _galileo_correction_latency
    4
    ;; float32 _beidou_correction_latency
    4
    ;; uint32 _raw_status_flags
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _gps_tow
       (sys::poke _gps_tow (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint16 _gps_week
       (write-word _gps_week s)
     ;; uint16 _epoch_status
       (write-word _epoch_status s)
     ;; uint8 _dongle_version
       (write-byte _dongle_version s)
     ;; uint8 _dongle_controller_state
       (write-byte _dongle_controller_state s)
     ;; uint8 _dongle_platform_state
       (write-byte _dongle_platform_state s)
     ;; uint8 _dongle_controller_status
       (write-byte _dongle_controller_status s)
     ;; uint8 _dongle_platform_status
       (write-byte _dongle_platform_status s)
     ;; uint8 _dongle_reset_reason
       (write-byte _dongle_reset_reason s)
     ;; uint8 _dongle_signal_quality
       (write-byte _dongle_signal_quality s)
     ;; float32 _gps_correction_latency
       (sys::poke _gps_correction_latency (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _glonass_correction_latency
       (sys::poke _glonass_correction_latency (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _galileo_correction_latency
       (sys::poke _galileo_correction_latency (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _beidou_correction_latency
       (sys::poke _beidou_correction_latency (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _raw_status_flags
       (write-long _raw_status_flags s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _gps_tow
     (setq _gps_tow (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint16 _gps_week
     (setq _gps_week (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _epoch_status
     (setq _epoch_status (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint8 _dongle_version
     (setq _dongle_version (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_controller_state
     (setq _dongle_controller_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_platform_state
     (setq _dongle_platform_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_controller_status
     (setq _dongle_controller_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_platform_status
     (setq _dongle_platform_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_reset_reason
     (setq _dongle_reset_reason (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dongle_signal_quality
     (setq _dongle_signal_quality (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _gps_correction_latency
     (setq _gps_correction_latency (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _glonass_correction_latency
     (setq _glonass_correction_latency (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _galileo_correction_latency
     (setq _galileo_correction_latency (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _beidou_correction_latency
     (setq _beidou_correction_latency (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _raw_status_flags
     (setq _raw_status_flags (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::RTKStatusV1 :md5sum-) "5892d8d3cacc1b4c1666dd4bc1af9236")
(setf (get microstrain_inertial_msgs::RTKStatusV1 :datatype-) "microstrain_inertial_msgs/RTKStatusV1")
(setf (get microstrain_inertial_msgs::RTKStatusV1 :definition-)
      "float64 gps_tow
uint16  gps_week
uint16  epoch_status

uint8   dongle_version
uint8   dongle_controller_state
uint8   dongle_platform_state
uint8   dongle_controller_status
uint8   dongle_platform_status
uint8   dongle_reset_reason
uint8   dongle_signal_quality

float32 gps_correction_latency
float32 glonass_correction_latency
float32 galileo_correction_latency
float32 beidou_correction_latency


uint32  raw_status_flags        # Raw status flags value
")



(provide :microstrain_inertial_msgs/RTKStatusV1 "5892d8d3cacc1b4c1666dd4bc1af9236")


