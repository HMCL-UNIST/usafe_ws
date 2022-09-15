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

let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class GetGyroBiasModelRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetGyroBiasModelRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetGyroBiasModelRequest
    let len;
    let data = new GetGyroBiasModelRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/GetGyroBiasModelRequest';
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
    const resolved = new GetGyroBiasModelRequest(null);
    return resolved;
    }
};

class GetGyroBiasModelResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.noise_vector = null;
      this.beta_vector = null;
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('noise_vector')) {
        this.noise_vector = initObj.noise_vector
      }
      else {
        this.noise_vector = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('beta_vector')) {
        this.beta_vector = initObj.beta_vector
      }
      else {
        this.beta_vector = new geometry_msgs.msg.Vector3();
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
    // Serializes a message object of type GetGyroBiasModelResponse
    // Serialize message field [noise_vector]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.noise_vector, buffer, bufferOffset);
    // Serialize message field [beta_vector]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.beta_vector, buffer, bufferOffset);
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetGyroBiasModelResponse
    let len;
    let data = new GetGyroBiasModelResponse(null);
    // Deserialize message field [noise_vector]
    data.noise_vector = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [beta_vector]
    data.beta_vector = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 49;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/GetGyroBiasModelResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b507c17fd666c16c0721d62595a47085';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Vector3 noise_vector
    geometry_msgs/Vector3 beta_vector
    bool success
    
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetGyroBiasModelResponse(null);
    if (msg.noise_vector !== undefined) {
      resolved.noise_vector = geometry_msgs.msg.Vector3.Resolve(msg.noise_vector)
    }
    else {
      resolved.noise_vector = new geometry_msgs.msg.Vector3()
    }

    if (msg.beta_vector !== undefined) {
      resolved.beta_vector = geometry_msgs.msg.Vector3.Resolve(msg.beta_vector)
    }
    else {
      resolved.beta_vector = new geometry_msgs.msg.Vector3()
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
  Request: GetGyroBiasModelRequest,
  Response: GetGyroBiasModelResponse,
  md5sum() { return 'b507c17fd666c16c0721d62595a47085'; },
  datatype() { return 'microstrain_inertial_msgs/GetGyroBiasModel'; }
};
