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
let ReferencePoints = require('./ReferencePoints.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class LKA {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.left_lane = null;
      this.right_lane = null;
      this.reference_points = null;
      this.number_of_next_lane_markers = null;
      this.next_lane = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('left_lane')) {
        this.left_lane = initObj.left_lane
      }
      else {
        this.left_lane = new LKAlane();
      }
      if (initObj.hasOwnProperty('right_lane')) {
        this.right_lane = initObj.right_lane
      }
      else {
        this.right_lane = new LKAlane();
      }
      if (initObj.hasOwnProperty('reference_points')) {
        this.reference_points = initObj.reference_points
      }
      else {
        this.reference_points = new ReferencePoints();
      }
      if (initObj.hasOwnProperty('number_of_next_lane_markers')) {
        this.number_of_next_lane_markers = initObj.number_of_next_lane_markers
      }
      else {
        this.number_of_next_lane_markers = 0;
      }
      if (initObj.hasOwnProperty('next_lane')) {
        this.next_lane = initObj.next_lane
      }
      else {
        this.next_lane = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LKA
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [left_lane]
    bufferOffset = LKAlane.serialize(obj.left_lane, buffer, bufferOffset);
    // Serialize message field [right_lane]
    bufferOffset = LKAlane.serialize(obj.right_lane, buffer, bufferOffset);
    // Serialize message field [reference_points]
    bufferOffset = ReferencePoints.serialize(obj.reference_points, buffer, bufferOffset);
    // Serialize message field [number_of_next_lane_markers]
    bufferOffset = _serializer.uint8(obj.number_of_next_lane_markers, buffer, bufferOffset);
    // Serialize message field [next_lane]
    // Serialize the length for message field [next_lane]
    bufferOffset = _serializer.uint32(obj.next_lane.length, buffer, bufferOffset);
    obj.next_lane.forEach((val) => {
      bufferOffset = LKAlane.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LKA
    let len;
    let data = new LKA(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [left_lane]
    data.left_lane = LKAlane.deserialize(buffer, bufferOffset);
    // Deserialize message field [right_lane]
    data.right_lane = LKAlane.deserialize(buffer, bufferOffset);
    // Deserialize message field [reference_points]
    data.reference_points = ReferencePoints.deserialize(buffer, bufferOffset);
    // Deserialize message field [number_of_next_lane_markers]
    data.number_of_next_lane_markers = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [next_lane]
    // Deserialize array length for message field [next_lane]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.next_lane = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.next_lane[i] = LKAlane.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 28 * object.next_lane.length;
    return length + 79;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/LKA';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b5e3ba1f4afa652894372b06e4e02639';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    LKAlane left_lane
    LKAlane right_lane
    
    ReferencePoints reference_points
    
    uint8 number_of_next_lane_markers
    
    LKAlane[] next_lane
    
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
    
    ================================================================================
    MSG: mobileye_msgs/ReferencePoints
    float32 ref_point1_position
    float32 ref_point1_distance
    bool ref_point1_validity
    float32 ref_point2_position
    float32 ref_point2_distance
    bool ref_point2_validity
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LKA(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.left_lane !== undefined) {
      resolved.left_lane = LKAlane.Resolve(msg.left_lane)
    }
    else {
      resolved.left_lane = new LKAlane()
    }

    if (msg.right_lane !== undefined) {
      resolved.right_lane = LKAlane.Resolve(msg.right_lane)
    }
    else {
      resolved.right_lane = new LKAlane()
    }

    if (msg.reference_points !== undefined) {
      resolved.reference_points = ReferencePoints.Resolve(msg.reference_points)
    }
    else {
      resolved.reference_points = new ReferencePoints()
    }

    if (msg.number_of_next_lane_markers !== undefined) {
      resolved.number_of_next_lane_markers = msg.number_of_next_lane_markers;
    }
    else {
      resolved.number_of_next_lane_markers = 0
    }

    if (msg.next_lane !== undefined) {
      resolved.next_lane = new Array(msg.next_lane.length);
      for (let i = 0; i < resolved.next_lane.length; ++i) {
        resolved.next_lane[i] = LKAlane.Resolve(msg.next_lane[i]);
      }
    }
    else {
      resolved.next_lane = []
    }

    return resolved;
    }
};

module.exports = LKA;
