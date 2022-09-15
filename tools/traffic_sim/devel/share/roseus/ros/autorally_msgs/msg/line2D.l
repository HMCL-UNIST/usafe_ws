;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::line2D)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'line2D (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::LINE2D")
  (make-package "AUTORALLY_MSGS::LINE2D"))

(in-package "ROS")
;;//! \htmlinclude line2D.msg.html


(defclass autorally_msgs::line2D
  :super ros::object
  :slots (_start _end ))

(defmethod autorally_msgs::line2D
  (:init
   (&key
    ((:start __start) (instance autorally_msgs::point2D :init))
    ((:end __end) (instance autorally_msgs::point2D :init))
    )
   (send-super :init)
   (setq _start __start)
   (setq _end __end)
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
  (:serialization-length
   ()
   (+
    ;; autorally_msgs/point2D _start
    (send _start :serialization-length)
    ;; autorally_msgs/point2D _end
    (send _end :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; autorally_msgs/point2D _start
       (send _start :serialize s)
     ;; autorally_msgs/point2D _end
       (send _end :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; autorally_msgs/point2D _start
     (send _start :deserialize buf ptr-) (incf ptr- (send _start :serialization-length))
   ;; autorally_msgs/point2D _end
     (send _end :deserialize buf ptr-) (incf ptr- (send _end :serialization-length))
   ;;
   self)
  )

(setf (get autorally_msgs::line2D :md5sum-) "7a338da65a86a1f736887760a0feaccd")
(setf (get autorally_msgs::line2D :datatype-) "autorally_msgs/line2D")
(setf (get autorally_msgs::line2D :definition-)
      "point2D start
point2D end

================================================================================
MSG: autorally_msgs/point2D
uint16 x
uint16 y

")



(provide :autorally_msgs/line2D "7a338da65a86a1f736887760a0feaccd")


