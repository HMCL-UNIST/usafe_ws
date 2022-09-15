;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetZeroVelocityUpdateThreshold)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetZeroVelocityUpdateThreshold (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETZEROVELOCITYUPDATETHRESHOLD")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETZEROVELOCITYUPDATETHRESHOLD"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETZEROVELOCITYUPDATETHRESHOLDREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETZEROVELOCITYUPDATETHRESHOLDREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETZEROVELOCITYUPDATETHRESHOLDRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETZEROVELOCITYUPDATETHRESHOLDRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdRequest
  :super ros::object
  :slots (_enable _threshold ))

(defmethod microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdRequest
  (:init
   (&key
    ((:enable __enable) 0)
    ((:threshold __threshold) 0.0)
    )
   (send-super :init)
   (setq _enable (round __enable))
   (setq _threshold (float __threshold))
   self)
  (:enable
   (&optional __enable)
   (if __enable (setq _enable __enable)) _enable)
  (:threshold
   (&optional __threshold)
   (if __threshold (setq _threshold __threshold)) _threshold)
  (:serialization-length
   ()
   (+
    ;; int8 _enable
    1
    ;; float32 _threshold
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _enable
       (write-byte _enable s)
     ;; float32 _threshold
       (sys::poke _threshold (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _enable
     (setq _enable (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _enable 127) (setq _enable (- _enable 256)))
   ;; float32 _threshold
     (setq _threshold (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdResponse
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

(defclass microstrain_inertial_msgs::SetZeroVelocityUpdateThreshold
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThreshold :md5sum-) "ea1115ed39d8a581530c7c251ee443e6")
(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThreshold :datatype-) "microstrain_inertial_msgs/SetZeroVelocityUpdateThreshold")
(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThreshold :request) microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdRequest)
(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThreshold :response) microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdResponse)

(defmethod microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdRequest
  (:response () (instance microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdResponse :init)))

(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdRequest :md5sum-) "ea1115ed39d8a581530c7c251ee443e6")
(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdRequest :datatype-) "microstrain_inertial_msgs/SetZeroVelocityUpdateThresholdRequest")
(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdRequest :definition-)
      "int8 enable
float32 threshold
---
bool success

")

(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdResponse :md5sum-) "ea1115ed39d8a581530c7c251ee443e6")
(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdResponse :datatype-) "microstrain_inertial_msgs/SetZeroVelocityUpdateThresholdResponse")
(setf (get microstrain_inertial_msgs::SetZeroVelocityUpdateThresholdResponse :definition-)
      "int8 enable
float32 threshold
---
bool success

")



(provide :microstrain_inertial_msgs/SetZeroVelocityUpdateThreshold "ea1115ed39d8a581530c7c251ee443e6")


