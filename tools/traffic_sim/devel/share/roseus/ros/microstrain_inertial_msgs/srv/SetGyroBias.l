;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetGyroBias)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetGyroBias (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETGYROBIAS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETGYROBIAS"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETGYROBIASREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETGYROBIASREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETGYROBIASRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETGYROBIASRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass microstrain_inertial_msgs::SetGyroBiasRequest
  :super ros::object
  :slots (_bias ))

(defmethod microstrain_inertial_msgs::SetGyroBiasRequest
  (:init
   (&key
    ((:bias __bias) (instance geometry_msgs::Vector3 :init))
    )
   (send-super :init)
   (setq _bias __bias)
   self)
  (:bias
   (&rest __bias)
   (if (keywordp (car __bias))
       (send* _bias __bias)
     (progn
       (if __bias (setq _bias (car __bias)))
       _bias)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _bias
    (send _bias :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _bias
       (send _bias :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _bias
     (send _bias :deserialize buf ptr-) (incf ptr- (send _bias :serialization-length))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetGyroBiasResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetGyroBiasResponse
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

(defclass microstrain_inertial_msgs::SetGyroBias
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetGyroBias :md5sum-) "7f2cf85b824b45f9f629310ab233f3c6")
(setf (get microstrain_inertial_msgs::SetGyroBias :datatype-) "microstrain_inertial_msgs/SetGyroBias")
(setf (get microstrain_inertial_msgs::SetGyroBias :request) microstrain_inertial_msgs::SetGyroBiasRequest)
(setf (get microstrain_inertial_msgs::SetGyroBias :response) microstrain_inertial_msgs::SetGyroBiasResponse)

(defmethod microstrain_inertial_msgs::SetGyroBiasRequest
  (:response () (instance microstrain_inertial_msgs::SetGyroBiasResponse :init)))

(setf (get microstrain_inertial_msgs::SetGyroBiasRequest :md5sum-) "7f2cf85b824b45f9f629310ab233f3c6")
(setf (get microstrain_inertial_msgs::SetGyroBiasRequest :datatype-) "microstrain_inertial_msgs/SetGyroBiasRequest")
(setf (get microstrain_inertial_msgs::SetGyroBiasRequest :definition-)
      "geometry_msgs/Vector3 bias

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

(setf (get microstrain_inertial_msgs::SetGyroBiasResponse :md5sum-) "7f2cf85b824b45f9f629310ab233f3c6")
(setf (get microstrain_inertial_msgs::SetGyroBiasResponse :datatype-) "microstrain_inertial_msgs/SetGyroBiasResponse")
(setf (get microstrain_inertial_msgs::SetGyroBiasResponse :definition-)
      "geometry_msgs/Vector3 bias

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



(provide :microstrain_inertial_msgs/SetGyroBias "7f2cf85b824b45f9f629310ab233f3c6")


