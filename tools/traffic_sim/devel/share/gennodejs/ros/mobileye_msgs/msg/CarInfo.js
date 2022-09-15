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

class CarInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.high_beam = null;
      this.low_beam = null;
      this.wipers = null;
      this.right_signal = null;
      this.left_signal = null;
      this.brake_signal = null;
      this.wipers_available = null;
      this.low_beam_available = null;
      this.high_beam_available = null;
      this.right_blink_available = null;
      this.left_blink_available = null;
      this.brake_available = null;
      this.speed_available = null;
      this.speed = null;
      this.shield_plus_settings = null;
    }
    else {
      if (initObj.hasOwnProperty('high_beam')) {
        this.high_beam = initObj.high_beam
      }
      else {
        this.high_beam = false;
      }
      if (initObj.hasOwnProperty('low_beam')) {
        this.low_beam = initObj.low_beam
      }
      else {
        this.low_beam = false;
      }
      if (initObj.hasOwnProperty('wipers')) {
        this.wipers = initObj.wipers
      }
      else {
        this.wipers = false;
      }
      if (initObj.hasOwnProperty('right_signal')) {
        this.right_signal = initObj.right_signal
      }
      else {
        this.right_signal = false;
      }
      if (initObj.hasOwnProperty('left_signal')) {
        this.left_signal = initObj.left_signal
      }
      else {
        this.left_signal = false;
      }
      if (initObj.hasOwnProperty('brake_signal')) {
        this.brake_signal = initObj.brake_signal
      }
      else {
        this.brake_signal = false;
      }
      if (initObj.hasOwnProperty('wipers_available')) {
        this.wipers_available = initObj.wipers_available
      }
      else {
        this.wipers_available = false;
      }
      if (initObj.hasOwnProperty('low_beam_available')) {
        this.low_beam_available = initObj.low_beam_available
      }
      else {
        this.low_beam_available = false;
      }
      if (initObj.hasOwnProperty('high_beam_available')) {
        this.high_beam_available = initObj.high_beam_available
      }
      else {
        this.high_beam_available = false;
      }
      if (initObj.hasOwnProperty('right_blink_available')) {
        this.right_blink_available = initObj.right_blink_available
      }
      else {
        this.right_blink_available = false;
      }
      if (initObj.hasOwnProperty('left_blink_available')) {
        this.left_blink_available = initObj.left_blink_available
      }
      else {
        this.left_blink_available = false;
      }
      if (initObj.hasOwnProperty('brake_available')) {
        this.brake_available = initObj.brake_available
      }
      else {
        this.brake_available = false;
      }
      if (initObj.hasOwnProperty('speed_available')) {
        this.speed_available = initObj.speed_available
      }
      else {
        this.speed_available = false;
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0;
      }
      if (initObj.hasOwnProperty('shield_plus_settings')) {
        this.shield_plus_settings = initObj.shield_plus_settings
      }
      else {
        this.shield_plus_settings = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CarInfo
    // Serialize message field [high_beam]
    bufferOffset = _serializer.bool(obj.high_beam, buffer, bufferOffset);
    // Serialize message field [low_beam]
    bufferOffset = _serializer.bool(obj.low_beam, buffer, bufferOffset);
    // Serialize message field [wipers]
    bufferOffset = _serializer.bool(obj.wipers, buffer, bufferOffset);
    // Serialize message field [right_signal]
    bufferOffset = _serializer.bool(obj.right_signal, buffer, bufferOffset);
    // Serialize message field [left_signal]
    bufferOffset = _serializer.bool(obj.left_signal, buffer, bufferOffset);
    // Serialize message field [brake_signal]
    bufferOffset = _serializer.bool(obj.brake_signal, buffer, bufferOffset);
    // Serialize message field [wipers_available]
    bufferOffset = _serializer.bool(obj.wipers_available, buffer, bufferOffset);
    // Serialize message field [low_beam_available]
    bufferOffset = _serializer.bool(obj.low_beam_available, buffer, bufferOffset);
    // Serialize message field [high_beam_available]
    bufferOffset = _serializer.bool(obj.high_beam_available, buffer, bufferOffset);
    // Serialize message field [right_blink_available]
    bufferOffset = _serializer.bool(obj.right_blink_available, buffer, bufferOffset);
    // Serialize message field [left_blink_available]
    bufferOffset = _serializer.bool(obj.left_blink_available, buffer, bufferOffset);
    // Serialize message field [brake_available]
    bufferOffset = _serializer.bool(obj.brake_available, buffer, bufferOffset);
    // Serialize message field [speed_available]
    bufferOffset = _serializer.bool(obj.speed_available, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.uint8(obj.speed, buffer, bufferOffset);
    // Serialize message field [shield_plus_settings]
    bufferOffset = _serializer.uint8(obj.shield_plus_settings, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CarInfo
    let len;
    let data = new CarInfo(null);
    // Deserialize message field [high_beam]
    data.high_beam = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [low_beam]
    data.low_beam = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [wipers]
    data.wipers = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [right_signal]
    data.right_signal = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [left_signal]
    data.left_signal = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [brake_signal]
    data.brake_signal = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [wipers_available]
    data.wipers_available = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [low_beam_available]
    data.low_beam_available = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [high_beam_available]
    data.high_beam_available = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [right_blink_available]
    data.right_blink_available = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [left_blink_available]
    data.left_blink_available = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [brake_available]
    data.brake_available = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [speed_available]
    data.speed_available = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [shield_plus_settings]
    data.shield_plus_settings = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 15;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/CarInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '50aff2fafecf310fa3fc9bcf4c9a5c85';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool high_beam
    bool low_beam
    bool wipers
    bool right_signal
    bool left_signal
    bool brake_signal
    bool wipers_available
    bool low_beam_available
    bool high_beam_available
    bool right_blink_available
    bool left_blink_available
    bool brake_available
    bool speed_available
    uint8 speed
    uint8 shield_plus_settings
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CarInfo(null);
    if (msg.high_beam !== undefined) {
      resolved.high_beam = msg.high_beam;
    }
    else {
      resolved.high_beam = false
    }

    if (msg.low_beam !== undefined) {
      resolved.low_beam = msg.low_beam;
    }
    else {
      resolved.low_beam = false
    }

    if (msg.wipers !== undefined) {
      resolved.wipers = msg.wipers;
    }
    else {
      resolved.wipers = false
    }

    if (msg.right_signal !== undefined) {
      resolved.right_signal = msg.right_signal;
    }
    else {
      resolved.right_signal = false
    }

    if (msg.left_signal !== undefined) {
      resolved.left_signal = msg.left_signal;
    }
    else {
      resolved.left_signal = false
    }

    if (msg.brake_signal !== undefined) {
      resolved.brake_signal = msg.brake_signal;
    }
    else {
      resolved.brake_signal = false
    }

    if (msg.wipers_available !== undefined) {
      resolved.wipers_available = msg.wipers_available;
    }
    else {
      resolved.wipers_available = false
    }

    if (msg.low_beam_available !== undefined) {
      resolved.low_beam_available = msg.low_beam_available;
    }
    else {
      resolved.low_beam_available = false
    }

    if (msg.high_beam_available !== undefined) {
      resolved.high_beam_available = msg.high_beam_available;
    }
    else {
      resolved.high_beam_available = false
    }

    if (msg.right_blink_available !== undefined) {
      resolved.right_blink_available = msg.right_blink_available;
    }
    else {
      resolved.right_blink_available = false
    }

    if (msg.left_blink_available !== undefined) {
      resolved.left_blink_available = msg.left_blink_available;
    }
    else {
      resolved.left_blink_available = false
    }

    if (msg.brake_available !== undefined) {
      resolved.brake_available = msg.brake_available;
    }
    else {
      resolved.brake_available = false
    }

    if (msg.speed_available !== undefined) {
      resolved.speed_available = msg.speed_available;
    }
    else {
      resolved.speed_available = false
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0
    }

    if (msg.shield_plus_settings !== undefined) {
      resolved.shield_plus_settings = msg.shield_plus_settings;
    }
    else {
      resolved.shield_plus_settings = 0
    }

    return resolved;
    }
};

module.exports = CarInfo;
