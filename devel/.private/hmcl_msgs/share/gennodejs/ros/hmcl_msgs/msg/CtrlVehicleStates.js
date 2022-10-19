// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class CtrlVehicleStates {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.delta = null;
      this.ey = null;
      this.epsi = null;
      this.dt = null;
      this.curvature = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('delta')) {
        this.delta = initObj.delta
      }
      else {
        this.delta = 0.0;
      }
      if (initObj.hasOwnProperty('ey')) {
        this.ey = initObj.ey
      }
      else {
        this.ey = 0.0;
      }
      if (initObj.hasOwnProperty('epsi')) {
        this.epsi = initObj.epsi
      }
      else {
        this.epsi = 0.0;
      }
      if (initObj.hasOwnProperty('dt')) {
        this.dt = initObj.dt
      }
      else {
        this.dt = 0.0;
      }
      if (initObj.hasOwnProperty('curvature')) {
        this.curvature = initObj.curvature
      }
      else {
        this.curvature = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CtrlVehicleStates
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [delta]
    bufferOffset = _serializer.float64(obj.delta, buffer, bufferOffset);
    // Serialize message field [ey]
    bufferOffset = _serializer.float64(obj.ey, buffer, bufferOffset);
    // Serialize message field [epsi]
    bufferOffset = _serializer.float64(obj.epsi, buffer, bufferOffset);
    // Serialize message field [dt]
    bufferOffset = _serializer.float64(obj.dt, buffer, bufferOffset);
    // Serialize message field [curvature]
    bufferOffset = _arraySerializer.float64(obj.curvature, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CtrlVehicleStates
    let len;
    let data = new CtrlVehicleStates(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [delta]
    data.delta = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ey]
    data.ey = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [epsi]
    data.epsi = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dt]
    data.dt = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [curvature]
    data.curvature = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 8 * object.curvature.length;
    return length + 36;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/CtrlVehicleStates';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '050afb3606d23886eff6dc2145e85984';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float64 delta
    float64 ey
    float64 epsi
    float64 dt
    float64[] curvature
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CtrlVehicleStates(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.delta !== undefined) {
      resolved.delta = msg.delta;
    }
    else {
      resolved.delta = 0.0
    }

    if (msg.ey !== undefined) {
      resolved.ey = msg.ey;
    }
    else {
      resolved.ey = 0.0
    }

    if (msg.epsi !== undefined) {
      resolved.epsi = msg.epsi;
    }
    else {
      resolved.epsi = 0.0
    }

    if (msg.dt !== undefined) {
      resolved.dt = msg.dt;
    }
    else {
      resolved.dt = 0.0
    }

    if (msg.curvature !== undefined) {
      resolved.curvature = msg.curvature;
    }
    else {
      resolved.curvature = []
    }

    return resolved;
    }
};

module.exports = CtrlVehicleStates;
