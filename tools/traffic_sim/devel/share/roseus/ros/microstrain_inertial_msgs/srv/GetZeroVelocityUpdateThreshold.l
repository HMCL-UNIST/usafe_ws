;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetZeroVelocityUpdateThreshold)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetZeroVelocityUpdateThreshold (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROVELOCITYUPDATETHRESHOLD")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROVELOCITYUPDATETHRESHOLD"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROVELOCITYUPDATETHRESHOLDREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROVELOCITYUPDATETHRESHOLDREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROVELOCITYUPDATETHRESHOLDRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROVELOCITYUPDATETHRESHOLDRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdResponse
  :super ros::object
  :slots (_enable _threshold _success ))

(defmethod microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdResponse
  (:init
   (&key
    ((:enable __enable) 0)
    ((:threshold __threshold) 0.0)
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _enable (round __enable))
   (setq _threshold (float __threshold))
   (setq _success __success)
   self)
  (:enable
   (&optional __enable)
   (if __enable (setq _enable __enable)) _enable)
  (:threshold
   (&optional __threshold)
   (if __threshold (setq _threshold __threshold)) _threshold)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int8 _enable
    1
    ;; float32 _threshold
    4
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _enable
       (write-byte _enable s)
     ;; float32 _threshold
       (sys::poke _threshold (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _enable
     (setq _enable (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _enable 127) (setq _enable (- _enable 256)))
   ;; float32 _threshold
     (setq _threshold (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetZeroVelocityUpdateThreshold
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThreshold :md5sum-) "1d55bd0c555abfd31bce740efa684526")
(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThreshold :datatype-) "microstrain_inertial_msgs/GetZeroVelocityUpdateThreshold")
(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThreshold :request) microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdRequest)
(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThreshold :response) microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdResponse)

(defmethod microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdRequest
  (:response () (instance microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdResponse :init)))

(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdRequest :md5sum-) "1d55bd0c555abfd31bce740efa684526")
(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdRequest :datatype-) "microstrain_inertial_msgs/GetZeroVelocityUpdateThresholdRequest")
(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdRequest :definition-)
      "---
int8 enable
float32 threshold
bool success

")

(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdResponse :md5sum-) "1d55bd0c555abfd31bce740efa684526")
(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdResponse :datatype-) "microstrain_inertial_msgs/GetZeroVelocityUpdateThresholdResponse")
(setf (get microstrain_inertial_msgs::GetZeroVelocityUpdateThresholdResponse :definition-)
      "---
int8 enable
float32 threshold
bool success

")



(provide :microstrain_inertial_msgs/GetZeroVelocityUpdateThreshold "1d55bd0c555abfd31bce740efa684526")


