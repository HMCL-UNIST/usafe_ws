;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::MobileyeInfo_number_of_next_lane_markers)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'MobileyeInfo_number_of_next_lane_markers (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::MOBILEYEINFO_NUMBER_OF_NEXT_LANE_MARKERS")
  (make-package "MOBILEYE_MSGS::MOBILEYEINFO_NUMBER_OF_NEXT_LANE_MARKERS"))

(in-package "ROS")
;;//! \htmlinclude MobileyeInfo_number_of_next_lane_markers.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::MobileyeInfo_number_of_next_lane_markers
  :super ros::object
  :slots (_header _number_of_next_lane_markers _next_lane ))

(defmethod mobileye_msgs::MobileyeInfo_number_of_next_lane_markers
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:number_of_next_lane_markers __number_of_next_lane_markers) 0)
    ((:next_lane __next_lane) (let (r) (dotimes (i 0) (push (instance mobileye_msgs::LKAlane :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _number_of_next_lane_markers (round __number_of_next_lane_markers))
   (setq _next_lane __next_lane)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:number_of_next_lane_markers
   (&optional __number_of_next_lane_markers)
   (if __number_of_next_lane_markers (setq _number_of_next_lane_markers __number_of_next_lane_markers)) _number_of_next_lane_markers)
  (:next_lane
   (&rest __next_lane)
   (if (keywordp (car __next_lane))
       (send* _next_lane __next_lane)
     (progn
       (if __next_lane (setq _next_lane (car __next_lane)))
       _next_lane)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint8 _number_of_next_lane_markers
    1
    ;; mobileye_msgs/LKAlane[] _next_lane
    (apply #'+ (send-all _next_lane :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint8 _number_of_next_lane_markers
       (write-byte _number_of_next_lane_markers s)
     ;; mobileye_msgs/LKAlane[] _next_lane
     (write-long (length _next_lane) s)
     (dolist (elem _next_lane)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint8 _number_of_next_lane_markers
     (setq _number_of_next_lane_markers (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; mobileye_msgs/LKAlane[] _next_lane
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _next_lane (let (r) (dotimes (i n) (push (instance mobileye_msgs::LKAlane :init) r)) r))
     (dolist (elem- _next_lane)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get mobileye_msgs::MobileyeInfo_number_of_next_lane_markers :md5sum-) "d32c337c79d434dc5fdbc8145e767dc2")
(setf (get mobileye_msgs::MobileyeInfo_number_of_next_lane_markers :datatype-) "mobileye_msgs/MobileyeInfo_number_of_next_lane_markers")
(setf (get mobileye_msgs::MobileyeInfo_number_of_next_lane_markers :definition-)
      "Header header

uint8 number_of_next_lane_markers

LKAlane[] next_lane

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
MSG: mobileye_msgs/LKAlane
uint8 lane_type
uint8 quality
uint8 model_degree

float32 position_parameter_c0
float32 curvature_parameter_c2
float32 curvature_derivative_c3
float32 width_marking

float32 heading_angle_parameter_c1
float32 view_range
bool view_range_availability

")



(provide :mobileye_msgs/MobileyeInfo_number_of_next_lane_markers "d32c337c79d434dc5fdbc8145e767dc2")


