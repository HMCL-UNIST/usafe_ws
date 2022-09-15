;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetConingScullingComp)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetConingScullingComp (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETCONINGSCULLINGCOMP")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETCONINGSCULLINGCOMP"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETCONINGSCULLINGCOMPREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETCONINGSCULLINGCOMPREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETCONINGSCULLINGCOMPRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETCONINGSCULLINGCOMPRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::GetConingScullingCompRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetConingScullingCompRequest
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

(defclass microstrain_inertial_msgs::GetConingScullingCompResponse
  :super ros::object
  :slots (_enable _success ))

(defmethod microstrain_inertial_msgs::GetConingScullingCompResponse
  (:init
   (&key
    ((:enable __enable) 0)
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _enable (round __enable))
   (setq _success __success)
   self)
  (:enable
   (&optional __enable)
   (if __enable (setq _enable __enable)) _enable)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int8 _enable
    1
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _enable
       (write-byte _enable s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _enable
     (setq _enable (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _enable 127) (setq _enable (- _enable 256)))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetConingScullingComp
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetConingScullingComp :md5sum-) "73ec157fb12f6cbfec05839300a44bb3")
(setf (get microstrain_inertial_msgs::GetConingScullingComp :datatype-) "microstrain_inertial_msgs/GetConingScullingComp")
(setf (get microstrain_inertial_msgs::GetConingScullingComp :request) microstrain_inertial_msgs::GetConingScullingCompRequest)
(setf (get microstrain_inertial_msgs::GetConingScullingComp :response) microstrain_inertial_msgs::GetConingScullingCompResponse)

(defmethod microstrain_inertial_msgs::GetConingScullingCompRequest
  (:response () (instance microstrain_inertial_msgs::GetConingScullingCompResponse :init)))

(setf (get microstrain_inertial_msgs::GetConingScullingCompRequest :md5sum-) "73ec157fb12f6cbfec05839300a44bb3")
(setf (get microstrain_inertial_msgs::GetConingScullingCompRequest :datatype-) "microstrain_inertial_msgs/GetConingScullingCompRequest")
(setf (get microstrain_inertial_msgs::GetConingScullingCompRequest :definition-)
      "---
int8 enable
bool success

")

(setf (get microstrain_inertial_msgs::GetConingScullingCompResponse :md5sum-) "73ec157fb12f6cbfec05839300a44bb3")
(setf (get microstrain_inertial_msgs::GetConingScullingCompResponse :datatype-) "microstrain_inertial_msgs/GetConingScullingCompResponse")
(setf (get microstrain_inertial_msgs::GetConingScullingCompResponse :definition-)
      "---
int8 enable
bool success

")



(provide :microstrain_inertial_msgs/GetConingScullingComp "73ec157fb12f6cbfec05839300a44bb3")


