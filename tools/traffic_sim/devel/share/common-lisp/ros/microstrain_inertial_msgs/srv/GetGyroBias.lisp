; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetGyroBias-request.msg.html

(cl:defclass <GetGyroBias-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetGyroBias-request (<GetGyroBias-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetGyroBias-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetGyroBias-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetGyroBias-request> is deprecated: use microstrain_inertial_msgs-srv:GetGyroBias-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetGyroBias-request>) ostream)
  "Serializes a message object of type '<GetGyroBias-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetGyroBias-request>) istream)
  "Deserializes a message object of type '<GetGyroBias-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetGyroBias-request>)))
  "Returns string type for a service object of type '<GetGyroBias-request>"
  "microstrain_inertial_msgs/GetGyroBiasRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetGyroBias-request)))
  "Returns string type for a service object of type 'GetGyroBias-request"
  "microstrain_inertial_msgs/GetGyroBiasRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetGyroBias-request>)))
  "Returns md5sum for a message object of type '<GetGyroBias-request>"
  "9427c94a8464f80e7ccfb4c788698d94")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetGyroBias-request)))
  "Returns md5sum for a message object of type 'GetGyroBias-request"
  "9427c94a8464f80e7ccfb4c788698d94")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetGyroBias-request>)))
  "Returns full string definition for message of type '<GetGyroBias-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetGyroBias-request)))
  "Returns full string definition for message of type 'GetGyroBias-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetGyroBias-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetGyroBias-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetGyroBias-request
))
;//! \htmlinclude GetGyroBias-response.msg.html

(cl:defclass <GetGyroBias-response> (roslisp-msg-protocol:ros-message)
  ((bias
    :reader bias
    :initarg :bias
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetGyroBias-response (<GetGyroBias-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetGyroBias-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetGyroBias-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetGyroBias-response> is deprecated: use microstrain_inertial_msgs-srv:GetGyroBias-response instead.")))

(cl:ensure-generic-function 'bias-val :lambda-list '(m))
(cl:defmethod bias-val ((m <GetGyroBias-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:bias-val is deprecated.  Use microstrain_inertial_msgs-srv:bias instead.")
  (bias m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetGyroBias-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetGyroBias-response>) ostream)
  "Serializes a message object of type '<GetGyroBias-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bias) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetGyroBias-response>) istream)
  "Deserializes a message object of type '<GetGyroBias-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bias) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetGyroBias-response>)))
  "Returns string type for a service object of type '<GetGyroBias-response>"
  "microstrain_inertial_msgs/GetGyroBiasResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetGyroBias-response)))
  "Returns string type for a service object of type 'GetGyroBias-response"
  "microstrain_inertial_msgs/GetGyroBiasResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetGyroBias-response>)))
  "Returns md5sum for a message object of type '<GetGyroBias-response>"
  "9427c94a8464f80e7ccfb4c788698d94")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetGyroBias-response)))
  "Returns md5sum for a message object of type 'GetGyroBias-response"
  "9427c94a8464f80e7ccfb4c788698d94")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetGyroBias-response>)))
  "Returns full string definition for message of type '<GetGyroBias-response>"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetGyroBias-response)))
  "Returns full string definition for message of type 'GetGyroBias-response"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetGyroBias-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bias))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetGyroBias-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetGyroBias-response
    (cl:cons ':bias (bias msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetGyroBias)))
  'GetGyroBias-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetGyroBias)))
  'GetGyroBias-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetGyroBias)))
  "Returns string type for a service object of type '<GetGyroBias>"
  "microstrain_inertial_msgs/GetGyroBias")