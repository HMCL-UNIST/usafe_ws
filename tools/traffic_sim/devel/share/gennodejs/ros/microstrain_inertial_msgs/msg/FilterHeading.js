// Auto-generated. Do not edit!

// (in-package microstrain_inertial_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class FilterHeading {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.heading_deg = null;
      this.heading_rad = null;
      this.status_flags = null;
    }
    else {
      if (initObj.hasOwnProperty('heading_deg')) {
        this.heading_deg = initObj.heading_deg
      }
      else {
        this.heading_deg = 0.0;
      }
      if (initObj.hasOwnProperty('heading_rad')) {
        this.heading_rad = initObj.heading_rad
      }
      else {
        this.heading_rad = 0.0;
      }
      if (initObj.hasOwnProperty('status_flags')) {
        this.status_flags = initObj.status_flags
      }
      else {
        this.status_flags = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FilterHeading
    // Serialize message field [heading_deg]
    bufferOffset = _serializer.float32(obj.heading_deg, buffer, bufferOffset);
    // Serialize message field [heading_rad]
    bufferOffset = _serializer.float32(obj.heading_rad, buffer, bufferOffset);
    // Serialize message field [status_flags]
    bufferOffset = _serializer.uint16(obj.status_flags, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FilterHeading
    let len;
    let data = new FilterHeading(null);
    // Deserialize message field [heading_deg]
    data.heading_deg = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading_rad]
    data.heading_rad = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [status_flags]
    data.status_flags = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 10;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/FilterHeading';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b90b446055a9cca548055d2a70764344';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 heading_deg
    
    float32 heading_rad
    
    uint16 status_flags
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FilterHeading(null);
    if (msg.heading_deg !== undefined) {
      resolved.heading_deg = msg.heading_deg;
    }
    else {
      resolved.heading_deg = 0.0
    }

    if (msg.heading_rad !== undefined) {
      resolved.heading_rad = msg.heading_rad;
    }
    else {
      resolved.heading_rad = 0.0
    }

    if (msg.status_flags !== undefined) {
      resolved.status_flags = msg.status_flags;
    }
    else {
      resolved.status_flags = 0
    }

    return resolved;
    }
};

module.exports = FilterHeading;
