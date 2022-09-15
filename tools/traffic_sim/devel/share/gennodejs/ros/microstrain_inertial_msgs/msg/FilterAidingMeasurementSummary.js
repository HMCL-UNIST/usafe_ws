// Auto-generated. Do not edit!

// (in-package microstrain_inertial_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let FilterAidingMeasurementSummaryIndicator = require('./FilterAidingMeasurementSummaryIndicator.js');

//-----------------------------------------------------------

class FilterAidingMeasurementSummary {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_tow = null;
      this.gnss1 = null;
      this.gnss2 = null;
      this.dual_antenna = null;
      this.heading = null;
      this.pressure = null;
      this.magnetometer = null;
      this.speed = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_tow')) {
        this.gps_tow = initObj.gps_tow
      }
      else {
        this.gps_tow = 0.0;
      }
      if (initObj.hasOwnProperty('gnss1')) {
        this.gnss1 = initObj.gnss1
      }
      else {
        this.gnss1 = new FilterAidingMeasurementSummaryIndicator();
      }
      if (initObj.hasOwnProperty('gnss2')) {
        this.gnss2 = initObj.gnss2
      }
      else {
        this.gnss2 = new FilterAidingMeasurementSummaryIndicator();
      }
      if (initObj.hasOwnProperty('dual_antenna')) {
        this.dual_antenna = initObj.dual_antenna
      }
      else {
        this.dual_antenna = new FilterAidingMeasurementSummaryIndicator();
      }
      if (initObj.hasOwnProperty('heading')) {
        this.heading = initObj.heading
      }
      else {
        this.heading = new FilterAidingMeasurementSummaryIndicator();
      }
      if (initObj.hasOwnProperty('pressure')) {
        this.pressure = initObj.pressure
      }
      else {
        this.pressure = new FilterAidingMeasurementSummaryIndicator();
      }
      if (initObj.hasOwnProperty('magnetometer')) {
        this.magnetometer = initObj.magnetometer
      }
      else {
        this.magnetometer = new FilterAidingMeasurementSummaryIndicator();
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = new FilterAidingMeasurementSummaryIndicator();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FilterAidingMeasurementSummary
    // Serialize message field [gps_tow]
    bufferOffset = _serializer.float64(obj.gps_tow, buffer, bufferOffset);
    // Serialize message field [gnss1]
    bufferOffset = FilterAidingMeasurementSummaryIndicator.serialize(obj.gnss1, buffer, bufferOffset);
    // Serialize message field [gnss2]
    bufferOffset = FilterAidingMeasurementSummaryIndicator.serialize(obj.gnss2, buffer, bufferOffset);
    // Serialize message field [dual_antenna]
    bufferOffset = FilterAidingMeasurementSummaryIndicator.serialize(obj.dual_antenna, buffer, bufferOffset);
    // Serialize message field [heading]
    bufferOffset = FilterAidingMeasurementSummaryIndicator.serialize(obj.heading, buffer, bufferOffset);
    // Serialize message field [pressure]
    bufferOffset = FilterAidingMeasurementSummaryIndicator.serialize(obj.pressure, buffer, bufferOffset);
    // Serialize message field [magnetometer]
    bufferOffset = FilterAidingMeasurementSummaryIndicator.serialize(obj.magnetometer, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = FilterAidingMeasurementSummaryIndicator.serialize(obj.speed, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FilterAidingMeasurementSummary
    let len;
    let data = new FilterAidingMeasurementSummary(null);
    // Deserialize message field [gps_tow]
    data.gps_tow = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gnss1]
    data.gnss1 = FilterAidingMeasurementSummaryIndicator.deserialize(buffer, bufferOffset);
    // Deserialize message field [gnss2]
    data.gnss2 = FilterAidingMeasurementSummaryIndicator.deserialize(buffer, bufferOffset);
    // Deserialize message field [dual_antenna]
    data.dual_antenna = FilterAidingMeasurementSummaryIndicator.deserialize(buffer, bufferOffset);
    // Deserialize message field [heading]
    data.heading = FilterAidingMeasurementSummaryIndicator.deserialize(buffer, bufferOffset);
    // Deserialize message field [pressure]
    data.pressure = FilterAidingMeasurementSummaryIndicator.deserialize(buffer, bufferOffset);
    // Deserialize message field [magnetometer]
    data.magnetometer = FilterAidingMeasurementSummaryIndicator.deserialize(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = FilterAidingMeasurementSummaryIndicator.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 50;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/FilterAidingMeasurementSummary';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '150119d26260add7097bcac810af3fdb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 gps_tow
    microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator gnss1
    microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator gnss2
    microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator dual_antenna
    microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator heading
    microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator pressure
    microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator magnetometer
    microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator speed
    ================================================================================
    MSG: microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator
    bool enabled
    bool used
    bool residual_high_warning
    bool sample_time_warning
    bool configuration_error
    bool max_num_meas_exceeded
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FilterAidingMeasurementSummary(null);
    if (msg.gps_tow !== undefined) {
      resolved.gps_tow = msg.gps_tow;
    }
    else {
      resolved.gps_tow = 0.0
    }

    if (msg.gnss1 !== undefined) {
      resolved.gnss1 = FilterAidingMeasurementSummaryIndicator.Resolve(msg.gnss1)
    }
    else {
      resolved.gnss1 = new FilterAidingMeasurementSummaryIndicator()
    }

    if (msg.gnss2 !== undefined) {
      resolved.gnss2 = FilterAidingMeasurementSummaryIndicator.Resolve(msg.gnss2)
    }
    else {
      resolved.gnss2 = new FilterAidingMeasurementSummaryIndicator()
    }

    if (msg.dual_antenna !== undefined) {
      resolved.dual_antenna = FilterAidingMeasurementSummaryIndicator.Resolve(msg.dual_antenna)
    }
    else {
      resolved.dual_antenna = new FilterAidingMeasurementSummaryIndicator()
    }

    if (msg.heading !== undefined) {
      resolved.heading = FilterAidingMeasurementSummaryIndicator.Resolve(msg.heading)
    }
    else {
      resolved.heading = new FilterAidingMeasurementSummaryIndicator()
    }

    if (msg.pressure !== undefined) {
      resolved.pressure = FilterAidingMeasurementSummaryIndicator.Resolve(msg.pressure)
    }
    else {
      resolved.pressure = new FilterAidingMeasurementSummaryIndicator()
    }

    if (msg.magnetometer !== undefined) {
      resolved.magnetometer = FilterAidingMeasurementSummaryIndicator.Resolve(msg.magnetometer)
    }
    else {
      resolved.magnetometer = new FilterAidingMeasurementSummaryIndicator()
    }

    if (msg.speed !== undefined) {
      resolved.speed = FilterAidingMeasurementSummaryIndicator.Resolve(msg.speed)
    }
    else {
      resolved.speed = new FilterAidingMeasurementSummaryIndicator()
    }

    return resolved;
    }
};

module.exports = FilterAidingMeasurementSummary;
