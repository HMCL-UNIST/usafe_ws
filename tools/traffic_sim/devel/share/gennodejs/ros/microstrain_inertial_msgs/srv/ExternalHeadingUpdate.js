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

class ExternalHeadingUpdateRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_tow = null;
      this.gps_week_number = null;
      this.heading_rad = null;
      this.heading_1sigma_rad = null;
      this.heading_type = null;
      this.use_time = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_tow')) {
        this.gps_tow = initObj.gps_tow
      }
      else {
        this.gps_tow = 0.0;
      }
      if (initObj.hasOwnProperty('gps_week_number')) {
        this.gps_week_number = initObj.gps_week_number
      }
      else {
        this.gps_week_number = 0;
      }
      if (initObj.hasOwnProperty('heading_rad')) {
        this.heading_rad = initObj.heading_rad
      }
      else {
        this.heading_rad = 0.0;
      }
      if (initObj.hasOwnProperty('heading_1sigma_rad')) {
        this.heading_1sigma_rad = initObj.heading_1sigma_rad
      }
      else {
        this.heading_1sigma_rad = 0.0;
      }
      if (initObj.hasOwnProperty('heading_type')) {
        this.heading_type = initObj.heading_type
      }
      else {
        this.heading_type = 0;
      }
      if (initObj.hasOwnProperty('use_time')) {
        this.use_time = initObj.use_time
      }
      else {
        this.use_time = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ExternalHeadingUpdateRequest
    // Serialize message field [gps_tow]
    bufferOffset = _serializer.float64(obj.gps_tow, buffer, bufferOffset);
    // Serialize message field [gps_week_number]
    bufferOffset = _serializer.uint16(obj.gps_week_number, buffer, bufferOffset);
    // Serialize message field [heading_rad]
    bufferOffset = _serializer.float32(obj.heading_rad, buffer, bufferOffset);
    // Serialize message field [heading_1sigma_rad]
    bufferOffset = _serializer.float32(obj.heading_1sigma_rad, buffer, bufferOffset);
    // Serialize message field [heading_type]
    bufferOffset = _serializer.uint16(obj.heading_type, buffer, bufferOffset);
    // Serialize message field [use_time]
    bufferOffset = _serializer.bool(obj.use_time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ExternalHeadingUpdateRequest
    let len;
    let data = new ExternalHeadingUpdateRequest(null);
    // Deserialize message field [gps_tow]
    data.gps_tow = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gps_week_number]
    data.gps_week_number = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [heading_rad]
    data.heading_rad = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading_1sigma_rad]
    data.heading_1sigma_rad = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading_type]
    data.heading_type = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [use_time]
    data.use_time = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 21;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/ExternalHeadingUpdateRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1ce6764f0be974407aa8df95cfdafba2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 gps_tow
    uint16  gps_week_number
    float32 heading_rad
    float32 heading_1sigma_rad
    uint16  heading_type
    bool    use_time
    uint16 HEADING_TYPE_TRUE      = 1  
    uint16 HEADING_TYPE_MAGNETIC  = 2  
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ExternalHeadingUpdateRequest(null);
    if (msg.gps_tow !== undefined) {
      resolved.gps_tow = msg.gps_tow;
    }
    else {
      resolved.gps_tow = 0.0
    }

    if (msg.gps_week_number !== undefined) {
      resolved.gps_week_number = msg.gps_week_number;
    }
    else {
      resolved.gps_week_number = 0
    }

    if (msg.heading_rad !== undefined) {
      resolved.heading_rad = msg.heading_rad;
    }
    else {
      resolved.heading_rad = 0.0
    }

    if (msg.heading_1sigma_rad !== undefined) {
      resolved.heading_1sigma_rad = msg.heading_1sigma_rad;
    }
    else {
      resolved.heading_1sigma_rad = 0.0
    }

    if (msg.heading_type !== undefined) {
      resolved.heading_type = msg.heading_type;
    }
    else {
      resolved.heading_type = 0
    }

    if (msg.use_time !== undefined) {
      resolved.use_time = msg.use_time;
    }
    else {
      resolved.use_time = false
    }

    return resolved;
    }
};

// Constants for message
ExternalHeadingUpdateRequest.Constants = {
  HEADING_TYPE_TRUE: 1,
  HEADING_TYPE_MAGNETIC: 2,
}

class ExternalHeadingUpdateResponse {
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
    // Serializes a message object of type ExternalHeadingUpdateResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ExternalHeadingUpdateResponse
    let len;
    let data = new ExternalHeadingUpdateResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/ExternalHeadingUpdateResponse';
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
    const resolved = new ExternalHeadingUpdateResponse(null);
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
  Request: ExternalHeadingUpdateRequest,
  Response: ExternalHeadingUpdateResponse,
  md5sum() { return 'c947f180cef8662c7c56b8c41afcba62'; },
  datatype() { return 'microstrain_inertial_msgs/ExternalHeadingUpdate'; }
};
