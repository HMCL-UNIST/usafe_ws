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

class SystemWarnings {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sound_type = null;
      this.peds_in_dz = null;
      this.peds_fcw = null;
      this.time_indicator = null;
      this.error_valid = null;
      this.error_code = null;
      this.zero_speed = null;
      this.headway_valid = null;
      this.headway_measurement = null;
      this.ldw_off = null;
      this.left_ldw_on = null;
      this.right_ldw_on = null;
      this.fcw_on = null;
      this.maintenance = null;
      this.failsafe = null;
      this.tsr_enabled = null;
      this.hw_repeatable_enabled = null;
      this.headway_warning_level = null;
      this.tsr_warning_level = null;
      this.tamper_alert = null;
    }
    else {
      if (initObj.hasOwnProperty('sound_type')) {
        this.sound_type = initObj.sound_type
      }
      else {
        this.sound_type = 0;
      }
      if (initObj.hasOwnProperty('peds_in_dz')) {
        this.peds_in_dz = initObj.peds_in_dz
      }
      else {
        this.peds_in_dz = false;
      }
      if (initObj.hasOwnProperty('peds_fcw')) {
        this.peds_fcw = initObj.peds_fcw
      }
      else {
        this.peds_fcw = false;
      }
      if (initObj.hasOwnProperty('time_indicator')) {
        this.time_indicator = initObj.time_indicator
      }
      else {
        this.time_indicator = 0;
      }
      if (initObj.hasOwnProperty('error_valid')) {
        this.error_valid = initObj.error_valid
      }
      else {
        this.error_valid = false;
      }
      if (initObj.hasOwnProperty('error_code')) {
        this.error_code = initObj.error_code
      }
      else {
        this.error_code = 0;
      }
      if (initObj.hasOwnProperty('zero_speed')) {
        this.zero_speed = initObj.zero_speed
      }
      else {
        this.zero_speed = false;
      }
      if (initObj.hasOwnProperty('headway_valid')) {
        this.headway_valid = initObj.headway_valid
      }
      else {
        this.headway_valid = false;
      }
      if (initObj.hasOwnProperty('headway_measurement')) {
        this.headway_measurement = initObj.headway_measurement
      }
      else {
        this.headway_measurement = 0.0;
      }
      if (initObj.hasOwnProperty('ldw_off')) {
        this.ldw_off = initObj.ldw_off
      }
      else {
        this.ldw_off = false;
      }
      if (initObj.hasOwnProperty('left_ldw_on')) {
        this.left_ldw_on = initObj.left_ldw_on
      }
      else {
        this.left_ldw_on = false;
      }
      if (initObj.hasOwnProperty('right_ldw_on')) {
        this.right_ldw_on = initObj.right_ldw_on
      }
      else {
        this.right_ldw_on = false;
      }
      if (initObj.hasOwnProperty('fcw_on')) {
        this.fcw_on = initObj.fcw_on
      }
      else {
        this.fcw_on = false;
      }
      if (initObj.hasOwnProperty('maintenance')) {
        this.maintenance = initObj.maintenance
      }
      else {
        this.maintenance = false;
      }
      if (initObj.hasOwnProperty('failsafe')) {
        this.failsafe = initObj.failsafe
      }
      else {
        this.failsafe = false;
      }
      if (initObj.hasOwnProperty('tsr_enabled')) {
        this.tsr_enabled = initObj.tsr_enabled
      }
      else {
        this.tsr_enabled = false;
      }
      if (initObj.hasOwnProperty('hw_repeatable_enabled')) {
        this.hw_repeatable_enabled = initObj.hw_repeatable_enabled
      }
      else {
        this.hw_repeatable_enabled = false;
      }
      if (initObj.hasOwnProperty('headway_warning_level')) {
        this.headway_warning_level = initObj.headway_warning_level
      }
      else {
        this.headway_warning_level = 0;
      }
      if (initObj.hasOwnProperty('tsr_warning_level')) {
        this.tsr_warning_level = initObj.tsr_warning_level
      }
      else {
        this.tsr_warning_level = 0;
      }
      if (initObj.hasOwnProperty('tamper_alert')) {
        this.tamper_alert = initObj.tamper_alert
      }
      else {
        this.tamper_alert = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SystemWarnings
    // Serialize message field [sound_type]
    bufferOffset = _serializer.uint8(obj.sound_type, buffer, bufferOffset);
    // Serialize message field [peds_in_dz]
    bufferOffset = _serializer.bool(obj.peds_in_dz, buffer, bufferOffset);
    // Serialize message field [peds_fcw]
    bufferOffset = _serializer.bool(obj.peds_fcw, buffer, bufferOffset);
    // Serialize message field [time_indicator]
    bufferOffset = _serializer.uint8(obj.time_indicator, buffer, bufferOffset);
    // Serialize message field [error_valid]
    bufferOffset = _serializer.bool(obj.error_valid, buffer, bufferOffset);
    // Serialize message field [error_code]
    bufferOffset = _serializer.uint8(obj.error_code, buffer, bufferOffset);
    // Serialize message field [zero_speed]
    bufferOffset = _serializer.bool(obj.zero_speed, buffer, bufferOffset);
    // Serialize message field [headway_valid]
    bufferOffset = _serializer.bool(obj.headway_valid, buffer, bufferOffset);
    // Serialize message field [headway_measurement]
    bufferOffset = _serializer.float32(obj.headway_measurement, buffer, bufferOffset);
    // Serialize message field [ldw_off]
    bufferOffset = _serializer.bool(obj.ldw_off, buffer, bufferOffset);
    // Serialize message field [left_ldw_on]
    bufferOffset = _serializer.bool(obj.left_ldw_on, buffer, bufferOffset);
    // Serialize message field [right_ldw_on]
    bufferOffset = _serializer.bool(obj.right_ldw_on, buffer, bufferOffset);
    // Serialize message field [fcw_on]
    bufferOffset = _serializer.bool(obj.fcw_on, buffer, bufferOffset);
    // Serialize message field [maintenance]
    bufferOffset = _serializer.bool(obj.maintenance, buffer, bufferOffset);
    // Serialize message field [failsafe]
    bufferOffset = _serializer.bool(obj.failsafe, buffer, bufferOffset);
    // Serialize message field [tsr_enabled]
    bufferOffset = _serializer.bool(obj.tsr_enabled, buffer, bufferOffset);
    // Serialize message field [hw_repeatable_enabled]
    bufferOffset = _serializer.bool(obj.hw_repeatable_enabled, buffer, bufferOffset);
    // Serialize message field [headway_warning_level]
    bufferOffset = _serializer.uint8(obj.headway_warning_level, buffer, bufferOffset);
    // Serialize message field [tsr_warning_level]
    bufferOffset = _serializer.uint8(obj.tsr_warning_level, buffer, bufferOffset);
    // Serialize message field [tamper_alert]
    bufferOffset = _serializer.bool(obj.tamper_alert, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SystemWarnings
    let len;
    let data = new SystemWarnings(null);
    // Deserialize message field [sound_type]
    data.sound_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [peds_in_dz]
    data.peds_in_dz = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [peds_fcw]
    data.peds_fcw = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [time_indicator]
    data.time_indicator = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [error_valid]
    data.error_valid = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [error_code]
    data.error_code = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [zero_speed]
    data.zero_speed = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [headway_valid]
    data.headway_valid = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [headway_measurement]
    data.headway_measurement = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ldw_off]
    data.ldw_off = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [left_ldw_on]
    data.left_ldw_on = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [right_ldw_on]
    data.right_ldw_on = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [fcw_on]
    data.fcw_on = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [maintenance]
    data.maintenance = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [failsafe]
    data.failsafe = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [tsr_enabled]
    data.tsr_enabled = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [hw_repeatable_enabled]
    data.hw_repeatable_enabled = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [headway_warning_level]
    data.headway_warning_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [tsr_warning_level]
    data.tsr_warning_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [tamper_alert]
    data.tamper_alert = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 23;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/SystemWarnings';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '13b6bac628f7b8055c48f3c1bf2dfa99';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 sound_type
    bool peds_in_dz
    bool peds_fcw
    uint8 time_indicator
    
    bool error_valid
    uint8 error_code
    bool zero_speed
    bool headway_valid
    float32 headway_measurement
    
    bool ldw_off
    bool left_ldw_on
    bool right_ldw_on
    bool fcw_on
    bool maintenance
    bool failsafe
    
    bool tsr_enabled
    bool hw_repeatable_enabled
    uint8 headway_warning_level
    uint8 tsr_warning_level
    bool tamper_alert
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SystemWarnings(null);
    if (msg.sound_type !== undefined) {
      resolved.sound_type = msg.sound_type;
    }
    else {
      resolved.sound_type = 0
    }

    if (msg.peds_in_dz !== undefined) {
      resolved.peds_in_dz = msg.peds_in_dz;
    }
    else {
      resolved.peds_in_dz = false
    }

    if (msg.peds_fcw !== undefined) {
      resolved.peds_fcw = msg.peds_fcw;
    }
    else {
      resolved.peds_fcw = false
    }

    if (msg.time_indicator !== undefined) {
      resolved.time_indicator = msg.time_indicator;
    }
    else {
      resolved.time_indicator = 0
    }

    if (msg.error_valid !== undefined) {
      resolved.error_valid = msg.error_valid;
    }
    else {
      resolved.error_valid = false
    }

    if (msg.error_code !== undefined) {
      resolved.error_code = msg.error_code;
    }
    else {
      resolved.error_code = 0
    }

    if (msg.zero_speed !== undefined) {
      resolved.zero_speed = msg.zero_speed;
    }
    else {
      resolved.zero_speed = false
    }

    if (msg.headway_valid !== undefined) {
      resolved.headway_valid = msg.headway_valid;
    }
    else {
      resolved.headway_valid = false
    }

    if (msg.headway_measurement !== undefined) {
      resolved.headway_measurement = msg.headway_measurement;
    }
    else {
      resolved.headway_measurement = 0.0
    }

    if (msg.ldw_off !== undefined) {
      resolved.ldw_off = msg.ldw_off;
    }
    else {
      resolved.ldw_off = false
    }

    if (msg.left_ldw_on !== undefined) {
      resolved.left_ldw_on = msg.left_ldw_on;
    }
    else {
      resolved.left_ldw_on = false
    }

    if (msg.right_ldw_on !== undefined) {
      resolved.right_ldw_on = msg.right_ldw_on;
    }
    else {
      resolved.right_ldw_on = false
    }

    if (msg.fcw_on !== undefined) {
      resolved.fcw_on = msg.fcw_on;
    }
    else {
      resolved.fcw_on = false
    }

    if (msg.maintenance !== undefined) {
      resolved.maintenance = msg.maintenance;
    }
    else {
      resolved.maintenance = false
    }

    if (msg.failsafe !== undefined) {
      resolved.failsafe = msg.failsafe;
    }
    else {
      resolved.failsafe = false
    }

    if (msg.tsr_enabled !== undefined) {
      resolved.tsr_enabled = msg.tsr_enabled;
    }
    else {
      resolved.tsr_enabled = false
    }

    if (msg.hw_repeatable_enabled !== undefined) {
      resolved.hw_repeatable_enabled = msg.hw_repeatable_enabled;
    }
    else {
      resolved.hw_repeatable_enabled = false
    }

    if (msg.headway_warning_level !== undefined) {
      resolved.headway_warning_level = msg.headway_warning_level;
    }
    else {
      resolved.headway_warning_level = 0
    }

    if (msg.tsr_warning_level !== undefined) {
      resolved.tsr_warning_level = msg.tsr_warning_level;
    }
    else {
      resolved.tsr_warning_level = 0
    }

    if (msg.tamper_alert !== undefined) {
      resolved.tamper_alert = msg.tamper_alert;
    }
    else {
      resolved.tamper_alert = false
    }

    return resolved;
    }
};

module.exports = SystemWarnings;
