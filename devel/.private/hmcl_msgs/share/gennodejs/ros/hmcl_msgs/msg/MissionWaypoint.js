// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class MissionWaypoint {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.start = null;
      this.end = null;
      this.remain = null;
    }
    else {
      if (initObj.hasOwnProperty('start')) {
        this.start = initObj.start
      }
      else {
        this.start = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('end')) {
        this.end = initObj.end
      }
      else {
        this.end = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('remain')) {
        this.remain = initObj.remain
      }
      else {
        this.remain = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MissionWaypoint
    // Serialize message field [start]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.start, buffer, bufferOffset);
    // Serialize message field [end]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.end, buffer, bufferOffset);
    // Serialize message field [remain]
    bufferOffset = _serializer.int32(obj.remain, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MissionWaypoint
    let len;
    let data = new MissionWaypoint(null);
    // Deserialize message field [start]
    data.start = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [end]
    data.end = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [remain]
    data.remain = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 52;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/MissionWaypoint';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '787e74dd4a3e0df7f1ef38d7abe84225';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # global id
    geometry_msgs/Point start
    geometry_msgs/Point end
    int32 remain
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MissionWaypoint(null);
    if (msg.start !== undefined) {
      resolved.start = geometry_msgs.msg.Point.Resolve(msg.start)
    }
    else {
      resolved.start = new geometry_msgs.msg.Point()
    }

    if (msg.end !== undefined) {
      resolved.end = geometry_msgs.msg.Point.Resolve(msg.end)
    }
    else {
      resolved.end = new geometry_msgs.msg.Point()
    }

    if (msg.remain !== undefined) {
      resolved.remain = msg.remain;
    }
    else {
      resolved.remain = 0
    }

    return resolved;
    }
};

module.exports = MissionWaypoint;
