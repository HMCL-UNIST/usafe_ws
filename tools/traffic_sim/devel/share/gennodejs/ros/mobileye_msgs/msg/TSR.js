// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class TSR {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vision_only_sign_type = null;
      this.supplementary_sign_type = null;
      this.sign_position_x = null;
      this.sign_position_y = null;
      this.sign_position_z = null;
      this.filter_type = null;
    }
    else {
      if (initObj.hasOwnProperty('vision_only_sign_type')) {
        this.vision_only_sign_type = initObj.vision_only_sign_type
      }
      else {
        this.vision_only_sign_type = 0;
      }
      if (initObj.hasOwnProperty('supplementary_sign_type')) {
        this.supplementary_sign_type = initObj.supplementary_sign_type
      }
      else {
        this.supplementary_sign_type = 0;
      }
      if (initObj.hasOwnProperty('sign_position_x')) {
        this.sign_position_x = initObj.sign_position_x
      }
      else {
        this.sign_position_x = 0.0;
      }
      if (initObj.hasOwnProperty('sign_position_y')) {
        this.sign_position_y = initObj.sign_position_y
      }
      else {
        this.sign_position_y = 0.0;
      }
      if (initObj.hasOwnProperty('sign_position_z')) {
        this.sign_position_z = initObj.sign_position_z
      }
      else {
        this.sign_position_z = 0.0;
      }
      if (initObj.hasOwnProperty('filter_type')) {
        this.filter_type = initObj.filter_type
      }
      else {
        this.filter_type = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TSR
    // Serialize message field [vision_only_sign_type]
    bufferOffset = _serializer.uint8(obj.vision_only_sign_type, buffer, bufferOffset);
    // Serialize message field [supplementary_sign_type]
    bufferOffset = _serializer.uint8(obj.supplementary_sign_type, buffer, bufferOffset);
    // Serialize message field [sign_position_x]
    bufferOffset = _serializer.float32(obj.sign_position_x, buffer, bufferOffset);
    // Serialize message field [sign_position_y]
    bufferOffset = _serializer.float32(obj.sign_position_y, buffer, bufferOffset);
    // Serialize message field [sign_position_z]
    bufferOffset = _serializer.float32(obj.sign_position_z, buffer, bufferOffset);
    // Serialize message field [filter_type]
    bufferOffset = _serializer.uint8(obj.filter_type, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TSR
    let len;
    let data = new TSR(null);
    // Deserialize message field [vision_only_sign_type]
    data.vision_only_sign_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [supplementary_sign_type]
    data.supplementary_sign_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sign_position_x]
    data.sign_position_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [sign_position_y]
    data.sign_position_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [sign_position_z]
    data.sign_position_z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [filter_type]
    data.filter_type = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 15;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/TSR';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3b21293c7f6ed978e4a364de1d436a9c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 vision_only_sign_type
    uint8 supplementary_sign_type
    float32 sign_position_x
    float32 sign_position_y
    float32 sign_position_z
    uint8 filter_type
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TSR(null);
    if (msg.vision_only_sign_type !== undefined) {
      resolved.vision_only_sign_type = msg.vision_only_sign_type;
    }
    else {
      resolved.vision_only_sign_type = 0
    }

    if (msg.supplementary_sign_type !== undefined) {
      resolved.supplementary_sign_type = msg.supplementary_sign_type;
    }
    else {
      resolved.supplementary_sign_type = 0
    }

    if (msg.sign_position_x !== undefined) {
      resolved.sign_position_x = msg.sign_position_x;
    }
    else {
      resolved.sign_position_x = 0.0
    }

    if (msg.sign_position_y !== undefined) {
      resolved.sign_position_y = msg.sign_position_y;
    }
    else {
      resolved.sign_position_y = 0.0
    }

    if (msg.sign_position_z !== undefined) {
      resolved.sign_position_z = msg.sign_position_z;
    }
    else {
      resolved.sign_position_z = 0.0
    }

    if (msg.filter_type !== undefined) {
      resolved.filter_type = msg.filter_type;
    }
    else {
      resolved.filter_type = 0
    }

    return resolved;
    }
};

module.exports = TSR;
