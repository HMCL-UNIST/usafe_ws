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

class FilterStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.filter_state = null;
      this.dynamics_mode = null;
      this.status_flags = null;
    }
    else {
      if (initObj.hasOwnProperty('filter_state')) {
        this.filter_state = initObj.filter_state
      }
      else {
        this.filter_state = 0;
      }
      if (initObj.hasOwnProperty('dynamics_mode')) {
        this.dynamics_mode = initObj.dynamics_mode
      }
      else {
        this.dynamics_mode = 0;
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
    // Serializes a message object of type FilterStatus
    // Serialize message field [filter_state]
    bufferOffset = _serializer.uint16(obj.filter_state, buffer, bufferOffset);
    // Serialize message field [dynamics_mode]
    bufferOffset = _serializer.uint16(obj.dynamics_mode, buffer, bufferOffset);
    // Serialize message field [status_flags]
    bufferOffset = _serializer.uint16(obj.status_flags, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FilterStatus
    let len;
    let data = new FilterStatus(null);
    // Deserialize message field [filter_state]
    data.filter_state = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [dynamics_mode]
    data.dynamics_mode = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [status_flags]
    data.status_flags = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/FilterStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '44b6cdd5e336c9a880e785b76ea6be97';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 filter_state
    
    uint16 dynamics_mode
    
    uint16 status_flags
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FilterStatus(null);
    if (msg.filter_state !== undefined) {
      resolved.filter_state = msg.filter_state;
    }
    else {
      resolved.filter_state = 0
    }

    if (msg.dynamics_mode !== undefined) {
      resolved.dynamics_mode = msg.dynamics_mode;
    }
    else {
      resolved.dynamics_mode = 0
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

module.exports = FilterStatus;
