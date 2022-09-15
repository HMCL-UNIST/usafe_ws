; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetRelativePositionReference-request.msg.html

(cl:defclass <SetRelativePositionReference-request> (roslisp-msg-protocol:ros-message)
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
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetRelativePositionReference-request (<SetRelativePositionReference-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetRelativePositionReference-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetRelativePositionReference-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetRelativePositionReference-request> is deprecated: use microstrain_inertial_msgs-srv:SetRelativePositionReference-request instead.")))

(cl:ensure-generic-function 'source-val :lambda-list '(m))
(cl:defmethod source-val ((m <SetRelativePositionReference-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:source-val is deprecated.  Use microstrain_inertial_msgs-srv:source instead.")
  (source m))

(cl:ensure-generic-function 'frame-val :lambda-list '(m))
(cl:defmethod frame-val ((m <SetRelativePositionReference-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:frame-val is deprecated.  Use microstrain_inertial_msgs-srv:frame instead.")
  (frame m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <SetRelativePositionReference-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:position-val is deprecated.  Use microstrain_inertial_msgs-srv:position instead.")
  (position m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<SetRelativePositionReference-request>)))
    "Constants for message type '<SetRelativePositionReference-request>"
  '((:SOURCE_AUTO . 0)
    (:SOURCE_MANUAL . 1)
    (:FRAME_ECEF . 1)
    (:FRAME_LLH . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'SetRelativePositionReference-request)))
    "Constants for message type 'SetRelativePositionReference-request"
  '((:SOURCE_AUTO . 0)
    (:SOURCE_MANUAL . 1)
    (:FRAME_ECEF . 1)
    (:FRAME_LLH . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetRelativePositionReference-request>) ostream)
  "Serializes a message object of type '<SetRelativePositionReference-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'source)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'frame)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetRelativePositionReference-request>) istream)
  "Deserializes a message object of type '<SetRelativePositionReference-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'source)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'frame)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetRelativePositionReference-request>)))
  "Returns string type for a service object of type '<SetRelativePositionReference-request>"
  "microstrain_inertial_msgs/SetRelativePositionReferenceRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRelativePositionReference-request)))
  "Returns string type for a service object of type 'SetRelativePositionReference-request"
  "microstrain_inertial_msgs/SetRelativePositionReferenceRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetRelativePositionReference-request>)))
  "Returns md5sum for a message object of type '<SetRelativePositionReference-request>"
  "322dca82c4e06e7f4805393b2e113aed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetRelativePositionReference-request)))
  "Returns md5sum for a message object of type 'SetRelativePositionReference-request"
  "322dca82c4e06e7f4805393b2e113aed")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetRelativePositionReference-request>)))
  "Returns full string definition for message of type '<SetRelativePositionReference-request>"
  (cl:format cl:nil "uint8  source~%uint8  frame~%geometry_msgs/Vector3 position~%~%uint8 SOURCE_AUTO   = 0  #RTK base station required~%uint8 SOURCE_MANUAL = 1  ~%uint8 FRAME_ECEF = 1  ~%uint8 FRAME_LLH  = 2  ~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetRelativePositionReference-request)))
  "Returns full string definition for message of type 'SetRelativePositionReference-request"
  (cl:format cl:nil "uint8  source~%uint8  frame~%geometry_msgs/Vector3 position~%~%uint8 SOURCE_AUTO   = 0  #RTK base station required~%uint8 SOURCE_MANUAL = 1  ~%uint8 FRAME_ECEF = 1  ~%uint8 FRAME_LLH  = 2  ~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetRelativePositionReference-request>))
  (cl:+ 0
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetRelativePositionReference-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetRelativePositionReference-request
    (cl:cons ':source (source msg))
    (cl:cons ':frame (frame msg))
    (cl:cons ':position (position msg))
))
;//! \htmlinclude SetRelativePositionReference-response.msg.html

(cl:defclass <SetRelativePositionReference-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetRelativePositionReference-response (<SetRelativePositionReference-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetRelativePositionReference-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetRelativePositionReference-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetRelativePositionReference-response> is deprecated: use microstrain_inertial_msgs-srv:SetRelativePositionReference-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetRelativePositionReference-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetRelativePositionReference-response>) ostream)
  "Serializes a message object of type '<SetRelativePositionReference-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetRelativePositionReference-response>) istream)
  "Deserializes a message object of type '<SetRelativePositionReference-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetRelativePositionReference-response>)))
  "Returns string type for a service object of type '<SetRelativePositionReference-response>"
  "microstrain_inertial_msgs/SetRelativePositionReferenceResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRelativePositionReference-response)))
  "Returns string type for a service object of type 'SetRelativePositionReference-response"
  "microstrain_inertial_msgs/SetRelativePositionReferenceResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetRelativePositionReference-response>)))
  "Returns md5sum for a message object of type '<SetRelativePositionReference-response>"
  "322dca82c4e06e7f4805393b2e113aed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetRelativePositionReference-response)))
  "Returns md5sum for a message object of type 'SetRelativePositionReference-response"
  "322dca82c4e06e7f4805393b2e113aed")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetRelativePositionReference-response>)))
  "Returns full string definition for message of type '<SetRelativePositionReference-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetRelativePositionReference-response)))
  "Returns full string definition for message of type 'SetRelativePositionReference-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetRelativePositionReference-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetRelativePositionReference-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetRelativePositionReference-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetRelativePositionReference)))
  'SetRelativePositionReference-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetRelativePositionReference)))
  'SetRelativePositionReference-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRelativePositionReference)))
  "Returns string type for a service object of type '<SetRelativePositionReference>"
  "microstrain_inertial_msgs/SetRelativePositionReference")