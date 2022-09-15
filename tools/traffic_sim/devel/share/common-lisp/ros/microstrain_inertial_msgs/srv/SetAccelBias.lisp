; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetAccelBias-request.msg.html

(cl:defclass <SetAccelBias-request> (roslisp-msg-protocol:ros-message)
  ((bias
    :reader bias
    :initarg :bias
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetAccelBias-request (<SetAccelBias-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetAccelBias-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetAccelBias-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetAccelBias-request> is deprecated: use microstrain_inertial_msgs-srv:SetAccelBias-request instead.")))

(cl:ensure-generic-function 'bias-val :lambda-list '(m))
(cl:defmethod bias-val ((m <SetAccelBias-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:bias-val is deprecated.  Use microstrain_inertial_msgs-srv:bias instead.")
  (bias m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetAccelBias-request>) ostream)
  "Serializes a message object of type '<SetAccelBias-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bias) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetAccelBias-request>) istream)
  "Deserializes a message object of type '<SetAccelBias-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bias) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetAccelBias-request>)))
  "Returns string type for a service object of type '<SetAccelBias-request>"
  "microstrain_inertial_msgs/SetAccelBiasRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetAccelBias-request)))
  "Returns string type for a service object of type 'SetAccelBias-request"
  "microstrain_inertial_msgs/SetAccelBiasRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetAccelBias-request>)))
  "Returns md5sum for a message object of type '<SetAccelBias-request>"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetAccelBias-request)))
  "Returns md5sum for a message object of type 'SetAccelBias-request"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetAccelBias-request>)))
  "Returns full string definition for message of type '<SetAccelBias-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetAccelBias-request)))
  "Returns full string definition for message of type 'SetAccelBias-request"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetAccelBias-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bias))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetAccelBias-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetAccelBias-request
    (cl:cons ':bias (bias msg))
))
;//! \htmlinclude SetAccelBias-response.msg.html

(cl:defclass <SetAccelBias-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetAccelBias-response (<SetAccelBias-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetAccelBias-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetAccelBias-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetAccelBias-response> is deprecated: use microstrain_inertial_msgs-srv:SetAccelBias-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetAccelBias-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetAccelBias-response>) ostream)
  "Serializes a message object of type '<SetAccelBias-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetAccelBias-response>) istream)
  "Deserializes a message object of type '<SetAccelBias-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetAccelBias-response>)))
  "Returns string type for a service object of type '<SetAccelBias-response>"
  "microstrain_inertial_msgs/SetAccelBiasResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetAccelBias-response)))
  "Returns string type for a service object of type 'SetAccelBias-response"
  "microstrain_inertial_msgs/SetAccelBiasResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetAccelBias-response>)))
  "Returns md5sum for a message object of type '<SetAccelBias-response>"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetAccelBias-response)))
  "Returns md5sum for a message object of type 'SetAccelBias-response"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetAccelBias-response>)))
  "Returns full string definition for message of type '<SetAccelBias-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetAccelBias-response)))
  "Returns full string definition for message of type 'SetAccelBias-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetAccelBias-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetAccelBias-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetAccelBias-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetAccelBias)))
  'SetAccelBias-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetAccelBias)))
  'SetAccelBias-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetAccelBias)))
  "Returns string type for a service object of type '<SetAccelBias>"
  "microstrain_inertial_msgs/SetAccelBias")