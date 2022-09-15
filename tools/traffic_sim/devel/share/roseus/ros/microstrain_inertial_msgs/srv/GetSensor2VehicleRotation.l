;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetSensor2VehicleRotation)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetSensor2VehicleRotation (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEROTATION")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEROTATION"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEROTATIONREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEROTATIONREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEROTATIONRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEROTATIONRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetSensor2VehicleRotationRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetSensor2VehicleRotationRequest
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

(defclass microstrain_inertial_msgs::GetSensor2VehicleRotationResponse
  :super ros::object
  :slots (_angle _success ))

(defmethod microstrain_inertial_msgs::GetSensor2VehicleRotationResponse
  (:init
   (&key
    ((:angle __angle) (instance geometry_msgs::Vector3 :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _angle __angle)
   (setq _success __success)
   self)
  (:angle
   (&rest __angle)
   (if (keywordp (car __angle))
       (send* _angle __angle)
     (progn
       (if __angle (setq _angle (car __angle)))
       _angle)))
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _angle
    (send _angle :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _angle
       (send _angle :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _angle
     (send _angle :deserialize buf ptr-) (incf ptr- (send _angle :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetSensor2VehicleRotation
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotation :md5sum-) "f17f1953dd3d01dff314cf417fc7232c")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotation :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleRotation")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotation :request) microstrain_inertial_msgs::GetSensor2VehicleRotationRequest)
(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotation :response) microstrain_inertial_msgs::GetSensor2VehicleRotationResponse)

(defmethod microstrain_inertial_msgs::GetSensor2VehicleRotationRequest
  (:response () (instance microstrain_inertial_msgs::GetSensor2VehicleRotationResponse :init)))

(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotationRequest :md5sum-) "f17f1953dd3d01dff314cf417fc7232c")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotationRequest :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleRotationRequest")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotationRequest :definition-)
      "---
geometry_msgs/Vector3 angle
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

(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotationResponse :md5sum-) "f17f1953dd3d01dff314cf417fc7232c")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotationResponse :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleRotationResponse")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleRotationResponse :definition-)
      "---
geometry_msgs/Vector3 angle
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



(provide :microstrain_inertial_msgs/GetSensor2VehicleRotation "f17f1953dd3d01dff314cf417fc7232c")


