; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo.msg.html

(cl:defclass <MobileyeInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (left_lane
    :reader left_lane
    :initarg :left_lane
    :type mobileye_msgs-msg:LKAlane
    :initform (cl:make-instance 'mobileye_msgs-msg:LKAlane))
   (right_lane
    :reader right_lane
    :initarg :right_lane
    :type mobileye_msgs-msg:LKAlane
    :initform (cl:make-instance 'mobileye_msgs-msg:LKAlane))
   (reference_points
    :reader reference_points
    :initarg :reference_points
    :type mobileye_msgs-msg:ReferencePoints
    :initform (cl:make-instance 'mobileye_msgs-msg:ReferencePoints))
   (number_of_next_lane_markers
    :reader number_of_next_lane_markers
    :initarg :number_of_next_lane_markers
    :type cl:fixnum
    :initform 0)
   (next_lane
    :reader next_lane
    :initarg :next_lane
    :type (cl:vector mobileye_msgs-msg:LKAlane)
   :initform (cl:make-array 0 :element-type 'mobileye_msgs-msg:LKAlane :initial-element (cl:make-instance 'mobileye_msgs-msg:LKAlane)))
   (lane
    :reader lane
    :initarg :lane
    :type mobileye_msgs-msg:Lane
    :initform (cl:make-instance 'mobileye_msgs-msg:Lane))
   (obstacle_status
    :reader obstacle_status
    :initarg :obstacle_status
    :type mobileye_msgs-msg:ObstacleStatus
    :initform (cl:make-instance 'mobileye_msgs-msg:ObstacleStatus))
   (obstacle_data
    :reader obstacle_data
    :initarg :obstacle_data
    :type (cl:vector mobileye_msgs-msg:ObstacleData)
   :initform (cl:make-array 0 :element-type 'mobileye_msgs-msg:ObstacleData :initial-element (cl:make-instance 'mobileye_msgs-msg:ObstacleData)))
   (system_warnings
    :reader system_warnings
    :initarg :system_warnings
    :type mobileye_msgs-msg:SystemWarnings
    :initform (cl:make-instance 'mobileye_msgs-msg:SystemWarnings))
   (car_info
    :reader car_info
    :initarg :car_info
    :type mobileye_msgs-msg:CarInfo
    :initform (cl:make-instance 'mobileye_msgs-msg:CarInfo))
   (tsr
    :reader tsr
    :initarg :tsr
    :type (cl:vector mobileye_msgs-msg:TSR)
   :initform (cl:make-array 0 :element-type 'mobileye_msgs-msg:TSR :initial-element (cl:make-instance 'mobileye_msgs-msg:TSR)))
   (tsr_vision_only
    :reader tsr_vision_only
    :initarg :tsr_vision_only
    :type mobileye_msgs-msg:TSRVisionOnlySign
    :initform (cl:make-instance 'mobileye_msgs-msg:TSRVisionOnlySign))
   (gyro
    :reader gyro
    :initarg :gyro
    :type mobileye_msgs-msg:Gyro
    :initform (cl:make-instance 'mobileye_msgs-msg:Gyro))
   (smart_adas
    :reader smart_adas
    :initarg :smart_adas
    :type mobileye_msgs-msg:SmartADAS
    :initform (cl:make-instance 'mobileye_msgs-msg:SmartADAS))
   (seeq
    :reader seeq
    :initarg :seeq
    :type mobileye_msgs-msg:SeeQ
    :initform (cl:make-instance 'mobileye_msgs-msg:SeeQ)))
)

(cl:defclass MobileyeInfo (<MobileyeInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo> is deprecated: use mobileye_msgs-msg:MobileyeInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'left_lane-val :lambda-list '(m))
(cl:defmethod left_lane-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:left_lane-val is deprecated.  Use mobileye_msgs-msg:left_lane instead.")
  (left_lane m))

(cl:ensure-generic-function 'right_lane-val :lambda-list '(m))
(cl:defmethod right_lane-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:right_lane-val is deprecated.  Use mobileye_msgs-msg:right_lane instead.")
  (right_lane m))

(cl:ensure-generic-function 'reference_points-val :lambda-list '(m))
(cl:defmethod reference_points-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:reference_points-val is deprecated.  Use mobileye_msgs-msg:reference_points instead.")
  (reference_points m))

(cl:ensure-generic-function 'number_of_next_lane_markers-val :lambda-list '(m))
(cl:defmethod number_of_next_lane_markers-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:number_of_next_lane_markers-val is deprecated.  Use mobileye_msgs-msg:number_of_next_lane_markers instead.")
  (number_of_next_lane_markers m))

(cl:ensure-generic-function 'next_lane-val :lambda-list '(m))
(cl:defmethod next_lane-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:next_lane-val is deprecated.  Use mobileye_msgs-msg:next_lane instead.")
  (next_lane m))

(cl:ensure-generic-function 'lane-val :lambda-list '(m))
(cl:defmethod lane-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:lane-val is deprecated.  Use mobileye_msgs-msg:lane instead.")
  (lane m))

(cl:ensure-generic-function 'obstacle_status-val :lambda-list '(m))
(cl:defmethod obstacle_status-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_status-val is deprecated.  Use mobileye_msgs-msg:obstacle_status instead.")
  (obstacle_status m))

(cl:ensure-generic-function 'obstacle_data-val :lambda-list '(m))
(cl:defmethod obstacle_data-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_data-val is deprecated.  Use mobileye_msgs-msg:obstacle_data instead.")
  (obstacle_data m))

(cl:ensure-generic-function 'system_warnings-val :lambda-list '(m))
(cl:defmethod system_warnings-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:system_warnings-val is deprecated.  Use mobileye_msgs-msg:system_warnings instead.")
  (system_warnings m))

(cl:ensure-generic-function 'car_info-val :lambda-list '(m))
(cl:defmethod car_info-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:car_info-val is deprecated.  Use mobileye_msgs-msg:car_info instead.")
  (car_info m))

(cl:ensure-generic-function 'tsr-val :lambda-list '(m))
(cl:defmethod tsr-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tsr-val is deprecated.  Use mobileye_msgs-msg:tsr instead.")
  (tsr m))

(cl:ensure-generic-function 'tsr_vision_only-val :lambda-list '(m))
(cl:defmethod tsr_vision_only-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tsr_vision_only-val is deprecated.  Use mobileye_msgs-msg:tsr_vision_only instead.")
  (tsr_vision_only m))

(cl:ensure-generic-function 'gyro-val :lambda-list '(m))
(cl:defmethod gyro-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:gyro-val is deprecated.  Use mobileye_msgs-msg:gyro instead.")
  (gyro m))

(cl:ensure-generic-function 'smart_adas-val :lambda-list '(m))
(cl:defmethod smart_adas-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:smart_adas-val is deprecated.  Use mobileye_msgs-msg:smart_adas instead.")
  (smart_adas m))

(cl:ensure-generic-function 'seeq-val :lambda-list '(m))
(cl:defmethod seeq-val ((m <MobileyeInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:seeq-val is deprecated.  Use mobileye_msgs-msg:seeq instead.")
  (seeq m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo>) ostream)
  "Serializes a message object of type '<MobileyeInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'left_lane) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'right_lane) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'reference_points) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'number_of_next_lane_markers)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'next_lane))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'next_lane))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'lane) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'obstacle_status) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'obstacle_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'obstacle_data))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'system_warnings) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'car_info) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'tsr))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'tsr))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'tsr_vision_only) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gyro) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'smart_adas) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'seeq) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo>) istream)
  "Deserializes a message object of type '<MobileyeInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'left_lane) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'right_lane) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'reference_points) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'number_of_next_lane_markers)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'next_lane) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'next_lane)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'mobileye_msgs-msg:LKAlane))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'lane) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'obstacle_status) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'obstacle_data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'obstacle_data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'mobileye_msgs-msg:ObstacleData))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'system_warnings) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'car_info) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'tsr) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'tsr)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'mobileye_msgs-msg:TSR))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'tsr_vision_only) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gyro) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'smart_adas) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'seeq) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo>)))
  "Returns string type for a message object of type '<MobileyeInfo>"
  "mobileye_msgs/MobileyeInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo)))
  "Returns string type for a message object of type 'MobileyeInfo"
  "mobileye_msgs/MobileyeInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo>)))
  "Returns md5sum for a message object of type '<MobileyeInfo>"
  "f347fd8c2960b4f7e8d7a1b937971d62")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo)))
  "Returns md5sum for a message object of type 'MobileyeInfo"
  "f347fd8c2960b4f7e8d7a1b937971d62")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo>)))
  "Returns full string definition for message of type '<MobileyeInfo>"
  (cl:format cl:nil "Header header~%~%LKAlane left_lane~%LKAlane right_lane~%~%ReferencePoints reference_points~%~%uint8 number_of_next_lane_markers~%~%LKAlane[] next_lane~%~%Lane lane~%~%ObstacleStatus obstacle_status~%ObstacleData[] obstacle_data~%~%SystemWarnings system_warnings~%CarInfo car_info~%TSR[] tsr~%TSRVisionOnlySign tsr_vision_only~%Gyro gyro~%SmartADAS smart_adas~%SeeQ seeq~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%================================================================================~%MSG: mobileye_msgs/ReferencePoints~%float32 ref_point1_position~%float32 ref_point1_distance~%bool ref_point1_validity~%float32 ref_point2_position~%float32 ref_point2_distance~%bool ref_point2_validity~%================================================================================~%MSG: mobileye_msgs/Lane~%float32 lane_curvature~%float32 lane_heading~%~%bool ca~%float32 pitch_angle~%float32 yaw_angle~%~%bool right_ldw_availability~%bool left_ldw_availability~%~%================================================================================~%MSG: mobileye_msgs/ObstacleStatus~%uint8 number_of_obstacles~%uint8 timestamp~%~%bool left_close_rang_cut_in~%bool right_close_rang_cut_in~%~%uint8 go~%bool close_car~%uint8 failsafe~%~%================================================================================~%MSG: mobileye_msgs/ObstacleData~%uint8 obstacle_id~%float32 obstacle_position_x~%float32 obstacle_position_y~%float32 obstacle_relative_velocity_x~%~%uint8 obstacle_type~%uint8 obstacle_status~%bool obstacle_brake_lights~%uint8 cut_in_and_out~%uint8 blinker_info~%uint8 obstacle_valid~%~%float32 obstacle_length~%float32 obstacle_width~%uint8 obstacle_age~%uint8 obstacle_lane~%uint8 cipv_flag~%~%float32 radar_position_x~%float32 radar_velocity_x~%uint8 radar_match_confidence~%uint8 matched_radar_id~%~%float32 obstacle_angle_rate~%float32 obstacle_scale_change~%float32 obstacle_object_accel_x~%bool obstacle_replaced~%float32 obstacle_angle~%~%================================================================================~%MSG: mobileye_msgs/SystemWarnings~%uint8 sound_type~%bool peds_in_dz~%bool peds_fcw~%uint8 time_indicator~%~%bool error_valid~%uint8 error_code~%bool zero_speed~%bool headway_valid~%float32 headway_measurement~%~%bool ldw_off~%bool left_ldw_on~%bool right_ldw_on~%bool fcw_on~%bool maintenance~%bool failsafe~%~%bool tsr_enabled~%bool hw_repeatable_enabled~%uint8 headway_warning_level~%uint8 tsr_warning_level~%bool tamper_alert~%================================================================================~%MSG: mobileye_msgs/CarInfo~%bool high_beam~%bool low_beam~%bool wipers~%bool right_signal~%bool left_signal~%bool brake_signal~%bool wipers_available~%bool low_beam_available~%bool high_beam_available~%bool right_blink_available~%bool left_blink_available~%bool brake_available~%bool speed_available~%uint8 speed~%uint8 shield_plus_settings~%================================================================================~%MSG: mobileye_msgs/TSR~%uint8 vision_only_sign_type~%uint8 supplementary_sign_type~%float32 sign_position_x~%float32 sign_position_y~%float32 sign_position_z~%uint8 filter_type~%================================================================================~%MSG: mobileye_msgs/TSRVisionOnlySign~%uint8 vision_only_sign_type_display_1~%uint8 vision_only_sign_type_display_2~%uint8 vision_only_sign_type_display_3~%uint8 vision_only_sign_type_display_4~%~%uint8 supplementary_sign_type_display_1~%uint8 supplementary_sign_type_display_2~%uint8 supplementary_sign_type_display_3~%uint8 supplementary_sign_type_display_4~%================================================================================~%MSG: mobileye_msgs/Gyro~%bool gyro_sensor_data_available~%float32 x_axis_data~%================================================================================~%MSG: mobileye_msgs/SmartADAS~%uint8 persistent_on_off~%uint8 volume_level~%uint8 hmw_level~%uint8 ldw_volume_level~%uint8 hmw_volume_level~%uint8 ldw_level~%uint8 pedestrian_warning_level~%uint8 sli_warning_level~%uint8 blinker_reminder_level~%uint8 virtual_bumper_level~%uint8 hw_repeatable_level~%~%uint8 buzzer_min_volume~%uint8 buzzer_max_volume~%uint8 buzzer_hmw_min_volume~%uint8 buzzer_hmw_max_volume~%uint8 buzzer_ldw_min_volume~%uint8 buzzer_ldw_max_volume~%uint8 ewiii_speed_indication~%uint8 disable_system_off~%uint8 calibration_source~%uint8 ldw_min_value~%uint8 ldw_max_value~%uint8 ldw_speed~%uint8 ped_min_value~%uint8 ped_max_value~%uint8 speed_for_high_low_beam_control~%uint8 virtual_bumper_min_value~%uint8 virtual_bumper_max_value~%uint8 blinker_reminder_min_value~%uint8 blinker_reminder_max_value~%~%uint8 hmw_min_value~%uint8 hmw_max_value~%uint8 hmw_repeatable_min_value~%uint8 hmw_repeatable_max_value~%uint8 sli_min_value~%uint8 sli_max_value~%uint8 sli_delta_round_step~%uint8 sli_delta_round_upwards~%uint8 country_code~%uint8 sli_unit_speed~%uint8 tamper_alert_on_frames~%uint8 tamper_alert_off_frames~%uint8 tamper_alert_enable_j1939~%~%bool[16] menu_ticks~%~%bool[16] advanced_menu_ticks~%================================================================================~%MSG: mobileye_msgs/SeeQ~%uint32 serial_number~%uint64 production_date~%~%uint8 brain_version_major~%uint8 brain_version_minor~%uint8 mest_version_major~%uint8 mest_version_minor~%uint8 mest_version_subminor~%uint8 mest_version_patch_number~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo)))
  "Returns full string definition for message of type 'MobileyeInfo"
  (cl:format cl:nil "Header header~%~%LKAlane left_lane~%LKAlane right_lane~%~%ReferencePoints reference_points~%~%uint8 number_of_next_lane_markers~%~%LKAlane[] next_lane~%~%Lane lane~%~%ObstacleStatus obstacle_status~%ObstacleData[] obstacle_data~%~%SystemWarnings system_warnings~%CarInfo car_info~%TSR[] tsr~%TSRVisionOnlySign tsr_vision_only~%Gyro gyro~%SmartADAS smart_adas~%SeeQ seeq~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/LKAlane~%uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%================================================================================~%MSG: mobileye_msgs/ReferencePoints~%float32 ref_point1_position~%float32 ref_point1_distance~%bool ref_point1_validity~%float32 ref_point2_position~%float32 ref_point2_distance~%bool ref_point2_validity~%================================================================================~%MSG: mobileye_msgs/Lane~%float32 lane_curvature~%float32 lane_heading~%~%bool ca~%float32 pitch_angle~%float32 yaw_angle~%~%bool right_ldw_availability~%bool left_ldw_availability~%~%================================================================================~%MSG: mobileye_msgs/ObstacleStatus~%uint8 number_of_obstacles~%uint8 timestamp~%~%bool left_close_rang_cut_in~%bool right_close_rang_cut_in~%~%uint8 go~%bool close_car~%uint8 failsafe~%~%================================================================================~%MSG: mobileye_msgs/ObstacleData~%uint8 obstacle_id~%float32 obstacle_position_x~%float32 obstacle_position_y~%float32 obstacle_relative_velocity_x~%~%uint8 obstacle_type~%uint8 obstacle_status~%bool obstacle_brake_lights~%uint8 cut_in_and_out~%uint8 blinker_info~%uint8 obstacle_valid~%~%float32 obstacle_length~%float32 obstacle_width~%uint8 obstacle_age~%uint8 obstacle_lane~%uint8 cipv_flag~%~%float32 radar_position_x~%float32 radar_velocity_x~%uint8 radar_match_confidence~%uint8 matched_radar_id~%~%float32 obstacle_angle_rate~%float32 obstacle_scale_change~%float32 obstacle_object_accel_x~%bool obstacle_replaced~%float32 obstacle_angle~%~%================================================================================~%MSG: mobileye_msgs/SystemWarnings~%uint8 sound_type~%bool peds_in_dz~%bool peds_fcw~%uint8 time_indicator~%~%bool error_valid~%uint8 error_code~%bool zero_speed~%bool headway_valid~%float32 headway_measurement~%~%bool ldw_off~%bool left_ldw_on~%bool right_ldw_on~%bool fcw_on~%bool maintenance~%bool failsafe~%~%bool tsr_enabled~%bool hw_repeatable_enabled~%uint8 headway_warning_level~%uint8 tsr_warning_level~%bool tamper_alert~%================================================================================~%MSG: mobileye_msgs/CarInfo~%bool high_beam~%bool low_beam~%bool wipers~%bool right_signal~%bool left_signal~%bool brake_signal~%bool wipers_available~%bool low_beam_available~%bool high_beam_available~%bool right_blink_available~%bool left_blink_available~%bool brake_available~%bool speed_available~%uint8 speed~%uint8 shield_plus_settings~%================================================================================~%MSG: mobileye_msgs/TSR~%uint8 vision_only_sign_type~%uint8 supplementary_sign_type~%float32 sign_position_x~%float32 sign_position_y~%float32 sign_position_z~%uint8 filter_type~%================================================================================~%MSG: mobileye_msgs/TSRVisionOnlySign~%uint8 vision_only_sign_type_display_1~%uint8 vision_only_sign_type_display_2~%uint8 vision_only_sign_type_display_3~%uint8 vision_only_sign_type_display_4~%~%uint8 supplementary_sign_type_display_1~%uint8 supplementary_sign_type_display_2~%uint8 supplementary_sign_type_display_3~%uint8 supplementary_sign_type_display_4~%================================================================================~%MSG: mobileye_msgs/Gyro~%bool gyro_sensor_data_available~%float32 x_axis_data~%================================================================================~%MSG: mobileye_msgs/SmartADAS~%uint8 persistent_on_off~%uint8 volume_level~%uint8 hmw_level~%uint8 ldw_volume_level~%uint8 hmw_volume_level~%uint8 ldw_level~%uint8 pedestrian_warning_level~%uint8 sli_warning_level~%uint8 blinker_reminder_level~%uint8 virtual_bumper_level~%uint8 hw_repeatable_level~%~%uint8 buzzer_min_volume~%uint8 buzzer_max_volume~%uint8 buzzer_hmw_min_volume~%uint8 buzzer_hmw_max_volume~%uint8 buzzer_ldw_min_volume~%uint8 buzzer_ldw_max_volume~%uint8 ewiii_speed_indication~%uint8 disable_system_off~%uint8 calibration_source~%uint8 ldw_min_value~%uint8 ldw_max_value~%uint8 ldw_speed~%uint8 ped_min_value~%uint8 ped_max_value~%uint8 speed_for_high_low_beam_control~%uint8 virtual_bumper_min_value~%uint8 virtual_bumper_max_value~%uint8 blinker_reminder_min_value~%uint8 blinker_reminder_max_value~%~%uint8 hmw_min_value~%uint8 hmw_max_value~%uint8 hmw_repeatable_min_value~%uint8 hmw_repeatable_max_value~%uint8 sli_min_value~%uint8 sli_max_value~%uint8 sli_delta_round_step~%uint8 sli_delta_round_upwards~%uint8 country_code~%uint8 sli_unit_speed~%uint8 tamper_alert_on_frames~%uint8 tamper_alert_off_frames~%uint8 tamper_alert_enable_j1939~%~%bool[16] menu_ticks~%~%bool[16] advanced_menu_ticks~%================================================================================~%MSG: mobileye_msgs/SeeQ~%uint32 serial_number~%uint64 production_date~%~%uint8 brain_version_major~%uint8 brain_version_minor~%uint8 mest_version_major~%uint8 mest_version_minor~%uint8 mest_version_subminor~%uint8 mest_version_patch_number~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'left_lane))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'right_lane))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'reference_points))
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'next_lane) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'lane))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'obstacle_status))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'obstacle_data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'system_warnings))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'car_info))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'tsr) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'tsr_vision_only))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gyro))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'smart_adas))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'seeq))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo
    (cl:cons ':header (header msg))
    (cl:cons ':left_lane (left_lane msg))
    (cl:cons ':right_lane (right_lane msg))
    (cl:cons ':reference_points (reference_points msg))
    (cl:cons ':number_of_next_lane_markers (number_of_next_lane_markers msg))
    (cl:cons ':next_lane (next_lane msg))
    (cl:cons ':lane (lane msg))
    (cl:cons ':obstacle_status (obstacle_status msg))
    (cl:cons ':obstacle_data (obstacle_data msg))
    (cl:cons ':system_warnings (system_warnings msg))
    (cl:cons ':car_info (car_info msg))
    (cl:cons ':tsr (tsr msg))
    (cl:cons ':tsr_vision_only (tsr_vision_only msg))
    (cl:cons ':gyro (gyro msg))
    (cl:cons ':smart_adas (smart_adas msg))
    (cl:cons ':seeq (seeq msg))
))
