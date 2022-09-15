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

class GNSSDualAntennaStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_tow = null;
      this.heading = null;
      this.heading_uncertainty = null;
      this.fix_type = null;
      this.rcv_1_valid = null;
      this.rcv_2_valid = null;
      this.antenna_offsets_valid = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_tow')) {
        this.gps_tow = initObj.gps_tow
      }
      else {
        this.gps_tow = 0.0;
      }
      if (initObj.hasOwnProperty('heading')) {
        this.heading = initObj.heading
      }
      else {
        this.heading = 0.0;
      }
      if (initObj.hasOwnProperty('heading_uncertainty')) {
        this.heading_uncertainty = initObj.heading_uncertainty
      }
      else {
        this.heading_uncertainty = 0.0;
      }
      if (initObj.hasOwnProperty('fix_type')) {
        this.fix_type = initObj.fix_type
      }
      else {
        this.fix_type = 0;
      }
      if (initObj.hasOwnProperty('rcv_1_valid')) {
        this.rcv_1_valid = initObj.rcv_1_valid
      }
      else {
        this.rcv_1_valid = 0;
      }
      if (initObj.hasOwnProperty('rcv_2_valid')) {
        this.rcv_2_valid = initObj.rcv_2_valid
      }
      else {
        this.rcv_2_valid = 0;
      }
      if (initObj.hasOwnProperty('antenna_offsets_valid')) {
        this.antenna_offsets_valid = initObj.antenna_offsets_valid
      }
      else {
        this.antenna_offsets_valid = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GNSSDualAntennaStatus
    // Serialize message field [gps_tow]
    bufferOffset = _serializer.float32(obj.gps_tow, buffer, bufferOffset);
    // Serialize message field [heading]
    bufferOffset = _serializer.float32(obj.heading, buffer, bufferOffset);
    // Serialize message field [heading_uncertainty]
    bufferOffset = _serializer.float32(obj.heading_uncertainty, buffer, bufferOffset);
    // Serialize message field [fix_type]
    bufferOffset = _serializer.uint8(obj.fix_type, buffer, bufferOffset);
    // Serialize message field [rcv_1_valid]
    bufferOffset = _serializer.uint8(obj.rcv_1_valid, buffer, bufferOffset);
    // Serialize message field [rcv_2_valid]
    bufferOffset = _serializer.uint8(obj.rcv_2_valid, buffer, bufferOffset);
    // Serialize message field [antenna_offsets_valid]
    bufferOffset = _serializer.uint8(obj.antenna_offsets_valid, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GNSSDualAntennaStatus
    let len;
    let data = new GNSSDualAntennaStatus(null);
    // Deserialize message field [gps_tow]
    data.gps_tow = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading]
    data.heading = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading_uncertainty]
    data.heading_uncertainty = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [fix_type]
    data.fix_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [rcv_1_valid]
    data.rcv_1_valid = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [rcv_2_valid]
    data.rcv_2_valid = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [antenna_offsets_valid]
    data.antenna_offsets_valid = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/GNSSDualAntennaStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'efecf4f9bdf572f04f6f06ccc9c1095a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 gps_tow
    float32 heading
    float32 heading_uncertainty
    uint8   fix_type
    uint8   rcv_1_valid
    uint8   rcv_2_valid
    uint8   antenna_offsets_valid
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GNSSDualAntennaStatus(null);
    if (msg.gps_tow !== undefined) {
      resolved.gps_tow = msg.gps_tow;
    }
    else {
      resolved.gps_tow = 0.0
    }

    if (msg.heading !== undefined) {
      resolved.heading = msg.heading;
    }
    else {
      resolved.heading = 0.0
    }

    if (msg.heading_uncertainty !== undefined) {
      resolved.heading_uncertainty = msg.heading_uncertainty;
    }
    else {
      resolved.heading_uncertainty = 0.0
    }

    if (msg.fix_type !== undefined) {
      resolved.fix_type = msg.fix_type;
    }
    else {
      resolved.fix_type = 0
    }

    if (msg.rcv_1_valid !== undefined) {
      resolved.rcv_1_valid = msg.rcv_1_valid;
    }
    else {
      resolved.rcv_1_valid = 0
    }

    if (msg.rcv_2_valid !== undefined) {
      resolved.rcv_2_valid = msg.rcv_2_valid;
    }
    else {
      resolved.rcv_2_valid = 0
    }

    if (msg.antenna_offsets_valid !== undefined) {
      resolved.antenna_offsets_valid = msg.antenna_offsets_valid;
    }
    else {
      resolved.antenna_offsets_valid = 0
    }

    return resolved;
    }
};

module.exports = GNSSDualAntennaStatus;
