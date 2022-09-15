;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'FilterAidingMeasurementSummaryIndicator (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::FILTERAIDINGMEASUREMENTSUMMARYINDICATOR")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::FILTERAIDINGMEASUREMENTSUMMARYINDICATOR"))

(in-package "ROS")
;;//! \htmlinclude FilterAidingMeasurementSummaryIndicator.msg.html


(defclass microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator
  :super ros::object
  :slots (_enabled _used _residual_high_warning _sample_time_warning _configuration_error _max_num_meas_exceeded ))

(defmethod microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator
  (:init
   (&key
    ((:enabled __enabled) nil)
    ((:used __used) nil)
    ((:residual_high_warning __residual_high_warning) nil)
    ((:sample_time_warning __sample_time_warning) nil)
    ((:configuration_error __configuration_error) nil)
    ((:max_num_meas_exceeded __max_num_meas_exceeded) nil)
    )
   (send-super :init)
   (setq _enabled __enabled)
   (setq _used __used)
   (setq _residual_high_warning __residual_high_warning)
   (setq _sample_time_warning __sample_time_warning)
   (setq _configuration_error __configuration_error)
   (setq _max_num_meas_exceeded __max_num_meas_exceeded)
   self)
  (:enabled
   (&optional __enabled)
   (if __enabled (setq _enabled __enabled)) _enabled)
  (:used
   (&optional __used)
   (if __used (setq _used __used)) _used)
  (:residual_high_warning
   (&optional __residual_high_warning)
   (if __residual_high_warning (setq _residual_high_warning __residual_high_warning)) _residual_high_warning)
  (:sample_time_warning
   (&optional __sample_time_warning)
   (if __sample_time_warning (setq _sample_time_warning __sample_time_warning)) _sample_time_warning)
  (:configuration_error
   (&optional __configuration_error)
   (if __configuration_error (setq _configuration_error __configuration_error)) _configuration_error)
  (:max_num_meas_exceeded
   (&optional __max_num_meas_exceeded)
   (if __max_num_meas_exceeded (setq _max_num_meas_exceeded __max_num_meas_exceeded)) _max_num_meas_exceeded)
  (:serialization-length
   ()
   (+
    ;; bool _enabled
    1
    ;; bool _used
    1
    ;; bool _residual_high_warning
    1
    ;; bool _sample_time_warning
    1
    ;; bool _configuration_error
    1
    ;; bool _max_num_meas_exceeded
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _enabled
       (if _enabled (write-byte -1 s) (write-byte 0 s))
     ;; bool _used
       (if _used (write-byte -1 s) (write-byte 0 s))
     ;; bool _residual_high_warning
       (if _residual_high_warning (write-byte -1 s) (write-byte 0 s))
     ;; bool _sample_time_warning
       (if _sample_time_warning (write-byte -1 s) (write-byte 0 s))
     ;; bool _configuration_error
       (if _configuration_error (write-byte -1 s) (write-byte 0 s))
     ;; bool _max_num_meas_exceeded
       (if _max_num_meas_exceeded (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _enabled
     (setq _enabled (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _used
     (setq _used (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _residual_high_warning
     (setq _residual_high_warning (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _sample_time_warning
     (setq _sample_time_warning (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _configuration_error
     (setq _configuration_error (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _max_num_meas_exceeded
     (setq _max_num_meas_exceeded (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :md5sum-) "4e3131125b51ac75dceed1517c488713")
(setf (get microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :datatype-) "microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator")
(setf (get microstrain_inertial_msgs::FilterAidingMeasurementSummaryIndicator :definition-)
      "bool enabled
bool used
bool residual_high_warning
bool sample_time_warning
bool configuration_error
bool max_num_meas_exceeded
")



(provide :microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator "4e3131125b51ac75dceed1517c488713")


