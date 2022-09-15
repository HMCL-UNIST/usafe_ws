; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetRelativePositionReference-request.msg.html

(cl:defclass <GetRelativePositionReference-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetRelativePositionReference-request (<GetRelativePositionReference-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetRelativePositionReference-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetRelativePositionReference-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetRelativePositionReference-request> is deprecated: use microstrain_inertial_msgs-srv:GetRelativePositionReference-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetRelativePositionReference-request>) ostream)
  "Serializes a message object of type '<GetRelativePositionReference-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetRelativePositionReference-request>) istream)
  "Deserializes a message object of type '<GetRelativePositionReference-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetRelativePositionReference-request>)))
  "Returns string type for a service object of type '<GetRelativePositionReference-request>"
  "microstrain_inertial_msgs/GetRelativePositionReferenceRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetRelativePositionReference-request)))
  "Returns string type for a service object of type 'GetRelativePositionReference-request"
  "microstrain_inertial_msgs/GetRelativePositionReferenceRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetRelativePositionReference-request>)))
  "Returns md5sum for a message object of type '<GetRelativePositionReference-request>"
  "7778d2daa4ab0de5ddac855cca257e01")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetRelativePositionReference-request)))
  "Returns md5sum for a message object of type 'GetRelativePositionReference-request"
  "7778d2daa4ab0de5ddac855cca257e01")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetRelativePositionReference-request>)))
  "Returns full string definition for message of type '<GetRelativePositionReference-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetRelativePositionReference-request)))
  "Returns full string definition for message of type 'GetRelativePositionReference-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetRelativePositionReference-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetRelativePositionReference-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetRelativePositionReference-request
))
;//! \htmlinclude GetRelativePositionReference-response.msg.html

(cl:defclass <GetRelativePositionReference-response> (roslisp-msg-protocol:ros-message)
  ((source
    :reader source
    :initarg :source
    :type cl:fixnum
    :initform 0)
   (frame
    :reader frame
    :initarg :frame
    :type cl:fixnum
    :initform 0)
   (position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetRelativePositionReference-response (<GetRelativePositionReference-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetRelativePositionReference-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetRelativePositionReference-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetRelativePositionReference-response> is deprecated: use microstrain_inertial_msgs-srv:GetRelativePositionReference-response instead.")))

(cl:ensure-generic-function 'source-val :lambda-list '(m))
(cl:defmethod source-val ((m <GetRelativePositionReference-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:source-val is deprecated.  Use microstrain_inertial_msgs-srv:source instead.")
  (source m))

(cl:ensure-generic-function 'frame-val :lambda-list '(m))
(cl:defmethod frame-val ((m <GetRelativePositionReference-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:frame-val is deprecated.  Use microstrain_inertial_msgs-srv:frame instead.")
  (frame m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <GetRelativePositionReference-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:position-val is deprecated.  Use microstrain_inertial_msgs-srv:position instead.")
  (position m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetRelativePositionReference-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<GetRelativePositionReference-response>)))
    "Constants for message type '<GetRelativePositionReference-response>"
  '((:SOURCE_AUTO . 0)
    (:SOURCE_MANUAL . 1)
    (:FRAME_ECEF . 1)
    (:FRAME_LLH . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'GetRelativePositionReference-response)))
    "Constants for message type 'GetRelativePositionReference-response"
  '((:SOURCE_AUTO . 0)
    (:SOURCE_MANUAL . 1)
    (:FRAME_ECEF . 1)
    (:FRAME_LLH . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetRelativePositionReference-response>) ostream)
  "Serializes a message object of type '<GetRelativePositionReference-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'source)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'frame)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetRelativePositionReference-response>) istream)
  "Deserializes a message object of type '<GetRelativePositionReference-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'source)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'frame)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetRelativePositionReference-response>)))
  "Returns string type for a service object of type '<GetRelativePositionReference-response>"
  "microstrain_inertial_msgs/GetRelativePositionReferenceResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetRelativePositionReference-response)))
  "Returns string type for a service object of type 'GetRelativePositionReference-response"
  "microstrain_inertial_msgs/GetRelativePositionReferenceResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetRelativePositionReference-response>)))
  "Returns md5sum for a message object of type '<GetRelativePositionReference-response>"
  "7778d2daa4ab0de5ddac855cca257e01")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetRelativePositionReference-response)))
  "Returns md5sum for a message object of type 'GetRelativePositionReference-response"
  "7778d2daa4ab0de5ddac855cca257e01")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetRelativePositionReference-response>)))
  "Returns full string definition for message of type '<GetRelativePositionReference-response>"
  (cl:format cl:nil "uint8  source~%uint8  frame~%geometry_msgs/Vector3 position~%bool success~%~%uint8 SOURCE_AUTO   = 0  #RTK base station required  ~%uint8 SOURCE_MANUAL = 1  ~%uint8 FRAME_ECEF = 1  ~%uint8 FRAME_LLH  = 2  ~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetRelativePositionReference-response)))
  "Returns full string definition for message of type 'GetRelativePositionReference-response"
  (cl:format cl:nil "uint8  source~%uint8  frame~%geometry_msgs/Vector3 position~%bool success~%~%uint8 SOURCE_AUTO   = 0  #RTK base station required  ~%uint8 SOURCE_MANUAL = 1  ~%uint8 FRAME_ECEF = 1  ~%uint8 FRAME_LLH  = 2  ~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetRelativePositionReference-response>))
  (cl:+ 0
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetRelativePositionReference-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetRelativePositionReference-response
    (cl:cons ':source (source msg))
    (cl:cons ':frame (frame msg))
    (cl:cons ':position (position msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetRelativePositionReference)))
  'GetRelativePositionReference-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetRelativePositionReference)))
  'GetRelativePositionReference-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetRelativePositionReference)))
  "Returns string type for a service object of type '<GetRelativePositionReference>"
  "microstrain_inertial_msgs/GetRelativePositionReference")