; Auto-generated. Do not edit!


(cl:in-package hmcl_msgs-msg)


;//! \htmlinclude TransitionCondition.msg.html

(cl:defclass <TransitionCondition> (roslisp-msg-protocol:ros-message)
  ((missionStart
    :reader missionStart
    :initarg :missionStart
    :type cl:boolean
    :initform cl:nil)
   (approachToStartPos
    :reader approachToStartPos
    :initarg :approachToStartPos
    :type cl:boolean
    :initform cl:nil)
   (startArrivalCheck
    :reader startArrivalCheck
    :initarg :startArrivalCheck
    :type cl:boolean
    :initform cl:nil)
   (startArrivalSuccess
    :reader startArrivalSuccess
    :initarg :startArrivalSuccess
    :type cl:boolean
    :initform cl:nil)
   (frontCar
    :reader frontCar
    :initarg :frontCar
    :type cl:boolean
    :initform cl:nil)
   (stationaryFrontCar
    :reader stationaryFrontCar
    :initarg :stationaryFrontCar
    :type cl:boolean
    :initform cl:nil)
   (approachToCrosswalk
    :reader approachToCrosswalk
    :initarg :approachToCrosswalk
    :type cl:boolean
    :initform cl:nil)
   (crosswalkPass
    :reader crosswalkPass
    :initarg :crosswalkPass
    :type cl:boolean
    :initform cl:nil)
   (pedestrianOnCrosswalk
    :reader pedestrianOnCrosswalk
    :initarg :pedestrianOnCrosswalk
    :type cl:boolean
    :initform cl:nil)
   (leftTurn
    :reader leftTurn
    :initarg :leftTurn
    :type cl:boolean
    :initform cl:nil)
   (rightTurn
    :reader rightTurn
    :initarg :rightTurn
    :type cl:boolean
    :initform cl:nil)
   (turn
    :reader turn
    :initarg :turn
    :type cl:boolean
    :initform cl:nil)
   (trafficLightStop
    :reader trafficLightStop
    :initarg :trafficLightStop
    :type cl:boolean
    :initform cl:nil)
   (stopCheck
    :reader stopCheck
    :initarg :stopCheck
    :type cl:boolean
    :initform cl:nil)
   (luggageDrop
    :reader luggageDrop
    :initarg :luggageDrop
    :type cl:boolean
    :initform cl:nil)
   (brokenFrontCar
    :reader brokenFrontCar
    :initarg :brokenFrontCar
    :type cl:boolean
    :initform cl:nil)
   (laneChangeDone
    :reader laneChangeDone
    :initarg :laneChangeDone
    :type cl:boolean
    :initform cl:nil)
   (essentialLaneChange
    :reader essentialLaneChange
    :initarg :essentialLaneChange
    :type cl:boolean
    :initform cl:nil)
   (speedBumpSign
    :reader speedBumpSign
    :initarg :speedBumpSign
    :type cl:boolean
    :initform cl:nil)
   (speedBumpPass
    :reader speedBumpPass
    :initarg :speedBumpPass
    :type cl:boolean
    :initform cl:nil)
   (approachToGoalPos
    :reader approachToGoalPos
    :initarg :approachToGoalPos
    :type cl:boolean
    :initform cl:nil)
   (goalArrivalCheck
    :reader goalArrivalCheck
    :initarg :goalArrivalCheck
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass TransitionCondition (<TransitionCondition>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TransitionCondition>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TransitionCondition)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hmcl_msgs-msg:<TransitionCondition> is deprecated: use hmcl_msgs-msg:TransitionCondition instead.")))

(cl:ensure-generic-function 'missionStart-val :lambda-list '(m))
(cl:defmethod missionStart-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:missionStart-val is deprecated.  Use hmcl_msgs-msg:missionStart instead.")
  (missionStart m))

(cl:ensure-generic-function 'approachToStartPos-val :lambda-list '(m))
(cl:defmethod approachToStartPos-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:approachToStartPos-val is deprecated.  Use hmcl_msgs-msg:approachToStartPos instead.")
  (approachToStartPos m))

(cl:ensure-generic-function 'startArrivalCheck-val :lambda-list '(m))
(cl:defmethod startArrivalCheck-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:startArrivalCheck-val is deprecated.  Use hmcl_msgs-msg:startArrivalCheck instead.")
  (startArrivalCheck m))

(cl:ensure-generic-function 'startArrivalSuccess-val :lambda-list '(m))
(cl:defmethod startArrivalSuccess-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:startArrivalSuccess-val is deprecated.  Use hmcl_msgs-msg:startArrivalSuccess instead.")
  (startArrivalSuccess m))

(cl:ensure-generic-function 'frontCar-val :lambda-list '(m))
(cl:defmethod frontCar-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:frontCar-val is deprecated.  Use hmcl_msgs-msg:frontCar instead.")
  (frontCar m))

(cl:ensure-generic-function 'stationaryFrontCar-val :lambda-list '(m))
(cl:defmethod stationaryFrontCar-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:stationaryFrontCar-val is deprecated.  Use hmcl_msgs-msg:stationaryFrontCar instead.")
  (stationaryFrontCar m))

(cl:ensure-generic-function 'approachToCrosswalk-val :lambda-list '(m))
(cl:defmethod approachToCrosswalk-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:approachToCrosswalk-val is deprecated.  Use hmcl_msgs-msg:approachToCrosswalk instead.")
  (approachToCrosswalk m))

(cl:ensure-generic-function 'crosswalkPass-val :lambda-list '(m))
(cl:defmethod crosswalkPass-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:crosswalkPass-val is deprecated.  Use hmcl_msgs-msg:crosswalkPass instead.")
  (crosswalkPass m))

(cl:ensure-generic-function 'pedestrianOnCrosswalk-val :lambda-list '(m))
(cl:defmethod pedestrianOnCrosswalk-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:pedestrianOnCrosswalk-val is deprecated.  Use hmcl_msgs-msg:pedestrianOnCrosswalk instead.")
  (pedestrianOnCrosswalk m))

(cl:ensure-generic-function 'leftTurn-val :lambda-list '(m))
(cl:defmethod leftTurn-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:leftTurn-val is deprecated.  Use hmcl_msgs-msg:leftTurn instead.")
  (leftTurn m))

(cl:ensure-generic-function 'rightTurn-val :lambda-list '(m))
(cl:defmethod rightTurn-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:rightTurn-val is deprecated.  Use hmcl_msgs-msg:rightTurn instead.")
  (rightTurn m))

(cl:ensure-generic-function 'turn-val :lambda-list '(m))
(cl:defmethod turn-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:turn-val is deprecated.  Use hmcl_msgs-msg:turn instead.")
  (turn m))

(cl:ensure-generic-function 'trafficLightStop-val :lambda-list '(m))
(cl:defmethod trafficLightStop-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:trafficLightStop-val is deprecated.  Use hmcl_msgs-msg:trafficLightStop instead.")
  (trafficLightStop m))

(cl:ensure-generic-function 'stopCheck-val :lambda-list '(m))
(cl:defmethod stopCheck-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:stopCheck-val is deprecated.  Use hmcl_msgs-msg:stopCheck instead.")
  (stopCheck m))

(cl:ensure-generic-function 'luggageDrop-val :lambda-list '(m))
(cl:defmethod luggageDrop-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:luggageDrop-val is deprecated.  Use hmcl_msgs-msg:luggageDrop instead.")
  (luggageDrop m))

(cl:ensure-generic-function 'brokenFrontCar-val :lambda-list '(m))
(cl:defmethod brokenFrontCar-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:brokenFrontCar-val is deprecated.  Use hmcl_msgs-msg:brokenFrontCar instead.")
  (brokenFrontCar m))

(cl:ensure-generic-function 'laneChangeDone-val :lambda-list '(m))
(cl:defmethod laneChangeDone-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:laneChangeDone-val is deprecated.  Use hmcl_msgs-msg:laneChangeDone instead.")
  (laneChangeDone m))

(cl:ensure-generic-function 'essentialLaneChange-val :lambda-list '(m))
(cl:defmethod essentialLaneChange-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:essentialLaneChange-val is deprecated.  Use hmcl_msgs-msg:essentialLaneChange instead.")
  (essentialLaneChange m))

(cl:ensure-generic-function 'speedBumpSign-val :lambda-list '(m))
(cl:defmethod speedBumpSign-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:speedBumpSign-val is deprecated.  Use hmcl_msgs-msg:speedBumpSign instead.")
  (speedBumpSign m))

(cl:ensure-generic-function 'speedBumpPass-val :lambda-list '(m))
(cl:defmethod speedBumpPass-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:speedBumpPass-val is deprecated.  Use hmcl_msgs-msg:speedBumpPass instead.")
  (speedBumpPass m))

(cl:ensure-generic-function 'approachToGoalPos-val :lambda-list '(m))
(cl:defmethod approachToGoalPos-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:approachToGoalPos-val is deprecated.  Use hmcl_msgs-msg:approachToGoalPos instead.")
  (approachToGoalPos m))

(cl:ensure-generic-function 'goalArrivalCheck-val :lambda-list '(m))
(cl:defmethod goalArrivalCheck-val ((m <TransitionCondition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hmcl_msgs-msg:goalArrivalCheck-val is deprecated.  Use hmcl_msgs-msg:goalArrivalCheck instead.")
  (goalArrivalCheck m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TransitionCondition>) ostream)
  "Serializes a message object of type '<TransitionCondition>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'missionStart) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'approachToStartPos) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'startArrivalCheck) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'startArrivalSuccess) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'frontCar) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stationaryFrontCar) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'approachToCrosswalk) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'crosswalkPass) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pedestrianOnCrosswalk) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'leftTurn) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'rightTurn) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'turn) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'trafficLightStop) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stopCheck) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'luggageDrop) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'brokenFrontCar) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'laneChangeDone) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'essentialLaneChange) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'speedBumpSign) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'speedBumpPass) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'approachToGoalPos) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'goalArrivalCheck) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TransitionCondition>) istream)
  "Deserializes a message object of type '<TransitionCondition>"
    (cl:setf (cl:slot-value msg 'missionStart) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'approachToStartPos) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'startArrivalCheck) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'startArrivalSuccess) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'frontCar) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'stationaryFrontCar) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'approachToCrosswalk) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'crosswalkPass) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'pedestrianOnCrosswalk) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'leftTurn) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'rightTurn) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'turn) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'trafficLightStop) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'stopCheck) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'luggageDrop) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'brokenFrontCar) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'laneChangeDone) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'essentialLaneChange) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'speedBumpSign) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'speedBumpPass) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'approachToGoalPos) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'goalArrivalCheck) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TransitionCondition>)))
  "Returns string type for a message object of type '<TransitionCondition>"
  "hmcl_msgs/TransitionCondition")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TransitionCondition)))
  "Returns string type for a message object of type 'TransitionCondition"
  "hmcl_msgs/TransitionCondition")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TransitionCondition>)))
  "Returns md5sum for a message object of type '<TransitionCondition>"
  "cca5c3113432d6f9d44e33df94544699")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TransitionCondition)))
  "Returns md5sum for a message object of type 'TransitionCondition"
  "cca5c3113432d6f9d44e33df94544699")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TransitionCondition>)))
  "Returns full string definition for message of type '<TransitionCondition>"
  (cl:format cl:nil "bool missionStart~%bool approachToStartPos~%bool startArrivalCheck~%bool startArrivalSuccess~%bool frontCar~%bool stationaryFrontCar~%bool approachToCrosswalk~%bool crosswalkPass~%bool pedestrianOnCrosswalk~%bool leftTurn~%bool rightTurn~%bool turn~%bool trafficLightStop~%bool stopCheck~%bool luggageDrop~%bool brokenFrontCar~%bool laneChangeDone~%bool essentialLaneChange~%bool speedBumpSign~%bool speedBumpPass~%bool approachToGoalPos~%bool goalArrivalCheck~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TransitionCondition)))
  "Returns full string definition for message of type 'TransitionCondition"
  (cl:format cl:nil "bool missionStart~%bool approachToStartPos~%bool startArrivalCheck~%bool startArrivalSuccess~%bool frontCar~%bool stationaryFrontCar~%bool approachToCrosswalk~%bool crosswalkPass~%bool pedestrianOnCrosswalk~%bool leftTurn~%bool rightTurn~%bool turn~%bool trafficLightStop~%bool stopCheck~%bool luggageDrop~%bool brokenFrontCar~%bool laneChangeDone~%bool essentialLaneChange~%bool speedBumpSign~%bool speedBumpPass~%bool approachToGoalPos~%bool goalArrivalCheck~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TransitionCondition>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TransitionCondition>))
  "Converts a ROS message object to a list"
  (cl:list 'TransitionCondition
    (cl:cons ':missionStart (missionStart msg))
    (cl:cons ':approachToStartPos (approachToStartPos msg))
    (cl:cons ':startArrivalCheck (startArrivalCheck msg))
    (cl:cons ':startArrivalSuccess (startArrivalSuccess msg))
    (cl:cons ':frontCar (frontCar msg))
    (cl:cons ':stationaryFrontCar (stationaryFrontCar msg))
    (cl:cons ':approachToCrosswalk (approachToCrosswalk msg))
    (cl:cons ':crosswalkPass (crosswalkPass msg))
    (cl:cons ':pedestrianOnCrosswalk (pedestrianOnCrosswalk msg))
    (cl:cons ':leftTurn (leftTurn msg))
    (cl:cons ':rightTurn (rightTurn msg))
    (cl:cons ':turn (turn msg))
    (cl:cons ':trafficLightStop (trafficLightStop msg))
    (cl:cons ':stopCheck (stopCheck msg))
    (cl:cons ':luggageDrop (luggageDrop msg))
    (cl:cons ':brokenFrontCar (brokenFrontCar msg))
    (cl:cons ':laneChangeDone (laneChangeDone msg))
    (cl:cons ':essentialLaneChange (essentialLaneChange msg))
    (cl:cons ':speedBumpSign (speedBumpSign msg))
    (cl:cons ':speedBumpPass (speedBumpPass msg))
    (cl:cons ':approachToGoalPos (approachToGoalPos msg))
    (cl:cons ':goalArrivalCheck (goalArrivalCheck msg))
))
