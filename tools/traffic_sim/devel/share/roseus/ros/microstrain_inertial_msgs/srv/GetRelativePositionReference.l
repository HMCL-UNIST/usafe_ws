;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetRelativePositionReference)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetRelativePositionReference (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass microstrain_inertial_msgs::GetRelativePositionReferenceRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetRelativePositionReferenceRequest
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

(intern "*SOURCE_AUTO*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))
(shadow '*SOURCE_AUTO* (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))
(defconstant microstrain_inertial_msgs::GetRelativePositionReferenceResponse::*SOURCE_AUTO* 0)
(intern "*SOURCE_MANUAL*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))
(shadow '*SOURCE_MANUAL* (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))
(defconstant microstrain_inertial_msgs::GetRelativePositionReferenceResponse::*SOURCE_MANUAL* 1)
(intern "*FRAME_ECEF*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))
(shadow '*FRAME_ECEF* (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))
(defconstant microstrain_inertial_msgs::GetRelativePositionReferenceResponse::*FRAME_ECEF* 1)
(intern "*FRAME_LLH*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))
(shadow '*FRAME_LLH* (find-package "MICROSTRAIN_INERTIAL_MSGS::GETRELATIVEPOSITIONREFERENCERESPONSE"))
(defconstant microstrain_inertial_msgs::GetRelativePositionReferenceResponse::*FRAME_LLH* 2)
(defclass microstrain_inertial_msgs::GetRelativePositionReferenceResponse
  :super ros::object
  :slots (_source _frame _position _success ))

(defmethod microstrain_inertial_msgs::GetRelativePositionReferenceResponse
  (:init
   (&key
    ((:source __source) 0)
    ((:frame __frame) 0)
    ((:position __position) (instance geometry_msgs::Vector3 :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _source (round __source))
   (setq _frame (round __frame))
   (setq _position __position)
   (setq _success __success)
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
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; uint8 _source
    1
    ;; uint8 _frame
    1
    ;; geometry_msgs/Vector3 _position
    (send _position :serialization-length)
    ;; bool _success
    1
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
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
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
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetRelativePositionReference
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetRelativePositionReference :md5sum-) "7778d2daa4ab0de5ddac855cca257e01")
(setf (get microstrain_inertial_msgs::GetRelativePositionReference :datatype-) "microstrain_inertial_msgs/GetRelativePositionReference")
(setf (get microstrain_inertial_msgs::GetRelativePositionReference :request) microstrain_inertial_msgs::GetRelativePositionReferenceRequest)
(setf (get microstrain_inertial_msgs::GetRelativePositionReference :response) microstrain_inertial_msgs::GetRelativePositionReferenceResponse)

(defmethod microstrain_inertial_msgs::GetRelativePositionReferenceRequest
  (:response () (instance microstrain_inertial_msgs::GetRelativePositionReferenceResponse :init)))

(setf (get microstrain_inertial_msgs::GetRelativePositionReferenceRequest :md5sum-) "7778d2daa4ab0de5ddac855cca257e01")
(setf (get microstrain_inertial_msgs::GetRelativePositionReferenceRequest :datatype-) "microstrain_inertial_msgs/GetRelativePositionReferenceRequest")
(setf (get microstrain_inertial_msgs::GetRelativePositionReferenceRequest :definition-)
      "---
uint8  source
uint8  frame
geometry_msgs/Vector3 position
bool success

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
")

(setf (get microstrain_inertial_msgs::GetRelativePositionReferenceResponse :md5sum-) "7778d2daa4ab0de5ddac855cca257e01")
(setf (get microstrain_inertial_msgs::GetRelativePositionReferenceResponse :datatype-) "microstrain_inertial_msgs/GetRelativePositionReferenceResponse")
(setf (get microstrain_inertial_msgs::GetRelativePositionReferenceResponse :definition-)
      "---
uint8  source
uint8  frame
geometry_msgs/Vector3 position
bool success

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
")



(provide :microstrain_inertial_msgs/GetRelativePositionReference "7778d2daa4ab0de5ddac855cca257e01")


