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

class SetSoftIronMatrixRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.soft_iron_1 = null;
      this.soft_iron_2 = null;
      this.soft_iron_3 = null;
    }
    else {
      if (initObj.hasOwnProperty('soft_iron_1')) {
        this.soft_iron_1 = initObj.soft_iron_1
      }
      else {
        this.soft_iron_1 = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('soft_iron_2')) {
        this.soft_iron_2 = initObj.soft_iron_2
      }
      else {
        this.soft_iron_2 = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('soft_iron_3')) {
        this.soft_iron_3 = initObj.soft_iron_3
      }
      else {
        this.soft_iron_3 = new geometry_msgs.msg.Vector3();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetSoftIronMatrixRequest
    // Serialize message field [soft_iron_1]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.soft_iron_1, buffer, bufferOffset);
    // Serialize message field [soft_iron_2]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.soft_iron_2, buffer, bufferOffset);
    // Serialize message field [soft_iron_3]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.soft_iron_3, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetSoftIronMatrixRequest
    let len;
    let data = new SetSoftIronMatrixRequest(null);
    // Deserialize message field [soft_iron_1]
    data.soft_iron_1 = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [soft_iron_2]
    data.soft_iron_2 = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [soft_iron_3]
    data.soft_iron_3 = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 72;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetSoftIronMatrixRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7f7e0181b730797800abbfc3104a7df3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Vector3 soft_iron_1
    geometry_msgs/Vector3 soft_iron_2
    geometry_msgs/Vector3 soft_iron_3
    
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
    const resolved = new SetSoftIronMatrixRequest(null);
    if (msg.soft_iron_1 !== undefined) {
      resolved.soft_iron_1 = geometry_msgs.msg.Vector3.Resolve(msg.soft_iron_1)
    }
    else {
      resolved.soft_iron_1 = new geometry_msgs.msg.Vector3()
    }

    if (msg.soft_iron_2 !== undefined) {
      resolved.soft_iron_2 = geometry_msgs.msg.Vector3.Resolve(msg.soft_iron_2)
    }
    else {
      resolved.soft_iron_2 = new geometry_msgs.msg.Vector3()
    }

    if (msg.soft_iron_3 !== undefined) {
      resolved.soft_iron_3 = geometry_msgs.msg.Vector3.Resolve(msg.soft_iron_3)
    }
    else {
      resolved.soft_iron_3 = new geometry_msgs.msg.Vector3()
    }

    return resolved;
    }
};

class SetSoftIronMatrixResponse {
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
    // Serializes a message object of type SetSoftIronMatrixResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetSoftIronMatrixResponse
    let len;
    let data = new SetSoftIronMatrixResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/SetSoftIronMatrixResponse';
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
    const resolved = new SetSoftIronMatrixResponse(null);
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
  Request: SetSoftIronMatrixRequest,
  Response: SetSoftIronMatrixResponse,
  md5sum() { return 'ec07578ea93b9bb8b21d87ab5d1f0c81'; },
  datatype() { return 'microstrain_inertial_msgs/SetSoftIronMatrix'; }
};
