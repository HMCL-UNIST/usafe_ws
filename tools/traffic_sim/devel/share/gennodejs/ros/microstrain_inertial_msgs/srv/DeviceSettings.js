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

class DeviceSettingsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.function_selector = null;
    }
    else {
      if (initObj.hasOwnProperty('function_selector')) {
        this.function_selector = initObj.function_selector
      }
      else {
        this.function_selector = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DeviceSettingsRequest
    // Serialize message field [function_selector]
    bufferOffset = _serializer.uint8(obj.function_selector, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DeviceSettingsRequest
    let len;
    let data = new DeviceSettingsRequest(null);
    // Deserialize message field [function_selector]
    data.function_selector = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/DeviceSettingsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8af3ea6ac2cd14406fd4b4301d1878d2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 function_selector
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DeviceSettingsRequest(null);
    if (msg.function_selector !== undefined) {
      resolved.function_selector = msg.function_selector;
    }
    else {
      resolved.function_selector = 0
    }

    return resolved;
    }
};

class DeviceSettingsResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DeviceSettingsResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DeviceSettingsResponse
    let len;
    let data = new DeviceSettingsResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/DeviceSettingsResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '358e233cde0c8a8bcfea4ce193f8fc15';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool success
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DeviceSettingsResponse(null);
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
  Request: DeviceSettingsRequest,
  Response: DeviceSettingsResponse,
  md5sum() { return 'a5738bbd08ff2569a7464cd41b071fc3'; },
  datatype() { return 'microstrain_inertial_msgs/DeviceSettings'; }
};
