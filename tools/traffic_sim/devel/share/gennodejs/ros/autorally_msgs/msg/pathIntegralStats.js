// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let pathIntegralParams = require('./pathIntegralParams.js');
let lapStats = require('./lapStats.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class pathIntegralStats {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.tag = null;
      this.params = null;
      this.stats = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('tag')) {
        this.tag = initObj.tag
      }
      else {
        this.tag = '';
      }
      if (initObj.hasOwnProperty('params')) {
        this.params = initObj.params
      }
      else {
        this.params = new pathIntegralParams();
      }
      if (initObj.hasOwnProperty('stats')) {
        this.stats = initObj.stats
      }
      else {
        this.stats = new lapStats();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pathIntegralStats
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [tag]
    bufferOffset = _serializer.string(obj.tag, buffer, bufferOffset);
    // Serialize message field [params]
    bufferOffset = pathIntegralParams.serialize(obj.params, buffer, bufferOffset);
    // Serialize message field [stats]
    bufferOffset = lapStats.serialize(obj.stats, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pathIntegralStats
    let len;
    let data = new pathIntegralStats(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [tag]
    data.tag = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [params]
    data.params = pathIntegralParams.deserialize(buffer, bufferOffset);
    // Deserialize message field [stats]
    data.stats = lapStats.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += object.tag.length;
    length += pathIntegralParams.getMessageSize(object.params);
    return length + 36;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/pathIntegralStats';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cfb6f9017ebb92f4695492c3201de3c3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    string tag
    
    pathIntegralParams params
    lapStats stats
    
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
    MSG: autorally_msgs/pathIntegralParams
    int64 hz
    int64 num_timesteps
    int64 num_iters
    float64 gamma
    float64 init_steering
    float64 init_throttle
    float64 steering_var
    float64 throttle_var
    float64 max_throttle
    float64 speed_coefficient
    float64 track_coefficient
    float64 max_slip_angle
    float64 track_slop
    float64 crash_coeff
    string map_path
    float64 desired_speed
    ================================================================================
    MSG: autorally_msgs/lapStats
    int64 lap_number
    float64 lap_time
    float64 max_speed
    float64 max_slip
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pathIntegralStats(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.tag !== undefined) {
      resolved.tag = msg.tag;
    }
    else {
      resolved.tag = ''
    }

    if (msg.params !== undefined) {
      resolved.params = pathIntegralParams.Resolve(msg.params)
    }
    else {
      resolved.params = new pathIntegralParams()
    }

    if (msg.stats !== undefined) {
      resolved.stats = lapStats.Resolve(msg.stats)
    }
    else {
      resolved.stats = new lapStats()
    }

    return resolved;
    }
};

module.exports = pathIntegralStats;
