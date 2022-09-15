; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetHeadingSource-request.msg.html

(cl:defclass <SetHeadingSource-request> (roslisp-msg-protocol:ros-message)
  ((heading_source
    :reader heading_source
    :initarg :heading_source
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetHeadingSource-request (<SetHeadingSource-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetHeadingSource-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetHeadingSource-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetHeadingSource-request> is deprecated: use microstrain_inertial_msgs-srv:SetHeadingSource-request instead.")))

(cl:ensure-generic-function 'heading_source-val :lambda-list '(m))
(cl:defmethod heading_source-val ((m <SetHeadingSource-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:heading_source-val is deprecated.  Use microstrain_inertial_msgs-srv:heading_source instead.")
  (heading_source m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetHeadingSource-request>) ostream)
  "Serializes a message object of type '<SetHeadingSource-request>"
  (cl:let* ((signed (cl:slot-value msg 'heading_source)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetHeadingSource-request>) istream)
  "Deserializes a message object of type '<SetHeadingSource-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'heading_source) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetHeadingSource-request>)))
  "Returns string type for a service object of type '<SetHeadingSource-request>"
  "microstrain_inertial_msgs/SetHeadingSourceRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetHeadingSource-request)))
  "Returns string type for a service object of type 'SetHeadingSource-request"
  "microstrain_inertial_msgs/SetHeadingSourceRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetHeadingSource-request>)))
  "Returns md5sum for a message object of type '<SetHeadingSource-request>"
  "e390de146ace4f3cbedb9445dd2ef6f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetHeadingSource-request)))
  "Returns md5sum for a message object of type 'SetHeadingSource-request"
  "e390de146ace4f3cbedb9445dd2ef6f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetHeadingSource-request>)))
  "Returns full string definition for message of type '<SetHeadingSource-request>"
  (cl:format cl:nil "int8 heading_source~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetHeadingSource-request)))
  "Returns full string definition for message of type 'SetHeadingSource-request"
  (cl:format cl:nil "int8 heading_source~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetHeadingSource-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetHeadingSource-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetHeadingSource-request
    (cl:cons ':heading_source (heading_source msg))
))
;//! \htmlinclude SetHeadingSource-response.msg.html

(cl:defclass <SetHeadingSource-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetHeadingSource-response (<SetHeadingSource-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetHeadingSource-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetHeadingSource-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetHeadingSource-response> is deprecated: use microstrain_inertial_msgs-srv:SetHeadingSource-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetHeadingSource-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetHeadingSource-response>) ostream)
  "Serializes a message object of type '<SetHeadingSource-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetHeadingSource-response>) istream)
  "Deserializes a message object of type '<SetHeadingSource-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetHeadingSource-response>)))
  "Returns string type for a service object of type '<SetHeadingSource-response>"
  "microstrain_inertial_msgs/SetHeadingSourceResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetHeadingSource-response)))
  "Returns string type for a service object of type 'SetHeadingSource-response"
  "microstrain_inertial_msgs/SetHeadingSourceResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetHeadingSource-response>)))
  "Returns md5sum for a message object of type '<SetHeadingSource-response>"
  "e390de146ace4f3cbedb9445dd2ef6f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetHeadingSource-response)))
  "Returns md5sum for a message object of type 'SetHeadingSource-response"
  "e390de146ace4f3cbedb9445dd2ef6f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetHeadingSource-response>)))
  "Returns full string definition for message of type '<SetHeadingSource-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetHeadingSource-response)))
  "Returns full string definition for message of type 'SetHeadingSource-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetHeadingSource-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetHeadingSource-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetHeadingSource-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetHeadingSource)))
  'SetHeadingSource-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetHeadingSource)))
  'SetHeadingSource-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetHeadingSource)))
  "Returns string type for a service object of type '<SetHeadingSource>"
  "microstrain_inertial_msgs/SetHeadingSource")