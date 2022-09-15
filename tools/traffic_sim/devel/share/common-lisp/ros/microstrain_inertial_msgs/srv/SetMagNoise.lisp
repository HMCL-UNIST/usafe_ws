; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetMagNoise-request.msg.html

(cl:defclass <SetMagNoise-request> (roslisp-msg-protocol:ros-message)
  ((noise
    :reader noise
    :initarg :noise
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetMagNoise-request (<SetMagNoise-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetMagNoise-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetMagNoise-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetMagNoise-request> is deprecated: use microstrain_inertial_msgs-srv:SetMagNoise-request instead.")))

(cl:ensure-generic-function 'noise-val :lambda-list '(m))
(cl:defmethod noise-val ((m <SetMagNoise-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:noise-val is deprecated.  Use microstrain_inertial_msgs-srv:noise instead.")
  (noise m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetMagNoise-request>) ostream)
  "Serializes a message object of type '<SetMagNoise-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'noise) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetMagNoise-request>) istream)
  "Deserializes a message object of type '<SetMagNoise-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'noise) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetMagNoise-request>)))
  "Returns string type for a service object of type '<SetMagNoise-request>"
  "microstrain_inertial_msgs/SetMagNoiseRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetMagNoise-request)))
  "Returns string type for a service object of type 'SetMagNoise-request"
  "microstrain_inertial_msgs/SetMagNoiseRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetMagNoise-request>)))
  "Returns md5sum for a message object of type '<SetMagNoise-request>"
  "6a73c0e939ba0cee17d40a2e3a5f667f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetMagNoise-request)))
  "Returns md5sum for a message object of type 'SetMagNoise-request"
  "6a73c0e939ba0cee17d40a2e3a5f667f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetMagNoise-request>)))
  "Returns full string definition for message of type '<SetMagNoise-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 noise~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetMagNoise-request)))
  "Returns full string definition for message of type 'SetMagNoise-request"
  (cl:format cl:nil "geometry_msgs/Vector3 noise~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetMagNoise-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'noise))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetMagNoise-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetMagNoise-request
    (cl:cons ':noise (noise msg))
))
;//! \htmlinclude SetMagNoise-response.msg.html

(cl:defclass <SetMagNoise-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetMagNoise-response (<SetMagNoise-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetMagNoise-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetMagNoise-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetMagNoise-response> is deprecated: use microstrain_inertial_msgs-srv:SetMagNoise-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetMagNoise-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetMagNoise-response>) ostream)
  "Serializes a message object of type '<SetMagNoise-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetMagNoise-response>) istream)
  "Deserializes a message object of type '<SetMagNoise-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetMagNoise-response>)))
  "Returns string type for a service object of type '<SetMagNoise-response>"
  "microstrain_inertial_msgs/SetMagNoiseResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetMagNoise-response)))
  "Returns string type for a service object of type 'SetMagNoise-response"
  "microstrain_inertial_msgs/SetMagNoiseResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetMagNoise-response>)))
  "Returns md5sum for a message object of type '<SetMagNoise-response>"
  "6a73c0e939ba0cee17d40a2e3a5f667f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetMagNoise-response)))
  "Returns md5sum for a message object of type 'SetMagNoise-response"
  "6a73c0e939ba0cee17d40a2e3a5f667f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetMagNoise-response>)))
  "Returns full string definition for message of type '<SetMagNoise-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetMagNoise-response)))
  "Returns full string definition for message of type 'SetMagNoise-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetMagNoise-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetMagNoise-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetMagNoise-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetMagNoise)))
  'SetMagNoise-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetMagNoise)))
  'SetMagNoise-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetMagNoise)))
  "Returns string type for a service object of type '<SetMagNoise>"
  "microstrain_inertial_msgs/SetMagNoise")