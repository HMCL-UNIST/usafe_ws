// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Waypoint = require('./Waypoint.js');
let Trafficlight = require('./Trafficlight.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Lane {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.lane_id = null;
      this.lane_change_flag = null;
      this.speed_limit = null;
      this.waypoints = null;
      this.trafficlights = null;
      this.speedbumps = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('lane_id')) {
        this.lane_id = initObj.lane_id
      }
      else {
        this.lane_id = 0;
      }
      if (initObj.hasOwnProperty('lane_change_flag')) {
        this.lane_change_flag = initObj.lane_change_flag
      }
      else {
        this.lane_change_flag = false;
      }
      if (initObj.hasOwnProperty('speed_limit')) {
        this.speed_limit = initObj.speed_limit
      }
      else {
        this.speed_limit = 0.0;
      }
      if (initObj.hasOwnProperty('waypoints')) {
        this.waypoints = initObj.waypoints
      }
      else {
        this.waypoints = [];
      }
      if (initObj.hasOwnProperty('trafficlights')) {
        this.trafficlights = initObj.trafficlights
      }
      else {
        this.trafficlights = [];
      }
      if (initObj.hasOwnProperty('speedbumps')) {
        this.speedbumps = initObj.speedbumps
      }
      else {
        this.speedbumps = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Lane
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [lane_id]
    bufferOffset = _serializer.int32(obj.lane_id, buffer, bufferOffset);
    // Serialize message field [lane_change_flag]
    bufferOffset = _serializer.bool(obj.lane_change_flag, buffer, bufferOffset);
    // Serialize message field [speed_limit]
    bufferOffset = _serializer.float32(obj.speed_limit, buffer, bufferOffset);
    // Serialize message field [waypoints]
    // Serialize the length for message field [waypoints]
    bufferOffset = _serializer.uint32(obj.waypoints.length, buffer, bufferOffset);
    obj.waypoints.forEach((val) => {
      bufferOffset = Waypoint.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [trafficlights]
    // Serialize the length for message field [trafficlights]
    bufferOffset = _serializer.uint32(obj.trafficlights.length, buffer, bufferOffset);
    obj.trafficlights.forEach((val) => {
      bufferOffset = Trafficlight.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [speedbumps]
    // Serialize the length for message field [speedbumps]
    bufferOffset = _serializer.uint32(obj.speedbumps.length, buffer, bufferOffset);
    obj.speedbumps.forEach((val) => {
      bufferOffset = Waypoint.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Lane
    let len;
    let data = new Lane(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [lane_id]
    data.lane_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [lane_change_flag]
    data.lane_change_flag = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [speed_limit]
    data.speed_limit = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [waypoints]
    // Deserialize array length for message field [waypoints]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.waypoints = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.waypoints[i] = Waypoint.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [trafficlights]
    // Deserialize array length for message field [trafficlights]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.trafficlights = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.trafficlights[i] = Trafficlight.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [speedbumps]
    // Deserialize array length for message field [speedbumps]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.speedbumps = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.speedbumps[i] = Waypoint.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.waypoints.forEach((val) => {
      length += Waypoint.getMessageSize(val);
    });
    object.trafficlights.forEach((val) => {
      length += Trafficlight.getMessageSize(val);
    });
    object.speedbumps.forEach((val) => {
      length += Waypoint.getMessageSize(val);
    });
    return length + 21;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/Lane';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '923d2c4fa02093b723f235ff09a4673f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    int32 lane_id
    bool lane_change_flag
    float32 speed_limit 
    Waypoint[] waypoints
    Trafficlight[] trafficlights
    Waypoint[] speedbumps
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
    MSG: hmcl_msgs/Waypoint
    # global id
    int32 gid 
    # local id
    int32 lid
    geometry_msgs/PoseStamped pose
    geometry_msgs/TwistStamped twist
    uint32 lane_id
    ================================================================================
    MSG: geometry_msgs/PoseStamped
    # A Pose with reference coordinate frame and timestamp
    Header header
    Pose pose
    
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
    MSG: geometry_msgs/TwistStamped
    # A twist with reference coordinate frame and timestamp
    Header header
    Twist twist
    
    ================================================================================
    MSG: geometry_msgs/Twist
    # This expresses velocity in free space broken into its linear and angular parts.
    Vector3  linear
    Vector3  angular
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
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
    const resolved = new Lane(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.lane_id !== undefined) {
      resolved.lane_id = msg.lane_id;
    }
    else {
      resolved.lane_id = 0
    }

    if (msg.lane_change_flag !== undefined) {
      resolved.lane_change_flag = msg.lane_change_flag;
    }
    else {
      resolved.lane_change_flag = false
    }

    if (msg.speed_limit !== undefined) {
      resolved.speed_limit = msg.speed_limit;
    }
    else {
      resolved.speed_limit = 0.0
    }

    if (msg.waypoints !== undefined) {
      resolved.waypoints = new Array(msg.waypoints.length);
      for (let i = 0; i < resolved.waypoints.length; ++i) {
        resolved.waypoints[i] = Waypoint.Resolve(msg.waypoints[i]);
      }
    }
    else {
      resolved.waypoints = []
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

    if (msg.speedbumps !== undefined) {
      resolved.speedbumps = new Array(msg.speedbumps.length);
      for (let i = 0; i < resolved.speedbumps.length; ++i) {
        resolved.speedbumps[i] = Waypoint.Resolve(msg.speedbumps[i]);
      }
    }
    else {
      resolved.speedbumps = []
    }

    return resolved;
    }
};

module.exports = Lane;
