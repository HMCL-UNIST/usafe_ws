;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_referencepoints)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_referencepoints (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_REFERENCEPOINTS")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_REFERENCEPOINTS"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_referencepoints.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_referencepoints
  :super ros::object
  :slots (_header _reference_points ))

(defmethod mobileye_msgs::MobileyeInfo_referencepoints
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:reference_points __reference_points) (instance mobileye_msgs::ReferencePoints :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _reference_points __reference_points)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:reference_points
   (&rest __reference_points)
   (if (keywordp (car __reference_points))
       (send* _reference_points __reference_points)
     (progn
       (if __reference_points (setq _reference_points (car __reference_points)))
       _reference_points)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; mobileye_msgs/ReferencePoints _reference_points
    (send _reference_points :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; mobileye_msgs/ReferencePoints _reference_points
       (send _reference_points :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; mobileye_msgs/ReferencePoints _reference_points
     (send _reference_points :deserialize buf ptr-) (incf ptr- (send _reference_points :serialization-length))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_referencepoints :md5sum-) "cb5549c03c083f3d1a2ac1fe68010326")
(setf (get mobileye_msgs::MobileyeInfo_referencepoints :datatype-) "mobileye_msgs/MobileyeInfo_referencepoints")
(setf (get mobileye_msgs::MobileyeInfo_referencepoints :definition-)
      "Header header

ReferencePoints reference_points


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
MSG: mobileye_msgs/ReferencePoints
float32 ref_point1_position
float32 ref_point1_distance
bool ref_point1_validity
float32 ref_point2_position
float32 ref_point2_distance
bool ref_point2_validity
")



(provide :mobileye_msgs/MobileyeInfo_referencepoints "cb5549c03c083f3d1a2ac1fe68010326")


