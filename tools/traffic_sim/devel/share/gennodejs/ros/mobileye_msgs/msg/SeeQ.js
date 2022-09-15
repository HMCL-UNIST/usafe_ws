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

class SeeQ {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.serial_number = null;
      this.production_date = null;
      this.brain_version_major = null;
      this.brain_version_minor = null;
      this.mest_version_major = null;
      this.mest_version_minor = null;
      this.mest_version_subminor = null;
      this.mest_version_patch_number = null;
    }
    else {
      if (initObj.hasOwnProperty('serial_number')) {
        this.serial_number = initObj.serial_number
      }
      else {
        this.serial_number = 0;
      }
      if (initObj.hasOwnProperty('production_date')) {
        this.production_date = initObj.production_date
      }
      else {
        this.production_date = 0;
      }
      if (initObj.hasOwnProperty('brain_version_major')) {
        this.brain_version_major = initObj.brain_version_major
      }
      else {
        this.brain_version_major = 0;
      }
      if (initObj.hasOwnProperty('brain_version_minor')) {
        this.brain_version_minor = initObj.brain_version_minor
      }
      else {
        this.brain_version_minor = 0;
      }
      if (initObj.hasOwnProperty('mest_version_major')) {
        this.mest_version_major = initObj.mest_version_major
      }
      else {
        this.mest_version_major = 0;
      }
      if (initObj.hasOwnProperty('mest_version_minor')) {
        this.mest_version_minor = initObj.mest_version_minor
      }
      else {
        this.mest_version_minor = 0;
      }
      if (initObj.hasOwnProperty('mest_version_subminor')) {
        this.mest_version_subminor = initObj.mest_version_subminor
      }
      else {
        this.mest_version_subminor = 0;
      }
      if (initObj.hasOwnProperty('mest_version_patch_number')) {
        this.mest_version_patch_number = initObj.mest_version_patch_number
      }
      else {
        this.mest_version_patch_number = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SeeQ
    // Serialize message field [serial_number]
    bufferOffset = _serializer.uint32(obj.serial_number, buffer, bufferOffset);
    // Serialize message field [production_date]
    bufferOffset = _serializer.uint64(obj.production_date, buffer, bufferOffset);
    // Serialize message field [brain_version_major]
    bufferOffset = _serializer.uint8(obj.brain_version_major, buffer, bufferOffset);
    // Serialize message field [brain_version_minor]
    bufferOffset = _serializer.uint8(obj.brain_version_minor, buffer, bufferOffset);
    // Serialize message field [mest_version_major]
    bufferOffset = _serializer.uint8(obj.mest_version_major, buffer, bufferOffset);
    // Serialize message field [mest_version_minor]
    bufferOffset = _serializer.uint8(obj.mest_version_minor, buffer, bufferOffset);
    // Serialize message field [mest_version_subminor]
    bufferOffset = _serializer.uint8(obj.mest_version_subminor, buffer, bufferOffset);
    // Serialize message field [mest_version_patch_number]
    bufferOffset = _serializer.uint8(obj.mest_version_patch_number, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SeeQ
    let len;
    let data = new SeeQ(null);
    // Deserialize message field [serial_number]
    data.serial_number = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [production_date]
    data.production_date = _deserializer.uint64(buffer, bufferOffset);
    // Deserialize message field [brain_version_major]
    data.brain_version_major = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [brain_version_minor]
    data.brain_version_minor = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [mest_version_major]
    data.mest_version_major = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [mest_version_minor]
    data.mest_version_minor = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [mest_version_subminor]
    data.mest_version_subminor = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [mest_version_patch_number]
    data.mest_version_patch_number = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 18;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/SeeQ';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bd0f4ac945460fd2020ae1118ef5c53f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint32 serial_number
    uint64 production_date
    
    uint8 brain_version_major
    uint8 brain_version_minor
    uint8 mest_version_major
    uint8 mest_version_minor
    uint8 mest_version_subminor
    uint8 mest_version_patch_number
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SeeQ(null);
    if (msg.serial_number !== undefined) {
      resolved.serial_number = msg.serial_number;
    }
    else {
      resolved.serial_number = 0
    }

    if (msg.production_date !== undefined) {
      resolved.production_date = msg.production_date;
    }
    else {
      resolved.production_date = 0
    }

    if (msg.brain_version_major !== undefined) {
      resolved.brain_version_major = msg.brain_version_major;
    }
    else {
      resolved.brain_version_major = 0
    }

    if (msg.brain_version_minor !== undefined) {
      resolved.brain_version_minor = msg.brain_version_minor;
    }
    else {
      resolved.brain_version_minor = 0
    }

    if (msg.mest_version_major !== undefined) {
      resolved.mest_version_major = msg.mest_version_major;
    }
    else {
      resolved.mest_version_major = 0
    }

    if (msg.mest_version_minor !== undefined) {
      resolved.mest_version_minor = msg.mest_version_minor;
    }
    else {
      resolved.mest_version_minor = 0
    }

    if (msg.mest_version_subminor !== undefined) {
      resolved.mest_version_subminor = msg.mest_version_subminor;
    }
    else {
      resolved.mest_version_subminor = 0
    }

    if (msg.mest_version_patch_number !== undefined) {
      resolved.mest_version_patch_number = msg.mest_version_patch_number;
    }
    else {
      resolved.mest_version_patch_number = 0
    }

    return resolved;
    }
};

module.exports = SeeQ;
