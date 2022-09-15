;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::TSR)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'TSR (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::TSR")
  (make-package "MOBILEYE_MSGS::TSR"))

(in-package "ROS")
;;//! \htmlinclude TSR.msg.html


(defclass mobileye_msgs::TSR
  :super ros::object
  :slots (_vision_only_sign_type _supplementary_sign_type _sign_position_x _sign_position_y _sign_position_z _filter_type ))

(defmethod mobileye_msgs::TSR
  (:init
   (&key
    ((:vision_only_sign_type __vision_only_sign_type) 0)
    ((:supplementary_sign_type __supplementary_sign_type) 0)
    ((:sign_position_x __sign_position_x) 0.0)
    ((:sign_position_y __sign_position_y) 0.0)
    ((:sign_position_z __sign_position_z) 0.0)
    ((:filter_type __filter_type) 0)
    )
   (send-super :init)
   (setq _vision_only_sign_type (round __vision_only_sign_type))
   (setq _supplementary_sign_type (round __supplementary_sign_type))
   (setq _sign_position_x (float __sign_position_x))
   (setq _sign_position_y (float __sign_position_y))
   (setq _sign_position_z (float __sign_position_z))
   (setq _filter_type (round __filter_type))
   self)
  (:vision_only_sign_type
   (&optional __vision_only_sign_type)
   (if __vision_only_sign_type (setq _vision_only_sign_type __vision_only_sign_type)) _vision_only_sign_type)
  (:supplementary_sign_type
   (&optional __supplementary_sign_type)
   (if __supplementary_sign_type (setq _supplementary_sign_type __supplementary_sign_type)) _supplementary_sign_type)
  (:sign_position_x
   (&optional __sign_position_x)
   (if __sign_position_x (setq _sign_position_x __sign_position_x)) _sign_position_x)
  (:sign_position_y
   (&optional __sign_position_y)
   (if __sign_position_y (setq _sign_position_y __sign_position_y)) _sign_position_y)
  (:sign_position_z
   (&optional __sign_position_z)
   (if __sign_position_z (setq _sign_position_z __sign_position_z)) _sign_position_z)
  (:filter_type
   (&optional __filter_type)
   (if __filter_type (setq _filter_type __filter_type)) _filter_type)
  (:serialization-length
   ()
   (+
    ;; uint8 _vision_only_sign_type
    1
    ;; uint8 _supplementary_sign_type
    1
    ;; float32 _sign_position_x
    4
    ;; float32 _sign_position_y
    4
    ;; float32 _sign_position_z
    4
    ;; uint8 _filter_type
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _vision_only_sign_type
       (write-byte _vision_only_sign_type s)
     ;; uint8 _supplementary_sign_type
       (write-byte _supplementary_sign_type s)
     ;; float32 _sign_position_x
       (sys::poke _sign_position_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _sign_position_y
       (sys::poke _sign_position_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _sign_position_z
       (sys::poke _sign_position_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _filter_type
       (write-byte _filter_type s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _vision_only_sign_type
     (setq _vision_only_sign_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _supplementary_sign_type
     (setq _supplementary_sign_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _sign_position_x
     (setq _sign_position_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _sign_position_y
     (setq _sign_position_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _sign_position_z
     (setq _sign_position_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _filter_type
     (setq _filter_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::TSR :md5sum-) "3b21293c7f6ed978e4a364de1d436a9c")
(setf (get mobileye_msgs::TSR :datatype-) "mobileye_msgs/TSR")
(setf (get mobileye_msgs::TSR :definition-)
      "uint8 vision_only_sign_type
uint8 supplementary_sign_type
float32 sign_position_x
float32 sign_position_y
float32 sign_position_z
uint8 filter_type
")



(provide :mobileye_msgs/TSR "3b21293c7f6ed978e4a364de1d436a9c")


