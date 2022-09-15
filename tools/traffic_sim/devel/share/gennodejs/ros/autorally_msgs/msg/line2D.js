// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let point2D = require('./point2D.js');

//-----------------------------------------------------------

class line2D {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.start = null;
      this.end = null;
    }
    else {
      if (initObj.hasOwnProperty('start')) {
        this.start = initObj.start
      }
      else {
        this.start = new point2D();
      }
      if (initObj.hasOwnProperty('end')) {
        this.end = initObj.end
      }
      else {
        this.end = new point2D();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type line2D
    // Serialize message field [start]
    bufferOffset = point2D.serialize(obj.start, buffer, bufferOffset);
    // Serialize message field [end]
    bufferOffset = point2D.serialize(obj.end, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type line2D
    let len;
    let data = new line2D(null);
    // Deserialize message field [start]
    data.start = point2D.deserialize(buffer, bufferOffset);
    // Deserialize message field [end]
    data.end = point2D.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/line2D';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7a338da65a86a1f736887760a0feaccd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    point2D start
    point2D end
    
    ================================================================================
    MSG: autorally_msgs/point2D
    uint16 x
    uint16 y
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new line2D(null);
    if (msg.start !== undefined) {
      resolved.start = point2D.Resolve(msg.start)
    }
    else {
      resolved.start = new point2D()
    }

    if (msg.end !== undefined) {
      resolved.end = point2D.Resolve(msg.end)
    }
    else {
      resolved.end = new point2D()
    }

    return resolved;
    }
};

module.exports = line2D;
