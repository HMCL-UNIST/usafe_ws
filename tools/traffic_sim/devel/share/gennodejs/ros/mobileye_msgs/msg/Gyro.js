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

class Gyro {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gyro_sensor_data_available = null;
      this.x_axis_data = null;
    }
    else {
      if (initObj.hasOwnProperty('gyro_sensor_data_available')) {
        this.gyro_sensor_data_available = initObj.gyro_sensor_data_available
      }
      else {
        this.gyro_sensor_data_available = false;
      }
      if (initObj.hasOwnProperty('x_axis_data')) {
        this.x_axis_data = initObj.x_axis_data
      }
      else {
        this.x_axis_data = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Gyro
    // Serialize message field [gyro_sensor_data_available]
    bufferOffset = _serializer.bool(obj.gyro_sensor_data_available, buffer, bufferOffset);
    // Serialize message field [x_axis_data]
    bufferOffset = _serializer.float32(obj.x_axis_data, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Gyro
    let len;
    let data = new Gyro(null);
    // Deserialize message field [gyro_sensor_data_available]
    data.gyro_sensor_data_available = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [x_axis_data]
    data.x_axis_data = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/Gyro';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '15689ec0f13fb1c15689a8f65d1fda0b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool gyro_sensor_data_available
    float32 x_axis_data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Gyro(null);
    if (msg.gyro_sensor_data_available !== undefined) {
      resolved.gyro_sensor_data_available = msg.gyro_sensor_data_available;
    }
    else {
      resolved.gyro_sensor_data_available = false
    }

    if (msg.x_axis_data !== undefined) {
      resolved.x_axis_data = msg.x_axis_data;
    }
    else {
      resolved.x_axis_data = 0.0
    }

    return resolved;
    }
};

module.exports = Gyro;
