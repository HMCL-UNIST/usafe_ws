// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class lapStats {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.lap_number = null;
      this.lap_time = null;
      this.max_speed = null;
      this.max_slip = null;
    }
    else {
      if (initObj.hasOwnProperty('lap_number')) {
        this.lap_number = initObj.lap_number
      }
      else {
        this.lap_number = 0;
      }
      if (initObj.hasOwnProperty('lap_time')) {
        this.lap_time = initObj.lap_time
      }
      else {
        this.lap_time = 0.0;
      }
      if (initObj.hasOwnProperty('max_speed')) {
        this.max_speed = initObj.max_speed
      }
      else {
        this.max_speed = 0.0;
      }
      if (initObj.hasOwnProperty('max_slip')) {
        this.max_slip = initObj.max_slip
      }
      else {
        this.max_slip = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type lapStats
    // Serialize message field [lap_number]
    bufferOffset = _serializer.int64(obj.lap_number, buffer, bufferOffset);
    // Serialize message field [lap_time]
    bufferOffset = _serializer.float64(obj.lap_time, buffer, bufferOffset);
    // Serialize message field [max_speed]
    bufferOffset = _serializer.float64(obj.max_speed, buffer, bufferOffset);
    // Serialize message field [max_slip]
    bufferOffset = _serializer.float64(obj.max_slip, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type lapStats
    let len;
    let data = new lapStats(null);
    // Deserialize message field [lap_number]
    data.lap_number = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [lap_time]
    data.lap_time = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_speed]
    data.max_speed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_slip]
    data.max_slip = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/lapStats';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd0c1580b11cbef99426a15c0443b2e19';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 lap_number
    float64 lap_time
    float64 max_speed
    float64 max_slip
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new lapStats(null);
    if (msg.lap_number !== undefined) {
      resolved.lap_number = msg.lap_number;
    }
    else {
      resolved.lap_number = 0
    }

    if (msg.lap_time !== undefined) {
      resolved.lap_time = msg.lap_time;
    }
    else {
      resolved.lap_time = 0.0
    }

    if (msg.max_speed !== undefined) {
      resolved.max_speed = msg.max_speed;
    }
    else {
      resolved.max_speed = 0.0
    }

    if (msg.max_slip !== undefined) {
      resolved.max_slip = msg.max_slip;
    }
    else {
      resolved.max_slip = 0.0
    }

    return resolved;
    }
};

module.exports = lapStats;
