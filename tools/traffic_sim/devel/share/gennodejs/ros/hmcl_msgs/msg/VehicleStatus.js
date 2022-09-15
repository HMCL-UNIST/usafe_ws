// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let VehicleSteering = require('./VehicleSteering.js');
let VehicleSCC = require('./VehicleSCC.js');
let VehicleWheelSpeed = require('./VehicleWheelSpeed.js');
let VehicleGear = require('./VehicleGear.js');
let VehicleLight = require('./VehicleLight.js');
let RemoteButton = require('./RemoteButton.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VehicleStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.steering_info = null;
      this.scc_info = null;
      this.wheelspeed = null;
      this.gear_info = null;
      this.light_info = null;
      this.remote_button_info = null;
      this.auto_mode = null;
      this.ems_mode = null;
      this.x_acceleration = null;
      this.y_acceleration = null;
      this.yaw_rate = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('steering_info')) {
        this.steering_info = initObj.steering_info
      }
      else {
        this.steering_info = new VehicleSteering();
      }
      if (initObj.hasOwnProperty('scc_info')) {
        this.scc_info = initObj.scc_info
      }
      else {
        this.scc_info = new VehicleSCC();
      }
      if (initObj.hasOwnProperty('wheelspeed')) {
        this.wheelspeed = initObj.wheelspeed
      }
      else {
        this.wheelspeed = new VehicleWheelSpeed();
      }
      if (initObj.hasOwnProperty('gear_info')) {
        this.gear_info = initObj.gear_info
      }
      else {
        this.gear_info = new VehicleGear();
      }
      if (initObj.hasOwnProperty('light_info')) {
        this.light_info = initObj.light_info
      }
      else {
        this.light_info = new VehicleLight();
      }
      if (initObj.hasOwnProperty('remote_button_info')) {
        this.remote_button_info = initObj.remote_button_info
      }
      else {
        this.remote_button_info = new RemoteButton();
      }
      if (initObj.hasOwnProperty('auto_mode')) {
        this.auto_mode = initObj.auto_mode
      }
      else {
        this.auto_mode = 0;
      }
      if (initObj.hasOwnProperty('ems_mode')) {
        this.ems_mode = initObj.ems_mode
      }
      else {
        this.ems_mode = 0;
      }
      if (initObj.hasOwnProperty('x_acceleration')) {
        this.x_acceleration = initObj.x_acceleration
      }
      else {
        this.x_acceleration = 0.0;
      }
      if (initObj.hasOwnProperty('y_acceleration')) {
        this.y_acceleration = initObj.y_acceleration
      }
      else {
        this.y_acceleration = 0.0;
      }
      if (initObj.hasOwnProperty('yaw_rate')) {
        this.yaw_rate = initObj.yaw_rate
      }
      else {
        this.yaw_rate = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleStatus
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [steering_info]
    bufferOffset = VehicleSteering.serialize(obj.steering_info, buffer, bufferOffset);
    // Serialize message field [scc_info]
    bufferOffset = VehicleSCC.serialize(obj.scc_info, buffer, bufferOffset);
    // Serialize message field [wheelspeed]
    bufferOffset = VehicleWheelSpeed.serialize(obj.wheelspeed, buffer, bufferOffset);
    // Serialize message field [gear_info]
    bufferOffset = VehicleGear.serialize(obj.gear_info, buffer, bufferOffset);
    // Serialize message field [light_info]
    bufferOffset = VehicleLight.serialize(obj.light_info, buffer, bufferOffset);
    // Serialize message field [remote_button_info]
    bufferOffset = RemoteButton.serialize(obj.remote_button_info, buffer, bufferOffset);
    // Serialize message field [auto_mode]
    bufferOffset = _serializer.uint8(obj.auto_mode, buffer, bufferOffset);
    // Serialize message field [ems_mode]
    bufferOffset = _serializer.uint8(obj.ems_mode, buffer, bufferOffset);
    // Serialize message field [x_acceleration]
    bufferOffset = _serializer.float64(obj.x_acceleration, buffer, bufferOffset);
    // Serialize message field [y_acceleration]
    bufferOffset = _serializer.float64(obj.y_acceleration, buffer, bufferOffset);
    // Serialize message field [yaw_rate]
    bufferOffset = _serializer.float64(obj.yaw_rate, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleStatus
    let len;
    let data = new VehicleStatus(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [steering_info]
    data.steering_info = VehicleSteering.deserialize(buffer, bufferOffset);
    // Deserialize message field [scc_info]
    data.scc_info = VehicleSCC.deserialize(buffer, bufferOffset);
    // Deserialize message field [wheelspeed]
    data.wheelspeed = VehicleWheelSpeed.deserialize(buffer, bufferOffset);
    // Deserialize message field [gear_info]
    data.gear_info = VehicleGear.deserialize(buffer, bufferOffset);
    // Deserialize message field [light_info]
    data.light_info = VehicleLight.deserialize(buffer, bufferOffset);
    // Deserialize message field [remote_button_info]
    data.remote_button_info = RemoteButton.deserialize(buffer, bufferOffset);
    // Deserialize message field [auto_mode]
    data.auto_mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ems_mode]
    data.ems_mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [x_acceleration]
    data.x_acceleration = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y_acceleration]
    data.y_acceleration = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [yaw_rate]
    data.yaw_rate = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += VehicleSteering.getMessageSize(object.steering_info);
    length += VehicleSCC.getMessageSize(object.scc_info);
    length += VehicleWheelSpeed.getMessageSize(object.wheelspeed);
    return length + 33;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/VehicleStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '257eaa74ca2595e01127664962d58d27';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    hmcl_msgs/VehicleSteering steering_info
    hmcl_msgs/VehicleSCC scc_info
    hmcl_msgs/VehicleWheelSpeed wheelspeed
    hmcl_msgs/VehicleGear gear_info
    hmcl_msgs/VehicleLight light_info
    hmcl_msgs/RemoteButton remote_button_info
    # auto mode -> 0  off
    # auto mode -> 1  on
    uint8 auto_mode 
    # ems mode -> 0  off
    # ems mode -> 1  on
    uint8 ems_mode 
    float64 x_acceleration
    float64 y_acceleration
    float64 yaw_rate
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: hmcl_msgs/VehicleSteering
    Header header
    # steering takeover -> off       = 0
    # steering takeover -> on      = 1
    uint8 takeover
    # steering mode -> off       = 0
    # steering mode -> on      = 1
    uint8 mode
    float32 steering_angle
    ================================================================================
    MSG: hmcl_msgs/VehicleSCC
    Header header
    # sccmode -> off       = 0
    # sccmode -> ready       = 1
    # sccmode -> on       = 2
    uint8 scc_mode
    # scc takeover -> off       = 0
    # scc takeover -> n      = 1
    uint8 scc_takeover
    float64 acceleration
    ================================================================================
    MSG: hmcl_msgs/VehicleWheelSpeed
    Header header
    float64 wheel_speed
    float64 fr
    float64 fl
    float64 rr
    float64 rl
    ================================================================================
    MSG: hmcl_msgs/VehicleGear
    # Gear -> P       = 1
    # Gear -> D       = 2
    # Gear -> N       = 3
    # Gear -> R       = 4
    uint8 gear
    
    ================================================================================
    MSG: hmcl_msgs/VehicleLight
    # 0 off, 1 on 
    uint8 left_light
    uint8 right_light
    uint8 hazard_light
    ================================================================================
    MSG: hmcl_msgs/RemoteButton
    # wirelessbutton -> 0 push off, 1 -> push on
    uint8 button1
    uint8 button2
    uint8 button3
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VehicleStatus(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.steering_info !== undefined) {
      resolved.steering_info = VehicleSteering.Resolve(msg.steering_info)
    }
    else {
      resolved.steering_info = new VehicleSteering()
    }

    if (msg.scc_info !== undefined) {
      resolved.scc_info = VehicleSCC.Resolve(msg.scc_info)
    }
    else {
      resolved.scc_info = new VehicleSCC()
    }

    if (msg.wheelspeed !== undefined) {
      resolved.wheelspeed = VehicleWheelSpeed.Resolve(msg.wheelspeed)
    }
    else {
      resolved.wheelspeed = new VehicleWheelSpeed()
    }

    if (msg.gear_info !== undefined) {
      resolved.gear_info = VehicleGear.Resolve(msg.gear_info)
    }
    else {
      resolved.gear_info = new VehicleGear()
    }

    if (msg.light_info !== undefined) {
      resolved.light_info = VehicleLight.Resolve(msg.light_info)
    }
    else {
      resolved.light_info = new VehicleLight()
    }

    if (msg.remote_button_info !== undefined) {
      resolved.remote_button_info = RemoteButton.Resolve(msg.remote_button_info)
    }
    else {
      resolved.remote_button_info = new RemoteButton()
    }

    if (msg.auto_mode !== undefined) {
      resolved.auto_mode = msg.auto_mode;
    }
    else {
      resolved.auto_mode = 0
    }

    if (msg.ems_mode !== undefined) {
      resolved.ems_mode = msg.ems_mode;
    }
    else {
      resolved.ems_mode = 0
    }

    if (msg.x_acceleration !== undefined) {
      resolved.x_acceleration = msg.x_acceleration;
    }
    else {
      resolved.x_acceleration = 0.0
    }

    if (msg.y_acceleration !== undefined) {
      resolved.y_acceleration = msg.y_acceleration;
    }
    else {
      resolved.y_acceleration = 0.0
    }

    if (msg.yaw_rate !== undefined) {
      resolved.yaw_rate = msg.yaw_rate;
    }
    else {
      resolved.yaw_rate = 0.0
    }

    return resolved;
    }
};

module.exports = VehicleStatus;
