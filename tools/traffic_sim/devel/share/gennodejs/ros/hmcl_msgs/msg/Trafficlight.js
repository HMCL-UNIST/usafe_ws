// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let TrafficlightBulb = require('./TrafficlightBulb.js');
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Trafficlight {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.id = null;
      this.lanelet_id = null;
      this.pose = null;
      this.left_light = null;
      this.straight_light = null;
      this.right_light = null;
      this.valid_stop_line = null;
      this.stop_line = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('lanelet_id')) {
        this.lanelet_id = initObj.lanelet_id
      }
      else {
        this.lanelet_id = 0;
      }
      if (initObj.hasOwnProperty('pose')) {
        this.pose = initObj.pose
      }
      else {
        this.pose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('left_light')) {
        this.left_light = initObj.left_light
      }
      else {
        this.left_light = new TrafficlightBulb();
      }
      if (initObj.hasOwnProperty('straight_light')) {
        this.straight_light = initObj.straight_light
      }
      else {
        this.straight_light = new TrafficlightBulb();
      }
      if (initObj.hasOwnProperty('right_light')) {
        this.right_light = initObj.right_light
      }
      else {
        this.right_light = new TrafficlightBulb();
      }
      if (initObj.hasOwnProperty('valid_stop_line')) {
        this.valid_stop_line = initObj.valid_stop_line
      }
      else {
        this.valid_stop_line = false;
      }
      if (initObj.hasOwnProperty('stop_line')) {
        this.stop_line = initObj.stop_line
      }
      else {
        this.stop_line = new geometry_msgs.msg.Pose();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Trafficlight
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [id]
    bufferOffset = _serializer.int32(obj.id, buffer, bufferOffset);
    // Serialize message field [lanelet_id]
    bufferOffset = _serializer.int32(obj.lanelet_id, buffer, bufferOffset);
    // Serialize message field [pose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.pose, buffer, bufferOffset);
    // Serialize message field [left_light]
    bufferOffset = TrafficlightBulb.serialize(obj.left_light, buffer, bufferOffset);
    // Serialize message field [straight_light]
    bufferOffset = TrafficlightBulb.serialize(obj.straight_light, buffer, bufferOffset);
    // Serialize message field [right_light]
    bufferOffset = TrafficlightBulb.serialize(obj.right_light, buffer, bufferOffset);
    // Serialize message field [valid_stop_line]
    bufferOffset = _serializer.bool(obj.valid_stop_line, buffer, bufferOffset);
    // Serialize message field [stop_line]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.stop_line, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Trafficlight
    let len;
    let data = new Trafficlight(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [id]
    data.id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [lanelet_id]
    data.lanelet_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [pose]
    data.pose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [left_light]
    data.left_light = TrafficlightBulb.deserialize(buffer, bufferOffset);
    // Deserialize message field [straight_light]
    data.straight_light = TrafficlightBulb.deserialize(buffer, bufferOffset);
    // Deserialize message field [right_light]
    data.right_light = TrafficlightBulb.deserialize(buffer, bufferOffset);
    // Deserialize message field [valid_stop_line]
    data.valid_stop_line = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [stop_line]
    data.stop_line = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 145;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/Trafficlight';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a8bcc1bd70d49e0e7bdd9aa331d45dc1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new Trafficlight(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.lanelet_id !== undefined) {
      resolved.lanelet_id = msg.lanelet_id;
    }
    else {
      resolved.lanelet_id = 0
    }

    if (msg.pose !== undefined) {
      resolved.pose = geometry_msgs.msg.Pose.Resolve(msg.pose)
    }
    else {
      resolved.pose = new geometry_msgs.msg.Pose()
    }

    if (msg.left_light !== undefined) {
      resolved.left_light = TrafficlightBulb.Resolve(msg.left_light)
    }
    else {
      resolved.left_light = new TrafficlightBulb()
    }

    if (msg.straight_light !== undefined) {
      resolved.straight_light = TrafficlightBulb.Resolve(msg.straight_light)
    }
    else {
      resolved.straight_light = new TrafficlightBulb()
    }

    if (msg.right_light !== undefined) {
      resolved.right_light = TrafficlightBulb.Resolve(msg.right_light)
    }
    else {
      resolved.right_light = new TrafficlightBulb()
    }

    if (msg.valid_stop_line !== undefined) {
      resolved.valid_stop_line = msg.valid_stop_line;
    }
    else {
      resolved.valid_stop_line = false
    }

    if (msg.stop_line !== undefined) {
      resolved.stop_line = geometry_msgs.msg.Pose.Resolve(msg.stop_line)
    }
    else {
      resolved.stop_line = new geometry_msgs.msg.Pose()
    }

    return resolved;
    }
};

module.exports = Trafficlight;
