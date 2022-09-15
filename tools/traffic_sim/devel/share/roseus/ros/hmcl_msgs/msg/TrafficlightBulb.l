;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::TrafficlightBulb)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'TrafficlightBulb (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::TRAFFICLIGHTBULB")
  (make-package "HMCL_MSGS::TRAFFICLIGHTBULB"))

(in-package "ROS")
;;//! \htmlinclude TrafficlightBulb.msg.html


(defclass hmcl_msgs::TrafficlightBulb
  :super ros::object
  :slots (_id _light_status ))

(defmethod hmcl_msgs::TrafficlightBulb
  (:init
   (&key
    ((:id __id) 0)
    ((:light_status __light_status) 0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _light_status (round __light_status))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:light_status
   (&optional __light_status)
   (if __light_status (setq _light_status __light_status)) _light_status)
  (:serialization-length
   ()
   (+
    ;; int32 _id
    4
    ;; int32 _light_status
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _id
       (write-long _id s)
     ;; int32 _light_status
       (write-long _light_status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _light_status
     (setq _light_status (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get hmcl_msgs::TrafficlightBulb :md5sum-) "29a65252a3c7d022a599aef3b93bd92c")
(setf (get hmcl_msgs::TrafficlightBulb :datatype-) "hmcl_msgs/TrafficlightBulb")
(setf (get hmcl_msgs::TrafficlightBulb :definition-)
      "int32 id
int32 light_status # 0 red, 1 green, 2 yellow 
")



(provide :hmcl_msgs/TrafficlightBulb "29a65252a3c7d022a599aef3b93bd92c")


