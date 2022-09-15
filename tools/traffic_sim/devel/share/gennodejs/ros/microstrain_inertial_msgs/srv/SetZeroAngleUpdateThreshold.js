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

class SetZeroAngleUpdateThresholdRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.enable = null;
      this.threshold = null;
    }
    else {
      if (initObj.hasOwnProperty('enable')) {
        this.enable = initObj.enable
      }
      else {
        this.enable = 0;
      }
      if (initObj.hasOwnProperty('threshold')) {
        this.threshold = initObj.threshold
      }
      else {
        this.threshold = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetZeroAngleUpdateThresholdRequest
    // Serialize message field [enable]
    bufferOffset = _serializer.int8(obj.enable, buffer, bufferOffset);
    // Serialize message field [threshold]
    bufferOffset = _serializer.float32(obj.threshold, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetZeroAngleUpdateThresholdRequest
    let len;
    let data = new SetZeroAngleUpdateThresholdRequest(null);
    // Deserialize message field [enable]
    data.enable = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [threshold]
    data.threshold = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetZeroAngleUpdateThresholdRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6eacdc5ab3df5e6c977f6645124a7f61';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 enable
    float32 threshold
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetZeroAngleUpdateThresholdRequest(null);
    if (msg.enable !== undefined) {
      resolved.enable = msg.enable;
    }
    else {
      resolved.enable = 0
    }

    if (msg.threshold !== undefined) {
      resolved.threshold = msg.threshold;
    }
    else {
      resolved.threshold = 0.0
    }

    return resolved;
    }
};

class SetZeroAngleUpdateThresholdResponse {
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
    // Serializes a message object of type SetZeroAngleUpdateThresholdResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetZeroAngleUpdateThresholdResponse
    let len;
    let data = new SetZeroAngleUpdateThresholdResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetZeroAngleUpdateThresholdResponse';
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
    const resolved = new SetZeroAngleUpdateThresholdResponse(null);
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
  Request: SetZeroAngleUpdateThresholdRequest,
  Response: SetZeroAngleUpdateThresholdResponse,
  md5sum() { return 'ea1115ed39d8a581530c7c251ee443e6'; },
  datatype() { return 'microstrain_inertial_msgs/SetZeroAngleUpdateThreshold'; }
};
