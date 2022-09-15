;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetGyroBiasModel)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetGyroBiasModel (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETGYROBIASMODEL")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETGYROBIASMODEL"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETGYROBIASMODELREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETGYROBIASMODELREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETGYROBIASMODELRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETGYROBIASMODELRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetGyroBiasModelRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetGyroBiasModelRequest
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

(defclass microstrain_inertial_msgs::GetGyroBiasModelResponse
  :super ros::object
  :slots (_noise_vector _beta_vector _success ))

(defmethod microstrain_inertial_msgs::GetGyroBiasModelResponse
  (:init
   (&key
    ((:noise_vector __noise_vector) (instance geometry_msgs::Vector3 :init))
    ((:beta_vector __beta_vector) (instance geometry_msgs::Vector3 :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _noise_vector __noise_vector)
   (setq _beta_vector __beta_vector)
   (setq _success __success)
   self)
  (:noise_vector
   (&rest __noise_vector)
   (if (keywordp (car __noise_vector))
       (send* _noise_vector __noise_vector)
     (progn
       (if __noise_vector (setq _noise_vector (car __noise_vector)))
       _noise_vector)))
  (:beta_vector
   (&rest __beta_vector)
   (if (keywordp (car __beta_vector))
       (send* _beta_vector __beta_vector)
     (progn
       (if __beta_vector (setq _beta_vector (car __beta_vector)))
       _beta_vector)))
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Vector3 _noise_vector
    (send _noise_vector :serialization-length)
    ;; geometry_msgs/Vector3 _beta_vector
    (send _beta_vector :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Vector3 _noise_vector
       (send _noise_vector :serialize s)
     ;; geometry_msgs/Vector3 _beta_vector
       (send _beta_vector :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Vector3 _noise_vector
     (send _noise_vector :deserialize buf ptr-) (incf ptr- (send _noise_vector :serialization-length))
   ;; geometry_msgs/Vector3 _beta_vector
     (send _beta_vector :deserialize buf ptr-) (incf ptr- (send _beta_vector :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetGyroBiasModel
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetGyroBiasModel :md5sum-) "b507c17fd666c16c0721d62595a47085")
(setf (get microstrain_inertial_msgs::GetGyroBiasModel :datatype-) "microstrain_inertial_msgs/GetGyroBiasModel")
(setf (get microstrain_inertial_msgs::GetGyroBiasModel :request) microstrain_inertial_msgs::GetGyroBiasModelRequest)
(setf (get microstrain_inertial_msgs::GetGyroBiasModel :response) microstrain_inertial_msgs::GetGyroBiasModelResponse)

(defmethod microstrain_inertial_msgs::GetGyroBiasModelRequest
  (:response () (instance microstrain_inertial_msgs::GetGyroBiasModelResponse :init)))

(setf (get microstrain_inertial_msgs::GetGyroBiasModelRequest :md5sum-) "b507c17fd666c16c0721d62595a47085")
(setf (get microstrain_inertial_msgs::GetGyroBiasModelRequest :datatype-) "microstrain_inertial_msgs/GetGyroBiasModelRequest")
(setf (get microstrain_inertial_msgs::GetGyroBiasModelRequest :definition-)
      "---
geometry_msgs/Vector3 noise_vector
geometry_msgs/Vector3 beta_vector
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

(setf (get microstrain_inertial_msgs::GetGyroBiasModelResponse :md5sum-) "b507c17fd666c16c0721d62595a47085")
(setf (get microstrain_inertial_msgs::GetGyroBiasModelResponse :datatype-) "microstrain_inertial_msgs/GetGyroBiasModelResponse")
(setf (get microstrain_inertial_msgs::GetGyroBiasModelResponse :definition-)
      "---
geometry_msgs/Vector3 noise_vector
geometry_msgs/Vector3 beta_vector
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



(provide :microstrain_inertial_msgs/GetGyroBiasModel "b507c17fd666c16c0721d62595a47085")


