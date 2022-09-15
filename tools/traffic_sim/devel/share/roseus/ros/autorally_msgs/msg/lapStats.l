;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::lapStats)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'lapStats (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::LAPSTATS")
  (make-package "AUTORALLY_MSGS::LAPSTATS"))

(in-package "ROS")
;;//! \htmlinclude lapStats.msg.html


(defclass autorally_msgs::lapStats
  :super ros::object
  :slots (_lap_number _lap_time _max_speed _max_slip ))

(defmethod autorally_msgs::lapStats
  (:init
   (&key
    ((:lap_number __lap_number) 0)
    ((:lap_time __lap_time) 0.0)
    ((:max_speed __max_speed) 0.0)
    ((:max_slip __max_slip) 0.0)
    )
   (send-super :init)
   (setq _lap_number (round __lap_number))
   (setq _lap_time (float __lap_time))
   (setq _max_speed (float __max_speed))
   (setq _max_slip (float __max_slip))
   self)
  (:lap_number
   (&optional __lap_number)
   (if __lap_number (setq _lap_number __lap_number)) _lap_number)
  (:lap_time
   (&optional __lap_time)
   (if __lap_time (setq _lap_time __lap_time)) _lap_time)
  (:max_speed
   (&optional __max_speed)
   (if __max_speed (setq _max_speed __max_speed)) _max_speed)
  (:max_slip
   (&optional __max_slip)
   (if __max_slip (setq _max_slip __max_slip)) _max_slip)
  (:serialization-length
   ()
   (+
    ;; int64 _lap_number
    8
    ;; float64 _lap_time
    8
    ;; float64 _max_speed
    8
    ;; float64 _max_slip
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _lap_number
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _lap_number (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _lap_number) (= (length (_lap_number . bv)) 2)) ;; bignum
              (write-long (ash (elt (_lap_number . bv) 0) 0) s)
              (write-long (ash (elt (_lap_number . bv) 1) -1) s))
             ((and (class _lap_number) (= (length (_lap_number . bv)) 1)) ;; big1
              (write-long (elt (_lap_number . bv) 0) s)
              (write-long (if (>= _lap_number 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _lap_number s)(write-long (if (>= _lap_number 0) 0 #xffffffff) s)))
     ;; float64 _lap_time
       (sys::poke _lap_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_speed
       (sys::poke _max_speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_slip
       (sys::poke _max_slip (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _lap_number
#+(or :alpha :irix6 :x86_64)
      (setf _lap_number (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _lap_number (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; float64 _lap_time
     (setq _lap_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_speed
     (setq _max_speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_slip
     (setq _max_slip (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autorally_msgs::lapStats :md5sum-) "d0c1580b11cbef99426a15c0443b2e19")
(setf (get autorally_msgs::lapStats :datatype-) "autorally_msgs/lapStats")
(setf (get autorally_msgs::lapStats :definition-)
      "int64 lap_number
float64 lap_time
float64 max_speed
float64 max_slip

")



(provide :autorally_msgs/lapStats "d0c1580b11cbef99426a15c0443b2e19")


