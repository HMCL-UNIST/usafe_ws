; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetGyroBiasModel-request.msg.html

(cl:defclass <SetGyroBiasModel-request> (roslisp-msg-protocol:ros-message)
  ((noise_vector
    :reader noise_vector
    :initarg :noise_vector
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (beta_vector
    :reader beta_vector
    :initarg :beta_vector
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetGyroBiasModel-request (<SetGyroBiasModel-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetGyroBiasModel-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetGyroBiasModel-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetGyroBiasModel-request> is deprecated: use microstrain_inertial_msgs-srv:SetGyroBiasModel-request instead.")))

(cl:ensure-generic-function 'noise_vector-val :lambda-list '(m))
(cl:defmethod noise_vector-val ((m <SetGyroBiasModel-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:noise_vector-val is deprecated.  Use microstrain_inertial_msgs-srv:noise_vector instead.")
  (noise_vector m))

(cl:ensure-generic-function 'beta_vector-val :lambda-list '(m))
(cl:defmethod beta_vector-val ((m <SetGyroBiasModel-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:beta_vector-val is deprecated.  Use microstrain_inertial_msgs-srv:beta_vector instead.")
  (beta_vector m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetGyroBiasModel-request>) ostream)
  "Serializes a message object of type '<SetGyroBiasModel-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'noise_vector) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'beta_vector) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetGyroBiasModel-request>) istream)
  "Deserializes a message object of type '<SetGyroBiasModel-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'noise_vector) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'beta_vector) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetGyroBiasModel-request>)))
  "Returns string type for a service object of type '<SetGyroBiasModel-request>"
  "microstrain_inertial_msgs/SetGyroBiasModelRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGyroBiasModel-request)))
  "Returns string type for a service object of type 'SetGyroBiasModel-request"
  "microstrain_inertial_msgs/SetGyroBiasModelRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetGyroBiasModel-request>)))
  "Returns md5sum for a message object of type '<SetGyroBiasModel-request>"
  "f3cdd18c97add875be98974ab1d992b9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetGyroBiasModel-request)))
  "Returns md5sum for a message object of type 'SetGyroBiasModel-request"
  "f3cdd18c97add875be98974ab1d992b9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetGyroBiasModel-request>)))
  "Returns full string definition for message of type '<SetGyroBiasModel-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 noise_vector~%geometry_msgs/Vector3 beta_vector~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetGyroBiasModel-request)))
  "Returns full string definition for message of type 'SetGyroBiasModel-request"
  (cl:format cl:nil "geometry_msgs/Vector3 noise_vector~%geometry_msgs/Vector3 beta_vector~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetGyroBiasModel-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'noise_vector))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'beta_vector))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetGyroBiasModel-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetGyroBiasModel-request
    (cl:cons ':noise_vector (noise_vector msg))
    (cl:cons ':beta_vector (beta_vector msg))
))
;//! \htmlinclude SetGyroBiasModel-response.msg.html

(cl:defclass <SetGyroBiasModel-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetGyroBiasModel-response (<SetGyroBiasModel-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetGyroBiasModel-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetGyroBiasModel-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetGyroBiasModel-response> is deprecated: use microstrain_inertial_msgs-srv:SetGyroBiasModel-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetGyroBiasModel-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetGyroBiasModel-response>) ostream)
  "Serializes a message object of type '<SetGyroBiasModel-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetGyroBiasModel-response>) istream)
  "Deserializes a message object of type '<SetGyroBiasModel-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetGyroBiasModel-response>)))
  "Returns string type for a service object of type '<SetGyroBiasModel-response>"
  "microstrain_inertial_msgs/SetGyroBiasModelResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGyroBiasModel-response)))
  "Returns string type for a service object of type 'SetGyroBiasModel-response"
  "microstrain_inertial_msgs/SetGyroBiasModelResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetGyroBiasModel-response>)))
  "Returns md5sum for a message object of type '<SetGyroBiasModel-response>"
  "f3cdd18c97add875be98974ab1d992b9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetGyroBiasModel-response)))
  "Returns md5sum for a message object of type 'SetGyroBiasModel-response"
  "f3cdd18c97add875be98974ab1d992b9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetGyroBiasModel-response>)))
  "Returns full string definition for message of type '<SetGyroBiasModel-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetGyroBiasModel-response)))
  "Returns full string definition for message of type 'SetGyroBiasModel-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetGyroBiasModel-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetGyroBiasModel-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetGyroBiasModel-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetGyroBiasModel)))
  'SetGyroBiasModel-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetGyroBiasModel)))
  'SetGyroBiasModel-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGyroBiasModel)))
  "Returns string type for a service object of type '<SetGyroBiasModel>"
  "microstrain_inertial_msgs/SetGyroBiasModel")