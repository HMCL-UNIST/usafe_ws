;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::VehicleGear)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'VehicleGear (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::VEHICLEGEAR")
  (make-package "HMCL_MSGS::VEHICLEGEAR"))

(in-package "ROS")
;;//! \htmlinclude VehicleGear.msg.html


(defclass hmcl_msgs::VehicleGear
  :super ros::object
  :slots (_gear ))

(defmethod hmcl_msgs::VehicleGear
  (:init
   (&key
    ((:gear __gear) 0)
    )
   (send-super :init)
   (setq _gear (round __gear))
   self)
  (:gear
   (&optional __gear)
   (if __gear (setq _gear __gear)) _gear)
  (:serialization-length
   ()
   (+
    ;; uint8 _gear
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _gear
       (write-byte _gear s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _gear
     (setq _gear (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get hmcl_msgs::VehicleGear :md5sum-) "8bb854d7dfa42e038a119fb419a368ec")
(setf (get hmcl_msgs::VehicleGear :datatype-) "hmcl_msgs/VehicleGear")
(setf (get hmcl_msgs::VehicleGear :definition-)
      "# Gear -> P       = 1
# Gear -> D       = 2
# Gear -> N       = 3
# Gear -> R       = 4
uint8 gear

")



(provide :hmcl_msgs/VehicleGear "8bb854d7dfa42e038a119fb419a368ec")


