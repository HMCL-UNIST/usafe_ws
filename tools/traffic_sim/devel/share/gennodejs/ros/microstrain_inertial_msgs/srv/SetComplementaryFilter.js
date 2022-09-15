// Auto-generated. Do not edit!

// (in-package microstrain_inertial_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetComplementaryFilterRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.north_comp_enable = null;
      this.up_comp_enable = null;
      this.north_comp_time_const = null;
      this.up_comp_time_const = null;
    }
    else {
      if (initObj.hasOwnProperty('north_comp_enable')) {
        this.north_comp_enable = initObj.north_comp_enable
      }
      else {
        this.north_comp_enable = 0;
      }
      if (initObj.hasOwnProperty('up_comp_enable')) {
        this.up_comp_enable = initObj.up_comp_enable
      }
      else {
        this.up_comp_enable = 0;
      }
      if (initObj.hasOwnProperty('north_comp_time_const')) {
        this.north_comp_time_const = initObj.north_comp_time_const
      }
      else {
        this.north_comp_time_const = 0.0;
      }
      if (initObj.hasOwnProperty('up_comp_time_const')) {
        this.up_comp_time_const = initObj.up_comp_time_const
      }
      else {
        this.up_comp_time_const = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetComplementaryFilterRequest
    // Serialize message field [north_comp_enable]
    bufferOffset = _serializer.int8(obj.north_comp_enable, buffer, bufferOffset);
    // Serialize message field [up_comp_enable]
    bufferOffset = _serializer.int8(obj.up_comp_enable, buffer, bufferOffset);
    // Serialize message field [north_comp_time_const]
    bufferOffset = _serializer.float32(obj.north_comp_time_const, buffer, bufferOffset);
    // Serialize message field [up_comp_time_const]
    bufferOffset = _serializer.float32(obj.up_comp_time_const, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetComplementaryFilterRequest
    let len;
    let data = new SetComplementaryFilterRequest(null);
    // Deserialize message field [north_comp_enable]
    data.north_comp_enable = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [up_comp_enable]
    data.up_comp_enable = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [north_comp_time_const]
    data.north_comp_time_const = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [up_comp_time_const]
    data.up_comp_time_const = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 10;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetComplementaryFilterRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '45ff6c0b3e0fce49632971cc1d368393';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 north_comp_enable
    int8 up_comp_enable
    float32 north_comp_time_const
    float32 up_comp_time_const
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetComplementaryFilterRequest(null);
    if (msg.north_comp_enable !== undefined) {
      resolved.north_comp_enable = msg.north_comp_enable;
    }
    else {
      resolved.north_comp_enable = 0
    }

    if (msg.up_comp_enable !== undefined) {
      resolved.up_comp_enable = msg.up_comp_enable;
    }
    else {
      resolved.up_comp_enable = 0
    }

    if (msg.north_comp_time_const !== undefined) {
      resolved.north_comp_time_const = msg.north_comp_time_const;
    }
    else {
      resolved.north_comp_time_const = 0.0
    }

    if (msg.up_comp_time_const !== undefined) {
      resolved.up_comp_time_const = msg.up_comp_time_const;
    }
    else {
      resolved.up_comp_time_const = 0.0
    }

    return resolved;
    }
};

class SetComplementaryFilterResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetComplementaryFilterResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetComplementaryFilterResponse
    let len;
    let data = new SetComplementaryFilterResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetComplementaryFilterResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '358e233cde0c8a8bcfea4ce193f8fc15';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool success
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetComplementaryFilterResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: SetComplementaryFilterRequest,
  Response: SetComplementaryFilterResponse,
  md5sum() { return 'f2496add5126d026ef6c94d30c11db4c'; },
  datatype() { return 'microstrain_inertial_msgs/SetComplementaryFilter'; }
};
