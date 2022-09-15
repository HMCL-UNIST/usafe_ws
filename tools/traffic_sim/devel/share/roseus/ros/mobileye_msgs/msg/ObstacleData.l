;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::ObstacleData)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'ObstacleData (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::OBSTACLEDATA")
  (make-package "MOBILEYE_MSGS::OBSTACLEDATA"))

(in-package "ROS")
;;//! \htmlinclude ObstacleData.msg.html


(defclass mobileye_msgs::ObstacleData
  :super ros::object
  :slots (_obstacle_id _obstacle_position_x _obstacle_position_y _obstacle_relative_velocity_x _obstacle_type _obstacle_status _obstacle_brake_lights _cut_in_and_out _blinker_info _obstacle_valid _obstacle_length _obstacle_width _obstacle_age _obstacle_lane _cipv_flag _radar_position_x _radar_velocity_x _radar_match_confidence _matched_radar_id _obstacle_angle_rate _obstacle_scale_change _obstacle_object_accel_x _obstacle_replaced _obstacle_angle ))

(defmethod mobileye_msgs::ObstacleData
  (:init
   (&key
    ((:obstacle_id __obstacle_id) 0)
    ((:obstacle_position_x __obstacle_position_x) 0.0)
    ((:obstacle_position_y __obstacle_position_y) 0.0)
    ((:obstacle_relative_velocity_x __obstacle_relative_velocity_x) 0.0)
    ((:obstacle_type __obstacle_type) 0)
    ((:obstacle_status __obstacle_status) 0)
    ((:obstacle_brake_lights __obstacle_brake_lights) nil)
    ((:cut_in_and_out __cut_in_and_out) 0)
    ((:blinker_info __blinker_info) 0)
    ((:obstacle_valid __obstacle_valid) 0)
    ((:obstacle_length __obstacle_length) 0.0)
    ((:obstacle_width __obstacle_width) 0.0)
    ((:obstacle_age __obstacle_age) 0)
    ((:obstacle_lane __obstacle_lane) 0)
    ((:cipv_flag __cipv_flag) 0)
    ((:radar_position_x __radar_position_x) 0.0)
    ((:radar_velocity_x __radar_velocity_x) 0.0)
    ((:radar_match_confidence __radar_match_confidence) 0)
    ((:matched_radar_id __matched_radar_id) 0)
    ((:obstacle_angle_rate __obstacle_angle_rate) 0.0)
    ((:obstacle_scale_change __obstacle_scale_change) 0.0)
    ((:obstacle_object_accel_x __obstacle_object_accel_x) 0.0)
    ((:obstacle_replaced __obstacle_replaced) nil)
    ((:obstacle_angle __obstacle_angle) 0.0)
    )
   (send-super :init)
   (setq _obstacle_id (round __obstacle_id))
   (setq _obstacle_position_x (float __obstacle_position_x))
   (setq _obstacle_position_y (float __obstacle_position_y))
   (setq _obstacle_relative_velocity_x (float __obstacle_relative_velocity_x))
   (setq _obstacle_type (round __obstacle_type))
   (setq _obstacle_status (round __obstacle_status))
   (setq _obstacle_brake_lights __obstacle_brake_lights)
   (setq _cut_in_and_out (round __cut_in_and_out))
   (setq _blinker_info (round __blinker_info))
   (setq _obstacle_valid (round __obstacle_valid))
   (setq _obstacle_length (float __obstacle_length))
   (setq _obstacle_width (float __obstacle_width))
   (setq _obstacle_age (round __obstacle_age))
   (setq _obstacle_lane (round __obstacle_lane))
   (setq _cipv_flag (round __cipv_flag))
   (setq _radar_position_x (float __radar_position_x))
   (setq _radar_velocity_x (float __radar_velocity_x))
   (setq _radar_match_confidence (round __radar_match_confidence))
   (setq _matched_radar_id (round __matched_radar_id))
   (setq _obstacle_angle_rate (float __obstacle_angle_rate))
   (setq _obstacle_scale_change (float __obstacle_scale_change))
   (setq _obstacle_object_accel_x (float __obstacle_object_accel_x))
   (setq _obstacle_replaced __obstacle_replaced)
   (setq _obstacle_angle (float __obstacle_angle))
   self)
  (:obstacle_id
   (&optional __obstacle_id)
   (if __obstacle_id (setq _obstacle_id __obstacle_id)) _obstacle_id)
  (:obstacle_position_x
   (&optional __obstacle_position_x)
   (if __obstacle_position_x (setq _obstacle_position_x __obstacle_position_x)) _obstacle_position_x)
  (:obstacle_position_y
   (&optional __obstacle_position_y)
   (if __obstacle_position_y (setq _obstacle_position_y __obstacle_position_y)) _obstacle_position_y)
  (:obstacle_relative_velocity_x
   (&optional __obstacle_relative_velocity_x)
   (if __obstacle_relative_velocity_x (setq _obstacle_relative_velocity_x __obstacle_relative_velocity_x)) _obstacle_relative_velocity_x)
  (:obstacle_type
   (&optional __obstacle_type)
   (if __obstacle_type (setq _obstacle_type __obstacle_type)) _obstacle_type)
  (:obstacle_status
   (&optional __obstacle_status)
   (if __obstacle_status (setq _obstacle_status __obstacle_status)) _obstacle_status)
  (:obstacle_brake_lights
   (&optional __obstacle_brake_lights)
   (if __obstacle_brake_lights (setq _obstacle_brake_lights __obstacle_brake_lights)) _obstacle_brake_lights)
  (:cut_in_and_out
   (&optional __cut_in_and_out)
   (if __cut_in_and_out (setq _cut_in_and_out __cut_in_and_out)) _cut_in_and_out)
  (:blinker_info
   (&optional __blinker_info)
   (if __blinker_info (setq _blinker_info __blinker_info)) _blinker_info)
  (:obstacle_valid
   (&optional __obstacle_valid)
   (if __obstacle_valid (setq _obstacle_valid __obstacle_valid)) _obstacle_valid)
  (:obstacle_length
   (&optional __obstacle_length)
   (if __obstacle_length (setq _obstacle_length __obstacle_length)) _obstacle_length)
  (:obstacle_width
   (&optional __obstacle_width)
   (if __obstacle_width (setq _obstacle_width __obstacle_width)) _obstacle_width)
  (:obstacle_age
   (&optional __obstacle_age)
   (if __obstacle_age (setq _obstacle_age __obstacle_age)) _obstacle_age)
  (:obstacle_lane
   (&optional __obstacle_lane)
   (if __obstacle_lane (setq _obstacle_lane __obstacle_lane)) _obstacle_lane)
  (:cipv_flag
   (&optional __cipv_flag)
   (if __cipv_flag (setq _cipv_flag __cipv_flag)) _cipv_flag)
  (:radar_position_x
   (&optional __radar_position_x)
   (if __radar_position_x (setq _radar_position_x __radar_position_x)) _radar_position_x)
  (:radar_velocity_x
   (&optional __radar_velocity_x)
   (if __radar_velocity_x (setq _radar_velocity_x __radar_velocity_x)) _radar_velocity_x)
  (:radar_match_confidence
   (&optional __radar_match_confidence)
   (if __radar_match_confidence (setq _radar_match_confidence __radar_match_confidence)) _radar_match_confidence)
  (:matched_radar_id
   (&optional __matched_radar_id)
   (if __matched_radar_id (setq _matched_radar_id __matched_radar_id)) _matched_radar_id)
  (:obstacle_angle_rate
   (&optional __obstacle_angle_rate)
   (if __obstacle_angle_rate (setq _obstacle_angle_rate __obstacle_angle_rate)) _obstacle_angle_rate)
  (:obstacle_scale_change
   (&optional __obstacle_scale_change)
   (if __obstacle_scale_change (setq _obstacle_scale_change __obstacle_scale_change)) _obstacle_scale_change)
  (:obstacle_object_accel_x
   (&optional __obstacle_object_accel_x)
   (if __obstacle_object_accel_x (setq _obstacle_object_accel_x __obstacle_object_accel_x)) _obstacle_object_accel_x)
  (:obstacle_replaced
   (&optional __obstacle_replaced)
   (if __obstacle_replaced (setq _obstacle_replaced __obstacle_replaced)) _obstacle_replaced)
  (:obstacle_angle
   (&optional __obstacle_angle)
   (if __obstacle_angle (setq _obstacle_angle __obstacle_angle)) _obstacle_angle)
  (:serialization-length
   ()
   (+
    ;; uint8 _obstacle_id
    1
    ;; float32 _obstacle_position_x
    4
    ;; float32 _obstacle_position_y
    4
    ;; float32 _obstacle_relative_velocity_x
    4
    ;; uint8 _obstacle_type
    1
    ;; uint8 _obstacle_status
    1
    ;; bool _obstacle_brake_lights
    1
    ;; uint8 _cut_in_and_out
    1
    ;; uint8 _blinker_info
    1
    ;; uint8 _obstacle_valid
    1
    ;; float32 _obstacle_length
    4
    ;; float32 _obstacle_width
    4
    ;; uint8 _obstacle_age
    1
    ;; uint8 _obstacle_lane
    1
    ;; uint8 _cipv_flag
    1
    ;; float32 _radar_position_x
    4
    ;; float32 _radar_velocity_x
    4
    ;; uint8 _radar_match_confidence
    1
    ;; uint8 _matched_radar_id
    1
    ;; float32 _obstacle_angle_rate
    4
    ;; float32 _obstacle_scale_change
    4
    ;; float32 _obstacle_object_accel_x
    4
    ;; bool _obstacle_replaced
    1
    ;; float32 _obstacle_angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _obstacle_id
       (write-byte _obstacle_id s)
     ;; float32 _obstacle_position_x
       (sys::poke _obstacle_position_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _obstacle_position_y
       (sys::poke _obstacle_position_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _obstacle_relative_velocity_x
       (sys::poke _obstacle_relative_velocity_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _obstacle_type
       (write-byte _obstacle_type s)
     ;; uint8 _obstacle_status
       (write-byte _obstacle_status s)
     ;; bool _obstacle_brake_lights
       (if _obstacle_brake_lights (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _cut_in_and_out
       (write-byte _cut_in_and_out s)
     ;; uint8 _blinker_info
       (write-byte _blinker_info s)
     ;; uint8 _obstacle_valid
       (write-byte _obstacle_valid s)
     ;; float32 _obstacle_length
       (sys::poke _obstacle_length (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _obstacle_width
       (sys::poke _obstacle_width (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _obstacle_age
       (write-byte _obstacle_age s)
     ;; uint8 _obstacle_lane
       (write-byte _obstacle_lane s)
     ;; uint8 _cipv_flag
       (write-byte _cipv_flag s)
     ;; float32 _radar_position_x
       (sys::poke _radar_position_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _radar_velocity_x
       (sys::poke _radar_velocity_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _radar_match_confidence
       (write-byte _radar_match_confidence s)
     ;; uint8 _matched_radar_id
       (write-byte _matched_radar_id s)
     ;; float32 _obstacle_angle_rate
       (sys::poke _obstacle_angle_rate (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _obstacle_scale_change
       (sys::poke _obstacle_scale_change (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _obstacle_object_accel_x
       (sys::poke _obstacle_object_accel_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _obstacle_replaced
       (if _obstacle_replaced (write-byte -1 s) (write-byte 0 s))
     ;; float32 _obstacle_angle
       (sys::poke _obstacle_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _obstacle_id
     (setq _obstacle_id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _obstacle_position_x
     (setq _obstacle_position_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _obstacle_position_y
     (setq _obstacle_position_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _obstacle_relative_velocity_x
     (setq _obstacle_relative_velocity_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _obstacle_type
     (setq _obstacle_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _obstacle_status
     (setq _obstacle_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _obstacle_brake_lights
     (setq _obstacle_brake_lights (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _cut_in_and_out
     (setq _cut_in_and_out (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _blinker_info
     (setq _blinker_info (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _obstacle_valid
     (setq _obstacle_valid (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _obstacle_length
     (setq _obstacle_length (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _obstacle_width
     (setq _obstacle_width (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _obstacle_age
     (setq _obstacle_age (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _obstacle_lane
     (setq _obstacle_lane (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _cipv_flag
     (setq _cipv_flag (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _radar_position_x
     (setq _radar_position_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _radar_velocity_x
     (setq _radar_velocity_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _radar_match_confidence
     (setq _radar_match_confidence (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _matched_radar_id
     (setq _matched_radar_id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _obstacle_angle_rate
     (setq _obstacle_angle_rate (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _obstacle_scale_change
     (setq _obstacle_scale_change (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _obstacle_object_accel_x
     (setq _obstacle_object_accel_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _obstacle_replaced
     (setq _obstacle_replaced (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _obstacle_angle
     (setq _obstacle_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get mobileye_msgs::ObstacleData :md5sum-) "0f95ac1fed6a2bf8af234e0196c675c0")
(setf (get mobileye_msgs::ObstacleData :datatype-) "mobileye_msgs/ObstacleData")
(setf (get mobileye_msgs::ObstacleData :definition-)
      "uint8 obstacle_id
float32 obstacle_position_x
float32 obstacle_position_y
float32 obstacle_relative_velocity_x

uint8 obstacle_type
uint8 obstacle_status
bool obstacle_brake_lights
uint8 cut_in_and_out
uint8 blinker_info
uint8 obstacle_valid

float32 obstacle_length
float32 obstacle_width
uint8 obstacle_age
uint8 obstacle_lane
uint8 cipv_flag

float32 radar_position_x
float32 radar_velocity_x
uint8 radar_match_confidence
uint8 matched_radar_id

float32 obstacle_angle_rate
float32 obstacle_scale_change
float32 obstacle_object_accel_x
bool obstacle_replaced
float32 obstacle_angle

")



(provide :mobileye_msgs/ObstacleData "0f95ac1fed6a2bf8af234e0196c675c0")


