;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::RemoteButton)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'RemoteButton (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::REMOTEBUTTON")
  (make-package "HMCL_MSGS::REMOTEBUTTON"))

(in-package "ROS")
;;//! \htmlinclude RemoteButton.msg.html


(defclass hmcl_msgs::RemoteButton
  :super ros::object
  :slots (_button1 _button2 _button3 ))

(defmethod hmcl_msgs::RemoteButton
  (:init
   (&key
    ((:button1 __button1) 0)
    ((:button2 __button2) 0)
    ((:button3 __button3) 0)
    )
   (send-super :init)
   (setq _button1 (round __button1))
   (setq _button2 (round __button2))
   (setq _button3 (round __button3))
   self)
  (:button1
   (&optional __button1)
   (if __button1 (setq _button1 __button1)) _button1)
  (:button2
   (&optional __button2)
   (if __button2 (setq _button2 __button2)) _button2)
  (:button3
   (&optional __button3)
   (if __button3 (setq _button3 __button3)) _button3)
  (:serialization-length
   ()
   (+
    ;; uint8 _button1
    1
    ;; uint8 _button2
    1
    ;; uint8 _button3
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _button1
       (write-byte _button1 s)
     ;; uint8 _button2
       (write-byte _button2 s)
     ;; uint8 _button3
       (write-byte _button3 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _button1
     (setq _button1 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _button2
     (setq _button2 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _button3
     (setq _button3 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get hmcl_msgs::RemoteButton :md5sum-) "e0761a580fd3c116926a0b07701fd25f")
(setf (get hmcl_msgs::RemoteButton :datatype-) "hmcl_msgs/RemoteButton")
(setf (get hmcl_msgs::RemoteButton :definition-)
      "# wirelessbutton -> 0 push off, 1 -> push on
uint8 button1
uint8 button2
uint8 button3
")



(provide :hmcl_msgs/RemoteButton "e0761a580fd3c116926a0b07701fd25f")


