;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetSensor2VehicleOffset)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetSensor2VehicleOffset (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETSENSOR2VEHICLEOFFSET")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETSENSOR2VEHICLEOFFSET"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETSENSOR2VEHICLEOFFSETREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETSENSOR2VEHICLEOFFSETREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETSENSOR2VEHICLEOFFSETRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETSENSOR2VEHICLEOFFSETRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass microstrain_inertial_msgs::SetSensor2VehicleOffsetRequest
  :super ros::object
  :slots (_offset ))

(defmethod microstrain_inertial_msgs::SetSensor2VehicleOffsetRequest
  (:init
   (&key
    ((:offset __offset) (instance geometry_msgs::Vector3 :init))
    )
   (send-super :init)
   (setq _offset __offset)
   self)
  (:offset
   (&rest __offset)
   (if (keywordp (car __offset))
       (send* _offset __offset)
     (progn
       (if __offset (setq _offset (car __offset)))
       _offset)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _offset
    (send _offset :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _offset
       (send _offset :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _offset
     (send _offset :deserialize buf ptr-) (incf ptr- (send _offset :serialization-length))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetSensor2VehicleOffsetResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetSensor2VehicleOffsetResponse
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

(defclass microstrain_inertial_msgs::SetSensor2VehicleOffset
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffset :md5sum-) "17d27ff1259ce523baf9de57b7c37e18")
(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffset :datatype-) "microstrain_inertial_msgs/SetSensor2VehicleOffset")
(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffset :request) microstrain_inertial_msgs::SetSensor2VehicleOffsetRequest)
(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffset :response) microstrain_inertial_msgs::SetSensor2VehicleOffsetResponse)

(defmethod microstrain_inertial_msgs::SetSensor2VehicleOffsetRequest
  (:response () (instance microstrain_inertial_msgs::SetSensor2VehicleOffsetResponse :init)))

(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffsetRequest :md5sum-) "17d27ff1259ce523baf9de57b7c37e18")
(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffsetRequest :datatype-) "microstrain_inertial_msgs/SetSensor2VehicleOffsetRequest")
(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffsetRequest :definition-)
      "geometry_msgs/Vector3 offset

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

(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffsetResponse :md5sum-) "17d27ff1259ce523baf9de57b7c37e18")
(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffsetResponse :datatype-) "microstrain_inertial_msgs/SetSensor2VehicleOffsetResponse")
(setf (get microstrain_inertial_msgs::SetSensor2VehicleOffsetResponse :definition-)
      "geometry_msgs/Vector3 offset

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



(provide :microstrain_inertial_msgs/SetSensor2VehicleOffset "17d27ff1259ce523baf9de57b7c37e18")


