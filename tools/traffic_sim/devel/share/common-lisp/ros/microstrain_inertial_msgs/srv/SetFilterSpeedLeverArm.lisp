; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetFilterSpeedLeverArm-request.msg.html

(cl:defclass <SetFilterSpeedLeverArm-request> (roslisp-msg-protocol:ros-message)
  ((offset
    :reader offset
    :initarg :offset
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetFilterSpeedLeverArm-request (<SetFilterSpeedLeverArm-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetFilterSpeedLeverArm-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetFilterSpeedLeverArm-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetFilterSpeedLeverArm-request> is deprecated: use microstrain_inertial_msgs-srv:SetFilterSpeedLeverArm-request instead.")))

(cl:ensure-generic-function 'offset-val :lambda-list '(m))
(cl:defmethod offset-val ((m <SetFilterSpeedLeverArm-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:offset-val is deprecated.  Use microstrain_inertial_msgs-srv:offset instead.")
  (offset m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetFilterSpeedLeverArm-request>) ostream)
  "Serializes a message object of type '<SetFilterSpeedLeverArm-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'offset) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetFilterSpeedLeverArm-request>) istream)
  "Deserializes a message object of type '<SetFilterSpeedLeverArm-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'offset) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetFilterSpeedLeverArm-request>)))
  "Returns string type for a service object of type '<SetFilterSpeedLeverArm-request>"
  "microstrain_inertial_msgs/SetFilterSpeedLeverArmRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFilterSpeedLeverArm-request)))
  "Returns string type for a service object of type 'SetFilterSpeedLeverArm-request"
  "microstrain_inertial_msgs/SetFilterSpeedLeverArmRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetFilterSpeedLeverArm-request>)))
  "Returns md5sum for a message object of type '<SetFilterSpeedLeverArm-request>"
  "17d27ff1259ce523baf9de57b7c37e18")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetFilterSpeedLeverArm-request)))
  "Returns md5sum for a message object of type 'SetFilterSpeedLeverArm-request"
  "17d27ff1259ce523baf9de57b7c37e18")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetFilterSpeedLeverArm-request>)))
  "Returns full string definition for message of type '<SetFilterSpeedLeverArm-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 offset~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetFilterSpeedLeverArm-request)))
  "Returns full string definition for message of type 'SetFilterSpeedLeverArm-request"
  (cl:format cl:nil "geometry_msgs/Vector3 offset~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetFilterSpeedLeverArm-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'offset))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetFilterSpeedLeverArm-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetFilterSpeedLeverArm-request
    (cl:cons ':offset (offset msg))
))
;//! \htmlinclude SetFilterSpeedLeverArm-response.msg.html

(cl:defclass <SetFilterSpeedLeverArm-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetFilterSpeedLeverArm-response (<SetFilterSpeedLeverArm-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetFilterSpeedLeverArm-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetFilterSpeedLeverArm-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetFilterSpeedLeverArm-response> is deprecated: use microstrain_inertial_msgs-srv:SetFilterSpeedLeverArm-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetFilterSpeedLeverArm-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetFilterSpeedLeverArm-response>) ostream)
  "Serializes a message object of type '<SetFilterSpeedLeverArm-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetFilterSpeedLeverArm-response>) istream)
  "Deserializes a message object of type '<SetFilterSpeedLeverArm-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetFilterSpeedLeverArm-response>)))
  "Returns string type for a service object of type '<SetFilterSpeedLeverArm-response>"
  "microstrain_inertial_msgs/SetFilterSpeedLeverArmResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFilterSpeedLeverArm-response)))
  "Returns string type for a service object of type 'SetFilterSpeedLeverArm-response"
  "microstrain_inertial_msgs/SetFilterSpeedLeverArmResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetFilterSpeedLeverArm-response>)))
  "Returns md5sum for a message object of type '<SetFilterSpeedLeverArm-response>"
  "17d27ff1259ce523baf9de57b7c37e18")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetFilterSpeedLeverArm-response)))
  "Returns md5sum for a message object of type 'SetFilterSpeedLeverArm-response"
  "17d27ff1259ce523baf9de57b7c37e18")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetFilterSpeedLeverArm-response>)))
  "Returns full string definition for message of type '<SetFilterSpeedLeverArm-response>"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetFilterSpeedLeverArm-response)))
  "Returns full string definition for message of type 'SetFilterSpeedLeverArm-response"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetFilterSpeedLeverArm-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetFilterSpeedLeverArm-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetFilterSpeedLeverArm-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetFilterSpeedLeverArm)))
  'SetFilterSpeedLeverArm-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetFilterSpeedLeverArm)))
  'SetFilterSpeedLeverArm-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetFilterSpeedLeverArm)))
  "Returns string type for a service object of type '<SetFilterSpeedLeverArm>"
  "microstrain_inertial_msgs/SetFilterSpeedLeverArm")