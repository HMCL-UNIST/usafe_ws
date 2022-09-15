// Auto-generated. Do not edit!

// (in-package microstrain_inertial_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let GPSCorrelationTimestamp = require('./GPSCorrelationTimestamp.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class GPSCorrelationTimestampStamped {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.gps_cor = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('gps_cor')) {
        this.gps_cor = initObj.gps_cor
      }
      else {
        this.gps_cor = new GPSCorrelationTimestamp();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GPSCorrelationTimestampStamped
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [gps_cor]
    bufferOffset = GPSCorrelationTimestamp.serialize(obj.gps_cor, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GPSCorrelationTimestampStamped
    let len;
    let data = new GPSCorrelationTimestampStamped(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [gps_cor]
    data.gps_cor = GPSCorrelationTimestamp.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/GPSCorrelationTimestampStamped';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '879558b5dd82252329a1da11593c6fee';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    GPSCorrelationTimestamp gps_cor
    
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: microstrain_inertial_msgs/GPSCorrelationTimestamp
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
    const resolved = new GPSCorrelationTimestampStamped(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.gps_cor !== undefined) {
      resolved.gps_cor = GPSCorrelationTimestamp.Resolve(msg.gps_cor)
    }
    else {
      resolved.gps_cor = new GPSCorrelationTimestamp()
    }

    return resolved;
    }
};

module.exports = GPSCorrelationTimestampStamped;
