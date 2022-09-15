;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::FilterStatus)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'FilterStatus (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::FILTERSTATUS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::FILTERSTATUS"))

(in-package "ROS")
;;//! \htmlinclude FilterStatus.msg.html


(defclass microstrain_inertial_msgs::FilterStatus
  :super ros::object
  :slots (_filter_state _dynamics_mode _status_flags ))

(defmethod microstrain_inertial_msgs::FilterStatus
  (:init
   (&key
    ((:filter_state __filter_state) 0)
    ((:dynamics_mode __dynamics_mode) 0)
    ((:status_flags __status_flags) 0)
    )
   (send-super :init)
   (setq _filter_state (round __filter_state))
   (setq _dynamics_mode (round __dynamics_mode))
   (setq _status_flags (round __status_flags))
   self)
  (:filter_state
   (&optional __filter_state)
   (if __filter_state (setq _filter_state __filter_state)) _filter_state)
  (:dynamics_mode
   (&optional __dynamics_mode)
   (if __dynamics_mode (setq _dynamics_mode __dynamics_mode)) _dynamics_mode)
  (:status_flags
   (&optional __status_flags)
   (if __status_flags (setq _status_flags __status_flags)) _status_flags)
  (:serialization-length
   ()
   (+
    ;; uint16 _filter_state
    2
    ;; uint16 _dynamics_mode
    2
    ;; uint16 _status_flags
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _filter_state
       (write-word _filter_state s)
     ;; uint16 _dynamics_mode
       (write-word _dynamics_mode s)
     ;; uint16 _status_flags
       (write-word _status_flags s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _filter_state
     (setq _filter_state (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _dynamics_mode
     (setq _dynamics_mode (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _status_flags
     (setq _status_flags (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::FilterStatus :md5sum-) "44b6cdd5e336c9a880e785b76ea6be97")
(setf (get microstrain_inertial_msgs::FilterStatus :datatype-) "microstrain_inertial_msgs/FilterStatus")
(setf (get microstrain_inertial_msgs::FilterStatus :definition-)
      "uint16 filter_state

uint16 dynamics_mode

uint16 status_flags

")



(provide :microstrain_inertial_msgs/FilterStatus "44b6cdd5e336c9a880e785b76ea6be97")


