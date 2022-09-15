// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class wheelSpeeds {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.lfSpeed = null;
      this.rfSpeed = null;
      this.lbSpeed = null;
      this.rbSpeed = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('lfSpeed')) {
        this.lfSpeed = initObj.lfSpeed
      }
      else {
        this.lfSpeed = 0.0;
      }
      if (initObj.hasOwnProperty('rfSpeed')) {
        this.rfSpeed = initObj.rfSpeed
      }
      else {
        this.rfSpeed = 0.0;
      }
      if (initObj.hasOwnProperty('lbSpeed')) {
        this.lbSpeed = initObj.lbSpeed
      }
      else {
        this.lbSpeed = 0.0;
      }
      if (initObj.hasOwnProperty('rbSpeed')) {
        this.rbSpeed = initObj.rbSpeed
      }
      else {
        this.rbSpeed = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type wheelSpeeds
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [lfSpeed]
    bufferOffset = _serializer.float64(obj.lfSpeed, buffer, bufferOffset);
    // Serialize message field [rfSpeed]
    bufferOffset = _serializer.float64(obj.rfSpeed, buffer, bufferOffset);
    // Serialize message field [lbSpeed]
    bufferOffset = _serializer.float64(obj.lbSpeed, buffer, bufferOffset);
    // Serialize message field [rbSpeed]
    bufferOffset = _serializer.float64(obj.rbSpeed, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type wheelSpeeds
    let len;
    let data = new wheelSpeeds(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [lfSpeed]
    data.lfSpeed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rfSpeed]
    data.rfSpeed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [lbSpeed]
    data.lbSpeed = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rbSpeed]
    data.rbSpeed = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/wheelSpeeds';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c5c4a96a4e17d91e72a2f7397af4d720';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float64 lfSpeed
    float64 rfSpeed
    float64 lbSpeed
    float64 rbSpeed
    
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
    const resolved = new wheelSpeeds(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.lfSpeed !== undefined) {
      resolved.lfSpeed = msg.lfSpeed;
    }
    else {
      resolved.lfSpeed = 0.0
    }

    if (msg.rfSpeed !== undefined) {
      resolved.rfSpeed = msg.rfSpeed;
    }
    else {
      resolved.rfSpeed = 0.0
    }

    if (msg.lbSpeed !== undefined) {
      resolved.lbSpeed = msg.lbSpeed;
    }
    else {
      resolved.lbSpeed = 0.0
    }

    if (msg.rbSpeed !== undefined) {
      resolved.rbSpeed = msg.rbSpeed;
    }
    else {
      resolved.rbSpeed = 0.0
    }

    return resolved;
    }
};

module.exports = wheelSpeeds;
