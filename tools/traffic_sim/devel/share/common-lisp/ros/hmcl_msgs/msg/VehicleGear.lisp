; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude VehicleGear.msg.html

(cl:defclass <VehicleGear> (roslisp-msg-protocol:ros-message)
  ((gear
    :reader gear
    :initarg :gear
    :type cl:fixnum
    :initform 0))
)

(cl:defclass VehicleGear (<VehicleGear>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleGear>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleGear)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<VehicleGear> is deprecated: use hmcl_msgs-msg:VehicleGear instead.")))

(cl:ensure-generic-function 'gear-val :lambda-list '(m))
(cl:defmethod gear-val ((m <VehicleGear>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:gear-val is deprecated.  Use hmcl_msgs-msg:gear instead.")
  (gear m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleGear>) ostream)
  "Serializes a message object of type '<VehicleGear>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleGear>) istream)
  "Deserializes a message object of type '<VehicleGear>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleGear>)))
  "Returns string type for a message object of type '<VehicleGear>"
  "hmcl_msgs/VehicleGear")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleGear)))
  "Returns string type for a message object of type 'VehicleGear"
  "hmcl_msgs/VehicleGear")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleGear>)))
  "Returns md5sum for a message object of type '<VehicleGear>"
  "8bb854d7dfa42e038a119fb419a368ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleGear)))
  "Returns md5sum for a message object of type 'VehicleGear"
  "8bb854d7dfa42e038a119fb419a368ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleGear>)))
  "Returns full string definition for message of type '<VehicleGear>"
  (cl:format cl:nil "# Gear -> P       = 1~%# Gear -> D       = 2~%# Gear -> N       = 3~%# Gear -> R       = 4~%uint8 gear~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleGear)))
  "Returns full string definition for message of type 'VehicleGear"
  (cl:format cl:nil "# Gear -> P       = 1~%# Gear -> D       = 2~%# Gear -> N       = 3~%# Gear -> R       = 4~%uint8 gear~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleGear>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleGear>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleGear
    (cl:cons ':gear (gear msg))
))
