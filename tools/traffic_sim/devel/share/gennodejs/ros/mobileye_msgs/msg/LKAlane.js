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

class LKAlane {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.lane_type = null;
      this.quality = null;
      this.model_degree = null;
      this.position_parameter_c0 = null;
      this.curvature_parameter_c2 = null;
      this.curvature_derivative_c3 = null;
      this.width_marking = null;
      this.heading_angle_parameter_c1 = null;
      this.view_range = null;
      this.view_range_availability = null;
    }
    else {
      if (initObj.hasOwnProperty('lane_type')) {
        this.lane_type = initObj.lane_type
      }
      else {
        this.lane_type = 0;
      }
      if (initObj.hasOwnProperty('quality')) {
        this.quality = initObj.quality
      }
      else {
        this.quality = 0;
      }
      if (initObj.hasOwnProperty('model_degree')) {
        this.model_degree = initObj.model_degree
      }
      else {
        this.model_degree = 0;
      }
      if (initObj.hasOwnProperty('position_parameter_c0')) {
        this.position_parameter_c0 = initObj.position_parameter_c0
      }
      else {
        this.position_parameter_c0 = 0.0;
      }
      if (initObj.hasOwnProperty('curvature_parameter_c2')) {
        this.curvature_parameter_c2 = initObj.curvature_parameter_c2
      }
      else {
        this.curvature_parameter_c2 = 0.0;
      }
      if (initObj.hasOwnProperty('curvature_derivative_c3')) {
        this.curvature_derivative_c3 = initObj.curvature_derivative_c3
      }
      else {
        this.curvature_derivative_c3 = 0.0;
      }
      if (initObj.hasOwnProperty('width_marking')) {
        this.width_marking = initObj.width_marking
      }
      else {
        this.width_marking = 0.0;
      }
      if (initObj.hasOwnProperty('heading_angle_parameter_c1')) {
        this.heading_angle_parameter_c1 = initObj.heading_angle_parameter_c1
      }
      else {
        this.heading_angle_parameter_c1 = 0.0;
      }
      if (initObj.hasOwnProperty('view_range')) {
        this.view_range = initObj.view_range
      }
      else {
        this.view_range = 0.0;
      }
      if (initObj.hasOwnProperty('view_range_availability')) {
        this.view_range_availability = initObj.view_range_availability
      }
      else {
        this.view_range_availability = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LKAlane
    // Serialize message field [lane_type]
    bufferOffset = _serializer.uint8(obj.lane_type, buffer, bufferOffset);
    // Serialize message field [quality]
    bufferOffset = _serializer.uint8(obj.quality, buffer, bufferOffset);
    // Serialize message field [model_degree]
    bufferOffset = _serializer.uint8(obj.model_degree, buffer, bufferOffset);
    // Serialize message field [position_parameter_c0]
    bufferOffset = _serializer.float32(obj.position_parameter_c0, buffer, bufferOffset);
    // Serialize message field [curvature_parameter_c2]
    bufferOffset = _serializer.float32(obj.curvature_parameter_c2, buffer, bufferOffset);
    // Serialize message field [curvature_derivative_c3]
    bufferOffset = _serializer.float32(obj.curvature_derivative_c3, buffer, bufferOffset);
    // Serialize message field [width_marking]
    bufferOffset = _serializer.float32(obj.width_marking, buffer, bufferOffset);
    // Serialize message field [heading_angle_parameter_c1]
    bufferOffset = _serializer.float32(obj.heading_angle_parameter_c1, buffer, bufferOffset);
    // Serialize message field [view_range]
    bufferOffset = _serializer.float32(obj.view_range, buffer, bufferOffset);
    // Serialize message field [view_range_availability]
    bufferOffset = _serializer.bool(obj.view_range_availability, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LKAlane
    let len;
    let data = new LKAlane(null);
    // Deserialize message field [lane_type]
    data.lane_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [quality]
    data.quality = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [model_degree]
    data.model_degree = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [position_parameter_c0]
    data.position_parameter_c0 = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [curvature_parameter_c2]
    data.curvature_parameter_c2 = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [curvature_derivative_c3]
    data.curvature_derivative_c3 = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [width_marking]
    data.width_marking = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading_angle_parameter_c1]
    data.heading_angle_parameter_c1 = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [view_range]
    data.view_range = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [view_range_availability]
    data.view_range_availability = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/LKAlane';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7b414dd7d22f435b47d4035bf3d8fde4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 lane_type
    uint8 quality
    uint8 model_degree
    
    float32 position_parameter_c0
    float32 curvature_parameter_c2
    float32 curvature_derivative_c3
    float32 width_marking
    
    float32 heading_angle_parameter_c1
    float32 view_range
    bool view_range_availability
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LKAlane(null);
    if (msg.lane_type !== undefined) {
      resolved.lane_type = msg.lane_type;
    }
    else {
      resolved.lane_type = 0
    }

    if (msg.quality !== undefined) {
      resolved.quality = msg.quality;
    }
    else {
      resolved.quality = 0
    }

    if (msg.model_degree !== undefined) {
      resolved.model_degree = msg.model_degree;
    }
    else {
      resolved.model_degree = 0
    }

    if (msg.position_parameter_c0 !== undefined) {
      resolved.position_parameter_c0 = msg.position_parameter_c0;
    }
    else {
      resolved.position_parameter_c0 = 0.0
    }

    if (msg.curvature_parameter_c2 !== undefined) {
      resolved.curvature_parameter_c2 = msg.curvature_parameter_c2;
    }
    else {
      resolved.curvature_parameter_c2 = 0.0
    }

    if (msg.curvature_derivative_c3 !== undefined) {
      resolved.curvature_derivative_c3 = msg.curvature_derivative_c3;
    }
    else {
      resolved.curvature_derivative_c3 = 0.0
    }

    if (msg.width_marking !== undefined) {
      resolved.width_marking = msg.width_marking;
    }
    else {
      resolved.width_marking = 0.0
    }

    if (msg.heading_angle_parameter_c1 !== undefined) {
      resolved.heading_angle_parameter_c1 = msg.heading_angle_parameter_c1;
    }
    else {
      resolved.heading_angle_parameter_c1 = 0.0
    }

    if (msg.view_range !== undefined) {
      resolved.view_range = msg.view_range;
    }
    else {
      resolved.view_range = 0.0
    }

    if (msg.view_range_availability !== undefined) {
      resolved.view_range_availability = msg.view_range_availability;
    }
    else {
      resolved.view_range_availability = false
    }

    return resolved;
    }
};

module.exports = LKAlane;
