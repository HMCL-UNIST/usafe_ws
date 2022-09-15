; Auto-generated. Do not edit!


(cl:in-package microstrain_inertial_msgs-msg)


;//! \htmlinclude FilterAidingMeasurementSummaryIndicator.msg.html

(cl:defclass <FilterAidingMeasurementSummaryIndicator> (roslisp-msg-protocol:ros-message)
  ((enabled
    :reader enabled
    :initarg :enabled
    :type cl:boolean
    :initform cl:nil)
   (used
    :reader used
    :initarg :used
    :type cl:boolean
    :initform cl:nil)
   (residual_high_warning
    :reader residual_high_warning
    :initarg :residual_high_warning
    :type cl:boolean
    :initform cl:nil)
   (sample_time_warning
    :reader sample_time_warning
    :initarg :sample_time_warning
    :type cl:boolean
    :initform cl:nil)
   (configuration_error
    :reader configuration_error
    :initarg :configuration_error
    :type cl:boolean
    :initform cl:nil)
   (max_num_meas_exceeded
    :reader max_num_meas_exceeded
    :initarg :max_num_meas_exceeded
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass FilterAidingMeasurementSummaryIndicator (<FilterAidingMeasurementSummaryIndicator>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FilterAidingMeasurementSummaryIndicator>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FilterAidingMeasurementSummaryIndicator)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name microstrain_inertial_msgs-msg:<FilterAidingMeasurementSummaryIndicator> is deprecated: use microstrain_inertial_msgs-msg:FilterAidingMeasurementSummaryIndicator instead.")))

(cl:ensure-generic-function 'enabled-val :lambda-list '(m))
(cl:defmethod enabled-val ((m <FilterAidingMeasurementSummaryIndicator>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:enabled-val is deprecated.  Use microstrain_inertial_msgs-msg:enabled instead.")
  (enabled m))

(cl:ensure-generic-function 'used-val :lambda-list '(m))
(cl:defmethod used-val ((m <FilterAidingMeasurementSummaryIndicator>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:used-val is deprecated.  Use microstrain_inertial_msgs-msg:used instead.")
  (used m))

(cl:ensure-generic-function 'residual_high_warning-val :lambda-list '(m))
(cl:defmethod residual_high_warning-val ((m <FilterAidingMeasurementSummaryIndicator>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:residual_high_warning-val is deprecated.  Use microstrain_inertial_msgs-msg:residual_high_warning instead.")
  (residual_high_warning m))

(cl:ensure-generic-function 'sample_time_warning-val :lambda-list '(m))
(cl:defmethod sample_time_warning-val ((m <FilterAidingMeasurementSummaryIndicator>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:sample_time_warning-val is deprecated.  Use microstrain_inertial_msgs-msg:sample_time_warning instead.")
  (sample_time_warning m))

(cl:ensure-generic-function 'configuration_error-val :lambda-list '(m))
(cl:defmethod configuration_error-val ((m <FilterAidingMeasurementSummaryIndicator>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:configuration_error-val is deprecated.  Use microstrain_inertial_msgs-msg:configuration_error instead.")
  (configuration_error m))

(cl:ensure-generic-function 'max_num_meas_exceeded-val :lambda-list '(m))
(cl:defmethod max_num_meas_exceeded-val ((m <FilterAidingMeasurementSummaryIndicator>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader microstrain_inertial_msgs-msg:max_num_meas_exceeded-val is deprecated.  Use microstrain_inertial_msgs-msg:max_num_meas_exceeded instead.")
  (max_num_meas_exceeded m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FilterAidingMeasurementSummaryIndicator>) ostream)
  "Serializes a message object of type '<FilterAidingMeasurementSummaryIndicator>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'enabled) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'used) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'residual_high_warning) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'sample_time_warning) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'configuration_error) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'max_num_meas_exceeded) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FilterAidingMeasurementSummaryIndicator>) istream)
  "Deserializes a message object of type '<FilterAidingMeasurementSummaryIndicator>"
    (cl:setf (cl:slot-value msg 'enabled) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'used) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'residual_high_warning) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'sample_time_warning) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'configuration_error) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'max_num_meas_exceeded) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FilterAidingMeasurementSummaryIndicator>)))
  "Returns string type for a message object of type '<FilterAidingMeasurementSummaryIndicator>"
  "microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FilterAidingMeasurementSummaryIndicator)))
  "Returns string type for a message object of type 'FilterAidingMeasurementSummaryIndicator"
  "microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FilterAidingMeasurementSummaryIndicator>)))
  "Returns md5sum for a message object of type '<FilterAidingMeasurementSummaryIndicator>"
  "4e3131125b51ac75dceed1517c488713")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FilterAidingMeasurementSummaryIndicator)))
  "Returns md5sum for a message object of type 'FilterAidingMeasurementSummaryIndicator"
  "4e3131125b51ac75dceed1517c488713")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FilterAidingMeasurementSummaryIndicator>)))
  "Returns full string definition for message of type '<FilterAidingMeasurementSummaryIndicator>"
  (cl:format cl:nil "bool enabled~%bool used~%bool residual_high_warning~%bool sample_time_warning~%bool configuration_error~%bool max_num_meas_exceeded~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FilterAidingMeasurementSummaryIndicator)))
  "Returns full string definition for message of type 'FilterAidingMeasurementSummaryIndicator"
  (cl:format cl:nil "bool enabled~%bool used~%bool residual_high_warning~%bool sample_time_warning~%bool configuration_error~%bool max_num_meas_exceeded~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FilterAidingMeasurementSummaryIndicator>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FilterAidingMeasurementSummaryIndicator>))
  "Converts a ROS message object to a list"
  (cl:list 'FilterAidingMeasurementSummaryIndicator
    (cl:cons ':enabled (enabled msg))
    (cl:cons ':used (used msg))
    (cl:cons ':residual_high_warning (residual_high_warning msg))
    (cl:cons ':sample_time_warning (sample_time_warning msg))
    (cl:cons ':configuration_error (configuration_error msg))
    (cl:cons ':max_num_meas_exceeded (max_num_meas_exceeded msg))
))
