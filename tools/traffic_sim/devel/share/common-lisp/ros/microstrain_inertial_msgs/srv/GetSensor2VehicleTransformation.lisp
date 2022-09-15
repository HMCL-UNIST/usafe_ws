; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetSensor2VehicleTransformation-request.msg.html

(cl:defclass <GetSensor2VehicleTransformation-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetSensor2VehicleTransformation-request (<GetSensor2VehicleTransformation-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetSensor2VehicleTransformation-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetSensor2VehicleTransformation-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetSensor2VehicleTransformation-request> is deprecated: use microstrain_inertial_msgs-srv:GetSensor2VehicleTransformation-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetSensor2VehicleTransformation-request>) ostream)
  "Serializes a message object of type '<GetSensor2VehicleTransformation-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetSensor2VehicleTransformation-request>) istream)
  "Deserializes a message object of type '<GetSensor2VehicleTransformation-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetSensor2VehicleTransformation-request>)))
  "Returns string type for a service object of type '<GetSensor2VehicleTransformation-request>"
  "microstrain_inertial_msgs/GetSensor2VehicleTransformationRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleTransformation-request)))
  "Returns string type for a service object of type 'GetSensor2VehicleTransformation-request"
  "microstrain_inertial_msgs/GetSensor2VehicleTransformationRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetSensor2VehicleTransformation-request>)))
  "Returns md5sum for a message object of type '<GetSensor2VehicleTransformation-request>"
  "004f75cd783f40825cb5e1db7049f127")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetSensor2VehicleTransformation-request)))
  "Returns md5sum for a message object of type 'GetSensor2VehicleTransformation-request"
  "004f75cd783f40825cb5e1db7049f127")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetSensor2VehicleTransformation-request>)))
  "Returns full string definition for message of type '<GetSensor2VehicleTransformation-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetSensor2VehicleTransformation-request)))
  "Returns full string definition for message of type 'GetSensor2VehicleTransformation-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetSensor2VehicleTransformation-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetSensor2VehicleTransformation-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetSensor2VehicleTransformation-request
))
;//! \htmlinclude GetSensor2VehicleTransformation-response.msg.html

(cl:defclass <GetSensor2VehicleTransformation-response> (roslisp-msg-protocol:ros-message)
  ((offset
    :reader offset
    :initarg :offset
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (rotation
    :reader rotation
    :initarg :rotation
    :type geometry_msgs-msg:Quaternion
    :initform (cl:make-instance 'geometry_msgs-msg:Quaternion))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetSensor2VehicleTransformation-response (<GetSensor2VehicleTransformation-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetSensor2VehicleTransformation-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetSensor2VehicleTransformation-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetSensor2VehicleTransformation-response> is deprecated: use microstrain_inertial_msgs-srv:GetSensor2VehicleTransformation-response instead.")))

(cl:ensure-generic-function 'offset-val :lambda-list '(m))
(cl:defmethod offset-val ((m <GetSensor2VehicleTransformation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:offset-val is deprecated.  Use microstrain_inertial_msgs-srv:offset instead.")
  (offset m))

(cl:ensure-generic-function 'rotation-val :lambda-list '(m))
(cl:defmethod rotation-val ((m <GetSensor2VehicleTransformation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:rotation-val is deprecated.  Use microstrain_inertial_msgs-srv:rotation instead.")
  (rotation m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetSensor2VehicleTransformation-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetSensor2VehicleTransformation-response>) ostream)
  "Serializes a message object of type '<GetSensor2VehicleTransformation-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'offset) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'rotation) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetSensor2VehicleTransformation-response>) istream)
  "Deserializes a message object of type '<GetSensor2VehicleTransformation-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'offset) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'rotation) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetSensor2VehicleTransformation-response>)))
  "Returns string type for a service object of type '<GetSensor2VehicleTransformation-response>"
  "microstrain_inertial_msgs/GetSensor2VehicleTransformationResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleTransformation-response)))
  "Returns string type for a service object of type 'GetSensor2VehicleTransformation-response"
  "microstrain_inertial_msgs/GetSensor2VehicleTransformationResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetSensor2VehicleTransformation-response>)))
  "Returns md5sum for a message object of type '<GetSensor2VehicleTransformation-response>"
  "004f75cd783f40825cb5e1db7049f127")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetSensor2VehicleTransformation-response)))
  "Returns md5sum for a message object of type 'GetSensor2VehicleTransformation-response"
  "004f75cd783f40825cb5e1db7049f127")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetSensor2VehicleTransformation-response>)))
  "Returns full string definition for message of type '<GetSensor2VehicleTransformation-response>"
  (cl:format cl:nil "geometry_msgs/Vector3 offset~%geometry_msgs/Quaternion rotation~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetSensor2VehicleTransformation-response)))
  "Returns full string definition for message of type 'GetSensor2VehicleTransformation-response"
  (cl:format cl:nil "geometry_msgs/Vector3 offset~%geometry_msgs/Quaternion rotation~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetSensor2VehicleTransformation-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'offset))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'rotation))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetSensor2VehicleTransformation-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetSensor2VehicleTransformation-response
    (cl:cons ':offset (offset msg))
    (cl:cons ':rotation (rotation msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetSensor2VehicleTransformation)))
  'GetSensor2VehicleTransformation-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetSensor2VehicleTransformation)))
  'GetSensor2VehicleTransformation-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleTransformation)))
  "Returns string type for a service object of type '<GetSensor2VehicleTransformation>"
  "microstrain_inertial_msgs/GetSensor2VehicleTransformation")