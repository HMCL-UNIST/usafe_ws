// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let TSR = require('./TSR.js');
let TSRVisionOnlySign = require('./TSRVisionOnlySign.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class MobileyeInfo_tsr {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.tsr = null;
      this.tsr_vision_only = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('tsr')) {
        this.tsr = initObj.tsr
      }
      else {
        this.tsr = [];
      }
      if (initObj.hasOwnProperty('tsr_vision_only')) {
        this.tsr_vision_only = initObj.tsr_vision_only
      }
      else {
        this.tsr_vision_only = new TSRVisionOnlySign();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MobileyeInfo_tsr
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [tsr]
    // Serialize the length for message field [tsr]
    bufferOffset = _serializer.uint32(obj.tsr.length, buffer, bufferOffset);
    obj.tsr.forEach((val) => {
      bufferOffset = TSR.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [tsr_vision_only]
    bufferOffset = TSRVisionOnlySign.serialize(obj.tsr_vision_only, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MobileyeInfo_tsr
    let len;
    let data = new MobileyeInfo_tsr(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [tsr]
    // Deserialize array length for message field [tsr]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.tsr = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.tsr[i] = TSR.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [tsr_vision_only]
    data.tsr_vision_only = TSRVisionOnlySign.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 15 * object.tsr.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/MobileyeInfo_tsr';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '12ef6ff06090fe03856140fe8fe950f9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    TSR[] tsr
    TSRVisionOnlySign tsr_vision_only
    
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
    MSG: mobileye_msgs/TSR
    uint8 vision_only_sign_type
    uint8 supplementary_sign_type
    float32 sign_position_x
    float32 sign_position_y
    float32 sign_position_z
    uint8 filter_type
    ================================================================================
    MSG: mobileye_msgs/TSRVisionOnlySign
    uint8 vision_only_sign_type_display_1
    uint8 vision_only_sign_type_display_2
    uint8 vision_only_sign_type_display_3
    uint8 vision_only_sign_type_display_4
    
    uint8 supplementary_sign_type_display_1
    uint8 supplementary_sign_type_display_2
    uint8 supplementary_sign_type_display_3
    uint8 supplementary_sign_type_display_4
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MobileyeInfo_tsr(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.tsr !== undefined) {
      resolved.tsr = new Array(msg.tsr.length);
      for (let i = 0; i < resolved.tsr.length; ++i) {
        resolved.tsr[i] = TSR.Resolve(msg.tsr[i]);
      }
    }
    else {
      resolved.tsr = []
    }

    if (msg.tsr_vision_only !== undefined) {
      resolved.tsr_vision_only = TSRVisionOnlySign.Resolve(msg.tsr_vision_only)
    }
    else {
      resolved.tsr_vision_only = new TSRVisionOnlySign()
    }

    return resolved;
    }
};

module.exports = MobileyeInfo_tsr;
