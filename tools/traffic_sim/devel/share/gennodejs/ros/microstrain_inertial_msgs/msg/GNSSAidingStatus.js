// Auto-generated. Do not edit!

// (in-package microstrain_inertial_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class GNSSAidingStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_tow = null;
      this.has_position_fix = null;
      this.tight_coupling = null;
      this.differential_corrections = null;
      this.integer_fix = null;
      this.using_gps = null;
      this.using_glonass = null;
      this.using_galileo = null;
      this.using_beidou = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_tow')) {
        this.gps_tow = initObj.gps_tow
      }
      else {
        this.gps_tow = 0.0;
      }
      if (initObj.hasOwnProperty('has_position_fix')) {
        this.has_position_fix = initObj.has_position_fix
      }
      else {
        this.has_position_fix = false;
      }
      if (initObj.hasOwnProperty('tight_coupling')) {
        this.tight_coupling = initObj.tight_coupling
      }
      else {
        this.tight_coupling = false;
      }
      if (initObj.hasOwnProperty('differential_corrections')) {
        this.differential_corrections = initObj.differential_corrections
      }
      else {
        this.differential_corrections = false;
      }
      if (initObj.hasOwnProperty('integer_fix')) {
        this.integer_fix = initObj.integer_fix
      }
      else {
        this.integer_fix = false;
      }
      if (initObj.hasOwnProperty('using_gps')) {
        this.using_gps = initObj.using_gps
      }
      else {
        this.using_gps = false;
      }
      if (initObj.hasOwnProperty('using_glonass')) {
        this.using_glonass = initObj.using_glonass
      }
      else {
        this.using_glonass = false;
      }
      if (initObj.hasOwnProperty('using_galileo')) {
        this.using_galileo = initObj.using_galileo
      }
      else {
        this.using_galileo = false;
      }
      if (initObj.hasOwnProperty('using_beidou')) {
        this.using_beidou = initObj.using_beidou
      }
      else {
        this.using_beidou = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GNSSAidingStatus
    // Serialize message field [gps_tow]
    bufferOffset = _serializer.float64(obj.gps_tow, buffer, bufferOffset);
    // Serialize message field [has_position_fix]
    bufferOffset = _serializer.bool(obj.has_position_fix, buffer, bufferOffset);
    // Serialize message field [tight_coupling]
    bufferOffset = _serializer.bool(obj.tight_coupling, buffer, bufferOffset);
    // Serialize message field [differential_corrections]
    bufferOffset = _serializer.bool(obj.differential_corrections, buffer, bufferOffset);
    // Serialize message field [integer_fix]
    bufferOffset = _serializer.bool(obj.integer_fix, buffer, bufferOffset);
    // Serialize message field [using_gps]
    bufferOffset = _serializer.bool(obj.using_gps, buffer, bufferOffset);
    // Serialize message field [using_glonass]
    bufferOffset = _serializer.bool(obj.using_glonass, buffer, bufferOffset);
    // Serialize message field [using_galileo]
    bufferOffset = _serializer.bool(obj.using_galileo, buffer, bufferOffset);
    // Serialize message field [using_beidou]
    bufferOffset = _serializer.bool(obj.using_beidou, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GNSSAidingStatus
    let len;
    let data = new GNSSAidingStatus(null);
    // Deserialize message field [gps_tow]
    data.gps_tow = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [has_position_fix]
    data.has_position_fix = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [tight_coupling]
    data.tight_coupling = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [differential_corrections]
    data.differential_corrections = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [integer_fix]
    data.integer_fix = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [using_gps]
    data.using_gps = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [using_glonass]
    data.using_glonass = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [using_galileo]
    data.using_galileo = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [using_beidou]
    data.using_beidou = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/GNSSAidingStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '93a07537312a9e616123b06cec1efdf6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 gps_tow
    bool    has_position_fix
    bool    tight_coupling
    bool    differential_corrections
    bool    integer_fix
    bool    using_gps 
    bool    using_glonass
    bool    using_galileo
    bool    using_beidou
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GNSSAidingStatus(null);
    if (msg.gps_tow !== undefined) {
      resolved.gps_tow = msg.gps_tow;
    }
    else {
      resolved.gps_tow = 0.0
    }

    if (msg.has_position_fix !== undefined) {
      resolved.has_position_fix = msg.has_position_fix;
    }
    else {
      resolved.has_position_fix = false
    }

    if (msg.tight_coupling !== undefined) {
      resolved.tight_coupling = msg.tight_coupling;
    }
    else {
      resolved.tight_coupling = false
    }

    if (msg.differential_corrections !== undefined) {
      resolved.differential_corrections = msg.differential_corrections;
    }
    else {
      resolved.differential_corrections = false
    }

    if (msg.integer_fix !== undefined) {
      resolved.integer_fix = msg.integer_fix;
    }
    else {
      resolved.integer_fix = false
    }

    if (msg.using_gps !== undefined) {
      resolved.using_gps = msg.using_gps;
    }
    else {
      resolved.using_gps = false
    }

    if (msg.using_glonass !== undefined) {
      resolved.using_glonass = msg.using_glonass;
    }
    else {
      resolved.using_glonass = false
    }

    if (msg.using_galileo !== undefined) {
      resolved.using_galileo = msg.using_galileo;
    }
    else {
      resolved.using_galileo = false
    }

    if (msg.using_beidou !== undefined) {
      resolved.using_beidou = msg.using_beidou;
    }
    else {
      resolved.using_beidou = false
    }

    return resolved;
    }
};

module.exports = GNSSAidingStatus;
