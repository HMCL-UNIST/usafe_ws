// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let neuralNetLayer = require('./neuralNetLayer.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class neuralNetModel {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.network = null;
      this.numLayers = null;
      this.structure = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('network')) {
        this.network = initObj.network
      }
      else {
        this.network = [];
      }
      if (initObj.hasOwnProperty('numLayers')) {
        this.numLayers = initObj.numLayers
      }
      else {
        this.numLayers = 0;
      }
      if (initObj.hasOwnProperty('structure')) {
        this.structure = initObj.structure
      }
      else {
        this.structure = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type neuralNetModel
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [network]
    // Serialize the length for message field [network]
    bufferOffset = _serializer.uint32(obj.network.length, buffer, bufferOffset);
    obj.network.forEach((val) => {
      bufferOffset = neuralNetLayer.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [numLayers]
    bufferOffset = _serializer.int32(obj.numLayers, buffer, bufferOffset);
    // Serialize message field [structure]
    bufferOffset = _arraySerializer.int32(obj.structure, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type neuralNetModel
    let len;
    let data = new neuralNetModel(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [network]
    // Deserialize array length for message field [network]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.network = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.network[i] = neuralNetLayer.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [numLayers]
    data.numLayers = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [structure]
    data.structure = _arrayDeserializer.int32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.network.forEach((val) => {
      length += neuralNetLayer.getMessageSize(val);
    });
    length += 4 * object.structure.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/neuralNetModel';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3c8c8380b1c9bb122f00005291fff0d0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    neuralNetLayer[] network
    int32 numLayers
    int32[] structure
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
    MSG: autorally_msgs/neuralNetLayer
    string name
    float32[] weight
    float32[] bias
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new neuralNetModel(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.network !== undefined) {
      resolved.network = new Array(msg.network.length);
      for (let i = 0; i < resolved.network.length; ++i) {
        resolved.network[i] = neuralNetLayer.Resolve(msg.network[i]);
      }
    }
    else {
      resolved.network = []
    }

    if (msg.numLayers !== undefined) {
      resolved.numLayers = msg.numLayers;
    }
    else {
      resolved.numLayers = 0
    }

    if (msg.structure !== undefined) {
      resolved.structure = msg.structure;
    }
    else {
      resolved.structure = []
    }

    return resolved;
    }
};

module.exports = neuralNetModel;
