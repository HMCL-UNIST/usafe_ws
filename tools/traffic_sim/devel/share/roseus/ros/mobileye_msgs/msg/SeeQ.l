;; Auto-generated. Do not edit!


(when (boundp 'mobileye_msgs::SeeQ)
  (if (not (find-package "MOBILEYE_MSGS"))
    (make-package "MOBILEYE_MSGS"))
  (shadow 'SeeQ (find-package "MOBILEYE_MSGS")))
(unless (find-package "MOBILEYE_MSGS::SEEQ")
  (make-package "MOBILEYE_MSGS::SEEQ"))

(in-package "ROS")
;;//! \htmlinclude SeeQ.msg.html


(defclass mobileye_msgs::SeeQ
  :super ros::object
  :slots (_serial_number _production_date _brain_version_major _brain_version_minor _mest_version_major _mest_version_minor _mest_version_subminor _mest_version_patch_number ))

(defmethod mobileye_msgs::SeeQ
  (:init
   (&key
    ((:serial_number __serial_number) 0)
    ((:production_date __production_date) 0)
    ((:brain_version_major __brain_version_major) 0)
    ((:brain_version_minor __brain_version_minor) 0)
    ((:mest_version_major __mest_version_major) 0)
    ((:mest_version_minor __mest_version_minor) 0)
    ((:mest_version_subminor __mest_version_subminor) 0)
    ((:mest_version_patch_number __mest_version_patch_number) 0)
    )
   (send-super :init)
   (setq _serial_number (round __serial_number))
   (setq _production_date (round __production_date))
   (setq _brain_version_major (round __brain_version_major))
   (setq _brain_version_minor (round __brain_version_minor))
   (setq _mest_version_major (round __mest_version_major))
   (setq _mest_version_minor (round __mest_version_minor))
   (setq _mest_version_subminor (round __mest_version_subminor))
   (setq _mest_version_patch_number (round __mest_version_patch_number))
   self)
  (:serial_number
   (&optional __serial_number)
   (if __serial_number (setq _serial_number __serial_number)) _serial_number)
  (:production_date
   (&optional __production_date)
   (if __production_date (setq _production_date __production_date)) _production_date)
  (:brain_version_major
   (&optional __brain_version_major)
   (if __brain_version_major (setq _brain_version_major __brain_version_major)) _brain_version_major)
  (:brain_version_minor
   (&optional __brain_version_minor)
   (if __brain_version_minor (setq _brain_version_minor __brain_version_minor)) _brain_version_minor)
  (:mest_version_major
   (&optional __mest_version_major)
   (if __mest_version_major (setq _mest_version_major __mest_version_major)) _mest_version_major)
  (:mest_version_minor
   (&optional __mest_version_minor)
   (if __mest_version_minor (setq _mest_version_minor __mest_version_minor)) _mest_version_minor)
  (:mest_version_subminor
   (&optional __mest_version_subminor)
   (if __mest_version_subminor (setq _mest_version_subminor __mest_version_subminor)) _mest_version_subminor)
  (:mest_version_patch_number
   (&optional __mest_version_patch_number)
   (if __mest_version_patch_number (setq _mest_version_patch_number __mest_version_patch_number)) _mest_version_patch_number)
  (:serialization-length
   ()
   (+
    ;; uint32 _serial_number
    4
    ;; uint64 _production_date
    8
    ;; uint8 _brain_version_major
    1
    ;; uint8 _brain_version_minor
    1
    ;; uint8 _mest_version_major
    1
    ;; uint8 _mest_version_minor
    1
    ;; uint8 _mest_version_subminor
    1
    ;; uint8 _mest_version_patch_number
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _serial_number
       (write-long _serial_number s)
     ;; uint64 _production_date
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _production_date (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _production_date) (= (length (_production_date . bv)) 2)) ;; bignum
              (write-long (ash (elt (_production_date . bv) 0) 0) s)
              (write-long (ash (elt (_production_date . bv) 1) -1) s))
             ((and (class _production_date) (= (length (_production_date . bv)) 1)) ;; big1
              (write-long (elt (_production_date . bv) 0) s)
              (write-long (if (>= _production_date 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _production_date s)(write-long (if (>= _production_date 0) 0 #xffffffff) s)))
     ;; uint8 _brain_version_major
       (write-byte _brain_version_major s)
     ;; uint8 _brain_version_minor
       (write-byte _brain_version_minor s)
     ;; uint8 _mest_version_major
       (write-byte _mest_version_major s)
     ;; uint8 _mest_version_minor
       (write-byte _mest_version_minor s)
     ;; uint8 _mest_version_subminor
       (write-byte _mest_version_subminor s)
     ;; uint8 _mest_version_patch_number
       (write-byte _mest_version_patch_number s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _serial_number
     (setq _serial_number (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint64 _production_date
     
#+(or :alpha :irix6 :x86_64)
      (setf _production_date (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _production_date (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; uint8 _brain_version_major
     (setq _brain_version_major (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _brain_version_minor
     (setq _brain_version_minor (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _mest_version_major
     (setq _mest_version_major (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _mest_version_minor
     (setq _mest_version_minor (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _mest_version_subminor
     (setq _mest_version_subminor (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _mest_version_patch_number
     (setq _mest_version_patch_number (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get mobileye_msgs::SeeQ :md5sum-) "bd0f4ac945460fd2020ae1118ef5c53f")
(setf (get mobileye_msgs::SeeQ :datatype-) "mobileye_msgs/SeeQ")
(setf (get mobileye_msgs::SeeQ :definition-)
      "uint32 serial_number
uint64 production_date

uint8 brain_version_major
uint8 brain_version_minor
uint8 mest_version_major
uint8 mest_version_minor
uint8 mest_version_subminor
uint8 mest_version_patch_number
")



(provide :mobileye_msgs/SeeQ "bd0f4ac945460fd2020ae1118ef5c53f")


