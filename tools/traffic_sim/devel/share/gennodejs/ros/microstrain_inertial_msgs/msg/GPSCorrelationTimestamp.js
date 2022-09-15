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

class GPSCorrelationTimestamp {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_tow = null;
      this.gps_week_number = null;
      this.timestamp_flags = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_tow')) {
        this.gps_tow = initObj.gps_tow
      }
      else {
        this.gps_tow = 0.0;
      }
      if (initObj.hasOwnProperty('gps_week_number')) {
        this.gps_week_number = initObj.gps_week_number
      }
      else {
        this.gps_week_number = 0;
      }
      if (initObj.hasOwnProperty('timestamp_flags')) {
        this.timestamp_flags = initObj.timestamp_flags
      }
      else {
        this.timestamp_flags = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GPSCorrelationTimestamp
    // Serialize message field [gps_tow]
    bufferOffset = _serializer.float64(obj.gps_tow, buffer, bufferOffset);
    // Serialize message field [gps_week_number]
    bufferOffset = _serializer.uint16(obj.gps_week_number, buffer, bufferOffset);
    // Serialize message field [timestamp_flags]
    bufferOffset = _serializer.uint16(obj.timestamp_flags, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GPSCorrelationTimestamp
    let len;
    let data = new GPSCorrelationTimestamp(null);
    // Deserialize message field [gps_tow]
    data.gps_tow = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gps_week_number]
    data.gps_week_number = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [timestamp_flags]
    data.timestamp_flags = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/GPSCorrelationTimestamp';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e4273ef053cace34fe47537c314897d4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 gps_tow
    uint16 gps_week_number
    uint16 timestamp_flags
    uint16 TIMESTAMP_FLAG_PPS_GOOD      = 1  #0b001
    uint16 TIMESTAMP_FLAG_GPS_REFRESH   = 2  #0b010
    uint16 TIMESTAMP_FLAG_GPS_INITALIZED= 4  #0b100
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GPSCorrelationTimestamp(null);
    if (msg.gps_tow !== undefined) {
      resolved.gps_tow = msg.gps_tow;
    }
    else {
      resolved.gps_tow = 0.0
    }

    if (msg.gps_week_number !== undefined) {
      resolved.gps_week_number = msg.gps_week_number;
    }
    else {
      resolved.gps_week_number = 0
    }

    if (msg.timestamp_flags !== undefined) {
      resolved.timestamp_flags = msg.timestamp_flags;
    }
    else {
      resolved.timestamp_flags = 0
    }

    return resolved;
    }
};

// Constants for message
GPSCorrelationTimestamp.Constants = {
  TIMESTAMP_FLAG_PPS_GOOD: 1,
  TIMESTAMP_FLAG_GPS_REFRESH: 2,
  TIMESTAMP_FLAG_GPS_INITALIZED: 4,
}

module.exports = GPSCorrelationTimestamp;
