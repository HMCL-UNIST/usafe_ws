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

class InputSpeedMeasurement {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_tow = null;
      this.speed = null;
      this.speed_uncertainty = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_tow')) {
        this.gps_tow = initObj.gps_tow
      }
      else {
        this.gps_tow = 0.0;
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0.0;
      }
      if (initObj.hasOwnProperty('speed_uncertainty')) {
        this.speed_uncertainty = initObj.speed_uncertainty
      }
      else {
        this.speed_uncertainty = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type InputSpeedMeasurement
    // Serialize message field [gps_tow]
    bufferOffset = _serializer.float32(obj.gps_tow, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float32(obj.speed, buffer, bufferOffset);
    // Serialize message field [speed_uncertainty]
    bufferOffset = _serializer.float32(obj.speed_uncertainty, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type InputSpeedMeasurement
    let len;
    let data = new InputSpeedMeasurement(null);
    // Deserialize message field [gps_tow]
    data.gps_tow = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [speed_uncertainty]
    data.speed_uncertainty = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/InputSpeedMeasurement';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c23013e9b4813b23fc2611c8b2e2b2c8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 gps_tow  # GPS time of week when speed was sampled
    float32 speed  # Estimated speed along vehicle's x-axis (may be positive or negative) (m/s)
    float32 speed_uncertainty  # Estimated uncertainty in the speed measurement (1-sigma value) (m/s)
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new InputSpeedMeasurement(null);
    if (msg.gps_tow !== undefined) {
      resolved.gps_tow = msg.gps_tow;
    }
    else {
      resolved.gps_tow = 0.0
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0.0
    }

    if (msg.speed_uncertainty !== undefined) {
      resolved.speed_uncertainty = msg.speed_uncertainty;
    }
    else {
      resolved.speed_uncertainty = 0.0
    }

    return resolved;
    }
};

module.exports = InputSpeedMeasurement;
