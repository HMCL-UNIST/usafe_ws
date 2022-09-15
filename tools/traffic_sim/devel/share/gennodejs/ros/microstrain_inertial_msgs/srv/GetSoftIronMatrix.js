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

class GetSoftIronMatrixRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetSoftIronMatrixRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetSoftIronMatrixRequest
    let len;
    let data = new GetSoftIronMatrixRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/GetSoftIronMatrixRequest';
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
    const resolved = new GetSoftIronMatrixRequest(null);
    return resolved;
    }
};

class GetSoftIronMatrixResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.soft_iron_1 = null;
      this.soft_iron_2 = null;
      this.soft_iron_3 = null;
      this.success = null;
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
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetSoftIronMatrixResponse
    // Serialize message field [soft_iron_1]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.soft_iron_1, buffer, bufferOffset);
    // Serialize message field [soft_iron_2]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.soft_iron_2, buffer, bufferOffset);
    // Serialize message field [soft_iron_3]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.soft_iron_3, buffer, bufferOffset);
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetSoftIronMatrixResponse
    let len;
    let data = new GetSoftIronMatrixResponse(null);
    // Deserialize message field [soft_iron_1]
    data.soft_iron_1 = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [soft_iron_2]
    data.soft_iron_2 = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [soft_iron_3]
    data.soft_iron_3 = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 73;
  }

  static datatype() {
    // Returns string type for a service object
    return 'microstrain_inertial_msgs/GetSoftIronMatrixResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '028ca441ebb3dc279988e1ab8c3f73cf';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Vector3 soft_iron_1
    geometry_msgs/Vector3 soft_iron_2
    geometry_msgs/Vector3 soft_iron_3
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
    const resolved = new GetSoftIronMatrixResponse(null);
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
  Request: GetSoftIronMatrixRequest,
  Response: GetSoftIronMatrixResponse,
  md5sum() { return '028ca441ebb3dc279988e1ab8c3f73cf'; },
  datatype() { return 'microstrain_inertial_msgs/GetSoftIronMatrix'; }
};
