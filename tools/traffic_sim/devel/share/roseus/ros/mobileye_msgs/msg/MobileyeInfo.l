;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo
  :super ros::object
  :slots (_header _left_lane _right_lane _reference_points _number_of_next_lane_markers _next_lane _lane _obstacle_status _obstacle_data _system_warnings _car_info _tsr _tsr_vision_only _gyro _smart_adas _seeq ))

(defmethod mobileye_msgs::MobileyeInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:left_lane __left_lane) (instance mobileye_msgs::LKAlane :init))
    ((:right_lane __right_lane) (instance mobileye_msgs::LKAlane :init))
    ((:reference_points __reference_points) (instance mobileye_msgs::ReferencePoints :init))
    ((:number_of_next_lane_markers __number_of_next_lane_markers) 0)
    ((:next_lane __next_lane) (let (r) (dotimes (i 0) (push (instance mobileye_msgs::LKAlane :init) r)) r))
    ((:lane __lane) (instance mobileye_msgs::Lane :init))
    ((:obstacle_status __obstacle_status) (instance mobileye_msgs::ObstacleStatus :init))
    ((:obstacle_data __obstacle_data) (let (r) (dotimes (i 0) (push (instance mobileye_msgs::ObstacleData :init) r)) r))
    ((:system_warnings __system_warnings) (instance mobileye_msgs::SystemWarnings :init))
    ((:car_info __car_info) (instance mobileye_msgs::CarInfo :init))
    ((:tsr __tsr) (let (r) (dotimes (i 0) (push (instance mobileye_msgs::TSR :init) r)) r))
    ((:tsr_vision_only __tsr_vision_only) (instance mobileye_msgs::TSRVisionOnlySign :init))
    ((:gyro __gyro) (instance mobileye_msgs::Gyro :init))
    ((:smart_adas __smart_adas) (instance mobileye_msgs::SmartADAS :init))
    ((:seeq __seeq) (instance mobileye_msgs::SeeQ :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _left_lane __left_lane)
   (setq _right_lane __right_lane)
   (setq _reference_points __reference_points)
   (setq _number_of_next_lane_markers (round __number_of_next_lane_markers))
   (setq _next_lane __next_lane)
   (setq _lane __lane)
   (setq _obstacle_status __obstacle_status)
   (setq _obstacle_data __obstacle_data)
   (setq _system_warnings __system_warnings)
   (setq _car_info __car_info)
   (setq _tsr __tsr)
   (setq _tsr_vision_only __tsr_vision_only)
   (setq _gyro __gyro)
   (setq _smart_adas __smart_adas)
   (setq _seeq __seeq)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:left_lane
   (&rest __left_lane)
   (if (keywordp (car __left_lane))
       (send* _left_lane __left_lane)
     (progn
       (if __left_lane (setq _left_lane (car __left_lane)))
       _left_lane)))
  (:right_lane
   (&rest __right_lane)
   (if (keywordp (car __right_lane))
       (send* _right_lane __right_lane)
     (progn
       (if __right_lane (setq _right_lane (car __right_lane)))
       _right_lane)))
  (:reference_points
   (&rest __reference_points)
   (if (keywordp (car __reference_points))
       (send* _reference_points __reference_points)
     (progn
       (if __reference_points (setq _reference_points (car __reference_points)))
       _reference_points)))
  (:number_of_next_lane_markers
   (&optional __number_of_next_lane_markers)
   (if __number_of_next_lane_markers (setq _number_of_next_lane_markers __number_of_next_lane_markers)) _number_of_next_lane_markers)
  (:next_lane
   (&rest __next_lane)
   (if (keywordp (car __next_lane))
       (send* _next_lane __next_lane)
     (progn
       (if __next_lane (setq _next_lane (car __next_lane)))
       _next_lane)))
  (:lane
   (&rest __lane)
   (if (keywordp (car __lane))
       (send* _lane __lane)
     (progn
       (if __lane (setq _lane (car __lane)))
       _lane)))
  (:obstacle_status
   (&rest __obstacle_status)
   (if (keywordp (car __obstacle_status))
       (send* _obstacle_status __obstacle_status)
     (progn
       (if __obstacle_status (setq _obstacle_status (car __obstacle_status)))
       _obstacle_status)))
  (:obstacle_data
   (&rest __obstacle_data)
   (if (keywordp (car __obstacle_data))
       (send* _obstacle_data __obstacle_data)
     (progn
       (if __obstacle_data (setq _obstacle_data (car __obstacle_data)))
       _obstacle_data)))
  (:system_warnings
   (&rest __system_warnings)
   (if (keywordp (car __system_warnings))
       (send* _system_warnings __system_warnings)
     (progn
       (if __system_warnings (setq _system_warnings (car __system_warnings)))
       _system_warnings)))
  (:car_info
   (&rest __car_info)
   (if (keywordp (car __car_info))
       (send* _car_info __car_info)
     (progn
       (if __car_info (setq _car_info (car __car_info)))
       _car_info)))
  (:tsr
   (&rest __tsr)
   (if (keywordp (car __tsr))
       (send* _tsr __tsr)
     (progn
       (if __tsr (setq _tsr (car __tsr)))
       _tsr)))
  (:tsr_vision_only
   (&rest __tsr_vision_only)
   (if (keywordp (car __tsr_vision_only))
       (send* _tsr_vision_only __tsr_vision_only)
     (progn
       (if __tsr_vision_only (setq _tsr_vision_only (car __tsr_vision_only)))
       _tsr_vision_only)))
  (:gyro
   (&rest __gyro)
   (if (keywordp (car __gyro))
       (send* _gyro __gyro)
     (progn
       (if __gyro (setq _gyro (car __gyro)))
       _gyro)))
  (:smart_adas
   (&rest __smart_adas)
   (if (keywordp (car __smart_adas))
       (send* _smart_adas __smart_adas)
     (progn
       (if __smart_adas (setq _smart_adas (car __smart_adas)))
       _smart_adas)))
  (:seeq
   (&rest __seeq)
   (if (keywordp (car __seeq))
       (send* _seeq __seeq)
     (progn
       (if __seeq (setq _seeq (car __seeq)))
       _seeq)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/LKAlane _left_lane
    (send _left_lane :serialization-length)
    ;; mobileye_msgs/LKAlane _right_lane
    (send _right_lane :serialization-length)
    ;; mobileye_msgs/ReferencePoints _reference_points
    (send _reference_points :serialization-length)
    ;; uint8 _number_of_next_lane_markers
    1
    ;; mobileye_msgs/LKAlane[] _next_lane
    (apply #'+ (send-all _next_lane :serialization-length)) 4
    ;; mobileye_msgs/Lane _lane
    (send _lane :serialization-length)
    ;; mobileye_msgs/ObstacleStatus _obstacle_status
    (send _obstacle_status :serialization-length)
    ;; mobileye_msgs/ObstacleData[] _obstacle_data
    (apply #'+ (send-all _obstacle_data :serialization-length)) 4
    ;; mobileye_msgs/SystemWarnings _system_warnings
    (send _system_warnings :serialization-length)
    ;; mobileye_msgs/CarInfo _car_info
    (send _car_info :serialization-length)
    ;; mobileye_msgs/TSR[] _tsr
    (apply #'+ (send-all _tsr :serialization-length)) 4
    ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
    (send _tsr_vision_only :serialization-length)
    ;; mobileye_msgs/Gyro _gyro
    (send _gyro :serialization-length)
    ;; mobileye_msgs/SmartADAS _smart_adas
    (send _smart_adas :serialization-length)
    ;; mobileye_msgs/SeeQ _seeq
    (send _seeq :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/LKAlane _left_lane
       (send _left_lane :serialize s)
     ;; mobileye_msgs/LKAlane _right_lane
       (send _right_lane :serialize s)
     ;; mobileye_msgs/ReferencePoints _reference_points
       (send _reference_points :serialize s)
     ;; uint8 _number_of_next_lane_markers
       (write-byte _number_of_next_lane_markers s)
     ;; mobileye_msgs/LKAlane[] _next_lane
     (write-long (length _next_lane) s)
     (dolist (elem _next_lane)
       (send elem :serialize s)
       )
     ;; mobileye_msgs/Lane _lane
       (send _lane :serialize s)
     ;; mobileye_msgs/ObstacleStatus _obstacle_status
       (send _obstacle_status :serialize s)
     ;; mobileye_msgs/ObstacleData[] _obstacle_data
     (write-long (length _obstacle_data) s)
     (dolist (elem _obstacle_data)
       (send elem :serialize s)
       )
     ;; mobileye_msgs/SystemWarnings _system_warnings
       (send _system_warnings :serialize s)
     ;; mobileye_msgs/CarInfo _car_info
       (send _car_info :serialize s)
     ;; mobileye_msgs/TSR[] _tsr
     (write-long (length _tsr) s)
     (dolist (elem _tsr)
       (send elem :serialize s)
       )
     ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
       (send _tsr_vision_only :serialize s)
     ;; mobileye_msgs/Gyro _gyro
       (send _gyro :serialize s)
     ;; mobileye_msgs/SmartADAS _smart_adas
       (send _smart_adas :serialize s)
     ;; mobileye_msgs/SeeQ _seeq
       (send _seeq :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/LKAlane _left_lane
     (send _left_lane :deserialize buf ptr-) (incf ptr- (send _left_lane :serialization-length))
   ;; mobileye_msgs/LKAlane _right_lane
     (send _right_lane :deserialize buf ptr-) (incf ptr- (send _right_lane :serialization-length))
   ;; mobileye_msgs/ReferencePoints _reference_points
     (send _reference_points :deserialize buf ptr-) (incf ptr- (send _reference_points :serialization-length))
   ;; uint8 _number_of_next_lane_markers
     (setq _number_of_next_lane_markers (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; mobileye_msgs/LKAlane[] _next_lane
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _next_lane (let (r) (dotimes (i n) (push (instance mobileye_msgs::LKAlane :init) r)) r))
     (dolist (elem- _next_lane)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; mobileye_msgs/Lane _lane
     (send _lane :deserialize buf ptr-) (incf ptr- (send _lane :serialization-length))
   ;; mobileye_msgs/ObstacleStatus _obstacle_status
     (send _obstacle_status :deserialize buf ptr-) (incf ptr- (send _obstacle_status :serialization-length))
   ;; mobileye_msgs/ObstacleData[] _obstacle_data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _obstacle_data (let (r) (dotimes (i n) (push (instance mobileye_msgs::ObstacleData :init) r)) r))
     (dolist (elem- _obstacle_data)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; mobileye_msgs/SystemWarnings _system_warnings
     (send _system_warnings :deserialize buf ptr-) (incf ptr- (send _system_warnings :serialization-length))
   ;; mobileye_msgs/CarInfo _car_info
     (send _car_info :deserialize buf ptr-) (incf ptr- (send _car_info :serialization-length))
   ;; mobileye_msgs/TSR[] _tsr
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _tsr (let (r) (dotimes (i n) (push (instance mobileye_msgs::TSR :init) r)) r))
     (dolist (elem- _tsr)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
     (send _tsr_vision_only :deserialize buf ptr-) (incf ptr- (send _tsr_vision_only :serialization-length))
   ;; mobileye_msgs/Gyro _gyro
     (send _gyro :deserialize buf ptr-) (incf ptr- (send _gyro :serialization-length))
   ;; mobileye_msgs/SmartADAS _smart_adas
     (send _smart_adas :deserialize buf ptr-) (incf ptr- (send _smart_adas :serialization-length))
   ;; mobileye_msgs/SeeQ _seeq
     (send _seeq :deserialize buf ptr-) (incf ptr- (send _seeq :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo :md5sum-) "f347fd8c2960b4f7e8d7a1b937971d62")
(setf (get mobileye_msgs::MobileyeInfo :datatype-) "mobileye_msgs/MobileyeInfo")
(setf (get mobileye_msgs::MobileyeInfo :definition-)
      "Header header

LKAlane left_lane
LKAlane right_lane

ReferencePoints reference_points

uint8 number_of_next_lane_markers

LKAlane[] next_lane

Lane lane

ObstacleStatus obstacle_status
ObstacleData[] obstacle_data

SystemWarnings system_warnings
CarInfo car_info
TSR[] tsr
TSRVisionOnlySign tsr_vision_only
Gyro gyro
SmartADAS smart_adas
SeeQ seeq
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: mobileye_msgs/LKAlane
uint8 lane_type
uint8 quality
uint8 model_degree

float32 position_parameter_c0
float32 curvature_parameter_c2
float32 curvature_derivative_c3
float32 width_marking

float32 heading_angle_parameter_c1
float32 view_range
bool view_range_availability

================================================================================
MSG: mobileye_msgs/ReferencePoints
float32 ref_point1_position
float32 ref_point1_distance
bool ref_point1_validity
float32 ref_point2_position
float32 ref_point2_distance
bool ref_point2_validity
================================================================================
MSG: mobileye_msgs/Lane
float32 lane_curvature
float32 lane_heading

bool ca
float32 pitch_angle
float32 yaw_angle

bool right_ldw_availability
bool left_ldw_availability

================================================================================
MSG: mobileye_msgs/ObstacleStatus
uint8 number_of_obstacles
uint8 timestamp

bool left_close_rang_cut_in
bool right_close_rang_cut_in

uint8 go
bool close_car
uint8 failsafe

================================================================================
MSG: mobileye_msgs/ObstacleData
uint8 obstacle_id
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

================================================================================
MSG: mobileye_msgs/SystemWarnings
uint8 sound_type
bool peds_in_dz
bool peds_fcw
uint8 time_indicator

bool error_valid
uint8 error_code
bool zero_speed
bool headway_valid
float32 headway_measurement

bool ldw_off
bool left_ldw_on
bool right_ldw_on
bool fcw_on
bool maintenance
bool failsafe

bool tsr_enabled
bool hw_repeatable_enabled
uint8 headway_warning_level
uint8 tsr_warning_level
bool tamper_alert
================================================================================
MSG: mobileye_msgs/CarInfo
bool high_beam
bool low_beam
bool wipers
bool right_signal
bool left_signal
bool brake_signal
bool wipers_available
bool low_beam_available
bool high_beam_available
bool right_blink_available
bool left_blink_available
bool brake_available
bool speed_available
uint8 speed
uint8 shield_plus_settings
================================================================================
MSG: mobileye_msgs/TSR
uint8 vision_only_sign_type
uint8 supplementary_sign_type
float32 sign_position_x
float32 sign_position_y
float32 sign_position_z
uint8 filter_type
================================================================================
MSG: mobileye_msgs/TSRVisionOnlySign
uint8 vision_only_sign_type_display_1
uint8 vision_only_sign_type_display_2
uint8 vision_only_sign_type_display_3
uint8 vision_only_sign_type_display_4

uint8 supplementary_sign_type_display_1
uint8 supplementary_sign_type_display_2
uint8 supplementary_sign_type_display_3
uint8 supplementary_sign_type_display_4
================================================================================
MSG: mobileye_msgs/Gyro
bool gyro_sensor_data_available
float32 x_axis_data
================================================================================
MSG: mobileye_msgs/SmartADAS
uint8 persistent_on_off
uint8 volume_level
uint8 hmw_level
uint8 ldw_volume_level
uint8 hmw_volume_level
uint8 ldw_level
uint8 pedestrian_warning_level
uint8 sli_warning_level
uint8 blinker_reminder_level
uint8 virtual_bumper_level
uint8 hw_repeatable_level

uint8 buzzer_min_volume
uint8 buzzer_max_volume
uint8 buzzer_hmw_min_volume
uint8 buzzer_hmw_max_volume
uint8 buzzer_ldw_min_volume
uint8 buzzer_ldw_max_volume
uint8 ewiii_speed_indication
uint8 disable_system_off
uint8 calibration_source
uint8 ldw_min_value
uint8 ldw_max_value
uint8 ldw_speed
uint8 ped_min_value
uint8 ped_max_value
uint8 speed_for_high_low_beam_control
uint8 virtual_bumper_min_value
uint8 virtual_bumper_max_value
uint8 blinker_reminder_min_value
uint8 blinker_reminder_max_value

uint8 hmw_min_value
uint8 hmw_max_value
uint8 hmw_repeatable_min_value
uint8 hmw_repeatable_max_value
uint8 sli_min_value
uint8 sli_max_value
uint8 sli_delta_round_step
uint8 sli_delta_round_upwards
uint8 country_code
uint8 sli_unit_speed
uint8 tamper_alert_on_frames
uint8 tamper_alert_off_frames
uint8 tamper_alert_enable_j1939

bool[16] menu_ticks

bool[16] advanced_menu_ticks
================================================================================
MSG: mobileye_msgs/SeeQ
uint32 serial_number
uint64 production_date

uint8 brain_version_major
uint8 brain_version_minor
uint8 mest_version_major
uint8 mest_version_minor
uint8 mest_version_subminor
uint8 mest_version_patch_number
")



(provide :mobileye_msgs/MobileyeInfo "f347fd8c2960b4f7e8d7a1b937971d62")


