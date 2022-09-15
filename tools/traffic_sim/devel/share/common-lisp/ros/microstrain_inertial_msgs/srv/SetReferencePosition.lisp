; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude SetReferencePosition-request.msg.html

(cl:defclass <SetReferencePosition-request> (roslisp-msg-protocol:ros-message)
  ((position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass SetReferencePosition-request (<SetReferencePosition-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetReferencePosition-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetReferencePosition-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetReferencePosition-request> is deprecated: use microstrain_inertial_msgs-srv:SetReferencePosition-request instead.")))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <SetReferencePosition-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:position-val is deprecated.  Use microstrain_inertial_msgs-srv:position instead.")
  (position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetReferencePosition-request>) ostream)
  "Serializes a message object of type '<SetReferencePosition-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetReferencePosition-request>) istream)
  "Deserializes a message object of type '<SetReferencePosition-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetReferencePosition-request>)))
  "Returns string type for a service object of type '<SetReferencePosition-request>"
  "microstrain_inertial_msgs/SetReferencePositionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetReferencePosition-request)))
  "Returns string type for a service object of type 'SetReferencePosition-request"
  "microstrain_inertial_msgs/SetReferencePositionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetReferencePosition-request>)))
  "Returns md5sum for a message object of type '<SetReferencePosition-request>"
  "eed8c009a979878261617f53e8264ddc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetReferencePosition-request)))
  "Returns md5sum for a message object of type 'SetReferencePosition-request"
  "eed8c009a979878261617f53e8264ddc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetReferencePosition-request>)))
  "Returns full string definition for message of type '<SetReferencePosition-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 position~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetReferencePosition-request)))
  "Returns full string definition for message of type 'SetReferencePosition-request"
  (cl:format cl:nil "geometry_msgs/Vector3 position~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetReferencePosition-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetReferencePosition-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetReferencePosition-request
    (cl:cons ':position (position msg))
))
;//! \htmlinclude SetReferencePosition-response.msg.html

(cl:defclass <SetReferencePosition-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetReferencePosition-response (<SetReferencePosition-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetReferencePosition-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetReferencePosition-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<SetReferencePosition-response> is deprecated: use microstrain_inertial_msgs-srv:SetReferencePosition-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetReferencePosition-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetReferencePosition-response>) ostream)
  "Serializes a message object of type '<SetReferencePosition-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetReferencePosition-response>) istream)
  "Deserializes a message object of type '<SetReferencePosition-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetReferencePosition-response>)))
  "Returns string type for a service object of type '<SetReferencePosition-response>"
  "microstrain_inertial_msgs/SetReferencePositionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetReferencePosition-response)))
  "Returns string type for a service object of type 'SetReferencePosition-response"
  "microstrain_inertial_msgs/SetReferencePositionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetReferencePosition-response>)))
  "Returns md5sum for a message object of type '<SetReferencePosition-response>"
  "eed8c009a979878261617f53e8264ddc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetReferencePosition-response)))
  "Returns md5sum for a message object of type 'SetReferencePosition-response"
  "eed8c009a979878261617f53e8264ddc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetReferencePosition-response>)))
  "Returns full string definition for message of type '<SetReferencePosition-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetReferencePosition-response)))
  "Returns full string definition for message of type 'SetReferencePosition-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetReferencePosition-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetReferencePosition-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetReferencePosition-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetReferencePosition)))
  'SetReferencePosition-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetReferencePosition)))
  'SetReferencePosition-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetReferencePosition)))
  "Returns string type for a service object of type '<SetReferencePosition>"
  "microstrain_inertial_msgs/SetReferencePosition")