; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude Gyro.msg.html

(cl:defclass <Gyro> (roslisp-msg-protocol:ros-message)
  ((gyro_sensor_data_available
    :reader gyro_sensor_data_available
    :initarg :gyro_sensor_data_available
    :type cl:boolean
    :initform cl:nil)
   (x_axis_data
    :reader x_axis_data
    :initarg :x_axis_data
    :type cl:float
    :initform 0.0))
)

(cl:defclass Gyro (<Gyro>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Gyro>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Gyro)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<Gyro> is deprecated: use mobileye_msgs-msg:Gyro instead.")))

(cl:ensure-generic-function 'gyro_sensor_data_available-val :lambda-list '(m))
(cl:defmethod gyro_sensor_data_available-val ((m <Gyro>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:gyro_sensor_data_available-val is deprecated.  Use mobileye_msgs-msg:gyro_sensor_data_available instead.")
  (gyro_sensor_data_available m))

(cl:ensure-generic-function 'x_axis_data-val :lambda-list '(m))
(cl:defmethod x_axis_data-val ((m <Gyro>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:x_axis_data-val is deprecated.  Use mobileye_msgs-msg:x_axis_data instead.")
  (x_axis_data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Gyro>) ostream)
  "Serializes a message object of type '<Gyro>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'gyro_sensor_data_available) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x_axis_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Gyro>) istream)
  "Deserializes a message object of type '<Gyro>"
    (cl:setf (cl:slot-value msg 'gyro_sensor_data_available) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x_axis_data) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Gyro>)))
  "Returns string type for a message object of type '<Gyro>"
  "mobileye_msgs/Gyro")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Gyro)))
  "Returns string type for a message object of type 'Gyro"
  "mobileye_msgs/Gyro")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Gyro>)))
  "Returns md5sum for a message object of type '<Gyro>"
  "15689ec0f13fb1c15689a8f65d1fda0b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Gyro)))
  "Returns md5sum for a message object of type 'Gyro"
  "15689ec0f13fb1c15689a8f65d1fda0b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Gyro>)))
  "Returns full string definition for message of type '<Gyro>"
  (cl:format cl:nil "bool gyro_sensor_data_available~%float32 x_axis_data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Gyro)))
  "Returns full string definition for message of type 'Gyro"
  (cl:format cl:nil "bool gyro_sensor_data_available~%float32 x_axis_data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Gyro>))
  (cl:+ 0
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Gyro>))
  "Converts a ROS message object to a list"
  (cl:list 'Gyro
    (cl:cons ':gyro_sensor_data_available (gyro_sensor_data_available msg))
    (cl:cons ':x_axis_data (x_axis_data msg))
))
