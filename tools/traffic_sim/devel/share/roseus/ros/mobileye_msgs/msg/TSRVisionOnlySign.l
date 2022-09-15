;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::TSRVisionOnlySign)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'TSRVisionOnlySign (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::TSRVISIONONLYSIGN")
  (make-package "MOBILEYE_MSGS::TSRVISIONONLYSIGN"))

(in-package "ROS")
;;//! \htmlinclude TSRVisionOnlySign.msg.html


(defclass mobileye_msgs::TSRVisionOnlySign
  :super ros::object
  :slots (_vision_only_sign_type_display_1 _vision_only_sign_type_display_2 _vision_only_sign_type_display_3 _vision_only_sign_type_display_4 _supplementary_sign_type_display_1 _supplementary_sign_type_display_2 _supplementary_sign_type_display_3 _supplementary_sign_type_display_4 ))

(defmethod mobileye_msgs::TSRVisionOnlySign
  (:init
   (&key
    ((:vision_only_sign_type_display_1 __vision_only_sign_type_display_1) 0)
    ((:vision_only_sign_type_display_2 __vision_only_sign_type_display_2) 0)
    ((:vision_only_sign_type_display_3 __vision_only_sign_type_display_3) 0)
    ((:vision_only_sign_type_display_4 __vision_only_sign_type_display_4) 0)
    ((:supplementary_sign_type_display_1 __supplementary_sign_type_display_1) 0)
    ((:supplementary_sign_type_display_2 __supplementary_sign_type_display_2) 0)
    ((:supplementary_sign_type_display_3 __supplementary_sign_type_display_3) 0)
    ((:supplementary_sign_type_display_4 __supplementary_sign_type_display_4) 0)
    )
   (send-super :init)
   (setq _vision_only_sign_type_display_1 (round __vision_only_sign_type_display_1))
   (setq _vision_only_sign_type_display_2 (round __vision_only_sign_type_display_2))
   (setq _vision_only_sign_type_display_3 (round __vision_only_sign_type_display_3))
   (setq _vision_only_sign_type_display_4 (round __vision_only_sign_type_display_4))
   (setq _supplementary_sign_type_display_1 (round __supplementary_sign_type_display_1))
   (setq _supplementary_sign_type_display_2 (round __supplementary_sign_type_display_2))
   (setq _supplementary_sign_type_display_3 (round __supplementary_sign_type_display_3))
   (setq _supplementary_sign_type_display_4 (round __supplementary_sign_type_display_4))
   self)
  (:vision_only_sign_type_display_1
   (&optional __vision_only_sign_type_display_1)
   (if __vision_only_sign_type_display_1 (setq _vision_only_sign_type_display_1 __vision_only_sign_type_display_1)) _vision_only_sign_type_display_1)
  (:vision_only_sign_type_display_2
   (&optional __vision_only_sign_type_display_2)
   (if __vision_only_sign_type_display_2 (setq _vision_only_sign_type_display_2 __vision_only_sign_type_display_2)) _vision_only_sign_type_display_2)
  (:vision_only_sign_type_display_3
   (&optional __vision_only_sign_type_display_3)
   (if __vision_only_sign_type_display_3 (setq _vision_only_sign_type_display_3 __vision_only_sign_type_display_3)) _vision_only_sign_type_display_3)
  (:vision_only_sign_type_display_4
   (&optional __vision_only_sign_type_display_4)
   (if __vision_only_sign_type_display_4 (setq _vision_only_sign_type_display_4 __vision_only_sign_type_display_4)) _vision_only_sign_type_display_4)
  (:supplementary_sign_type_display_1
   (&optional __supplementary_sign_type_display_1)
   (if __supplementary_sign_type_display_1 (setq _supplementary_sign_type_display_1 __supplementary_sign_type_display_1)) _supplementary_sign_type_display_1)
  (:supplementary_sign_type_display_2
   (&optional __supplementary_sign_type_display_2)
   (if __supplementary_sign_type_display_2 (setq _supplementary_sign_type_display_2 __supplementary_sign_type_display_2)) _supplementary_sign_type_display_2)
  (:supplementary_sign_type_display_3
   (&optional __supplementary_sign_type_display_3)
   (if __supplementary_sign_type_display_3 (setq _supplementary_sign_type_display_3 __supplementary_sign_type_display_3)) _supplementary_sign_type_display_3)
  (:supplementary_sign_type_display_4
   (&optional __supplementary_sign_type_display_4)
   (if __supplementary_sign_type_display_4 (setq _supplementary_sign_type_display_4 __supplementary_sign_type_display_4)) _supplementary_sign_type_display_4)
  (:serialization-length
   ()
   (+
    ;; uint8 _vision_only_sign_type_display_1
    1
    ;; uint8 _vision_only_sign_type_display_2
    1
    ;; uint8 _vision_only_sign_type_display_3
    1
    ;; uint8 _vision_only_sign_type_display_4
    1
    ;; uint8 _supplementary_sign_type_display_1
    1
    ;; uint8 _supplementary_sign_type_display_2
    1
    ;; uint8 _supplementary_sign_type_display_3
    1
    ;; uint8 _supplementary_sign_type_display_4
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _vision_only_sign_type_display_1
       (write-byte _vision_only_sign_type_display_1 s)
     ;; uint8 _vision_only_sign_type_display_2
       (write-byte _vision_only_sign_type_display_2 s)
     ;; uint8 _vision_only_sign_type_display_3
       (write-byte _vision_only_sign_type_display_3 s)
     ;; uint8 _vision_only_sign_type_display_4
       (write-byte _vision_only_sign_type_display_4 s)
     ;; uint8 _supplementary_sign_type_display_1
       (write-byte _supplementary_sign_type_display_1 s)
     ;; uint8 _supplementary_sign_type_display_2
       (write-byte _supplementary_sign_type_display_2 s)
     ;; uint8 _supplementary_sign_type_display_3
       (write-byte _supplementary_sign_type_display_3 s)
     ;; uint8 _supplementary_sign_type_display_4
       (write-byte _supplementary_sign_type_display_4 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _vision_only_sign_type_display_1
     (setq _vision_only_sign_type_display_1 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _vision_only_sign_type_display_2
     (setq _vision_only_sign_type_display_2 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _vision_only_sign_type_display_3
     (setq _vision_only_sign_type_display_3 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _vision_only_sign_type_display_4
     (setq _vision_only_sign_type_display_4 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _supplementary_sign_type_display_1
     (setq _supplementary_sign_type_display_1 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _supplementary_sign_type_display_2
     (setq _supplementary_sign_type_display_2 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _supplementary_sign_type_display_3
     (setq _supplementary_sign_type_display_3 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _supplementary_sign_type_display_4
     (setq _supplementary_sign_type_display_4 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::TSRVisionOnlySign :md5sum-) "81ad54807425b67a5be6ad808e97e8ee")
(setf (get mobileye_msgs::TSRVisionOnlySign :datatype-) "mobileye_msgs/TSRVisionOnlySign")
(setf (get mobileye_msgs::TSRVisionOnlySign :definition-)
      "uint8 vision_only_sign_type_display_1
uint8 vision_only_sign_type_display_2
uint8 vision_only_sign_type_display_3
uint8 vision_only_sign_type_display_4

uint8 supplementary_sign_type_display_1
uint8 supplementary_sign_type_display_2
uint8 supplementary_sign_type_display_3
uint8 supplementary_sign_type_display_4
")



(provide :mobileye_msgs/TSRVisionOnlySign "81ad54807425b67a5be6ad808e97e8ee")


