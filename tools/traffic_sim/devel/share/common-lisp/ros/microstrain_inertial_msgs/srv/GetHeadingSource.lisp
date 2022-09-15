; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetHeadingSource-request.msg.html

(cl:defclass <GetHeadingSource-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetHeadingSource-request (<GetHeadingSource-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetHeadingSource-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetHeadingSource-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetHeadingSource-request> is deprecated: use microstrain_inertial_msgs-srv:GetHeadingSource-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetHeadingSource-request>) ostream)
  "Serializes a message object of type '<GetHeadingSource-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetHeadingSource-request>) istream)
  "Deserializes a message object of type '<GetHeadingSource-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetHeadingSource-request>)))
  "Returns string type for a service object of type '<GetHeadingSource-request>"
  "microstrain_inertial_msgs/GetHeadingSourceRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetHeadingSource-request)))
  "Returns string type for a service object of type 'GetHeadingSource-request"
  "microstrain_inertial_msgs/GetHeadingSourceRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetHeadingSource-request>)))
  "Returns md5sum for a message object of type '<GetHeadingSource-request>"
  "2f4a68a47587634cd4d34560ad178beb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetHeadingSource-request)))
  "Returns md5sum for a message object of type 'GetHeadingSource-request"
  "2f4a68a47587634cd4d34560ad178beb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetHeadingSource-request>)))
  "Returns full string definition for message of type '<GetHeadingSource-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetHeadingSource-request)))
  "Returns full string definition for message of type 'GetHeadingSource-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetHeadingSource-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetHeadingSource-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetHeadingSource-request
))
;//! \htmlinclude GetHeadingSource-response.msg.html

(cl:defclass <GetHeadingSource-response> (roslisp-msg-protocol:ros-message)
  ((heading_source
    :reader heading_source
    :initarg :heading_source
    :type cl:fixnum
    :initform 0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetHeadingSource-response (<GetHeadingSource-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetHeadingSource-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetHeadingSource-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetHeadingSource-response> is deprecated: use microstrain_inertial_msgs-srv:GetHeadingSource-response instead.")))

(cl:ensure-generic-function 'heading_source-val :lambda-list '(m))
(cl:defmethod heading_source-val ((m <GetHeadingSource-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:heading_source-val is deprecated.  Use microstrain_inertial_msgs-srv:heading_source instead.")
  (heading_source m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetHeadingSource-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetHeadingSource-response>) ostream)
  "Serializes a message object of type '<GetHeadingSource-response>"
  (cl:let* ((signed (cl:slot-value msg 'heading_source)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetHeadingSource-response>) istream)
  "Deserializes a message object of type '<GetHeadingSource-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'heading_source) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetHeadingSource-response>)))
  "Returns string type for a service object of type '<GetHeadingSource-response>"
  "microstrain_inertial_msgs/GetHeadingSourceResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetHeadingSource-response)))
  "Returns string type for a service object of type 'GetHeadingSource-response"
  "microstrain_inertial_msgs/GetHeadingSourceResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetHeadingSource-response>)))
  "Returns md5sum for a message object of type '<GetHeadingSource-response>"
  "2f4a68a47587634cd4d34560ad178beb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetHeadingSource-response)))
  "Returns md5sum for a message object of type 'GetHeadingSource-response"
  "2f4a68a47587634cd4d34560ad178beb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetHeadingSource-response>)))
  "Returns full string definition for message of type '<GetHeadingSource-response>"
  (cl:format cl:nil "int8 heading_source~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetHeadingSource-response)))
  "Returns full string definition for message of type 'GetHeadingSource-response"
  (cl:format cl:nil "int8 heading_source~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetHeadingSource-response>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetHeadingSource-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetHeadingSource-response
    (cl:cons ':heading_source (heading_source msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetHeadingSource)))
  'GetHeadingSource-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetHeadingSource)))
  'GetHeadingSource-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetHeadingSource)))
  "Returns string type for a service object of type '<GetHeadingSource>"
  "microstrain_inertial_msgs/GetHeadingSource")