; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude LKAlane.msg.html

(cl:defclass <LKAlane> (roslisp-msg-protocol:ros-message)
  ((lane_type
    :reader lane_type
    :initarg :lane_type
    :type cl:fixnum
    :initform 0)
   (quality
    :reader quality
    :initarg :quality
    :type cl:fixnum
    :initform 0)
   (model_degree
    :reader model_degree
    :initarg :model_degree
    :type cl:fixnum
    :initform 0)
   (position_parameter_c0
    :reader position_parameter_c0
    :initarg :position_parameter_c0
    :type cl:float
    :initform 0.0)
   (curvature_parameter_c2
    :reader curvature_parameter_c2
    :initarg :curvature_parameter_c2
    :type cl:float
    :initform 0.0)
   (curvature_derivative_c3
    :reader curvature_derivative_c3
    :initarg :curvature_derivative_c3
    :type cl:float
    :initform 0.0)
   (width_marking
    :reader width_marking
    :initarg :width_marking
    :type cl:float
    :initform 0.0)
   (heading_angle_parameter_c1
    :reader heading_angle_parameter_c1
    :initarg :heading_angle_parameter_c1
    :type cl:float
    :initform 0.0)
   (view_range
    :reader view_range
    :initarg :view_range
    :type cl:float
    :initform 0.0)
   (view_range_availability
    :reader view_range_availability
    :initarg :view_range_availability
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass LKAlane (<LKAlane>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LKAlane>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LKAlane)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<LKAlane> is deprecated: use mobileye_msgs-msg:LKAlane instead.")))

(cl:ensure-generic-function 'lane_type-val :lambda-list '(m))
(cl:defmethod lane_type-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:lane_type-val is deprecated.  Use mobileye_msgs-msg:lane_type instead.")
  (lane_type m))

(cl:ensure-generic-function 'quality-val :lambda-list '(m))
(cl:defmethod quality-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:quality-val is deprecated.  Use mobileye_msgs-msg:quality instead.")
  (quality m))

(cl:ensure-generic-function 'model_degree-val :lambda-list '(m))
(cl:defmethod model_degree-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:model_degree-val is deprecated.  Use mobileye_msgs-msg:model_degree instead.")
  (model_degree m))

(cl:ensure-generic-function 'position_parameter_c0-val :lambda-list '(m))
(cl:defmethod position_parameter_c0-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:position_parameter_c0-val is deprecated.  Use mobileye_msgs-msg:position_parameter_c0 instead.")
  (position_parameter_c0 m))

(cl:ensure-generic-function 'curvature_parameter_c2-val :lambda-list '(m))
(cl:defmethod curvature_parameter_c2-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:curvature_parameter_c2-val is deprecated.  Use mobileye_msgs-msg:curvature_parameter_c2 instead.")
  (curvature_parameter_c2 m))

(cl:ensure-generic-function 'curvature_derivative_c3-val :lambda-list '(m))
(cl:defmethod curvature_derivative_c3-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:curvature_derivative_c3-val is deprecated.  Use mobileye_msgs-msg:curvature_derivative_c3 instead.")
  (curvature_derivative_c3 m))

(cl:ensure-generic-function 'width_marking-val :lambda-list '(m))
(cl:defmethod width_marking-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:width_marking-val is deprecated.  Use mobileye_msgs-msg:width_marking instead.")
  (width_marking m))

(cl:ensure-generic-function 'heading_angle_parameter_c1-val :lambda-list '(m))
(cl:defmethod heading_angle_parameter_c1-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:heading_angle_parameter_c1-val is deprecated.  Use mobileye_msgs-msg:heading_angle_parameter_c1 instead.")
  (heading_angle_parameter_c1 m))

(cl:ensure-generic-function 'view_range-val :lambda-list '(m))
(cl:defmethod view_range-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:view_range-val is deprecated.  Use mobileye_msgs-msg:view_range instead.")
  (view_range m))

(cl:ensure-generic-function 'view_range_availability-val :lambda-list '(m))
(cl:defmethod view_range_availability-val ((m <LKAlane>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:view_range_availability-val is deprecated.  Use mobileye_msgs-msg:view_range_availability instead.")
  (view_range_availability m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LKAlane>) ostream)
  "Serializes a message object of type '<LKAlane>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'lane_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'model_degree)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'position_parameter_c0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'curvature_parameter_c2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'curvature_derivative_c3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'width_marking))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_angle_parameter_c1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'view_range))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'view_range_availability) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LKAlane>) istream)
  "Deserializes a message object of type '<LKAlane>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'lane_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'model_degree)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'position_parameter_c0) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curvature_parameter_c2) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curvature_derivative_c3) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width_marking) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_angle_parameter_c1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'view_range) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'view_range_availability) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LKAlane>)))
  "Returns string type for a message object of type '<LKAlane>"
  "mobileye_msgs/LKAlane")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LKAlane)))
  "Returns string type for a message object of type 'LKAlane"
  "mobileye_msgs/LKAlane")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LKAlane>)))
  "Returns md5sum for a message object of type '<LKAlane>"
  "7b414dd7d22f435b47d4035bf3d8fde4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LKAlane)))
  "Returns md5sum for a message object of type 'LKAlane"
  "7b414dd7d22f435b47d4035bf3d8fde4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LKAlane>)))
  "Returns full string definition for message of type '<LKAlane>"
  (cl:format cl:nil "uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LKAlane)))
  "Returns full string definition for message of type 'LKAlane"
  (cl:format cl:nil "uint8 lane_type~%uint8 quality~%uint8 model_degree~%~%float32 position_parameter_c0~%float32 curvature_parameter_c2~%float32 curvature_derivative_c3~%float32 width_marking~%~%float32 heading_angle_parameter_c1~%float32 view_range~%bool view_range_availability~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LKAlane>))
  (cl:+ 0
     1
     1
     1
     4
     4
     4
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LKAlane>))
  "Converts a ROS message object to a list"
  (cl:list 'LKAlane
    (cl:cons ':lane_type (lane_type msg))
    (cl:cons ':quality (quality msg))
    (cl:cons ':model_degree (model_degree msg))
    (cl:cons ':position_parameter_c0 (position_parameter_c0 msg))
    (cl:cons ':curvature_parameter_c2 (curvature_parameter_c2 msg))
    (cl:cons ':curvature_derivative_c3 (curvature_derivative_c3 msg))
    (cl:cons ':width_marking (width_marking msg))
    (cl:cons ':heading_angle_parameter_c1 (heading_angle_parameter_c1 msg))
    (cl:cons ':view_range (view_range msg))
    (cl:cons ':view_range_availability (view_range_availability msg))
))
