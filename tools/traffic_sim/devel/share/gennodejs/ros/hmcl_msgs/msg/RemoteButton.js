// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class RemoteButton {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.button1 = null;
      this.button2 = null;
      this.button3 = null;
    }
    else {
      if (initObj.hasOwnProperty('button1')) {
        this.button1 = initObj.button1
      }
      else {
        this.button1 = 0;
      }
      if (initObj.hasOwnProperty('button2')) {
        this.button2 = initObj.button2
      }
      else {
        this.button2 = 0;
      }
      if (initObj.hasOwnProperty('button3')) {
        this.button3 = initObj.button3
      }
      else {
        this.button3 = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RemoteButton
    // Serialize message field [button1]
    bufferOffset = _serializer.uint8(obj.button1, buffer, bufferOffset);
    // Serialize message field [button2]
    bufferOffset = _serializer.uint8(obj.button2, buffer, bufferOffset);
    // Serialize message field [button3]
    bufferOffset = _serializer.uint8(obj.button3, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RemoteButton
    let len;
    let data = new RemoteButton(null);
    // Deserialize message field [button1]
    data.button1 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [button2]
    data.button2 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [button3]
    data.button3 = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 3;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/RemoteButton';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e0761a580fd3c116926a0b07701fd25f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # wirelessbutton -> 0 push off, 1 -> push on
    uint8 button1
    uint8 button2
    uint8 button3
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RemoteButton(null);
    if (msg.button1 !== undefined) {
      resolved.button1 = msg.button1;
    }
    else {
      resolved.button1 = 0
    }

    if (msg.button2 !== undefined) {
      resolved.button2 = msg.button2;
    }
    else {
      resolved.button2 = 0
    }

    if (msg.button3 !== undefined) {
      resolved.button3 = msg.button3;
    }
    else {
      resolved.button3 = 0
    }

    return resolved;
    }
};

module.exports = RemoteButton;
