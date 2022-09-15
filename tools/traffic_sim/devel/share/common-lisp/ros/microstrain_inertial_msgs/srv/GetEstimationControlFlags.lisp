; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetEstimationControlFlags-request.msg.html

(cl:defclass <GetEstimationControlFlags-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetEstimationControlFlags-request (<GetEstimationControlFlags-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetEstimationControlFlags-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetEstimationControlFlags-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetEstimationControlFlags-request> is deprecated: use microstrain_inertial_msgs-srv:GetEstimationControlFlags-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetEstimationControlFlags-request>) ostream)
  "Serializes a message object of type '<GetEstimationControlFlags-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetEstimationControlFlags-request>) istream)
  "Deserializes a message object of type '<GetEstimationControlFlags-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetEstimationControlFlags-request>)))
  "Returns string type for a service object of type '<GetEstimationControlFlags-request>"
  "microstrain_inertial_msgs/GetEstimationControlFlagsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetEstimationControlFlags-request)))
  "Returns string type for a service object of type 'GetEstimationControlFlags-request"
  "microstrain_inertial_msgs/GetEstimationControlFlagsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetEstimationControlFlags-request>)))
  "Returns md5sum for a message object of type '<GetEstimationControlFlags-request>"
  "20bb471857675e9f69991d48317a4755")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetEstimationControlFlags-request)))
  "Returns md5sum for a message object of type 'GetEstimationControlFlags-request"
  "20bb471857675e9f69991d48317a4755")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetEstimationControlFlags-request>)))
  "Returns full string definition for message of type '<GetEstimationControlFlags-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetEstimationControlFlags-request)))
  "Returns full string definition for message of type 'GetEstimationControlFlags-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetEstimationControlFlags-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetEstimationControlFlags-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetEstimationControlFlags-request
))
;//! \htmlinclude GetEstimationControlFlags-response.msg.html

(cl:defclass <GetEstimationControlFlags-response> (roslisp-msg-protocol:ros-message)
  ((flags
    :reader flags
    :initarg :flags
    :type cl:fixnum
    :initform 0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetEstimationControlFlags-response (<GetEstimationControlFlags-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetEstimationControlFlags-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetEstimationControlFlags-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetEstimationControlFlags-response> is deprecated: use microstrain_inertial_msgs-srv:GetEstimationControlFlags-response instead.")))

(cl:ensure-generic-function 'flags-val :lambda-list '(m))
(cl:defmethod flags-val ((m <GetEstimationControlFlags-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:flags-val is deprecated.  Use microstrain_inertial_msgs-srv:flags instead.")
  (flags m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetEstimationControlFlags-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetEstimationControlFlags-response>) ostream)
  "Serializes a message object of type '<GetEstimationControlFlags-response>"
  (cl:let* ((signed (cl:slot-value msg 'flags)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetEstimationControlFlags-response>) istream)
  "Deserializes a message object of type '<GetEstimationControlFlags-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'flags) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetEstimationControlFlags-response>)))
  "Returns string type for a service object of type '<GetEstimationControlFlags-response>"
  "microstrain_inertial_msgs/GetEstimationControlFlagsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetEstimationControlFlags-response)))
  "Returns string type for a service object of type 'GetEstimationControlFlags-response"
  "microstrain_inertial_msgs/GetEstimationControlFlagsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetEstimationControlFlags-response>)))
  "Returns md5sum for a message object of type '<GetEstimationControlFlags-response>"
  "20bb471857675e9f69991d48317a4755")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetEstimationControlFlags-response)))
  "Returns md5sum for a message object of type 'GetEstimationControlFlags-response"
  "20bb471857675e9f69991d48317a4755")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetEstimationControlFlags-response>)))
  "Returns full string definition for message of type '<GetEstimationControlFlags-response>"
  (cl:format cl:nil "int8 flags~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetEstimationControlFlags-response)))
  "Returns full string definition for message of type 'GetEstimationControlFlags-response"
  (cl:format cl:nil "int8 flags~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetEstimationControlFlags-response>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetEstimationControlFlags-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetEstimationControlFlags-response
    (cl:cons ':flags (flags msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetEstimationControlFlags)))
  'GetEstimationControlFlags-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetEstimationControlFlags)))
  'GetEstimationControlFlags-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetEstimationControlFlags)))
  "Returns string type for a service object of type '<GetEstimationControlFlags>"
  "microstrain_inertial_msgs/GetEstimationControlFlags")