; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-srv)


;//! \htmlinclude DeviceReport-request.msg.html

(cl:defclass <DeviceReport-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass DeviceReport-request (<DeviceReport-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DeviceReport-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DeviceReport-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<DeviceReport-request> is deprecated: use microstrain_inertial_msgs-srv:DeviceReport-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DeviceReport-request>) ostream)
  "Serializes a message object of type '<DeviceReport-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DeviceReport-request>) istream)
  "Deserializes a message object of type '<DeviceReport-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DeviceReport-request>)))
  "Returns string type for a service object of type '<DeviceReport-request>"
  "microstrain_inertial_msgs/DeviceReportRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DeviceReport-request)))
  "Returns string type for a service object of type 'DeviceReport-request"
  "microstrain_inertial_msgs/DeviceReportRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DeviceReport-request>)))
  "Returns md5sum for a message object of type '<DeviceReport-request>"
  "1306d0bab1f48bed0d0146c601d0ebe2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DeviceReport-request)))
  "Returns md5sum for a message object of type 'DeviceReport-request"
  "1306d0bab1f48bed0d0146c601d0ebe2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DeviceReport-request>)))
  "Returns full string definition for message of type '<DeviceReport-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DeviceReport-request)))
  "Returns full string definition for message of type 'DeviceReport-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DeviceReport-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DeviceReport-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DeviceReport-request
))
;//! \htmlinclude DeviceReport-response.msg.html

(cl:defclass <DeviceReport-response> (roslisp-msg-protocol:ros-message)
  ((model_name
    :reader model_name
    :initarg :model_name
    :type cl:string
    :initform "")
   (model_number
    :reader model_number
    :initarg :model_number
    :type cl:string
    :initform "")
   (serial_number
    :reader serial_number
    :initarg :serial_number
    :type cl:string
    :initform "")
   (options
    :reader options
    :initarg :options
    :type cl:string
    :initform "")
   (firmware_version
    :reader firmware_version
    :initarg :firmware_version
    :type cl:string
    :initform "")
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass DeviceReport-response (<DeviceReport-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DeviceReport-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DeviceReport-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-srv:<DeviceReport-response> is deprecated: use microstrain_inertial_msgs-srv:DeviceReport-response instead.")))

(cl:ensure-generic-function 'model_name-val :lambda-list '(m))
(cl:defmethod model_name-val ((m <DeviceReport-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:model_name-val is deprecated.  Use microstrain_inertial_msgs-srv:model_name instead.")
  (model_name m))

(cl:ensure-generic-function 'model_number-val :lambda-list '(m))
(cl:defmethod model_number-val ((m <DeviceReport-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:model_number-val is deprecated.  Use microstrain_inertial_msgs-srv:model_number instead.")
  (model_number m))

(cl:ensure-generic-function 'serial_number-val :lambda-list '(m))
(cl:defmethod serial_number-val ((m <DeviceReport-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:serial_number-val is deprecated.  Use microstrain_inertial_msgs-srv:serial_number instead.")
  (serial_number m))

(cl:ensure-generic-function 'options-val :lambda-list '(m))
(cl:defmethod options-val ((m <DeviceReport-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:options-val is deprecated.  Use microstrain_inertial_msgs-srv:options instead.")
  (options m))

(cl:ensure-generic-function 'firmware_version-val :lambda-list '(m))
(cl:defmethod firmware_version-val ((m <DeviceReport-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:firmware_version-val is deprecated.  Use microstrain_inertial_msgs-srv:firmware_version instead.")
  (firmware_version m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <DeviceReport-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-srv:success-val is deprecated.  Use microstrain_inertial_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DeviceReport-response>) ostream)
  "Serializes a message object of type '<DeviceReport-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'model_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'model_name))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'model_number))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'model_number))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'serial_number))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'serial_number))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'options))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'options))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'firmware_version))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'firmware_version))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DeviceReport-response>) istream)
  "Deserializes a message object of type '<DeviceReport-response>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'model_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'model_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'model_number) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'model_number) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'serial_number) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'serial_number) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'options) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'options) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'firmware_version) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'firmware_version) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DeviceReport-response>)))
  "Returns string type for a service object of type '<DeviceReport-response>"
  "microstrain_inertial_msgs/DeviceReportResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DeviceReport-response)))
  "Returns string type for a service object of type 'DeviceReport-response"
  "microstrain_inertial_msgs/DeviceReportResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DeviceReport-response>)))
  "Returns md5sum for a message object of type '<DeviceReport-response>"
  "1306d0bab1f48bed0d0146c601d0ebe2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DeviceReport-response)))
  "Returns md5sum for a message object of type 'DeviceReport-response"
  "1306d0bab1f48bed0d0146c601d0ebe2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DeviceReport-response>)))
  "Returns full string definition for message of type '<DeviceReport-response>"
  (cl:format cl:nil "string model_name~%string model_number~%string serial_number~%string options~%string firmware_version~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DeviceReport-response)))
  "Returns full string definition for message of type 'DeviceReport-response"
  (cl:format cl:nil "string model_name~%string model_number~%string serial_number~%string options~%string firmware_version~%bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DeviceReport-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'model_name))
     4 (cl:length (cl:slot-value msg 'model_number))
     4 (cl:length (cl:slot-value msg 'serial_number))
     4 (cl:length (cl:slot-value msg 'options))
     4 (cl:length (cl:slot-value msg 'firmware_version))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DeviceReport-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DeviceReport-response
    (cl:cons ':model_name (model_name msg))
    (cl:cons ':model_number (model_number msg))
    (cl:cons ':serial_number (serial_number msg))
    (cl:cons ':options (options msg))
    (cl:cons ':firmware_version (firmware_version msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DeviceReport)))
  'DeviceReport-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DeviceReport)))
  'DeviceReport-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DeviceReport)))
  "Returns string type for a service object of type '<DeviceReport>"
  "microstrain_inertial_msgs/DeviceReport")