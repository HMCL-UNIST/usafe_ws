;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::MissionWaypoint)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'MissionWaypoint (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::MISSIONWAYPOINT")
  (make-package "HMCL_MSGS::MISSIONWAYPOINT"))

(in-package "ROS")
;;//! \htmlinclude MissionWaypoint.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass hmcl_msgs::MissionWaypoint
  :super ros::object
  :slots (_start _end _remain ))

(defmethod hmcl_msgs::MissionWaypoint
  (:init
   (&key
    ((:start __start) (instance geometry_msgs::Point :init))
    ((:end __end) (instance geometry_msgs::Point :init))
    ((:remain __remain) 0)
    )
   (send-super :init)
   (setq _start __start)
   (setq _end __end)
   (setq _remain (round __remain))
   self)
  (:start
   (&rest __start)
   (if (keywordp (car __start))
       (send* _start __start)
     (progn
       (if __start (setq _start (car __start)))
       _start)))
  (:end
   (&rest __end)
   (if (keywordp (car __end))
       (send* _end __end)
     (progn
       (if __end (setq _end (car __end)))
       _end)))
  (:remain
   (&optional __remain)
   (if __remain (setq _remain __remain)) _remain)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _start
    (send _start :serialization-length)
    ;; geometry_msgs/Point _end
    (send _end :serialization-length)
    ;; int32 _remain
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _start
       (send _start :serialize s)
     ;; geometry_msgs/Point _end
       (send _end :serialize s)
     ;; int32 _remain
       (write-long _remain s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _start
     (send _start :deserialize buf ptr-) (incf ptr- (send _start :serialization-length))
   ;; geometry_msgs/Point _end
     (send _end :deserialize buf ptr-) (incf ptr- (send _end :serialization-length))
   ;; int32 _remain
     (setq _remain (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get hmcl_msgs::MissionWaypoint :md5sum-) "787e74dd4a3e0df7f1ef38d7abe84225")
(setf (get hmcl_msgs::MissionWaypoint :datatype-) "hmcl_msgs/MissionWaypoint")
(setf (get hmcl_msgs::MissionWaypoint :definition-)
      "# global id
geometry_msgs/Point start
geometry_msgs/Point end
int32 remain
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :hmcl_msgs/MissionWaypoint "787e74dd4a3e0df7f1ef38d7abe84225")


