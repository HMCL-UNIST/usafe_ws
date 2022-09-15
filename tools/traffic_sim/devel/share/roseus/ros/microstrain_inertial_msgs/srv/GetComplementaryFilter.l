;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetComplementaryFilter)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetComplementaryFilter (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETCOMPLEMENTARYFILTER")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETCOMPLEMENTARYFILTER"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETCOMPLEMENTARYFILTERREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETCOMPLEMENTARYFILTERREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETCOMPLEMENTARYFILTERRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETCOMPLEMENTARYFILTERRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::GetComplementaryFilterRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetComplementaryFilterRequest
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

(defclass microstrain_inertial_msgs::GetComplementaryFilterResponse
  :super ros::object
  :slots (_north_comp_enable _up_comp_enable _north_comp_time_const _up_comp_time_const _success ))

(defmethod microstrain_inertial_msgs::GetComplementaryFilterResponse
  (:init
   (&key
    ((:north_comp_enable __north_comp_enable) 0)
    ((:up_comp_enable __up_comp_enable) 0)
    ((:north_comp_time_const __north_comp_time_const) 0.0)
    ((:up_comp_time_const __up_comp_time_const) 0.0)
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _north_comp_enable (round __north_comp_enable))
   (setq _up_comp_enable (round __up_comp_enable))
   (setq _north_comp_time_const (float __north_comp_time_const))
   (setq _up_comp_time_const (float __up_comp_time_const))
   (setq _success __success)
   self)
  (:north_comp_enable
   (&optional __north_comp_enable)
   (if __north_comp_enable (setq _north_comp_enable __north_comp_enable)) _north_comp_enable)
  (:up_comp_enable
   (&optional __up_comp_enable)
   (if __up_comp_enable (setq _up_comp_enable __up_comp_enable)) _up_comp_enable)
  (:north_comp_time_const
   (&optional __north_comp_time_const)
   (if __north_comp_time_const (setq _north_comp_time_const __north_comp_time_const)) _north_comp_time_const)
  (:up_comp_time_const
   (&optional __up_comp_time_const)
   (if __up_comp_time_const (setq _up_comp_time_const __up_comp_time_const)) _up_comp_time_const)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int8 _north_comp_enable
    1
    ;; int8 _up_comp_enable
    1
    ;; float32 _north_comp_time_const
    4
    ;; float32 _up_comp_time_const
    4
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _north_comp_enable
       (write-byte _north_comp_enable s)
     ;; int8 _up_comp_enable
       (write-byte _up_comp_enable s)
     ;; float32 _north_comp_time_const
       (sys::poke _north_comp_time_const (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _up_comp_time_const
       (sys::poke _up_comp_time_const (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _north_comp_enable
     (setq _north_comp_enable (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _north_comp_enable 127) (setq _north_comp_enable (- _north_comp_enable 256)))
   ;; int8 _up_comp_enable
     (setq _up_comp_enable (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _up_comp_enable 127) (setq _up_comp_enable (- _up_comp_enable 256)))
   ;; float32 _north_comp_time_const
     (setq _north_comp_time_const (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _up_comp_time_const
     (setq _up_comp_time_const (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetComplementaryFilter
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetComplementaryFilter :md5sum-) "182da770aa33d31e1eeca2d1e7ed5c19")
(setf (get microstrain_inertial_msgs::GetComplementaryFilter :datatype-) "microstrain_inertial_msgs/GetComplementaryFilter")
(setf (get microstrain_inertial_msgs::GetComplementaryFilter :request) microstrain_inertial_msgs::GetComplementaryFilterRequest)
(setf (get microstrain_inertial_msgs::GetComplementaryFilter :response) microstrain_inertial_msgs::GetComplementaryFilterResponse)

(defmethod microstrain_inertial_msgs::GetComplementaryFilterRequest
  (:response () (instance microstrain_inertial_msgs::GetComplementaryFilterResponse :init)))

(setf (get microstrain_inertial_msgs::GetComplementaryFilterRequest :md5sum-) "182da770aa33d31e1eeca2d1e7ed5c19")
(setf (get microstrain_inertial_msgs::GetComplementaryFilterRequest :datatype-) "microstrain_inertial_msgs/GetComplementaryFilterRequest")
(setf (get microstrain_inertial_msgs::GetComplementaryFilterRequest :definition-)
      "---
int8 north_comp_enable
int8 up_comp_enable
float32 north_comp_time_const
float32 up_comp_time_const
bool success

")

(setf (get microstrain_inertial_msgs::GetComplementaryFilterResponse :md5sum-) "182da770aa33d31e1eeca2d1e7ed5c19")
(setf (get microstrain_inertial_msgs::GetComplementaryFilterResponse :datatype-) "microstrain_inertial_msgs/GetComplementaryFilterResponse")
(setf (get microstrain_inertial_msgs::GetComplementaryFilterResponse :definition-)
      "---
int8 north_comp_enable
int8 up_comp_enable
float32 north_comp_time_const
float32 up_comp_time_const
bool success

")



(provide :microstrain_inertial_msgs/GetComplementaryFilter "182da770aa33d31e1eeca2d1e7ed5c19")


