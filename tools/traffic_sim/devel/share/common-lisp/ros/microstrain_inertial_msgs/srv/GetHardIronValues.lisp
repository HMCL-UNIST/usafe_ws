; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude GetHardIronValues-request.msg.html

(cl:defclass <GetHardIronValues-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetHardIronValues-request (<GetHardIronValues-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetHardIronValues-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetHardIronValues-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetHardIronValues-request> is deprecated: use microstrain_inertial_msgs-srv:GetHardIronValues-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetHardIronValues-request>) ostream)
  "Serializes a message object of type '<GetHardIronValues-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetHardIronValues-request>) istream)
  "Deserializes a message object of type '<GetHardIronValues-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetHardIronValues-request>)))
  "Returns string type for a service object of type '<GetHardIronValues-request>"
  "microstrain_inertial_msgs/GetHardIronValuesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetHardIronValues-request)))
  "Returns string type for a service object of type 'GetHardIronValues-request"
  "microstrain_inertial_msgs/GetHardIronValuesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetHardIronValues-request>)))
  "Returns md5sum for a message object of type '<GetHardIronValues-request>"
  "9427c94a8464f80e7ccfb4c788698d94")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetHardIronValues-request)))
  "Returns md5sum for a message object of type 'GetHardIronValues-request"
  "9427c94a8464f80e7ccfb4c788698d94")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetHardIronValues-request>)))
  "Returns full string definition for message of type '<GetHardIronValues-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetHardIronValues-request)))
  "Returns full string definition for message of type 'GetHardIronValues-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetHardIronValues-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetHardIronValues-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetHardIronValues-request
))
;//! \htmlinclude GetHardIronValues-response.msg.html

(cl:defclass <GetHardIronValues-response> (roslisp-msg-protocol:ros-message)
  ((bias
    :reader bias
    :initarg :bias
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GetHardIronValues-response (<GetHardIronValues-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetHardIronValues-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetHardIronValues-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<GetHardIronValues-response> is deprecated: use microstrain_inertial_msgs-srv:GetHardIronValues-response instead.")))

(cl:ensure-generic-function 'bias-val :lambda-list '(m))
(cl:defmethod bias-val ((m <GetHardIronValues-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:bias-val is deprecated.  Use microstrain_inertial_msgs-srv:bias instead.")
  (bias m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GetHardIronValues-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetHardIronValues-response>) ostream)
  "Serializes a message object of type '<GetHardIronValues-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bias) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetHardIronValues-response>) istream)
  "Deserializes a message object of type '<GetHardIronValues-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bias) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetHardIronValues-response>)))
  "Returns string type for a service object of type '<GetHardIronValues-response>"
  "microstrain_inertial_msgs/GetHardIronValuesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetHardIronValues-response)))
  "Returns string type for a service object of type 'GetHardIronValues-response"
  "microstrain_inertial_msgs/GetHardIronValuesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetHardIronValues-response>)))
  "Returns md5sum for a message object of type '<GetHardIronValues-response>"
  "9427c94a8464f80e7ccfb4c788698d94")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetHardIronValues-response)))
  "Returns md5sum for a message object of type 'GetHardIronValues-response"
  "9427c94a8464f80e7ccfb4c788698d94")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetHardIronValues-response>)))
  "Returns full string definition for message of type '<GetHardIronValues-response>"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetHardIronValues-response)))
  "Returns full string definition for message of type 'GetHardIronValues-response"
  (cl:format cl:nil "geometry_msgs/Vector3 bias~%bool success~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetHardIronValues-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bias))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetHardIronValues-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetHardIronValues-response
    (cl:cons ':bias (bias msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetHardIronValues)))
  'GetHardIronValues-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetHardIronValues)))
  'GetHardIronValues-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetHardIronValues)))
  "Returns string type for a service object of type '<GetHardIronValues>"
  "microstrain_inertial_msgs/GetHardIronValues")