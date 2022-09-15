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

class SetEstimationControlFlagsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.flags = null;
    }
    else {
      if (initObj.hasOwnProperty('flags')) {
        this.flags = initObj.flags
      }
      else {
        this.flags = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetEstimationControlFlagsRequest
    // Serialize message field [flags]
    bufferOffset = _serializer.int8(obj.flags, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetEstimationControlFlagsRequest
    let len;
    let data = new SetEstimationControlFlagsRequest(null);
    // Deserialize message field [flags]
    data.flags = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetEstimationControlFlagsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bcc1a9b0f97d53343afbd10c56611cf6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 GYRO_BIAS_ESTIMATION=1
    int8 HARD_IRON_AUTO_CALIBRATION=32
    int8 SOFT_IRON_AUTO_CALIBRATION=64
    int8 flags
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetEstimationControlFlagsRequest(null);
    if (msg.flags !== undefined) {
      resolved.flags = msg.flags;
    }
    else {
      resolved.flags = 0
    }

    return resolved;
    }
};

// Constants for message
SetEstimationControlFlagsRequest.Constants = {
  GYRO_BIAS_ESTIMATION: 1,
  HARD_IRON_AUTO_CALIBRATION: 32,
  SOFT_IRON_AUTO_CALIBRATION: 64,
}

class SetEstimationControlFlagsResponse {
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
    // Serializes a message object of type SetEstimationControlFlagsResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetEstimationControlFlagsResponse
    let len;
    let data = new SetEstimationControlFlagsResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetEstimationControlFlagsResponse';
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
    const resolved = new SetEstimationControlFlagsResponse(null);
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
  Request: SetEstimationControlFlagsRequest,
  Response: SetEstimationControlFlagsResponse,
  md5sum() { return '7efd025d74deaecd09a7eaf56530e702'; },
  datatype() { return 'microstrain_inertial_msgs/SetEstimationControlFlags'; }
};
