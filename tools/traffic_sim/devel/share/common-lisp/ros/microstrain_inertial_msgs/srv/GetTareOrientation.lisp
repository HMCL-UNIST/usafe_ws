; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetTareOrientation-request.msg.html

(cl:defclass <GetTareOrientation-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetTareOrientation-request (<GetTareOrientation-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetTareOrientation-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetTareOrientation-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetTareOrientation-request> is deprecated: use microstrain_inertial_msgs-srv:GetTareOrientation-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetTareOrientation-request>) ostream)
  "Serializes a message object of type '<GetTareOrientation-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetTareOrientation-request>) istream)
  "Deserializes a message object of type '<GetTareOrientation-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetTareOrientation-request>)))
  "Returns string type for a service object of type '<GetTareOrientation-request>"
  "microstrain_inertial_msgs/GetTareOrientationRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetTareOrientation-request)))
  "Returns string type for a service object of type 'GetTareOrientation-request"
  "microstrain_inertial_msgs/GetTareOrientationRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetTareOrientation-request>)))
  "Returns md5sum for a message object of type '<GetTareOrientation-request>"
  "87ecd93a5c8679ed9b5ed373f0919456")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetTareOrientation-request)))
  "Returns md5sum for a message object of type 'GetTareOrientation-request"
  "87ecd93a5c8679ed9b5ed373f0919456")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetTareOrientation-request>)))
  "Returns full string definition for message of type '<GetTareOrientation-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetTareOrientation-request)))
  "Returns full string definition for message of type 'GetTareOrientation-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetTareOrientation-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetTareOrientation-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetTareOrientation-request
))
;//! \htmlinclude GetTareOrientation-response.msg.html

(cl:defclass <GetTareOrientation-response> (roslisp-msg-protocol:ros-message)
  ((axis
    :reader axis
    :initarg :axis
    :type cl:fixnum
    :initform 0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetTareOrientation-response (<GetTareOrientation-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetTareOrientation-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetTareOrientation-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetTareOrientation-response> is deprecated: use microstrain_inertial_msgs-srv:GetTareOrientation-response instead.")))

(cl:ensure-generic-function 'axis-val :lambda-list '(m))
(cl:defmethod axis-val ((m <GetTareOrientation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:axis-val is deprecated.  Use microstrain_inertial_msgs-srv:axis instead.")
  (axis m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetTareOrientation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetTareOrientation-response>) ostream)
  "Serializes a message object of type '<GetTareOrientation-response>"
  (cl:let* ((signed (cl:slot-value msg 'axis)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetTareOrientation-response>) istream)
  "Deserializes a message object of type '<GetTareOrientation-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'axis) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetTareOrientation-response>)))
  "Returns string type for a service object of type '<GetTareOrientation-response>"
  "microstrain_inertial_msgs/GetTareOrientationResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetTareOrientation-response)))
  "Returns string type for a service object of type 'GetTareOrientation-response"
  "microstrain_inertial_msgs/GetTareOrientationResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetTareOrientation-response>)))
  "Returns md5sum for a message object of type '<GetTareOrientation-response>"
  "87ecd93a5c8679ed9b5ed373f0919456")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetTareOrientation-response)))
  "Returns md5sum for a message object of type 'GetTareOrientation-response"
  "87ecd93a5c8679ed9b5ed373f0919456")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetTareOrientation-response>)))
  "Returns full string definition for message of type '<GetTareOrientation-response>"
  (cl:format cl:nil "int8 axis~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetTareOrientation-response)))
  "Returns full string definition for message of type 'GetTareOrientation-response"
  (cl:format cl:nil "int8 axis~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetTareOrientation-response>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetTareOrientation-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetTareOrientation-response
    (cl:cons ':axis (axis msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetTareOrientation)))
  'GetTareOrientation-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetTareOrientation)))
  'GetTareOrientation-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetTareOrientation)))
  "Returns string type for a service object of type '<GetTareOrientation>"
  "microstrain_inertial_msgs/GetTareOrientation")