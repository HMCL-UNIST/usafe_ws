; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetAccelNoise-request.msg.html

(cl:defclass <SetAccelNoise-request> (roslisp-msg-protocol:ros-message)
  ((noise
    :reader noise
    :initarg :noise
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetAccelNoise-request (<SetAccelNoise-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetAccelNoise-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetAccelNoise-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetAccelNoise-request> is deprecated: use microstrain_inertial_msgs-srv:SetAccelNoise-request instead.")))

(cl:ensure-generic-function 'noise-val :lambda-list '(m))
(cl:defmethod noise-val ((m <SetAccelNoise-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:noise-val is deprecated.  Use microstrain_inertial_msgs-srv:noise instead.")
  (noise m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetAccelNoise-request>) ostream)
  "Serializes a message object of type '<SetAccelNoise-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'noise) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetAccelNoise-request>) istream)
  "Deserializes a message object of type '<SetAccelNoise-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'noise) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetAccelNoise-request>)))
  "Returns string type for a service object of type '<SetAccelNoise-request>"
  "microstrain_inertial_msgs/SetAccelNoiseRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetAccelNoise-request)))
  "Returns string type for a service object of type 'SetAccelNoise-request"
  "microstrain_inertial_msgs/SetAccelNoiseRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetAccelNoise-request>)))
  "Returns md5sum for a message object of type '<SetAccelNoise-request>"
  "6a73c0e939ba0cee17d40a2e3a5f667f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetAccelNoise-request)))
  "Returns md5sum for a message object of type 'SetAccelNoise-request"
  "6a73c0e939ba0cee17d40a2e3a5f667f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetAccelNoise-request>)))
  "Returns full string definition for message of type '<SetAccelNoise-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 noise~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetAccelNoise-request)))
  "Returns full string definition for message of type 'SetAccelNoise-request"
  (cl:format cl:nil "geometry_msgs/Vector3 noise~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetAccelNoise-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'noise))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetAccelNoise-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetAccelNoise-request
    (cl:cons ':noise (noise msg))
))
;//! \htmlinclude SetAccelNoise-response.msg.html

(cl:defclass <SetAccelNoise-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetAccelNoise-response (<SetAccelNoise-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetAccelNoise-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetAccelNoise-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetAccelNoise-response> is deprecated: use microstrain_inertial_msgs-srv:SetAccelNoise-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetAccelNoise-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetAccelNoise-response>) ostream)
  "Serializes a message object of type '<SetAccelNoise-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetAccelNoise-response>) istream)
  "Deserializes a message object of type '<SetAccelNoise-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetAccelNoise-response>)))
  "Returns string type for a service object of type '<SetAccelNoise-response>"
  "microstrain_inertial_msgs/SetAccelNoiseResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetAccelNoise-response)))
  "Returns string type for a service object of type 'SetAccelNoise-response"
  "microstrain_inertial_msgs/SetAccelNoiseResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetAccelNoise-response>)))
  "Returns md5sum for a message object of type '<SetAccelNoise-response>"
  "6a73c0e939ba0cee17d40a2e3a5f667f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetAccelNoise-response)))
  "Returns md5sum for a message object of type 'SetAccelNoise-response"
  "6a73c0e939ba0cee17d40a2e3a5f667f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetAccelNoise-response>)))
  "Returns full string definition for message of type '<SetAccelNoise-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetAccelNoise-response)))
  "Returns full string definition for message of type 'SetAccelNoise-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetAccelNoise-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetAccelNoise-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetAccelNoise-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetAccelNoise)))
  'SetAccelNoise-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetAccelNoise)))
  'SetAccelNoise-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetAccelNoise)))
  "Returns string type for a service object of type '<SetAccelNoise>"
  "microstrain_inertial_msgs/SetAccelNoise")