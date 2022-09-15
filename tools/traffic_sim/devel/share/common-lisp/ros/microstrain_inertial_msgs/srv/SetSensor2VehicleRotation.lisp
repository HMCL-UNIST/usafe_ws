; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetSensor2VehicleRotation-request.msg.html

(cl:defclass <SetSensor2VehicleRotation-request> (roslisp-msg-protocol:ros-message)
  ((angle
    :reader angle
    :initarg :angle
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetSensor2VehicleRotation-request (<SetSensor2VehicleRotation-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetSensor2VehicleRotation-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetSensor2VehicleRotation-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetSensor2VehicleRotation-request> is deprecated: use microstrain_inertial_msgs-srv:SetSensor2VehicleRotation-request instead.")))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <SetSensor2VehicleRotation-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:angle-val is deprecated.  Use microstrain_inertial_msgs-srv:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetSensor2VehicleRotation-request>) ostream)
  "Serializes a message object of type '<SetSensor2VehicleRotation-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'angle) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetSensor2VehicleRotation-request>) istream)
  "Deserializes a message object of type '<SetSensor2VehicleRotation-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'angle) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetSensor2VehicleRotation-request>)))
  "Returns string type for a service object of type '<SetSensor2VehicleRotation-request>"
  "microstrain_inertial_msgs/SetSensor2VehicleRotationRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSensor2VehicleRotation-request)))
  "Returns string type for a service object of type 'SetSensor2VehicleRotation-request"
  "microstrain_inertial_msgs/SetSensor2VehicleRotationRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetSensor2VehicleRotation-request>)))
  "Returns md5sum for a message object of type '<SetSensor2VehicleRotation-request>"
  "dae0af6e9e855f125599090c94e6955e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetSensor2VehicleRotation-request)))
  "Returns md5sum for a message object of type 'SetSensor2VehicleRotation-request"
  "dae0af6e9e855f125599090c94e6955e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetSensor2VehicleRotation-request>)))
  "Returns full string definition for message of type '<SetSensor2VehicleRotation-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 angle~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetSensor2VehicleRotation-request)))
  "Returns full string definition for message of type 'SetSensor2VehicleRotation-request"
  (cl:format cl:nil "geometry_msgs/Vector3 angle~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetSensor2VehicleRotation-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'angle))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetSensor2VehicleRotation-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetSensor2VehicleRotation-request
    (cl:cons ':angle (angle msg))
))
;//! \htmlinclude SetSensor2VehicleRotation-response.msg.html

(cl:defclass <SetSensor2VehicleRotation-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetSensor2VehicleRotation-response (<SetSensor2VehicleRotation-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetSensor2VehicleRotation-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetSensor2VehicleRotation-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetSensor2VehicleRotation-response> is deprecated: use microstrain_inertial_msgs-srv:SetSensor2VehicleRotation-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetSensor2VehicleRotation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetSensor2VehicleRotation-response>) ostream)
  "Serializes a message object of type '<SetSensor2VehicleRotation-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetSensor2VehicleRotation-response>) istream)
  "Deserializes a message object of type '<SetSensor2VehicleRotation-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetSensor2VehicleRotation-response>)))
  "Returns string type for a service object of type '<SetSensor2VehicleRotation-response>"
  "microstrain_inertial_msgs/SetSensor2VehicleRotationResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSensor2VehicleRotation-response)))
  "Returns string type for a service object of type 'SetSensor2VehicleRotation-response"
  "microstrain_inertial_msgs/SetSensor2VehicleRotationResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetSensor2VehicleRotation-response>)))
  "Returns md5sum for a message object of type '<SetSensor2VehicleRotation-response>"
  "dae0af6e9e855f125599090c94e6955e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetSensor2VehicleRotation-response)))
  "Returns md5sum for a message object of type 'SetSensor2VehicleRotation-response"
  "dae0af6e9e855f125599090c94e6955e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetSensor2VehicleRotation-response>)))
  "Returns full string definition for message of type '<SetSensor2VehicleRotation-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetSensor2VehicleRotation-response)))
  "Returns full string definition for message of type 'SetSensor2VehicleRotation-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetSensor2VehicleRotation-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetSensor2VehicleRotation-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetSensor2VehicleRotation-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetSensor2VehicleRotation)))
  'SetSensor2VehicleRotation-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetSensor2VehicleRotation)))
  'SetSensor2VehicleRotation-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSensor2VehicleRotation)))
  "Returns string type for a service object of type '<SetSensor2VehicleRotation>"
  "microstrain_inertial_msgs/SetSensor2VehicleRotation")