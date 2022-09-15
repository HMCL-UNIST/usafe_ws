// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let SystemWarnings = require('./SystemWarnings.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class MobileyeInfo_system_warnings {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.system_warnings = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('system_warnings')) {
        this.system_warnings = initObj.system_warnings
      }
      else {
        this.system_warnings = new SystemWarnings();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MobileyeInfo_system_warnings
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [system_warnings]
    bufferOffset = SystemWarnings.serialize(obj.system_warnings, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MobileyeInfo_system_warnings
    let len;
    let data = new MobileyeInfo_system_warnings(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [system_warnings]
    data.system_warnings = SystemWarnings.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 23;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/MobileyeInfo_system_warnings';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e70b067bf40c41c403fb3be0e8758d41';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    SystemWarnings system_warnings
    
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
    MSG: mobileye_msgs/SystemWarnings
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
    const resolved = new MobileyeInfo_system_warnings(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.system_warnings !== undefined) {
      resolved.system_warnings = SystemWarnings.Resolve(msg.system_warnings)
    }
    else {
      resolved.system_warnings = new SystemWarnings()
    }

    return resolved;
    }
};

module.exports = MobileyeInfo_system_warnings;
