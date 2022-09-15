; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude StandardCAN.msg.html

(cl:defclass <StandardCAN> (roslisp-msg-protocol:ros-message)
  ((system_warnings
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

(cl:defclass StandardCAN (<StandardCAN>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StandardCAN>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StandardCAN)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<StandardCAN> is deprecated: use mobileye_msgs-msg:StandardCAN instead.")))

(cl:ensure-generic-function 'system_warnings-val :lambda-list '(m))
(cl:defmethod system_warnings-val ((m <StandardCAN>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:system_warnings-val is deprecated.  Use mobileye_msgs-msg:system_warnings instead.")
  (system_warnings m))

(cl:ensure-generic-function 'car_info-val :lambda-list '(m))
(cl:defmethod car_info-val ((m <StandardCAN>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:car_info-val is deprecated.  Use mobileye_msgs-msg:car_info instead.")
  (car_info m))

(cl:ensure-generic-function 'tsr-val :lambda-list '(m))
(cl:defmethod tsr-val ((m <StandardCAN>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tsr-val is deprecated.  Use mobileye_msgs-msg:tsr instead.")
  (tsr m))

(cl:ensure-generic-function 'tsr_vision_only-val :lambda-list '(m))
(cl:defmethod tsr_vision_only-val ((m <StandardCAN>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tsr_vision_only-val is deprecated.  Use mobileye_msgs-msg:tsr_vision_only instead.")
  (tsr_vision_only m))

(cl:ensure-generic-function 'gyro-val :lambda-list '(m))
(cl:defmethod gyro-val ((m <StandardCAN>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:gyro-val is deprecated.  Use mobileye_msgs-msg:gyro instead.")
  (gyro m))

(cl:ensure-generic-function 'smart_adas-val :lambda-list '(m))
(cl:defmethod smart_adas-val ((m <StandardCAN>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:smart_adas-val is deprecated.  Use mobileye_msgs-msg:smart_adas instead.")
  (smart_adas m))

(cl:ensure-generic-function 'seeq-val :lambda-list '(m))
(cl:defmethod seeq-val ((m <StandardCAN>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:seeq-val is deprecated.  Use mobileye_msgs-msg:seeq instead.")
  (seeq m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StandardCAN>) ostream)
  "Serializes a message object of type '<StandardCAN>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StandardCAN>) istream)
  "Deserializes a message object of type '<StandardCAN>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StandardCAN>)))
  "Returns string type for a message object of type '<StandardCAN>"
  "mobileye_msgs/StandardCAN")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StandardCAN)))
  "Returns string type for a message object of type 'StandardCAN"
  "mobileye_msgs/StandardCAN")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StandardCAN>)))
  "Returns md5sum for a message object of type '<StandardCAN>"
  "54e4cfc9bd8b43c069770d7bbb9295cd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StandardCAN)))
  "Returns md5sum for a message object of type 'StandardCAN"
  "54e4cfc9bd8b43c069770d7bbb9295cd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StandardCAN>)))
  "Returns full string definition for message of type '<StandardCAN>"
  (cl:format cl:nil "SystemWarnings system_warnings~%CarInfo car_info~%TSR[] tsr~%TSRVisionOnlySign tsr_vision_only~%Gyro gyro~%SmartADAS smart_adas~%SeeQ seeq~%================================================================================~%MSG: mobileye_msgs/SystemWarnings~%uint8 sound_type~%bool peds_in_dz~%bool peds_fcw~%uint8 time_indicator~%~%bool error_valid~%uint8 error_code~%bool zero_speed~%bool headway_valid~%float32 headway_measurement~%~%bool ldw_off~%bool left_ldw_on~%bool right_ldw_on~%bool fcw_on~%bool maintenance~%bool failsafe~%~%bool tsr_enabled~%bool hw_repeatable_enabled~%uint8 headway_warning_level~%uint8 tsr_warning_level~%bool tamper_alert~%================================================================================~%MSG: mobileye_msgs/CarInfo~%bool high_beam~%bool low_beam~%bool wipers~%bool right_signal~%bool left_signal~%bool brake_signal~%bool wipers_available~%bool low_beam_available~%bool high_beam_available~%bool right_blink_available~%bool left_blink_available~%bool brake_available~%bool speed_available~%uint8 speed~%uint8 shield_plus_settings~%================================================================================~%MSG: mobileye_msgs/TSR~%uint8 vision_only_sign_type~%uint8 supplementary_sign_type~%float32 sign_position_x~%float32 sign_position_y~%float32 sign_position_z~%uint8 filter_type~%================================================================================~%MSG: mobileye_msgs/TSRVisionOnlySign~%uint8 vision_only_sign_type_display_1~%uint8 vision_only_sign_type_display_2~%uint8 vision_only_sign_type_display_3~%uint8 vision_only_sign_type_display_4~%~%uint8 supplementary_sign_type_display_1~%uint8 supplementary_sign_type_display_2~%uint8 supplementary_sign_type_display_3~%uint8 supplementary_sign_type_display_4~%================================================================================~%MSG: mobileye_msgs/Gyro~%bool gyro_sensor_data_available~%float32 x_axis_data~%================================================================================~%MSG: mobileye_msgs/SmartADAS~%uint8 persistent_on_off~%uint8 volume_level~%uint8 hmw_level~%uint8 ldw_volume_level~%uint8 hmw_volume_level~%uint8 ldw_level~%uint8 pedestrian_warning_level~%uint8 sli_warning_level~%uint8 blinker_reminder_level~%uint8 virtual_bumper_level~%uint8 hw_repeatable_level~%~%uint8 buzzer_min_volume~%uint8 buzzer_max_volume~%uint8 buzzer_hmw_min_volume~%uint8 buzzer_hmw_max_volume~%uint8 buzzer_ldw_min_volume~%uint8 buzzer_ldw_max_volume~%uint8 ewiii_speed_indication~%uint8 disable_system_off~%uint8 calibration_source~%uint8 ldw_min_value~%uint8 ldw_max_value~%uint8 ldw_speed~%uint8 ped_min_value~%uint8 ped_max_value~%uint8 speed_for_high_low_beam_control~%uint8 virtual_bumper_min_value~%uint8 virtual_bumper_max_value~%uint8 blinker_reminder_min_value~%uint8 blinker_reminder_max_value~%~%uint8 hmw_min_value~%uint8 hmw_max_value~%uint8 hmw_repeatable_min_value~%uint8 hmw_repeatable_max_value~%uint8 sli_min_value~%uint8 sli_max_value~%uint8 sli_delta_round_step~%uint8 sli_delta_round_upwards~%uint8 country_code~%uint8 sli_unit_speed~%uint8 tamper_alert_on_frames~%uint8 tamper_alert_off_frames~%uint8 tamper_alert_enable_j1939~%~%bool[16] menu_ticks~%~%bool[16] advanced_menu_ticks~%================================================================================~%MSG: mobileye_msgs/SeeQ~%uint32 serial_number~%uint64 production_date~%~%uint8 brain_version_major~%uint8 brain_version_minor~%uint8 mest_version_major~%uint8 mest_version_minor~%uint8 mest_version_subminor~%uint8 mest_version_patch_number~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StandardCAN)))
  "Returns full string definition for message of type 'StandardCAN"
  (cl:format cl:nil "SystemWarnings system_warnings~%CarInfo car_info~%TSR[] tsr~%TSRVisionOnlySign tsr_vision_only~%Gyro gyro~%SmartADAS smart_adas~%SeeQ seeq~%================================================================================~%MSG: mobileye_msgs/SystemWarnings~%uint8 sound_type~%bool peds_in_dz~%bool peds_fcw~%uint8 time_indicator~%~%bool error_valid~%uint8 error_code~%bool zero_speed~%bool headway_valid~%float32 headway_measurement~%~%bool ldw_off~%bool left_ldw_on~%bool right_ldw_on~%bool fcw_on~%bool maintenance~%bool failsafe~%~%bool tsr_enabled~%bool hw_repeatable_enabled~%uint8 headway_warning_level~%uint8 tsr_warning_level~%bool tamper_alert~%================================================================================~%MSG: mobileye_msgs/CarInfo~%bool high_beam~%bool low_beam~%bool wipers~%bool right_signal~%bool left_signal~%bool brake_signal~%bool wipers_available~%bool low_beam_available~%bool high_beam_available~%bool right_blink_available~%bool left_blink_available~%bool brake_available~%bool speed_available~%uint8 speed~%uint8 shield_plus_settings~%================================================================================~%MSG: mobileye_msgs/TSR~%uint8 vision_only_sign_type~%uint8 supplementary_sign_type~%float32 sign_position_x~%float32 sign_position_y~%float32 sign_position_z~%uint8 filter_type~%================================================================================~%MSG: mobileye_msgs/TSRVisionOnlySign~%uint8 vision_only_sign_type_display_1~%uint8 vision_only_sign_type_display_2~%uint8 vision_only_sign_type_display_3~%uint8 vision_only_sign_type_display_4~%~%uint8 supplementary_sign_type_display_1~%uint8 supplementary_sign_type_display_2~%uint8 supplementary_sign_type_display_3~%uint8 supplementary_sign_type_display_4~%================================================================================~%MSG: mobileye_msgs/Gyro~%bool gyro_sensor_data_available~%float32 x_axis_data~%================================================================================~%MSG: mobileye_msgs/SmartADAS~%uint8 persistent_on_off~%uint8 volume_level~%uint8 hmw_level~%uint8 ldw_volume_level~%uint8 hmw_volume_level~%uint8 ldw_level~%uint8 pedestrian_warning_level~%uint8 sli_warning_level~%uint8 blinker_reminder_level~%uint8 virtual_bumper_level~%uint8 hw_repeatable_level~%~%uint8 buzzer_min_volume~%uint8 buzzer_max_volume~%uint8 buzzer_hmw_min_volume~%uint8 buzzer_hmw_max_volume~%uint8 buzzer_ldw_min_volume~%uint8 buzzer_ldw_max_volume~%uint8 ewiii_speed_indication~%uint8 disable_system_off~%uint8 calibration_source~%uint8 ldw_min_value~%uint8 ldw_max_value~%uint8 ldw_speed~%uint8 ped_min_value~%uint8 ped_max_value~%uint8 speed_for_high_low_beam_control~%uint8 virtual_bumper_min_value~%uint8 virtual_bumper_max_value~%uint8 blinker_reminder_min_value~%uint8 blinker_reminder_max_value~%~%uint8 hmw_min_value~%uint8 hmw_max_value~%uint8 hmw_repeatable_min_value~%uint8 hmw_repeatable_max_value~%uint8 sli_min_value~%uint8 sli_max_value~%uint8 sli_delta_round_step~%uint8 sli_delta_round_upwards~%uint8 country_code~%uint8 sli_unit_speed~%uint8 tamper_alert_on_frames~%uint8 tamper_alert_off_frames~%uint8 tamper_alert_enable_j1939~%~%bool[16] menu_ticks~%~%bool[16] advanced_menu_ticks~%================================================================================~%MSG: mobileye_msgs/SeeQ~%uint32 serial_number~%uint64 production_date~%~%uint8 brain_version_major~%uint8 brain_version_minor~%uint8 mest_version_major~%uint8 mest_version_minor~%uint8 mest_version_subminor~%uint8 mest_version_patch_number~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StandardCAN>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'system_warnings))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'car_info))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'tsr) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'tsr_vision_only))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gyro))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'smart_adas))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'seeq))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StandardCAN>))
  "Converts a ROS message object to a list"
  (cl:list 'StandardCAN
    (cl:cons ':system_warnings (system_warnings msg))
    (cl:cons ':car_info (car_info msg))
    (cl:cons ':tsr (tsr msg))
    (cl:cons ':tsr_vision_only (tsr_vision_only msg))
    (cl:cons ':gyro (gyro msg))
    (cl:cons ':smart_adas (smart_adas msg))
    (cl:cons ':seeq (seeq msg))
))
