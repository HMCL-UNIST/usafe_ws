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

class ObstacleData {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.obstacle_id = null;
      this.obstacle_position_x = null;
      this.obstacle_position_y = null;
      this.obstacle_relative_velocity_x = null;
      this.obstacle_type = null;
      this.obstacle_status = null;
      this.obstacle_brake_lights = null;
      this.cut_in_and_out = null;
      this.blinker_info = null;
      this.obstacle_valid = null;
      this.obstacle_length = null;
      this.obstacle_width = null;
      this.obstacle_age = null;
      this.obstacle_lane = null;
      this.cipv_flag = null;
      this.radar_position_x = null;
      this.radar_velocity_x = null;
      this.radar_match_confidence = null;
      this.matched_radar_id = null;
      this.obstacle_angle_rate = null;
      this.obstacle_scale_change = null;
      this.obstacle_object_accel_x = null;
      this.obstacle_replaced = null;
      this.obstacle_angle = null;
    }
    else {
      if (initObj.hasOwnProperty('obstacle_id')) {
        this.obstacle_id = initObj.obstacle_id
      }
      else {
        this.obstacle_id = 0;
      }
      if (initObj.hasOwnProperty('obstacle_position_x')) {
        this.obstacle_position_x = initObj.obstacle_position_x
      }
      else {
        this.obstacle_position_x = 0.0;
      }
      if (initObj.hasOwnProperty('obstacle_position_y')) {
        this.obstacle_position_y = initObj.obstacle_position_y
      }
      else {
        this.obstacle_position_y = 0.0;
      }
      if (initObj.hasOwnProperty('obstacle_relative_velocity_x')) {
        this.obstacle_relative_velocity_x = initObj.obstacle_relative_velocity_x
      }
      else {
        this.obstacle_relative_velocity_x = 0.0;
      }
      if (initObj.hasOwnProperty('obstacle_type')) {
        this.obstacle_type = initObj.obstacle_type
      }
      else {
        this.obstacle_type = 0;
      }
      if (initObj.hasOwnProperty('obstacle_status')) {
        this.obstacle_status = initObj.obstacle_status
      }
      else {
        this.obstacle_status = 0;
      }
      if (initObj.hasOwnProperty('obstacle_brake_lights')) {
        this.obstacle_brake_lights = initObj.obstacle_brake_lights
      }
      else {
        this.obstacle_brake_lights = false;
      }
      if (initObj.hasOwnProperty('cut_in_and_out')) {
        this.cut_in_and_out = initObj.cut_in_and_out
      }
      else {
        this.cut_in_and_out = 0;
      }
      if (initObj.hasOwnProperty('blinker_info')) {
        this.blinker_info = initObj.blinker_info
      }
      else {
        this.blinker_info = 0;
      }
      if (initObj.hasOwnProperty('obstacle_valid')) {
        this.obstacle_valid = initObj.obstacle_valid
      }
      else {
        this.obstacle_valid = 0;
      }
      if (initObj.hasOwnProperty('obstacle_length')) {
        this.obstacle_length = initObj.obstacle_length
      }
      else {
        this.obstacle_length = 0.0;
      }
      if (initObj.hasOwnProperty('obstacle_width')) {
        this.obstacle_width = initObj.obstacle_width
      }
      else {
        this.obstacle_width = 0.0;
      }
      if (initObj.hasOwnProperty('obstacle_age')) {
        this.obstacle_age = initObj.obstacle_age
      }
      else {
        this.obstacle_age = 0;
      }
      if (initObj.hasOwnProperty('obstacle_lane')) {
        this.obstacle_lane = initObj.obstacle_lane
      }
      else {
        this.obstacle_lane = 0;
      }
      if (initObj.hasOwnProperty('cipv_flag')) {
        this.cipv_flag = initObj.cipv_flag
      }
      else {
        this.cipv_flag = 0;
      }
      if (initObj.hasOwnProperty('radar_position_x')) {
        this.radar_position_x = initObj.radar_position_x
      }
      else {
        this.radar_position_x = 0.0;
      }
      if (initObj.hasOwnProperty('radar_velocity_x')) {
        this.radar_velocity_x = initObj.radar_velocity_x
      }
      else {
        this.radar_velocity_x = 0.0;
      }
      if (initObj.hasOwnProperty('radar_match_confidence')) {
        this.radar_match_confidence = initObj.radar_match_confidence
      }
      else {
        this.radar_match_confidence = 0;
      }
      if (initObj.hasOwnProperty('matched_radar_id')) {
        this.matched_radar_id = initObj.matched_radar_id
      }
      else {
        this.matched_radar_id = 0;
      }
      if (initObj.hasOwnProperty('obstacle_angle_rate')) {
        this.obstacle_angle_rate = initObj.obstacle_angle_rate
      }
      else {
        this.obstacle_angle_rate = 0.0;
      }
      if (initObj.hasOwnProperty('obstacle_scale_change')) {
        this.obstacle_scale_change = initObj.obstacle_scale_change
      }
      else {
        this.obstacle_scale_change = 0.0;
      }
      if (initObj.hasOwnProperty('obstacle_object_accel_x')) {
        this.obstacle_object_accel_x = initObj.obstacle_object_accel_x
      }
      else {
        this.obstacle_object_accel_x = 0.0;
      }
      if (initObj.hasOwnProperty('obstacle_replaced')) {
        this.obstacle_replaced = initObj.obstacle_replaced
      }
      else {
        this.obstacle_replaced = false;
      }
      if (initObj.hasOwnProperty('obstacle_angle')) {
        this.obstacle_angle = initObj.obstacle_angle
      }
      else {
        this.obstacle_angle = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ObstacleData
    // Serialize message field [obstacle_id]
    bufferOffset = _serializer.uint8(obj.obstacle_id, buffer, bufferOffset);
    // Serialize message field [obstacle_position_x]
    bufferOffset = _serializer.float32(obj.obstacle_position_x, buffer, bufferOffset);
    // Serialize message field [obstacle_position_y]
    bufferOffset = _serializer.float32(obj.obstacle_position_y, buffer, bufferOffset);
    // Serialize message field [obstacle_relative_velocity_x]
    bufferOffset = _serializer.float32(obj.obstacle_relative_velocity_x, buffer, bufferOffset);
    // Serialize message field [obstacle_type]
    bufferOffset = _serializer.uint8(obj.obstacle_type, buffer, bufferOffset);
    // Serialize message field [obstacle_status]
    bufferOffset = _serializer.uint8(obj.obstacle_status, buffer, bufferOffset);
    // Serialize message field [obstacle_brake_lights]
    bufferOffset = _serializer.bool(obj.obstacle_brake_lights, buffer, bufferOffset);
    // Serialize message field [cut_in_and_out]
    bufferOffset = _serializer.uint8(obj.cut_in_and_out, buffer, bufferOffset);
    // Serialize message field [blinker_info]
    bufferOffset = _serializer.uint8(obj.blinker_info, buffer, bufferOffset);
    // Serialize message field [obstacle_valid]
    bufferOffset = _serializer.uint8(obj.obstacle_valid, buffer, bufferOffset);
    // Serialize message field [obstacle_length]
    bufferOffset = _serializer.float32(obj.obstacle_length, buffer, bufferOffset);
    // Serialize message field [obstacle_width]
    bufferOffset = _serializer.float32(obj.obstacle_width, buffer, bufferOffset);
    // Serialize message field [obstacle_age]
    bufferOffset = _serializer.uint8(obj.obstacle_age, buffer, bufferOffset);
    // Serialize message field [obstacle_lane]
    bufferOffset = _serializer.uint8(obj.obstacle_lane, buffer, bufferOffset);
    // Serialize message field [cipv_flag]
    bufferOffset = _serializer.uint8(obj.cipv_flag, buffer, bufferOffset);
    // Serialize message field [radar_position_x]
    bufferOffset = _serializer.float32(obj.radar_position_x, buffer, bufferOffset);
    // Serialize message field [radar_velocity_x]
    bufferOffset = _serializer.float32(obj.radar_velocity_x, buffer, bufferOffset);
    // Serialize message field [radar_match_confidence]
    bufferOffset = _serializer.uint8(obj.radar_match_confidence, buffer, bufferOffset);
    // Serialize message field [matched_radar_id]
    bufferOffset = _serializer.uint8(obj.matched_radar_id, buffer, bufferOffset);
    // Serialize message field [obstacle_angle_rate]
    bufferOffset = _serializer.float32(obj.obstacle_angle_rate, buffer, bufferOffset);
    // Serialize message field [obstacle_scale_change]
    bufferOffset = _serializer.float32(obj.obstacle_scale_change, buffer, bufferOffset);
    // Serialize message field [obstacle_object_accel_x]
    bufferOffset = _serializer.float32(obj.obstacle_object_accel_x, buffer, bufferOffset);
    // Serialize message field [obstacle_replaced]
    bufferOffset = _serializer.bool(obj.obstacle_replaced, buffer, bufferOffset);
    // Serialize message field [obstacle_angle]
    bufferOffset = _serializer.float32(obj.obstacle_angle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ObstacleData
    let len;
    let data = new ObstacleData(null);
    // Deserialize message field [obstacle_id]
    data.obstacle_id = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [obstacle_position_x]
    data.obstacle_position_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [obstacle_position_y]
    data.obstacle_position_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [obstacle_relative_velocity_x]
    data.obstacle_relative_velocity_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [obstacle_type]
    data.obstacle_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [obstacle_status]
    data.obstacle_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [obstacle_brake_lights]
    data.obstacle_brake_lights = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [cut_in_and_out]
    data.cut_in_and_out = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [blinker_info]
    data.blinker_info = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [obstacle_valid]
    data.obstacle_valid = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [obstacle_length]
    data.obstacle_length = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [obstacle_width]
    data.obstacle_width = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [obstacle_age]
    data.obstacle_age = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [obstacle_lane]
    data.obstacle_lane = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [cipv_flag]
    data.cipv_flag = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [radar_position_x]
    data.radar_position_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [radar_velocity_x]
    data.radar_velocity_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [radar_match_confidence]
    data.radar_match_confidence = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [matched_radar_id]
    data.matched_radar_id = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [obstacle_angle_rate]
    data.obstacle_angle_rate = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [obstacle_scale_change]
    data.obstacle_scale_change = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [obstacle_object_accel_x]
    data.obstacle_object_accel_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [obstacle_replaced]
    data.obstacle_replaced = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [obstacle_angle]
    data.obstacle_angle = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 57;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/ObstacleData';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0f95ac1fed6a2bf8af234e0196c675c0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 obstacle_id
    float32 obstacle_position_x
    float32 obstacle_position_y
    float32 obstacle_relative_velocity_x
    
    uint8 obstacle_type
    uint8 obstacle_status
    bool obstacle_brake_lights
    uint8 cut_in_and_out
    uint8 blinker_info
    uint8 obstacle_valid
    
    float32 obstacle_length
    float32 obstacle_width
    uint8 obstacle_age
    uint8 obstacle_lane
    uint8 cipv_flag
    
    float32 radar_position_x
    float32 radar_velocity_x
    uint8 radar_match_confidence
    uint8 matched_radar_id
    
    float32 obstacle_angle_rate
    float32 obstacle_scale_change
    float32 obstacle_object_accel_x
    bool obstacle_replaced
    float32 obstacle_angle
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ObstacleData(null);
    if (msg.obstacle_id !== undefined) {
      resolved.obstacle_id = msg.obstacle_id;
    }
    else {
      resolved.obstacle_id = 0
    }

    if (msg.obstacle_position_x !== undefined) {
      resolved.obstacle_position_x = msg.obstacle_position_x;
    }
    else {
      resolved.obstacle_position_x = 0.0
    }

    if (msg.obstacle_position_y !== undefined) {
      resolved.obstacle_position_y = msg.obstacle_position_y;
    }
    else {
      resolved.obstacle_position_y = 0.0
    }

    if (msg.obstacle_relative_velocity_x !== undefined) {
      resolved.obstacle_relative_velocity_x = msg.obstacle_relative_velocity_x;
    }
    else {
      resolved.obstacle_relative_velocity_x = 0.0
    }

    if (msg.obstacle_type !== undefined) {
      resolved.obstacle_type = msg.obstacle_type;
    }
    else {
      resolved.obstacle_type = 0
    }

    if (msg.obstacle_status !== undefined) {
      resolved.obstacle_status = msg.obstacle_status;
    }
    else {
      resolved.obstacle_status = 0
    }

    if (msg.obstacle_brake_lights !== undefined) {
      resolved.obstacle_brake_lights = msg.obstacle_brake_lights;
    }
    else {
      resolved.obstacle_brake_lights = false
    }

    if (msg.cut_in_and_out !== undefined) {
      resolved.cut_in_and_out = msg.cut_in_and_out;
    }
    else {
      resolved.cut_in_and_out = 0
    }

    if (msg.blinker_info !== undefined) {
      resolved.blinker_info = msg.blinker_info;
    }
    else {
      resolved.blinker_info = 0
    }

    if (msg.obstacle_valid !== undefined) {
      resolved.obstacle_valid = msg.obstacle_valid;
    }
    else {
      resolved.obstacle_valid = 0
    }

    if (msg.obstacle_length !== undefined) {
      resolved.obstacle_length = msg.obstacle_length;
    }
    else {
      resolved.obstacle_length = 0.0
    }

    if (msg.obstacle_width !== undefined) {
      resolved.obstacle_width = msg.obstacle_width;
    }
    else {
      resolved.obstacle_width = 0.0
    }

    if (msg.obstacle_age !== undefined) {
      resolved.obstacle_age = msg.obstacle_age;
    }
    else {
      resolved.obstacle_age = 0
    }

    if (msg.obstacle_lane !== undefined) {
      resolved.obstacle_lane = msg.obstacle_lane;
    }
    else {
      resolved.obstacle_lane = 0
    }

    if (msg.cipv_flag !== undefined) {
      resolved.cipv_flag = msg.cipv_flag;
    }
    else {
      resolved.cipv_flag = 0
    }

    if (msg.radar_position_x !== undefined) {
      resolved.radar_position_x = msg.radar_position_x;
    }
    else {
      resolved.radar_position_x = 0.0
    }

    if (msg.radar_velocity_x !== undefined) {
      resolved.radar_velocity_x = msg.radar_velocity_x;
    }
    else {
      resolved.radar_velocity_x = 0.0
    }

    if (msg.radar_match_confidence !== undefined) {
      resolved.radar_match_confidence = msg.radar_match_confidence;
    }
    else {
      resolved.radar_match_confidence = 0
    }

    if (msg.matched_radar_id !== undefined) {
      resolved.matched_radar_id = msg.matched_radar_id;
    }
    else {
      resolved.matched_radar_id = 0
    }

    if (msg.obstacle_angle_rate !== undefined) {
      resolved.obstacle_angle_rate = msg.obstacle_angle_rate;
    }
    else {
      resolved.obstacle_angle_rate = 0.0
    }

    if (msg.obstacle_scale_change !== undefined) {
      resolved.obstacle_scale_change = msg.obstacle_scale_change;
    }
    else {
      resolved.obstacle_scale_change = 0.0
    }

    if (msg.obstacle_object_accel_x !== undefined) {
      resolved.obstacle_object_accel_x = msg.obstacle_object_accel_x;
    }
    else {
      resolved.obstacle_object_accel_x = 0.0
    }

    if (msg.obstacle_replaced !== undefined) {
      resolved.obstacle_replaced = msg.obstacle_replaced;
    }
    else {
      resolved.obstacle_replaced = false
    }

    if (msg.obstacle_angle !== undefined) {
      resolved.obstacle_angle = msg.obstacle_angle;
    }
    else {
      resolved.obstacle_angle = 0.0
    }

    return resolved;
    }
};

module.exports = ObstacleData;
