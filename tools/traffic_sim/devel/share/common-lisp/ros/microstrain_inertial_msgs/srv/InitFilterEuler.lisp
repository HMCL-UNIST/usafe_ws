; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude InitFilterEuler-request.msg.html

(cl:defclass <InitFilterEuler-request> (roslisp-msg-protocol:ros-message)
  ((angle
    :reader angle
    :initarg :angle
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass InitFilterEuler-request (<InitFilterEuler-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InitFilterEuler-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InitFilterEuler-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<InitFilterEuler-request> is deprecated: use microstrain_inertial_msgs-srv:InitFilterEuler-request instead.")))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <InitFilterEuler-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:angle-val is deprecated.  Use microstrain_inertial_msgs-srv:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InitFilterEuler-request>) ostream)
  "Serializes a message object of type '<InitFilterEuler-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'angle) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InitFilterEuler-request>) istream)
  "Deserializes a message object of type '<InitFilterEuler-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'angle) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InitFilterEuler-request>)))
  "Returns string type for a service object of type '<InitFilterEuler-request>"
  "microstrain_inertial_msgs/InitFilterEulerRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitFilterEuler-request)))
  "Returns string type for a service object of type 'InitFilterEuler-request"
  "microstrain_inertial_msgs/InitFilterEulerRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InitFilterEuler-request>)))
  "Returns md5sum for a message object of type '<InitFilterEuler-request>"
  "dae0af6e9e855f125599090c94e6955e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InitFilterEuler-request)))
  "Returns md5sum for a message object of type 'InitFilterEuler-request"
  "dae0af6e9e855f125599090c94e6955e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InitFilterEuler-request>)))
  "Returns full string definition for message of type '<InitFilterEuler-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 angle~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InitFilterEuler-request)))
  "Returns full string definition for message of type 'InitFilterEuler-request"
  (cl:format cl:nil "geometry_msgs/Vector3 angle~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InitFilterEuler-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'angle))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InitFilterEuler-request>))
  "Converts a ROS message object to a list"
  (cl:list 'InitFilterEuler-request
    (cl:cons ':angle (angle msg))
))
;//! \htmlinclude InitFilterEuler-response.msg.html

(cl:defclass <InitFilterEuler-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass InitFilterEuler-response (<InitFilterEuler-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InitFilterEuler-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InitFilterEuler-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<InitFilterEuler-response> is deprecated: use microstrain_inertial_msgs-srv:InitFilterEuler-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <InitFilterEuler-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InitFilterEuler-response>) ostream)
  "Serializes a message object of type '<InitFilterEuler-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InitFilterEuler-response>) istream)
  "Deserializes a message object of type '<InitFilterEuler-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InitFilterEuler-response>)))
  "Returns string type for a service object of type '<InitFilterEuler-response>"
  "microstrain_inertial_msgs/InitFilterEulerResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitFilterEuler-response)))
  "Returns string type for a service object of type 'InitFilterEuler-response"
  "microstrain_inertial_msgs/InitFilterEulerResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InitFilterEuler-response>)))
  "Returns md5sum for a message object of type '<InitFilterEuler-response>"
  "dae0af6e9e855f125599090c94e6955e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InitFilterEuler-response)))
  "Returns md5sum for a message object of type 'InitFilterEuler-response"
  "dae0af6e9e855f125599090c94e6955e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InitFilterEuler-response>)))
  "Returns full string definition for message of type '<InitFilterEuler-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InitFilterEuler-response)))
  "Returns full string definition for message of type 'InitFilterEuler-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InitFilterEuler-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InitFilterEuler-response>))
  "Converts a ROS message object to a list"
  (cl:list 'InitFilterEuler-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'InitFilterEuler)))
  'InitFilterEuler-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'InitFilterEuler)))
  'InitFilterEuler-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitFilterEuler)))
  "Returns string type for a service object of type '<InitFilterEuler>"
  "microstrain_inertial_msgs/InitFilterEuler")