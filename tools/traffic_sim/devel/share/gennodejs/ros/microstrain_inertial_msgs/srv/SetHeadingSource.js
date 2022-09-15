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

class SetHeadingSourceRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.heading_source = null;
    }
    else {
      if (initObj.hasOwnProperty('heading_source')) {
        this.heading_source = initObj.heading_source
      }
      else {
        this.heading_source = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetHeadingSourceRequest
    // Serialize message field [heading_source]
    bufferOffset = _serializer.int8(obj.heading_source, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetHeadingSourceRequest
    let len;
    let data = new SetHeadingSourceRequest(null);
    // Deserialize message field [heading_source]
    data.heading_source = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetHeadingSourceRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c645f74f48e2efd41041018e43ce0ff2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 heading_source
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetHeadingSourceRequest(null);
    if (msg.heading_source !== undefined) {
      resolved.heading_source = msg.heading_source;
    }
    else {
      resolved.heading_source = 0
    }

    return resolved;
    }
};

class SetHeadingSourceResponse {
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
    // Serializes a message object of type SetHeadingSourceResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetHeadingSourceResponse
    let len;
    let data = new SetHeadingSourceResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetHeadingSourceResponse';
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
    const resolved = new SetHeadingSourceResponse(null);
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
  Request: SetHeadingSourceRequest,
  Response: SetHeadingSourceResponse,
  md5sum() { return 'e390de146ace4f3cbedb9445dd2ef6f7'; },
  datatype() { return 'microstrain_inertial_msgs/SetHeadingSource'; }
};
