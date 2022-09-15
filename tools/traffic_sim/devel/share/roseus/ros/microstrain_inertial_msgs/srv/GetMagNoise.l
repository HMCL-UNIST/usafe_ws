;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetMagNoise)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetMagNoise (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETMAGNOISE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETMAGNOISE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETMAGNOISEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETMAGNOISEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETMAGNOISERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETMAGNOISERESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetMagNoiseRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetMagNoiseRequest
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

(defclass microstrain_inertial_msgs::GetMagNoiseResponse
  :super ros::object
  :slots (_noise _success ))

(defmethod microstrain_inertial_msgs::GetMagNoiseResponse
  (:init
   (&key
    ((:noise __noise) (instance geometry_msgs::Vector3 :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _noise __noise)
   (setq _success __success)
   self)
  (:noise
   (&rest __noise)
   (if (keywordp (car __noise))
       (send* _noise __noise)
     (progn
       (if __noise (setq _noise (car __noise)))
       _noise)))
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _noise
    (send _noise :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _noise
       (send _noise :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _noise
     (send _noise :deserialize buf ptr-) (incf ptr- (send _noise :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetMagNoise
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetMagNoise :md5sum-) "f98ca1a5e4f9d504cd0b08eeeda072c5")
(setf (get microstrain_inertial_msgs::GetMagNoise :datatype-) "microstrain_inertial_msgs/GetMagNoise")
(setf (get microstrain_inertial_msgs::GetMagNoise :request) microstrain_inertial_msgs::GetMagNoiseRequest)
(setf (get microstrain_inertial_msgs::GetMagNoise :response) microstrain_inertial_msgs::GetMagNoiseResponse)

(defmethod microstrain_inertial_msgs::GetMagNoiseRequest
  (:response () (instance microstrain_inertial_msgs::GetMagNoiseResponse :init)))

(setf (get microstrain_inertial_msgs::GetMagNoiseRequest :md5sum-) "f98ca1a5e4f9d504cd0b08eeeda072c5")
(setf (get microstrain_inertial_msgs::GetMagNoiseRequest :datatype-) "microstrain_inertial_msgs/GetMagNoiseRequest")
(setf (get microstrain_inertial_msgs::GetMagNoiseRequest :definition-)
      "---
geometry_msgs/Vector3 noise
bool success


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
")

(setf (get microstrain_inertial_msgs::GetMagNoiseResponse :md5sum-) "f98ca1a5e4f9d504cd0b08eeeda072c5")
(setf (get microstrain_inertial_msgs::GetMagNoiseResponse :datatype-) "microstrain_inertial_msgs/GetMagNoiseResponse")
(setf (get microstrain_inertial_msgs::GetMagNoiseResponse :definition-)
      "---
geometry_msgs/Vector3 noise
bool success


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
")



(provide :microstrain_inertial_msgs/GetMagNoise "f98ca1a5e4f9d504cd0b08eeeda072c5")


