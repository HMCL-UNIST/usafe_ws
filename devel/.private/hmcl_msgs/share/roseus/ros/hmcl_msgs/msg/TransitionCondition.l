;; Auto-generated. Do not edit!


(when (boundp 'hmcl_msgs::TransitionCondition)
  (if (not (find-package "HMCL_MSGS"))
    (make-package "HMCL_MSGS"))
  (shadow 'TransitionCondition (find-package "HMCL_MSGS")))
(unless (find-package "HMCL_MSGS::TRANSITIONCONDITION")
  (make-package "HMCL_MSGS::TRANSITIONCONDITION"))

(in-package "ROS")
;;//! \htmlinclude TransitionCondition.msg.html


(defclass hmcl_msgs::TransitionCondition
  :super ros::object
  :slots (_missionStart _approachToStartPos _startArrivalCheck _startArrivalSuccess _frontCar _stationaryFrontCar _approachToCrosswalk _crosswalkPass _pedestrianOnCrosswalk _leftTurn _rightTurn _turn _trafficLightStop _stopCheck _luggageDrop _brokenFrontCar _laneChangeDone _essentialLaneChange _speedBumpSign _speedBumpPass _approachToGoalPos _goalArrivalCheck ))

(defmethod hmcl_msgs::TransitionCondition
  (:init
   (&key
    ((:missionStart __missionStart) nil)
    ((:approachToStartPos __approachToStartPos) nil)
    ((:startArrivalCheck __startArrivalCheck) nil)
    ((:startArrivalSuccess __startArrivalSuccess) nil)
    ((:frontCar __frontCar) nil)
    ((:stationaryFrontCar __stationaryFrontCar) nil)
    ((:approachToCrosswalk __approachToCrosswalk) nil)
    ((:crosswalkPass __crosswalkPass) nil)
    ((:pedestrianOnCrosswalk __pedestrianOnCrosswalk) nil)
    ((:leftTurn __leftTurn) nil)
    ((:rightTurn __rightTurn) nil)
    ((:turn __turn) nil)
    ((:trafficLightStop __trafficLightStop) nil)
    ((:stopCheck __stopCheck) nil)
    ((:luggageDrop __luggageDrop) nil)
    ((:brokenFrontCar __brokenFrontCar) nil)
    ((:laneChangeDone __laneChangeDone) nil)
    ((:essentialLaneChange __essentialLaneChange) nil)
    ((:speedBumpSign __speedBumpSign) nil)
    ((:speedBumpPass __speedBumpPass) nil)
    ((:approachToGoalPos __approachToGoalPos) nil)
    ((:goalArrivalCheck __goalArrivalCheck) nil)
    )
   (send-super :init)
   (setq _missionStart __missionStart)
   (setq _approachToStartPos __approachToStartPos)
   (setq _startArrivalCheck __startArrivalCheck)
   (setq _startArrivalSuccess __startArrivalSuccess)
   (setq _frontCar __frontCar)
   (setq _stationaryFrontCar __stationaryFrontCar)
   (setq _approachToCrosswalk __approachToCrosswalk)
   (setq _crosswalkPass __crosswalkPass)
   (setq _pedestrianOnCrosswalk __pedestrianOnCrosswalk)
   (setq _leftTurn __leftTurn)
   (setq _rightTurn __rightTurn)
   (setq _turn __turn)
   (setq _trafficLightStop __trafficLightStop)
   (setq _stopCheck __stopCheck)
   (setq _luggageDrop __luggageDrop)
   (setq _brokenFrontCar __brokenFrontCar)
   (setq _laneChangeDone __laneChangeDone)
   (setq _essentialLaneChange __essentialLaneChange)
   (setq _speedBumpSign __speedBumpSign)
   (setq _speedBumpPass __speedBumpPass)
   (setq _approachToGoalPos __approachToGoalPos)
   (setq _goalArrivalCheck __goalArrivalCheck)
   self)
  (:missionStart
   (&optional __missionStart)
   (if __missionStart (setq _missionStart __missionStart)) _missionStart)
  (:approachToStartPos
   (&optional __approachToStartPos)
   (if __approachToStartPos (setq _approachToStartPos __approachToStartPos)) _approachToStartPos)
  (:startArrivalCheck
   (&optional __startArrivalCheck)
   (if __startArrivalCheck (setq _startArrivalCheck __startArrivalCheck)) _startArrivalCheck)
  (:startArrivalSuccess
   (&optional __startArrivalSuccess)
   (if __startArrivalSuccess (setq _startArrivalSuccess __startArrivalSuccess)) _startArrivalSuccess)
  (:frontCar
   (&optional __frontCar)
   (if __frontCar (setq _frontCar __frontCar)) _frontCar)
  (:stationaryFrontCar
   (&optional __stationaryFrontCar)
   (if __stationaryFrontCar (setq _stationaryFrontCar __stationaryFrontCar)) _stationaryFrontCar)
  (:approachToCrosswalk
   (&optional __approachToCrosswalk)
   (if __approachToCrosswalk (setq _approachToCrosswalk __approachToCrosswalk)) _approachToCrosswalk)
  (:crosswalkPass
   (&optional __crosswalkPass)
   (if __crosswalkPass (setq _crosswalkPass __crosswalkPass)) _crosswalkPass)
  (:pedestrianOnCrosswalk
   (&optional __pedestrianOnCrosswalk)
   (if __pedestrianOnCrosswalk (setq _pedestrianOnCrosswalk __pedestrianOnCrosswalk)) _pedestrianOnCrosswalk)
  (:leftTurn
   (&optional __leftTurn)
   (if __leftTurn (setq _leftTurn __leftTurn)) _leftTurn)
  (:rightTurn
   (&optional __rightTurn)
   (if __rightTurn (setq _rightTurn __rightTurn)) _rightTurn)
  (:turn
   (&optional __turn)
   (if __turn (setq _turn __turn)) _turn)
  (:trafficLightStop
   (&optional __trafficLightStop)
   (if __trafficLightStop (setq _trafficLightStop __trafficLightStop)) _trafficLightStop)
  (:stopCheck
   (&optional __stopCheck)
   (if __stopCheck (setq _stopCheck __stopCheck)) _stopCheck)
  (:luggageDrop
   (&optional __luggageDrop)
   (if __luggageDrop (setq _luggageDrop __luggageDrop)) _luggageDrop)
  (:brokenFrontCar
   (&optional __brokenFrontCar)
   (if __brokenFrontCar (setq _brokenFrontCar __brokenFrontCar)) _brokenFrontCar)
  (:laneChangeDone
   (&optional __laneChangeDone)
   (if __laneChangeDone (setq _laneChangeDone __laneChangeDone)) _laneChangeDone)
  (:essentialLaneChange
   (&optional __essentialLaneChange)
   (if __essentialLaneChange (setq _essentialLaneChange __essentialLaneChange)) _essentialLaneChange)
  (:speedBumpSign
   (&optional __speedBumpSign)
   (if __speedBumpSign (setq _speedBumpSign __speedBumpSign)) _speedBumpSign)
  (:speedBumpPass
   (&optional __speedBumpPass)
   (if __speedBumpPass (setq _speedBumpPass __speedBumpPass)) _speedBumpPass)
  (:approachToGoalPos
   (&optional __approachToGoalPos)
   (if __approachToGoalPos (setq _approachToGoalPos __approachToGoalPos)) _approachToGoalPos)
  (:goalArrivalCheck
   (&optional __goalArrivalCheck)
   (if __goalArrivalCheck (setq _goalArrivalCheck __goalArrivalCheck)) _goalArrivalCheck)
  (:serialization-length
   ()
   (+
    ;; bool _missionStart
    1
    ;; bool _approachToStartPos
    1
    ;; bool _startArrivalCheck
    1
    ;; bool _startArrivalSuccess
    1
    ;; bool _frontCar
    1
    ;; bool _stationaryFrontCar
    1
    ;; bool _approachToCrosswalk
    1
    ;; bool _crosswalkPass
    1
    ;; bool _pedestrianOnCrosswalk
    1
    ;; bool _leftTurn
    1
    ;; bool _rightTurn
    1
    ;; bool _turn
    1
    ;; bool _trafficLightStop
    1
    ;; bool _stopCheck
    1
    ;; bool _luggageDrop
    1
    ;; bool _brokenFrontCar
    1
    ;; bool _laneChangeDone
    1
    ;; bool _essentialLaneChange
    1
    ;; bool _speedBumpSign
    1
    ;; bool _speedBumpPass
    1
    ;; bool _approachToGoalPos
    1
    ;; bool _goalArrivalCheck
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _missionStart
       (if _missionStart (write-byte -1 s) (write-byte 0 s))
     ;; bool _approachToStartPos
       (if _approachToStartPos (write-byte -1 s) (write-byte 0 s))
     ;; bool _startArrivalCheck
       (if _startArrivalCheck (write-byte -1 s) (write-byte 0 s))
     ;; bool _startArrivalSuccess
       (if _startArrivalSuccess (write-byte -1 s) (write-byte 0 s))
     ;; bool _frontCar
       (if _frontCar (write-byte -1 s) (write-byte 0 s))
     ;; bool _stationaryFrontCar
       (if _stationaryFrontCar (write-byte -1 s) (write-byte 0 s))
     ;; bool _approachToCrosswalk
       (if _approachToCrosswalk (write-byte -1 s) (write-byte 0 s))
     ;; bool _crosswalkPass
       (if _crosswalkPass (write-byte -1 s) (write-byte 0 s))
     ;; bool _pedestrianOnCrosswalk
       (if _pedestrianOnCrosswalk (write-byte -1 s) (write-byte 0 s))
     ;; bool _leftTurn
       (if _leftTurn (write-byte -1 s) (write-byte 0 s))
     ;; bool _rightTurn
       (if _rightTurn (write-byte -1 s) (write-byte 0 s))
     ;; bool _turn
       (if _turn (write-byte -1 s) (write-byte 0 s))
     ;; bool _trafficLightStop
       (if _trafficLightStop (write-byte -1 s) (write-byte 0 s))
     ;; bool _stopCheck
       (if _stopCheck (write-byte -1 s) (write-byte 0 s))
     ;; bool _luggageDrop
       (if _luggageDrop (write-byte -1 s) (write-byte 0 s))
     ;; bool _brokenFrontCar
       (if _brokenFrontCar (write-byte -1 s) (write-byte 0 s))
     ;; bool _laneChangeDone
       (if _laneChangeDone (write-byte -1 s) (write-byte 0 s))
     ;; bool _essentialLaneChange
       (if _essentialLaneChange (write-byte -1 s) (write-byte 0 s))
     ;; bool _speedBumpSign
       (if _speedBumpSign (write-byte -1 s) (write-byte 0 s))
     ;; bool _speedBumpPass
       (if _speedBumpPass (write-byte -1 s) (write-byte 0 s))
     ;; bool _approachToGoalPos
       (if _approachToGoalPos (write-byte -1 s) (write-byte 0 s))
     ;; bool _goalArrivalCheck
       (if _goalArrivalCheck (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _missionStart
     (setq _missionStart (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _approachToStartPos
     (setq _approachToStartPos (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _startArrivalCheck
     (setq _startArrivalCheck (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _startArrivalSuccess
     (setq _startArrivalSuccess (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _frontCar
     (setq _frontCar (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _stationaryFrontCar
     (setq _stationaryFrontCar (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _approachToCrosswalk
     (setq _approachToCrosswalk (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _crosswalkPass
     (setq _crosswalkPass (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _pedestrianOnCrosswalk
     (setq _pedestrianOnCrosswalk (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _leftTurn
     (setq _leftTurn (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _rightTurn
     (setq _rightTurn (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _turn
     (setq _turn (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _trafficLightStop
     (setq _trafficLightStop (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _stopCheck
     (setq _stopCheck (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _luggageDrop
     (setq _luggageDrop (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _brokenFrontCar
     (setq _brokenFrontCar (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _laneChangeDone
     (setq _laneChangeDone (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _essentialLaneChange
     (setq _essentialLaneChange (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _speedBumpSign
     (setq _speedBumpSign (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _speedBumpPass
     (setq _speedBumpPass (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _approachToGoalPos
     (setq _approachToGoalPos (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _goalArrivalCheck
     (setq _goalArrivalCheck (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get hmcl_msgs::TransitionCondition :md5sum-) "cca5c3113432d6f9d44e33df94544699")
(setf (get hmcl_msgs::TransitionCondition :datatype-) "hmcl_msgs/TransitionCondition")
(setf (get hmcl_msgs::TransitionCondition :definition-)
      "bool missionStart
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



(provide :hmcl_msgs/TransitionCondition "cca5c3113432d6f9d44e33df94544699")


