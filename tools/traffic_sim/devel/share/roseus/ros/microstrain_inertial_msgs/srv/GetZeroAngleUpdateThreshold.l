;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetZeroAngleUpdateThreshold)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetZeroAngleUpdateThreshold (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROANGLEUPDATETHRESHOLD")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROANGLEUPDATETHRESHOLD"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROANGLEUPDATETHRESHOLDREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROANGLEUPDATETHRESHOLDREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROANGLEUPDATETHRESHOLDRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETZEROANGLEUPDATETHRESHOLDRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::GetZeroAngleUpdateThresholdRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetZeroAngleUpdateThresholdRequest
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

(defclass microstrain_inertial_msgs::GetZeroAngleUpdateThresholdResponse
  :super ros::object
  :slots (_enable _threshold _success ))

(defmethod microstrain_inertial_msgs::GetZeroAngleUpdateThresholdResponse
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

(defclass microstrain_inertial_msgs::GetZeroAngleUpdateThreshold
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThreshold :md5sum-) "1d55bd0c555abfd31bce740efa684526")
(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThreshold :datatype-) "microstrain_inertial_msgs/GetZeroAngleUpdateThreshold")
(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThreshold :request) microstrain_inertial_msgs::GetZeroAngleUpdateThresholdRequest)
(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThreshold :response) microstrain_inertial_msgs::GetZeroAngleUpdateThresholdResponse)

(defmethod microstrain_inertial_msgs::GetZeroAngleUpdateThresholdRequest
  (:response () (instance microstrain_inertial_msgs::GetZeroAngleUpdateThresholdResponse :init)))

(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThresholdRequest :md5sum-) "1d55bd0c555abfd31bce740efa684526")
(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThresholdRequest :datatype-) "microstrain_inertial_msgs/GetZeroAngleUpdateThresholdRequest")
(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThresholdRequest :definition-)
      "---
int8 enable
float32 threshold
bool success

")

(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThresholdResponse :md5sum-) "1d55bd0c555abfd31bce740efa684526")
(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThresholdResponse :datatype-) "microstrain_inertial_msgs/GetZeroAngleUpdateThresholdResponse")
(setf (get microstrain_inertial_msgs::GetZeroAngleUpdateThresholdResponse :definition-)
      "---
int8 enable
float32 threshold
bool success

")



(provide :microstrain_inertial_msgs/GetZeroAngleUpdateThreshold "1d55bd0c555abfd31bce740efa684526")


