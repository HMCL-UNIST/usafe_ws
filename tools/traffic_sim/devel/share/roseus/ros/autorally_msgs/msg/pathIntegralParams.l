;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::pathIntegralParams)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'pathIntegralParams (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::PATHINTEGRALPARAMS")
  (make-package "AUTORALLY_MSGS::PATHINTEGRALPARAMS"))

(in-package "ROS")
;;//! \htmlinclude pathIntegralParams.msg.html


(defclass autorally_msgs::pathIntegralParams
  :super ros::object
  :slots (_hz _num_timesteps _num_iters _gamma _init_steering _init_throttle _steering_var _throttle_var _max_throttle _speed_coefficient _track_coefficient _max_slip_angle _track_slop _crash_coeff _map_path _desired_speed ))

(defmethod autorally_msgs::pathIntegralParams
  (:init
   (&key
    ((:hz __hz) 0)
    ((:num_timesteps __num_timesteps) 0)
    ((:num_iters __num_iters) 0)
    ((:gamma __gamma) 0.0)
    ((:init_steering __init_steering) 0.0)
    ((:init_throttle __init_throttle) 0.0)
    ((:steering_var __steering_var) 0.0)
    ((:throttle_var __throttle_var) 0.0)
    ((:max_throttle __max_throttle) 0.0)
    ((:speed_coefficient __speed_coefficient) 0.0)
    ((:track_coefficient __track_coefficient) 0.0)
    ((:max_slip_angle __max_slip_angle) 0.0)
    ((:track_slop __track_slop) 0.0)
    ((:crash_coeff __crash_coeff) 0.0)
    ((:map_path __map_path) "")
    ((:desired_speed __desired_speed) 0.0)
    )
   (send-super :init)
   (setq _hz (round __hz))
   (setq _num_timesteps (round __num_timesteps))
   (setq _num_iters (round __num_iters))
   (setq _gamma (float __gamma))
   (setq _init_steering (float __init_steering))
   (setq _init_throttle (float __init_throttle))
   (setq _steering_var (float __steering_var))
   (setq _throttle_var (float __throttle_var))
   (setq _max_throttle (float __max_throttle))
   (setq _speed_coefficient (float __speed_coefficient))
   (setq _track_coefficient (float __track_coefficient))
   (setq _max_slip_angle (float __max_slip_angle))
   (setq _track_slop (float __track_slop))
   (setq _crash_coeff (float __crash_coeff))
   (setq _map_path (string __map_path))
   (setq _desired_speed (float __desired_speed))
   self)
  (:hz
   (&optional __hz)
   (if __hz (setq _hz __hz)) _hz)
  (:num_timesteps
   (&optional __num_timesteps)
   (if __num_timesteps (setq _num_timesteps __num_timesteps)) _num_timesteps)
  (:num_iters
   (&optional __num_iters)
   (if __num_iters (setq _num_iters __num_iters)) _num_iters)
  (:gamma
   (&optional __gamma)
   (if __gamma (setq _gamma __gamma)) _gamma)
  (:init_steering
   (&optional __init_steering)
   (if __init_steering (setq _init_steering __init_steering)) _init_steering)
  (:init_throttle
   (&optional __init_throttle)
   (if __init_throttle (setq _init_throttle __init_throttle)) _init_throttle)
  (:steering_var
   (&optional __steering_var)
   (if __steering_var (setq _steering_var __steering_var)) _steering_var)
  (:throttle_var
   (&optional __throttle_var)
   (if __throttle_var (setq _throttle_var __throttle_var)) _throttle_var)
  (:max_throttle
   (&optional __max_throttle)
   (if __max_throttle (setq _max_throttle __max_throttle)) _max_throttle)
  (:speed_coefficient
   (&optional __speed_coefficient)
   (if __speed_coefficient (setq _speed_coefficient __speed_coefficient)) _speed_coefficient)
  (:track_coefficient
   (&optional __track_coefficient)
   (if __track_coefficient (setq _track_coefficient __track_coefficient)) _track_coefficient)
  (:max_slip_angle
   (&optional __max_slip_angle)
   (if __max_slip_angle (setq _max_slip_angle __max_slip_angle)) _max_slip_angle)
  (:track_slop
   (&optional __track_slop)
   (if __track_slop (setq _track_slop __track_slop)) _track_slop)
  (:crash_coeff
   (&optional __crash_coeff)
   (if __crash_coeff (setq _crash_coeff __crash_coeff)) _crash_coeff)
  (:map_path
   (&optional __map_path)
   (if __map_path (setq _map_path __map_path)) _map_path)
  (:desired_speed
   (&optional __desired_speed)
   (if __desired_speed (setq _desired_speed __desired_speed)) _desired_speed)
  (:serialization-length
   ()
   (+
    ;; int64 _hz
    8
    ;; int64 _num_timesteps
    8
    ;; int64 _num_iters
    8
    ;; float64 _gamma
    8
    ;; float64 _init_steering
    8
    ;; float64 _init_throttle
    8
    ;; float64 _steering_var
    8
    ;; float64 _throttle_var
    8
    ;; float64 _max_throttle
    8
    ;; float64 _speed_coefficient
    8
    ;; float64 _track_coefficient
    8
    ;; float64 _max_slip_angle
    8
    ;; float64 _track_slop
    8
    ;; float64 _crash_coeff
    8
    ;; string _map_path
    4 (length _map_path)
    ;; float64 _desired_speed
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _hz
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _hz (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _hz) (= (length (_hz . bv)) 2)) ;; bignum
              (write-long (ash (elt (_hz . bv) 0) 0) s)
              (write-long (ash (elt (_hz . bv) 1) -1) s))
             ((and (class _hz) (= (length (_hz . bv)) 1)) ;; big1
              (write-long (elt (_hz . bv) 0) s)
              (write-long (if (>= _hz 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _hz s)(write-long (if (>= _hz 0) 0 #xffffffff) s)))
     ;; int64 _num_timesteps
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _num_timesteps (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _num_timesteps) (= (length (_num_timesteps . bv)) 2)) ;; bignum
              (write-long (ash (elt (_num_timesteps . bv) 0) 0) s)
              (write-long (ash (elt (_num_timesteps . bv) 1) -1) s))
             ((and (class _num_timesteps) (= (length (_num_timesteps . bv)) 1)) ;; big1
              (write-long (elt (_num_timesteps . bv) 0) s)
              (write-long (if (>= _num_timesteps 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _num_timesteps s)(write-long (if (>= _num_timesteps 0) 0 #xffffffff) s)))
     ;; int64 _num_iters
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _num_iters (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _num_iters) (= (length (_num_iters . bv)) 2)) ;; bignum
              (write-long (ash (elt (_num_iters . bv) 0) 0) s)
              (write-long (ash (elt (_num_iters . bv) 1) -1) s))
             ((and (class _num_iters) (= (length (_num_iters . bv)) 1)) ;; big1
              (write-long (elt (_num_iters . bv) 0) s)
              (write-long (if (>= _num_iters 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _num_iters s)(write-long (if (>= _num_iters 0) 0 #xffffffff) s)))
     ;; float64 _gamma
       (sys::poke _gamma (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _init_steering
       (sys::poke _init_steering (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _init_throttle
       (sys::poke _init_throttle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steering_var
       (sys::poke _steering_var (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _throttle_var
       (sys::poke _throttle_var (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_throttle
       (sys::poke _max_throttle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_coefficient
       (sys::poke _speed_coefficient (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _track_coefficient
       (sys::poke _track_coefficient (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _max_slip_angle
       (sys::poke _max_slip_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _track_slop
       (sys::poke _track_slop (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _crash_coeff
       (sys::poke _crash_coeff (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; string _map_path
       (write-long (length _map_path) s) (princ _map_path s)
     ;; float64 _desired_speed
       (sys::poke _desired_speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _hz
#+(or :alpha :irix6 :x86_64)
      (setf _hz (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _hz (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _num_timesteps
#+(or :alpha :irix6 :x86_64)
      (setf _num_timesteps (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _num_timesteps (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _num_iters
#+(or :alpha :irix6 :x86_64)
      (setf _num_iters (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _num_iters (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; float64 _gamma
     (setq _gamma (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _init_steering
     (setq _init_steering (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _init_throttle
     (setq _init_throttle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steering_var
     (setq _steering_var (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _throttle_var
     (setq _throttle_var (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_throttle
     (setq _max_throttle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_coefficient
     (setq _speed_coefficient (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _track_coefficient
     (setq _track_coefficient (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _max_slip_angle
     (setq _max_slip_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _track_slop
     (setq _track_slop (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _crash_coeff
     (setq _crash_coeff (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; string _map_path
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _map_path (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _desired_speed
     (setq _desired_speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autorally_msgs::pathIntegralParams :md5sum-) "262665b21f53db4e41908d6cccfe0a29")
(setf (get autorally_msgs::pathIntegralParams :datatype-) "autorally_msgs/pathIntegralParams")
(setf (get autorally_msgs::pathIntegralParams :definition-)
      "int64 hz
int64 num_timesteps
int64 num_iters
float64 gamma
float64 init_steering
float64 init_throttle
float64 steering_var
float64 throttle_var
float64 max_throttle
float64 speed_coefficient
float64 track_coefficient
float64 max_slip_angle
float64 track_slop
float64 crash_coeff
string map_path
float64 desired_speed
")



(provide :autorally_msgs/pathIntegralParams "262665b21f53db4e41908d6cccfe0a29")


