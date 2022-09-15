; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetTareOrientation-request.msg.html

(cl:defclass <SetTareOrientation-request> (roslisp-msg-protocol:ros-message)
  ((axis
    :reader axis
    :initarg :axis
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetTareOrientation-request (<SetTareOrientation-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetTareOrientation-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetTareOrientation-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetTareOrientation-request> is deprecated: use microstrain_inertial_msgs-srv:SetTareOrientation-request instead.")))

(cl:ensure-generic-function 'axis-val :lambda-list '(m))
(cl:defmethod axis-val ((m <SetTareOrientation-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:axis-val is deprecated.  Use microstrain_inertial_msgs-srv:axis instead.")
  (axis m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetTareOrientation-request>) ostream)
  "Serializes a message object of type '<SetTareOrientation-request>"
  (cl:let* ((signed (cl:slot-value msg 'axis)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetTareOrientation-request>) istream)
  "Deserializes a message object of type '<SetTareOrientation-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'axis) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetTareOrientation-request>)))
  "Returns string type for a service object of type '<SetTareOrientation-request>"
  "microstrain_inertial_msgs/SetTareOrientationRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTareOrientation-request)))
  "Returns string type for a service object of type 'SetTareOrientation-request"
  "microstrain_inertial_msgs/SetTareOrientationRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetTareOrientation-request>)))
  "Returns md5sum for a message object of type '<SetTareOrientation-request>"
  "75811cb68205ae4484ed796af90a6397")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetTareOrientation-request)))
  "Returns md5sum for a message object of type 'SetTareOrientation-request"
  "75811cb68205ae4484ed796af90a6397")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetTareOrientation-request>)))
  "Returns full string definition for message of type '<SetTareOrientation-request>"
  (cl:format cl:nil "int8 axis~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetTareOrientation-request)))
  "Returns full string definition for message of type 'SetTareOrientation-request"
  (cl:format cl:nil "int8 axis~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetTareOrientation-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetTareOrientation-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetTareOrientation-request
    (cl:cons ':axis (axis msg))
))
;//! \htmlinclude SetTareOrientation-response.msg.html

(cl:defclass <SetTareOrientation-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetTareOrientation-response (<SetTareOrientation-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetTareOrientation-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetTareOrientation-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetTareOrientation-response> is deprecated: use microstrain_inertial_msgs-srv:SetTareOrientation-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetTareOrientation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetTareOrientation-response>) ostream)
  "Serializes a message object of type '<SetTareOrientation-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetTareOrientation-response>) istream)
  "Deserializes a message object of type '<SetTareOrientation-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetTareOrientation-response>)))
  "Returns string type for a service object of type '<SetTareOrientation-response>"
  "microstrain_inertial_msgs/SetTareOrientationResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTareOrientation-response)))
  "Returns string type for a service object of type 'SetTareOrientation-response"
  "microstrain_inertial_msgs/SetTareOrientationResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetTareOrientation-response>)))
  "Returns md5sum for a message object of type '<SetTareOrientation-response>"
  "75811cb68205ae4484ed796af90a6397")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetTareOrientation-response)))
  "Returns md5sum for a message object of type 'SetTareOrientation-response"
  "75811cb68205ae4484ed796af90a6397")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetTareOrientation-response>)))
  "Returns full string definition for message of type '<SetTareOrientation-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetTareOrientation-response)))
  "Returns full string definition for message of type 'SetTareOrientation-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetTareOrientation-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetTareOrientation-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetTareOrientation-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetTareOrientation)))
  'SetTareOrientation-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetTareOrientation)))
  'SetTareOrientation-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTareOrientation)))
  "Returns string type for a service object of type '<SetTareOrientation>"
  "microstrain_inertial_msgs/SetTareOrientation")