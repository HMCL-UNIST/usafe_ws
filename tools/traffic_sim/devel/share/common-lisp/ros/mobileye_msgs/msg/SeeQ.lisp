; Auto-generated. Do not edit!


(cl:in-package mobileye_msgs-msg)


;//! \htmlinclude SeeQ.msg.html

(cl:defclass <SeeQ> (roslisp-msg-protocol:ros-message)
  ((serial_number
    :reader serial_number
    :initarg :serial_number
    :type cl:integer
    :initform 0)
   (production_date
    :reader production_date
    :initarg :production_date
    :type cl:integer
    :initform 0)
   (brain_version_major
    :reader brain_version_major
    :initarg :brain_version_major
    :type cl:fixnum
    :initform 0)
   (brain_version_minor
    :reader brain_version_minor
    :initarg :brain_version_minor
    :type cl:fixnum
    :initform 0)
   (mest_version_major
    :reader mest_version_major
    :initarg :mest_version_major
    :type cl:fixnum
    :initform 0)
   (mest_version_minor
    :reader mest_version_minor
    :initarg :mest_version_minor
    :type cl:fixnum
    :initform 0)
   (mest_version_subminor
    :reader mest_version_subminor
    :initarg :mest_version_subminor
    :type cl:fixnum
    :initform 0)
   (mest_version_patch_number
    :reader mest_version_patch_number
    :initarg :mest_version_patch_number
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SeeQ (<SeeQ>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SeeQ>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SeeQ)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mobileye_msgs-msg:<SeeQ> is deprecated: use mobileye_msgs-msg:SeeQ instead.")))

(cl:ensure-generic-function 'serial_number-val :lambda-list '(m))
(cl:defmethod serial_number-val ((m <SeeQ>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:serial_number-val is deprecated.  Use mobileye_msgs-msg:serial_number instead.")
  (serial_number m))

(cl:ensure-generic-function 'production_date-val :lambda-list '(m))
(cl:defmethod production_date-val ((m <SeeQ>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:production_date-val is deprecated.  Use mobileye_msgs-msg:production_date instead.")
  (production_date m))

(cl:ensure-generic-function 'brain_version_major-val :lambda-list '(m))
(cl:defmethod brain_version_major-val ((m <SeeQ>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:brain_version_major-val is deprecated.  Use mobileye_msgs-msg:brain_version_major instead.")
  (brain_version_major m))

(cl:ensure-generic-function 'brain_version_minor-val :lambda-list '(m))
(cl:defmethod brain_version_minor-val ((m <SeeQ>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:brain_version_minor-val is deprecated.  Use mobileye_msgs-msg:brain_version_minor instead.")
  (brain_version_minor m))

(cl:ensure-generic-function 'mest_version_major-val :lambda-list '(m))
(cl:defmethod mest_version_major-val ((m <SeeQ>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:mest_version_major-val is deprecated.  Use mobileye_msgs-msg:mest_version_major instead.")
  (mest_version_major m))

(cl:ensure-generic-function 'mest_version_minor-val :lambda-list '(m))
(cl:defmethod mest_version_minor-val ((m <SeeQ>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:mest_version_minor-val is deprecated.  Use mobileye_msgs-msg:mest_version_minor instead.")
  (mest_version_minor m))

(cl:ensure-generic-function 'mest_version_subminor-val :lambda-list '(m))
(cl:defmethod mest_version_subminor-val ((m <SeeQ>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:mest_version_subminor-val is deprecated.  Use mobileye_msgs-msg:mest_version_subminor instead.")
  (mest_version_subminor m))

(cl:ensure-generic-function 'mest_version_patch_number-val :lambda-list '(m))
(cl:defmethod mest_version_patch_number-val ((m <SeeQ>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mobileye_msgs-msg:mest_version_patch_number-val is deprecated.  Use mobileye_msgs-msg:mest_version_patch_number instead.")
  (mest_version_patch_number m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SeeQ>) ostream)
  "Serializes a message object of type '<SeeQ>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'serial_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'serial_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'serial_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'serial_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'production_date)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'production_date)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'production_date)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'production_date)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 32) (cl:slot-value msg 'production_date)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 40) (cl:slot-value msg 'production_date)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 48) (cl:slot-value msg 'production_date)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 56) (cl:slot-value msg 'production_date)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brain_version_major)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brain_version_minor)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mest_version_major)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mest_version_minor)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mest_version_subminor)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mest_version_patch_number)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SeeQ>) istream)
  "Deserializes a message object of type '<SeeQ>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'serial_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'serial_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'serial_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'serial_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'production_date)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'production_date)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'production_date)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'production_date)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 32) (cl:slot-value msg 'production_date)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 40) (cl:slot-value msg 'production_date)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 48) (cl:slot-value msg 'production_date)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 56) (cl:slot-value msg 'production_date)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brain_version_major)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brain_version_minor)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mest_version_major)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mest_version_minor)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mest_version_subminor)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mest_version_patch_number)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SeeQ>)))
  "Returns string type for a message object of type '<SeeQ>"
  "mobileye_msgs/SeeQ")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SeeQ)))
  "Returns string type for a message object of type 'SeeQ"
  "mobileye_msgs/SeeQ")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SeeQ>)))
  "Returns md5sum for a message object of type '<SeeQ>"
  "bd0f4ac945460fd2020ae1118ef5c53f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SeeQ)))
  "Returns md5sum for a message object of type 'SeeQ"
  "bd0f4ac945460fd2020ae1118ef5c53f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SeeQ>)))
  "Returns full string definition for message of type '<SeeQ>"
  (cl:format cl:nil "uint32 serial_number~%uint64 production_date~%~%uint8 brain_version_major~%uint8 brain_version_minor~%uint8 mest_version_major~%uint8 mest_version_minor~%uint8 mest_version_subminor~%uint8 mest_version_patch_number~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SeeQ)))
  "Returns full string definition for message of type 'SeeQ"
  (cl:format cl:nil "uint32 serial_number~%uint64 production_date~%~%uint8 brain_version_major~%uint8 brain_version_minor~%uint8 mest_version_major~%uint8 mest_version_minor~%uint8 mest_version_subminor~%uint8 mest_version_patch_number~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SeeQ>))
  (cl:+ 0
     4
     8
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SeeQ>))
  "Converts a ROS message object to a list"
  (cl:list 'SeeQ
    (cl:cons ':serial_number (serial_number msg))
    (cl:cons ':production_date (production_date msg))
    (cl:cons ':brain_version_major (brain_version_major msg))
    (cl:cons ':brain_version_minor (brain_version_minor msg))
    (cl:cons ':mest_version_major (mest_version_major msg))
    (cl:cons ':mest_version_minor (mest_version_minor msg))
    (cl:cons ':mest_version_subminor (mest_version_subminor msg))
    (cl:cons ':mest_version_patch_number (mest_version_patch_number msg))
))
