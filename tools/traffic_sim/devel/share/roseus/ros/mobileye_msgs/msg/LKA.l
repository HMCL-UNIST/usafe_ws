;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::LKA)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'LKA (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::LKA")
  (make-package "MOBILEYE_MSGS::LKA"))

(in-package "ROS")
;;//! \htmlinclude LKA.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mobileye_msgs::LKA
  :super ros::object
  :slots (_header _left_lane _right_lane _reference_points _number_of_next_lane_markers _next_lane ))

(defmethod mobileye_msgs::LKA
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:left_lane __left_lane) (instance mobileye_msgs::LKAlane :init))
    ((:right_lane __right_lane) (instance mobileye_msgs::LKAlane :init))
    ((:reference_points __reference_points) (instance mobileye_msgs::ReferencePoints :init))
    ((:number_of_next_lane_markers __number_of_next_lane_markers) 0)
    ((:next_lane __next_lane) (let (r) (dotimes (i 0) (push (instance mobileye_msgs::LKAlane :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _left_lane __left_lane)
   (setq _right_lane __right_lane)
   (setq _reference_points __reference_points)
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
  (:left_lane
   (&rest __left_lane)
   (if (keywordp (car __left_lane))
       (send* _left_lane __left_lane)
     (progn
       (if __left_lane (setq _left_lane (car __left_lane)))
       _left_lane)))
  (:right_lane
   (&rest __right_lane)
   (if (keywordp (car __right_lane))
       (send* _right_lane __right_lane)
     (progn
       (if __right_lane (setq _right_lane (car __right_lane)))
       _right_lane)))
  (:reference_points
   (&rest __reference_points)
   (if (keywordp (car __reference_points))
       (send* _reference_points __reference_points)
     (progn
       (if __reference_points (setq _reference_points (car __reference_points)))
       _reference_points)))
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
    ;; mobileye_msgs/LKAlane _left_lane
    (send _left_lane :serialization-length)
    ;; mobileye_msgs/LKAlane _right_lane
    (send _right_lane :serialization-length)
    ;; mobileye_msgs/ReferencePoints _reference_points
    (send _reference_points :serialization-length)
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
     ;; mobileye_msgs/LKAlane _left_lane
       (send _left_lane :serialize s)
     ;; mobileye_msgs/LKAlane _right_lane
       (send _right_lane :serialize s)
     ;; mobileye_msgs/ReferencePoints _reference_points
       (send _reference_points :serialize s)
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
   ;; mobileye_msgs/LKAlane _left_lane
     (send _left_lane :deserialize buf ptr-) (incf ptr- (send _left_lane :serialization-length))
   ;; mobileye_msgs/LKAlane _right_lane
     (send _right_lane :deserialize buf ptr-) (incf ptr- (send _right_lane :serialization-length))
   ;; mobileye_msgs/ReferencePoints _reference_points
     (send _reference_points :deserialize buf ptr-) (incf ptr- (send _reference_points :serialization-length))
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

(setf (get mobileye_msgs::LKA :md5sum-) "b5e3ba1f4afa652894372b06e4e02639")
(setf (get mobileye_msgs::LKA :datatype-) "mobileye_msgs/LKA")
(setf (get mobileye_msgs::LKA :definition-)
      "Header header

LKAlane left_lane
LKAlane right_lane

ReferencePoints reference_points

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

================================================================================
MSG: mobileye_msgs/ReferencePoints
float32 ref_point1_position
float32 ref_point1_distance
bool ref_point1_validity
float32 ref_point2_position
float32 ref_point2_distance
bool ref_point2_validity
")



(provide :mobileye_msgs/LKA "b5e3ba1f4afa652894372b06e4e02639")


