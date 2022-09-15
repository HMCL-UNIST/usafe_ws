// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class chassisState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.throttleRelayEnabled = null;
      this.autonomousEnabled = null;
      this.runstopMotionEnabled = null;
      this.steeringCommander = null;
      this.steering = null;
      this.throttleCommander = null;
      this.throttle = null;
      this.frontBrakeCommander = null;
      this.frontBrake = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('throttleRelayEnabled')) {
        this.throttleRelayEnabled = initObj.throttleRelayEnabled
      }
      else {
        this.throttleRelayEnabled = false;
      }
      if (initObj.hasOwnProperty('autonomousEnabled')) {
        this.autonomousEnabled = initObj.autonomousEnabled
      }
      else {
        this.autonomousEnabled = false;
      }
      if (initObj.hasOwnProperty('runstopMotionEnabled')) {
        this.runstopMotionEnabled = initObj.runstopMotionEnabled
      }
      else {
        this.runstopMotionEnabled = false;
      }
      if (initObj.hasOwnProperty('steeringCommander')) {
        this.steeringCommander = initObj.steeringCommander
      }
      else {
        this.steeringCommander = '';
      }
      if (initObj.hasOwnProperty('steering')) {
        this.steering = initObj.steering
      }
      else {
        this.steering = 0.0;
      }
      if (initObj.hasOwnProperty('throttleCommander')) {
        this.throttleCommander = initObj.throttleCommander
      }
      else {
        this.throttleCommander = '';
      }
      if (initObj.hasOwnProperty('throttle')) {
        this.throttle = initObj.throttle
      }
      else {
        this.throttle = 0.0;
      }
      if (initObj.hasOwnProperty('frontBrakeCommander')) {
        this.frontBrakeCommander = initObj.frontBrakeCommander
      }
      else {
        this.frontBrakeCommander = '';
      }
      if (initObj.hasOwnProperty('frontBrake')) {
        this.frontBrake = initObj.frontBrake
      }
      else {
        this.frontBrake = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type chassisState
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [throttleRelayEnabled]
    bufferOffset = _serializer.bool(obj.throttleRelayEnabled, buffer, bufferOffset);
    // Serialize message field [autonomousEnabled]
    bufferOffset = _serializer.bool(obj.autonomousEnabled, buffer, bufferOffset);
    // Serialize message field [runstopMotionEnabled]
    bufferOffset = _serializer.bool(obj.runstopMotionEnabled, buffer, bufferOffset);
    // Serialize message field [steeringCommander]
    bufferOffset = _serializer.string(obj.steeringCommander, buffer, bufferOffset);
    // Serialize message field [steering]
    bufferOffset = _serializer.float64(obj.steering, buffer, bufferOffset);
    // Serialize message field [throttleCommander]
    bufferOffset = _serializer.string(obj.throttleCommander, buffer, bufferOffset);
    // Serialize message field [throttle]
    bufferOffset = _serializer.float64(obj.throttle, buffer, bufferOffset);
    // Serialize message field [frontBrakeCommander]
    bufferOffset = _serializer.string(obj.frontBrakeCommander, buffer, bufferOffset);
    // Serialize message field [frontBrake]
    bufferOffset = _serializer.float64(obj.frontBrake, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type chassisState
    let len;
    let data = new chassisState(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [throttleRelayEnabled]
    data.throttleRelayEnabled = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [autonomousEnabled]
    data.autonomousEnabled = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [runstopMotionEnabled]
    data.runstopMotionEnabled = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [steeringCommander]
    data.steeringCommander = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [steering]
    data.steering = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [throttleCommander]
    data.throttleCommander = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [throttle]
    data.throttle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [frontBrakeCommander]
    data.frontBrakeCommander = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [frontBrake]
    data.frontBrake = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += object.steeringCommander.length;
    length += object.throttleCommander.length;
    length += object.frontBrakeCommander.length;
    return length + 39;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/chassisState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cbd23a33a5ec266cc70ab1630ddbccef';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new chassisState(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.throttleRelayEnabled !== undefined) {
      resolved.throttleRelayEnabled = msg.throttleRelayEnabled;
    }
    else {
      resolved.throttleRelayEnabled = false
    }

    if (msg.autonomousEnabled !== undefined) {
      resolved.autonomousEnabled = msg.autonomousEnabled;
    }
    else {
      resolved.autonomousEnabled = false
    }

    if (msg.runstopMotionEnabled !== undefined) {
      resolved.runstopMotionEnabled = msg.runstopMotionEnabled;
    }
    else {
      resolved.runstopMotionEnabled = false
    }

    if (msg.steeringCommander !== undefined) {
      resolved.steeringCommander = msg.steeringCommander;
    }
    else {
      resolved.steeringCommander = ''
    }

    if (msg.steering !== undefined) {
      resolved.steering = msg.steering;
    }
    else {
      resolved.steering = 0.0
    }

    if (msg.throttleCommander !== undefined) {
      resolved.throttleCommander = msg.throttleCommander;
    }
    else {
      resolved.throttleCommander = ''
    }

    if (msg.throttle !== undefined) {
      resolved.throttle = msg.throttle;
    }
    else {
      resolved.throttle = 0.0
    }

    if (msg.frontBrakeCommander !== undefined) {
      resolved.frontBrakeCommander = msg.frontBrakeCommander;
    }
    else {
      resolved.frontBrakeCommander = ''
    }

    if (msg.frontBrake !== undefined) {
      resolved.frontBrake = msg.frontBrake;
    }
    else {
      resolved.frontBrake = 0.0
    }

    return resolved;
    }
};

module.exports = chassisState;
