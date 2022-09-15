;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetDynamicsMode)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetDynamicsMode (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETDYNAMICSMODE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETDYNAMICSMODE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETDYNAMICSMODEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETDYNAMICSMODEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETDYNAMICSMODERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETDYNAMICSMODERESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::GetDynamicsModeRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetDynamicsModeRequest
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

(defclass microstrain_inertial_msgs::GetDynamicsModeResponse
  :super ros::object
  :slots (_mode _success ))

(defmethod microstrain_inertial_msgs::GetDynamicsModeResponse
  (:init
   (&key
    ((:mode __mode) 0)
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _mode (round __mode))
   (setq _success __success)
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int8 _mode
    1
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _mode
       (write-byte _mode s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _mode 127) (setq _mode (- _mode 256)))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetDynamicsMode
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetDynamicsMode :md5sum-) "4315dfa070d15c7ffc8d87836f8ad09c")
(setf (get microstrain_inertial_msgs::GetDynamicsMode :datatype-) "microstrain_inertial_msgs/GetDynamicsMode")
(setf (get microstrain_inertial_msgs::GetDynamicsMode :request) microstrain_inertial_msgs::GetDynamicsModeRequest)
(setf (get microstrain_inertial_msgs::GetDynamicsMode :response) microstrain_inertial_msgs::GetDynamicsModeResponse)

(defmethod microstrain_inertial_msgs::GetDynamicsModeRequest
  (:response () (instance microstrain_inertial_msgs::GetDynamicsModeResponse :init)))

(setf (get microstrain_inertial_msgs::GetDynamicsModeRequest :md5sum-) "4315dfa070d15c7ffc8d87836f8ad09c")
(setf (get microstrain_inertial_msgs::GetDynamicsModeRequest :datatype-) "microstrain_inertial_msgs/GetDynamicsModeRequest")
(setf (get microstrain_inertial_msgs::GetDynamicsModeRequest :definition-)
      "---
int8 mode
bool success

")

(setf (get microstrain_inertial_msgs::GetDynamicsModeResponse :md5sum-) "4315dfa070d15c7ffc8d87836f8ad09c")
(setf (get microstrain_inertial_msgs::GetDynamicsModeResponse :datatype-) "microstrain_inertial_msgs/GetDynamicsModeResponse")
(setf (get microstrain_inertial_msgs::GetDynamicsModeResponse :definition-)
      "---
int8 mode
bool success

")



(provide :microstrain_inertial_msgs/GetDynamicsMode "4315dfa070d15c7ffc8d87836f8ad09c")


