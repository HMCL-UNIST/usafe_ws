;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_tsr)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_tsr (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_TSR")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_TSR"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_tsr.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_tsr
  :super ros::object
  :slots (_header _tsr _tsr_vision_only ))

(defmethod mobileye_msgs::MobileyeInfo_tsr
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:tsr __tsr) (let (r) (dotimes (i 0) (push (instance mobileye_msgs::TSR :init) r)) r))
    ((:tsr_vision_only __tsr_vision_only) (instance mobileye_msgs::TSRVisionOnlySign :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _tsr __tsr)
   (setq _tsr_vision_only __tsr_vision_only)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:tsr
   (&rest __tsr)
   (if (keywordp (car __tsr))
       (send* _tsr __tsr)
     (progn
       (if __tsr (setq _tsr (car __tsr)))
       _tsr)))
  (:tsr_vision_only
   (&rest __tsr_vision_only)
   (if (keywordp (car __tsr_vision_only))
       (send* _tsr_vision_only __tsr_vision_only)
     (progn
       (if __tsr_vision_only (setq _tsr_vision_only (car __tsr_vision_only)))
       _tsr_vision_only)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/TSR[] _tsr
    (apply #'+ (send-all _tsr :serialization-length)) 4
    ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
    (send _tsr_vision_only :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/TSR[] _tsr
     (write-long (length _tsr) s)
     (dolist (elem _tsr)
       (send elem :serialize s)
       )
     ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
       (send _tsr_vision_only :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/TSR[] _tsr
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _tsr (let (r) (dotimes (i n) (push (instance mobileye_msgs::TSR :init) r)) r))
     (dolist (elem- _tsr)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; mobileye_msgs/TSRVisionOnlySign _tsr_vision_only
     (send _tsr_vision_only :deserialize buf ptr-) (incf ptr- (send _tsr_vision_only :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_tsr :md5sum-) "12ef6ff06090fe03856140fe8fe950f9")
(setf (get mobileye_msgs::MobileyeInfo_tsr :datatype-) "mobileye_msgs/MobileyeInfo_tsr")
(setf (get mobileye_msgs::MobileyeInfo_tsr :definition-)
      "Header header

TSR[] tsr
TSRVisionOnlySign tsr_vision_only

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: mobileye_msgs/TSR
uint8 vision_only_sign_type
uint8 supplementary_sign_type
float32 sign_position_x
float32 sign_position_y
float32 sign_position_z
uint8 filter_type
================================================================================
MSG: mobileye_msgs/TSRVisionOnlySign
uint8 vision_only_sign_type_display_1
uint8 vision_only_sign_type_display_2
uint8 vision_only_sign_type_display_3
uint8 vision_only_sign_type_display_4

uint8 supplementary_sign_type_display_1
uint8 supplementary_sign_type_display_2
uint8 supplementary_sign_type_display_3
uint8 supplementary_sign_type_display_4
")



(provide :mobileye_msgs/MobileyeInfo_tsr "12ef6ff06090fe03856140fe8fe950f9")


