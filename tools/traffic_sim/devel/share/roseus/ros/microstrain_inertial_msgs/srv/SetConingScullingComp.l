;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetConingScullingComp)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetConingScullingComp (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETCONINGSCULLINGCOMP")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETCONINGSCULLINGCOMP"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETCONINGSCULLINGCOMPREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETCONINGSCULLINGCOMPREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETCONINGSCULLINGCOMPRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETCONINGSCULLINGCOMPRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::SetConingScullingCompRequest
  :super ros::object
  :slots (_enable ))

(defmethod microstrain_inertial_msgs::SetConingScullingCompRequest
  (:init
   (&key
    ((:enable __enable) 0)
    )
   (send-super :init)
   (setq _enable (round __enable))
   self)
  (:enable
   (&optional __enable)
   (if __enable (setq _enable __enable)) _enable)
  (:serialization-length
   ()
   (+
    ;; int8 _enable
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _enable
       (write-byte _enable s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _enable
     (setq _enable (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _enable 127) (setq _enable (- _enable 256)))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetConingScullingCompResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetConingScullingCompResponse
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

(defclass microstrain_inertial_msgs::SetConingScullingComp
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetConingScullingComp :md5sum-) "f7caf6e1618fb8cc640ac244d6c53d7f")
(setf (get microstrain_inertial_msgs::SetConingScullingComp :datatype-) "microstrain_inertial_msgs/SetConingScullingComp")
(setf (get microstrain_inertial_msgs::SetConingScullingComp :request) microstrain_inertial_msgs::SetConingScullingCompRequest)
(setf (get microstrain_inertial_msgs::SetConingScullingComp :response) microstrain_inertial_msgs::SetConingScullingCompResponse)

(defmethod microstrain_inertial_msgs::SetConingScullingCompRequest
  (:response () (instance microstrain_inertial_msgs::SetConingScullingCompResponse :init)))

(setf (get microstrain_inertial_msgs::SetConingScullingCompRequest :md5sum-) "f7caf6e1618fb8cc640ac244d6c53d7f")
(setf (get microstrain_inertial_msgs::SetConingScullingCompRequest :datatype-) "microstrain_inertial_msgs/SetConingScullingCompRequest")
(setf (get microstrain_inertial_msgs::SetConingScullingCompRequest :definition-)
      "int8 enable
---
bool success

")

(setf (get microstrain_inertial_msgs::SetConingScullingCompResponse :md5sum-) "f7caf6e1618fb8cc640ac244d6c53d7f")
(setf (get microstrain_inertial_msgs::SetConingScullingCompResponse :datatype-) "microstrain_inertial_msgs/SetConingScullingCompResponse")
(setf (get microstrain_inertial_msgs::SetConingScullingCompResponse :definition-)
      "int8 enable
---
bool success

")



(provide :microstrain_inertial_msgs/SetConingScullingComp "f7caf6e1618fb8cc640ac244d6c53d7f")


