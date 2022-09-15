// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class ObstacleStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.number_of_obstacles = null;
      this.timestamp = null;
      this.left_close_rang_cut_in = null;
      this.right_close_rang_cut_in = null;
      this.go = null;
      this.close_car = null;
      this.failsafe = null;
    }
    else {
      if (initObj.hasOwnProperty('number_of_obstacles')) {
        this.number_of_obstacles = initObj.number_of_obstacles
      }
      else {
        this.number_of_obstacles = 0;
      }
      if (initObj.hasOwnProperty('timestamp')) {
        this.timestamp = initObj.timestamp
      }
      else {
        this.timestamp = 0;
      }
      if (initObj.hasOwnProperty('left_close_rang_cut_in')) {
        this.left_close_rang_cut_in = initObj.left_close_rang_cut_in
      }
      else {
        this.left_close_rang_cut_in = false;
      }
      if (initObj.hasOwnProperty('right_close_rang_cut_in')) {
        this.right_close_rang_cut_in = initObj.right_close_rang_cut_in
      }
      else {
        this.right_close_rang_cut_in = false;
      }
      if (initObj.hasOwnProperty('go')) {
        this.go = initObj.go
      }
      else {
        this.go = 0;
      }
      if (initObj.hasOwnProperty('close_car')) {
        this.close_car = initObj.close_car
      }
      else {
        this.close_car = false;
      }
      if (initObj.hasOwnProperty('failsafe')) {
        this.failsafe = initObj.failsafe
      }
      else {
        this.failsafe = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ObstacleStatus
    // Serialize message field [number_of_obstacles]
    bufferOffset = _serializer.uint8(obj.number_of_obstacles, buffer, bufferOffset);
    // Serialize message field [timestamp]
    bufferOffset = _serializer.uint8(obj.timestamp, buffer, bufferOffset);
    // Serialize message field [left_close_rang_cut_in]
    bufferOffset = _serializer.bool(obj.left_close_rang_cut_in, buffer, bufferOffset);
    // Serialize message field [right_close_rang_cut_in]
    bufferOffset = _serializer.bool(obj.right_close_rang_cut_in, buffer, bufferOffset);
    // Serialize message field [go]
    bufferOffset = _serializer.uint8(obj.go, buffer, bufferOffset);
    // Serialize message field [close_car]
    bufferOffset = _serializer.bool(obj.close_car, buffer, bufferOffset);
    // Serialize message field [failsafe]
    bufferOffset = _serializer.uint8(obj.failsafe, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ObstacleStatus
    let len;
    let data = new ObstacleStatus(null);
    // Deserialize message field [number_of_obstacles]
    data.number_of_obstacles = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [timestamp]
    data.timestamp = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [left_close_rang_cut_in]
    data.left_close_rang_cut_in = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [right_close_rang_cut_in]
    data.right_close_rang_cut_in = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [go]
    data.go = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [close_car]
    data.close_car = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [failsafe]
    data.failsafe = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 7;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/ObstacleStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3b9b8b37869bebe9592f8765c69bab28';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 number_of_obstacles
    uint8 timestamp
    
    bool left_close_rang_cut_in
    bool right_close_rang_cut_in
    
    uint8 go
    bool close_car
    uint8 failsafe
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ObstacleStatus(null);
    if (msg.number_of_obstacles !== undefined) {
      resolved.number_of_obstacles = msg.number_of_obstacles;
    }
    else {
      resolved.number_of_obstacles = 0
    }

    if (msg.timestamp !== undefined) {
      resolved.timestamp = msg.timestamp;
    }
    else {
      resolved.timestamp = 0
    }

    if (msg.left_close_rang_cut_in !== undefined) {
      resolved.left_close_rang_cut_in = msg.left_close_rang_cut_in;
    }
    else {
      resolved.left_close_rang_cut_in = false
    }

    if (msg.right_close_rang_cut_in !== undefined) {
      resolved.right_close_rang_cut_in = msg.right_close_rang_cut_in;
    }
    else {
      resolved.right_close_rang_cut_in = false
    }

    if (msg.go !== undefined) {
      resolved.go = msg.go;
    }
    else {
      resolved.go = 0
    }

    if (msg.close_car !== undefined) {
      resolved.close_car = msg.close_car;
    }
    else {
      resolved.close_car = false
    }

    if (msg.failsafe !== undefined) {
      resolved.failsafe = msg.failsafe;
    }
    else {
      resolved.failsafe = 0
    }

    return resolved;
    }
};

module.exports = ObstacleStatus;
