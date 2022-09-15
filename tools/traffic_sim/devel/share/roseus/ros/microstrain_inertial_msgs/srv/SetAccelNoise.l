;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetAccelNoise)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetAccelNoise (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETACCELNOISE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETACCELNOISE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETACCELNOISEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETACCELNOISEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETACCELNOISERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETACCELNOISERESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass microstrain_inertial_msgs::SetAccelNoiseRequest
  :super ros::object
  :slots (_noise ))

(defmethod microstrain_inertial_msgs::SetAccelNoiseRequest
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

(defclass microstrain_inertial_msgs::SetAccelNoiseResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetAccelNoiseResponse
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

(defclass microstrain_inertial_msgs::SetAccelNoise
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetAccelNoise :md5sum-) "6a73c0e939ba0cee17d40a2e3a5f667f")
(setf (get microstrain_inertial_msgs::SetAccelNoise :datatype-) "microstrain_inertial_msgs/SetAccelNoise")
(setf (get microstrain_inertial_msgs::SetAccelNoise :request) microstrain_inertial_msgs::SetAccelNoiseRequest)
(setf (get microstrain_inertial_msgs::SetAccelNoise :response) microstrain_inertial_msgs::SetAccelNoiseResponse)

(defmethod microstrain_inertial_msgs::SetAccelNoiseRequest
  (:response () (instance microstrain_inertial_msgs::SetAccelNoiseResponse :init)))

(setf (get microstrain_inertial_msgs::SetAccelNoiseRequest :md5sum-) "6a73c0e939ba0cee17d40a2e3a5f667f")
(setf (get microstrain_inertial_msgs::SetAccelNoiseRequest :datatype-) "microstrain_inertial_msgs/SetAccelNoiseRequest")
(setf (get microstrain_inertial_msgs::SetAccelNoiseRequest :definition-)
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

(setf (get microstrain_inertial_msgs::SetAccelNoiseResponse :md5sum-) "6a73c0e939ba0cee17d40a2e3a5f667f")
(setf (get microstrain_inertial_msgs::SetAccelNoiseResponse :datatype-) "microstrain_inertial_msgs/SetAccelNoiseResponse")
(setf (get microstrain_inertial_msgs::SetAccelNoiseResponse :definition-)
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



(provide :microstrain_inertial_msgs/SetAccelNoise "6a73c0e939ba0cee17d40a2e3a5f667f")


