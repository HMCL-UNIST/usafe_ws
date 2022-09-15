;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::VehicleLight)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'VehicleLight (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::VEHICLELIGHT")
  (make-package "HMCL_MSGS::VEHICLELIGHT"))

(in-package "ROS")
;;//! \htmlinclude VehicleLight.msg.html


(defclass hmcl_msgs::VehicleLight
  :super ros::object
  :slots (_left_light _right_light _hazard_light ))

(defmethod hmcl_msgs::VehicleLight
  (:init
   (&key
    ((:left_light __left_light) 0)
    ((:right_light __right_light) 0)
    ((:hazard_light __hazard_light) 0)
    )
   (send-super :init)
   (setq _left_light (round __left_light))
   (setq _right_light (round __right_light))
   (setq _hazard_light (round __hazard_light))
   self)
  (:left_light
   (&optional __left_light)
   (if __left_light (setq _left_light __left_light)) _left_light)
  (:right_light
   (&optional __right_light)
   (if __right_light (setq _right_light __right_light)) _right_light)
  (:hazard_light
   (&optional __hazard_light)
   (if __hazard_light (setq _hazard_light __hazard_light)) _hazard_light)
  (:serialization-length
   ()
   (+
    ;; uint8 _left_light
    1
    ;; uint8 _right_light
    1
    ;; uint8 _hazard_light
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _left_light
       (write-byte _left_light s)
     ;; uint8 _right_light
       (write-byte _right_light s)
     ;; uint8 _hazard_light
       (write-byte _hazard_light s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _left_light
     (setq _left_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _right_light
     (setq _right_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _hazard_light
     (setq _hazard_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get hmcl_msgs::VehicleLight :md5sum-) "b381125a33d115f19eb1624e1387eaae")
(setf (get hmcl_msgs::VehicleLight :datatype-) "hmcl_msgs/VehicleLight")
(setf (get hmcl_msgs::VehicleLight :definition-)
      "# 0 off, 1 on 
uint8 left_light
uint8 right_light
uint8 hazard_light
")



(provide :hmcl_msgs/VehicleLight "b381125a33d115f19eb1624e1387eaae")


