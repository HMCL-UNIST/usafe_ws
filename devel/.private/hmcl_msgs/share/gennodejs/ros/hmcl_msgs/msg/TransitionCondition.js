// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class TransitionCondition {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.missionStart = null;
      this.approachToStartPos = null;
      this.startArrivalCheck = null;
      this.startArrivalSuccess = null;
      this.frontCar = null;
      this.stationaryFrontCar = null;
      this.approachToCrosswalk = null;
      this.crosswalkPass = null;
      this.pedestrianOnCrosswalk = null;
      this.leftTurn = null;
      this.rightTurn = null;
      this.turn = null;
      this.trafficLightStop = null;
      this.stopCheck = null;
      this.luggageDrop = null;
      this.brokenFrontCar = null;
      this.laneChangeDone = null;
      this.essentialLaneChange = null;
      this.speedBumpSign = null;
      this.speedBumpPass = null;
      this.approachToGoalPos = null;
      this.goalArrivalCheck = null;
    }
    else {
      if (initObj.hasOwnProperty('missionStart')) {
        this.missionStart = initObj.missionStart
      }
      else {
        this.missionStart = false;
      }
      if (initObj.hasOwnProperty('approachToStartPos')) {
        this.approachToStartPos = initObj.approachToStartPos
      }
      else {
        this.approachToStartPos = false;
      }
      if (initObj.hasOwnProperty('startArrivalCheck')) {
        this.startArrivalCheck = initObj.startArrivalCheck
      }
      else {
        this.startArrivalCheck = false;
      }
      if (initObj.hasOwnProperty('startArrivalSuccess')) {
        this.startArrivalSuccess = initObj.startArrivalSuccess
      }
      else {
        this.startArrivalSuccess = false;
      }
      if (initObj.hasOwnProperty('frontCar')) {
        this.frontCar = initObj.frontCar
      }
      else {
        this.frontCar = false;
      }
      if (initObj.hasOwnProperty('stationaryFrontCar')) {
        this.stationaryFrontCar = initObj.stationaryFrontCar
      }
      else {
        this.stationaryFrontCar = false;
      }
      if (initObj.hasOwnProperty('approachToCrosswalk')) {
        this.approachToCrosswalk = initObj.approachToCrosswalk
      }
      else {
        this.approachToCrosswalk = false;
      }
      if (initObj.hasOwnProperty('crosswalkPass')) {
        this.crosswalkPass = initObj.crosswalkPass
      }
      else {
        this.crosswalkPass = false;
      }
      if (initObj.hasOwnProperty('pedestrianOnCrosswalk')) {
        this.pedestrianOnCrosswalk = initObj.pedestrianOnCrosswalk
      }
      else {
        this.pedestrianOnCrosswalk = false;
      }
      if (initObj.hasOwnProperty('leftTurn')) {
        this.leftTurn = initObj.leftTurn
      }
      else {
        this.leftTurn = false;
      }
      if (initObj.hasOwnProperty('rightTurn')) {
        this.rightTurn = initObj.rightTurn
      }
      else {
        this.rightTurn = false;
      }
      if (initObj.hasOwnProperty('turn')) {
        this.turn = initObj.turn
      }
      else {
        this.turn = false;
      }
      if (initObj.hasOwnProperty('trafficLightStop')) {
        this.trafficLightStop = initObj.trafficLightStop
      }
      else {
        this.trafficLightStop = false;
      }
      if (initObj.hasOwnProperty('stopCheck')) {
        this.stopCheck = initObj.stopCheck
      }
      else {
        this.stopCheck = false;
      }
      if (initObj.hasOwnProperty('luggageDrop')) {
        this.luggageDrop = initObj.luggageDrop
      }
      else {
        this.luggageDrop = false;
      }
      if (initObj.hasOwnProperty('brokenFrontCar')) {
        this.brokenFrontCar = initObj.brokenFrontCar
      }
      else {
        this.brokenFrontCar = false;
      }
      if (initObj.hasOwnProperty('laneChangeDone')) {
        this.laneChangeDone = initObj.laneChangeDone
      }
      else {
        this.laneChangeDone = false;
      }
      if (initObj.hasOwnProperty('essentialLaneChange')) {
        this.essentialLaneChange = initObj.essentialLaneChange
      }
      else {
        this.essentialLaneChange = false;
      }
      if (initObj.hasOwnProperty('speedBumpSign')) {
        this.speedBumpSign = initObj.speedBumpSign
      }
      else {
        this.speedBumpSign = false;
      }
      if (initObj.hasOwnProperty('speedBumpPass')) {
        this.speedBumpPass = initObj.speedBumpPass
      }
      else {
        this.speedBumpPass = false;
      }
      if (initObj.hasOwnProperty('approachToGoalPos')) {
        this.approachToGoalPos = initObj.approachToGoalPos
      }
      else {
        this.approachToGoalPos = false;
      }
      if (initObj.hasOwnProperty('goalArrivalCheck')) {
        this.goalArrivalCheck = initObj.goalArrivalCheck
      }
      else {
        this.goalArrivalCheck = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TransitionCondition
    // Serialize message field [missionStart]
    bufferOffset = _serializer.bool(obj.missionStart, buffer, bufferOffset);
    // Serialize message field [approachToStartPos]
    bufferOffset = _serializer.bool(obj.approachToStartPos, buffer, bufferOffset);
    // Serialize message field [startArrivalCheck]
    bufferOffset = _serializer.bool(obj.startArrivalCheck, buffer, bufferOffset);
    // Serialize message field [startArrivalSuccess]
    bufferOffset = _serializer.bool(obj.startArrivalSuccess, buffer, bufferOffset);
    // Serialize message field [frontCar]
    bufferOffset = _serializer.bool(obj.frontCar, buffer, bufferOffset);
    // Serialize message field [stationaryFrontCar]
    bufferOffset = _serializer.bool(obj.stationaryFrontCar, buffer, bufferOffset);
    // Serialize message field [approachToCrosswalk]
    bufferOffset = _serializer.bool(obj.approachToCrosswalk, buffer, bufferOffset);
    // Serialize message field [crosswalkPass]
    bufferOffset = _serializer.bool(obj.crosswalkPass, buffer, bufferOffset);
    // Serialize message field [pedestrianOnCrosswalk]
    bufferOffset = _serializer.bool(obj.pedestrianOnCrosswalk, buffer, bufferOffset);
    // Serialize message field [leftTurn]
    bufferOffset = _serializer.bool(obj.leftTurn, buffer, bufferOffset);
    // Serialize message field [rightTurn]
    bufferOffset = _serializer.bool(obj.rightTurn, buffer, bufferOffset);
    // Serialize message field [turn]
    bufferOffset = _serializer.bool(obj.turn, buffer, bufferOffset);
    // Serialize message field [trafficLightStop]
    bufferOffset = _serializer.bool(obj.trafficLightStop, buffer, bufferOffset);
    // Serialize message field [stopCheck]
    bufferOffset = _serializer.bool(obj.stopCheck, buffer, bufferOffset);
    // Serialize message field [luggageDrop]
    bufferOffset = _serializer.bool(obj.luggageDrop, buffer, bufferOffset);
    // Serialize message field [brokenFrontCar]
    bufferOffset = _serializer.bool(obj.brokenFrontCar, buffer, bufferOffset);
    // Serialize message field [laneChangeDone]
    bufferOffset = _serializer.bool(obj.laneChangeDone, buffer, bufferOffset);
    // Serialize message field [essentialLaneChange]
    bufferOffset = _serializer.bool(obj.essentialLaneChange, buffer, bufferOffset);
    // Serialize message field [speedBumpSign]
    bufferOffset = _serializer.bool(obj.speedBumpSign, buffer, bufferOffset);
    // Serialize message field [speedBumpPass]
    bufferOffset = _serializer.bool(obj.speedBumpPass, buffer, bufferOffset);
    // Serialize message field [approachToGoalPos]
    bufferOffset = _serializer.bool(obj.approachToGoalPos, buffer, bufferOffset);
    // Serialize message field [goalArrivalCheck]
    bufferOffset = _serializer.bool(obj.goalArrivalCheck, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TransitionCondition
    let len;
    let data = new TransitionCondition(null);
    // Deserialize message field [missionStart]
    data.missionStart = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [approachToStartPos]
    data.approachToStartPos = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [startArrivalCheck]
    data.startArrivalCheck = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [startArrivalSuccess]
    data.startArrivalSuccess = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [frontCar]
    data.frontCar = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [stationaryFrontCar]
    data.stationaryFrontCar = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [approachToCrosswalk]
    data.approachToCrosswalk = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [crosswalkPass]
    data.crosswalkPass = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [pedestrianOnCrosswalk]
    data.pedestrianOnCrosswalk = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [leftTurn]
    data.leftTurn = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [rightTurn]
    data.rightTurn = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [turn]
    data.turn = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [trafficLightStop]
    data.trafficLightStop = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [stopCheck]
    data.stopCheck = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [luggageDrop]
    data.luggageDrop = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [brokenFrontCar]
    data.brokenFrontCar = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [laneChangeDone]
    data.laneChangeDone = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [essentialLaneChange]
    data.essentialLaneChange = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [speedBumpSign]
    data.speedBumpSign = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [speedBumpPass]
    data.speedBumpPass = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [approachToGoalPos]
    data.approachToGoalPos = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [goalArrivalCheck]
    data.goalArrivalCheck = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 22;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/TransitionCondition';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cca5c3113432d6f9d44e33df94544699';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TransitionCondition(null);
    if (msg.missionStart !== undefined) {
      resolved.missionStart = msg.missionStart;
    }
    else {
      resolved.missionStart = false
    }

    if (msg.approachToStartPos !== undefined) {
      resolved.approachToStartPos = msg.approachToStartPos;
    }
    else {
      resolved.approachToStartPos = false
    }

    if (msg.startArrivalCheck !== undefined) {
      resolved.startArrivalCheck = msg.startArrivalCheck;
    }
    else {
      resolved.startArrivalCheck = false
    }

    if (msg.startArrivalSuccess !== undefined) {
      resolved.startArrivalSuccess = msg.startArrivalSuccess;
    }
    else {
      resolved.startArrivalSuccess = false
    }

    if (msg.frontCar !== undefined) {
      resolved.frontCar = msg.frontCar;
    }
    else {
      resolved.frontCar = false
    }

    if (msg.stationaryFrontCar !== undefined) {
      resolved.stationaryFrontCar = msg.stationaryFrontCar;
    }
    else {
      resolved.stationaryFrontCar = false
    }

    if (msg.approachToCrosswalk !== undefined) {
      resolved.approachToCrosswalk = msg.approachToCrosswalk;
    }
    else {
      resolved.approachToCrosswalk = false
    }

    if (msg.crosswalkPass !== undefined) {
      resolved.crosswalkPass = msg.crosswalkPass;
    }
    else {
      resolved.crosswalkPass = false
    }

    if (msg.pedestrianOnCrosswalk !== undefined) {
      resolved.pedestrianOnCrosswalk = msg.pedestrianOnCrosswalk;
    }
    else {
      resolved.pedestrianOnCrosswalk = false
    }

    if (msg.leftTurn !== undefined) {
      resolved.leftTurn = msg.leftTurn;
    }
    else {
      resolved.leftTurn = false
    }

    if (msg.rightTurn !== undefined) {
      resolved.rightTurn = msg.rightTurn;
    }
    else {
      resolved.rightTurn = false
    }

    if (msg.turn !== undefined) {
      resolved.turn = msg.turn;
    }
    else {
      resolved.turn = false
    }

    if (msg.trafficLightStop !== undefined) {
      resolved.trafficLightStop = msg.trafficLightStop;
    }
    else {
      resolved.trafficLightStop = false
    }

    if (msg.stopCheck !== undefined) {
      resolved.stopCheck = msg.stopCheck;
    }
    else {
      resolved.stopCheck = false
    }

    if (msg.luggageDrop !== undefined) {
      resolved.luggageDrop = msg.luggageDrop;
    }
    else {
      resolved.luggageDrop = false
    }

    if (msg.brokenFrontCar !== undefined) {
      resolved.brokenFrontCar = msg.brokenFrontCar;
    }
    else {
      resolved.brokenFrontCar = false
    }

    if (msg.laneChangeDone !== undefined) {
      resolved.laneChangeDone = msg.laneChangeDone;
    }
    else {
      resolved.laneChangeDone = false
    }

    if (msg.essentialLaneChange !== undefined) {
      resolved.essentialLaneChange = msg.essentialLaneChange;
    }
    else {
      resolved.essentialLaneChange = false
    }

    if (msg.speedBumpSign !== undefined) {
      resolved.speedBumpSign = msg.speedBumpSign;
    }
    else {
      resolved.speedBumpSign = false
    }

    if (msg.speedBumpPass !== undefined) {
      resolved.speedBumpPass = msg.speedBumpPass;
    }
    else {
      resolved.speedBumpPass = false
    }

    if (msg.approachToGoalPos !== undefined) {
      resolved.approachToGoalPos = msg.approachToGoalPos;
    }
    else {
      resolved.approachToGoalPos = false
    }

    if (msg.goalArrivalCheck !== undefined) {
      resolved.goalArrivalCheck = msg.goalArrivalCheck;
    }
    else {
      resolved.goalArrivalCheck = false
    }

    return resolved;
    }
};

module.exports = TransitionCondition;
