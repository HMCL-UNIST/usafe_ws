;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::imageMask)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'imageMask (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::IMAGEMASK")
  (make-package "AUTORALLY_MSGS::IMAGEMASK"))

(in-package "ROS")
;;//! \htmlinclude imageMask.msg.html
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass autorally_msgs::imageMask
  :super ros::object
  :slots (_header _sender _points _lines _rois ))

(defmethod autorally_msgs::imageMask
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:sender __sender) "")
    ((:points __points) (let (r) (dotimes (i 0) (push (instance autorally_msgs::point2D :init) r)) r))
    ((:lines __lines) (let (r) (dotimes (i 0) (push (instance autorally_msgs::line2D :init) r)) r))
    ((:rois __rois) (let (r) (dotimes (i 0) (push (instance sensor_msgs::RegionOfInterest :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _sender (string __sender))
   (setq _points __points)
   (setq _lines __lines)
   (setq _rois __rois)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:sender
   (&optional __sender)
   (if __sender (setq _sender __sender)) _sender)
  (:points
   (&rest __points)
   (if (keywordp (car __points))
       (send* _points __points)
     (progn
       (if __points (setq _points (car __points)))
       _points)))
  (:lines
   (&rest __lines)
   (if (keywordp (car __lines))
       (send* _lines __lines)
     (progn
       (if __lines (setq _lines (car __lines)))
       _lines)))
  (:rois
   (&rest __rois)
   (if (keywordp (car __rois))
       (send* _rois __rois)
     (progn
       (if __rois (setq _rois (car __rois)))
       _rois)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _sender
    4 (length _sender)
    ;; autorally_msgs/point2D[] _points
    (apply #'+ (send-all _points :serialization-length)) 4
    ;; autorally_msgs/line2D[] _lines
    (apply #'+ (send-all _lines :serialization-length)) 4
    ;; sensor_msgs/RegionOfInterest[] _rois
    (apply #'+ (send-all _rois :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _sender
       (write-long (length _sender) s) (princ _sender s)
     ;; autorally_msgs/point2D[] _points
     (write-long (length _points) s)
     (dolist (elem _points)
       (send elem :serialize s)
       )
     ;; autorally_msgs/line2D[] _lines
     (write-long (length _lines) s)
     (dolist (elem _lines)
       (send elem :serialize s)
       )
     ;; sensor_msgs/RegionOfInterest[] _rois
     (write-long (length _rois) s)
     (dolist (elem _rois)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _sender
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _sender (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; autorally_msgs/point2D[] _points
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _points (let (r) (dotimes (i n) (push (instance autorally_msgs::point2D :init) r)) r))
     (dolist (elem- _points)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; autorally_msgs/line2D[] _lines
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lines (let (r) (dotimes (i n) (push (instance autorally_msgs::line2D :init) r)) r))
     (dolist (elem- _lines)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; sensor_msgs/RegionOfInterest[] _rois
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _rois (let (r) (dotimes (i n) (push (instance sensor_msgs::RegionOfInterest :init) r)) r))
     (dolist (elem- _rois)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get autorally_msgs::imageMask :md5sum-) "da71ef8be852ae3b57ef13c4fd86dd46")
(setf (get autorally_msgs::imageMask :datatype-) "autorally_msgs/imageMask")
(setf (get autorally_msgs::imageMask :definition-)
      "Header header

string sender
point2D[] points
line2D[] lines
sensor_msgs/RegionOfInterest[] rois

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
MSG: autorally_msgs/point2D
uint16 x
uint16 y

================================================================================
MSG: autorally_msgs/line2D
point2D start
point2D end

================================================================================
MSG: sensor_msgs/RegionOfInterest
# This message is used to specify a region of interest within an image.
#
# When used to specify the ROI setting of the camera when the image was
# taken, the height and width fields should either match the height and
# width fields for the associated image; or height = width = 0
# indicates that the full resolution image was captured.

uint32 x_offset  # Leftmost pixel of the ROI
                 # (0 if the ROI includes the left edge of the image)
uint32 y_offset  # Topmost pixel of the ROI
                 # (0 if the ROI includes the top edge of the image)
uint32 height    # Height of ROI
uint32 width     # Width of ROI

# True if a distinct rectified ROI should be calculated from the \"raw\"
# ROI in this message. Typically this should be False if the full image
# is captured (ROI not used), and True if a subwindow is captured (ROI
# used).
bool do_rectify

")



(provide :autorally_msgs/imageMask "da71ef8be852ae3b57ef13c4fd86dd46")


