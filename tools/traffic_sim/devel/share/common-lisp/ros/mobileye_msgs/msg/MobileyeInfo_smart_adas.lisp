; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude MobileyeInfo_smart_adas.msg.html

(cl:defclass <MobileyeInfo_smart_adas> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (smart_adas
    :reader smart_adas
    :initarg :smart_adas
    :type mobileye_msgs-msg:SmartADAS
    :initform (cl:make-instance 'mobileye_msgs-msg:SmartADAS)))
)

(cl:defclass MobileyeInfo_smart_adas (<MobileyeInfo_smart_adas>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MobileyeInfo_smart_adas>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MobileyeInfo_smart_adas)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<MobileyeInfo_smart_adas> is deprecated: use mobileye_msgs-msg:MobileyeInfo_smart_adas instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MobileyeInfo_smart_adas>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:header-val is deprecated.  Use mobileye_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'smart_adas-val :lambda-list '(m))
(cl:defmethod smart_adas-val ((m <MobileyeInfo_smart_adas>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:smart_adas-val is deprecated.  Use mobileye_msgs-msg:smart_adas instead.")
  (smart_adas m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MobileyeInfo_smart_adas>) ostream)
  "Serializes a message object of type '<MobileyeInfo_smart_adas>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'smart_adas) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MobileyeInfo_smart_adas>) istream)
  "Deserializes a message object of type '<MobileyeInfo_smart_adas>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'smart_adas) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MobileyeInfo_smart_adas>)))
  "Returns string type for a message object of type '<MobileyeInfo_smart_adas>"
  "mobileye_msgs/MobileyeInfo_smart_adas")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MobileyeInfo_smart_adas)))
  "Returns string type for a message object of type 'MobileyeInfo_smart_adas"
  "mobileye_msgs/MobileyeInfo_smart_adas")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MobileyeInfo_smart_adas>)))
  "Returns md5sum for a message object of type '<MobileyeInfo_smart_adas>"
  "1b63fad4adb86b289d19be4eadb354a3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MobileyeInfo_smart_adas)))
  "Returns md5sum for a message object of type 'MobileyeInfo_smart_adas"
  "1b63fad4adb86b289d19be4eadb354a3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MobileyeInfo_smart_adas>)))
  "Returns full string definition for message of type '<MobileyeInfo_smart_adas>"
  (cl:format cl:nil "Header header~%~%SmartADAS smart_adas~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/SmartADAS~%uint8 persistent_on_off~%uint8 volume_level~%uint8 hmw_level~%uint8 ldw_volume_level~%uint8 hmw_volume_level~%uint8 ldw_level~%uint8 pedestrian_warning_level~%uint8 sli_warning_level~%uint8 blinker_reminder_level~%uint8 virtual_bumper_level~%uint8 hw_repeatable_level~%~%uint8 buzzer_min_volume~%uint8 buzzer_max_volume~%uint8 buzzer_hmw_min_volume~%uint8 buzzer_hmw_max_volume~%uint8 buzzer_ldw_min_volume~%uint8 buzzer_ldw_max_volume~%uint8 ewiii_speed_indication~%uint8 disable_system_off~%uint8 calibration_source~%uint8 ldw_min_value~%uint8 ldw_max_value~%uint8 ldw_speed~%uint8 ped_min_value~%uint8 ped_max_value~%uint8 speed_for_high_low_beam_control~%uint8 virtual_bumper_min_value~%uint8 virtual_bumper_max_value~%uint8 blinker_reminder_min_value~%uint8 blinker_reminder_max_value~%~%uint8 hmw_min_value~%uint8 hmw_max_value~%uint8 hmw_repeatable_min_value~%uint8 hmw_repeatable_max_value~%uint8 sli_min_value~%uint8 sli_max_value~%uint8 sli_delta_round_step~%uint8 sli_delta_round_upwards~%uint8 country_code~%uint8 sli_unit_speed~%uint8 tamper_alert_on_frames~%uint8 tamper_alert_off_frames~%uint8 tamper_alert_enable_j1939~%~%bool[16] menu_ticks~%~%bool[16] advanced_menu_ticks~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MobileyeInfo_smart_adas)))
  "Returns full string definition for message of type 'MobileyeInfo_smart_adas"
  (cl:format cl:nil "Header header~%~%SmartADAS smart_adas~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: mobileye_msgs/SmartADAS~%uint8 persistent_on_off~%uint8 volume_level~%uint8 hmw_level~%uint8 ldw_volume_level~%uint8 hmw_volume_level~%uint8 ldw_level~%uint8 pedestrian_warning_level~%uint8 sli_warning_level~%uint8 blinker_reminder_level~%uint8 virtual_bumper_level~%uint8 hw_repeatable_level~%~%uint8 buzzer_min_volume~%uint8 buzzer_max_volume~%uint8 buzzer_hmw_min_volume~%uint8 buzzer_hmw_max_volume~%uint8 buzzer_ldw_min_volume~%uint8 buzzer_ldw_max_volume~%uint8 ewiii_speed_indication~%uint8 disable_system_off~%uint8 calibration_source~%uint8 ldw_min_value~%uint8 ldw_max_value~%uint8 ldw_speed~%uint8 ped_min_value~%uint8 ped_max_value~%uint8 speed_for_high_low_beam_control~%uint8 virtual_bumper_min_value~%uint8 virtual_bumper_max_value~%uint8 blinker_reminder_min_value~%uint8 blinker_reminder_max_value~%~%uint8 hmw_min_value~%uint8 hmw_max_value~%uint8 hmw_repeatable_min_value~%uint8 hmw_repeatable_max_value~%uint8 sli_min_value~%uint8 sli_max_value~%uint8 sli_delta_round_step~%uint8 sli_delta_round_upwards~%uint8 country_code~%uint8 sli_unit_speed~%uint8 tamper_alert_on_frames~%uint8 tamper_alert_off_frames~%uint8 tamper_alert_enable_j1939~%~%bool[16] menu_ticks~%~%bool[16] advanced_menu_ticks~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MobileyeInfo_smart_adas>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'smart_adas))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MobileyeInfo_smart_adas>))
  "Converts a ROS message object to a list"
  (cl:list 'MobileyeInfo_smart_adas
    (cl:cons ':header (header msg))
    (cl:cons ':smart_adas (smart_adas msg))
))
