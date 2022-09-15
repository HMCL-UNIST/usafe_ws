// Auto-generated. Do not edit!

// (in-package microstrain_inertial_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetAccelBiasModelRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.noise_vector = null;
      this.beta_vector = null;
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
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetAccelBiasModelRequest
    // Serialize message field [noise_vector]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.noise_vector, buffer, bufferOffset);
    // Serialize message field [beta_vector]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.beta_vector, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetAccelBiasModelRequest
    let len;
    let data = new SetAccelBiasModelRequest(null);
    // Deserialize message field [noise_vector]
    data.noise_vector = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [beta_vector]
    data.beta_vector = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 48;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetAccelBiasModelRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '89f0f0cd6d52eb4058eea24a6259c0d1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Vector3 noise_vector
    geometry_msgs/Vector3 beta_vector
    
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
    const resolved = new SetAccelBiasModelRequest(null);
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

    return resolved;
    }
};

class SetAccelBiasModelResponse {
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
    // Serializes a message object of type SetAccelBiasModelResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetAccelBiasModelResponse
    let len;
    let data = new SetAccelBiasModelResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetAccelBiasModelResponse';
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
    const resolved = new SetAccelBiasModelResponse(null);
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
  Request: SetAccelBiasModelRequest,
  Response: SetAccelBiasModelResponse,
  md5sum() { return 'f3cdd18c97add875be98974ab1d992b9'; },
  datatype() { return 'microstrain_inertial_msgs/SetAccelBiasModel'; }
};
