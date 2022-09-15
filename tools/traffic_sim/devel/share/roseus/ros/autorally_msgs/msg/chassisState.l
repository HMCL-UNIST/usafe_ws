;; Auto-generated. Do not edit!


(when (boundp 'autorally_msgs::chassisState)
  (if (not (find-package "AUTORALLY_MSGS"))
    (make-package "AUTORALLY_MSGS"))
  (shadow 'chassisState (find-package "AUTORALLY_MSGS")))
(unless (find-package "AUTORALLY_MSGS::CHASSISSTATE")
  (make-package "AUTORALLY_MSGS::CHASSISSTATE"))

(in-package "ROS")
;;//! \htmlinclude chassisState.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass autorally_msgs::chassisState
  :super ros::object
  :slots (_header _throttleRelayEnabled _autonomousEnabled _runstopMotionEnabled _steeringCommander _steering _throttleCommander _throttle _frontBrakeCommander _frontBrake ))

(defmethod autorally_msgs::chassisState
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:throttleRelayEnabled __throttleRelayEnabled) nil)
    ((:autonomousEnabled __autonomousEnabled) nil)
    ((:runstopMotionEnabled __runstopMotionEnabled) nil)
    ((:steeringCommander __steeringCommander) "")
    ((:steering __steering) 0.0)
    ((:throttleCommander __throttleCommander) "")
    ((:throttle __throttle) 0.0)
    ((:frontBrakeCommander __frontBrakeCommander) "")
    ((:frontBrake __frontBrake) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _throttleRelayEnabled __throttleRelayEnabled)
   (setq _autonomousEnabled __autonomousEnabled)
   (setq _runstopMotionEnabled __runstopMotionEnabled)
   (setq _steeringCommander (string __steeringCommander))
   (setq _steering (float __steering))
   (setq _throttleCommander (string __throttleCommander))
   (setq _throttle (float __throttle))
   (setq _frontBrakeCommander (string __frontBrakeCommander))
   (setq _frontBrake (float __frontBrake))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:throttleRelayEnabled
   (&optional __throttleRelayEnabled)
   (if __throttleRelayEnabled (setq _throttleRelayEnabled __throttleRelayEnabled)) _throttleRelayEnabled)
  (:autonomousEnabled
   (&optional __autonomousEnabled)
   (if __autonomousEnabled (setq _autonomousEnabled __autonomousEnabled)) _autonomousEnabled)
  (:runstopMotionEnabled
   (&optional __runstopMotionEnabled)
   (if __runstopMotionEnabled (setq _runstopMotionEnabled __runstopMotionEnabled)) _runstopMotionEnabled)
  (:steeringCommander
   (&optional __steeringCommander)
   (if __steeringCommander (setq _steeringCommander __steeringCommander)) _steeringCommander)
  (:steering
   (&optional __steering)
   (if __steering (setq _steering __steering)) _steering)
  (:throttleCommander
   (&optional __throttleCommander)
   (if __throttleCommander (setq _throttleCommander __throttleCommander)) _throttleCommander)
  (:throttle
   (&optional __throttle)
   (if __throttle (setq _throttle __throttle)) _throttle)
  (:frontBrakeCommander
   (&optional __frontBrakeCommander)
   (if __frontBrakeCommander (setq _frontBrakeCommander __frontBrakeCommander)) _frontBrakeCommander)
  (:frontBrake
   (&optional __frontBrake)
   (if __frontBrake (setq _frontBrake __frontBrake)) _frontBrake)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; bool _throttleRelayEnabled
    1
    ;; bool _autonomousEnabled
    1
    ;; bool _runstopMotionEnabled
    1
    ;; string _steeringCommander
    4 (length _steeringCommander)
    ;; float64 _steering
    8
    ;; string _throttleCommander
    4 (length _throttleCommander)
    ;; float64 _throttle
    8
    ;; string _frontBrakeCommander
    4 (length _frontBrakeCommander)
    ;; float64 _frontBrake
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; bool _throttleRelayEnabled
       (if _throttleRelayEnabled (write-byte -1 s) (write-byte 0 s))
     ;; bool _autonomousEnabled
       (if _autonomousEnabled (write-byte -1 s) (write-byte 0 s))
     ;; bool _runstopMotionEnabled
       (if _runstopMotionEnabled (write-byte -1 s) (write-byte 0 s))
     ;; string _steeringCommander
       (write-long (length _steeringCommander) s) (princ _steeringCommander s)
     ;; float64 _steering
       (sys::poke _steering (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; string _throttleCommander
       (write-long (length _throttleCommander) s) (princ _throttleCommander s)
     ;; float64 _throttle
       (sys::poke _throttle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; string _frontBrakeCommander
       (write-long (length _frontBrakeCommander) s) (princ _frontBrakeCommander s)
     ;; float64 _frontBrake
       (sys::poke _frontBrake (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; bool _throttleRelayEnabled
     (setq _throttleRelayEnabled (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _autonomousEnabled
     (setq _autonomousEnabled (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _runstopMotionEnabled
     (setq _runstopMotionEnabled (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _steeringCommander
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _steeringCommander (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _steering
     (setq _steering (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; string _throttleCommander
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _throttleCommander (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _throttle
     (setq _throttle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; string _frontBrakeCommander
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _frontBrakeCommander (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _frontBrake
     (setq _frontBrake (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autorally_msgs::chassisState :md5sum-) "cbd23a33a5ec266cc70ab1630ddbccef")
(setf (get autorally_msgs::chassisState :datatype-) "autorally_msgs/chassisState")
(setf (get autorally_msgs::chassisState :definition-)
      "Header header

bool throttleRelayEnabled
bool autonomousEnabled
bool runstopMotionEnabled

string steeringCommander
float64 steering

string throttleCommander
float64 throttle

string frontBrakeCommander
float64 frontBrake
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :autorally_msgs/chassisState "cbd23a33a5ec266cc70ab1630ddbccef")


