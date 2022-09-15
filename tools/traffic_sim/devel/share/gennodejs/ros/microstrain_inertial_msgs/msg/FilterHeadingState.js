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

class FilterHeadingState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.heading_rad = null;
      this.heading_uncertainty = null;
      this.source = null;
      this.status_flags = null;
    }
    else {
      if (initObj.hasOwnProperty('heading_rad')) {
        this.heading_rad = initObj.heading_rad
      }
      else {
        this.heading_rad = 0.0;
      }
      if (initObj.hasOwnProperty('heading_uncertainty')) {
        this.heading_uncertainty = initObj.heading_uncertainty
      }
      else {
        this.heading_uncertainty = 0.0;
      }
      if (initObj.hasOwnProperty('source')) {
        this.source = initObj.source
      }
      else {
        this.source = 0;
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
    // Serializes a message object of type FilterHeadingState
    // Serialize message field [heading_rad]
    bufferOffset = _serializer.float32(obj.heading_rad, buffer, bufferOffset);
    // Serialize message field [heading_uncertainty]
    bufferOffset = _serializer.float32(obj.heading_uncertainty, buffer, bufferOffset);
    // Serialize message field [source]
    bufferOffset = _serializer.uint16(obj.source, buffer, bufferOffset);
    // Serialize message field [status_flags]
    bufferOffset = _serializer.uint16(obj.status_flags, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FilterHeadingState
    let len;
    let data = new FilterHeadingState(null);
    // Deserialize message field [heading_rad]
    data.heading_rad = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading_uncertainty]
    data.heading_uncertainty = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [source]
    data.source = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [status_flags]
    data.status_flags = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/FilterHeadingState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ca75e8c156e8551037af1d0f6d896ef2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 heading_rad
    
    float32 heading_uncertainty
    
    uint16 source
    
    uint16 status_flags
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FilterHeadingState(null);
    if (msg.heading_rad !== undefined) {
      resolved.heading_rad = msg.heading_rad;
    }
    else {
      resolved.heading_rad = 0.0
    }

    if (msg.heading_uncertainty !== undefined) {
      resolved.heading_uncertainty = msg.heading_uncertainty;
    }
    else {
      resolved.heading_uncertainty = 0.0
    }

    if (msg.source !== undefined) {
      resolved.source = msg.source;
    }
    else {
      resolved.source = 0
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

module.exports = FilterHeadingState;
