;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetReferencePosition)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetReferencePosition (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETREFERENCEPOSITION")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETREFERENCEPOSITION"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETREFERENCEPOSITIONREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETREFERENCEPOSITIONREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETREFERENCEPOSITIONRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETREFERENCEPOSITIONRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass microstrain_inertial_msgs::SetReferencePositionRequest
  :super ros::object
  :slots (_position ))

(defmethod microstrain_inertial_msgs::SetReferencePositionRequest
  (:init
   (&key
    ((:position __position) (instance geometry_msgs::Vector3 :init))
    )
   (send-super :init)
   (setq _position __position)
   self)
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _position
    (send _position :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _position
       (send _position :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetReferencePositionResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetReferencePositionResponse
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

(defclass microstrain_inertial_msgs::SetReferencePosition
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetReferencePosition :md5sum-) "eed8c009a979878261617f53e8264ddc")
(setf (get microstrain_inertial_msgs::SetReferencePosition :datatype-) "microstrain_inertial_msgs/SetReferencePosition")
(setf (get microstrain_inertial_msgs::SetReferencePosition :request) microstrain_inertial_msgs::SetReferencePositionRequest)
(setf (get microstrain_inertial_msgs::SetReferencePosition :response) microstrain_inertial_msgs::SetReferencePositionResponse)

(defmethod microstrain_inertial_msgs::SetReferencePositionRequest
  (:response () (instance microstrain_inertial_msgs::SetReferencePositionResponse :init)))

(setf (get microstrain_inertial_msgs::SetReferencePositionRequest :md5sum-) "eed8c009a979878261617f53e8264ddc")
(setf (get microstrain_inertial_msgs::SetReferencePositionRequest :datatype-) "microstrain_inertial_msgs/SetReferencePositionRequest")
(setf (get microstrain_inertial_msgs::SetReferencePositionRequest :definition-)
      "geometry_msgs/Vector3 position

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

(setf (get microstrain_inertial_msgs::SetReferencePositionResponse :md5sum-) "eed8c009a979878261617f53e8264ddc")
(setf (get microstrain_inertial_msgs::SetReferencePositionResponse :datatype-) "microstrain_inertial_msgs/SetReferencePositionResponse")
(setf (get microstrain_inertial_msgs::SetReferencePositionResponse :definition-)
      "geometry_msgs/Vector3 position

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



(provide :microstrain_inertial_msgs/SetReferencePosition "eed8c009a979878261617f53e8264ddc")


