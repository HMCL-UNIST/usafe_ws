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

class RTKStatusV1 {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_tow = null;
      this.gps_week = null;
      this.epoch_status = null;
      this.dongle_version = null;
      this.dongle_controller_state = null;
      this.dongle_platform_state = null;
      this.dongle_controller_status = null;
      this.dongle_platform_status = null;
      this.dongle_reset_reason = null;
      this.dongle_signal_quality = null;
      this.gps_correction_latency = null;
      this.glonass_correction_latency = null;
      this.galileo_correction_latency = null;
      this.beidou_correction_latency = null;
      this.raw_status_flags = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_tow')) {
        this.gps_tow = initObj.gps_tow
      }
      else {
        this.gps_tow = 0.0;
      }
      if (initObj.hasOwnProperty('gps_week')) {
        this.gps_week = initObj.gps_week
      }
      else {
        this.gps_week = 0;
      }
      if (initObj.hasOwnProperty('epoch_status')) {
        this.epoch_status = initObj.epoch_status
      }
      else {
        this.epoch_status = 0;
      }
      if (initObj.hasOwnProperty('dongle_version')) {
        this.dongle_version = initObj.dongle_version
      }
      else {
        this.dongle_version = 0;
      }
      if (initObj.hasOwnProperty('dongle_controller_state')) {
        this.dongle_controller_state = initObj.dongle_controller_state
      }
      else {
        this.dongle_controller_state = 0;
      }
      if (initObj.hasOwnProperty('dongle_platform_state')) {
        this.dongle_platform_state = initObj.dongle_platform_state
      }
      else {
        this.dongle_platform_state = 0;
      }
      if (initObj.hasOwnProperty('dongle_controller_status')) {
        this.dongle_controller_status = initObj.dongle_controller_status
      }
      else {
        this.dongle_controller_status = 0;
      }
      if (initObj.hasOwnProperty('dongle_platform_status')) {
        this.dongle_platform_status = initObj.dongle_platform_status
      }
      else {
        this.dongle_platform_status = 0;
      }
      if (initObj.hasOwnProperty('dongle_reset_reason')) {
        this.dongle_reset_reason = initObj.dongle_reset_reason
      }
      else {
        this.dongle_reset_reason = 0;
      }
      if (initObj.hasOwnProperty('dongle_signal_quality')) {
        this.dongle_signal_quality = initObj.dongle_signal_quality
      }
      else {
        this.dongle_signal_quality = 0;
      }
      if (initObj.hasOwnProperty('gps_correction_latency')) {
        this.gps_correction_latency = initObj.gps_correction_latency
      }
      else {
        this.gps_correction_latency = 0.0;
      }
      if (initObj.hasOwnProperty('glonass_correction_latency')) {
        this.glonass_correction_latency = initObj.glonass_correction_latency
      }
      else {
        this.glonass_correction_latency = 0.0;
      }
      if (initObj.hasOwnProperty('galileo_correction_latency')) {
        this.galileo_correction_latency = initObj.galileo_correction_latency
      }
      else {
        this.galileo_correction_latency = 0.0;
      }
      if (initObj.hasOwnProperty('beidou_correction_latency')) {
        this.beidou_correction_latency = initObj.beidou_correction_latency
      }
      else {
        this.beidou_correction_latency = 0.0;
      }
      if (initObj.hasOwnProperty('raw_status_flags')) {
        this.raw_status_flags = initObj.raw_status_flags
      }
      else {
        this.raw_status_flags = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RTKStatusV1
    // Serialize message field [gps_tow]
    bufferOffset = _serializer.float64(obj.gps_tow, buffer, bufferOffset);
    // Serialize message field [gps_week]
    bufferOffset = _serializer.uint16(obj.gps_week, buffer, bufferOffset);
    // Serialize message field [epoch_status]
    bufferOffset = _serializer.uint16(obj.epoch_status, buffer, bufferOffset);
    // Serialize message field [dongle_version]
    bufferOffset = _serializer.uint8(obj.dongle_version, buffer, bufferOffset);
    // Serialize message field [dongle_controller_state]
    bufferOffset = _serializer.uint8(obj.dongle_controller_state, buffer, bufferOffset);
    // Serialize message field [dongle_platform_state]
    bufferOffset = _serializer.uint8(obj.dongle_platform_state, buffer, bufferOffset);
    // Serialize message field [dongle_controller_status]
    bufferOffset = _serializer.uint8(obj.dongle_controller_status, buffer, bufferOffset);
    // Serialize message field [dongle_platform_status]
    bufferOffset = _serializer.uint8(obj.dongle_platform_status, buffer, bufferOffset);
    // Serialize message field [dongle_reset_reason]
    bufferOffset = _serializer.uint8(obj.dongle_reset_reason, buffer, bufferOffset);
    // Serialize message field [dongle_signal_quality]
    bufferOffset = _serializer.uint8(obj.dongle_signal_quality, buffer, bufferOffset);
    // Serialize message field [gps_correction_latency]
    bufferOffset = _serializer.float32(obj.gps_correction_latency, buffer, bufferOffset);
    // Serialize message field [glonass_correction_latency]
    bufferOffset = _serializer.float32(obj.glonass_correction_latency, buffer, bufferOffset);
    // Serialize message field [galileo_correction_latency]
    bufferOffset = _serializer.float32(obj.galileo_correction_latency, buffer, bufferOffset);
    // Serialize message field [beidou_correction_latency]
    bufferOffset = _serializer.float32(obj.beidou_correction_latency, buffer, bufferOffset);
    // Serialize message field [raw_status_flags]
    bufferOffset = _serializer.uint32(obj.raw_status_flags, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RTKStatusV1
    let len;
    let data = new RTKStatusV1(null);
    // Deserialize message field [gps_tow]
    data.gps_tow = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gps_week]
    data.gps_week = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [epoch_status]
    data.epoch_status = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [dongle_version]
    data.dongle_version = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_controller_state]
    data.dongle_controller_state = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_platform_state]
    data.dongle_platform_state = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_controller_status]
    data.dongle_controller_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_platform_status]
    data.dongle_platform_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_reset_reason]
    data.dongle_reset_reason = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_signal_quality]
    data.dongle_signal_quality = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [gps_correction_latency]
    data.gps_correction_latency = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [glonass_correction_latency]
    data.glonass_correction_latency = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [galileo_correction_latency]
    data.galileo_correction_latency = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [beidou_correction_latency]
    data.beidou_correction_latency = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [raw_status_flags]
    data.raw_status_flags = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 39;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/RTKStatusV1';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5892d8d3cacc1b4c1666dd4bc1af9236';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 gps_tow
    uint16  gps_week
    uint16  epoch_status
    
    uint8   dongle_version
    uint8   dongle_controller_state
    uint8   dongle_platform_state
    uint8   dongle_controller_status
    uint8   dongle_platform_status
    uint8   dongle_reset_reason
    uint8   dongle_signal_quality
    
    float32 gps_correction_latency
    float32 glonass_correction_latency
    float32 galileo_correction_latency
    float32 beidou_correction_latency
    
    
    uint32  raw_status_flags        # Raw status flags value
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RTKStatusV1(null);
    if (msg.gps_tow !== undefined) {
      resolved.gps_tow = msg.gps_tow;
    }
    else {
      resolved.gps_tow = 0.0
    }

    if (msg.gps_week !== undefined) {
      resolved.gps_week = msg.gps_week;
    }
    else {
      resolved.gps_week = 0
    }

    if (msg.epoch_status !== undefined) {
      resolved.epoch_status = msg.epoch_status;
    }
    else {
      resolved.epoch_status = 0
    }

    if (msg.dongle_version !== undefined) {
      resolved.dongle_version = msg.dongle_version;
    }
    else {
      resolved.dongle_version = 0
    }

    if (msg.dongle_controller_state !== undefined) {
      resolved.dongle_controller_state = msg.dongle_controller_state;
    }
    else {
      resolved.dongle_controller_state = 0
    }

    if (msg.dongle_platform_state !== undefined) {
      resolved.dongle_platform_state = msg.dongle_platform_state;
    }
    else {
      resolved.dongle_platform_state = 0
    }

    if (msg.dongle_controller_status !== undefined) {
      resolved.dongle_controller_status = msg.dongle_controller_status;
    }
    else {
      resolved.dongle_controller_status = 0
    }

    if (msg.dongle_platform_status !== undefined) {
      resolved.dongle_platform_status = msg.dongle_platform_status;
    }
    else {
      resolved.dongle_platform_status = 0
    }

    if (msg.dongle_reset_reason !== undefined) {
      resolved.dongle_reset_reason = msg.dongle_reset_reason;
    }
    else {
      resolved.dongle_reset_reason = 0
    }

    if (msg.dongle_signal_quality !== undefined) {
      resolved.dongle_signal_quality = msg.dongle_signal_quality;
    }
    else {
      resolved.dongle_signal_quality = 0
    }

    if (msg.gps_correction_latency !== undefined) {
      resolved.gps_correction_latency = msg.gps_correction_latency;
    }
    else {
      resolved.gps_correction_latency = 0.0
    }

    if (msg.glonass_correction_latency !== undefined) {
      resolved.glonass_correction_latency = msg.glonass_correction_latency;
    }
    else {
      resolved.glonass_correction_latency = 0.0
    }

    if (msg.galileo_correction_latency !== undefined) {
      resolved.galileo_correction_latency = msg.galileo_correction_latency;
    }
    else {
      resolved.galileo_correction_latency = 0.0
    }

    if (msg.beidou_correction_latency !== undefined) {
      resolved.beidou_correction_latency = msg.beidou_correction_latency;
    }
    else {
      resolved.beidou_correction_latency = 0.0
    }

    if (msg.raw_status_flags !== undefined) {
      resolved.raw_status_flags = msg.raw_status_flags;
    }
    else {
      resolved.raw_status_flags = 0
    }

    return resolved;
    }
};

module.exports = RTKStatusV1;
