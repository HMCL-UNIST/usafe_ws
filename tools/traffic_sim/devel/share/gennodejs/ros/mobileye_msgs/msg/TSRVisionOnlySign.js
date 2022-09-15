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

class TSRVisionOnlySign {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vision_only_sign_type_display_1 = null;
      this.vision_only_sign_type_display_2 = null;
      this.vision_only_sign_type_display_3 = null;
      this.vision_only_sign_type_display_4 = null;
      this.supplementary_sign_type_display_1 = null;
      this.supplementary_sign_type_display_2 = null;
      this.supplementary_sign_type_display_3 = null;
      this.supplementary_sign_type_display_4 = null;
    }
    else {
      if (initObj.hasOwnProperty('vision_only_sign_type_display_1')) {
        this.vision_only_sign_type_display_1 = initObj.vision_only_sign_type_display_1
      }
      else {
        this.vision_only_sign_type_display_1 = 0;
      }
      if (initObj.hasOwnProperty('vision_only_sign_type_display_2')) {
        this.vision_only_sign_type_display_2 = initObj.vision_only_sign_type_display_2
      }
      else {
        this.vision_only_sign_type_display_2 = 0;
      }
      if (initObj.hasOwnProperty('vision_only_sign_type_display_3')) {
        this.vision_only_sign_type_display_3 = initObj.vision_only_sign_type_display_3
      }
      else {
        this.vision_only_sign_type_display_3 = 0;
      }
      if (initObj.hasOwnProperty('vision_only_sign_type_display_4')) {
        this.vision_only_sign_type_display_4 = initObj.vision_only_sign_type_display_4
      }
      else {
        this.vision_only_sign_type_display_4 = 0;
      }
      if (initObj.hasOwnProperty('supplementary_sign_type_display_1')) {
        this.supplementary_sign_type_display_1 = initObj.supplementary_sign_type_display_1
      }
      else {
        this.supplementary_sign_type_display_1 = 0;
      }
      if (initObj.hasOwnProperty('supplementary_sign_type_display_2')) {
        this.supplementary_sign_type_display_2 = initObj.supplementary_sign_type_display_2
      }
      else {
        this.supplementary_sign_type_display_2 = 0;
      }
      if (initObj.hasOwnProperty('supplementary_sign_type_display_3')) {
        this.supplementary_sign_type_display_3 = initObj.supplementary_sign_type_display_3
      }
      else {
        this.supplementary_sign_type_display_3 = 0;
      }
      if (initObj.hasOwnProperty('supplementary_sign_type_display_4')) {
        this.supplementary_sign_type_display_4 = initObj.supplementary_sign_type_display_4
      }
      else {
        this.supplementary_sign_type_display_4 = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TSRVisionOnlySign
    // Serialize message field [vision_only_sign_type_display_1]
    bufferOffset = _serializer.uint8(obj.vision_only_sign_type_display_1, buffer, bufferOffset);
    // Serialize message field [vision_only_sign_type_display_2]
    bufferOffset = _serializer.uint8(obj.vision_only_sign_type_display_2, buffer, bufferOffset);
    // Serialize message field [vision_only_sign_type_display_3]
    bufferOffset = _serializer.uint8(obj.vision_only_sign_type_display_3, buffer, bufferOffset);
    // Serialize message field [vision_only_sign_type_display_4]
    bufferOffset = _serializer.uint8(obj.vision_only_sign_type_display_4, buffer, bufferOffset);
    // Serialize message field [supplementary_sign_type_display_1]
    bufferOffset = _serializer.uint8(obj.supplementary_sign_type_display_1, buffer, bufferOffset);
    // Serialize message field [supplementary_sign_type_display_2]
    bufferOffset = _serializer.uint8(obj.supplementary_sign_type_display_2, buffer, bufferOffset);
    // Serialize message field [supplementary_sign_type_display_3]
    bufferOffset = _serializer.uint8(obj.supplementary_sign_type_display_3, buffer, bufferOffset);
    // Serialize message field [supplementary_sign_type_display_4]
    bufferOffset = _serializer.uint8(obj.supplementary_sign_type_display_4, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TSRVisionOnlySign
    let len;
    let data = new TSRVisionOnlySign(null);
    // Deserialize message field [vision_only_sign_type_display_1]
    data.vision_only_sign_type_display_1 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [vision_only_sign_type_display_2]
    data.vision_only_sign_type_display_2 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [vision_only_sign_type_display_3]
    data.vision_only_sign_type_display_3 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [vision_only_sign_type_display_4]
    data.vision_only_sign_type_display_4 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [supplementary_sign_type_display_1]
    data.supplementary_sign_type_display_1 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [supplementary_sign_type_display_2]
    data.supplementary_sign_type_display_2 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [supplementary_sign_type_display_3]
    data.supplementary_sign_type_display_3 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [supplementary_sign_type_display_4]
    data.supplementary_sign_type_display_4 = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/TSRVisionOnlySign';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '81ad54807425b67a5be6ad808e97e8ee';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 vision_only_sign_type_display_1
    uint8 vision_only_sign_type_display_2
    uint8 vision_only_sign_type_display_3
    uint8 vision_only_sign_type_display_4
    
    uint8 supplementary_sign_type_display_1
    uint8 supplementary_sign_type_display_2
    uint8 supplementary_sign_type_display_3
    uint8 supplementary_sign_type_display_4
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TSRVisionOnlySign(null);
    if (msg.vision_only_sign_type_display_1 !== undefined) {
      resolved.vision_only_sign_type_display_1 = msg.vision_only_sign_type_display_1;
    }
    else {
      resolved.vision_only_sign_type_display_1 = 0
    }

    if (msg.vision_only_sign_type_display_2 !== undefined) {
      resolved.vision_only_sign_type_display_2 = msg.vision_only_sign_type_display_2;
    }
    else {
      resolved.vision_only_sign_type_display_2 = 0
    }

    if (msg.vision_only_sign_type_display_3 !== undefined) {
      resolved.vision_only_sign_type_display_3 = msg.vision_only_sign_type_display_3;
    }
    else {
      resolved.vision_only_sign_type_display_3 = 0
    }

    if (msg.vision_only_sign_type_display_4 !== undefined) {
      resolved.vision_only_sign_type_display_4 = msg.vision_only_sign_type_display_4;
    }
    else {
      resolved.vision_only_sign_type_display_4 = 0
    }

    if (msg.supplementary_sign_type_display_1 !== undefined) {
      resolved.supplementary_sign_type_display_1 = msg.supplementary_sign_type_display_1;
    }
    else {
      resolved.supplementary_sign_type_display_1 = 0
    }

    if (msg.supplementary_sign_type_display_2 !== undefined) {
      resolved.supplementary_sign_type_display_2 = msg.supplementary_sign_type_display_2;
    }
    else {
      resolved.supplementary_sign_type_display_2 = 0
    }

    if (msg.supplementary_sign_type_display_3 !== undefined) {
      resolved.supplementary_sign_type_display_3 = msg.supplementary_sign_type_display_3;
    }
    else {
      resolved.supplementary_sign_type_display_3 = 0
    }

    if (msg.supplementary_sign_type_display_4 !== undefined) {
      resolved.supplementary_sign_type_display_4 = msg.supplementary_sign_type_display_4;
    }
    else {
      resolved.supplementary_sign_type_display_4 = 0
    }

    return resolved;
    }
};

module.exports = TSRVisionOnlySign;
