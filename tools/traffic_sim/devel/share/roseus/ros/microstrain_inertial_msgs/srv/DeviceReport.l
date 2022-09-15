;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::DeviceReport)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'DeviceReport (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::DEVICEREPORT")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::DEVICEREPORT"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::DEVICEREPORTREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::DEVICEREPORTREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::DEVICEREPORTRESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::DEVICEREPORTRESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::DeviceReportRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::DeviceReportRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::DeviceReportResponse
  :super ros::object
  :slots (_model_name _model_number _serial_number _options _firmware_version _success ))

(defmethod microstrain_inertial_msgs::DeviceReportResponse
  (:init
   (&key
    ((:model_name __model_name) "")
    ((:model_number __model_number) "")
    ((:serial_number __serial_number) "")
    ((:options __options) "")
    ((:firmware_version __firmware_version) "")
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _model_name (string __model_name))
   (setq _model_number (string __model_number))
   (setq _serial_number (string __serial_number))
   (setq _options (string __options))
   (setq _firmware_version (string __firmware_version))
   (setq _success __success)
   self)
  (:model_name
   (&optional __model_name)
   (if __model_name (setq _model_name __model_name)) _model_name)
  (:model_number
   (&optional __model_number)
   (if __model_number (setq _model_number __model_number)) _model_number)
  (:serial_number
   (&optional __serial_number)
   (if __serial_number (setq _serial_number __serial_number)) _serial_number)
  (:options
   (&optional __options)
   (if __options (setq _options __options)) _options)
  (:firmware_version
   (&optional __firmware_version)
   (if __firmware_version (setq _firmware_version __firmware_version)) _firmware_version)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; string _model_name
    4 (length _model_name)
    ;; string _model_number
    4 (length _model_number)
    ;; string _serial_number
    4 (length _serial_number)
    ;; string _options
    4 (length _options)
    ;; string _firmware_version
    4 (length _firmware_version)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _model_name
       (write-long (length _model_name) s) (princ _model_name s)
     ;; string _model_number
       (write-long (length _model_number) s) (princ _model_number s)
     ;; string _serial_number
       (write-long (length _serial_number) s) (princ _serial_number s)
     ;; string _options
       (write-long (length _options) s) (princ _options s)
     ;; string _firmware_version
       (write-long (length _firmware_version) s) (princ _firmware_version s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _model_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _model_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _model_number
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _model_number (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _serial_number
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _serial_number (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _options
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _options (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _firmware_version
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _firmware_version (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::DeviceReport
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::DeviceReport :md5sum-) "1306d0bab1f48bed0d0146c601d0ebe2")
(setf (get microstrain_inertial_msgs::DeviceReport :datatype-) "microstrain_inertial_msgs/DeviceReport")
(setf (get microstrain_inertial_msgs::DeviceReport :request) microstrain_inertial_msgs::DeviceReportRequest)
(setf (get microstrain_inertial_msgs::DeviceReport :response) microstrain_inertial_msgs::DeviceReportResponse)

(defmethod microstrain_inertial_msgs::DeviceReportRequest
  (:response () (instance microstrain_inertial_msgs::DeviceReportResponse :init)))

(setf (get microstrain_inertial_msgs::DeviceReportRequest :md5sum-) "1306d0bab1f48bed0d0146c601d0ebe2")
(setf (get microstrain_inertial_msgs::DeviceReportRequest :datatype-) "microstrain_inertial_msgs/DeviceReportRequest")
(setf (get microstrain_inertial_msgs::DeviceReportRequest :definition-)
      "---
string model_name
string model_number
string serial_number
string options
string firmware_version
bool success
")

(setf (get microstrain_inertial_msgs::DeviceReportResponse :md5sum-) "1306d0bab1f48bed0d0146c601d0ebe2")
(setf (get microstrain_inertial_msgs::DeviceReportResponse :datatype-) "microstrain_inertial_msgs/DeviceReportResponse")
(setf (get microstrain_inertial_msgs::DeviceReportResponse :definition-)
      "---
string model_name
string model_number
string serial_number
string options
string firmware_version
bool success
")



(provide :microstrain_inertial_msgs/DeviceReport "1306d0bab1f48bed0d0146c601d0ebe2")


