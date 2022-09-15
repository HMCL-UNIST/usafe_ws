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

class VehicleSCC {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.scc_mode = null;
      this.scc_takeover = null;
      this.acceleration = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('scc_mode')) {
        this.scc_mode = initObj.scc_mode
      }
      else {
        this.scc_mode = 0;
      }
      if (initObj.hasOwnProperty('scc_takeover')) {
        this.scc_takeover = initObj.scc_takeover
      }
      else {
        this.scc_takeover = 0;
      }
      if (initObj.hasOwnProperty('acceleration')) {
        this.acceleration = initObj.acceleration
      }
      else {
        this.acceleration = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleSCC
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [scc_mode]
    bufferOffset = _serializer.uint8(obj.scc_mode, buffer, bufferOffset);
    // Serialize message field [scc_takeover]
    bufferOffset = _serializer.uint8(obj.scc_takeover, buffer, bufferOffset);
    // Serialize message field [acceleration]
    bufferOffset = _serializer.float64(obj.acceleration, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleSCC
    let len;
    let data = new VehicleSCC(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [scc_mode]
    data.scc_mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [scc_takeover]
    data.scc_takeover = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [acceleration]
    data.acceleration = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 10;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/VehicleSCC';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0471adfa682d3742aa9adb20fb1e2600';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    # sccmode -> off       = 0
    # sccmode -> ready       = 1
    # sccmode -> on       = 2
    uint8 scc_mode
    # scc takeover -> off       = 0
    # scc takeover -> n      = 1
    uint8 scc_takeover
    float64 acceleration
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
    const resolved = new VehicleSCC(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.scc_mode !== undefined) {
      resolved.scc_mode = msg.scc_mode;
    }
    else {
      resolved.scc_mode = 0
    }

    if (msg.scc_takeover !== undefined) {
      resolved.scc_takeover = msg.scc_takeover;
    }
    else {
      resolved.scc_takeover = 0
    }

    if (msg.acceleration !== undefined) {
      resolved.acceleration = msg.acceleration;
    }
    else {
      resolved.acceleration = 0.0
    }

    return resolved;
    }
};

module.exports = VehicleSCC;
