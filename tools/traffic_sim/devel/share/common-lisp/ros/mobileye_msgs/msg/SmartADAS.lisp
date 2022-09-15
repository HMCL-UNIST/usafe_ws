; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude SmartADAS.msg.html

(cl:defclass <SmartADAS> (roslisp-msg-protocol:ros-message)
  ((persistent_on_off
    :reader persistent_on_off
    :initarg :persistent_on_off
    :type cl:fixnum
    :initform 0)
   (volume_level
    :reader volume_level
    :initarg :volume_level
    :type cl:fixnum
    :initform 0)
   (hmw_level
    :reader hmw_level
    :initarg :hmw_level
    :type cl:fixnum
    :initform 0)
   (ldw_volume_level
    :reader ldw_volume_level
    :initarg :ldw_volume_level
    :type cl:fixnum
    :initform 0)
   (hmw_volume_level
    :reader hmw_volume_level
    :initarg :hmw_volume_level
    :type cl:fixnum
    :initform 0)
   (ldw_level
    :reader ldw_level
    :initarg :ldw_level
    :type cl:fixnum
    :initform 0)
   (pedestrian_warning_level
    :reader pedestrian_warning_level
    :initarg :pedestrian_warning_level
    :type cl:fixnum
    :initform 0)
   (sli_warning_level
    :reader sli_warning_level
    :initarg :sli_warning_level
    :type cl:fixnum
    :initform 0)
   (blinker_reminder_level
    :reader blinker_reminder_level
    :initarg :blinker_reminder_level
    :type cl:fixnum
    :initform 0)
   (virtual_bumper_level
    :reader virtual_bumper_level
    :initarg :virtual_bumper_level
    :type cl:fixnum
    :initform 0)
   (hw_repeatable_level
    :reader hw_repeatable_level
    :initarg :hw_repeatable_level
    :type cl:fixnum
    :initform 0)
   (buzzer_min_volume
    :reader buzzer_min_volume
    :initarg :buzzer_min_volume
    :type cl:fixnum
    :initform 0)
   (buzzer_max_volume
    :reader buzzer_max_volume
    :initarg :buzzer_max_volume
    :type cl:fixnum
    :initform 0)
   (buzzer_hmw_min_volume
    :reader buzzer_hmw_min_volume
    :initarg :buzzer_hmw_min_volume
    :type cl:fixnum
    :initform 0)
   (buzzer_hmw_max_volume
    :reader buzzer_hmw_max_volume
    :initarg :buzzer_hmw_max_volume
    :type cl:fixnum
    :initform 0)
   (buzzer_ldw_min_volume
    :reader buzzer_ldw_min_volume
    :initarg :buzzer_ldw_min_volume
    :type cl:fixnum
    :initform 0)
   (buzzer_ldw_max_volume
    :reader buzzer_ldw_max_volume
    :initarg :buzzer_ldw_max_volume
    :type cl:fixnum
    :initform 0)
   (ewiii_speed_indication
    :reader ewiii_speed_indication
    :initarg :ewiii_speed_indication
    :type cl:fixnum
    :initform 0)
   (disable_system_off
    :reader disable_system_off
    :initarg :disable_system_off
    :type cl:fixnum
    :initform 0)
   (calibration_source
    :reader calibration_source
    :initarg :calibration_source
    :type cl:fixnum
    :initform 0)
   (ldw_min_value
    :reader ldw_min_value
    :initarg :ldw_min_value
    :type cl:fixnum
    :initform 0)
   (ldw_max_value
    :reader ldw_max_value
    :initarg :ldw_max_value
    :type cl:fixnum
    :initform 0)
   (ldw_speed
    :reader ldw_speed
    :initarg :ldw_speed
    :type cl:fixnum
    :initform 0)
   (ped_min_value
    :reader ped_min_value
    :initarg :ped_min_value
    :type cl:fixnum
    :initform 0)
   (ped_max_value
    :reader ped_max_value
    :initarg :ped_max_value
    :type cl:fixnum
    :initform 0)
   (speed_for_high_low_beam_control
    :reader speed_for_high_low_beam_control
    :initarg :speed_for_high_low_beam_control
    :type cl:fixnum
    :initform 0)
   (virtual_bumper_min_value
    :reader virtual_bumper_min_value
    :initarg :virtual_bumper_min_value
    :type cl:fixnum
    :initform 0)
   (virtual_bumper_max_value
    :reader virtual_bumper_max_value
    :initarg :virtual_bumper_max_value
    :type cl:fixnum
    :initform 0)
   (blinker_reminder_min_value
    :reader blinker_reminder_min_value
    :initarg :blinker_reminder_min_value
    :type cl:fixnum
    :initform 0)
   (blinker_reminder_max_value
    :reader blinker_reminder_max_value
    :initarg :blinker_reminder_max_value
    :type cl:fixnum
    :initform 0)
   (hmw_min_value
    :reader hmw_min_value
    :initarg :hmw_min_value
    :type cl:fixnum
    :initform 0)
   (hmw_max_value
    :reader hmw_max_value
    :initarg :hmw_max_value
    :type cl:fixnum
    :initform 0)
   (hmw_repeatable_min_value
    :reader hmw_repeatable_min_value
    :initarg :hmw_repeatable_min_value
    :type cl:fixnum
    :initform 0)
   (hmw_repeatable_max_value
    :reader hmw_repeatable_max_value
    :initarg :hmw_repeatable_max_value
    :type cl:fixnum
    :initform 0)
   (sli_min_value
    :reader sli_min_value
    :initarg :sli_min_value
    :type cl:fixnum
    :initform 0)
   (sli_max_value
    :reader sli_max_value
    :initarg :sli_max_value
    :type cl:fixnum
    :initform 0)
   (sli_delta_round_step
    :reader sli_delta_round_step
    :initarg :sli_delta_round_step
    :type cl:fixnum
    :initform 0)
   (sli_delta_round_upwards
    :reader sli_delta_round_upwards
    :initarg :sli_delta_round_upwards
    :type cl:fixnum
    :initform 0)
   (country_code
    :reader country_code
    :initarg :country_code
    :type cl:fixnum
    :initform 0)
   (sli_unit_speed
    :reader sli_unit_speed
    :initarg :sli_unit_speed
    :type cl:fixnum
    :initform 0)
   (tamper_alert_on_frames
    :reader tamper_alert_on_frames
    :initarg :tamper_alert_on_frames
    :type cl:fixnum
    :initform 0)
   (tamper_alert_off_frames
    :reader tamper_alert_off_frames
    :initarg :tamper_alert_off_frames
    :type cl:fixnum
    :initform 0)
   (tamper_alert_enable_j1939
    :reader tamper_alert_enable_j1939
    :initarg :tamper_alert_enable_j1939
    :type cl:fixnum
    :initform 0)
   (menu_ticks
    :reader menu_ticks
    :initarg :menu_ticks
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 16 :element-type 'cl:boolean :initial-element cl:nil))
   (advanced_menu_ticks
    :reader advanced_menu_ticks
    :initarg :advanced_menu_ticks
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 16 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass SmartADAS (<SmartADAS>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SmartADAS>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SmartADAS)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<SmartADAS> is deprecated: use mobileye_msgs-msg:SmartADAS instead.")))

(cl:ensure-generic-function 'persistent_on_off-val :lambda-list '(m))
(cl:defmethod persistent_on_off-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:persistent_on_off-val is deprecated.  Use mobileye_msgs-msg:persistent_on_off instead.")
  (persistent_on_off m))

(cl:ensure-generic-function 'volume_level-val :lambda-list '(m))
(cl:defmethod volume_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:volume_level-val is deprecated.  Use mobileye_msgs-msg:volume_level instead.")
  (volume_level m))

(cl:ensure-generic-function 'hmw_level-val :lambda-list '(m))
(cl:defmethod hmw_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:hmw_level-val is deprecated.  Use mobileye_msgs-msg:hmw_level instead.")
  (hmw_level m))

(cl:ensure-generic-function 'ldw_volume_level-val :lambda-list '(m))
(cl:defmethod ldw_volume_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ldw_volume_level-val is deprecated.  Use mobileye_msgs-msg:ldw_volume_level instead.")
  (ldw_volume_level m))

(cl:ensure-generic-function 'hmw_volume_level-val :lambda-list '(m))
(cl:defmethod hmw_volume_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:hmw_volume_level-val is deprecated.  Use mobileye_msgs-msg:hmw_volume_level instead.")
  (hmw_volume_level m))

(cl:ensure-generic-function 'ldw_level-val :lambda-list '(m))
(cl:defmethod ldw_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ldw_level-val is deprecated.  Use mobileye_msgs-msg:ldw_level instead.")
  (ldw_level m))

(cl:ensure-generic-function 'pedestrian_warning_level-val :lambda-list '(m))
(cl:defmethod pedestrian_warning_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:pedestrian_warning_level-val is deprecated.  Use mobileye_msgs-msg:pedestrian_warning_level instead.")
  (pedestrian_warning_level m))

(cl:ensure-generic-function 'sli_warning_level-val :lambda-list '(m))
(cl:defmethod sli_warning_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sli_warning_level-val is deprecated.  Use mobileye_msgs-msg:sli_warning_level instead.")
  (sli_warning_level m))

(cl:ensure-generic-function 'blinker_reminder_level-val :lambda-list '(m))
(cl:defmethod blinker_reminder_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:blinker_reminder_level-val is deprecated.  Use mobileye_msgs-msg:blinker_reminder_level instead.")
  (blinker_reminder_level m))

(cl:ensure-generic-function 'virtual_bumper_level-val :lambda-list '(m))
(cl:defmethod virtual_bumper_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:virtual_bumper_level-val is deprecated.  Use mobileye_msgs-msg:virtual_bumper_level instead.")
  (virtual_bumper_level m))

(cl:ensure-generic-function 'hw_repeatable_level-val :lambda-list '(m))
(cl:defmethod hw_repeatable_level-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:hw_repeatable_level-val is deprecated.  Use mobileye_msgs-msg:hw_repeatable_level instead.")
  (hw_repeatable_level m))

(cl:ensure-generic-function 'buzzer_min_volume-val :lambda-list '(m))
(cl:defmethod buzzer_min_volume-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:buzzer_min_volume-val is deprecated.  Use mobileye_msgs-msg:buzzer_min_volume instead.")
  (buzzer_min_volume m))

(cl:ensure-generic-function 'buzzer_max_volume-val :lambda-list '(m))
(cl:defmethod buzzer_max_volume-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:buzzer_max_volume-val is deprecated.  Use mobileye_msgs-msg:buzzer_max_volume instead.")
  (buzzer_max_volume m))

(cl:ensure-generic-function 'buzzer_hmw_min_volume-val :lambda-list '(m))
(cl:defmethod buzzer_hmw_min_volume-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:buzzer_hmw_min_volume-val is deprecated.  Use mobileye_msgs-msg:buzzer_hmw_min_volume instead.")
  (buzzer_hmw_min_volume m))

(cl:ensure-generic-function 'buzzer_hmw_max_volume-val :lambda-list '(m))
(cl:defmethod buzzer_hmw_max_volume-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:buzzer_hmw_max_volume-val is deprecated.  Use mobileye_msgs-msg:buzzer_hmw_max_volume instead.")
  (buzzer_hmw_max_volume m))

(cl:ensure-generic-function 'buzzer_ldw_min_volume-val :lambda-list '(m))
(cl:defmethod buzzer_ldw_min_volume-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:buzzer_ldw_min_volume-val is deprecated.  Use mobileye_msgs-msg:buzzer_ldw_min_volume instead.")
  (buzzer_ldw_min_volume m))

(cl:ensure-generic-function 'buzzer_ldw_max_volume-val :lambda-list '(m))
(cl:defmethod buzzer_ldw_max_volume-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:buzzer_ldw_max_volume-val is deprecated.  Use mobileye_msgs-msg:buzzer_ldw_max_volume instead.")
  (buzzer_ldw_max_volume m))

(cl:ensure-generic-function 'ewiii_speed_indication-val :lambda-list '(m))
(cl:defmethod ewiii_speed_indication-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ewiii_speed_indication-val is deprecated.  Use mobileye_msgs-msg:ewiii_speed_indication instead.")
  (ewiii_speed_indication m))

(cl:ensure-generic-function 'disable_system_off-val :lambda-list '(m))
(cl:defmethod disable_system_off-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:disable_system_off-val is deprecated.  Use mobileye_msgs-msg:disable_system_off instead.")
  (disable_system_off m))

(cl:ensure-generic-function 'calibration_source-val :lambda-list '(m))
(cl:defmethod calibration_source-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:calibration_source-val is deprecated.  Use mobileye_msgs-msg:calibration_source instead.")
  (calibration_source m))

(cl:ensure-generic-function 'ldw_min_value-val :lambda-list '(m))
(cl:defmethod ldw_min_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ldw_min_value-val is deprecated.  Use mobileye_msgs-msg:ldw_min_value instead.")
  (ldw_min_value m))

(cl:ensure-generic-function 'ldw_max_value-val :lambda-list '(m))
(cl:defmethod ldw_max_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ldw_max_value-val is deprecated.  Use mobileye_msgs-msg:ldw_max_value instead.")
  (ldw_max_value m))

(cl:ensure-generic-function 'ldw_speed-val :lambda-list '(m))
(cl:defmethod ldw_speed-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ldw_speed-val is deprecated.  Use mobileye_msgs-msg:ldw_speed instead.")
  (ldw_speed m))

(cl:ensure-generic-function 'ped_min_value-val :lambda-list '(m))
(cl:defmethod ped_min_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ped_min_value-val is deprecated.  Use mobileye_msgs-msg:ped_min_value instead.")
  (ped_min_value m))

(cl:ensure-generic-function 'ped_max_value-val :lambda-list '(m))
(cl:defmethod ped_max_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ped_max_value-val is deprecated.  Use mobileye_msgs-msg:ped_max_value instead.")
  (ped_max_value m))

(cl:ensure-generic-function 'speed_for_high_low_beam_control-val :lambda-list '(m))
(cl:defmethod speed_for_high_low_beam_control-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:speed_for_high_low_beam_control-val is deprecated.  Use mobileye_msgs-msg:speed_for_high_low_beam_control instead.")
  (speed_for_high_low_beam_control m))

(cl:ensure-generic-function 'virtual_bumper_min_value-val :lambda-list '(m))
(cl:defmethod virtual_bumper_min_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:virtual_bumper_min_value-val is deprecated.  Use mobileye_msgs-msg:virtual_bumper_min_value instead.")
  (virtual_bumper_min_value m))

(cl:ensure-generic-function 'virtual_bumper_max_value-val :lambda-list '(m))
(cl:defmethod virtual_bumper_max_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:virtual_bumper_max_value-val is deprecated.  Use mobileye_msgs-msg:virtual_bumper_max_value instead.")
  (virtual_bumper_max_value m))

(cl:ensure-generic-function 'blinker_reminder_min_value-val :lambda-list '(m))
(cl:defmethod blinker_reminder_min_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:blinker_reminder_min_value-val is deprecated.  Use mobileye_msgs-msg:blinker_reminder_min_value instead.")
  (blinker_reminder_min_value m))

(cl:ensure-generic-function 'blinker_reminder_max_value-val :lambda-list '(m))
(cl:defmethod blinker_reminder_max_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:blinker_reminder_max_value-val is deprecated.  Use mobileye_msgs-msg:blinker_reminder_max_value instead.")
  (blinker_reminder_max_value m))

(cl:ensure-generic-function 'hmw_min_value-val :lambda-list '(m))
(cl:defmethod hmw_min_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:hmw_min_value-val is deprecated.  Use mobileye_msgs-msg:hmw_min_value instead.")
  (hmw_min_value m))

(cl:ensure-generic-function 'hmw_max_value-val :lambda-list '(m))
(cl:defmethod hmw_max_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:hmw_max_value-val is deprecated.  Use mobileye_msgs-msg:hmw_max_value instead.")
  (hmw_max_value m))

(cl:ensure-generic-function 'hmw_repeatable_min_value-val :lambda-list '(m))
(cl:defmethod hmw_repeatable_min_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:hmw_repeatable_min_value-val is deprecated.  Use mobileye_msgs-msg:hmw_repeatable_min_value instead.")
  (hmw_repeatable_min_value m))

(cl:ensure-generic-function 'hmw_repeatable_max_value-val :lambda-list '(m))
(cl:defmethod hmw_repeatable_max_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:hmw_repeatable_max_value-val is deprecated.  Use mobileye_msgs-msg:hmw_repeatable_max_value instead.")
  (hmw_repeatable_max_value m))

(cl:ensure-generic-function 'sli_min_value-val :lambda-list '(m))
(cl:defmethod sli_min_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sli_min_value-val is deprecated.  Use mobileye_msgs-msg:sli_min_value instead.")
  (sli_min_value m))

(cl:ensure-generic-function 'sli_max_value-val :lambda-list '(m))
(cl:defmethod sli_max_value-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sli_max_value-val is deprecated.  Use mobileye_msgs-msg:sli_max_value instead.")
  (sli_max_value m))

(cl:ensure-generic-function 'sli_delta_round_step-val :lambda-list '(m))
(cl:defmethod sli_delta_round_step-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sli_delta_round_step-val is deprecated.  Use mobileye_msgs-msg:sli_delta_round_step instead.")
  (sli_delta_round_step m))

(cl:ensure-generic-function 'sli_delta_round_upwards-val :lambda-list '(m))
(cl:defmethod sli_delta_round_upwards-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sli_delta_round_upwards-val is deprecated.  Use mobileye_msgs-msg:sli_delta_round_upwards instead.")
  (sli_delta_round_upwards m))

(cl:ensure-generic-function 'country_code-val :lambda-list '(m))
(cl:defmethod country_code-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:country_code-val is deprecated.  Use mobileye_msgs-msg:country_code instead.")
  (country_code m))

(cl:ensure-generic-function 'sli_unit_speed-val :lambda-list '(m))
(cl:defmethod sli_unit_speed-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:sli_unit_speed-val is deprecated.  Use mobileye_msgs-msg:sli_unit_speed instead.")
  (sli_unit_speed m))

(cl:ensure-generic-function 'tamper_alert_on_frames-val :lambda-list '(m))
(cl:defmethod tamper_alert_on_frames-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tamper_alert_on_frames-val is deprecated.  Use mobileye_msgs-msg:tamper_alert_on_frames instead.")
  (tamper_alert_on_frames m))

(cl:ensure-generic-function 'tamper_alert_off_frames-val :lambda-list '(m))
(cl:defmethod tamper_alert_off_frames-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tamper_alert_off_frames-val is deprecated.  Use mobileye_msgs-msg:tamper_alert_off_frames instead.")
  (tamper_alert_off_frames m))

(cl:ensure-generic-function 'tamper_alert_enable_j1939-val :lambda-list '(m))
(cl:defmethod tamper_alert_enable_j1939-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:tamper_alert_enable_j1939-val is deprecated.  Use mobileye_msgs-msg:tamper_alert_enable_j1939 instead.")
  (tamper_alert_enable_j1939 m))

(cl:ensure-generic-function 'menu_ticks-val :lambda-list '(m))
(cl:defmethod menu_ticks-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:menu_ticks-val is deprecated.  Use mobileye_msgs-msg:menu_ticks instead.")
  (menu_ticks m))

(cl:ensure-generic-function 'advanced_menu_ticks-val :lambda-list '(m))
(cl:defmethod advanced_menu_ticks-val ((m <SmartADAS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:advanced_menu_ticks-val is deprecated.  Use mobileye_msgs-msg:advanced_menu_ticks instead.")
  (advanced_menu_ticks m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SmartADAS>) ostream)
  "Serializes a message object of type '<SmartADAS>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'persistent_on_off)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'volume_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_volume_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_volume_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pedestrian_warning_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_warning_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'blinker_reminder_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'virtual_bumper_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hw_repeatable_level)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_min_volume)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_max_volume)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_hmw_min_volume)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_hmw_max_volume)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_ldw_min_volume)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_ldw_max_volume)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ewiii_speed_indication)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'disable_system_off)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'calibration_source)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_min_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_max_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_speed)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ped_min_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ped_max_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'speed_for_high_low_beam_control)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'virtual_bumper_min_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'virtual_bumper_max_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'blinker_reminder_min_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'blinker_reminder_max_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_min_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_max_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_repeatable_min_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_repeatable_max_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_min_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_max_value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_delta_round_step)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_delta_round_upwards)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'country_code)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_unit_speed)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'tamper_alert_on_frames)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'tamper_alert_off_frames)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'tamper_alert_enable_j1939)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'menu_ticks))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'advanced_menu_ticks))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SmartADAS>) istream)
  "Deserializes a message object of type '<SmartADAS>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'persistent_on_off)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'volume_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_volume_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_volume_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pedestrian_warning_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_warning_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'blinker_reminder_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'virtual_bumper_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hw_repeatable_level)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_min_volume)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_max_volume)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_hmw_min_volume)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_hmw_max_volume)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_ldw_min_volume)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'buzzer_ldw_max_volume)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ewiii_speed_indication)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'disable_system_off)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'calibration_source)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_min_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_max_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ldw_speed)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ped_min_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'ped_max_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'speed_for_high_low_beam_control)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'virtual_bumper_min_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'virtual_bumper_max_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'blinker_reminder_min_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'blinker_reminder_max_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_min_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_max_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_repeatable_min_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hmw_repeatable_max_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_min_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_max_value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_delta_round_step)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_delta_round_upwards)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'country_code)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sli_unit_speed)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'tamper_alert_on_frames)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'tamper_alert_off_frames)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'tamper_alert_enable_j1939)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'menu_ticks) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'menu_ticks)))
    (cl:dotimes (i 16)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'advanced_menu_ticks) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'advanced_menu_ticks)))
    (cl:dotimes (i 16)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SmartADAS>)))
  "Returns string type for a message object of type '<SmartADAS>"
  "mobileye_msgs/SmartADAS")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SmartADAS)))
  "Returns string type for a message object of type 'SmartADAS"
  "mobileye_msgs/SmartADAS")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SmartADAS>)))
  "Returns md5sum for a message object of type '<SmartADAS>"
  "2234fe7679b621d841bd2d8b34cf58ad")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SmartADAS)))
  "Returns md5sum for a message object of type 'SmartADAS"
  "2234fe7679b621d841bd2d8b34cf58ad")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SmartADAS>)))
  "Returns full string definition for message of type '<SmartADAS>"
  (cl:format cl:nil "uint8 persistent_on_off~%uint8 volume_level~%uint8 hmw_level~%uint8 ldw_volume_level~%uint8 hmw_volume_level~%uint8 ldw_level~%uint8 pedestrian_warning_level~%uint8 sli_warning_level~%uint8 blinker_reminder_level~%uint8 virtual_bumper_level~%uint8 hw_repeatable_level~%~%uint8 buzzer_min_volume~%uint8 buzzer_max_volume~%uint8 buzzer_hmw_min_volume~%uint8 buzzer_hmw_max_volume~%uint8 buzzer_ldw_min_volume~%uint8 buzzer_ldw_max_volume~%uint8 ewiii_speed_indication~%uint8 disable_system_off~%uint8 calibration_source~%uint8 ldw_min_value~%uint8 ldw_max_value~%uint8 ldw_speed~%uint8 ped_min_value~%uint8 ped_max_value~%uint8 speed_for_high_low_beam_control~%uint8 virtual_bumper_min_value~%uint8 virtual_bumper_max_value~%uint8 blinker_reminder_min_value~%uint8 blinker_reminder_max_value~%~%uint8 hmw_min_value~%uint8 hmw_max_value~%uint8 hmw_repeatable_min_value~%uint8 hmw_repeatable_max_value~%uint8 sli_min_value~%uint8 sli_max_value~%uint8 sli_delta_round_step~%uint8 sli_delta_round_upwards~%uint8 country_code~%uint8 sli_unit_speed~%uint8 tamper_alert_on_frames~%uint8 tamper_alert_off_frames~%uint8 tamper_alert_enable_j1939~%~%bool[16] menu_ticks~%~%bool[16] advanced_menu_ticks~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SmartADAS)))
  "Returns full string definition for message of type 'SmartADAS"
  (cl:format cl:nil "uint8 persistent_on_off~%uint8 volume_level~%uint8 hmw_level~%uint8 ldw_volume_level~%uint8 hmw_volume_level~%uint8 ldw_level~%uint8 pedestrian_warning_level~%uint8 sli_warning_level~%uint8 blinker_reminder_level~%uint8 virtual_bumper_level~%uint8 hw_repeatable_level~%~%uint8 buzzer_min_volume~%uint8 buzzer_max_volume~%uint8 buzzer_hmw_min_volume~%uint8 buzzer_hmw_max_volume~%uint8 buzzer_ldw_min_volume~%uint8 buzzer_ldw_max_volume~%uint8 ewiii_speed_indication~%uint8 disable_system_off~%uint8 calibration_source~%uint8 ldw_min_value~%uint8 ldw_max_value~%uint8 ldw_speed~%uint8 ped_min_value~%uint8 ped_max_value~%uint8 speed_for_high_low_beam_control~%uint8 virtual_bumper_min_value~%uint8 virtual_bumper_max_value~%uint8 blinker_reminder_min_value~%uint8 blinker_reminder_max_value~%~%uint8 hmw_min_value~%uint8 hmw_max_value~%uint8 hmw_repeatable_min_value~%uint8 hmw_repeatable_max_value~%uint8 sli_min_value~%uint8 sli_max_value~%uint8 sli_delta_round_step~%uint8 sli_delta_round_upwards~%uint8 country_code~%uint8 sli_unit_speed~%uint8 tamper_alert_on_frames~%uint8 tamper_alert_off_frames~%uint8 tamper_alert_enable_j1939~%~%bool[16] menu_ticks~%~%bool[16] advanced_menu_ticks~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SmartADAS>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'menu_ticks) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'advanced_menu_ticks) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SmartADAS>))
  "Converts a ROS message object to a list"
  (cl:list 'SmartADAS
    (cl:cons ':persistent_on_off (persistent_on_off msg))
    (cl:cons ':volume_level (volume_level msg))
    (cl:cons ':hmw_level (hmw_level msg))
    (cl:cons ':ldw_volume_level (ldw_volume_level msg))
    (cl:cons ':hmw_volume_level (hmw_volume_level msg))
    (cl:cons ':ldw_level (ldw_level msg))
    (cl:cons ':pedestrian_warning_level (pedestrian_warning_level msg))
    (cl:cons ':sli_warning_level (sli_warning_level msg))
    (cl:cons ':blinker_reminder_level (blinker_reminder_level msg))
    (cl:cons ':virtual_bumper_level (virtual_bumper_level msg))
    (cl:cons ':hw_repeatable_level (hw_repeatable_level msg))
    (cl:cons ':buzzer_min_volume (buzzer_min_volume msg))
    (cl:cons ':buzzer_max_volume (buzzer_max_volume msg))
    (cl:cons ':buzzer_hmw_min_volume (buzzer_hmw_min_volume msg))
    (cl:cons ':buzzer_hmw_max_volume (buzzer_hmw_max_volume msg))
    (cl:cons ':buzzer_ldw_min_volume (buzzer_ldw_min_volume msg))
    (cl:cons ':buzzer_ldw_max_volume (buzzer_ldw_max_volume msg))
    (cl:cons ':ewiii_speed_indication (ewiii_speed_indication msg))
    (cl:cons ':disable_system_off (disable_system_off msg))
    (cl:cons ':calibration_source (calibration_source msg))
    (cl:cons ':ldw_min_value (ldw_min_value msg))
    (cl:cons ':ldw_max_value (ldw_max_value msg))
    (cl:cons ':ldw_speed (ldw_speed msg))
    (cl:cons ':ped_min_value (ped_min_value msg))
    (cl:cons ':ped_max_value (ped_max_value msg))
    (cl:cons ':speed_for_high_low_beam_control (speed_for_high_low_beam_control msg))
    (cl:cons ':virtual_bumper_min_value (virtual_bumper_min_value msg))
    (cl:cons ':virtual_bumper_max_value (virtual_bumper_max_value msg))
    (cl:cons ':blinker_reminder_min_value (blinker_reminder_min_value msg))
    (cl:cons ':blinker_reminder_max_value (blinker_reminder_max_value msg))
    (cl:cons ':hmw_min_value (hmw_min_value msg))
    (cl:cons ':hmw_max_value (hmw_max_value msg))
    (cl:cons ':hmw_repeatable_min_value (hmw_repeatable_min_value msg))
    (cl:cons ':hmw_repeatable_max_value (hmw_repeatable_max_value msg))
    (cl:cons ':sli_min_value (sli_min_value msg))
    (cl:cons ':sli_max_value (sli_max_value msg))
    (cl:cons ':sli_delta_round_step (sli_delta_round_step msg))
    (cl:cons ':sli_delta_round_upwards (sli_delta_round_upwards msg))
    (cl:cons ':country_code (country_code msg))
    (cl:cons ':sli_unit_speed (sli_unit_speed msg))
    (cl:cons ':tamper_alert_on_frames (tamper_alert_on_frames msg))
    (cl:cons ':tamper_alert_off_frames (tamper_alert_off_frames msg))
    (cl:cons ':tamper_alert_enable_j1939 (tamper_alert_enable_j1939 msg))
    (cl:cons ':menu_ticks (menu_ticks msg))
    (cl:cons ':advanced_menu_ticks (advanced_menu_ticks msg))
))
