;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GNSSDualAntennaStatus)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GNSSDualAntennaStatus (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSDUALANTENNASTATUS")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GNSSDUALANTENNASTATUS"))

(in-package "ROS")
;;//! \htmlinclude GNSSDualAntennaStatus.msg.html


(defclass microstrain_inertial_msgs::GNSSDualAntennaStatus
  :super ros::object
  :slots (_gps_tow _heading _heading_uncertainty _fix_type _rcv_1_valid _rcv_2_valid _antenna_offsets_valid ))

(defmethod microstrain_inertial_msgs::GNSSDualAntennaStatus
  (:init
   (&key
    ((:gps_tow __gps_tow) 0.0)
    ((:heading __heading) 0.0)
    ((:heading_uncertainty __heading_uncertainty) 0.0)
    ((:fix_type __fix_type) 0)
    ((:rcv_1_valid __rcv_1_valid) 0)
    ((:rcv_2_valid __rcv_2_valid) 0)
    ((:antenna_offsets_valid __antenna_offsets_valid) 0)
    )
   (send-super :init)
   (setq _gps_tow (float __gps_tow))
   (setq _heading (float __heading))
   (setq _heading_uncertainty (float __heading_uncertainty))
   (setq _fix_type (round __fix_type))
   (setq _rcv_1_valid (round __rcv_1_valid))
   (setq _rcv_2_valid (round __rcv_2_valid))
   (setq _antenna_offsets_valid (round __antenna_offsets_valid))
   self)
  (:gps_tow
   (&optional __gps_tow)
   (if __gps_tow (setq _gps_tow __gps_tow)) _gps_tow)
  (:heading
   (&optional __heading)
   (if __heading (setq _heading __heading)) _heading)
  (:heading_uncertainty
   (&optional __heading_uncertainty)
   (if __heading_uncertainty (setq _heading_uncertainty __heading_uncertainty)) _heading_uncertainty)
  (:fix_type
   (&optional __fix_type)
   (if __fix_type (setq _fix_type __fix_type)) _fix_type)
  (:rcv_1_valid
   (&optional __rcv_1_valid)
   (if __rcv_1_valid (setq _rcv_1_valid __rcv_1_valid)) _rcv_1_valid)
  (:rcv_2_valid
   (&optional __rcv_2_valid)
   (if __rcv_2_valid (setq _rcv_2_valid __rcv_2_valid)) _rcv_2_valid)
  (:antenna_offsets_valid
   (&optional __antenna_offsets_valid)
   (if __antenna_offsets_valid (setq _antenna_offsets_valid __antenna_offsets_valid)) _antenna_offsets_valid)
  (:serialization-length
   ()
   (+
    ;; float32 _gps_tow
    4
    ;; float32 _heading
    4
    ;; float32 _heading_uncertainty
    4
    ;; uint8 _fix_type
    1
    ;; uint8 _rcv_1_valid
    1
    ;; uint8 _rcv_2_valid
    1
    ;; uint8 _antenna_offsets_valid
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _gps_tow
       (sys::poke _gps_tow (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading
       (sys::poke _heading (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading_uncertainty
       (sys::poke _heading_uncertainty (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _fix_type
       (write-byte _fix_type s)
     ;; uint8 _rcv_1_valid
       (write-byte _rcv_1_valid s)
     ;; uint8 _rcv_2_valid
       (write-byte _rcv_2_valid s)
     ;; uint8 _antenna_offsets_valid
       (write-byte _antenna_offsets_valid s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _gps_tow
     (setq _gps_tow (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading
     (setq _heading (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading_uncertainty
     (setq _heading_uncertainty (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _fix_type
     (setq _fix_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _rcv_1_valid
     (setq _rcv_1_valid (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _rcv_2_valid
     (setq _rcv_2_valid (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _antenna_offsets_valid
     (setq _antenna_offsets_valid (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::GNSSDualAntennaStatus :md5sum-) "efecf4f9bdf572f04f6f06ccc9c1095a")
(setf (get microstrain_inertial_msgs::GNSSDualAntennaStatus :datatype-) "microstrain_inertial_msgs/GNSSDualAntennaStatus")
(setf (get microstrain_inertial_msgs::GNSSDualAntennaStatus :definition-)
      "float32 gps_tow
float32 heading
float32 heading_uncertainty
uint8   fix_type
uint8   rcv_1_valid
uint8   rcv_2_valid
uint8   antenna_offsets_valid
")



(provide :microstrain_inertial_msgs/GNSSDualAntennaStatus "efecf4f9bdf572f04f6f06ccc9c1095a")


