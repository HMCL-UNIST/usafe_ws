;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetRelativePositionReference)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetRelativePositionReference (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCERESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(intern "*SOURCE_AUTO*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(shadow '*SOURCE_AUTO* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(defconstant microstrain_inertial_msgs::SetRelativePositionReferenceRequest::*SOURCE_AUTO* 0)
(intern "*SOURCE_MANUAL*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(shadow '*SOURCE_MANUAL* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(defconstant microstrain_inertial_msgs::SetRelativePositionReferenceRequest::*SOURCE_MANUAL* 1)
(intern "*FRAME_ECEF*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(shadow '*FRAME_ECEF* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(defconstant microstrain_inertial_msgs::SetRelativePositionReferenceRequest::*FRAME_ECEF* 1)
(intern "*FRAME_LLH*" (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(shadow '*FRAME_LLH* (find-package "MICROSTRAIN_INERTIAL_MSGS::SETRELATIVEPOSITIONREFERENCEREQUEST"))
(defconstant microstrain_inertial_msgs::SetRelativePositionReferenceRequest::*FRAME_LLH* 2)
(defclass microstrain_inertial_msgs::SetRelativePositionReferenceRequest
  :super ros::object
  :slots (_source _frame _position ))

(defmethod microstrain_inertial_msgs::SetRelativePositionReferenceRequest
  (:init
   (&key
    ((:source __source) 0)
    ((:frame __frame) 0)
    ((:position __position) (instance geometry_msgs::Vector3 :init))
    )
   (send-super :init)
   (setq _source (round __source))
   (setq _frame (round __frame))
   (setq _position __position)
   self)
  (:source
   (&optional __source)
   (if __source (setq _source __source)) _source)
  (:frame
   (&optional __frame)
   (if __frame (setq _frame __frame)) _frame)
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
    ;; uint8 _source
    1
    ;; uint8 _frame
    1
    ;; geometry_msgs/Vector3 _position
    (send _position :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _source
       (write-byte _source s)
     ;; uint8 _frame
       (write-byte _frame s)
     ;; geometry_msgs/Vector3 _position
       (send _position :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _source
     (setq _source (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _frame
     (setq _frame (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; geometry_msgs/Vector3 _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetRelativePositionReferenceResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetRelativePositionReferenceResponse
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

(defclass microstrain_inertial_msgs::SetRelativePositionReference
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetRelativePositionReference :md5sum-) "322dca82c4e06e7f4805393b2e113aed")
(setf (get microstrain_inertial_msgs::SetRelativePositionReference :datatype-) "microstrain_inertial_msgs/SetRelativePositionReference")
(setf (get microstrain_inertial_msgs::SetRelativePositionReference :request) microstrain_inertial_msgs::SetRelativePositionReferenceRequest)
(setf (get microstrain_inertial_msgs::SetRelativePositionReference :response) microstrain_inertial_msgs::SetRelativePositionReferenceResponse)

(defmethod microstrain_inertial_msgs::SetRelativePositionReferenceRequest
  (:response () (instance microstrain_inertial_msgs::SetRelativePositionReferenceResponse :init)))

(setf (get microstrain_inertial_msgs::SetRelativePositionReferenceRequest :md5sum-) "322dca82c4e06e7f4805393b2e113aed")
(setf (get microstrain_inertial_msgs::SetRelativePositionReferenceRequest :datatype-) "microstrain_inertial_msgs/SetRelativePositionReferenceRequest")
(setf (get microstrain_inertial_msgs::SetRelativePositionReferenceRequest :definition-)
      "uint8  source
uint8  frame
geometry_msgs/Vector3 position

uint8 SOURCE_AUTO   = 0  #RTK base station required
uint8 SOURCE_MANUAL = 1  
uint8 FRAME_ECEF = 1  
uint8 FRAME_LLH  = 2  

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

(setf (get microstrain_inertial_msgs::SetRelativePositionReferenceResponse :md5sum-) "322dca82c4e06e7f4805393b2e113aed")
(setf (get microstrain_inertial_msgs::SetRelativePositionReferenceResponse :datatype-) "microstrain_inertial_msgs/SetRelativePositionReferenceResponse")
(setf (get microstrain_inertial_msgs::SetRelativePositionReferenceResponse :definition-)
      "uint8  source
uint8  frame
geometry_msgs/Vector3 position

uint8 SOURCE_AUTO   = 0  #RTK base station required
uint8 SOURCE_MANUAL = 1  
uint8 FRAME_ECEF = 1  
uint8 FRAME_LLH  = 2  

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



(provide :microstrain_inertial_msgs/SetRelativePositionReference "322dca82c4e06e7f4805393b2e113aed")


