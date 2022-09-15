;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_seeq)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_seeq (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_SEEQ")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_SEEQ"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_seeq.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_seeq
  :super ros::object
  :slots (_header _seeq ))

(defmethod mobileye_msgs::MobileyeInfo_seeq
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:seeq __seeq) (instance mobileye_msgs::SeeQ :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _seeq __seeq)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:seeq
   (&rest __seeq)
   (if (keywordp (car __seeq))
       (send* _seeq __seeq)
     (progn
       (if __seeq (setq _seeq (car __seeq)))
       _seeq)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/SeeQ _seeq
    (send _seeq :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/SeeQ _seeq
       (send _seeq :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/SeeQ _seeq
     (send _seeq :deserialize buf ptr-) (incf ptr- (send _seeq :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_seeq :md5sum-) "44adbcbb0282c17f8d689edcb40bf0ce")
(setf (get mobileye_msgs::MobileyeInfo_seeq :datatype-) "mobileye_msgs/MobileyeInfo_seeq")
(setf (get mobileye_msgs::MobileyeInfo_seeq :definition-)
      "Header header

SeeQ seeq

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
MSG: mobileye_msgs/SeeQ
uint32 serial_number
uint64 production_date

uint8 brain_version_major
uint8 brain_version_minor
uint8 mest_version_major
uint8 mest_version_minor
uint8 mest_version_subminor
uint8 mest_version_patch_number
")



(provide :mobileye_msgs/MobileyeInfo_seeq "44adbcbb0282c17f8d689edcb40bf0ce")


