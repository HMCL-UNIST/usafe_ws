;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::LKAlane)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'LKAlane (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::LKALANE")
  (make-package "MOBILEYE_MSGS::LKALANE"))

(in-package "ROS")
;;//! \htmlinclude LKAlane.msg.html


(defclass mobileye_msgs::LKAlane
  :super ros::object
  :slots (_lane_type _quality _model_degree _position_parameter_c0 _curvature_parameter_c2 _curvature_derivative_c3 _width_marking _heading_angle_parameter_c1 _view_range _view_range_availability ))

(defmethod mobileye_msgs::LKAlane
  (:init
   (&key
    ((:lane_type __lane_type) 0)
    ((:quality __quality) 0)
    ((:model_degree __model_degree) 0)
    ((:position_parameter_c0 __position_parameter_c0) 0.0)
    ((:curvature_parameter_c2 __curvature_parameter_c2) 0.0)
    ((:curvature_derivative_c3 __curvature_derivative_c3) 0.0)
    ((:width_marking __width_marking) 0.0)
    ((:heading_angle_parameter_c1 __heading_angle_parameter_c1) 0.0)
    ((:view_range __view_range) 0.0)
    ((:view_range_availability __view_range_availability) nil)
    )
   (send-super :init)
   (setq _lane_type (round __lane_type))
   (setq _quality (round __quality))
   (setq _model_degree (round __model_degree))
   (setq _position_parameter_c0 (float __position_parameter_c0))
   (setq _curvature_parameter_c2 (float __curvature_parameter_c2))
   (setq _curvature_derivative_c3 (float __curvature_derivative_c3))
   (setq _width_marking (float __width_marking))
   (setq _heading_angle_parameter_c1 (float __heading_angle_parameter_c1))
   (setq _view_range (float __view_range))
   (setq _view_range_availability __view_range_availability)
   self)
  (:lane_type
   (&optional __lane_type)
   (if __lane_type (setq _lane_type __lane_type)) _lane_type)
  (:quality
   (&optional __quality)
   (if __quality (setq _quality __quality)) _quality)
  (:model_degree
   (&optional __model_degree)
   (if __model_degree (setq _model_degree __model_degree)) _model_degree)
  (:position_parameter_c0
   (&optional __position_parameter_c0)
   (if __position_parameter_c0 (setq _position_parameter_c0 __position_parameter_c0)) _position_parameter_c0)
  (:curvature_parameter_c2
   (&optional __curvature_parameter_c2)
   (if __curvature_parameter_c2 (setq _curvature_parameter_c2 __curvature_parameter_c2)) _curvature_parameter_c2)
  (:curvature_derivative_c3
   (&optional __curvature_derivative_c3)
   (if __curvature_derivative_c3 (setq _curvature_derivative_c3 __curvature_derivative_c3)) _curvature_derivative_c3)
  (:width_marking
   (&optional __width_marking)
   (if __width_marking (setq _width_marking __width_marking)) _width_marking)
  (:heading_angle_parameter_c1
   (&optional __heading_angle_parameter_c1)
   (if __heading_angle_parameter_c1 (setq _heading_angle_parameter_c1 __heading_angle_parameter_c1)) _heading_angle_parameter_c1)
  (:view_range
   (&optional __view_range)
   (if __view_range (setq _view_range __view_range)) _view_range)
  (:view_range_availability
   (&optional __view_range_availability)
   (if __view_range_availability (setq _view_range_availability __view_range_availability)) _view_range_availability)
  (:serialization-length
   ()
   (+
    ;; uint8 _lane_type
    1
    ;; uint8 _quality
    1
    ;; uint8 _model_degree
    1
    ;; float32 _position_parameter_c0
    4
    ;; float32 _curvature_parameter_c2
    4
    ;; float32 _curvature_derivative_c3
    4
    ;; float32 _width_marking
    4
    ;; float32 _heading_angle_parameter_c1
    4
    ;; float32 _view_range
    4
    ;; bool _view_range_availability
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _lane_type
       (write-byte _lane_type s)
     ;; uint8 _quality
       (write-byte _quality s)
     ;; uint8 _model_degree
       (write-byte _model_degree s)
     ;; float32 _position_parameter_c0
       (sys::poke _position_parameter_c0 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _curvature_parameter_c2
       (sys::poke _curvature_parameter_c2 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _curvature_derivative_c3
       (sys::poke _curvature_derivative_c3 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _width_marking
       (sys::poke _width_marking (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading_angle_parameter_c1
       (sys::poke _heading_angle_parameter_c1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _view_range
       (sys::poke _view_range (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _view_range_availability
       (if _view_range_availability (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _lane_type
     (setq _lane_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _quality
     (setq _quality (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _model_degree
     (setq _model_degree (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _position_parameter_c0
     (setq _position_parameter_c0 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _curvature_parameter_c2
     (setq _curvature_parameter_c2 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _curvature_derivative_c3
     (setq _curvature_derivative_c3 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _width_marking
     (setq _width_marking (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading_angle_parameter_c1
     (setq _heading_angle_parameter_c1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _view_range
     (setq _view_range (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _view_range_availability
     (setq _view_range_availability (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::LKAlane :md5sum-) "7b414dd7d22f435b47d4035bf3d8fde4")
(setf (get mobileye_msgs::LKAlane :datatype-) "mobileye_msgs/LKAlane")
(setf (get mobileye_msgs::LKAlane :definition-)
      "uint8 lane_type
uint8 quality
uint8 model_degree

float32 position_parameter_c0
float32 curvature_parameter_c2
float32 curvature_derivative_c3
float32 width_marking

float32 heading_angle_parameter_c1
float32 view_range
bool view_range_availability

")



(provide :mobileye_msgs/LKAlane "7b414dd7d22f435b47d4035bf3d8fde4")


