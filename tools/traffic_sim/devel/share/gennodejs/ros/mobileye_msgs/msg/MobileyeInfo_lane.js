// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Lane = require('./Lane.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class MobileyeInfo_lane {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.lane = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('lane')) {
        this.lane = initObj.lane
      }
      else {
        this.lane = new Lane();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MobileyeInfo_lane
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [lane]
    bufferOffset = Lane.serialize(obj.lane, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MobileyeInfo_lane
    let len;
    let data = new MobileyeInfo_lane(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [lane]
    data.lane = Lane.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 19;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/MobileyeInfo_lane';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2167664513fbefa299d496bdde8fbd05';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    Lane lane
    
    
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
    MSG: mobileye_msgs/Lane
    float32 lane_curvature
    float32 lane_heading
    
    bool ca
    float32 pitch_angle
    float32 yaw_angle
    
    bool right_ldw_availability
    bool left_ldw_availability
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MobileyeInfo_lane(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.lane !== undefined) {
      resolved.lane = Lane.Resolve(msg.lane)
    }
    else {
      resolved.lane = new Lane()
    }

    return resolved;
    }
};

module.exports = MobileyeInfo_lane;
