;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::DeviceSettings)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'DeviceSettings (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::DEVICESETTINGS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::DEVICESETTINGS"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::DEVICESETTINGSREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::DEVICESETTINGSREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::DEVICESETTINGSRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::DEVICESETTINGSRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::DeviceSettingsRequest
  :super ros::object
  :slots (_function_selector ))

(defmethod microstrain_inertial_msgs::DeviceSettingsRequest
  (:init
   (&key
    ((:function_selector __function_selector) 0)
    )
   (send-super :init)
   (setq _function_selector (round __function_selector))
   self)
  (:function_selector
   (&optional __function_selector)
   (if __function_selector (setq _function_selector __function_selector)) _function_selector)
  (:serialization-length
   ()
   (+
    ;; uint8 _function_selector
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _function_selector
       (write-byte _function_selector s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _function_selector
     (setq _function_selector (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::DeviceSettingsResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::DeviceSettingsResponse
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

(defclass microstrain_inertial_msgs::DeviceSettings
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::DeviceSettings :md5sum-) "a5738bbd08ff2569a7464cd41b071fc3")
(setf (get microstrain_inertial_msgs::DeviceSettings :datatype-) "microstrain_inertial_msgs/DeviceSettings")
(setf (get microstrain_inertial_msgs::DeviceSettings :request) microstrain_inertial_msgs::DeviceSettingsRequest)
(setf (get microstrain_inertial_msgs::DeviceSettings :response) microstrain_inertial_msgs::DeviceSettingsResponse)

(defmethod microstrain_inertial_msgs::DeviceSettingsRequest
  (:response () (instance microstrain_inertial_msgs::DeviceSettingsResponse :init)))

(setf (get microstrain_inertial_msgs::DeviceSettingsRequest :md5sum-) "a5738bbd08ff2569a7464cd41b071fc3")
(setf (get microstrain_inertial_msgs::DeviceSettingsRequest :datatype-) "microstrain_inertial_msgs/DeviceSettingsRequest")
(setf (get microstrain_inertial_msgs::DeviceSettingsRequest :definition-)
      "uint8 function_selector
---
bool success

")

(setf (get microstrain_inertial_msgs::DeviceSettingsResponse :md5sum-) "a5738bbd08ff2569a7464cd41b071fc3")
(setf (get microstrain_inertial_msgs::DeviceSettingsResponse :datatype-) "microstrain_inertial_msgs/DeviceSettingsResponse")
(setf (get microstrain_inertial_msgs::DeviceSettingsResponse :definition-)
      "uint8 function_selector
---
bool success

")



(provide :microstrain_inertial_msgs/DeviceSettings "a5738bbd08ff2569a7464cd41b071fc3")


