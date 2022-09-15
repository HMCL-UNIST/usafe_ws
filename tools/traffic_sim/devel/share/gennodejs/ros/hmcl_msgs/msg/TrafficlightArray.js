// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Trafficlight = require('./Trafficlight.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class TrafficlightArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.trafficlights = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('trafficlights')) {
        this.trafficlights = initObj.trafficlights
      }
      else {
        this.trafficlights = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TrafficlightArray
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [trafficlights]
    // Serialize the length for message field [trafficlights]
    bufferOffset = _serializer.uint32(obj.trafficlights.length, buffer, bufferOffset);
    obj.trafficlights.forEach((val) => {
      bufferOffset = Trafficlight.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TrafficlightArray
    let len;
    let data = new TrafficlightArray(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [trafficlights]
    // Deserialize array length for message field [trafficlights]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.trafficlights = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.trafficlights[i] = Trafficlight.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.trafficlights.forEach((val) => {
      length += Trafficlight.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/TrafficlightArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '06a8e2673b5b387a7023181a4c767949';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    Trafficlight[] trafficlights
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
    MSG: hmcl_msgs/Trafficlight
    Header header
    int32 id
    int32 lanelet_id
    geometry_msgs/Pose pose
    TrafficlightBulb left_light
    TrafficlightBulb straight_light
    TrafficlightBulb right_light
    bool valid_stop_line
    geometry_msgs/Pose stop_line
    ================================================================================
    MSG: geometry_msgs/Pose
    # A representation of pose in free space, composed of position and orientation. 
    Point position
    Quaternion orientation
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    ================================================================================
    MSG: geometry_msgs/Quaternion
    # This represents an orientation in free space in quaternion form.
    
    float64 x
    float64 y
    float64 z
    float64 w
    
    ================================================================================
    MSG: hmcl_msgs/TrafficlightBulb
    int32 id
    int32 light_status # 0 red, 1 green, 2 yellow 
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TrafficlightArray(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.trafficlights !== undefined) {
      resolved.trafficlights = new Array(msg.trafficlights.length);
      for (let i = 0; i < resolved.trafficlights.length; ++i) {
        resolved.trafficlights[i] = Trafficlight.Resolve(msg.trafficlights[i]);
      }
    }
    else {
      resolved.trafficlights = []
    }

    return resolved;
    }
};

module.exports = TrafficlightArray;
