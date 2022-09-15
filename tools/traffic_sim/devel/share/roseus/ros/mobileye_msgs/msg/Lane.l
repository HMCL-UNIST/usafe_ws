;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::Lane)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'Lane (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::LANE")
  (make-package "MOBILEYE_MSGS::LANE"))

(in-package "ROS")
;;//! \htmlinclude Lane.msg.html


(defclass mobileye_msgs::Lane
  :super ros::object
  :slots (_lane_curvature _lane_heading _ca _pitch_angle _yaw_angle _right_ldw_availability _left_ldw_availability ))

(defmethod mobileye_msgs::Lane
  (:init
   (&key
    ((:lane_curvature __lane_curvature) 0.0)
    ((:lane_heading __lane_heading) 0.0)
    ((:ca __ca) nil)
    ((:pitch_angle __pitch_angle) 0.0)
    ((:yaw_angle __yaw_angle) 0.0)
    ((:right_ldw_availability __right_ldw_availability) nil)
    ((:left_ldw_availability __left_ldw_availability) nil)
    )
   (send-super :init)
   (setq _lane_curvature (float __lane_curvature))
   (setq _lane_heading (float __lane_heading))
   (setq _ca __ca)
   (setq _pitch_angle (float __pitch_angle))
   (setq _yaw_angle (float __yaw_angle))
   (setq _right_ldw_availability __right_ldw_availability)
   (setq _left_ldw_availability __left_ldw_availability)
   self)
  (:lane_curvature
   (&optional __lane_curvature)
   (if __lane_curvature (setq _lane_curvature __lane_curvature)) _lane_curvature)
  (:lane_heading
   (&optional __lane_heading)
   (if __lane_heading (setq _lane_heading __lane_heading)) _lane_heading)
  (:ca
   (&optional __ca)
   (if __ca (setq _ca __ca)) _ca)
  (:pitch_angle
   (&optional __pitch_angle)
   (if __pitch_angle (setq _pitch_angle __pitch_angle)) _pitch_angle)
  (:yaw_angle
   (&optional __yaw_angle)
   (if __yaw_angle (setq _yaw_angle __yaw_angle)) _yaw_angle)
  (:right_ldw_availability
   (&optional __right_ldw_availability)
   (if __right_ldw_availability (setq _right_ldw_availability __right_ldw_availability)) _right_ldw_availability)
  (:left_ldw_availability
   (&optional __left_ldw_availability)
   (if __left_ldw_availability (setq _left_ldw_availability __left_ldw_availability)) _left_ldw_availability)
  (:serialization-length
   ()
   (+
    ;; float32 _lane_curvature
    4
    ;; float32 _lane_heading
    4
    ;; bool _ca
    1
    ;; float32 _pitch_angle
    4
    ;; float32 _yaw_angle
    4
    ;; bool _right_ldw_availability
    1
    ;; bool _left_ldw_availability
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _lane_curvature
       (sys::poke _lane_curvature (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _lane_heading
       (sys::poke _lane_heading (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _ca
       (if _ca (write-byte -1 s) (write-byte 0 s))
     ;; float32 _pitch_angle
       (sys::poke _pitch_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw_angle
       (sys::poke _yaw_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _right_ldw_availability
       (if _right_ldw_availability (write-byte -1 s) (write-byte 0 s))
     ;; bool _left_ldw_availability
       (if _left_ldw_availability (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _lane_curvature
     (setq _lane_curvature (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _lane_heading
     (setq _lane_heading (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _ca
     (setq _ca (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _pitch_angle
     (setq _pitch_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw_angle
     (setq _yaw_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _right_ldw_availability
     (setq _right_ldw_availability (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _left_ldw_availability
     (setq _left_ldw_availability (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::Lane :md5sum-) "adf849929cf89885d76418e2f5f26f69")
(setf (get mobileye_msgs::Lane :datatype-) "mobileye_msgs/Lane")
(setf (get mobileye_msgs::Lane :definition-)
      "float32 lane_curvature
float32 lane_heading

bool ca
float32 pitch_angle
float32 yaw_angle

bool right_ldw_availability
bool left_ldw_availability

")



(provide :mobileye_msgs/Lane "adf849929cf89885d76418e2f5f26f69")


