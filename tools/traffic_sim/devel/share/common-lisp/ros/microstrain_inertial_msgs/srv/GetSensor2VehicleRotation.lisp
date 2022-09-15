; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetSensor2VehicleRotation-request.msg.html

(cl:defclass <GetSensor2VehicleRotation-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetSensor2VehicleRotation-request (<GetSensor2VehicleRotation-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetSensor2VehicleRotation-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetSensor2VehicleRotation-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetSensor2VehicleRotation-request> is deprecated: use microstrain_inertial_msgs-srv:GetSensor2VehicleRotation-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetSensor2VehicleRotation-request>) ostream)
  "Serializes a message object of type '<GetSensor2VehicleRotation-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetSensor2VehicleRotation-request>) istream)
  "Deserializes a message object of type '<GetSensor2VehicleRotation-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetSensor2VehicleRotation-request>)))
  "Returns string type for a service object of type '<GetSensor2VehicleRotation-request>"
  "microstrain_inertial_msgs/GetSensor2VehicleRotationRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleRotation-request)))
  "Returns string type for a service object of type 'GetSensor2VehicleRotation-request"
  "microstrain_inertial_msgs/GetSensor2VehicleRotationRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetSensor2VehicleRotation-request>)))
  "Returns md5sum for a message object of type '<GetSensor2VehicleRotation-request>"
  "f17f1953dd3d01dff314cf417fc7232c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetSensor2VehicleRotation-request)))
  "Returns md5sum for a message object of type 'GetSensor2VehicleRotation-request"
  "f17f1953dd3d01dff314cf417fc7232c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetSensor2VehicleRotation-request>)))
  "Returns full string definition for message of type '<GetSensor2VehicleRotation-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetSensor2VehicleRotation-request)))
  "Returns full string definition for message of type 'GetSensor2VehicleRotation-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetSensor2VehicleRotation-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetSensor2VehicleRotation-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetSensor2VehicleRotation-request
))
;//! \htmlinclude GetSensor2VehicleRotation-response.msg.html

(cl:defclass <GetSensor2VehicleRotation-response> (roslisp-msg-protocol:ros-message)
  ((angle
    :reader angle
    :initarg :angle
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetSensor2VehicleRotation-response (<GetSensor2VehicleRotation-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetSensor2VehicleRotation-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetSensor2VehicleRotation-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetSensor2VehicleRotation-response> is deprecated: use microstrain_inertial_msgs-srv:GetSensor2VehicleRotation-response instead.")))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <GetSensor2VehicleRotation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:angle-val is deprecated.  Use microstrain_inertial_msgs-srv:angle instead.")
  (angle m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetSensor2VehicleRotation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetSensor2VehicleRotation-response>) ostream)
  "Serializes a message object of type '<GetSensor2VehicleRotation-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'angle) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetSensor2VehicleRotation-response>) istream)
  "Deserializes a message object of type '<GetSensor2VehicleRotation-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'angle) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetSensor2VehicleRotation-response>)))
  "Returns string type for a service object of type '<GetSensor2VehicleRotation-response>"
  "microstrain_inertial_msgs/GetSensor2VehicleRotationResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleRotation-response)))
  "Returns string type for a service object of type 'GetSensor2VehicleRotation-response"
  "microstrain_inertial_msgs/GetSensor2VehicleRotationResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetSensor2VehicleRotation-response>)))
  "Returns md5sum for a message object of type '<GetSensor2VehicleRotation-response>"
  "f17f1953dd3d01dff314cf417fc7232c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetSensor2VehicleRotation-response)))
  "Returns md5sum for a message object of type 'GetSensor2VehicleRotation-response"
  "f17f1953dd3d01dff314cf417fc7232c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetSensor2VehicleRotation-response>)))
  "Returns full string definition for message of type '<GetSensor2VehicleRotation-response>"
  (cl:format cl:nil "geometry_msgs/Vector3 angle~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetSensor2VehicleRotation-response)))
  "Returns full string definition for message of type 'GetSensor2VehicleRotation-response"
  (cl:format cl:nil "geometry_msgs/Vector3 angle~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetSensor2VehicleRotation-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'angle))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetSensor2VehicleRotation-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetSensor2VehicleRotation-response
    (cl:cons ':angle (angle msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetSensor2VehicleRotation)))
  'GetSensor2VehicleRotation-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetSensor2VehicleRotation)))
  'GetSensor2VehicleRotation-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleRotation)))
  "Returns string type for a service object of type '<GetSensor2VehicleRotation>"
  "microstrain_inertial_msgs/GetSensor2VehicleRotation")