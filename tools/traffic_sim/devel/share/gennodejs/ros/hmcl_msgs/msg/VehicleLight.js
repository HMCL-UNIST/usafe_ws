// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class VehicleLight {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.left_light = null;
      this.right_light = null;
      this.hazard_light = null;
    }
    else {
      if (initObj.hasOwnProperty('left_light')) {
        this.left_light = initObj.left_light
      }
      else {
        this.left_light = 0;
      }
      if (initObj.hasOwnProperty('right_light')) {
        this.right_light = initObj.right_light
      }
      else {
        this.right_light = 0;
      }
      if (initObj.hasOwnProperty('hazard_light')) {
        this.hazard_light = initObj.hazard_light
      }
      else {
        this.hazard_light = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleLight
    // Serialize message field [left_light]
    bufferOffset = _serializer.uint8(obj.left_light, buffer, bufferOffset);
    // Serialize message field [right_light]
    bufferOffset = _serializer.uint8(obj.right_light, buffer, bufferOffset);
    // Serialize message field [hazard_light]
    bufferOffset = _serializer.uint8(obj.hazard_light, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleLight
    let len;
    let data = new VehicleLight(null);
    // Deserialize message field [left_light]
    data.left_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [right_light]
    data.right_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hazard_light]
    data.hazard_light = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 3;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/VehicleLight';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b381125a33d115f19eb1624e1387eaae';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # 0 off, 1 on 
    uint8 left_light
    uint8 right_light
    uint8 hazard_light
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VehicleLight(null);
    if (msg.left_light !== undefined) {
      resolved.left_light = msg.left_light;
    }
    else {
      resolved.left_light = 0
    }

    if (msg.right_light !== undefined) {
      resolved.right_light = msg.right_light;
    }
    else {
      resolved.right_light = 0
    }

    if (msg.hazard_light !== undefined) {
      resolved.hazard_light = msg.hazard_light;
    }
    else {
      resolved.hazard_light = 0
    }

    return resolved;
    }
};

module.exports = VehicleLight;
