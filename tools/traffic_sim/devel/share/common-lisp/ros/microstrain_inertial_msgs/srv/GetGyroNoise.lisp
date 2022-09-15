; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetGyroNoise-request.msg.html

(cl:defclass <GetGyroNoise-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetGyroNoise-request (<GetGyroNoise-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetGyroNoise-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetGyroNoise-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetGyroNoise-request> is deprecated: use microstrain_inertial_msgs-srv:GetGyroNoise-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetGyroNoise-request>) ostream)
  "Serializes a message object of type '<GetGyroNoise-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetGyroNoise-request>) istream)
  "Deserializes a message object of type '<GetGyroNoise-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetGyroNoise-request>)))
  "Returns string type for a service object of type '<GetGyroNoise-request>"
  "microstrain_inertial_msgs/GetGyroNoiseRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetGyroNoise-request)))
  "Returns string type for a service object of type 'GetGyroNoise-request"
  "microstrain_inertial_msgs/GetGyroNoiseRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetGyroNoise-request>)))
  "Returns md5sum for a message object of type '<GetGyroNoise-request>"
  "f98ca1a5e4f9d504cd0b08eeeda072c5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetGyroNoise-request)))
  "Returns md5sum for a message object of type 'GetGyroNoise-request"
  "f98ca1a5e4f9d504cd0b08eeeda072c5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetGyroNoise-request>)))
  "Returns full string definition for message of type '<GetGyroNoise-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetGyroNoise-request)))
  "Returns full string definition for message of type 'GetGyroNoise-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetGyroNoise-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetGyroNoise-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetGyroNoise-request
))
;//! \htmlinclude GetGyroNoise-response.msg.html

(cl:defclass <GetGyroNoise-response> (roslisp-msg-protocol:ros-message)
  ((noise
    :reader noise
    :initarg :noise
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetGyroNoise-response (<GetGyroNoise-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetGyroNoise-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetGyroNoise-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetGyroNoise-response> is deprecated: use microstrain_inertial_msgs-srv:GetGyroNoise-response instead.")))

(cl:ensure-generic-function 'noise-val :lambda-list '(m))
(cl:defmethod noise-val ((m <GetGyroNoise-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:noise-val is deprecated.  Use microstrain_inertial_msgs-srv:noise instead.")
  (noise m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetGyroNoise-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetGyroNoise-response>) ostream)
  "Serializes a message object of type '<GetGyroNoise-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'noise) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetGyroNoise-response>) istream)
  "Deserializes a message object of type '<GetGyroNoise-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'noise) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetGyroNoise-response>)))
  "Returns string type for a service object of type '<GetGyroNoise-response>"
  "microstrain_inertial_msgs/GetGyroNoiseResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetGyroNoise-response)))
  "Returns string type for a service object of type 'GetGyroNoise-response"
  "microstrain_inertial_msgs/GetGyroNoiseResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetGyroNoise-response>)))
  "Returns md5sum for a message object of type '<GetGyroNoise-response>"
  "f98ca1a5e4f9d504cd0b08eeeda072c5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetGyroNoise-response)))
  "Returns md5sum for a message object of type 'GetGyroNoise-response"
  "f98ca1a5e4f9d504cd0b08eeeda072c5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetGyroNoise-response>)))
  "Returns full string definition for message of type '<GetGyroNoise-response>"
  (cl:format cl:nil "geometry_msgs/Vector3 noise~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetGyroNoise-response)))
  "Returns full string definition for message of type 'GetGyroNoise-response"
  (cl:format cl:nil "geometry_msgs/Vector3 noise~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetGyroNoise-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'noise))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetGyroNoise-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetGyroNoise-response
    (cl:cons ':noise (noise msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetGyroNoise)))
  'GetGyroNoise-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetGyroNoise)))
  'GetGyroNoise-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetGyroNoise)))
  "Returns string type for a service object of type '<GetGyroNoise>"
  "microstrain_inertial_msgs/GetGyroNoise")