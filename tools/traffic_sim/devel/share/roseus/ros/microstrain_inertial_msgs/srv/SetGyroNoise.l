;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetGyroNoise)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetGyroNoise (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETGYRONOISE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETGYRONOISE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETGYRONOISEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETGYRONOISEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETGYRONOISERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETGYRONOISERESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass microstrain_inertial_msgs::SetGyroNoiseRequest
  :super ros::object
  :slots (_noise ))

(defmethod microstrain_inertial_msgs::SetGyroNoiseRequest
  (:init
   (&key
    ((:noise __noise) (instance geometry_msgs::Vector3 :init))
    )
   (send-super :init)
   (setq _noise __noise)
   self)
  (:noise
   (&rest __noise)
   (if (keywordp (car __noise))
       (send* _noise __noise)
     (progn
       (if __noise (setq _noise (car __noise)))
       _noise)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _noise
    (send _noise :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _noise
       (send _noise :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _noise
     (send _noise :deserialize buf ptr-) (incf ptr- (send _noise :serialization-length))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetGyroNoiseResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetGyroNoiseResponse
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

(defclass microstrain_inertial_msgs::SetGyroNoise
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetGyroNoise :md5sum-) "6a73c0e939ba0cee17d40a2e3a5f667f")
(setf (get microstrain_inertial_msgs::SetGyroNoise :datatype-) "microstrain_inertial_msgs/SetGyroNoise")
(setf (get microstrain_inertial_msgs::SetGyroNoise :request) microstrain_inertial_msgs::SetGyroNoiseRequest)
(setf (get microstrain_inertial_msgs::SetGyroNoise :response) microstrain_inertial_msgs::SetGyroNoiseResponse)

(defmethod microstrain_inertial_msgs::SetGyroNoiseRequest
  (:response () (instance microstrain_inertial_msgs::SetGyroNoiseResponse :init)))

(setf (get microstrain_inertial_msgs::SetGyroNoiseRequest :md5sum-) "6a73c0e939ba0cee17d40a2e3a5f667f")
(setf (get microstrain_inertial_msgs::SetGyroNoiseRequest :datatype-) "microstrain_inertial_msgs/SetGyroNoiseRequest")
(setf (get microstrain_inertial_msgs::SetGyroNoiseRequest :definition-)
      "geometry_msgs/Vector3 noise

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
---
bool success

")

(setf (get microstrain_inertial_msgs::SetGyroNoiseResponse :md5sum-) "6a73c0e939ba0cee17d40a2e3a5f667f")
(setf (get microstrain_inertial_msgs::SetGyroNoiseResponse :datatype-) "microstrain_inertial_msgs/SetGyroNoiseResponse")
(setf (get microstrain_inertial_msgs::SetGyroNoiseResponse :definition-)
      "geometry_msgs/Vector3 noise

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
---
bool success

")



(provide :microstrain_inertial_msgs/SetGyroNoise "6a73c0e939ba0cee17d40a2e3a5f667f")


