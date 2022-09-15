;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetSensor2VehicleTransformation)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetSensor2VehicleTransformation (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLETRANSFORMATION")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLETRANSFORMATION"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLETRANSFORMATIONREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLETRANSFORMATIONREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLETRANSFORMATIONRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLETRANSFORMATIONRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetSensor2VehicleTransformationRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetSensor2VehicleTransformationRequest
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

(defclass microstrain_inertial_msgs::GetSensor2VehicleTransformationResponse
  :super ros::object
  :slots (_offset _rotation _success ))

(defmethod microstrain_inertial_msgs::GetSensor2VehicleTransformationResponse
  (:init
   (&key
    ((:offset __offset) (instance geometry_msgs::Vector3 :init))
    ((:rotation __rotation) (instance geometry_msgs::Quaternion :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _offset __offset)
   (setq _rotation __rotation)
   (setq _success __success)
   self)
  (:offset
   (&rest __offset)
   (if (keywordp (car __offset))
       (send* _offset __offset)
     (progn
       (if __offset (setq _offset (car __offset)))
       _offset)))
  (:rotation
   (&rest __rotation)
   (if (keywordp (car __rotation))
       (send* _rotation __rotation)
     (progn
       (if __rotation (setq _rotation (car __rotation)))
       _rotation)))
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _offset
    (send _offset :serialization-length)
    ;; geometry_msgs/Quaternion _rotation
    (send _rotation :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _offset
       (send _offset :serialize s)
     ;; geometry_msgs/Quaternion _rotation
       (send _rotation :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _offset
     (send _offset :deserialize buf ptr-) (incf ptr- (send _offset :serialization-length))
   ;; geometry_msgs/Quaternion _rotation
     (send _rotation :deserialize buf ptr-) (incf ptr- (send _rotation :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetSensor2VehicleTransformation
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformation :md5sum-) "004f75cd783f40825cb5e1db7049f127")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformation :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleTransformation")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformation :request) microstrain_inertial_msgs::GetSensor2VehicleTransformationRequest)
(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformation :response) microstrain_inertial_msgs::GetSensor2VehicleTransformationResponse)

(defmethod microstrain_inertial_msgs::GetSensor2VehicleTransformationRequest
  (:response () (instance microstrain_inertial_msgs::GetSensor2VehicleTransformationResponse :init)))

(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformationRequest :md5sum-) "004f75cd783f40825cb5e1db7049f127")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformationRequest :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleTransformationRequest")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformationRequest :definition-)
      "---
geometry_msgs/Vector3 offset
geometry_msgs/Quaternion rotation
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
float64 z
================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")

(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformationResponse :md5sum-) "004f75cd783f40825cb5e1db7049f127")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformationResponse :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleTransformationResponse")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleTransformationResponse :definition-)
      "---
geometry_msgs/Vector3 offset
geometry_msgs/Quaternion rotation
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
float64 z
================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")



(provide :microstrain_inertial_msgs/GetSensor2VehicleTransformation "004f75cd783f40825cb5e1db7049f127")


