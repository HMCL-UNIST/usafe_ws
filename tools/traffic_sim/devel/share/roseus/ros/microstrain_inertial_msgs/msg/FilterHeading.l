;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::FilterHeading)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'FilterHeading (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::FILTERHEADING")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::FILTERHEADING"))

(in-package "ROS")
;;//! \htmlinclude FilterHeading.msg.html


(defclass microstrain_inertial_msgs::FilterHeading
  :super ros::object
  :slots (_heading_deg _heading_rad _status_flags ))

(defmethod microstrain_inertial_msgs::FilterHeading
  (:init
   (&key
    ((:heading_deg __heading_deg) 0.0)
    ((:heading_rad __heading_rad) 0.0)
    ((:status_flags __status_flags) 0)
    )
   (send-super :init)
   (setq _heading_deg (float __heading_deg))
   (setq _heading_rad (float __heading_rad))
   (setq _status_flags (round __status_flags))
   self)
  (:heading_deg
   (&optional __heading_deg)
   (if __heading_deg (setq _heading_deg __heading_deg)) _heading_deg)
  (:heading_rad
   (&optional __heading_rad)
   (if __heading_rad (setq _heading_rad __heading_rad)) _heading_rad)
  (:status_flags
   (&optional __status_flags)
   (if __status_flags (setq _status_flags __status_flags)) _status_flags)
  (:serialization-length
   ()
   (+
    ;; float32 _heading_deg
    4
    ;; float32 _heading_rad
    4
    ;; uint16 _status_flags
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _heading_deg
       (sys::poke _heading_deg (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading_rad
       (sys::poke _heading_rad (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint16 _status_flags
       (write-word _status_flags s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _heading_deg
     (setq _heading_deg (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading_rad
     (setq _heading_rad (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint16 _status_flags
     (setq _status_flags (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::FilterHeading :md5sum-) "b90b446055a9cca548055d2a70764344")
(setf (get microstrain_inertial_msgs::FilterHeading :datatype-) "microstrain_inertial_msgs/FilterHeading")
(setf (get microstrain_inertial_msgs::FilterHeading :definition-)
      "float32 heading_deg

float32 heading_rad

uint16 status_flags

")



(provide :microstrain_inertial_msgs/FilterHeading "b90b446055a9cca548055d2a70764344")


