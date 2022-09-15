; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude ObstacleData.msg.html

(cl:defclass <ObstacleData> (roslisp-msg-protocol:ros-message)
  ((obstacle_id
    :reader obstacle_id
    :initarg :obstacle_id
    :type cl:fixnum
    :initform 0)
   (obstacle_position_x
    :reader obstacle_position_x
    :initarg :obstacle_position_x
    :type cl:float
    :initform 0.0)
   (obstacle_position_y
    :reader obstacle_position_y
    :initarg :obstacle_position_y
    :type cl:float
    :initform 0.0)
   (obstacle_relative_velocity_x
    :reader obstacle_relative_velocity_x
    :initarg :obstacle_relative_velocity_x
    :type cl:float
    :initform 0.0)
   (obstacle_type
    :reader obstacle_type
    :initarg :obstacle_type
    :type cl:fixnum
    :initform 0)
   (obstacle_status
    :reader obstacle_status
    :initarg :obstacle_status
    :type cl:fixnum
    :initform 0)
   (obstacle_brake_lights
    :reader obstacle_brake_lights
    :initarg :obstacle_brake_lights
    :type cl:boolean
    :initform cl:nil)
   (cut_in_and_out
    :reader cut_in_and_out
    :initarg :cut_in_and_out
    :type cl:fixnum
    :initform 0)
   (blinker_info
    :reader blinker_info
    :initarg :blinker_info
    :type cl:fixnum
    :initform 0)
   (obstacle_valid
    :reader obstacle_valid
    :initarg :obstacle_valid
    :type cl:fixnum
    :initform 0)
   (obstacle_length
    :reader obstacle_length
    :initarg :obstacle_length
    :type cl:float
    :initform 0.0)
   (obstacle_width
    :reader obstacle_width
    :initarg :obstacle_width
    :type cl:float
    :initform 0.0)
   (obstacle_age
    :reader obstacle_age
    :initarg :obstacle_age
    :type cl:fixnum
    :initform 0)
   (obstacle_lane
    :reader obstacle_lane
    :initarg :obstacle_lane
    :type cl:fixnum
    :initform 0)
   (cipv_flag
    :reader cipv_flag
    :initarg :cipv_flag
    :type cl:fixnum
    :initform 0)
   (radar_position_x
    :reader radar_position_x
    :initarg :radar_position_x
    :type cl:float
    :initform 0.0)
   (radar_velocity_x
    :reader radar_velocity_x
    :initarg :radar_velocity_x
    :type cl:float
    :initform 0.0)
   (radar_match_confidence
    :reader radar_match_confidence
    :initarg :radar_match_confidence
    :type cl:fixnum
    :initform 0)
   (matched_radar_id
    :reader matched_radar_id
    :initarg :matched_radar_id
    :type cl:fixnum
    :initform 0)
   (obstacle_angle_rate
    :reader obstacle_angle_rate
    :initarg :obstacle_angle_rate
    :type cl:float
    :initform 0.0)
   (obstacle_scale_change
    :reader obstacle_scale_change
    :initarg :obstacle_scale_change
    :type cl:float
    :initform 0.0)
   (obstacle_object_accel_x
    :reader obstacle_object_accel_x
    :initarg :obstacle_object_accel_x
    :type cl:float
    :initform 0.0)
   (obstacle_replaced
    :reader obstacle_replaced
    :initarg :obstacle_replaced
    :type cl:boolean
    :initform cl:nil)
   (obstacle_angle
    :reader obstacle_angle
    :initarg :obstacle_angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass ObstacleData (<ObstacleData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ObstacleData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ObstacleData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<ObstacleData> is deprecated: use mobileye_msgs-msg:ObstacleData instead.")))

(cl:ensure-generic-function 'obstacle_id-val :lambda-list '(m))
(cl:defmethod obstacle_id-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_id-val is deprecated.  Use mobileye_msgs-msg:obstacle_id instead.")
  (obstacle_id m))

(cl:ensure-generic-function 'obstacle_position_x-val :lambda-list '(m))
(cl:defmethod obstacle_position_x-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_position_x-val is deprecated.  Use mobileye_msgs-msg:obstacle_position_x instead.")
  (obstacle_position_x m))

(cl:ensure-generic-function 'obstacle_position_y-val :lambda-list '(m))
(cl:defmethod obstacle_position_y-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_position_y-val is deprecated.  Use mobileye_msgs-msg:obstacle_position_y instead.")
  (obstacle_position_y m))

(cl:ensure-generic-function 'obstacle_relative_velocity_x-val :lambda-list '(m))
(cl:defmethod obstacle_relative_velocity_x-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_relative_velocity_x-val is deprecated.  Use mobileye_msgs-msg:obstacle_relative_velocity_x instead.")
  (obstacle_relative_velocity_x m))

(cl:ensure-generic-function 'obstacle_type-val :lambda-list '(m))
(cl:defmethod obstacle_type-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_type-val is deprecated.  Use mobileye_msgs-msg:obstacle_type instead.")
  (obstacle_type m))

(cl:ensure-generic-function 'obstacle_status-val :lambda-list '(m))
(cl:defmethod obstacle_status-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_status-val is deprecated.  Use mobileye_msgs-msg:obstacle_status instead.")
  (obstacle_status m))

(cl:ensure-generic-function 'obstacle_brake_lights-val :lambda-list '(m))
(cl:defmethod obstacle_brake_lights-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_brake_lights-val is deprecated.  Use mobileye_msgs-msg:obstacle_brake_lights instead.")
  (obstacle_brake_lights m))

(cl:ensure-generic-function 'cut_in_and_out-val :lambda-list '(m))
(cl:defmethod cut_in_and_out-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:cut_in_and_out-val is deprecated.  Use mobileye_msgs-msg:cut_in_and_out instead.")
  (cut_in_and_out m))

(cl:ensure-generic-function 'blinker_info-val :lambda-list '(m))
(cl:defmethod blinker_info-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:blinker_info-val is deprecated.  Use mobileye_msgs-msg:blinker_info instead.")
  (blinker_info m))

(cl:ensure-generic-function 'obstacle_valid-val :lambda-list '(m))
(cl:defmethod obstacle_valid-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_valid-val is deprecated.  Use mobileye_msgs-msg:obstacle_valid instead.")
  (obstacle_valid m))

(cl:ensure-generic-function 'obstacle_length-val :lambda-list '(m))
(cl:defmethod obstacle_length-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_length-val is deprecated.  Use mobileye_msgs-msg:obstacle_length instead.")
  (obstacle_length m))

(cl:ensure-generic-function 'obstacle_width-val :lambda-list '(m))
(cl:defmethod obstacle_width-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_width-val is deprecated.  Use mobileye_msgs-msg:obstacle_width instead.")
  (obstacle_width m))

(cl:ensure-generic-function 'obstacle_age-val :lambda-list '(m))
(cl:defmethod obstacle_age-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_age-val is deprecated.  Use mobileye_msgs-msg:obstacle_age instead.")
  (obstacle_age m))

(cl:ensure-generic-function 'obstacle_lane-val :lambda-list '(m))
(cl:defmethod obstacle_lane-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_lane-val is deprecated.  Use mobileye_msgs-msg:obstacle_lane instead.")
  (obstacle_lane m))

(cl:ensure-generic-function 'cipv_flag-val :lambda-list '(m))
(cl:defmethod cipv_flag-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:cipv_flag-val is deprecated.  Use mobileye_msgs-msg:cipv_flag instead.")
  (cipv_flag m))

(cl:ensure-generic-function 'radar_position_x-val :lambda-list '(m))
(cl:defmethod radar_position_x-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:radar_position_x-val is deprecated.  Use mobileye_msgs-msg:radar_position_x instead.")
  (radar_position_x m))

(cl:ensure-generic-function 'radar_velocity_x-val :lambda-list '(m))
(cl:defmethod radar_velocity_x-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:radar_velocity_x-val is deprecated.  Use mobileye_msgs-msg:radar_velocity_x instead.")
  (radar_velocity_x m))

(cl:ensure-generic-function 'radar_match_confidence-val :lambda-list '(m))
(cl:defmethod radar_match_confidence-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:radar_match_confidence-val is deprecated.  Use mobileye_msgs-msg:radar_match_confidence instead.")
  (radar_match_confidence m))

(cl:ensure-generic-function 'matched_radar_id-val :lambda-list '(m))
(cl:defmethod matched_radar_id-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:matched_radar_id-val is deprecated.  Use mobileye_msgs-msg:matched_radar_id instead.")
  (matched_radar_id m))

(cl:ensure-generic-function 'obstacle_angle_rate-val :lambda-list '(m))
(cl:defmethod obstacle_angle_rate-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_angle_rate-val is deprecated.  Use mobileye_msgs-msg:obstacle_angle_rate instead.")
  (obstacle_angle_rate m))

(cl:ensure-generic-function 'obstacle_scale_change-val :lambda-list '(m))
(cl:defmethod obstacle_scale_change-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_scale_change-val is deprecated.  Use mobileye_msgs-msg:obstacle_scale_change instead.")
  (obstacle_scale_change m))

(cl:ensure-generic-function 'obstacle_object_accel_x-val :lambda-list '(m))
(cl:defmethod obstacle_object_accel_x-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_object_accel_x-val is deprecated.  Use mobileye_msgs-msg:obstacle_object_accel_x instead.")
  (obstacle_object_accel_x m))

(cl:ensure-generic-function 'obstacle_replaced-val :lambda-list '(m))
(cl:defmethod obstacle_replaced-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_replaced-val is deprecated.  Use mobileye_msgs-msg:obstacle_replaced instead.")
  (obstacle_replaced m))

(cl:ensure-generic-function 'obstacle_angle-val :lambda-list '(m))
(cl:defmethod obstacle_angle-val ((m <ObstacleData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:obstacle_angle-val is deprecated.  Use mobileye_msgs-msg:obstacle_angle instead.")
  (obstacle_angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ObstacleData>) ostream)
  "Serializes a message object of type '<ObstacleData>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_id)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_position_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_position_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_relative_velocity_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'obstacle_brake_lights) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cut_in_and_out)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'blinker_info)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_valid)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_age)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_lane)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cipv_flag)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radar_position_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radar_velocity_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'radar_match_confidence)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'matched_radar_id)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_angle_rate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_scale_change))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_object_accel_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'obstacle_replaced) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'obstacle_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ObstacleData>) istream)
  "Deserializes a message object of type '<ObstacleData>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_id)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_position_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_position_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_relative_velocity_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_status)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_brake_lights) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cut_in_and_out)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'blinker_info)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_valid)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_length) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_age)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obstacle_lane)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cipv_flag)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radar_position_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radar_velocity_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'radar_match_confidence)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'matched_radar_id)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_angle_rate) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_scale_change) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_object_accel_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'obstacle_replaced) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle_angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ObstacleData>)))
  "Returns string type for a message object of type '<ObstacleData>"
  "mobileye_msgs/ObstacleData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ObstacleData)))
  "Returns string type for a message object of type 'ObstacleData"
  "mobileye_msgs/ObstacleData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ObstacleData>)))
  "Returns md5sum for a message object of type '<ObstacleData>"
  "0f95ac1fed6a2bf8af234e0196c675c0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ObstacleData)))
  "Returns md5sum for a message object of type 'ObstacleData"
  "0f95ac1fed6a2bf8af234e0196c675c0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ObstacleData>)))
  "Returns full string definition for message of type '<ObstacleData>"
  (cl:format cl:nil "uint8 obstacle_id~%float32 obstacle_position_x~%float32 obstacle_position_y~%float32 obstacle_relative_velocity_x~%~%uint8 obstacle_type~%uint8 obstacle_status~%bool obstacle_brake_lights~%uint8 cut_in_and_out~%uint8 blinker_info~%uint8 obstacle_valid~%~%float32 obstacle_length~%float32 obstacle_width~%uint8 obstacle_age~%uint8 obstacle_lane~%uint8 cipv_flag~%~%float32 radar_position_x~%float32 radar_velocity_x~%uint8 radar_match_confidence~%uint8 matched_radar_id~%~%float32 obstacle_angle_rate~%float32 obstacle_scale_change~%float32 obstacle_object_accel_x~%bool obstacle_replaced~%float32 obstacle_angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ObstacleData)))
  "Returns full string definition for message of type 'ObstacleData"
  (cl:format cl:nil "uint8 obstacle_id~%float32 obstacle_position_x~%float32 obstacle_position_y~%float32 obstacle_relative_velocity_x~%~%uint8 obstacle_type~%uint8 obstacle_status~%bool obstacle_brake_lights~%uint8 cut_in_and_out~%uint8 blinker_info~%uint8 obstacle_valid~%~%float32 obstacle_length~%float32 obstacle_width~%uint8 obstacle_age~%uint8 obstacle_lane~%uint8 cipv_flag~%~%float32 radar_position_x~%float32 radar_velocity_x~%uint8 radar_match_confidence~%uint8 matched_radar_id~%~%float32 obstacle_angle_rate~%float32 obstacle_scale_change~%float32 obstacle_object_accel_x~%bool obstacle_replaced~%float32 obstacle_angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ObstacleData>))
  (cl:+ 0
     1
     4
     4
     4
     1
     1
     1
     1
     1
     1
     4
     4
     1
     1
     1
     4
     4
     1
     1
     4
     4
     4
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ObstacleData>))
  "Converts a ROS message object to a list"
  (cl:list 'ObstacleData
    (cl:cons ':obstacle_id (obstacle_id msg))
    (cl:cons ':obstacle_position_x (obstacle_position_x msg))
    (cl:cons ':obstacle_position_y (obstacle_position_y msg))
    (cl:cons ':obstacle_relative_velocity_x (obstacle_relative_velocity_x msg))
    (cl:cons ':obstacle_type (obstacle_type msg))
    (cl:cons ':obstacle_status (obstacle_status msg))
    (cl:cons ':obstacle_brake_lights (obstacle_brake_lights msg))
    (cl:cons ':cut_in_and_out (cut_in_and_out msg))
    (cl:cons ':blinker_info (blinker_info msg))
    (cl:cons ':obstacle_valid (obstacle_valid msg))
    (cl:cons ':obstacle_length (obstacle_length msg))
    (cl:cons ':obstacle_width (obstacle_width msg))
    (cl:cons ':obstacle_age (obstacle_age msg))
    (cl:cons ':obstacle_lane (obstacle_lane msg))
    (cl:cons ':cipv_flag (cipv_flag msg))
    (cl:cons ':radar_position_x (radar_position_x msg))
    (cl:cons ':radar_velocity_x (radar_velocity_x msg))
    (cl:cons ':radar_match_confidence (radar_match_confidence msg))
    (cl:cons ':matched_radar_id (matched_radar_id msg))
    (cl:cons ':obstacle_angle_rate (obstacle_angle_rate msg))
    (cl:cons ':obstacle_scale_change (obstacle_scale_change msg))
    (cl:cons ':obstacle_object_accel_x (obstacle_object_accel_x msg))
    (cl:cons ':obstacle_replaced (obstacle_replaced msg))
    (cl:cons ':obstacle_angle (obstacle_angle msg))
))
