;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GetHeadingSource)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GetHeadingSource (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETHEADINGSOURCE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETHEADINGSOURCE"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETHEADINGSOURCEREQUEST")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETHEADINGSOURCEREQUEST"))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GETHEADINGSOURCERESPONSE")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GETHEADINGSOURCERESPONSE"))

(in-package "ROS")





(defclass microstrain_inertial_msgs::GetHeadingSourceRequest
  :super ros::object
  :slots ())

(defmethod microstrain_inertial_msgs::GetHeadingSourceRequest
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

(defclass microstrain_inertial_msgs::GetHeadingSourceResponse
  :super ros::object
  :slots (_heading_source _success ))

(defmethod microstrain_inertial_msgs::GetHeadingSourceResponse
  (:init
   (&key
    ((:heading_source __heading_source) 0)
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _heading_source (round __heading_source))
   (setq _success __success)
   self)
  (:heading_source
   (&optional __heading_source)
   (if __heading_source (setq _heading_source __heading_source)) _heading_source)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int8 _heading_source
    1
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _heading_source
       (write-byte _heading_source s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _heading_source
     (setq _heading_source (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _heading_source 127) (setq _heading_source (- _heading_source 256)))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass microstrain_inertial_msgs::GetHeadingSource
  :super ros::object
  :slots ())

(setf (get microstrain_inertial_msgs::GetHeadingSource :md5sum-) "2f4a68a47587634cd4d34560ad178beb")
(setf (get microstrain_inertial_msgs::GetHeadingSource :datatype-) "microstrain_inertial_msgs/GetHeadingSource")
(setf (get microstrain_inertial_msgs::GetHeadingSource :request) microstrain_inertial_msgs::GetHeadingSourceRequest)
(setf (get microstrain_inertial_msgs::GetHeadingSource :response) microstrain_inertial_msgs::GetHeadingSourceResponse)

(defmethod microstrain_inertial_msgs::GetHeadingSourceRequest
  (:response () (instance microstrain_inertial_msgs::GetHeadingSourceResponse :init)))

(setf (get microstrain_inertial_msgs::GetHeadingSourceRequest :md5sum-) "2f4a68a47587634cd4d34560ad178beb")
(setf (get microstrain_inertial_msgs::GetHeadingSourceRequest :datatype-) "microstrain_inertial_msgs/GetHeadingSourceRequest")
(setf (get microstrain_inertial_msgs::GetHeadingSourceRequest :definition-)
      "---
int8 heading_source
bool success

")

(setf (get microstrain_inertial_msgs::GetHeadingSourceResponse :md5sum-) "2f4a68a47587634cd4d34560ad178beb")
(setf (get microstrain_inertial_msgs::GetHeadingSourceResponse :datatype-) "microstrain_inertial_msgs/GetHeadingSourceResponse")
(setf (get microstrain_inertial_msgs::GetHeadingSourceResponse :definition-)
      "---
int8 heading_source
bool success

")



(provide :microstrain_inertial_msgs/GetHeadingSource "2f4a68a47587634cd4d34560ad178beb")


