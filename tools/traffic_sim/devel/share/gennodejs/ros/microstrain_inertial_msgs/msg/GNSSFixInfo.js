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

class GNSSFixInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.fix_type = null;
      this.num_sv = null;
      this.sbas_used = null;
      this.dngss_used = null;
    }
    else {
      if (initObj.hasOwnProperty('fix_type')) {
        this.fix_type = initObj.fix_type
      }
      else {
        this.fix_type = 0;
      }
      if (initObj.hasOwnProperty('num_sv')) {
        this.num_sv = initObj.num_sv
      }
      else {
        this.num_sv = 0;
      }
      if (initObj.hasOwnProperty('sbas_used')) {
        this.sbas_used = initObj.sbas_used
      }
      else {
        this.sbas_used = false;
      }
      if (initObj.hasOwnProperty('dngss_used')) {
        this.dngss_used = initObj.dngss_used
      }
      else {
        this.dngss_used = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GNSSFixInfo
    // Serialize message field [fix_type]
    bufferOffset = _serializer.uint8(obj.fix_type, buffer, bufferOffset);
    // Serialize message field [num_sv]
    bufferOffset = _serializer.uint8(obj.num_sv, buffer, bufferOffset);
    // Serialize message field [sbas_used]
    bufferOffset = _serializer.bool(obj.sbas_used, buffer, bufferOffset);
    // Serialize message field [dngss_used]
    bufferOffset = _serializer.bool(obj.dngss_used, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GNSSFixInfo
    let len;
    let data = new GNSSFixInfo(null);
    // Deserialize message field [fix_type]
    data.fix_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [num_sv]
    data.num_sv = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sbas_used]
    data.sbas_used = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [dngss_used]
    data.dngss_used = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/GNSSFixInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cb3314532886b25255798400e78fc222';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 fix_type
    uint8 num_sv
    bool sbas_used
    bool dngss_used
    
    uint8 FIX_3D = 0
    uint8 FIX_2D = 1
    uint8 FIX_TIME_ONLY = 2
    uint8 FIX_NONE = 3
    uint8 FIX_INVALID = 4
    uint8 FIX_RTK_FLOAT = 5
    uint8 FIX_RTK_FIXED = 6
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GNSSFixInfo(null);
    if (msg.fix_type !== undefined) {
      resolved.fix_type = msg.fix_type;
    }
    else {
      resolved.fix_type = 0
    }

    if (msg.num_sv !== undefined) {
      resolved.num_sv = msg.num_sv;
    }
    else {
      resolved.num_sv = 0
    }

    if (msg.sbas_used !== undefined) {
      resolved.sbas_used = msg.sbas_used;
    }
    else {
      resolved.sbas_used = false
    }

    if (msg.dngss_used !== undefined) {
      resolved.dngss_used = msg.dngss_used;
    }
    else {
      resolved.dngss_used = false
    }

    return resolved;
    }
};

// Constants for message
GNSSFixInfo.Constants = {
  FIX_3D: 0,
  FIX_2D: 1,
  FIX_TIME_ONLY: 2,
  FIX_NONE: 3,
  FIX_INVALID: 4,
  FIX_RTK_FLOAT: 5,
  FIX_RTK_FIXED: 6,
}

module.exports = GNSSFixInfo;
