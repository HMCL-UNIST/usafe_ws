;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::BehaviorFactor)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'BehaviorFactor (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::BEHAVIORFACTOR")
  (make-package "HMCL_MSGS::BEHAVIORFACTOR"))

(in-package "ROS")
;;//! \htmlinclude BehaviorFactor.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass hmcl_msgs::BehaviorFactor
  :super ros::object
  :slots (_header _transition_condition _front_id _stop_line_stop _front_dist ))

(defmethod hmcl_msgs::BehaviorFactor
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:transition_condition __transition_condition) (instance hmcl_msgs::TransitionCondition :init))
    ((:front_id __front_id) 0)
    ((:stop_line_stop __stop_line_stop) nil)
    ((:front_dist __front_dist) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _transition_condition __transition_condition)
   (setq _front_id (round __front_id))
   (setq _stop_line_stop __stop_line_stop)
   (setq _front_dist (float __front_dist))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:transition_condition
   (&rest __transition_condition)
   (if (keywordp (car __transition_condition))
       (send* _transition_condition __transition_condition)
     (progn
       (if __transition_condition (setq _transition_condition (car __transition_condition)))
       _transition_condition)))
  (:front_id
   (&optional __front_id)
   (if __front_id (setq _front_id __front_id)) _front_id)
  (:stop_line_stop
   (&optional __stop_line_stop)
   (if __stop_line_stop (setq _stop_line_stop __stop_line_stop)) _stop_line_stop)
  (:front_dist
   (&optional __front_dist)
   (if __front_dist (setq _front_dist __front_dist)) _front_dist)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; hmcl_msgs/TransitionCondition _transition_condition
    (send _transition_condition :serialization-length)
    ;; int16 _front_id
    2
    ;; bool _stop_line_stop
    1
    ;; float32 _front_dist
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; hmcl_msgs/TransitionCondition _transition_condition
       (send _transition_condition :serialize s)
     ;; int16 _front_id
       (write-word _front_id s)
     ;; bool _stop_line_stop
       (if _stop_line_stop (write-byte -1 s) (write-byte 0 s))
     ;; float32 _front_dist
       (sys::poke _front_dist (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; hmcl_msgs/TransitionCondition _transition_condition
     (send _transition_condition :deserialize buf ptr-) (incf ptr- (send _transition_condition :serialization-length))
   ;; int16 _front_id
     (setq _front_id (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; bool _stop_line_stop
     (setq _stop_line_stop (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _front_dist
     (setq _front_dist (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get hmcl_msgs::BehaviorFactor :md5sum-) "007955b848a31590079e09deb110b6e6")
(setf (get hmcl_msgs::BehaviorFactor :datatype-) "hmcl_msgs/BehaviorFactor")
(setf (get hmcl_msgs::BehaviorFactor :definition-)
      "Header header
hmcl_msgs/TransitionCondition transition_condition
int16 front_id
bool stop_line_stop
float32 front_dist

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

================================================================================
MSG: hmcl_msgs/TransitionCondition
bool missionStart
bool approachToStartPos
bool startArrivalCheck
bool startArrivalSuccess
bool frontCar
bool stationaryFrontCar
bool approachToCrosswalk
bool crosswalkPass
bool pedestrianOnCrosswalk
bool leftTurn
bool rightTurn
bool turn
bool trafficLightStop
bool stopCheck
bool luggageDrop
bool brokenFrontCar
bool laneChangeDone
bool essentialLaneChange
bool speedBumpSign
bool speedBumpPass
bool approachToGoalPos
bool goalArrivalCheck
")



(provide :hmcl_msgs/BehaviorFactor "007955b848a31590079e09deb110b6e6")


