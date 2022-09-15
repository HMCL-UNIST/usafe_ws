;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetAccelBias)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetAccelBias (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETACCELBIAS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETACCELBIAS"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETACCELBIASREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETACCELBIASREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETACCELBIASRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETACCELBIASRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetAccelBiasRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetAccelBiasRequest
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

(defclass microstrain_inertial_msgs::GetAccelBiasResponse
  :super ros::object
  :slots (_bias _success ))

(defmethod microstrain_inertial_msgs::GetAccelBiasResponse
  (:init
   (&key
    ((:bias __bias) (instance geometry_msgs::Vector3 :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _bias __bias)
   (setq _success __success)
   self)
  (:bias
   (&rest __bias)
   (if (keywordp (car __bias))
       (send* _bias __bias)
     (progn
       (if __bias (setq _bias (car __bias)))
       _bias)))
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _bias
    (send _bias :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _bias
       (send _bias :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _bias
     (send _bias :deserialize buf ptr-) (incf ptr- (send _bias :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetAccelBias
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetAccelBias :md5sum-) "9427c94a8464f80e7ccfb4c788698d94")
(setf (get microstrain_inertial_msgs::GetAccelBias :datatype-) "microstrain_inertial_msgs/GetAccelBias")
(setf (get microstrain_inertial_msgs::GetAccelBias :request) microstrain_inertial_msgs::GetAccelBiasRequest)
(setf (get microstrain_inertial_msgs::GetAccelBias :response) microstrain_inertial_msgs::GetAccelBiasResponse)

(defmethod microstrain_inertial_msgs::GetAccelBiasRequest
  (:response () (instance microstrain_inertial_msgs::GetAccelBiasResponse :init)))

(setf (get microstrain_inertial_msgs::GetAccelBiasRequest :md5sum-) "9427c94a8464f80e7ccfb4c788698d94")
(setf (get microstrain_inertial_msgs::GetAccelBiasRequest :datatype-) "microstrain_inertial_msgs/GetAccelBiasRequest")
(setf (get microstrain_inertial_msgs::GetAccelBiasRequest :definition-)
      "---
geometry_msgs/Vector3 bias
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

(setf (get microstrain_inertial_msgs::GetAccelBiasResponse :md5sum-) "9427c94a8464f80e7ccfb4c788698d94")
(setf (get microstrain_inertial_msgs::GetAccelBiasResponse :datatype-) "microstrain_inertial_msgs/GetAccelBiasResponse")
(setf (get microstrain_inertial_msgs::GetAccelBiasResponse :definition-)
      "---
geometry_msgs/Vector3 bias
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



(provide :microstrain_inertial_msgs/GetAccelBias "9427c94a8464f80e7ccfb4c788698d94")


