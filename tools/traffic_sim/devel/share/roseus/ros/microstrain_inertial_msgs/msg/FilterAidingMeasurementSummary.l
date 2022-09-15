;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::FilterAidingMeasurementSummary)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'FilterAidingMeasurementSummary (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::FILTERAIDINGMEASUREMENTSUMMARY")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::FILTERAIDINGMEASUREMENTSUMMARY"))

(in-package "ROS")
;;//! \htmlinclude FilterAidingMeasurementSummary.msg.html


(defclass microstrain_inertial_msgs::FilterAidingMeasurementSummary
  :super ros::object
  :slots (_gps_tow _gnss1 _gnss2 _dual_antenna _heading _pressure _magnetometer _speed ))

(defmethod microstrain_inertial_msgs::FilterAidingMeasurementSummary
  (:init
   (&key
    ((:gps_tow __gps_tow) 0.0)
    ((:gnss1 __gnss1) (instance microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :init))
    ((:gnss2 __gnss2) (instance microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :init))
    ((:dual_antenna __dual_antenna) (instance microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :init))
    ((:heading __heading) (instance microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :init))
    ((:pressure __pressure) (instance microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :init))
    ((:magnetometer __magnetometer) (instance microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :init))
    ((:speed __speed) (instance microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :init))
    )
   (send-super :init)
   (setq _gps_tow (float __gps_tow))
   (setq _gnss1 __gnss1)
   (setq _gnss2 __gnss2)
   (setq _dual_antenna __dual_antenna)
   (setq _heading __heading)
   (setq _pressure __pressure)
   (setq _magnetometer __magnetometer)
   (setq _speed __speed)
   self)
  (:gps_tow
   (&optional __gps_tow)
   (if __gps_tow (setq _gps_tow __gps_tow)) _gps_tow)
  (:gnss1
   (&rest __gnss1)
   (if (keywordp (car __gnss1))
       (send* _gnss1 __gnss1)
     (progn
       (if __gnss1 (setq _gnss1 (car __gnss1)))
       _gnss1)))
  (:gnss2
   (&rest __gnss2)
   (if (keywordp (car __gnss2))
       (send* _gnss2 __gnss2)
     (progn
       (if __gnss2 (setq _gnss2 (car __gnss2)))
       _gnss2)))
  (:dual_antenna
   (&rest __dual_antenna)
   (if (keywordp (car __dual_antenna))
       (send* _dual_antenna __dual_antenna)
     (progn
       (if __dual_antenna (setq _dual_antenna (car __dual_antenna)))
       _dual_antenna)))
  (:heading
   (&rest __heading)
   (if (keywordp (car __heading))
       (send* _heading __heading)
     (progn
       (if __heading (setq _heading (car __heading)))
       _heading)))
  (:pressure
   (&rest __pressure)
   (if (keywordp (car __pressure))
       (send* _pressure __pressure)
     (progn
       (if __pressure (setq _pressure (car __pressure)))
       _pressure)))
  (:magnetometer
   (&rest __magnetometer)
   (if (keywordp (car __magnetometer))
       (send* _magnetometer __magnetometer)
     (progn
       (if __magnetometer (setq _magnetometer (car __magnetometer)))
       _magnetometer)))
  (:speed
   (&rest __speed)
   (if (keywordp (car __speed))
       (send* _speed __speed)
     (progn
       (if __speed (setq _speed (car __speed)))
       _speed)))
  (:serialization-length
   ()
   (+
    ;; float64 _gps_tow
    8
    ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _gnss1
    (send _gnss1 :serialization-length)
    ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _gnss2
    (send _gnss2 :serialization-length)
    ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _dual_antenna
    (send _dual_antenna :serialization-length)
    ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _heading
    (send _heading :serialization-length)
    ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _pressure
    (send _pressure :serialization-length)
    ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _magnetometer
    (send _magnetometer :serialization-length)
    ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _speed
    (send _speed :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _gps_tow
       (sys::poke _gps_tow (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _gnss1
       (send _gnss1 :serialize s)
     ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _gnss2
       (send _gnss2 :serialize s)
     ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _dual_antenna
       (send _dual_antenna :serialize s)
     ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _heading
       (send _heading :serialize s)
     ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _pressure
       (send _pressure :serialize s)
     ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _magnetometer
       (send _magnetometer :serialize s)
     ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _speed
       (send _speed :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _gps_tow
     (setq _gps_tow (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _gnss1
     (send _gnss1 :deserialize buf ptr-) (incf ptr- (send _gnss1 :serialization-length))
   ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _gnss2
     (send _gnss2 :deserialize buf ptr-) (incf ptr- (send _gnss2 :serialization-length))
   ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _dual_antenna
     (send _dual_antenna :deserialize buf ptr-) (incf ptr- (send _dual_antenna :serialization-length))
   ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _heading
     (send _heading :deserialize buf ptr-) (incf ptr- (send _heading :serialization-length))
   ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _pressure
     (send _pressure :deserialize buf ptr-) (incf ptr- (send _pressure :serialization-length))
   ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _magnetometer
     (send _magnetometer :deserialize buf ptr-) (incf ptr- (send _magnetometer :serialization-length))
   ;; microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator _speed
     (send _speed :deserialize buf ptr-) (incf ptr- (send _speed :serialization-length))
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::FilterAidingMeasurementSummary :md5sum-) "150119d26260add7097bcac810af3fdb")
(setf (get microstrain_inertial_msgs::FilterAidingMeasurementSummary :datatype-) "microstrain_inertial_msgs/FilterAidingMeasurementSummary")
(setf (get microstrain_inertial_msgs::FilterAidingMeasurementSummary :definition-)
      "float64 gps_tow
microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator gnss1
microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator gnss2
microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator dual_antenna
microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator heading
microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator pressure
microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator magnetometer
microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator speed
================================================================================
MSG: microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator
bool enabled
bool used
bool residual_high_warning
bool sample_time_warning
bool configuration_error
bool max_num_meas_exceeded
")



(provide :microstrain_inertial_msgs/FilterAidingMeasurementSummary "150119d26260add7097bcac810af3fdb")


