; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetGyroBias-request.msg.html

(cl:defclass <SetGyroBias-request> (roslisp-msg-protocol:ros-message)
  ((bias
    :reader bias
    :initarg :bias
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetGyroBias-request (<SetGyroBias-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetGyroBias-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetGyroBias-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetGyroBias-request> is deprecated: use microstrain_inertial_msgs-srv:SetGyroBias-request instead.")))

(cl:ensure-generic-function 'bias-val :lambda-list '(m))
(cl:defmethod bias-val ((m <SetGyroBias-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:bias-val is deprecated.  Use microstrain_inertial_msgs-srv:bias instead.")
  (bias m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetGyroBias-request>) ostream)
  "Serializes a message object of type '<SetGyroBias-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bias) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetGyroBias-request>) istream)
  "Deserializes a message object of type '<SetGyroBias-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bias) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetGyroBias-request>)))
  "Returns string type for a service object of type '<SetGyroBias-request>"
  "microstrain_inertial_msgs/SetGyroBiasRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGyroBias-request)))
  "Returns string type for a service object of type 'SetGyroBias-request"
  "microstrain_inertial_msgs/SetGyroBiasRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetGyroBias-request>)))
  "Returns md5sum for a message object of type '<SetGyroBias-request>"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetGyroBias-request)))
  "Returns md5sum for a message object of type 'SetGyroBias-request"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetGyroBias-request>)))
  "Returns full string definition for message of type '<SetGyroBias-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetGyroBias-request)))
  "Returns full string definition for message of type 'SetGyroBias-request"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetGyroBias-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bias))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetGyroBias-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetGyroBias-request
    (cl:cons ':bias (bias msg))
))
;//! \htmlinclude SetGyroBias-response.msg.html

(cl:defclass <SetGyroBias-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetGyroBias-response (<SetGyroBias-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetGyroBias-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetGyroBias-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetGyroBias-response> is deprecated: use microstrain_inertial_msgs-srv:SetGyroBias-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetGyroBias-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetGyroBias-response>) ostream)
  "Serializes a message object of type '<SetGyroBias-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetGyroBias-response>) istream)
  "Deserializes a message object of type '<SetGyroBias-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetGyroBias-response>)))
  "Returns string type for a service object of type '<SetGyroBias-response>"
  "microstrain_inertial_msgs/SetGyroBiasResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGyroBias-response)))
  "Returns string type for a service object of type 'SetGyroBias-response"
  "microstrain_inertial_msgs/SetGyroBiasResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetGyroBias-response>)))
  "Returns md5sum for a message object of type '<SetGyroBias-response>"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetGyroBias-response)))
  "Returns md5sum for a message object of type 'SetGyroBias-response"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetGyroBias-response>)))
  "Returns full string definition for message of type '<SetGyroBias-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetGyroBias-response)))
  "Returns full string definition for message of type 'SetGyroBias-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetGyroBias-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetGyroBias-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetGyroBias-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetGyroBias)))
  'SetGyroBias-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetGyroBias)))
  'SetGyroBias-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGyroBias)))
  "Returns string type for a service object of type '<SetGyroBias>"
  "microstrain_inertial_msgs/SetGyroBias")