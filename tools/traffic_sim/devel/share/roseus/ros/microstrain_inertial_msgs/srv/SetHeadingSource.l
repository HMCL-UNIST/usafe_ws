;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::SetHeadingSource)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'SetHeadingSource (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETHEADINGSOURCE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETHEADINGSOURCE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETHEADINGSOURCEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETHEADINGSOURCEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::SETHEADINGSOURCERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::SETHEADINGSOURCERESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::SetHeadingSourceRequest
  :super ros::object
  :slots (_heading_source ))

(defmethod microstrain_inertial_msgs::SetHeadingSourceRequest
  (:init
   (&key
    ((:heading_source __heading_source) 0)
    )
   (send-super :init)
   (setq _heading_source (round __heading_source))
   self)
  (:heading_source
   (&optional __heading_source)
   (if __heading_source (setq _heading_source __heading_source)) _heading_source)
  (:serialization-length
   ()
   (+
    ;; int8 _heading_source
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _heading_source
       (write-byte _heading_source s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _heading_source
     (setq _heading_source (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _heading_source 127) (setq _heading_source (- _heading_source 256)))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::SetHeadingSourceResponse
  :super ros::object
  :slots (_success ))

(defmethod microstrain_inertial_msgs::SetHeadingSourceResponse
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

(defclass microstrain_inertial_msgs::SetHeadingSource
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::SetHeadingSource :md5sum-) "e390de146ace4f3cbedb9445dd2ef6f7")
(setf (get microstrain_inertial_msgs::SetHeadingSource :datatype-) "microstrain_inertial_msgs/SetHeadingSource")
(setf (get microstrain_inertial_msgs::SetHeadingSource :request) microstrain_inertial_msgs::SetHeadingSourceRequest)
(setf (get microstrain_inertial_msgs::SetHeadingSource :response) microstrain_inertial_msgs::SetHeadingSourceResponse)

(defmethod microstrain_inertial_msgs::SetHeadingSourceRequest
  (:response () (instance microstrain_inertial_msgs::SetHeadingSourceResponse :init)))

(setf (get microstrain_inertial_msgs::SetHeadingSourceRequest :md5sum-) "e390de146ace4f3cbedb9445dd2ef6f7")
(setf (get microstrain_inertial_msgs::SetHeadingSourceRequest :datatype-) "microstrain_inertial_msgs/SetHeadingSourceRequest")
(setf (get microstrain_inertial_msgs::SetHeadingSourceRequest :definition-)
      "int8 heading_source
---
bool success

")

(setf (get microstrain_inertial_msgs::SetHeadingSourceResponse :md5sum-) "e390de146ace4f3cbedb9445dd2ef6f7")
(setf (get microstrain_inertial_msgs::SetHeadingSourceResponse :datatype-) "microstrain_inertial_msgs/SetHeadingSourceResponse")
(setf (get microstrain_inertial_msgs::SetHeadingSourceResponse :definition-)
      "int8 heading_source
---
bool success

")



(provide :microstrain_inertial_msgs/SetHeadingSource "e390de146ace4f3cbedb9445dd2ef6f7")


