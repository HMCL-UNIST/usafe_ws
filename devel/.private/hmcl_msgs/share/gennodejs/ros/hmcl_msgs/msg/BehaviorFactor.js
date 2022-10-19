// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let TransitionCondition = require('./TransitionCondition.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class BehaviorFactor {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.transition_condition = null;
      this.front_id = null;
      this.stop_line_stop = null;
      this.front_dist = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('transition_condition')) {
        this.transition_condition = initObj.transition_condition
      }
      else {
        this.transition_condition = new TransitionCondition();
      }
      if (initObj.hasOwnProperty('front_id')) {
        this.front_id = initObj.front_id
      }
      else {
        this.front_id = 0;
      }
      if (initObj.hasOwnProperty('stop_line_stop')) {
        this.stop_line_stop = initObj.stop_line_stop
      }
      else {
        this.stop_line_stop = false;
      }
      if (initObj.hasOwnProperty('front_dist')) {
        this.front_dist = initObj.front_dist
      }
      else {
        this.front_dist = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BehaviorFactor
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [transition_condition]
    bufferOffset = TransitionCondition.serialize(obj.transition_condition, buffer, bufferOffset);
    // Serialize message field [front_id]
    bufferOffset = _serializer.int16(obj.front_id, buffer, bufferOffset);
    // Serialize message field [stop_line_stop]
    bufferOffset = _serializer.bool(obj.stop_line_stop, buffer, bufferOffset);
    // Serialize message field [front_dist]
    bufferOffset = _serializer.float32(obj.front_dist, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BehaviorFactor
    let len;
    let data = new BehaviorFactor(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [transition_condition]
    data.transition_condition = TransitionCondition.deserialize(buffer, bufferOffset);
    // Deserialize message field [front_id]
    data.front_id = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [stop_line_stop]
    data.stop_line_stop = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [front_dist]
    data.front_dist = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 29;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/BehaviorFactor';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '007955b848a31590079e09deb110b6e6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BehaviorFactor(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.transition_condition !== undefined) {
      resolved.transition_condition = TransitionCondition.Resolve(msg.transition_condition)
    }
    else {
      resolved.transition_condition = new TransitionCondition()
    }

    if (msg.front_id !== undefined) {
      resolved.front_id = msg.front_id;
    }
    else {
      resolved.front_id = 0
    }

    if (msg.stop_line_stop !== undefined) {
      resolved.stop_line_stop = msg.stop_line_stop;
    }
    else {
      resolved.stop_line_stop = false
    }

    if (msg.front_dist !== undefined) {
      resolved.front_dist = msg.front_dist;
    }
    else {
      resolved.front_dist = 0.0
    }

    return resolved;
    }
};

module.exports = BehaviorFactor;
