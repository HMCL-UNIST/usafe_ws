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

class FilterAidingMeasurementSummaryIndicator {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.enabled = null;
      this.used = null;
      this.residual_high_warning = null;
      this.sample_time_warning = null;
      this.configuration_error = null;
      this.max_num_meas_exceeded = null;
    }
    else {
      if (initObj.hasOwnProperty('enabled')) {
        this.enabled = initObj.enabled
      }
      else {
        this.enabled = false;
      }
      if (initObj.hasOwnProperty('used')) {
        this.used = initObj.used
      }
      else {
        this.used = false;
      }
      if (initObj.hasOwnProperty('residual_high_warning')) {
        this.residual_high_warning = initObj.residual_high_warning
      }
      else {
        this.residual_high_warning = false;
      }
      if (initObj.hasOwnProperty('sample_time_warning')) {
        this.sample_time_warning = initObj.sample_time_warning
      }
      else {
        this.sample_time_warning = false;
      }
      if (initObj.hasOwnProperty('configuration_error')) {
        this.configuration_error = initObj.configuration_error
      }
      else {
        this.configuration_error = false;
      }
      if (initObj.hasOwnProperty('max_num_meas_exceeded')) {
        this.max_num_meas_exceeded = initObj.max_num_meas_exceeded
      }
      else {
        this.max_num_meas_exceeded = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FilterAidingMeasurementSummaryIndicator
    // Serialize message field [enabled]
    bufferOffset = _serializer.bool(obj.enabled, buffer, bufferOffset);
    // Serialize message field [used]
    bufferOffset = _serializer.bool(obj.used, buffer, bufferOffset);
    // Serialize message field [residual_high_warning]
    bufferOffset = _serializer.bool(obj.residual_high_warning, buffer, bufferOffset);
    // Serialize message field [sample_time_warning]
    bufferOffset = _serializer.bool(obj.sample_time_warning, buffer, bufferOffset);
    // Serialize message field [configuration_error]
    bufferOffset = _serializer.bool(obj.configuration_error, buffer, bufferOffset);
    // Serialize message field [max_num_meas_exceeded]
    bufferOffset = _serializer.bool(obj.max_num_meas_exceeded, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FilterAidingMeasurementSummaryIndicator
    let len;
    let data = new FilterAidingMeasurementSummaryIndicator(null);
    // Deserialize message field [enabled]
    data.enabled = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [used]
    data.used = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [residual_high_warning]
    data.residual_high_warning = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [sample_time_warning]
    data.sample_time_warning = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [configuration_error]
    data.configuration_error = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [max_num_meas_exceeded]
    data.max_num_meas_exceeded = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/FilterAidingMeasurementSummaryIndicator';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4e3131125b51ac75dceed1517c488713';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new FilterAidingMeasurementSummaryIndicator(null);
    if (msg.enabled !== undefined) {
      resolved.enabled = msg.enabled;
    }
    else {
      resolved.enabled = false
    }

    if (msg.used !== undefined) {
      resolved.used = msg.used;
    }
    else {
      resolved.used = false
    }

    if (msg.residual_high_warning !== undefined) {
      resolved.residual_high_warning = msg.residual_high_warning;
    }
    else {
      resolved.residual_high_warning = false
    }

    if (msg.sample_time_warning !== undefined) {
      resolved.sample_time_warning = msg.sample_time_warning;
    }
    else {
      resolved.sample_time_warning = false
    }

    if (msg.configuration_error !== undefined) {
      resolved.configuration_error = msg.configuration_error;
    }
    else {
      resolved.configuration_error = false
    }

    if (msg.max_num_meas_exceeded !== undefined) {
      resolved.max_num_meas_exceeded = msg.max_num_meas_exceeded;
    }
    else {
      resolved.max_num_meas_exceeded = false
    }

    return resolved;
    }
};

module.exports = FilterAidingMeasurementSummaryIndicator;
