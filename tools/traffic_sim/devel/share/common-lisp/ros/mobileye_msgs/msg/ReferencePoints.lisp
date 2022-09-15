; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude ReferencePoints.msg.html

(cl:defclass <ReferencePoints> (roslisp-msg-protocol:ros-message)
  ((ref_point1_position
    :reader ref_point1_position
    :initarg :ref_point1_position
    :type cl:float
    :initform 0.0)
   (ref_point1_distance
    :reader ref_point1_distance
    :initarg :ref_point1_distance
    :type cl:float
    :initform 0.0)
   (ref_point1_validity
    :reader ref_point1_validity
    :initarg :ref_point1_validity
    :type cl:boolean
    :initform cl:nil)
   (ref_point2_position
    :reader ref_point2_position
    :initarg :ref_point2_position
    :type cl:float
    :initform 0.0)
   (ref_point2_distance
    :reader ref_point2_distance
    :initarg :ref_point2_distance
    :type cl:float
    :initform 0.0)
   (ref_point2_validity
    :reader ref_point2_validity
    :initarg :ref_point2_validity
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass ReferencePoints (<ReferencePoints>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ReferencePoints>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ReferencePoints)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<ReferencePoints> is deprecated: use mobileye_msgs-msg:ReferencePoints instead.")))

(cl:ensure-generic-function 'ref_point1_position-val :lambda-list '(m))
(cl:defmethod ref_point1_position-val ((m <ReferencePoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ref_point1_position-val is deprecated.  Use mobileye_msgs-msg:ref_point1_position instead.")
  (ref_point1_position m))

(cl:ensure-generic-function 'ref_point1_distance-val :lambda-list '(m))
(cl:defmethod ref_point1_distance-val ((m <ReferencePoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ref_point1_distance-val is deprecated.  Use mobileye_msgs-msg:ref_point1_distance instead.")
  (ref_point1_distance m))

(cl:ensure-generic-function 'ref_point1_validity-val :lambda-list '(m))
(cl:defmethod ref_point1_validity-val ((m <ReferencePoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ref_point1_validity-val is deprecated.  Use mobileye_msgs-msg:ref_point1_validity instead.")
  (ref_point1_validity m))

(cl:ensure-generic-function 'ref_point2_position-val :lambda-list '(m))
(cl:defmethod ref_point2_position-val ((m <ReferencePoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ref_point2_position-val is deprecated.  Use mobileye_msgs-msg:ref_point2_position instead.")
  (ref_point2_position m))

(cl:ensure-generic-function 'ref_point2_distance-val :lambda-list '(m))
(cl:defmethod ref_point2_distance-val ((m <ReferencePoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ref_point2_distance-val is deprecated.  Use mobileye_msgs-msg:ref_point2_distance instead.")
  (ref_point2_distance m))

(cl:ensure-generic-function 'ref_point2_validity-val :lambda-list '(m))
(cl:defmethod ref_point2_validity-val ((m <ReferencePoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:ref_point2_validity-val is deprecated.  Use mobileye_msgs-msg:ref_point2_validity instead.")
  (ref_point2_validity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ReferencePoints>) ostream)
  "Serializes a message object of type '<ReferencePoints>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ref_point1_position))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ref_point1_distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ref_point1_validity) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ref_point2_position))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ref_point2_distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ref_point2_validity) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ReferencePoints>) istream)
  "Deserializes a message object of type '<ReferencePoints>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ref_point1_position) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ref_point1_distance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'ref_point1_validity) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ref_point2_position) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ref_point2_distance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'ref_point2_validity) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ReferencePoints>)))
  "Returns string type for a message object of type '<ReferencePoints>"
  "mobileye_msgs/ReferencePoints")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ReferencePoints)))
  "Returns string type for a message object of type 'ReferencePoints"
  "mobileye_msgs/ReferencePoints")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ReferencePoints>)))
  "Returns md5sum for a message object of type '<ReferencePoints>"
  "56eb2a2d0b9b9695b81746d73432e3b8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ReferencePoints)))
  "Returns md5sum for a message object of type 'ReferencePoints"
  "56eb2a2d0b9b9695b81746d73432e3b8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ReferencePoints>)))
  "Returns full string definition for message of type '<ReferencePoints>"
  (cl:format cl:nil "float32 ref_point1_position~%float32 ref_point1_distance~%bool ref_point1_validity~%float32 ref_point2_position~%float32 ref_point2_distance~%bool ref_point2_validity~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ReferencePoints)))
  "Returns full string definition for message of type 'ReferencePoints"
  (cl:format cl:nil "float32 ref_point1_position~%float32 ref_point1_distance~%bool ref_point1_validity~%float32 ref_point2_position~%float32 ref_point2_distance~%bool ref_point2_validity~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ReferencePoints>))
  (cl:+ 0
     4
     4
     1
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ReferencePoints>))
  "Converts a ROS message object to a list"
  (cl:list 'ReferencePoints
    (cl:cons ':ref_point1_position (ref_point1_position msg))
    (cl:cons ':ref_point1_distance (ref_point1_distance msg))
    (cl:cons ':ref_point1_validity (ref_point1_validity msg))
    (cl:cons ':ref_point2_position (ref_point2_position msg))
    (cl:cons ':ref_point2_distance (ref_point2_distance msg))
    (cl:cons ':ref_point2_validity (ref_point2_validity msg))
))
