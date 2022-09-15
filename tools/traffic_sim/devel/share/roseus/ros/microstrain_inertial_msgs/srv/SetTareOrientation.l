;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetTareOrientation)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetTareOrientation (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETTAREORIENTATION")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETTAREORIENTATION"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETTAREORIENTATIONREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETTAREORIENTATIONREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETTAREORIENTATIONRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETTAREORIENTATIONRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::SetTareOrientationRequest
  :super ros::object
  :slots (_axis ))

(defmethod microstrain_inertial_msgs::SetTareOrientationRequest
  (:init
   (&key
    ((:axis __axis) 0)
    )
   (send-super :init)
   (setq _axis (round __axis))
   self)
  (:axis
   (&optional __axis)
   (if __axis (setq _axis __axis)) _axis)
  (:serialization-length
   ()
   (+
    ;; int8 _axis
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _axis
       (write-byte _axis s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _axis
     (setq _axis (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _axis 127) (setq _axis (- _axis 256)))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetTareOrientationResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetTareOrientationResponse
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

(defclass microstrain_inertial_msgs::SetTareOrientation
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetTareOrientation :md5sum-) "75811cb68205ae4484ed796af90a6397")
(setf (get microstrain_inertial_msgs::SetTareOrientation :datatype-) "microstrain_inertial_msgs/SetTareOrientation")
(setf (get microstrain_inertial_msgs::SetTareOrientation :request) microstrain_inertial_msgs::SetTareOrientationRequest)
(setf (get microstrain_inertial_msgs::SetTareOrientation :response) microstrain_inertial_msgs::SetTareOrientationResponse)

(defmethod microstrain_inertial_msgs::SetTareOrientationRequest
  (:response () (instance microstrain_inertial_msgs::SetTareOrientationResponse :init)))

(setf (get microstrain_inertial_msgs::SetTareOrientationRequest :md5sum-) "75811cb68205ae4484ed796af90a6397")
(setf (get microstrain_inertial_msgs::SetTareOrientationRequest :datatype-) "microstrain_inertial_msgs/SetTareOrientationRequest")
(setf (get microstrain_inertial_msgs::SetTareOrientationRequest :definition-)
      "int8 axis
---
bool success

")

(setf (get microstrain_inertial_msgs::SetTareOrientationResponse :md5sum-) "75811cb68205ae4484ed796af90a6397")
(setf (get microstrain_inertial_msgs::SetTareOrientationResponse :datatype-) "microstrain_inertial_msgs/SetTareOrientationResponse")
(setf (get microstrain_inertial_msgs::SetTareOrientationResponse :definition-)
      "int8 axis
---
bool success

")



(provide :microstrain_inertial_msgs/SetTareOrientation "75811cb68205ae4484ed796af90a6397")


