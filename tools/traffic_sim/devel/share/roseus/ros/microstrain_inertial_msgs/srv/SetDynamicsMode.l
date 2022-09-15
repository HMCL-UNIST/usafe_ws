;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetDynamicsMode)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetDynamicsMode (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODERESPONSE"))

(in-package "ROS")





(intern "*PORTABLE*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODEREQUEST"))
(shadow '*PORTABLE* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODEREQUEST"))
(defconstant microstrain_inertial_msgs::SetDynamicsModeRequest::*PORTABLE* 1)
(intern "*AUTOMOTIVE*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODEREQUEST"))
(shadow '*AUTOMOTIVE* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODEREQUEST"))
(defconstant microstrain_inertial_msgs::SetDynamicsModeRequest::*AUTOMOTIVE* 2)
(intern "*AIRBORNE*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODEREQUEST"))
(shadow '*AIRBORNE* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETDYNAMICSMODEREQUEST"))
(defconstant microstrain_inertial_msgs::SetDynamicsModeRequest::*AIRBORNE* 3)
(defclass microstrain_inertial_msgs::SetDynamicsModeRequest
  :super ros::object
  :slots (_mode ))

(defmethod microstrain_inertial_msgs::SetDynamicsModeRequest
  (:init
   (&key
    ((:mode __mode) 0)
    )
   (send-super :init)
   (setq _mode (round __mode))
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:serialization-length
   ()
   (+
    ;; int8 _mode
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _mode
       (write-byte _mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _mode 127) (setq _mode (- _mode 256)))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetDynamicsModeResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetDynamicsModeResponse
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

(defclass microstrain_inertial_msgs::SetDynamicsMode
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetDynamicsMode :md5sum-) "44114e5483e212902c0a057defaa1a3b")
(setf (get microstrain_inertial_msgs::SetDynamicsMode :datatype-) "microstrain_inertial_msgs/SetDynamicsMode")
(setf (get microstrain_inertial_msgs::SetDynamicsMode :request) microstrain_inertial_msgs::SetDynamicsModeRequest)
(setf (get microstrain_inertial_msgs::SetDynamicsMode :response) microstrain_inertial_msgs::SetDynamicsModeResponse)

(defmethod microstrain_inertial_msgs::SetDynamicsModeRequest
  (:response () (instance microstrain_inertial_msgs::SetDynamicsModeResponse :init)))

(setf (get microstrain_inertial_msgs::SetDynamicsModeRequest :md5sum-) "44114e5483e212902c0a057defaa1a3b")
(setf (get microstrain_inertial_msgs::SetDynamicsModeRequest :datatype-) "microstrain_inertial_msgs/SetDynamicsModeRequest")
(setf (get microstrain_inertial_msgs::SetDynamicsModeRequest :definition-)
      "int8 PORTABLE=1
int8 AUTOMOTIVE=2
int8 AIRBORNE=3
int8 mode
---
bool success

")

(setf (get microstrain_inertial_msgs::SetDynamicsModeResponse :md5sum-) "44114e5483e212902c0a057defaa1a3b")
(setf (get microstrain_inertial_msgs::SetDynamicsModeResponse :datatype-) "microstrain_inertial_msgs/SetDynamicsModeResponse")
(setf (get microstrain_inertial_msgs::SetDynamicsModeResponse :definition-)
      "int8 PORTABLE=1
int8 AUTOMOTIVE=2
int8 AIRBORNE=3
int8 mode
---
bool success

")



(provide :microstrain_inertial_msgs/SetDynamicsMode "44114e5483e212902c0a057defaa1a3b")


