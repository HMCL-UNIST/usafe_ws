;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::Gyro)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'Gyro (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::GYRO")
  (make-package "MOBILEYE_MSGS::GYRO"))

(in-package "ROS")
;;//! \htmlinclude Gyro.msg.html


(defclass mobileye_msgs::Gyro
  :super ros::object
  :slots (_gyro_sensor_data_available _x_axis_data ))

(defmethod mobileye_msgs::Gyro
  (:init
   (&key
    ((:gyro_sensor_data_available __gyro_sensor_data_available) nil)
    ((:x_axis_data __x_axis_data) 0.0)
    )
   (send-super :init)
   (setq _gyro_sensor_data_available __gyro_sensor_data_available)
   (setq _x_axis_data (float __x_axis_data))
   self)
  (:gyro_sensor_data_available
   (&optional __gyro_sensor_data_available)
   (if __gyro_sensor_data_available (setq _gyro_sensor_data_available __gyro_sensor_data_available)) _gyro_sensor_data_available)
  (:x_axis_data
   (&optional __x_axis_data)
   (if __x_axis_data (setq _x_axis_data __x_axis_data)) _x_axis_data)
  (:serialization-length
   ()
   (+
    ;; bool _gyro_sensor_data_available
    1
    ;; float32 _x_axis_data
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _gyro_sensor_data_available
       (if _gyro_sensor_data_available (write-byte -1 s) (write-byte 0 s))
     ;; float32 _x_axis_data
       (sys::poke _x_axis_data (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _gyro_sensor_data_available
     (setq _gyro_sensor_data_available (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _x_axis_data
     (setq _x_axis_data (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get mobileye_msgs::Gyro :md5sum-) "15689ec0f13fb1c15689a8f65d1fda0b")
(setf (get mobileye_msgs::Gyro :datatype-) "mobileye_msgs/Gyro")
(setf (get mobileye_msgs::Gyro :definition-)
      "bool gyro_sensor_data_available
float32 x_axis_data
")



(provide :mobileye_msgs/Gyro "15689ec0f13fb1c15689a8f65d1fda0b")


