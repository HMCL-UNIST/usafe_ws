// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let ObstacleStatus = require('./ObstacleStatus.js');
let ObstacleData = require('./ObstacleData.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class MobileyeInfo_obstacle {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.obstacle_status = null;
      this.obstacle_data = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('obstacle_status')) {
        this.obstacle_status = initObj.obstacle_status
      }
      else {
        this.obstacle_status = new ObstacleStatus();
      }
      if (initObj.hasOwnProperty('obstacle_data')) {
        this.obstacle_data = initObj.obstacle_data
      }
      else {
        this.obstacle_data = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MobileyeInfo_obstacle
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [obstacle_status]
    bufferOffset = ObstacleStatus.serialize(obj.obstacle_status, buffer, bufferOffset);
    // Serialize message field [obstacle_data]
    // Serialize the length for message field [obstacle_data]
    bufferOffset = _serializer.uint32(obj.obstacle_data.length, buffer, bufferOffset);
    obj.obstacle_data.forEach((val) => {
      bufferOffset = ObstacleData.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MobileyeInfo_obstacle
    let len;
    let data = new MobileyeInfo_obstacle(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [obstacle_status]
    data.obstacle_status = ObstacleStatus.deserialize(buffer, bufferOffset);
    // Deserialize message field [obstacle_data]
    // Deserialize array length for message field [obstacle_data]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.obstacle_data = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.obstacle_data[i] = ObstacleData.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 57 * object.obstacle_data.length;
    return length + 11;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/MobileyeInfo_obstacle';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '121aed0c94d2bb3256eb91e8d451839e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    ObstacleStatus obstacle_status
    ObstacleData[] obstacle_data
    
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
    MSG: mobileye_msgs/ObstacleStatus
    uint8 number_of_obstacles
    uint8 timestamp
    
    bool left_close_rang_cut_in
    bool right_close_rang_cut_in
    
    uint8 go
    bool close_car
    uint8 failsafe
    
    ================================================================================
    MSG: mobileye_msgs/ObstacleData
    uint8 obstacle_id
    float32 obstacle_position_x
    float32 obstacle_position_y
    float32 obstacle_relative_velocity_x
    
    uint8 obstacle_type
    uint8 obstacle_status
    bool obstacle_brake_lights
    uint8 cut_in_and_out
    uint8 blinker_info
    uint8 obstacle_valid
    
    float32 obstacle_length
    float32 obstacle_width
    uint8 obstacle_age
    uint8 obstacle_lane
    uint8 cipv_flag
    
    float32 radar_position_x
    float32 radar_velocity_x
    uint8 radar_match_confidence
    uint8 matched_radar_id
    
    float32 obstacle_angle_rate
    float32 obstacle_scale_change
    float32 obstacle_object_accel_x
    bool obstacle_replaced
    float32 obstacle_angle
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MobileyeInfo_obstacle(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.obstacle_status !== undefined) {
      resolved.obstacle_status = ObstacleStatus.Resolve(msg.obstacle_status)
    }
    else {
      resolved.obstacle_status = new ObstacleStatus()
    }

    if (msg.obstacle_data !== undefined) {
      resolved.obstacle_data = new Array(msg.obstacle_data.length);
      for (let i = 0; i < resolved.obstacle_data.length; ++i) {
        resolved.obstacle_data[i] = ObstacleData.Resolve(msg.obstacle_data[i]);
      }
    }
    else {
      resolved.obstacle_data = []
    }

    return resolved;
    }
};

module.exports = MobileyeInfo_obstacle;
