; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetSensor2VehicleOffset-request.msg.html

(cl:defclass <GetSensor2VehicleOffset-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetSensor2VehicleOffset-request (<GetSensor2VehicleOffset-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetSensor2VehicleOffset-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetSensor2VehicleOffset-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetSensor2VehicleOffset-request> is deprecated: use microstrain_inertial_msgs-srv:GetSensor2VehicleOffset-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetSensor2VehicleOffset-request>) ostream)
  "Serializes a message object of type '<GetSensor2VehicleOffset-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetSensor2VehicleOffset-request>) istream)
  "Deserializes a message object of type '<GetSensor2VehicleOffset-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetSensor2VehicleOffset-request>)))
  "Returns string type for a service object of type '<GetSensor2VehicleOffset-request>"
  "microstrain_inertial_msgs/GetSensor2VehicleOffsetRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleOffset-request)))
  "Returns string type for a service object of type 'GetSensor2VehicleOffset-request"
  "microstrain_inertial_msgs/GetSensor2VehicleOffsetRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetSensor2VehicleOffset-request>)))
  "Returns md5sum for a message object of type '<GetSensor2VehicleOffset-request>"
  "336379c9adc329d4ecaa355471c3cacd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetSensor2VehicleOffset-request)))
  "Returns md5sum for a message object of type 'GetSensor2VehicleOffset-request"
  "336379c9adc329d4ecaa355471c3cacd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetSensor2VehicleOffset-request>)))
  "Returns full string definition for message of type '<GetSensor2VehicleOffset-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetSensor2VehicleOffset-request)))
  "Returns full string definition for message of type 'GetSensor2VehicleOffset-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetSensor2VehicleOffset-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetSensor2VehicleOffset-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetSensor2VehicleOffset-request
))
;//! \htmlinclude GetSensor2VehicleOffset-response.msg.html

(cl:defclass <GetSensor2VehicleOffset-response> (roslisp-msg-protocol:ros-message)
  ((offset
    :reader offset
    :initarg :offset
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetSensor2VehicleOffset-response (<GetSensor2VehicleOffset-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetSensor2VehicleOffset-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetSensor2VehicleOffset-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetSensor2VehicleOffset-response> is deprecated: use microstrain_inertial_msgs-srv:GetSensor2VehicleOffset-response instead.")))

(cl:ensure-generic-function 'offset-val :lambda-list '(m))
(cl:defmethod offset-val ((m <GetSensor2VehicleOffset-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:offset-val is deprecated.  Use microstrain_inertial_msgs-srv:offset instead.")
  (offset m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetSensor2VehicleOffset-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetSensor2VehicleOffset-response>) ostream)
  "Serializes a message object of type '<GetSensor2VehicleOffset-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'offset) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetSensor2VehicleOffset-response>) istream)
  "Deserializes a message object of type '<GetSensor2VehicleOffset-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'offset) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetSensor2VehicleOffset-response>)))
  "Returns string type for a service object of type '<GetSensor2VehicleOffset-response>"
  "microstrain_inertial_msgs/GetSensor2VehicleOffsetResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleOffset-response)))
  "Returns string type for a service object of type 'GetSensor2VehicleOffset-response"
  "microstrain_inertial_msgs/GetSensor2VehicleOffsetResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetSensor2VehicleOffset-response>)))
  "Returns md5sum for a message object of type '<GetSensor2VehicleOffset-response>"
  "336379c9adc329d4ecaa355471c3cacd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetSensor2VehicleOffset-response)))
  "Returns md5sum for a message object of type 'GetSensor2VehicleOffset-response"
  "336379c9adc329d4ecaa355471c3cacd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetSensor2VehicleOffset-response>)))
  "Returns full string definition for message of type '<GetSensor2VehicleOffset-response>"
  (cl:format cl:nil "geometry_msgs/Vector3 offset~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetSensor2VehicleOffset-response)))
  "Returns full string definition for message of type 'GetSensor2VehicleOffset-response"
  (cl:format cl:nil "geometry_msgs/Vector3 offset~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetSensor2VehicleOffset-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'offset))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetSensor2VehicleOffset-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetSensor2VehicleOffset-response
    (cl:cons ':offset (offset msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetSensor2VehicleOffset)))
  'GetSensor2VehicleOffset-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetSensor2VehicleOffset)))
  'GetSensor2VehicleOffset-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetSensor2VehicleOffset)))
  "Returns string type for a service object of type '<GetSensor2VehicleOffset>"
  "microstrain_inertial_msgs/GetSensor2VehicleOffset")