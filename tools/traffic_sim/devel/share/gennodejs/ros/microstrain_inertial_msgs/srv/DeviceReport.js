// Auto-generated. Do not edit!

// (in-package microstrain_inertial_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class DeviceReportRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DeviceReportRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DeviceReportRequest
    let len;
    let data = new DeviceReportRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/DeviceReportRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DeviceReportRequest(null);
    return resolved;
    }
};

class DeviceReportResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.model_name = null;
      this.model_number = null;
      this.serial_number = null;
      this.options = null;
      this.firmware_version = null;
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('model_name')) {
        this.model_name = initObj.model_name
      }
      else {
        this.model_name = '';
      }
      if (initObj.hasOwnProperty('model_number')) {
        this.model_number = initObj.model_number
      }
      else {
        this.model_number = '';
      }
      if (initObj.hasOwnProperty('serial_number')) {
        this.serial_number = initObj.serial_number
      }
      else {
        this.serial_number = '';
      }
      if (initObj.hasOwnProperty('options')) {
        this.options = initObj.options
      }
      else {
        this.options = '';
      }
      if (initObj.hasOwnProperty('firmware_version')) {
        this.firmware_version = initObj.firmware_version
      }
      else {
        this.firmware_version = '';
      }
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DeviceReportResponse
    // Serialize message field [model_name]
    bufferOffset = _serializer.string(obj.model_name, buffer, bufferOffset);
    // Serialize message field [model_number]
    bufferOffset = _serializer.string(obj.model_number, buffer, bufferOffset);
    // Serialize message field [serial_number]
    bufferOffset = _serializer.string(obj.serial_number, buffer, bufferOffset);
    // Serialize message field [options]
    bufferOffset = _serializer.string(obj.options, buffer, bufferOffset);
    // Serialize message field [firmware_version]
    bufferOffset = _serializer.string(obj.firmware_version, buffer, bufferOffset);
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DeviceReportResponse
    let len;
    let data = new DeviceReportResponse(null);
    // Deserialize message field [model_name]
    data.model_name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [model_number]
    data.model_number = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [serial_number]
    data.serial_number = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [options]
    data.options = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [firmware_version]
    data.firmware_version = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.model_name.length;
    length += object.model_number.length;
    length += object.serial_number.length;
    length += object.options.length;
    length += object.firmware_version.length;
    return length + 21;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/DeviceReportResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1306d0bab1f48bed0d0146c601d0ebe2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string model_name
    string model_number
    string serial_number
    string options
    string firmware_version
    bool success
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DeviceReportResponse(null);
    if (msg.model_name !== undefined) {
      resolved.model_name = msg.model_name;
    }
    else {
      resolved.model_name = ''
    }

    if (msg.model_number !== undefined) {
      resolved.model_number = msg.model_number;
    }
    else {
      resolved.model_number = ''
    }

    if (msg.serial_number !== undefined) {
      resolved.serial_number = msg.serial_number;
    }
    else {
      resolved.serial_number = ''
    }

    if (msg.options !== undefined) {
      resolved.options = msg.options;
    }
    else {
      resolved.options = ''
    }

    if (msg.firmware_version !== undefined) {
      resolved.firmware_version = msg.firmware_version;
    }
    else {
      resolved.firmware_version = ''
    }

    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: DeviceReportRequest,
  Response: DeviceReportResponse,
  md5sum() { return '1306d0bab1f48bed0d0146c601d0ebe2'; },
  datatype() { return 'microstrain_inertial_msgs/DeviceReport'; }
};
