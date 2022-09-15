;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetTareOrientation)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetTareOrientation (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETTAREORIENTATION")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETTAREORIENTATION"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETTAREORIENTATIONREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETTAREORIENTATIONREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETTAREORIENTATIONRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETTAREORIENTATIONRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::GetTareOrientationRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetTareOrientationRequest
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

(defclass microstrain_inertial_msgs::GetTareOrientationResponse
  :super ros::object
  :slots (_axis _success ))

(defmethod microstrain_inertial_msgs::GetTareOrientationResponse
  (:init
   (&key
    ((:axis __axis) 0)
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _axis (round __axis))
   (setq _success __success)
   self)
  (:axis
   (&optional __axis)
   (if __axis (setq _axis __axis)) _axis)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int8 _axis
    1
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _axis
       (write-byte _axis s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _axis
     (setq _axis (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _axis 127) (setq _axis (- _axis 256)))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetTareOrientation
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetTareOrientation :md5sum-) "87ecd93a5c8679ed9b5ed373f0919456")
(setf (get microstrain_inertial_msgs::GetTareOrientation :datatype-) "microstrain_inertial_msgs/GetTareOrientation")
(setf (get microstrain_inertial_msgs::GetTareOrientation :request) microstrain_inertial_msgs::GetTareOrientationRequest)
(setf (get microstrain_inertial_msgs::GetTareOrientation :response) microstrain_inertial_msgs::GetTareOrientationResponse)

(defmethod microstrain_inertial_msgs::GetTareOrientationRequest
  (:response () (instance microstrain_inertial_msgs::GetTareOrientationResponse :init)))

(setf (get microstrain_inertial_msgs::GetTareOrientationRequest :md5sum-) "87ecd93a5c8679ed9b5ed373f0919456")
(setf (get microstrain_inertial_msgs::GetTareOrientationRequest :datatype-) "microstrain_inertial_msgs/GetTareOrientationRequest")
(setf (get microstrain_inertial_msgs::GetTareOrientationRequest :definition-)
      "---
int8 axis
bool success

")

(setf (get microstrain_inertial_msgs::GetTareOrientationResponse :md5sum-) "87ecd93a5c8679ed9b5ed373f0919456")
(setf (get microstrain_inertial_msgs::GetTareOrientationResponse :datatype-) "microstrain_inertial_msgs/GetTareOrientationResponse")
(setf (get microstrain_inertial_msgs::GetTareOrientationResponse :definition-)
      "---
int8 axis
bool success

")



(provide :microstrain_inertial_msgs/GetTareOrientation "87ecd93a5c8679ed9b5ed373f0919456")


