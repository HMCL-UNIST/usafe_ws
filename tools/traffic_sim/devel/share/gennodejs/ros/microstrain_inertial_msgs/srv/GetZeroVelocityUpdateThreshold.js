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

class GetZeroVelocityUpdateThresholdRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetZeroVelocityUpdateThresholdRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetZeroVelocityUpdateThresholdRequest
    let len;
    let data = new GetZeroVelocityUpdateThresholdRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/GetZeroVelocityUpdateThresholdRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetZeroVelocityUpdateThresholdRequest(null);
    return resolved;
    }
};

class GetZeroVelocityUpdateThresholdResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.enable = null;
      this.threshold = null;
      this.success = null;
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
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetZeroVelocityUpdateThresholdResponse
    // Serialize message field [enable]
    bufferOffset = _serializer.int8(obj.enable, buffer, bufferOffset);
    // Serialize message field [threshold]
    bufferOffset = _serializer.float32(obj.threshold, buffer, bufferOffset);
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetZeroVelocityUpdateThresholdResponse
    let len;
    let data = new GetZeroVelocityUpdateThresholdResponse(null);
    // Deserialize message field [enable]
    data.enable = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [threshold]
    data.threshold = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 6;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/GetZeroVelocityUpdateThresholdResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1d55bd0c555abfd31bce740efa684526';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 enable
    float32 threshold
    bool success
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetZeroVelocityUpdateThresholdResponse(null);
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
  Request: GetZeroVelocityUpdateThresholdRequest,
  Response: GetZeroVelocityUpdateThresholdResponse,
  md5sum() { return '1d55bd0c555abfd31bce740efa684526'; },
  datatype() { return 'microstrain_inertial_msgs/GetZeroVelocityUpdateThreshold'; }
};
