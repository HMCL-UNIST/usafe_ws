; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude InitFilterHeading-request.msg.html

(cl:defclass <InitFilterHeading-request> (roslisp-msg-protocol:ros-message)
  ((angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass InitFilterHeading-request (<InitFilterHeading-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InitFilterHeading-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InitFilterHeading-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<InitFilterHeading-request> is deprecated: use microstrain_inertial_msgs-srv:InitFilterHeading-request instead.")))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <InitFilterHeading-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:angle-val is deprecated.  Use microstrain_inertial_msgs-srv:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InitFilterHeading-request>) ostream)
  "Serializes a message object of type '<InitFilterHeading-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InitFilterHeading-request>) istream)
  "Deserializes a message object of type '<InitFilterHeading-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InitFilterHeading-request>)))
  "Returns string type for a service object of type '<InitFilterHeading-request>"
  "microstrain_inertial_msgs/InitFilterHeadingRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitFilterHeading-request)))
  "Returns string type for a service object of type 'InitFilterHeading-request"
  "microstrain_inertial_msgs/InitFilterHeadingRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InitFilterHeading-request>)))
  "Returns md5sum for a message object of type '<InitFilterHeading-request>"
  "194939c001a63802dc4131cae92cda22")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InitFilterHeading-request)))
  "Returns md5sum for a message object of type 'InitFilterHeading-request"
  "194939c001a63802dc4131cae92cda22")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InitFilterHeading-request>)))
  "Returns full string definition for message of type '<InitFilterHeading-request>"
  (cl:format cl:nil "float32 angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InitFilterHeading-request)))
  "Returns full string definition for message of type 'InitFilterHeading-request"
  (cl:format cl:nil "float32 angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InitFilterHeading-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InitFilterHeading-request>))
  "Converts a ROS message object to a list"
  (cl:list 'InitFilterHeading-request
    (cl:cons ':angle (angle msg))
))
;//! \htmlinclude InitFilterHeading-response.msg.html

(cl:defclass <InitFilterHeading-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass InitFilterHeading-response (<InitFilterHeading-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InitFilterHeading-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InitFilterHeading-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<InitFilterHeading-response> is deprecated: use microstrain_inertial_msgs-srv:InitFilterHeading-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <InitFilterHeading-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InitFilterHeading-response>) ostream)
  "Serializes a message object of type '<InitFilterHeading-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InitFilterHeading-response>) istream)
  "Deserializes a message object of type '<InitFilterHeading-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InitFilterHeading-response>)))
  "Returns string type for a service object of type '<InitFilterHeading-response>"
  "microstrain_inertial_msgs/InitFilterHeadingResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitFilterHeading-response)))
  "Returns string type for a service object of type 'InitFilterHeading-response"
  "microstrain_inertial_msgs/InitFilterHeadingResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InitFilterHeading-response>)))
  "Returns md5sum for a message object of type '<InitFilterHeading-response>"
  "194939c001a63802dc4131cae92cda22")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InitFilterHeading-response)))
  "Returns md5sum for a message object of type 'InitFilterHeading-response"
  "194939c001a63802dc4131cae92cda22")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InitFilterHeading-response>)))
  "Returns full string definition for message of type '<InitFilterHeading-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InitFilterHeading-response)))
  "Returns full string definition for message of type 'InitFilterHeading-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InitFilterHeading-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InitFilterHeading-response>))
  "Converts a ROS message object to a list"
  (cl:list 'InitFilterHeading-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'InitFilterHeading)))
  'InitFilterHeading-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'InitFilterHeading)))
  'InitFilterHeading-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitFilterHeading)))
  "Returns string type for a service object of type '<InitFilterHeading>"
  "microstrain_inertial_msgs/InitFilterHeading")