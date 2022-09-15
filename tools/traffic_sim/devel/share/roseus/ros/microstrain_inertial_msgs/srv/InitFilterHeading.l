;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::InitFilterHeading)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'InitFilterHeading (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::INITFILTERHEADING")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::INITFILTERHEADING"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::INITFILTERHEADINGREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::INITFILTERHEADINGREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::INITFILTERHEADINGRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::INITFILTERHEADINGRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::InitFilterHeadingRequest
  :super ros::object
  :slots (_angle ))

(defmethod microstrain_inertial_msgs::InitFilterHeadingRequest
  (:init
   (&key
    ((:angle __angle) 0.0)
    )
   (send-super :init)
   (setq _angle (float __angle))
   self)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:serialization-length
   ()
   (+
    ;; float32 _angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _angle
       (sys::poke _angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _angle
     (setq _angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::InitFilterHeadingResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::InitFilterHeadingResponse
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

(defclass microstrain_inertial_msgs::InitFilterHeading
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::InitFilterHeading :md5sum-) "194939c001a63802dc4131cae92cda22")
(setf (get microstrain_inertial_msgs::InitFilterHeading :datatype-) "microstrain_inertial_msgs/InitFilterHeading")
(setf (get microstrain_inertial_msgs::InitFilterHeading :request) microstrain_inertial_msgs::InitFilterHeadingRequest)
(setf (get microstrain_inertial_msgs::InitFilterHeading :response) microstrain_inertial_msgs::InitFilterHeadingResponse)

(defmethod microstrain_inertial_msgs::InitFilterHeadingRequest
  (:response () (instance microstrain_inertial_msgs::InitFilterHeadingResponse :init)))

(setf (get microstrain_inertial_msgs::InitFilterHeadingRequest :md5sum-) "194939c001a63802dc4131cae92cda22")
(setf (get microstrain_inertial_msgs::InitFilterHeadingRequest :datatype-) "microstrain_inertial_msgs/InitFilterHeadingRequest")
(setf (get microstrain_inertial_msgs::InitFilterHeadingRequest :definition-)
      "float32 angle
---
bool success

")

(setf (get microstrain_inertial_msgs::InitFilterHeadingResponse :md5sum-) "194939c001a63802dc4131cae92cda22")
(setf (get microstrain_inertial_msgs::InitFilterHeadingResponse :datatype-) "microstrain_inertial_msgs/InitFilterHeadingResponse")
(setf (get microstrain_inertial_msgs::InitFilterHeadingResponse :definition-)
      "float32 angle
---
bool success

")



(provide :microstrain_inertial_msgs/InitFilterHeading "194939c001a63802dc4131cae92cda22")


