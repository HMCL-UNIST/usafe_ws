;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::ReferencePoints)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'ReferencePoints (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::REFERENCEPOINTS")
  (make-package "MOBILEYE_MSGS::REFERENCEPOINTS"))

(in-package "ROS")
;;//! \htmlinclude ReferencePoints.msg.html


(defclass mobileye_msgs::ReferencePoints
  :super ros::object
  :slots (_ref_point1_position _ref_point1_distance _ref_point1_validity _ref_point2_position _ref_point2_distance _ref_point2_validity ))

(defmethod mobileye_msgs::ReferencePoints
  (:init
   (&key
    ((:ref_point1_position __ref_point1_position) 0.0)
    ((:ref_point1_distance __ref_point1_distance) 0.0)
    ((:ref_point1_validity __ref_point1_validity) nil)
    ((:ref_point2_position __ref_point2_position) 0.0)
    ((:ref_point2_distance __ref_point2_distance) 0.0)
    ((:ref_point2_validity __ref_point2_validity) nil)
    )
   (send-super :init)
   (setq _ref_point1_position (float __ref_point1_position))
   (setq _ref_point1_distance (float __ref_point1_distance))
   (setq _ref_point1_validity __ref_point1_validity)
   (setq _ref_point2_position (float __ref_point2_position))
   (setq _ref_point2_distance (float __ref_point2_distance))
   (setq _ref_point2_validity __ref_point2_validity)
   self)
  (:ref_point1_position
   (&optional __ref_point1_position)
   (if __ref_point1_position (setq _ref_point1_position __ref_point1_position)) _ref_point1_position)
  (:ref_point1_distance
   (&optional __ref_point1_distance)
   (if __ref_point1_distance (setq _ref_point1_distance __ref_point1_distance)) _ref_point1_distance)
  (:ref_point1_validity
   (&optional __ref_point1_validity)
   (if __ref_point1_validity (setq _ref_point1_validity __ref_point1_validity)) _ref_point1_validity)
  (:ref_point2_position
   (&optional __ref_point2_position)
   (if __ref_point2_position (setq _ref_point2_position __ref_point2_position)) _ref_point2_position)
  (:ref_point2_distance
   (&optional __ref_point2_distance)
   (if __ref_point2_distance (setq _ref_point2_distance __ref_point2_distance)) _ref_point2_distance)
  (:ref_point2_validity
   (&optional __ref_point2_validity)
   (if __ref_point2_validity (setq _ref_point2_validity __ref_point2_validity)) _ref_point2_validity)
  (:serialization-length
   ()
   (+
    ;; float32 _ref_point1_position
    4
    ;; float32 _ref_point1_distance
    4
    ;; bool _ref_point1_validity
    1
    ;; float32 _ref_point2_position
    4
    ;; float32 _ref_point2_distance
    4
    ;; bool _ref_point2_validity
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _ref_point1_position
       (sys::poke _ref_point1_position (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ref_point1_distance
       (sys::poke _ref_point1_distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _ref_point1_validity
       (if _ref_point1_validity (write-byte -1 s) (write-byte 0 s))
     ;; float32 _ref_point2_position
       (sys::poke _ref_point2_position (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ref_point2_distance
       (sys::poke _ref_point2_distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _ref_point2_validity
       (if _ref_point2_validity (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _ref_point1_position
     (setq _ref_point1_position (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ref_point1_distance
     (setq _ref_point1_distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _ref_point1_validity
     (setq _ref_point1_validity (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _ref_point2_position
     (setq _ref_point2_position (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ref_point2_distance
     (setq _ref_point2_distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _ref_point2_validity
     (setq _ref_point2_validity (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::ReferencePoints :md5sum-) "56eb2a2d0b9b9695b81746d73432e3b8")
(setf (get mobileye_msgs::ReferencePoints :datatype-) "mobileye_msgs/ReferencePoints")
(setf (get mobileye_msgs::ReferencePoints :definition-)
      "float32 ref_point1_position
float32 ref_point1_distance
bool ref_point1_validity
float32 ref_point2_position
float32 ref_point2_distance
bool ref_point2_validity
")



(provide :mobileye_msgs/ReferencePoints "56eb2a2d0b9b9695b81746d73432e3b8")


