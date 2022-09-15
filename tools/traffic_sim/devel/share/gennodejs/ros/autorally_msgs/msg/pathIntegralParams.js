// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class pathIntegralParams {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.hz = null;
      this.num_timesteps = null;
      this.num_iters = null;
      this.gamma = null;
      this.init_steering = null;
      this.init_throttle = null;
      this.steering_var = null;
      this.throttle_var = null;
      this.max_throttle = null;
      this.speed_coefficient = null;
      this.track_coefficient = null;
      this.max_slip_angle = null;
      this.track_slop = null;
      this.crash_coeff = null;
      this.map_path = null;
      this.desired_speed = null;
    }
    else {
      if (initObj.hasOwnProperty('hz')) {
        this.hz = initObj.hz
      }
      else {
        this.hz = 0;
      }
      if (initObj.hasOwnProperty('num_timesteps')) {
        this.num_timesteps = initObj.num_timesteps
      }
      else {
        this.num_timesteps = 0;
      }
      if (initObj.hasOwnProperty('num_iters')) {
        this.num_iters = initObj.num_iters
      }
      else {
        this.num_iters = 0;
      }
      if (initObj.hasOwnProperty('gamma')) {
        this.gamma = initObj.gamma
      }
      else {
        this.gamma = 0.0;
      }
      if (initObj.hasOwnProperty('init_steering')) {
        this.init_steering = initObj.init_steering
      }
      else {
        this.init_steering = 0.0;
      }
      if (initObj.hasOwnProperty('init_throttle')) {
        this.init_throttle = initObj.init_throttle
      }
      else {
        this.init_throttle = 0.0;
      }
      if (initObj.hasOwnProperty('steering_var')) {
        this.steering_var = initObj.steering_var
      }
      else {
        this.steering_var = 0.0;
      }
      if (initObj.hasOwnProperty('throttle_var')) {
        this.throttle_var = initObj.throttle_var
      }
      else {
        this.throttle_var = 0.0;
      }
      if (initObj.hasOwnProperty('max_throttle')) {
        this.max_throttle = initObj.max_throttle
      }
      else {
        this.max_throttle = 0.0;
      }
      if (initObj.hasOwnProperty('speed_coefficient')) {
        this.speed_coefficient = initObj.speed_coefficient
      }
      else {
        this.speed_coefficient = 0.0;
      }
      if (initObj.hasOwnProperty('track_coefficient')) {
        this.track_coefficient = initObj.track_coefficient
      }
      else {
        this.track_coefficient = 0.0;
      }
      if (initObj.hasOwnProperty('max_slip_angle')) {
        this.max_slip_angle = initObj.max_slip_angle
      }
      else {
        this.max_slip_angle = 0.0;
      }
      if (initObj.hasOwnProperty('track_slop')) {
        this.track_slop = initObj.track_slop
      }
      else {
        this.track_slop = 0.0;
      }
      if (initObj.hasOwnProperty('crash_coeff')) {
        this.crash_coeff = initObj.crash_coeff
      }
      else {
        this.crash_coeff = 0.0;
      }
      if (initObj.hasOwnProperty('map_path')) {
        this.map_path = initObj.map_path
      }
      else {
        this.map_path = '';
      }
      if (initObj.hasOwnProperty('desired_speed')) {
        this.desired_speed = initObj.desired_speed
      }
      else {
        this.desired_speed = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pathIntegralParams
    // Serialize message field [hz]
    bufferOffset = _serializer.int64(obj.hz, buffer, bufferOffset);
    // Serialize message field [num_timesteps]
    bufferOffset = _serializer.int64(obj.num_timesteps, buffer, bufferOffset);
    // Serialize message field [num_iters]
    bufferOffset = _serializer.int64(obj.num_iters, buffer, bufferOffset);
    // Serialize message field [gamma]
    bufferOffset = _serializer.float64(obj.gamma, buffer, bufferOffset);
    // Serialize message field [init_steering]
    bufferOffset = _serializer.float64(obj.init_steering, buffer, bufferOffset);
    // Serialize message field [init_throttle]
    bufferOffset = _serializer.float64(obj.init_throttle, buffer, bufferOffset);
    // Serialize message field [steering_var]
    bufferOffset = _serializer.float64(obj.steering_var, buffer, bufferOffset);
    // Serialize message field [throttle_var]
    bufferOffset = _serializer.float64(obj.throttle_var, buffer, bufferOffset);
    // Serialize message field [max_throttle]
    bufferOffset = _serializer.float64(obj.max_throttle, buffer, bufferOffset);
    // Serialize message field [speed_coefficient]
    bufferOffset = _serializer.float64(obj.speed_coefficient, buffer, bufferOffset);
    // Serialize message field [track_coefficient]
    bufferOffset = _serializer.float64(obj.track_coefficient, buffer, bufferOffset);
    // Serialize message field [max_slip_angle]
    bufferOffset = _serializer.float64(obj.max_slip_angle, buffer, bufferOffset);
    // Serialize message field [track_slop]
    bufferOffset = _serializer.float64(obj.track_slop, buffer, bufferOffset);
    // Serialize message field [crash_coeff]
    bufferOffset = _serializer.float64(obj.crash_coeff, buffer, bufferOffset);
    // Serialize message field [map_path]
    bufferOffset = _serializer.string(obj.map_path, buffer, bufferOffset);
    // Serialize message field [desired_speed]
    bufferOffset = _serializer.float64(obj.desired_speed, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pathIntegralParams
    let len;
    let data = new pathIntegralParams(null);
    // Deserialize message field [hz]
    data.hz = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [num_timesteps]
    data.num_timesteps = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [num_iters]
    data.num_iters = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [gamma]
    data.gamma = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [init_steering]
    data.init_steering = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [init_throttle]
    data.init_throttle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steering_var]
    data.steering_var = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [throttle_var]
    data.throttle_var = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_throttle]
    data.max_throttle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_coefficient]
    data.speed_coefficient = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [track_coefficient]
    data.track_coefficient = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [max_slip_angle]
    data.max_slip_angle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [track_slop]
    data.track_slop = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [crash_coeff]
    data.crash_coeff = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [map_path]
    data.map_path = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [desired_speed]
    data.desired_speed = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.map_path.length;
    return length + 124;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/pathIntegralParams';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '262665b21f53db4e41908d6cccfe0a29';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 hz
    int64 num_timesteps
    int64 num_iters
    float64 gamma
    float64 init_steering
    float64 init_throttle
    float64 steering_var
    float64 throttle_var
    float64 max_throttle
    float64 speed_coefficient
    float64 track_coefficient
    float64 max_slip_angle
    float64 track_slop
    float64 crash_coeff
    string map_path
    float64 desired_speed
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pathIntegralParams(null);
    if (msg.hz !== undefined) {
      resolved.hz = msg.hz;
    }
    else {
      resolved.hz = 0
    }

    if (msg.num_timesteps !== undefined) {
      resolved.num_timesteps = msg.num_timesteps;
    }
    else {
      resolved.num_timesteps = 0
    }

    if (msg.num_iters !== undefined) {
      resolved.num_iters = msg.num_iters;
    }
    else {
      resolved.num_iters = 0
    }

    if (msg.gamma !== undefined) {
      resolved.gamma = msg.gamma;
    }
    else {
      resolved.gamma = 0.0
    }

    if (msg.init_steering !== undefined) {
      resolved.init_steering = msg.init_steering;
    }
    else {
      resolved.init_steering = 0.0
    }

    if (msg.init_throttle !== undefined) {
      resolved.init_throttle = msg.init_throttle;
    }
    else {
      resolved.init_throttle = 0.0
    }

    if (msg.steering_var !== undefined) {
      resolved.steering_var = msg.steering_var;
    }
    else {
      resolved.steering_var = 0.0
    }

    if (msg.throttle_var !== undefined) {
      resolved.throttle_var = msg.throttle_var;
    }
    else {
      resolved.throttle_var = 0.0
    }

    if (msg.max_throttle !== undefined) {
      resolved.max_throttle = msg.max_throttle;
    }
    else {
      resolved.max_throttle = 0.0
    }

    if (msg.speed_coefficient !== undefined) {
      resolved.speed_coefficient = msg.speed_coefficient;
    }
    else {
      resolved.speed_coefficient = 0.0
    }

    if (msg.track_coefficient !== undefined) {
      resolved.track_coefficient = msg.track_coefficient;
    }
    else {
      resolved.track_coefficient = 0.0
    }

    if (msg.max_slip_angle !== undefined) {
      resolved.max_slip_angle = msg.max_slip_angle;
    }
    else {
      resolved.max_slip_angle = 0.0
    }

    if (msg.track_slop !== undefined) {
      resolved.track_slop = msg.track_slop;
    }
    else {
      resolved.track_slop = 0.0
    }

    if (msg.crash_coeff !== undefined) {
      resolved.crash_coeff = msg.crash_coeff;
    }
    else {
      resolved.crash_coeff = 0.0
    }

    if (msg.map_path !== undefined) {
      resolved.map_path = msg.map_path;
    }
    else {
      resolved.map_path = ''
    }

    if (msg.desired_speed !== undefined) {
      resolved.desired_speed = msg.desired_speed;
    }
    else {
      resolved.desired_speed = 0.0
    }

    return resolved;
    }
};

module.exports = pathIntegralParams;
