; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetEstimationControlFlags-request.msg.html

(cl:defclass <SetEstimationControlFlags-request> (roslisp-msg-protocol:ros-message)
  ((flags
    :reader flags
    :initarg :flags
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetEstimationControlFlags-request (<SetEstimationControlFlags-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetEstimationControlFlags-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetEstimationControlFlags-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetEstimationControlFlags-request> is deprecated: use microstrain_inertial_msgs-srv:SetEstimationControlFlags-request instead.")))

(cl:ensure-generic-function 'flags-val :lambda-list '(m))
(cl:defmethod flags-val ((m <SetEstimationControlFlags-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:flags-val is deprecated.  Use microstrain_inertial_msgs-srv:flags instead.")
  (flags m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<SetEstimationControlFlags-request>)))
    "Constants for message type '<SetEstimationControlFlags-request>"
  '((:GYRO_BIAS_ESTIMATION . 1)
    (:HARD_IRON_AUTO_CALIBRATION . 32)
    (:SOFT_IRON_AUTO_CALIBRATION . 64))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'SetEstimationControlFlags-request)))
    "Constants for message type 'SetEstimationControlFlags-request"
  '((:GYRO_BIAS_ESTIMATION . 1)
    (:HARD_IRON_AUTO_CALIBRATION . 32)
    (:SOFT_IRON_AUTO_CALIBRATION . 64))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetEstimationControlFlags-request>) ostream)
  "Serializes a message object of type '<SetEstimationControlFlags-request>"
  (cl:let* ((signed (cl:slot-value msg 'flags)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetEstimationControlFlags-request>) istream)
  "Deserializes a message object of type '<SetEstimationControlFlags-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'flags) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetEstimationControlFlags-request>)))
  "Returns string type for a service object of type '<SetEstimationControlFlags-request>"
  "microstrain_inertial_msgs/SetEstimationControlFlagsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetEstimationControlFlags-request)))
  "Returns string type for a service object of type 'SetEstimationControlFlags-request"
  "microstrain_inertial_msgs/SetEstimationControlFlagsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetEstimationControlFlags-request>)))
  "Returns md5sum for a message object of type '<SetEstimationControlFlags-request>"
  "7efd025d74deaecd09a7eaf56530e702")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetEstimationControlFlags-request)))
  "Returns md5sum for a message object of type 'SetEstimationControlFlags-request"
  "7efd025d74deaecd09a7eaf56530e702")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetEstimationControlFlags-request>)))
  "Returns full string definition for message of type '<SetEstimationControlFlags-request>"
  (cl:format cl:nil "int8 GYRO_BIAS_ESTIMATION=1~%int8 HARD_IRON_AUTO_CALIBRATION=32~%int8 SOFT_IRON_AUTO_CALIBRATION=64~%int8 flags~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetEstimationControlFlags-request)))
  "Returns full string definition for message of type 'SetEstimationControlFlags-request"
  (cl:format cl:nil "int8 GYRO_BIAS_ESTIMATION=1~%int8 HARD_IRON_AUTO_CALIBRATION=32~%int8 SOFT_IRON_AUTO_CALIBRATION=64~%int8 flags~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetEstimationControlFlags-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetEstimationControlFlags-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetEstimationControlFlags-request
    (cl:cons ':flags (flags msg))
))
;//! \htmlinclude SetEstimationControlFlags-response.msg.html

(cl:defclass <SetEstimationControlFlags-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetEstimationControlFlags-response (<SetEstimationControlFlags-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetEstimationControlFlags-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetEstimationControlFlags-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetEstimationControlFlags-response> is deprecated: use microstrain_inertial_msgs-srv:SetEstimationControlFlags-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetEstimationControlFlags-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetEstimationControlFlags-response>) ostream)
  "Serializes a message object of type '<SetEstimationControlFlags-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetEstimationControlFlags-response>) istream)
  "Deserializes a message object of type '<SetEstimationControlFlags-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetEstimationControlFlags-response>)))
  "Returns string type for a service object of type '<SetEstimationControlFlags-response>"
  "microstrain_inertial_msgs/SetEstimationControlFlagsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetEstimationControlFlags-response)))
  "Returns string type for a service object of type 'SetEstimationControlFlags-response"
  "microstrain_inertial_msgs/SetEstimationControlFlagsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetEstimationControlFlags-response>)))
  "Returns md5sum for a message object of type '<SetEstimationControlFlags-response>"
  "7efd025d74deaecd09a7eaf56530e702")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetEstimationControlFlags-response)))
  "Returns md5sum for a message object of type 'SetEstimationControlFlags-response"
  "7efd025d74deaecd09a7eaf56530e702")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetEstimationControlFlags-response>)))
  "Returns full string definition for message of type '<SetEstimationControlFlags-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetEstimationControlFlags-response)))
  "Returns full string definition for message of type 'SetEstimationControlFlags-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetEstimationControlFlags-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetEstimationControlFlags-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetEstimationControlFlags-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetEstimationControlFlags)))
  'SetEstimationControlFlags-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetEstimationControlFlags)))
  'SetEstimationControlFlags-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetEstimationControlFlags)))
  "Returns string type for a service object of type '<SetEstimationControlFlags>"
  "microstrain_inertial_msgs/SetEstimationControlFlags")