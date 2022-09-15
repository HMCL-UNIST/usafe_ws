;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetMagDipAdaptiveVals)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetMagDipAdaptiveVals (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETMAGDIPADAPTIVEVALS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETMAGDIPADAPTIVEVALS"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETMAGDIPADAPTIVEVALSREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETMAGDIPADAPTIVEVALSREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETMAGDIPADAPTIVEVALSRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETMAGDIPADAPTIVEVALSRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::SetMagDipAdaptiveValsRequest
  :super ros::object
  :slots (_enable _low_pass_cutoff _min_1sigma _high_limit _high_limit_1sigma ))

(defmethod microstrain_inertial_msgs::SetMagDipAdaptiveValsRequest
  (:init
   (&key
    ((:enable __enable) 0.0)
    ((:low_pass_cutoff __low_pass_cutoff) 0.0)
    ((:min_1sigma __min_1sigma) 0.0)
    ((:high_limit __high_limit) 0.0)
    ((:high_limit_1sigma __high_limit_1sigma) 0.0)
    )
   (send-super :init)
   (setq _enable (float __enable))
   (setq _low_pass_cutoff (float __low_pass_cutoff))
   (setq _min_1sigma (float __min_1sigma))
   (setq _high_limit (float __high_limit))
   (setq _high_limit_1sigma (float __high_limit_1sigma))
   self)
  (:enable
   (&optional __enable)
   (if __enable (setq _enable __enable)) _enable)
  (:low_pass_cutoff
   (&optional __low_pass_cutoff)
   (if __low_pass_cutoff (setq _low_pass_cutoff __low_pass_cutoff)) _low_pass_cutoff)
  (:min_1sigma
   (&optional __min_1sigma)
   (if __min_1sigma (setq _min_1sigma __min_1sigma)) _min_1sigma)
  (:high_limit
   (&optional __high_limit)
   (if __high_limit (setq _high_limit __high_limit)) _high_limit)
  (:high_limit_1sigma
   (&optional __high_limit_1sigma)
   (if __high_limit_1sigma (setq _high_limit_1sigma __high_limit_1sigma)) _high_limit_1sigma)
  (:serialization-length
   ()
   (+
    ;; float32 _enable
    4
    ;; float32 _low_pass_cutoff
    4
    ;; float32 _min_1sigma
    4
    ;; float32 _high_limit
    4
    ;; float32 _high_limit_1sigma
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _enable
       (sys::poke _enable (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _low_pass_cutoff
       (sys::poke _low_pass_cutoff (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _min_1sigma
       (sys::poke _min_1sigma (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _high_limit
       (sys::poke _high_limit (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _high_limit_1sigma
       (sys::poke _high_limit_1sigma (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _enable
     (setq _enable (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _low_pass_cutoff
     (setq _low_pass_cutoff (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _min_1sigma
     (setq _min_1sigma (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _high_limit
     (setq _high_limit (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _high_limit_1sigma
     (setq _high_limit_1sigma (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetMagDipAdaptiveValsResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetMagDipAdaptiveValsResponse
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

(defclass microstrain_inertial_msgs::SetMagDipAdaptiveVals
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveVals :md5sum-) "c71450f947e543c107e6e7b633ac2f16")
(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveVals :datatype-) "microstrain_inertial_msgs/SetMagDipAdaptiveVals")
(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveVals :request) microstrain_inertial_msgs::SetMagDipAdaptiveValsRequest)
(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveVals :response) microstrain_inertial_msgs::SetMagDipAdaptiveValsResponse)

(defmethod microstrain_inertial_msgs::SetMagDipAdaptiveValsRequest
  (:response () (instance microstrain_inertial_msgs::SetMagDipAdaptiveValsResponse :init)))

(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveValsRequest :md5sum-) "c71450f947e543c107e6e7b633ac2f16")
(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveValsRequest :datatype-) "microstrain_inertial_msgs/SetMagDipAdaptiveValsRequest")
(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveValsRequest :definition-)
      "float32 enable
float32 low_pass_cutoff
float32 min_1sigma
float32 high_limit
float32 high_limit_1sigma
---
bool success

")

(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveValsResponse :md5sum-) "c71450f947e543c107e6e7b633ac2f16")
(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveValsResponse :datatype-) "microstrain_inertial_msgs/SetMagDipAdaptiveValsResponse")
(setf (get microstrain_inertial_msgs::SetMagDipAdaptiveValsResponse :definition-)
      "float32 enable
float32 low_pass_cutoff
float32 min_1sigma
float32 high_limit
float32 high_limit_1sigma
---
bool success

")



(provide :microstrain_inertial_msgs/SetMagDipAdaptiveVals "c71450f947e543c107e6e7b633ac2f16")


