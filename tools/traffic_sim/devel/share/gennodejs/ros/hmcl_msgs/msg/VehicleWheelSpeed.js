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

class VehicleWheelSpeed {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.wheel_speed = null;
      this.fr = null;
      this.fl = null;
      this.rr = null;
      this.rl = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('wheel_speed')) {
        this.wheel_speed = initObj.wheel_speed
      }
      else {
        this.wheel_speed = 0.0;
      }
      if (initObj.hasOwnProperty('fr')) {
        this.fr = initObj.fr
      }
      else {
        this.fr = 0.0;
      }
      if (initObj.hasOwnProperty('fl')) {
        this.fl = initObj.fl
      }
      else {
        this.fl = 0.0;
      }
      if (initObj.hasOwnProperty('rr')) {
        this.rr = initObj.rr
      }
      else {
        this.rr = 0.0;
      }
      if (initObj.hasOwnProperty('rl')) {
        this.rl = initObj.rl
      }
      else {
        this.rl = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleWheelSpeed
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [wheel_speed]
    bufferOffset = _serializer.float64(obj.wheel_speed, buffer, bufferOffset);
    // Serialize message field [fr]
    bufferOffset = _serializer.float64(obj.fr, buffer, bufferOffset);
    // Serialize message field [fl]
    bufferOffset = _serializer.float64(obj.fl, buffer, bufferOffset);
    // Serialize message field [rr]
    bufferOffset = _serializer.float64(obj.rr, buffer, bufferOffset);
    // Serialize message field [rl]
    bufferOffset = _serializer.float64(obj.rl, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleWheelSpeed
    let len;
    let data = new VehicleWheelSpeed(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [wheel_speed]
    data.wheel_speed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fr]
    data.fr = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fl]
    data.fl = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rr]
    data.rr = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rl]
    data.rl = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 40;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/VehicleWheelSpeed';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'dd9bfec439fcf31963b917a79106fa20';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float64 wheel_speed
    float64 fr
    float64 fl
    float64 rr
    float64 rl
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
    const resolved = new VehicleWheelSpeed(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.wheel_speed !== undefined) {
      resolved.wheel_speed = msg.wheel_speed;
    }
    else {
      resolved.wheel_speed = 0.0
    }

    if (msg.fr !== undefined) {
      resolved.fr = msg.fr;
    }
    else {
      resolved.fr = 0.0
    }

    if (msg.fl !== undefined) {
      resolved.fl = msg.fl;
    }
    else {
      resolved.fl = 0.0
    }

    if (msg.rr !== undefined) {
      resolved.rr = msg.rr;
    }
    else {
      resolved.rr = 0.0
    }

    if (msg.rl !== undefined) {
      resolved.rl = msg.rl;
    }
    else {
      resolved.rl = 0.0
    }

    return resolved;
    }
};

module.exports = VehicleWheelSpeed;
