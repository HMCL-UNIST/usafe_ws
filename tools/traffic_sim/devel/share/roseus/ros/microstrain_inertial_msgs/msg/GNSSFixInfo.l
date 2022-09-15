;; Auto-generated. Do not edit!


(when (boundp 'microstrain_inertial_msgs::GNSSFixInfo)
  (if (not (find-package "MICROSTRAIN_INERTIAL_MSGS"))
    (make-package "MICROSTRAIN_INERTIAL_MSGS"))
  (shadow 'GNSSFixInfo (find-package "MICROSTRAIN_INERTIAL_MSGS")))
(unless (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO")
  (make-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))

(in-package "ROS")
;;//! \htmlinclude GNSSFixInfo.msg.html


(intern "*FIX_3D*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(shadow '*FIX_3D* (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(defconstant microstrain_inertial_msgs::GNSSFixInfo::*FIX_3D* 0)
(intern "*FIX_2D*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(shadow '*FIX_2D* (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(defconstant microstrain_inertial_msgs::GNSSFixInfo::*FIX_2D* 1)
(intern "*FIX_TIME_ONLY*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(shadow '*FIX_TIME_ONLY* (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(defconstant microstrain_inertial_msgs::GNSSFixInfo::*FIX_TIME_ONLY* 2)
(intern "*FIX_NONE*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(shadow '*FIX_NONE* (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(defconstant microstrain_inertial_msgs::GNSSFixInfo::*FIX_NONE* 3)
(intern "*FIX_INVALID*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(shadow '*FIX_INVALID* (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(defconstant microstrain_inertial_msgs::GNSSFixInfo::*FIX_INVALID* 4)
(intern "*FIX_RTK_FLOAT*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(shadow '*FIX_RTK_FLOAT* (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(defconstant microstrain_inertial_msgs::GNSSFixInfo::*FIX_RTK_FLOAT* 5)
(intern "*FIX_RTK_FIXED*" (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(shadow '*FIX_RTK_FIXED* (find-package "MICROSTRAIN_INERTIAL_MSGS::GNSSFIXINFO"))
(defconstant microstrain_inertial_msgs::GNSSFixInfo::*FIX_RTK_FIXED* 6)
(defclass microstrain_inertial_msgs::GNSSFixInfo
  :super ros::object
  :slots (_fix_type _num_sv _sbas_used _dngss_used ))

(defmethod microstrain_inertial_msgs::GNSSFixInfo
  (:init
   (&key
    ((:fix_type __fix_type) 0)
    ((:num_sv __num_sv) 0)
    ((:sbas_used __sbas_used) nil)
    ((:dngss_used __dngss_used) nil)
    )
   (send-super :init)
   (setq _fix_type (round __fix_type))
   (setq _num_sv (round __num_sv))
   (setq _sbas_used __sbas_used)
   (setq _dngss_used __dngss_used)
   self)
  (:fix_type
   (&optional __fix_type)
   (if __fix_type (setq _fix_type __fix_type)) _fix_type)
  (:num_sv
   (&optional __num_sv)
   (if __num_sv (setq _num_sv __num_sv)) _num_sv)
  (:sbas_used
   (&optional __sbas_used)
   (if __sbas_used (setq _sbas_used __sbas_used)) _sbas_used)
  (:dngss_used
   (&optional __dngss_used)
   (if __dngss_used (setq _dngss_used __dngss_used)) _dngss_used)
  (:serialization-length
   ()
   (+
    ;; uint8 _fix_type
    1
    ;; uint8 _num_sv
    1
    ;; bool _sbas_used
    1
    ;; bool _dngss_used
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _fix_type
       (write-byte _fix_type s)
     ;; uint8 _num_sv
       (write-byte _num_sv s)
     ;; bool _sbas_used
       (if _sbas_used (write-byte -1 s) (write-byte 0 s))
     ;; bool _dngss_used
       (if _dngss_used (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _fix_type
     (setq _fix_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _num_sv
     (setq _num_sv (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _sbas_used
     (setq _sbas_used (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _dngss_used
     (setq _dngss_used (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get microstrain_inertial_msgs::GNSSFixInfo :md5sum-) "cb3314532886b25255798400e78fc222")
(setf (get microstrain_inertial_msgs::GNSSFixInfo :datatype-) "microstrain_inertial_msgs/GNSSFixInfo")
(setf (get microstrain_inertial_msgs::GNSSFixInfo :definition-)
      "uint8 fix_type
uint8 num_sv
bool sbas_used
bool dngss_used

uint8 FIX_3D = 0
uint8 FIX_2D = 1
uint8 FIX_TIME_ONLY = 2
uint8 FIX_NONE = 3
uint8 FIX_INVALID = 4
uint8 FIX_RTK_FLOAT = 5
uint8 FIX_RTK_FIXED = 6
")



(provide :microstrain_inertial_msgs/GNSSFixInfo "cb3314532886b25255798400e78fc222")


