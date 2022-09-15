; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude ObstacleStatus.msg.html

(cl:defclass <ObstacleStatus> (roslisp-msg-protocol:ros-message)
  ((number_of_obstacles
    :reader number_of_obstacles
    :initarg :number_of_obstacles
    :type cl:fixnum
    :initform 0)
   (timestamp
    :reader timestamp
    :initarg :timestamp
    :type cl:fixnum
    :initform 0)
   (left_close_rang_cut_in
    :reader left_close_rang_cut_in
    :initarg :left_close_rang_cut_in
    :type cl:boolean
    :initform cl:nil)
   (right_close_rang_cut_in
    :reader right_close_rang_cut_in
    :initarg :right_close_rang_cut_in
    :type cl:boolean
    :initform cl:nil)
   (go
    :reader go
    :initarg :go
    :type cl:fixnum
    :initform 0)
   (close_car
    :reader close_car
    :initarg :close_car
    :type cl:boolean
    :initform cl:nil)
   (failsafe
    :reader failsafe
    :initarg :failsafe
    :type cl:fixnum
    :initform 0))
)

(cl:defclass ObstacleStatus (<ObstacleStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ObstacleStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ObstacleStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<ObstacleStatus> is deprecated: use mobileye_msgs-msg:ObstacleStatus instead.")))

(cl:ensure-generic-function 'number_of_obstacles-val :lambda-list '(m))
(cl:defmethod number_of_obstacles-val ((m <ObstacleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:number_of_obstacles-val is deprecated.  Use mobileye_msgs-msg:number_of_obstacles instead.")
  (number_of_obstacles m))

(cl:ensure-generic-function 'timestamp-val :lambda-list '(m))
(cl:defmethod timestamp-val ((m <ObstacleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:timestamp-val is deprecated.  Use mobileye_msgs-msg:timestamp instead.")
  (timestamp m))

(cl:ensure-generic-function 'left_close_rang_cut_in-val :lambda-list '(m))
(cl:defmethod left_close_rang_cut_in-val ((m <ObstacleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:left_close_rang_cut_in-val is deprecated.  Use mobileye_msgs-msg:left_close_rang_cut_in instead.")
  (left_close_rang_cut_in m))

(cl:ensure-generic-function 'right_close_rang_cut_in-val :lambda-list '(m))
(cl:defmethod right_close_rang_cut_in-val ((m <ObstacleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:right_close_rang_cut_in-val is deprecated.  Use mobileye_msgs-msg:right_close_rang_cut_in instead.")
  (right_close_rang_cut_in m))

(cl:ensure-generic-function 'go-val :lambda-list '(m))
(cl:defmethod go-val ((m <ObstacleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:go-val is deprecated.  Use mobileye_msgs-msg:go instead.")
  (go m))

(cl:ensure-generic-function 'close_car-val :lambda-list '(m))
(cl:defmethod close_car-val ((m <ObstacleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:close_car-val is deprecated.  Use mobileye_msgs-msg:close_car instead.")
  (close_car m))

(cl:ensure-generic-function 'failsafe-val :lambda-list '(m))
(cl:defmethod failsafe-val ((m <ObstacleStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:failsafe-val is deprecated.  Use mobileye_msgs-msg:failsafe instead.")
  (failsafe m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ObstacleStatus>) ostream)
  "Serializes a message object of type '<ObstacleStatus>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'number_of_obstacles)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'left_close_rang_cut_in) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'right_close_rang_cut_in) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'go)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'close_car) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'failsafe)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ObstacleStatus>) istream)
  "Deserializes a message object of type '<ObstacleStatus>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'number_of_obstacles)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timestamp)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'left_close_rang_cut_in) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'right_close_rang_cut_in) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'go)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'close_car) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'failsafe)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ObstacleStatus>)))
  "Returns string type for a message object of type '<ObstacleStatus>"
  "mobileye_msgs/ObstacleStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ObstacleStatus)))
  "Returns string type for a message object of type 'ObstacleStatus"
  "mobileye_msgs/ObstacleStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ObstacleStatus>)))
  "Returns md5sum for a message object of type '<ObstacleStatus>"
  "3b9b8b37869bebe9592f8765c69bab28")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ObstacleStatus)))
  "Returns md5sum for a message object of type 'ObstacleStatus"
  "3b9b8b37869bebe9592f8765c69bab28")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ObstacleStatus>)))
  "Returns full string definition for message of type '<ObstacleStatus>"
  (cl:format cl:nil "uint8 number_of_obstacles~%uint8 timestamp~%~%bool left_close_rang_cut_in~%bool right_close_rang_cut_in~%~%uint8 go~%bool close_car~%uint8 failsafe~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ObstacleStatus)))
  "Returns full string definition for message of type 'ObstacleStatus"
  (cl:format cl:nil "uint8 number_of_obstacles~%uint8 timestamp~%~%bool left_close_rang_cut_in~%bool right_close_rang_cut_in~%~%uint8 go~%bool close_car~%uint8 failsafe~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ObstacleStatus>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ObstacleStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'ObstacleStatus
    (cl:cons ':number_of_obstacles (number_of_obstacles msg))
    (cl:cons ':timestamp (timestamp msg))
    (cl:cons ':left_close_rang_cut_in (left_close_rang_cut_in msg))
    (cl:cons ':right_close_rang_cut_in (right_close_rang_cut_in msg))
    (cl:cons ':go (go msg))
    (cl:cons ':close_car (close_car msg))
    (cl:cons ':failsafe (failsafe msg))
))
