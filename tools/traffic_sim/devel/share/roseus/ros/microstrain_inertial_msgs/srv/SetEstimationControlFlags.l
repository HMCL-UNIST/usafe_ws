;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetEstimationControlFlags)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetEstimationControlFlags (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGS"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSRESPONSE"))

(in-package "ROS")





(intern "*GYRO_BIAS_ESTIMATION*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSREQUEST"))
(shadow '*GYRO_BIAS_ESTIMATION* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSREQUEST"))
(defconstant microstrain_inertial_msgs::SetEstimationControlFlagsRequest::*GYRO_BIAS_ESTIMATION* 1)
(intern "*HARD_IRON_AUTO_CALIBRATION*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSREQUEST"))
(shadow '*HARD_IRON_AUTO_CALIBRATION* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSREQUEST"))
(defconstant microstrain_inertial_msgs::SetEstimationControlFlagsRequest::*HARD_IRON_AUTO_CALIBRATION* 32)
(intern "*SOFT_IRON_AUTO_CALIBRATION*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSREQUEST"))
(shadow '*SOFT_IRON_AUTO_CALIBRATION* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETESTIMATIONCONTROLFLAGSREQUEST"))
(defconstant microstrain_inertial_msgs::SetEstimationControlFlagsRequest::*SOFT_IRON_AUTO_CALIBRATION* 64)
(defclass microstrain_inertial_msgs::SetEstimationControlFlagsRequest
  :super ros::object
  :slots (_flags ))

(defmethod microstrain_inertial_msgs::SetEstimationControlFlagsRequest
  (:init
   (&key
    ((:flags __flags) 0)
    )
   (send-super :init)
   (setq _flags (round __flags))
   self)
  (:flags
   (&optional __flags)
   (if __flags (setq _flags __flags)) _flags)
  (:serialization-length
   ()
   (+
    ;; int8 _flags
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _flags
       (write-byte _flags s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _flags
     (setq _flags (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _flags 127) (setq _flags (- _flags 256)))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetEstimationControlFlagsResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetEstimationControlFlagsResponse
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

(defclass microstrain_inertial_msgs::SetEstimationControlFlags
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetEstimationControlFlags :md5sum-) "7efd025d74deaecd09a7eaf56530e702")
(setf (get microstrain_inertial_msgs::SetEstimationControlFlags :datatype-) "microstrain_inertial_msgs/SetEstimationControlFlags")
(setf (get microstrain_inertial_msgs::SetEstimationControlFlags :request) microstrain_inertial_msgs::SetEstimationControlFlagsRequest)
(setf (get microstrain_inertial_msgs::SetEstimationControlFlags :response) microstrain_inertial_msgs::SetEstimationControlFlagsResponse)

(defmethod microstrain_inertial_msgs::SetEstimationControlFlagsRequest
  (:response () (instance microstrain_inertial_msgs::SetEstimationControlFlagsResponse :init)))

(setf (get microstrain_inertial_msgs::SetEstimationControlFlagsRequest :md5sum-) "7efd025d74deaecd09a7eaf56530e702")
(setf (get microstrain_inertial_msgs::SetEstimationControlFlagsRequest :datatype-) "microstrain_inertial_msgs/SetEstimationControlFlagsRequest")
(setf (get microstrain_inertial_msgs::SetEstimationControlFlagsRequest :definition-)
      "int8 GYRO_BIAS_ESTIMATION=1
int8 HARD_IRON_AUTO_CALIBRATION=32
int8 SOFT_IRON_AUTO_CALIBRATION=64
int8 flags
---
bool success

")

(setf (get microstrain_inertial_msgs::SetEstimationControlFlagsResponse :md5sum-) "7efd025d74deaecd09a7eaf56530e702")
(setf (get microstrain_inertial_msgs::SetEstimationControlFlagsResponse :datatype-) "microstrain_inertial_msgs/SetEstimationControlFlagsResponse")
(setf (get microstrain_inertial_msgs::SetEstimationControlFlagsResponse :definition-)
      "int8 GYRO_BIAS_ESTIMATION=1
int8 HARD_IRON_AUTO_CALIBRATION=32
int8 SOFT_IRON_AUTO_CALIBRATION=64
int8 flags
---
bool success

")



(provide :microstrain_inertial_msgs/SetEstimationControlFlags "7efd025d74deaecd09a7eaf56530e702")


