; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetReferencePosition-request.msg.html

(cl:defclass <GetReferencePosition-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetReferencePosition-request (<GetReferencePosition-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetReferencePosition-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetReferencePosition-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetReferencePosition-request> is deprecated: use microstrain_inertial_msgs-srv:GetReferencePosition-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetReferencePosition-request>) ostream)
  "Serializes a message object of type '<GetReferencePosition-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetReferencePosition-request>) istream)
  "Deserializes a message object of type '<GetReferencePosition-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetReferencePosition-request>)))
  "Returns string type for a service object of type '<GetReferencePosition-request>"
  "microstrain_inertial_msgs/GetReferencePositionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetReferencePosition-request)))
  "Returns string type for a service object of type 'GetReferencePosition-request"
  "microstrain_inertial_msgs/GetReferencePositionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetReferencePosition-request>)))
  "Returns md5sum for a message object of type '<GetReferencePosition-request>"
  "10b5e069422b2cf203664f7c0186f64a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetReferencePosition-request)))
  "Returns md5sum for a message object of type 'GetReferencePosition-request"
  "10b5e069422b2cf203664f7c0186f64a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetReferencePosition-request>)))
  "Returns full string definition for message of type '<GetReferencePosition-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetReferencePosition-request)))
  "Returns full string definition for message of type 'GetReferencePosition-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetReferencePosition-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetReferencePosition-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetReferencePosition-request
))
;//! \htmlinclude GetReferencePosition-response.msg.html

(cl:defclass <GetReferencePosition-response> (roslisp-msg-protocol:ros-message)
  ((position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetReferencePosition-response (<GetReferencePosition-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetReferencePosition-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetReferencePosition-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetReferencePosition-response> is deprecated: use microstrain_inertial_msgs-srv:GetReferencePosition-response instead.")))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <GetReferencePosition-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:position-val is deprecated.  Use microstrain_inertial_msgs-srv:position instead.")
  (position m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetReferencePosition-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetReferencePosition-response>) ostream)
  "Serializes a message object of type '<GetReferencePosition-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetReferencePosition-response>) istream)
  "Deserializes a message object of type '<GetReferencePosition-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetReferencePosition-response>)))
  "Returns string type for a service object of type '<GetReferencePosition-response>"
  "microstrain_inertial_msgs/GetReferencePositionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetReferencePosition-response)))
  "Returns string type for a service object of type 'GetReferencePosition-response"
  "microstrain_inertial_msgs/GetReferencePositionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetReferencePosition-response>)))
  "Returns md5sum for a message object of type '<GetReferencePosition-response>"
  "10b5e069422b2cf203664f7c0186f64a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetReferencePosition-response)))
  "Returns md5sum for a message object of type 'GetReferencePosition-response"
  "10b5e069422b2cf203664f7c0186f64a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetReferencePosition-response>)))
  "Returns full string definition for message of type '<GetReferencePosition-response>"
  (cl:format cl:nil "geometry_msgs/Vector3 position~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetReferencePosition-response)))
  "Returns full string definition for message of type 'GetReferencePosition-response"
  (cl:format cl:nil "geometry_msgs/Vector3 position~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetReferencePosition-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetReferencePosition-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetReferencePosition-response
    (cl:cons ':position (position msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetReferencePosition)))
  'GetReferencePosition-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetReferencePosition)))
  'GetReferencePosition-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetReferencePosition)))
  "Returns string type for a service object of type '<GetReferencePosition>"
  "microstrain_inertial_msgs/GetReferencePosition")