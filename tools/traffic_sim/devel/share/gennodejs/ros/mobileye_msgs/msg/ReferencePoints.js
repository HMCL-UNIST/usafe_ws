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

class ReferencePoints {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ref_point1_position = null;
      this.ref_point1_distance = null;
      this.ref_point1_validity = null;
      this.ref_point2_position = null;
      this.ref_point2_distance = null;
      this.ref_point2_validity = null;
    }
    else {
      if (initObj.hasOwnProperty('ref_point1_position')) {
        this.ref_point1_position = initObj.ref_point1_position
      }
      else {
        this.ref_point1_position = 0.0;
      }
      if (initObj.hasOwnProperty('ref_point1_distance')) {
        this.ref_point1_distance = initObj.ref_point1_distance
      }
      else {
        this.ref_point1_distance = 0.0;
      }
      if (initObj.hasOwnProperty('ref_point1_validity')) {
        this.ref_point1_validity = initObj.ref_point1_validity
      }
      else {
        this.ref_point1_validity = false;
      }
      if (initObj.hasOwnProperty('ref_point2_position')) {
        this.ref_point2_position = initObj.ref_point2_position
      }
      else {
        this.ref_point2_position = 0.0;
      }
      if (initObj.hasOwnProperty('ref_point2_distance')) {
        this.ref_point2_distance = initObj.ref_point2_distance
      }
      else {
        this.ref_point2_distance = 0.0;
      }
      if (initObj.hasOwnProperty('ref_point2_validity')) {
        this.ref_point2_validity = initObj.ref_point2_validity
      }
      else {
        this.ref_point2_validity = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ReferencePoints
    // Serialize message field [ref_point1_position]
    bufferOffset = _serializer.float32(obj.ref_point1_position, buffer, bufferOffset);
    // Serialize message field [ref_point1_distance]
    bufferOffset = _serializer.float32(obj.ref_point1_distance, buffer, bufferOffset);
    // Serialize message field [ref_point1_validity]
    bufferOffset = _serializer.bool(obj.ref_point1_validity, buffer, bufferOffset);
    // Serialize message field [ref_point2_position]
    bufferOffset = _serializer.float32(obj.ref_point2_position, buffer, bufferOffset);
    // Serialize message field [ref_point2_distance]
    bufferOffset = _serializer.float32(obj.ref_point2_distance, buffer, bufferOffset);
    // Serialize message field [ref_point2_validity]
    bufferOffset = _serializer.bool(obj.ref_point2_validity, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ReferencePoints
    let len;
    let data = new ReferencePoints(null);
    // Deserialize message field [ref_point1_position]
    data.ref_point1_position = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ref_point1_distance]
    data.ref_point1_distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ref_point1_validity]
    data.ref_point1_validity = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [ref_point2_position]
    data.ref_point2_position = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ref_point2_distance]
    data.ref_point2_distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ref_point2_validity]
    data.ref_point2_validity = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 18;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/ReferencePoints';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '56eb2a2d0b9b9695b81746d73432e3b8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 ref_point1_position
    float32 ref_point1_distance
    bool ref_point1_validity
    float32 ref_point2_position
    float32 ref_point2_distance
    bool ref_point2_validity
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ReferencePoints(null);
    if (msg.ref_point1_position !== undefined) {
      resolved.ref_point1_position = msg.ref_point1_position;
    }
    else {
      resolved.ref_point1_position = 0.0
    }

    if (msg.ref_point1_distance !== undefined) {
      resolved.ref_point1_distance = msg.ref_point1_distance;
    }
    else {
      resolved.ref_point1_distance = 0.0
    }

    if (msg.ref_point1_validity !== undefined) {
      resolved.ref_point1_validity = msg.ref_point1_validity;
    }
    else {
      resolved.ref_point1_validity = false
    }

    if (msg.ref_point2_position !== undefined) {
      resolved.ref_point2_position = msg.ref_point2_position;
    }
    else {
      resolved.ref_point2_position = 0.0
    }

    if (msg.ref_point2_distance !== undefined) {
      resolved.ref_point2_distance = msg.ref_point2_distance;
    }
    else {
      resolved.ref_point2_distance = 0.0
    }

    if (msg.ref_point2_validity !== undefined) {
      resolved.ref_point2_validity = msg.ref_point2_validity;
    }
    else {
      resolved.ref_point2_validity = false
    }

    return resolved;
    }
};

module.exports = ReferencePoints;
