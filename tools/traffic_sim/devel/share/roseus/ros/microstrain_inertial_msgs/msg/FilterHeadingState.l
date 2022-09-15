;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::FilterHeadingState)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'FilterHeadingState (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::FILTERHEADINGSTATE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::FILTERHEADINGSTATE"))

(in-package "ROS")
;;//! \htmlinclude FilterHeadingState.msg.html


(defclass microstrain_inertial_msgs::FilterHeadingState
  :super ros::object
  :slots (_heading_rad _heading_uncertainty _source _status_flags ))

(defmethod microstrain_inertial_msgs::FilterHeadingState
  (:init
   (&key
    ((:heading_rad __heading_rad) 0.0)
    ((:heading_uncertainty __heading_uncertainty) 0.0)
    ((:source __source) 0)
    ((:status_flags __status_flags) 0)
    )
   (send-super :init)
   (setq _heading_rad (float __heading_rad))
   (setq _heading_uncertainty (float __heading_uncertainty))
   (setq _source (round __source))
   (setq _status_flags (round __status_flags))
   self)
  (:heading_rad
   (&optional __heading_rad)
   (if __heading_rad (setq _heading_rad __heading_rad)) _heading_rad)
  (:heading_uncertainty
   (&optional __heading_uncertainty)
   (if __heading_uncertainty (setq _heading_uncertainty __heading_uncertainty)) _heading_uncertainty)
  (:source
   (&optional __source)
   (if __source (setq _source __source)) _source)
  (:status_flags
   (&optional __status_flags)
   (if __status_flags (setq _status_flags __status_flags)) _status_flags)
  (:serialization-length
   ()
   (+
    ;; float32 _heading_rad
    4
    ;; float32 _heading_uncertainty
    4
    ;; uint16 _source
    2
    ;; uint16 _status_flags
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _heading_rad
       (sys::poke _heading_rad (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading_uncertainty
       (sys::poke _heading_uncertainty (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint16 _source
       (write-word _source s)
     ;; uint16 _status_flags
       (write-word _status_flags s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _heading_rad
     (setq _heading_rad (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading_uncertainty
     (setq _heading_uncertainty (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint16 _source
     (setq _source (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _status_flags
     (setq _status_flags (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::FilterHeadingState :md5sum-) "ca75e8c156e8551037af1d0f6d896ef2")
(setf (get microstrain_inertial_msgs::FilterHeadingState :datatype-) "microstrain_inertial_msgs/FilterHeadingState")
(setf (get microstrain_inertial_msgs::FilterHeadingState :definition-)
      "float32 heading_rad

float32 heading_uncertainty

uint16 source

uint16 status_flags

")



(provide :microstrain_inertial_msgs/FilterHeadingState "ca75e8c156e8551037af1d0f6d896ef2")


