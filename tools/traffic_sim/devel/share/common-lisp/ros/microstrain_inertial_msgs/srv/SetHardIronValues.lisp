; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetHardIronValues-request.msg.html

(cl:defclass <SetHardIronValues-request> (roslisp-msg-protocol:ros-message)
  ((bias
    :reader bias
    :initarg :bias
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetHardIronValues-request (<SetHardIronValues-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetHardIronValues-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetHardIronValues-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetHardIronValues-request> is deprecated: use microstrain_inertial_msgs-srv:SetHardIronValues-request instead.")))

(cl:ensure-generic-function 'bias-val :lambda-list '(m))
(cl:defmethod bias-val ((m <SetHardIronValues-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:bias-val is deprecated.  Use microstrain_inertial_msgs-srv:bias instead.")
  (bias m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetHardIronValues-request>) ostream)
  "Serializes a message object of type '<SetHardIronValues-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bias) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetHardIronValues-request>) istream)
  "Deserializes a message object of type '<SetHardIronValues-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bias) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetHardIronValues-request>)))
  "Returns string type for a service object of type '<SetHardIronValues-request>"
  "microstrain_inertial_msgs/SetHardIronValuesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetHardIronValues-request)))
  "Returns string type for a service object of type 'SetHardIronValues-request"
  "microstrain_inertial_msgs/SetHardIronValuesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetHardIronValues-request>)))
  "Returns md5sum for a message object of type '<SetHardIronValues-request>"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetHardIronValues-request)))
  "Returns md5sum for a message object of type 'SetHardIronValues-request"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetHardIronValues-request>)))
  "Returns full string definition for message of type '<SetHardIronValues-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetHardIronValues-request)))
  "Returns full string definition for message of type 'SetHardIronValues-request"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetHardIronValues-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bias))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetHardIronValues-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetHardIronValues-request
    (cl:cons ':bias (bias msg))
))
;//! \htmlinclude SetHardIronValues-response.msg.html

(cl:defclass <SetHardIronValues-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetHardIronValues-response (<SetHardIronValues-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetHardIronValues-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetHardIronValues-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetHardIronValues-response> is deprecated: use microstrain_inertial_msgs-srv:SetHardIronValues-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetHardIronValues-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetHardIronValues-response>) ostream)
  "Serializes a message object of type '<SetHardIronValues-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetHardIronValues-response>) istream)
  "Deserializes a message object of type '<SetHardIronValues-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetHardIronValues-response>)))
  "Returns string type for a service object of type '<SetHardIronValues-response>"
  "microstrain_inertial_msgs/SetHardIronValuesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetHardIronValues-response)))
  "Returns string type for a service object of type 'SetHardIronValues-response"
  "microstrain_inertial_msgs/SetHardIronValuesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetHardIronValues-response>)))
  "Returns md5sum for a message object of type '<SetHardIronValues-response>"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetHardIronValues-response)))
  "Returns md5sum for a message object of type 'SetHardIronValues-response"
  "7f2cf85b824b45f9f629310ab233f3c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetHardIronValues-response>)))
  "Returns full string definition for message of type '<SetHardIronValues-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetHardIronValues-response)))
  "Returns full string definition for message of type 'SetHardIronValues-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetHardIronValues-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetHardIronValues-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetHardIronValues-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetHardIronValues)))
  'SetHardIronValues-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetHardIronValues)))
  'SetHardIronValues-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetHardIronValues)))
  "Returns string type for a service object of type '<SetHardIronValues>"
  "microstrain_inertial_msgs/SetHardIronValues")