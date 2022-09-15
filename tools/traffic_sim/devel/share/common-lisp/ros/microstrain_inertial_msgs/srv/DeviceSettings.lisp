; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude DeviceSettings-request.msg.html

(cl:defclass <DeviceSettings-request> (roslisp-msg-protocol:ros-message)
  ((function_selector
    :reader function_selector
    :initarg :function_selector
    :type cl:fixnum
    :initform 0))
)

(cl:defclass DeviceSettings-request (<DeviceSettings-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DeviceSettings-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DeviceSettings-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<DeviceSettings-request> is deprecated: use microstrain_inertial_msgs-srv:DeviceSettings-request instead.")))

(cl:ensure-generic-function 'function_selector-val :lambda-list '(m))
(cl:defmethod function_selector-val ((m <DeviceSettings-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:function_selector-val is deprecated.  Use microstrain_inertial_msgs-srv:function_selector instead.")
  (function_selector m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DeviceSettings-request>) ostream)
  "Serializes a message object of type '<DeviceSettings-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'function_selector)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DeviceSettings-request>) istream)
  "Deserializes a message object of type '<DeviceSettings-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'function_selector)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DeviceSettings-request>)))
  "Returns string type for a service object of type '<DeviceSettings-request>"
  "microstrain_inertial_msgs/DeviceSettingsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DeviceSettings-request)))
  "Returns string type for a service object of type 'DeviceSettings-request"
  "microstrain_inertial_msgs/DeviceSettingsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DeviceSettings-request>)))
  "Returns md5sum for a message object of type '<DeviceSettings-request>"
  "a5738bbd08ff2569a7464cd41b071fc3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DeviceSettings-request)))
  "Returns md5sum for a message object of type 'DeviceSettings-request"
  "a5738bbd08ff2569a7464cd41b071fc3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DeviceSettings-request>)))
  "Returns full string definition for message of type '<DeviceSettings-request>"
  (cl:format cl:nil "uint8 function_selector~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DeviceSettings-request)))
  "Returns full string definition for message of type 'DeviceSettings-request"
  (cl:format cl:nil "uint8 function_selector~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DeviceSettings-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DeviceSettings-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DeviceSettings-request
    (cl:cons ':function_selector (function_selector msg))
))
;//! \htmlinclude DeviceSettings-response.msg.html

(cl:defclass <DeviceSettings-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass DeviceSettings-response (<DeviceSettings-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DeviceSettings-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DeviceSettings-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<DeviceSettings-response> is deprecated: use microstrain_inertial_msgs-srv:DeviceSettings-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <DeviceSettings-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DeviceSettings-response>) ostream)
  "Serializes a message object of type '<DeviceSettings-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DeviceSettings-response>) istream)
  "Deserializes a message object of type '<DeviceSettings-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DeviceSettings-response>)))
  "Returns string type for a service object of type '<DeviceSettings-response>"
  "microstrain_inertial_msgs/DeviceSettingsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DeviceSettings-response)))
  "Returns string type for a service object of type 'DeviceSettings-response"
  "microstrain_inertial_msgs/DeviceSettingsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DeviceSettings-response>)))
  "Returns md5sum for a message object of type '<DeviceSettings-response>"
  "a5738bbd08ff2569a7464cd41b071fc3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DeviceSettings-response)))
  "Returns md5sum for a message object of type 'DeviceSettings-response"
  "a5738bbd08ff2569a7464cd41b071fc3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DeviceSettings-response>)))
  "Returns full string definition for message of type '<DeviceSettings-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DeviceSettings-response)))
  "Returns full string definition for message of type 'DeviceSettings-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DeviceSettings-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DeviceSettings-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DeviceSettings-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DeviceSettings)))
  'DeviceSettings-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DeviceSettings)))
  'DeviceSettings-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DeviceSettings)))
  "Returns string type for a service object of type '<DeviceSettings>"
  "microstrain_inertial_msgs/DeviceSettings")