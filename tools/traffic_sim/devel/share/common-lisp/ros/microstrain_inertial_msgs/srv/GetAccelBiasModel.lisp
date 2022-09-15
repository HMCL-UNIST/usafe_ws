; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetAccelBiasModel-request.msg.html

(cl:defclass <GetAccelBiasModel-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetAccelBiasModel-request (<GetAccelBiasModel-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetAccelBiasModel-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetAccelBiasModel-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetAccelBiasModel-request> is deprecated: use microstrain_inertial_msgs-srv:GetAccelBiasModel-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetAccelBiasModel-request>) ostream)
  "Serializes a message object of type '<GetAccelBiasModel-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetAccelBiasModel-request>) istream)
  "Deserializes a message object of type '<GetAccelBiasModel-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetAccelBiasModel-request>)))
  "Returns string type for a service object of type '<GetAccelBiasModel-request>"
  "microstrain_inertial_msgs/GetAccelBiasModelRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetAccelBiasModel-request)))
  "Returns string type for a service object of type 'GetAccelBiasModel-request"
  "microstrain_inertial_msgs/GetAccelBiasModelRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetAccelBiasModel-request>)))
  "Returns md5sum for a message object of type '<GetAccelBiasModel-request>"
  "b507c17fd666c16c0721d62595a47085")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetAccelBiasModel-request)))
  "Returns md5sum for a message object of type 'GetAccelBiasModel-request"
  "b507c17fd666c16c0721d62595a47085")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetAccelBiasModel-request>)))
  "Returns full string definition for message of type '<GetAccelBiasModel-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetAccelBiasModel-request)))
  "Returns full string definition for message of type 'GetAccelBiasModel-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetAccelBiasModel-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetAccelBiasModel-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetAccelBiasModel-request
))
;//! \htmlinclude GetAccelBiasModel-response.msg.html

(cl:defclass <GetAccelBiasModel-response> (roslisp-msg-protocol:ros-message)
  ((noise_vector
    :reader noise_vector
    :initarg :noise_vector
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (beta_vector
    :reader beta_vector
    :initarg :beta_vector
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetAccelBiasModel-response (<GetAccelBiasModel-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetAccelBiasModel-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetAccelBiasModel-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetAccelBiasModel-response> is deprecated: use microstrain_inertial_msgs-srv:GetAccelBiasModel-response instead.")))

(cl:ensure-generic-function 'noise_vector-val :lambda-list '(m))
(cl:defmethod noise_vector-val ((m <GetAccelBiasModel-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:noise_vector-val is deprecated.  Use microstrain_inertial_msgs-srv:noise_vector instead.")
  (noise_vector m))

(cl:ensure-generic-function 'beta_vector-val :lambda-list '(m))
(cl:defmethod beta_vector-val ((m <GetAccelBiasModel-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:beta_vector-val is deprecated.  Use microstrain_inertial_msgs-srv:beta_vector instead.")
  (beta_vector m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetAccelBiasModel-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetAccelBiasModel-response>) ostream)
  "Serializes a message object of type '<GetAccelBiasModel-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'noise_vector) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'beta_vector) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetAccelBiasModel-response>) istream)
  "Deserializes a message object of type '<GetAccelBiasModel-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'noise_vector) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'beta_vector) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetAccelBiasModel-response>)))
  "Returns string type for a service object of type '<GetAccelBiasModel-response>"
  "microstrain_inertial_msgs/GetAccelBiasModelResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetAccelBiasModel-response)))
  "Returns string type for a service object of type 'GetAccelBiasModel-response"
  "microstrain_inertial_msgs/GetAccelBiasModelResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetAccelBiasModel-response>)))
  "Returns md5sum for a message object of type '<GetAccelBiasModel-response>"
  "b507c17fd666c16c0721d62595a47085")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetAccelBiasModel-response)))
  "Returns md5sum for a message object of type 'GetAccelBiasModel-response"
  "b507c17fd666c16c0721d62595a47085")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetAccelBiasModel-response>)))
  "Returns full string definition for message of type '<GetAccelBiasModel-response>"
  (cl:format cl:nil "geometry_msgs/Vector3 noise_vector~%geometry_msgs/Vector3 beta_vector~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetAccelBiasModel-response)))
  "Returns full string definition for message of type 'GetAccelBiasModel-response"
  (cl:format cl:nil "geometry_msgs/Vector3 noise_vector~%geometry_msgs/Vector3 beta_vector~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetAccelBiasModel-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'noise_vector))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'beta_vector))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetAccelBiasModel-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetAccelBiasModel-response
    (cl:cons ':noise_vector (noise_vector msg))
    (cl:cons ':beta_vector (beta_vector msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetAccelBiasModel)))
  'GetAccelBiasModel-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetAccelBiasModel)))
  'GetAccelBiasModel-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetAccelBiasModel)))
  "Returns string type for a service object of type '<GetAccelBiasModel>"
  "microstrain_inertial_msgs/GetAccelBiasModel")