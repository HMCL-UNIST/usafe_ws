;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::point2D)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'point2D (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::POINT2D")
  (make-package "AUTORALLY_MSGS::POINT2D"))

(in-package "ROS")
;;//! \htmlinclude point2D.msg.html


(defclass autorally_msgs::point2D
  :super ros::object
  :slots (_x _y ))

(defmethod autorally_msgs::point2D
  (:init
   (&key
    ((:x __x) 0)
    ((:y __y) 0)
    )
   (send-super :init)
   (setq _x (round __x))
   (setq _y (round __y))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:serialization-length
   ()
   (+
    ;; uint16 _x
    2
    ;; uint16 _y
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _x
       (write-word _x s)
     ;; uint16 _y
       (write-word _y s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _x
     (setq _x (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _y
     (setq _y (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get autorally_msgs::point2D :md5sum-) "2b80853b9dd76da1c3efb4dbc2426fe9")
(setf (get autorally_msgs::point2D :datatype-) "autorally_msgs/point2D")
(setf (get autorally_msgs::point2D :definition-)
      "uint16 x
uint16 y

")



(provide :autorally_msgs/point2D "2b80853b9dd76da1c3efb4dbc2426fe9")


