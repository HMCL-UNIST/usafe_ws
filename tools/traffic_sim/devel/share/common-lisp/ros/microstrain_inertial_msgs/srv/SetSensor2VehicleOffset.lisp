; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetSensor2VehicleOffset-request.msg.html

(cl:defclass <SetSensor2VehicleOffset-request> (roslisp-msg-protocol:ros-message)
  ((offset
    :reader offset
    :initarg :offset
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetSensor2VehicleOffset-request (<SetSensor2VehicleOffset-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetSensor2VehicleOffset-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetSensor2VehicleOffset-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetSensor2VehicleOffset-request> is deprecated: use microstrain_inertial_msgs-srv:SetSensor2VehicleOffset-request instead.")))

(cl:ensure-generic-function 'offset-val :lambda-list '(m))
(cl:defmethod offset-val ((m <SetSensor2VehicleOffset-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:offset-val is deprecated.  Use microstrain_inertial_msgs-srv:offset instead.")
  (offset m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetSensor2VehicleOffset-request>) ostream)
  "Serializes a message object of type '<SetSensor2VehicleOffset-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'offset) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetSensor2VehicleOffset-request>) istream)
  "Deserializes a message object of type '<SetSensor2VehicleOffset-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'offset) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetSensor2VehicleOffset-request>)))
  "Returns string type for a service object of type '<SetSensor2VehicleOffset-request>"
  "microstrain_inertial_msgs/SetSensor2VehicleOffsetRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSensor2VehicleOffset-request)))
  "Returns string type for a service object of type 'SetSensor2VehicleOffset-request"
  "microstrain_inertial_msgs/SetSensor2VehicleOffsetRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetSensor2VehicleOffset-request>)))
  "Returns md5sum for a message object of type '<SetSensor2VehicleOffset-request>"
  "17d27ff1259ce523baf9de57b7c37e18")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetSensor2VehicleOffset-request)))
  "Returns md5sum for a message object of type 'SetSensor2VehicleOffset-request"
  "17d27ff1259ce523baf9de57b7c37e18")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetSensor2VehicleOffset-request>)))
  "Returns full string definition for message of type '<SetSensor2VehicleOffset-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 offset~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetSensor2VehicleOffset-request)))
  "Returns full string definition for message of type 'SetSensor2VehicleOffset-request"
  (cl:format cl:nil "geometry_msgs/Vector3 offset~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetSensor2VehicleOffset-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'offset))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetSensor2VehicleOffset-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetSensor2VehicleOffset-request
    (cl:cons ':offset (offset msg))
))
;//! \htmlinclude SetSensor2VehicleOffset-response.msg.html

(cl:defclass <SetSensor2VehicleOffset-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetSensor2VehicleOffset-response (<SetSensor2VehicleOffset-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetSensor2VehicleOffset-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetSensor2VehicleOffset-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetSensor2VehicleOffset-response> is deprecated: use microstrain_inertial_msgs-srv:SetSensor2VehicleOffset-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetSensor2VehicleOffset-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetSensor2VehicleOffset-response>) ostream)
  "Serializes a message object of type '<SetSensor2VehicleOffset-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetSensor2VehicleOffset-response>) istream)
  "Deserializes a message object of type '<SetSensor2VehicleOffset-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetSensor2VehicleOffset-response>)))
  "Returns string type for a service object of type '<SetSensor2VehicleOffset-response>"
  "microstrain_inertial_msgs/SetSensor2VehicleOffsetResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSensor2VehicleOffset-response)))
  "Returns string type for a service object of type 'SetSensor2VehicleOffset-response"
  "microstrain_inertial_msgs/SetSensor2VehicleOffsetResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetSensor2VehicleOffset-response>)))
  "Returns md5sum for a message object of type '<SetSensor2VehicleOffset-response>"
  "17d27ff1259ce523baf9de57b7c37e18")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetSensor2VehicleOffset-response)))
  "Returns md5sum for a message object of type 'SetSensor2VehicleOffset-response"
  "17d27ff1259ce523baf9de57b7c37e18")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetSensor2VehicleOffset-response>)))
  "Returns full string definition for message of type '<SetSensor2VehicleOffset-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetSensor2VehicleOffset-response)))
  "Returns full string definition for message of type 'SetSensor2VehicleOffset-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetSensor2VehicleOffset-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetSensor2VehicleOffset-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetSensor2VehicleOffset-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetSensor2VehicleOffset)))
  'SetSensor2VehicleOffset-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetSensor2VehicleOffset)))
  'SetSensor2VehicleOffset-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSensor2VehicleOffset)))
  "Returns string type for a service object of type '<SetSensor2VehicleOffset>"
  "microstrain_inertial_msgs/SetSensor2VehicleOffset")