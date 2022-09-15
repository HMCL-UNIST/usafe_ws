// Auto-generated. Do not edit!

// (in-package microstrain_inertial_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Status {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.device_model = null;
      this.status_selector = null;
      this.status_flags = null;
      this.system_state = null;
      this.system_timer_ms = null;
      this.gps_power_on = null;
      this.num_gps_pps_triggers = null;
      this.last_gps_pps_trigger_ms = null;
      this.imu_stream_enabled = null;
      this.gps_stream_enabled = null;
      this.filter_stream_enabled = null;
      this.imu_dropped_packets = null;
      this.gps_dropped_packets = null;
      this.filter_dropped_packets = null;
      this.com1_port_bytes_written = null;
      this.com1_port_bytes_read = null;
      this.com1_port_write_overruns = null;
      this.com1_port_read_overruns = null;
      this.imu_parser_errors = null;
      this.imu_message_count = null;
      this.imu_last_message_ms = null;
      this.gps_parser_errors = null;
      this.gps_message_count = null;
      this.gps_last_message_ms = null;
    }
    else {
      if (initObj.hasOwnProperty('device_model')) {
        this.device_model = initObj.device_model
      }
      else {
        this.device_model = 0;
      }
      if (initObj.hasOwnProperty('status_selector')) {
        this.status_selector = initObj.status_selector
      }
      else {
        this.status_selector = 0;
      }
      if (initObj.hasOwnProperty('status_flags')) {
        this.status_flags = initObj.status_flags
      }
      else {
        this.status_flags = 0;
      }
      if (initObj.hasOwnProperty('system_state')) {
        this.system_state = initObj.system_state
      }
      else {
        this.system_state = 0;
      }
      if (initObj.hasOwnProperty('system_timer_ms')) {
        this.system_timer_ms = initObj.system_timer_ms
      }
      else {
        this.system_timer_ms = 0;
      }
      if (initObj.hasOwnProperty('gps_power_on')) {
        this.gps_power_on = initObj.gps_power_on
      }
      else {
        this.gps_power_on = 0;
      }
      if (initObj.hasOwnProperty('num_gps_pps_triggers')) {
        this.num_gps_pps_triggers = initObj.num_gps_pps_triggers
      }
      else {
        this.num_gps_pps_triggers = 0;
      }
      if (initObj.hasOwnProperty('last_gps_pps_trigger_ms')) {
        this.last_gps_pps_trigger_ms = initObj.last_gps_pps_trigger_ms
      }
      else {
        this.last_gps_pps_trigger_ms = 0;
      }
      if (initObj.hasOwnProperty('imu_stream_enabled')) {
        this.imu_stream_enabled = initObj.imu_stream_enabled
      }
      else {
        this.imu_stream_enabled = 0;
      }
      if (initObj.hasOwnProperty('gps_stream_enabled')) {
        this.gps_stream_enabled = initObj.gps_stream_enabled
      }
      else {
        this.gps_stream_enabled = 0;
      }
      if (initObj.hasOwnProperty('filter_stream_enabled')) {
        this.filter_stream_enabled = initObj.filter_stream_enabled
      }
      else {
        this.filter_stream_enabled = 0;
      }
      if (initObj.hasOwnProperty('imu_dropped_packets')) {
        this.imu_dropped_packets = initObj.imu_dropped_packets
      }
      else {
        this.imu_dropped_packets = 0;
      }
      if (initObj.hasOwnProperty('gps_dropped_packets')) {
        this.gps_dropped_packets = initObj.gps_dropped_packets
      }
      else {
        this.gps_dropped_packets = 0;
      }
      if (initObj.hasOwnProperty('filter_dropped_packets')) {
        this.filter_dropped_packets = initObj.filter_dropped_packets
      }
      else {
        this.filter_dropped_packets = 0;
      }
      if (initObj.hasOwnProperty('com1_port_bytes_written')) {
        this.com1_port_bytes_written = initObj.com1_port_bytes_written
      }
      else {
        this.com1_port_bytes_written = 0;
      }
      if (initObj.hasOwnProperty('com1_port_bytes_read')) {
        this.com1_port_bytes_read = initObj.com1_port_bytes_read
      }
      else {
        this.com1_port_bytes_read = 0;
      }
      if (initObj.hasOwnProperty('com1_port_write_overruns')) {
        this.com1_port_write_overruns = initObj.com1_port_write_overruns
      }
      else {
        this.com1_port_write_overruns = 0;
      }
      if (initObj.hasOwnProperty('com1_port_read_overruns')) {
        this.com1_port_read_overruns = initObj.com1_port_read_overruns
      }
      else {
        this.com1_port_read_overruns = 0;
      }
      if (initObj.hasOwnProperty('imu_parser_errors')) {
        this.imu_parser_errors = initObj.imu_parser_errors
      }
      else {
        this.imu_parser_errors = 0;
      }
      if (initObj.hasOwnProperty('imu_message_count')) {
        this.imu_message_count = initObj.imu_message_count
      }
      else {
        this.imu_message_count = 0;
      }
      if (initObj.hasOwnProperty('imu_last_message_ms')) {
        this.imu_last_message_ms = initObj.imu_last_message_ms
      }
      else {
        this.imu_last_message_ms = 0;
      }
      if (initObj.hasOwnProperty('gps_parser_errors')) {
        this.gps_parser_errors = initObj.gps_parser_errors
      }
      else {
        this.gps_parser_errors = 0;
      }
      if (initObj.hasOwnProperty('gps_message_count')) {
        this.gps_message_count = initObj.gps_message_count
      }
      else {
        this.gps_message_count = 0;
      }
      if (initObj.hasOwnProperty('gps_last_message_ms')) {
        this.gps_last_message_ms = initObj.gps_last_message_ms
      }
      else {
        this.gps_last_message_ms = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Status
    // Serialize message field [device_model]
    bufferOffset = _serializer.uint16(obj.device_model, buffer, bufferOffset);
    // Serialize message field [status_selector]
    bufferOffset = _serializer.uint8(obj.status_selector, buffer, bufferOffset);
    // Serialize message field [status_flags]
    bufferOffset = _serializer.uint32(obj.status_flags, buffer, bufferOffset);
    // Serialize message field [system_state]
    bufferOffset = _serializer.uint16(obj.system_state, buffer, bufferOffset);
    // Serialize message field [system_timer_ms]
    bufferOffset = _serializer.uint32(obj.system_timer_ms, buffer, bufferOffset);
    // Serialize message field [gps_power_on]
    bufferOffset = _serializer.uint8(obj.gps_power_on, buffer, bufferOffset);
    // Serialize message field [num_gps_pps_triggers]
    bufferOffset = _serializer.uint32(obj.num_gps_pps_triggers, buffer, bufferOffset);
    // Serialize message field [last_gps_pps_trigger_ms]
    bufferOffset = _serializer.uint32(obj.last_gps_pps_trigger_ms, buffer, bufferOffset);
    // Serialize message field [imu_stream_enabled]
    bufferOffset = _serializer.uint8(obj.imu_stream_enabled, buffer, bufferOffset);
    // Serialize message field [gps_stream_enabled]
    bufferOffset = _serializer.uint8(obj.gps_stream_enabled, buffer, bufferOffset);
    // Serialize message field [filter_stream_enabled]
    bufferOffset = _serializer.uint8(obj.filter_stream_enabled, buffer, bufferOffset);
    // Serialize message field [imu_dropped_packets]
    bufferOffset = _serializer.uint32(obj.imu_dropped_packets, buffer, bufferOffset);
    // Serialize message field [gps_dropped_packets]
    bufferOffset = _serializer.uint32(obj.gps_dropped_packets, buffer, bufferOffset);
    // Serialize message field [filter_dropped_packets]
    bufferOffset = _serializer.uint32(obj.filter_dropped_packets, buffer, bufferOffset);
    // Serialize message field [com1_port_bytes_written]
    bufferOffset = _serializer.uint32(obj.com1_port_bytes_written, buffer, bufferOffset);
    // Serialize message field [com1_port_bytes_read]
    bufferOffset = _serializer.uint32(obj.com1_port_bytes_read, buffer, bufferOffset);
    // Serialize message field [com1_port_write_overruns]
    bufferOffset = _serializer.uint32(obj.com1_port_write_overruns, buffer, bufferOffset);
    // Serialize message field [com1_port_read_overruns]
    bufferOffset = _serializer.uint32(obj.com1_port_read_overruns, buffer, bufferOffset);
    // Serialize message field [imu_parser_errors]
    bufferOffset = _serializer.uint32(obj.imu_parser_errors, buffer, bufferOffset);
    // Serialize message field [imu_message_count]
    bufferOffset = _serializer.uint32(obj.imu_message_count, buffer, bufferOffset);
    // Serialize message field [imu_last_message_ms]
    bufferOffset = _serializer.uint32(obj.imu_last_message_ms, buffer, bufferOffset);
    // Serialize message field [gps_parser_errors]
    bufferOffset = _serializer.uint32(obj.gps_parser_errors, buffer, bufferOffset);
    // Serialize message field [gps_message_count]
    bufferOffset = _serializer.uint32(obj.gps_message_count, buffer, bufferOffset);
    // Serialize message field [gps_last_message_ms]
    bufferOffset = _serializer.uint32(obj.gps_last_message_ms, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Status
    let len;
    let data = new Status(null);
    // Deserialize message field [device_model]
    data.device_model = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [status_selector]
    data.status_selector = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [status_flags]
    data.status_flags = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [system_state]
    data.system_state = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [system_timer_ms]
    data.system_timer_ms = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [gps_power_on]
    data.gps_power_on = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [num_gps_pps_triggers]
    data.num_gps_pps_triggers = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [last_gps_pps_trigger_ms]
    data.last_gps_pps_trigger_ms = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [imu_stream_enabled]
    data.imu_stream_enabled = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [gps_stream_enabled]
    data.gps_stream_enabled = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [filter_stream_enabled]
    data.filter_stream_enabled = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [imu_dropped_packets]
    data.imu_dropped_packets = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [gps_dropped_packets]
    data.gps_dropped_packets = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [filter_dropped_packets]
    data.filter_dropped_packets = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [com1_port_bytes_written]
    data.com1_port_bytes_written = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [com1_port_bytes_read]
    data.com1_port_bytes_read = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [com1_port_write_overruns]
    data.com1_port_write_overruns = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [com1_port_read_overruns]
    data.com1_port_read_overruns = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [imu_parser_errors]
    data.imu_parser_errors = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [imu_message_count]
    data.imu_message_count = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [imu_last_message_ms]
    data.imu_last_message_ms = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [gps_parser_errors]
    data.gps_parser_errors = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [gps_message_count]
    data.gps_message_count = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [gps_last_message_ms]
    data.gps_last_message_ms = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 77;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/Status';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b19b8bec6f96c609664c27dbc51ddf60';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 device_model
    uint8  status_selector
    
    uint32 status_flags
    
    uint16 system_state
    uint32 system_timer_ms
    
    uint8 gps_power_on
    
    uint32 num_gps_pps_triggers
    uint32 last_gps_pps_trigger_ms
    
    uint8 imu_stream_enabled
    uint8 gps_stream_enabled
    uint8 filter_stream_enabled
    
    uint32 imu_dropped_packets
    uint32 gps_dropped_packets
    uint32 filter_dropped_packets
    
    uint32 com1_port_bytes_written
    uint32 com1_port_bytes_read
    uint32 com1_port_write_overruns
    uint32 com1_port_read_overruns
    
    uint32 imu_parser_errors
    uint32 imu_message_count
    uint32 imu_last_message_ms
    
    uint32 gps_parser_errors
    uint32 gps_message_count
    uint32 gps_last_message_ms
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Status(null);
    if (msg.device_model !== undefined) {
      resolved.device_model = msg.device_model;
    }
    else {
      resolved.device_model = 0
    }

    if (msg.status_selector !== undefined) {
      resolved.status_selector = msg.status_selector;
    }
    else {
      resolved.status_selector = 0
    }

    if (msg.status_flags !== undefined) {
      resolved.status_flags = msg.status_flags;
    }
    else {
      resolved.status_flags = 0
    }

    if (msg.system_state !== undefined) {
      resolved.system_state = msg.system_state;
    }
    else {
      resolved.system_state = 0
    }

    if (msg.system_timer_ms !== undefined) {
      resolved.system_timer_ms = msg.system_timer_ms;
    }
    else {
      resolved.system_timer_ms = 0
    }

    if (msg.gps_power_on !== undefined) {
      resolved.gps_power_on = msg.gps_power_on;
    }
    else {
      resolved.gps_power_on = 0
    }

    if (msg.num_gps_pps_triggers !== undefined) {
      resolved.num_gps_pps_triggers = msg.num_gps_pps_triggers;
    }
    else {
      resolved.num_gps_pps_triggers = 0
    }

    if (msg.last_gps_pps_trigger_ms !== undefined) {
      resolved.last_gps_pps_trigger_ms = msg.last_gps_pps_trigger_ms;
    }
    else {
      resolved.last_gps_pps_trigger_ms = 0
    }

    if (msg.imu_stream_enabled !== undefined) {
      resolved.imu_stream_enabled = msg.imu_stream_enabled;
    }
    else {
      resolved.imu_stream_enabled = 0
    }

    if (msg.gps_stream_enabled !== undefined) {
      resolved.gps_stream_enabled = msg.gps_stream_enabled;
    }
    else {
      resolved.gps_stream_enabled = 0
    }

    if (msg.filter_stream_enabled !== undefined) {
      resolved.filter_stream_enabled = msg.filter_stream_enabled;
    }
    else {
      resolved.filter_stream_enabled = 0
    }

    if (msg.imu_dropped_packets !== undefined) {
      resolved.imu_dropped_packets = msg.imu_dropped_packets;
    }
    else {
      resolved.imu_dropped_packets = 0
    }

    if (msg.gps_dropped_packets !== undefined) {
      resolved.gps_dropped_packets = msg.gps_dropped_packets;
    }
    else {
      resolved.gps_dropped_packets = 0
    }

    if (msg.filter_dropped_packets !== undefined) {
      resolved.filter_dropped_packets = msg.filter_dropped_packets;
    }
    else {
      resolved.filter_dropped_packets = 0
    }

    if (msg.com1_port_bytes_written !== undefined) {
      resolved.com1_port_bytes_written = msg.com1_port_bytes_written;
    }
    else {
      resolved.com1_port_bytes_written = 0
    }

    if (msg.com1_port_bytes_read !== undefined) {
      resolved.com1_port_bytes_read = msg.com1_port_bytes_read;
    }
    else {
      resolved.com1_port_bytes_read = 0
    }

    if (msg.com1_port_write_overruns !== undefined) {
      resolved.com1_port_write_overruns = msg.com1_port_write_overruns;
    }
    else {
      resolved.com1_port_write_overruns = 0
    }

    if (msg.com1_port_read_overruns !== undefined) {
      resolved.com1_port_read_overruns = msg.com1_port_read_overruns;
    }
    else {
      resolved.com1_port_read_overruns = 0
    }

    if (msg.imu_parser_errors !== undefined) {
      resolved.imu_parser_errors = msg.imu_parser_errors;
    }
    else {
      resolved.imu_parser_errors = 0
    }

    if (msg.imu_message_count !== undefined) {
      resolved.imu_message_count = msg.imu_message_count;
    }
    else {
      resolved.imu_message_count = 0
    }

    if (msg.imu_last_message_ms !== undefined) {
      resolved.imu_last_message_ms = msg.imu_last_message_ms;
    }
    else {
      resolved.imu_last_message_ms = 0
    }

    if (msg.gps_parser_errors !== undefined) {
      resolved.gps_parser_errors = msg.gps_parser_errors;
    }
    else {
      resolved.gps_parser_errors = 0
    }

    if (msg.gps_message_count !== undefined) {
      resolved.gps_message_count = msg.gps_message_count;
    }
    else {
      resolved.gps_message_count = 0
    }

    if (msg.gps_last_message_ms !== undefined) {
      resolved.gps_last_message_ms = msg.gps_last_message_ms;
    }
    else {
      resolved.gps_last_message_ms = 0
    }

    return resolved;
    }
};

module.exports = Status;
