; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude VehicleLight.msg.html

(cl:defclass <VehicleLight> (roslisp-msg-protocol:ros-message)
  ((left_light
    :reader left_light
    :initarg :left_light
    :type cl:fixnum
    :initform 0)
   (right_light
    :reader right_light
    :initarg :right_light
    :type cl:fixnum
    :initform 0)
   (hazard_light
    :reader hazard_light
    :initarg :hazard_light
    :type cl:fixnum
    :initform 0))
)

(cl:defclass VehicleLight (<VehicleLight>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleLight>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleLight)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<VehicleLight> is deprecated: use hmcl_msgs-msg:VehicleLight instead.")))

(cl:ensure-generic-function 'left_light-val :lambda-list '(m))
(cl:defmethod left_light-val ((m <VehicleLight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:left_light-val is deprecated.  Use hmcl_msgs-msg:left_light instead.")
  (left_light m))

(cl:ensure-generic-function 'right_light-val :lambda-list '(m))
(cl:defmethod right_light-val ((m <VehicleLight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:right_light-val is deprecated.  Use hmcl_msgs-msg:right_light instead.")
  (right_light m))

(cl:ensure-generic-function 'hazard_light-val :lambda-list '(m))
(cl:defmethod hazard_light-val ((m <VehicleLight>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:hazard_light-val is deprecated.  Use hmcl_msgs-msg:hazard_light instead.")
  (hazard_light m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleLight>) ostream)
  "Serializes a message object of type '<VehicleLight>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'left_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'right_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hazard_light)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleLight>) istream)
  "Deserializes a message object of type '<VehicleLight>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'left_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'right_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hazard_light)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleLight>)))
  "Returns string type for a message object of type '<VehicleLight>"
  "hmcl_msgs/VehicleLight")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleLight)))
  "Returns string type for a message object of type 'VehicleLight"
  "hmcl_msgs/VehicleLight")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleLight>)))
  "Returns md5sum for a message object of type '<VehicleLight>"
  "b381125a33d115f19eb1624e1387eaae")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleLight)))
  "Returns md5sum for a message object of type 'VehicleLight"
  "b381125a33d115f19eb1624e1387eaae")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleLight>)))
  "Returns full string definition for message of type '<VehicleLight>"
  (cl:format cl:nil "# 0 off, 1 on ~%uint8 left_light~%uint8 right_light~%uint8 hazard_light~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleLight)))
  "Returns full string definition for message of type 'VehicleLight"
  (cl:format cl:nil "# 0 off, 1 on ~%uint8 left_light~%uint8 right_light~%uint8 hazard_light~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleLight>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleLight>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleLight
    (cl:cons ':left_light (left_light msg))
    (cl:cons ':right_light (right_light msg))
    (cl:cons ':hazard_light (hazard_light msg))
))
