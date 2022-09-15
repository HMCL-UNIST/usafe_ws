; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetSoftIronMatrix-request.msg.html

(cl:defclass <SetSoftIronMatrix-request> (roslisp-msg-protocol:ros-message)
  ((soft_iron_1
    :reader soft_iron_1
    :initarg :soft_iron_1
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (soft_iron_2
    :reader soft_iron_2
    :initarg :soft_iron_2
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (soft_iron_3
    :reader soft_iron_3
    :initarg :soft_iron_3
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetSoftIronMatrix-request (<SetSoftIronMatrix-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetSoftIronMatrix-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetSoftIronMatrix-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetSoftIronMatrix-request> is deprecated: use microstrain_inertial_msgs-srv:SetSoftIronMatrix-request instead.")))

(cl:ensure-generic-function 'soft_iron_1-val :lambda-list '(m))
(cl:defmethod soft_iron_1-val ((m <SetSoftIronMatrix-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:soft_iron_1-val is deprecated.  Use microstrain_inertial_msgs-srv:soft_iron_1 instead.")
  (soft_iron_1 m))

(cl:ensure-generic-function 'soft_iron_2-val :lambda-list '(m))
(cl:defmethod soft_iron_2-val ((m <SetSoftIronMatrix-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:soft_iron_2-val is deprecated.  Use microstrain_inertial_msgs-srv:soft_iron_2 instead.")
  (soft_iron_2 m))

(cl:ensure-generic-function 'soft_iron_3-val :lambda-list '(m))
(cl:defmethod soft_iron_3-val ((m <SetSoftIronMatrix-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:soft_iron_3-val is deprecated.  Use microstrain_inertial_msgs-srv:soft_iron_3 instead.")
  (soft_iron_3 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetSoftIronMatrix-request>) ostream)
  "Serializes a message object of type '<SetSoftIronMatrix-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'soft_iron_1) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'soft_iron_2) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'soft_iron_3) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetSoftIronMatrix-request>) istream)
  "Deserializes a message object of type '<SetSoftIronMatrix-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'soft_iron_1) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'soft_iron_2) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'soft_iron_3) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetSoftIronMatrix-request>)))
  "Returns string type for a service object of type '<SetSoftIronMatrix-request>"
  "microstrain_inertial_msgs/SetSoftIronMatrixRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSoftIronMatrix-request)))
  "Returns string type for a service object of type 'SetSoftIronMatrix-request"
  "microstrain_inertial_msgs/SetSoftIronMatrixRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetSoftIronMatrix-request>)))
  "Returns md5sum for a message object of type '<SetSoftIronMatrix-request>"
  "ec07578ea93b9bb8b21d87ab5d1f0c81")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetSoftIronMatrix-request)))
  "Returns md5sum for a message object of type 'SetSoftIronMatrix-request"
  "ec07578ea93b9bb8b21d87ab5d1f0c81")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetSoftIronMatrix-request>)))
  "Returns full string definition for message of type '<SetSoftIronMatrix-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 soft_iron_1~%geometry_msgs/Vector3 soft_iron_2~%geometry_msgs/Vector3 soft_iron_3~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetSoftIronMatrix-request)))
  "Returns full string definition for message of type 'SetSoftIronMatrix-request"
  (cl:format cl:nil "geometry_msgs/Vector3 soft_iron_1~%geometry_msgs/Vector3 soft_iron_2~%geometry_msgs/Vector3 soft_iron_3~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetSoftIronMatrix-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'soft_iron_1))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'soft_iron_2))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'soft_iron_3))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetSoftIronMatrix-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetSoftIronMatrix-request
    (cl:cons ':soft_iron_1 (soft_iron_1 msg))
    (cl:cons ':soft_iron_2 (soft_iron_2 msg))
    (cl:cons ':soft_iron_3 (soft_iron_3 msg))
))
;//! \htmlinclude SetSoftIronMatrix-response.msg.html

(cl:defclass <SetSoftIronMatrix-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetSoftIronMatrix-response (<SetSoftIronMatrix-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetSoftIronMatrix-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetSoftIronMatrix-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetSoftIronMatrix-response> is deprecated: use microstrain_inertial_msgs-srv:SetSoftIronMatrix-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetSoftIronMatrix-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetSoftIronMatrix-response>) ostream)
  "Serializes a message object of type '<SetSoftIronMatrix-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetSoftIronMatrix-response>) istream)
  "Deserializes a message object of type '<SetSoftIronMatrix-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetSoftIronMatrix-response>)))
  "Returns string type for a service object of type '<SetSoftIronMatrix-response>"
  "microstrain_inertial_msgs/SetSoftIronMatrixResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSoftIronMatrix-response)))
  "Returns string type for a service object of type 'SetSoftIronMatrix-response"
  "microstrain_inertial_msgs/SetSoftIronMatrixResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetSoftIronMatrix-response>)))
  "Returns md5sum for a message object of type '<SetSoftIronMatrix-response>"
  "ec07578ea93b9bb8b21d87ab5d1f0c81")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetSoftIronMatrix-response)))
  "Returns md5sum for a message object of type 'SetSoftIronMatrix-response"
  "ec07578ea93b9bb8b21d87ab5d1f0c81")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetSoftIronMatrix-response>)))
  "Returns full string definition for message of type '<SetSoftIronMatrix-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetSoftIronMatrix-response)))
  "Returns full string definition for message of type 'SetSoftIronMatrix-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetSoftIronMatrix-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetSoftIronMatrix-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetSoftIronMatrix-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetSoftIronMatrix)))
  'SetSoftIronMatrix-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetSoftIronMatrix)))
  'SetSoftIronMatrix-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetSoftIronMatrix)))
  "Returns string type for a service object of type '<SetSoftIronMatrix>"
  "microstrain_inertial_msgs/SetSoftIronMatrix")