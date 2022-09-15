;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetHardIronValues)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetHardIronValues (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETHARDIRONVALUES")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETHARDIRONVALUES"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETHARDIRONVALUESREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETHARDIRONVALUESREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETHARDIRONVALUESRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETHARDIRONVALUESRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetHardIronValuesRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetHardIronValuesRequest
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

(defclass microstrain_inertial_msgs::GetHardIronValuesResponse
  :super ros::object
  :slots (_bias _success ))

(defmethod microstrain_inertial_msgs::GetHardIronValuesResponse
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

(defclass microstrain_inertial_msgs::GetHardIronValues
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetHardIronValues :md5sum-) "9427c94a8464f80e7ccfb4c788698d94")
(setf (get microstrain_inertial_msgs::GetHardIronValues :datatype-) "microstrain_inertial_msgs/GetHardIronValues")
(setf (get microstrain_inertial_msgs::GetHardIronValues :request) microstrain_inertial_msgs::GetHardIronValuesRequest)
(setf (get microstrain_inertial_msgs::GetHardIronValues :response) microstrain_inertial_msgs::GetHardIronValuesResponse)

(defmethod microstrain_inertial_msgs::GetHardIronValuesRequest
  (:response () (instance microstrain_inertial_msgs::GetHardIronValuesResponse :init)))

(setf (get microstrain_inertial_msgs::GetHardIronValuesRequest :md5sum-) "9427c94a8464f80e7ccfb4c788698d94")
(setf (get microstrain_inertial_msgs::GetHardIronValuesRequest :datatype-) "microstrain_inertial_msgs/GetHardIronValuesRequest")
(setf (get microstrain_inertial_msgs::GetHardIronValuesRequest :definition-)
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

(setf (get microstrain_inertial_msgs::GetHardIronValuesResponse :md5sum-) "9427c94a8464f80e7ccfb4c788698d94")
(setf (get microstrain_inertial_msgs::GetHardIronValuesResponse :datatype-) "microstrain_inertial_msgs/GetHardIronValuesResponse")
(setf (get microstrain_inertial_msgs::GetHardIronValuesResponse :definition-)
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



(provide :microstrain_inertial_msgs/GetHardIronValues "9427c94a8464f80e7ccfb4c788698d94")


