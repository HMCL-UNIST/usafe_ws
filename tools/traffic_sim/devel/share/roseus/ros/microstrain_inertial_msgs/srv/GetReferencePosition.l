;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetReferencePosition)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetReferencePosition (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETREFERENCEPOSITION")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETREFERENCEPOSITION"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETREFERENCEPOSITIONREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETREFERENCEPOSITIONREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETREFERENCEPOSITIONRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETREFERENCEPOSITIONRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetReferencePositionRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetReferencePositionRequest
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

(defclass microstrain_inertial_msgs::GetReferencePositionResponse
  :super ros::object
  :slots (_position _success ))

(defmethod microstrain_inertial_msgs::GetReferencePositionResponse
  (:init
   (&key
    ((:position __position) (instance geometry_msgs::Vector3 :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _position __position)
   (setq _success __success)
   self)
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _position
    (send _position :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _position
       (send _position :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetReferencePosition
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetReferencePosition :md5sum-) "10b5e069422b2cf203664f7c0186f64a")
(setf (get microstrain_inertial_msgs::GetReferencePosition :datatype-) "microstrain_inertial_msgs/GetReferencePosition")
(setf (get microstrain_inertial_msgs::GetReferencePosition :request) microstrain_inertial_msgs::GetReferencePositionRequest)
(setf (get microstrain_inertial_msgs::GetReferencePosition :response) microstrain_inertial_msgs::GetReferencePositionResponse)

(defmethod microstrain_inertial_msgs::GetReferencePositionRequest
  (:response () (instance microstrain_inertial_msgs::GetReferencePositionResponse :init)))

(setf (get microstrain_inertial_msgs::GetReferencePositionRequest :md5sum-) "10b5e069422b2cf203664f7c0186f64a")
(setf (get microstrain_inertial_msgs::GetReferencePositionRequest :datatype-) "microstrain_inertial_msgs/GetReferencePositionRequest")
(setf (get microstrain_inertial_msgs::GetReferencePositionRequest :definition-)
      "---
geometry_msgs/Vector3 position
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

(setf (get microstrain_inertial_msgs::GetReferencePositionResponse :md5sum-) "10b5e069422b2cf203664f7c0186f64a")
(setf (get microstrain_inertial_msgs::GetReferencePositionResponse :datatype-) "microstrain_inertial_msgs/GetReferencePositionResponse")
(setf (get microstrain_inertial_msgs::GetReferencePositionResponse :definition-)
      "---
geometry_msgs/Vector3 position
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



(provide :microstrain_inertial_msgs/GetReferencePosition "10b5e069422b2cf203664f7c0186f64a")


