;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::InputSpeedMeasurement)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'InputSpeedMeasurement (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::INPUTSPEEDMEASUREMENT")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::INPUTSPEEDMEASUREMENT"))

(in-package "ROS")
;;//! \htmlinclude InputSpeedMeasurement.msg.html


(defclass microstrain_inertial_msgs::InputSpeedMeasurement
  :super ros::object
  :slots (_gps_tow _speed _speed_uncertainty ))

(defmethod microstrain_inertial_msgs::InputSpeedMeasurement
  (:init
   (&key
    ((:gps_tow __gps_tow) 0.0)
    ((:speed __speed) 0.0)
    ((:speed_uncertainty __speed_uncertainty) 0.0)
    )
   (send-super :init)
   (setq _gps_tow (float __gps_tow))
   (setq _speed (float __speed))
   (setq _speed_uncertainty (float __speed_uncertainty))
   self)
  (:gps_tow
   (&optional __gps_tow)
   (if __gps_tow (setq _gps_tow __gps_tow)) _gps_tow)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:speed_uncertainty
   (&optional __speed_uncertainty)
   (if __speed_uncertainty (setq _speed_uncertainty __speed_uncertainty)) _speed_uncertainty)
  (:serialization-length
   ()
   (+
    ;; float32 _gps_tow
    4
    ;; float32 _speed
    4
    ;; float32 _speed_uncertainty
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _gps_tow
       (sys::poke _gps_tow (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _speed_uncertainty
       (sys::poke _speed_uncertainty (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _gps_tow
     (setq _gps_tow (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _speed_uncertainty
     (setq _speed_uncertainty (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::InputSpeedMeasurement :md5sum-) "c23013e9b4813b23fc2611c8b2e2b2c8")
(setf (get microstrain_inertial_msgs::InputSpeedMeasurement :datatype-) "microstrain_inertial_msgs/InputSpeedMeasurement")
(setf (get microstrain_inertial_msgs::InputSpeedMeasurement :definition-)
      "float32 gps_tow  # GPS time of week when speed was sampled
float32 speed  # Estimated speed along vehicle's x-axis (may be positive or negative) (m/s)
float32 speed_uncertainty  # Estimated uncertainty in the speed measurement (1-sigma value) (m/s)
")



(provide :microstrain_inertial_msgs/InputSpeedMeasurement "c23013e9b4813b23fc2611c8b2e2b2c8")


