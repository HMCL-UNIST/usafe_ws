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

class SetMagDipAdaptiveValsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.enable = null;
      this.low_pass_cutoff = null;
      this.min_1sigma = null;
      this.high_limit = null;
      this.high_limit_1sigma = null;
    }
    else {
      if (initObj.hasOwnProperty('enable')) {
        this.enable = initObj.enable
      }
      else {
        this.enable = 0.0;
      }
      if (initObj.hasOwnProperty('low_pass_cutoff')) {
        this.low_pass_cutoff = initObj.low_pass_cutoff
      }
      else {
        this.low_pass_cutoff = 0.0;
      }
      if (initObj.hasOwnProperty('min_1sigma')) {
        this.min_1sigma = initObj.min_1sigma
      }
      else {
        this.min_1sigma = 0.0;
      }
      if (initObj.hasOwnProperty('high_limit')) {
        this.high_limit = initObj.high_limit
      }
      else {
        this.high_limit = 0.0;
      }
      if (initObj.hasOwnProperty('high_limit_1sigma')) {
        this.high_limit_1sigma = initObj.high_limit_1sigma
      }
      else {
        this.high_limit_1sigma = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetMagDipAdaptiveValsRequest
    // Serialize message field [enable]
    bufferOffset = _serializer.float32(obj.enable, buffer, bufferOffset);
    // Serialize message field [low_pass_cutoff]
    bufferOffset = _serializer.float32(obj.low_pass_cutoff, buffer, bufferOffset);
    // Serialize message field [min_1sigma]
    bufferOffset = _serializer.float32(obj.min_1sigma, buffer, bufferOffset);
    // Serialize message field [high_limit]
    bufferOffset = _serializer.float32(obj.high_limit, buffer, bufferOffset);
    // Serialize message field [high_limit_1sigma]
    bufferOffset = _serializer.float32(obj.high_limit_1sigma, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetMagDipAdaptiveValsRequest
    let len;
    let data = new SetMagDipAdaptiveValsRequest(null);
    // Deserialize message field [enable]
    data.enable = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [low_pass_cutoff]
    data.low_pass_cutoff = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [min_1sigma]
    data.min_1sigma = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [high_limit]
    data.high_limit = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [high_limit_1sigma]
    data.high_limit_1sigma = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetMagDipAdaptiveValsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '04ce6c1f346dae412b474a781c1703c9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 enable
    float32 low_pass_cutoff
    float32 min_1sigma
    float32 high_limit
    float32 high_limit_1sigma
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetMagDipAdaptiveValsRequest(null);
    if (msg.enable !== undefined) {
      resolved.enable = msg.enable;
    }
    else {
      resolved.enable = 0.0
    }

    if (msg.low_pass_cutoff !== undefined) {
      resolved.low_pass_cutoff = msg.low_pass_cutoff;
    }
    else {
      resolved.low_pass_cutoff = 0.0
    }

    if (msg.min_1sigma !== undefined) {
      resolved.min_1sigma = msg.min_1sigma;
    }
    else {
      resolved.min_1sigma = 0.0
    }

    if (msg.high_limit !== undefined) {
      resolved.high_limit = msg.high_limit;
    }
    else {
      resolved.high_limit = 0.0
    }

    if (msg.high_limit_1sigma !== undefined) {
      resolved.high_limit_1sigma = msg.high_limit_1sigma;
    }
    else {
      resolved.high_limit_1sigma = 0.0
    }

    return resolved;
    }
};

class SetMagDipAdaptiveValsResponse {
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
    // Serializes a message object of type SetMagDipAdaptiveValsResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetMagDipAdaptiveValsResponse
    let len;
    let data = new SetMagDipAdaptiveValsResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetMagDipAdaptiveValsResponse';
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
    const resolved = new SetMagDipAdaptiveValsResponse(null);
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
  Request: SetMagDipAdaptiveValsRequest,
  Response: SetMagDipAdaptiveValsResponse,
  md5sum() { return 'c71450f947e543c107e6e7b633ac2f16'; },
  datatype() { return 'microstrain_inertial_msgs/SetMagDipAdaptiveVals'; }
};
