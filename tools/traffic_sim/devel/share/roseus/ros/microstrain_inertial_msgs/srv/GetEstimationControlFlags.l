;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetEstimationControlFlags)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetEstimationControlFlags (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETESTIMATIONCONTROLFLAGS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETESTIMATIONCONTROLFLAGS"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETESTIMATIONCONTROLFLAGSREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETESTIMATIONCONTROLFLAGSREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETESTIMATIONCONTROLFLAGSRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETESTIMATIONCONTROLFLAGSRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::GetEstimationControlFlagsRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetEstimationControlFlagsRequest
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

(defclass microstrain_inertial_msgs::GetEstimationControlFlagsResponse
  :super ros::object
  :slots (_flags _success ))

(defmethod microstrain_inertial_msgs::GetEstimationControlFlagsResponse
  (:init
   (&key
    ((:flags __flags) 0)
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _flags (round __flags))
   (setq _success __success)
   self)
  (:flags
   (&optional __flags)
   (if __flags (setq _flags __flags)) _flags)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int8 _flags
    1
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _flags
       (write-byte _flags s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _flags
     (setq _flags (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _flags 127) (setq _flags (- _flags 256)))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetEstimationControlFlags
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetEstimationControlFlags :md5sum-) "20bb471857675e9f69991d48317a4755")
(setf (get microstrain_inertial_msgs::GetEstimationControlFlags :datatype-) "microstrain_inertial_msgs/GetEstimationControlFlags")
(setf (get microstrain_inertial_msgs::GetEstimationControlFlags :request) microstrain_inertial_msgs::GetEstimationControlFlagsRequest)
(setf (get microstrain_inertial_msgs::GetEstimationControlFlags :response) microstrain_inertial_msgs::GetEstimationControlFlagsResponse)

(defmethod microstrain_inertial_msgs::GetEstimationControlFlagsRequest
  (:response () (instance microstrain_inertial_msgs::GetEstimationControlFlagsResponse :init)))

(setf (get microstrain_inertial_msgs::GetEstimationControlFlagsRequest :md5sum-) "20bb471857675e9f69991d48317a4755")
(setf (get microstrain_inertial_msgs::GetEstimationControlFlagsRequest :datatype-) "microstrain_inertial_msgs/GetEstimationControlFlagsRequest")
(setf (get microstrain_inertial_msgs::GetEstimationControlFlagsRequest :definition-)
      "---
int8 flags
bool success

")

(setf (get microstrain_inertial_msgs::GetEstimationControlFlagsResponse :md5sum-) "20bb471857675e9f69991d48317a4755")
(setf (get microstrain_inertial_msgs::GetEstimationControlFlagsResponse :datatype-) "microstrain_inertial_msgs/GetEstimationControlFlagsResponse")
(setf (get microstrain_inertial_msgs::GetEstimationControlFlagsResponse :definition-)
      "---
int8 flags
bool success

")



(provide :microstrain_inertial_msgs/GetEstimationControlFlags "20bb471857675e9f69991d48317a4755")


