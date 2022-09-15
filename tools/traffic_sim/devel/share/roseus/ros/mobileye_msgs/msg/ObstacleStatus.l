;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::ObstacleStatus)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'ObstacleStatus (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::OBSTACLESTATUS")
  (make-package "MOBILEYE_MSGS::OBSTACLESTATUS"))

(in-package "ROS")
;;//! \htmlinclude ObstacleStatus.msg.html


(defclass mobileye_msgs::ObstacleStatus
  :super ros::object
  :slots (_number_of_obstacles _timestamp _left_close_rang_cut_in _right_close_rang_cut_in _go _close_car _failsafe ))

(defmethod mobileye_msgs::ObstacleStatus
  (:init
   (&key
    ((:number_of_obstacles __number_of_obstacles) 0)
    ((:timestamp __timestamp) 0)
    ((:left_close_rang_cut_in __left_close_rang_cut_in) nil)
    ((:right_close_rang_cut_in __right_close_rang_cut_in) nil)
    ((:go __go) 0)
    ((:close_car __close_car) nil)
    ((:failsafe __failsafe) 0)
    )
   (send-super :init)
   (setq _number_of_obstacles (round __number_of_obstacles))
   (setq _timestamp (round __timestamp))
   (setq _left_close_rang_cut_in __left_close_rang_cut_in)
   (setq _right_close_rang_cut_in __right_close_rang_cut_in)
   (setq _go (round __go))
   (setq _close_car __close_car)
   (setq _failsafe (round __failsafe))
   self)
  (:number_of_obstacles
   (&optional __number_of_obstacles)
   (if __number_of_obstacles (setq _number_of_obstacles __number_of_obstacles)) _number_of_obstacles)
  (:timestamp
   (&optional __timestamp)
   (if __timestamp (setq _timestamp __timestamp)) _timestamp)
  (:left_close_rang_cut_in
   (&optional __left_close_rang_cut_in)
   (if __left_close_rang_cut_in (setq _left_close_rang_cut_in __left_close_rang_cut_in)) _left_close_rang_cut_in)
  (:right_close_rang_cut_in
   (&optional __right_close_rang_cut_in)
   (if __right_close_rang_cut_in (setq _right_close_rang_cut_in __right_close_rang_cut_in)) _right_close_rang_cut_in)
  (:go
   (&optional __go)
   (if __go (setq _go __go)) _go)
  (:close_car
   (&optional __close_car)
   (if __close_car (setq _close_car __close_car)) _close_car)
  (:failsafe
   (&optional __failsafe)
   (if __failsafe (setq _failsafe __failsafe)) _failsafe)
  (:serialization-length
   ()
   (+
    ;; uint8 _number_of_obstacles
    1
    ;; uint8 _timestamp
    1
    ;; bool _left_close_rang_cut_in
    1
    ;; bool _right_close_rang_cut_in
    1
    ;; uint8 _go
    1
    ;; bool _close_car
    1
    ;; uint8 _failsafe
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _number_of_obstacles
       (write-byte _number_of_obstacles s)
     ;; uint8 _timestamp
       (write-byte _timestamp s)
     ;; bool _left_close_rang_cut_in
       (if _left_close_rang_cut_in (write-byte -1 s) (write-byte 0 s))
     ;; bool _right_close_rang_cut_in
       (if _right_close_rang_cut_in (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _go
       (write-byte _go s)
     ;; bool _close_car
       (if _close_car (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _failsafe
       (write-byte _failsafe s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _number_of_obstacles
     (setq _number_of_obstacles (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _timestamp
     (setq _timestamp (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _left_close_rang_cut_in
     (setq _left_close_rang_cut_in (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _right_close_rang_cut_in
     (setq _right_close_rang_cut_in (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _go
     (setq _go (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _close_car
     (setq _close_car (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _failsafe
     (setq _failsafe (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::ObstacleStatus :md5sum-) "3b9b8b37869bebe9592f8765c69bab28")
(setf (get mobileye_msgs::ObstacleStatus :datatype-) "mobileye_msgs/ObstacleStatus")
(setf (get mobileye_msgs::ObstacleStatus :definition-)
      "uint8 number_of_obstacles
uint8 timestamp

bool left_close_rang_cut_in
bool right_close_rang_cut_in

uint8 go
bool close_car
uint8 failsafe

")



(provide :mobileye_msgs/ObstacleStatus "3b9b8b37869bebe9592f8765c69bab28")


