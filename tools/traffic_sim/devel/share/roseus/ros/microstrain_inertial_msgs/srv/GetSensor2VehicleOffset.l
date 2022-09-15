;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetSensor2VehicleOffset)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetSensor2VehicleOffset (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEOFFSET")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEOFFSET"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEOFFSETREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEOFFSETREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEOFFSETRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETSENSOR2VEHICLEOFFSETRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetSensor2VehicleOffsetRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetSensor2VehicleOffsetRequest
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

(defclass microstrain_inertial_msgs::GetSensor2VehicleOffsetResponse
  :super ros::object
  :slots (_offset _success ))

(defmethod microstrain_inertial_msgs::GetSensor2VehicleOffsetResponse
  (:init
   (&key
    ((:offset __offset) (instance geometry_msgs::Vector3 :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _offset __offset)
   (setq _success __success)
   self)
  (:offset
   (&rest __offset)
   (if (keywordp (car __offset))
       (send* _offset __offset)
     (progn
       (if __offset (setq _offset (car __offset)))
       _offset)))
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _offset
    (send _offset :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _offset
       (send _offset :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _offset
     (send _offset :deserialize buf ptr-) (incf ptr- (send _offset :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetSensor2VehicleOffset
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffset :md5sum-) "336379c9adc329d4ecaa355471c3cacd")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffset :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleOffset")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffset :request) microstrain_inertial_msgs::GetSensor2VehicleOffsetRequest)
(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffset :response) microstrain_inertial_msgs::GetSensor2VehicleOffsetResponse)

(defmethod microstrain_inertial_msgs::GetSensor2VehicleOffsetRequest
  (:response () (instance microstrain_inertial_msgs::GetSensor2VehicleOffsetResponse :init)))

(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffsetRequest :md5sum-) "336379c9adc329d4ecaa355471c3cacd")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffsetRequest :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleOffsetRequest")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffsetRequest :definition-)
      "---
geometry_msgs/Vector3 offset
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

(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffsetResponse :md5sum-) "336379c9adc329d4ecaa355471c3cacd")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffsetResponse :datatype-) "microstrain_inertial_msgs/GetSensor2VehicleOffsetResponse")
(setf (get microstrain_inertial_msgs::GetSensor2VehicleOffsetResponse :definition-)
      "---
geometry_msgs/Vector3 offset
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



(provide :microstrain_inertial_msgs/GetSensor2VehicleOffset "336379c9adc329d4ecaa355471c3cacd")


