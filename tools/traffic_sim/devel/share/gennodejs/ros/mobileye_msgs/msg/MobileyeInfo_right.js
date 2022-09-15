// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let LKAlane = require('./LKAlane.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class MobileyeInfo_right {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.right_lane = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('right_lane')) {
        this.right_lane = initObj.right_lane
      }
      else {
        this.right_lane = new LKAlane();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MobileyeInfo_right
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [right_lane]
    bufferOffset = LKAlane.serialize(obj.right_lane, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MobileyeInfo_right
    let len;
    let data = new MobileyeInfo_right(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [right_lane]
    data.right_lane = LKAlane.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/MobileyeInfo_right';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f403053ee52387e5c63c01fd8df420e3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    LKAlane right_lane
    
    
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
    MSG: mobileye_msgs/LKAlane
    uint8 lane_type
    uint8 quality
    uint8 model_degree
    
    float32 position_parameter_c0
    float32 curvature_parameter_c2
    float32 curvature_derivative_c3
    float32 width_marking
    
    float32 heading_angle_parameter_c1
    float32 view_range
    bool view_range_availability
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MobileyeInfo_right(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.right_lane !== undefined) {
      resolved.right_lane = LKAlane.Resolve(msg.right_lane)
    }
    else {
      resolved.right_lane = new LKAlane()
    }

    return resolved;
    }
};

module.exports = MobileyeInfo_right;
