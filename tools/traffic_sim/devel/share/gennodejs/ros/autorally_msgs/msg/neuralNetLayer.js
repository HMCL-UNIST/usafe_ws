// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class neuralNetLayer {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.name = null;
      this.weight = null;
      this.bias = null;
    }
    else {
      if (initObj.hasOwnProperty('name')) {
        this.name = initObj.name
      }
      else {
        this.name = '';
      }
      if (initObj.hasOwnProperty('weight')) {
        this.weight = initObj.weight
      }
      else {
        this.weight = [];
      }
      if (initObj.hasOwnProperty('bias')) {
        this.bias = initObj.bias
      }
      else {
        this.bias = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type neuralNetLayer
    // Serialize message field [name]
    bufferOffset = _serializer.string(obj.name, buffer, bufferOffset);
    // Serialize message field [weight]
    bufferOffset = _arraySerializer.float32(obj.weight, buffer, bufferOffset, null);
    // Serialize message field [bias]
    bufferOffset = _arraySerializer.float32(obj.bias, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type neuralNetLayer
    let len;
    let data = new neuralNetLayer(null);
    // Deserialize message field [name]
    data.name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [weight]
    data.weight = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [bias]
    data.bias = _arrayDeserializer.float32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.name.length;
    length += 4 * object.weight.length;
    length += 4 * object.bias.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/neuralNetLayer';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5c7ae79f2ee4ffbb5044508aa41abced';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new neuralNetLayer(null);
    if (msg.name !== undefined) {
      resolved.name = msg.name;
    }
    else {
      resolved.name = ''
    }

    if (msg.weight !== undefined) {
      resolved.weight = msg.weight;
    }
    else {
      resolved.weight = []
    }

    if (msg.bias !== undefined) {
      resolved.bias = msg.bias;
    }
    else {
      resolved.bias = []
    }

    return resolved;
    }
};

module.exports = neuralNetLayer;
