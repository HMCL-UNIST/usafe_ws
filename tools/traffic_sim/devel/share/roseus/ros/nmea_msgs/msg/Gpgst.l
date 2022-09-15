;; Auto-generated. Do not edit!


(when (boundp 'nmea_msgs::Gpgst)
  (if (not (find-package "NMEA_MSGS"))
    (make-package "NMEA_MSGS"))
  (shadow 'Gpgst (find-package "NMEA_MSGS")))
(unless (find-package "NMEA_MSGS::GPGST")
  (make-package "NMEA_MSGS::GPGST"))

(in-package "ROS")
;;//! \htmlinclude Gpgst.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nmea_msgs::Gpgst
  :super ros::object
  :slots (_header _message_id _utc_seconds _rms _semi_major_dev _semi_minor_dev _orientation _lat_dev _lon_dev _alt_dev ))

(defmethod nmea_msgs::Gpgst
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:message_id __message_id) "")
    ((:utc_seconds __utc_seconds) 0.0)
    ((:rms __rms) 0.0)
    ((:semi_major_dev __semi_major_dev) 0.0)
    ((:semi_minor_dev __semi_minor_dev) 0.0)
    ((:orientation __orientation) 0.0)
    ((:lat_dev __lat_dev) 0.0)
    ((:lon_dev __lon_dev) 0.0)
    ((:alt_dev __alt_dev) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _message_id (string __message_id))
   (setq _utc_seconds (float __utc_seconds))
   (setq _rms (float __rms))
   (setq _semi_major_dev (float __semi_major_dev))
   (setq _semi_minor_dev (float __semi_minor_dev))
   (setq _orientation (float __orientation))
   (setq _lat_dev (float __lat_dev))
   (setq _lon_dev (float __lon_dev))
   (setq _alt_dev (float __alt_dev))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:message_id
   (&optional __message_id)
   (if __message_id (setq _message_id __message_id)) _message_id)
  (:utc_seconds
   (&optional __utc_seconds)
   (if __utc_seconds (setq _utc_seconds __utc_seconds)) _utc_seconds)
  (:rms
   (&optional __rms)
   (if __rms (setq _rms __rms)) _rms)
  (:semi_major_dev
   (&optional __semi_major_dev)
   (if __semi_major_dev (setq _semi_major_dev __semi_major_dev)) _semi_major_dev)
  (:semi_minor_dev
   (&optional __semi_minor_dev)
   (if __semi_minor_dev (setq _semi_minor_dev __semi_minor_dev)) _semi_minor_dev)
  (:orientation
   (&optional __orientation)
   (if __orientation (setq _orientation __orientation)) _orientation)
  (:lat_dev
   (&optional __lat_dev)
   (if __lat_dev (setq _lat_dev __lat_dev)) _lat_dev)
  (:lon_dev
   (&optional __lon_dev)
   (if __lon_dev (setq _lon_dev __lon_dev)) _lon_dev)
  (:alt_dev
   (&optional __alt_dev)
   (if __alt_dev (setq _alt_dev __alt_dev)) _alt_dev)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _message_id
    4 (length _message_id)
    ;; float64 _utc_seconds
    8
    ;; float32 _rms
    4
    ;; float32 _semi_major_dev
    4
    ;; float32 _semi_minor_dev
    4
    ;; float32 _orientation
    4
    ;; float32 _lat_dev
    4
    ;; float32 _lon_dev
    4
    ;; float32 _alt_dev
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _message_id
       (write-long (length _message_id) s) (princ _message_id s)
     ;; float64 _utc_seconds
       (sys::poke _utc_seconds (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _rms
       (sys::poke _rms (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _semi_major_dev
       (sys::poke _semi_major_dev (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _semi_minor_dev
       (sys::poke _semi_minor_dev (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _orientation
       (sys::poke _orientation (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _lat_dev
       (sys::poke _lat_dev (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _lon_dev
       (sys::poke _lon_dev (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _alt_dev
       (sys::poke _alt_dev (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _message_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _utc_seconds
     (setq _utc_seconds (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _rms
     (setq _rms (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _semi_major_dev
     (setq _semi_major_dev (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _semi_minor_dev
     (setq _semi_minor_dev (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _orientation
     (setq _orientation (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _lat_dev
     (setq _lat_dev (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _lon_dev
     (setq _lon_dev (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _alt_dev
     (setq _alt_dev (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get nmea_msgs::Gpgst :md5sum-) "e4b77f6f4c211629ab0307177f71dcee")
(setf (get nmea_msgs::Gpgst :datatype-) "nmea_msgs/Gpgst")
(setf (get nmea_msgs::Gpgst :definition-)
      "# Message from GPGST NMEA String
Header header

string message_id

# UTC seconds from midnight
float64 utc_seconds

# Root-Mean-Squared value of standard deviation of range inputs
float32 rms

# Standard Deviations of semi-major and minor axes of error ellipse
float32 semi_major_dev
float32 semi_minor_dev

# Orientation of the semi-major axis of error ellipse with respect to true north
float32 orientation

# Standard Deviations of latitude, longitude, and altitude measurements
float32 lat_dev
float32 lon_dev
float32 alt_dev

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

")



(provide :nmea_msgs/Gpgst "e4b77f6f4c211629ab0307177f71dcee")


