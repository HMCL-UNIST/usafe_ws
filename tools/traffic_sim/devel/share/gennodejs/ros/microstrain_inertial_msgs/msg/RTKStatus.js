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

class RTKStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_tow = null;
      this.gps_week = null;
      this.epoch_status = null;
      this.dongle_version = null;
      this.dongle_modem_state = null;
      this.dongle_connection_type = null;
      this.dongle_rssi = null;
      this.dongle_signal_quality = null;
      this.dongle_tower_change_indicator = null;
      this.dongle_nmea_timeout = null;
      this.dongle_server_timeout = null;
      this.dongle_rtcm_timeout = null;
      this.dongle_out_of_range = null;
      this.dongle_corrections_unavailable = null;
      this.gps_correction_latency = null;
      this.glonass_correction_latency = null;
      this.galileo_correction_latency = null;
      this.beidou_correction_latency = null;
      this.raw_status_flags = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_tow')) {
        this.gps_tow = initObj.gps_tow
      }
      else {
        this.gps_tow = 0.0;
      }
      if (initObj.hasOwnProperty('gps_week')) {
        this.gps_week = initObj.gps_week
      }
      else {
        this.gps_week = 0;
      }
      if (initObj.hasOwnProperty('epoch_status')) {
        this.epoch_status = initObj.epoch_status
      }
      else {
        this.epoch_status = 0;
      }
      if (initObj.hasOwnProperty('dongle_version')) {
        this.dongle_version = initObj.dongle_version
      }
      else {
        this.dongle_version = 0;
      }
      if (initObj.hasOwnProperty('dongle_modem_state')) {
        this.dongle_modem_state = initObj.dongle_modem_state
      }
      else {
        this.dongle_modem_state = 0;
      }
      if (initObj.hasOwnProperty('dongle_connection_type')) {
        this.dongle_connection_type = initObj.dongle_connection_type
      }
      else {
        this.dongle_connection_type = 0;
      }
      if (initObj.hasOwnProperty('dongle_rssi')) {
        this.dongle_rssi = initObj.dongle_rssi
      }
      else {
        this.dongle_rssi = 0;
      }
      if (initObj.hasOwnProperty('dongle_signal_quality')) {
        this.dongle_signal_quality = initObj.dongle_signal_quality
      }
      else {
        this.dongle_signal_quality = 0;
      }
      if (initObj.hasOwnProperty('dongle_tower_change_indicator')) {
        this.dongle_tower_change_indicator = initObj.dongle_tower_change_indicator
      }
      else {
        this.dongle_tower_change_indicator = 0;
      }
      if (initObj.hasOwnProperty('dongle_nmea_timeout')) {
        this.dongle_nmea_timeout = initObj.dongle_nmea_timeout
      }
      else {
        this.dongle_nmea_timeout = false;
      }
      if (initObj.hasOwnProperty('dongle_server_timeout')) {
        this.dongle_server_timeout = initObj.dongle_server_timeout
      }
      else {
        this.dongle_server_timeout = false;
      }
      if (initObj.hasOwnProperty('dongle_rtcm_timeout')) {
        this.dongle_rtcm_timeout = initObj.dongle_rtcm_timeout
      }
      else {
        this.dongle_rtcm_timeout = false;
      }
      if (initObj.hasOwnProperty('dongle_out_of_range')) {
        this.dongle_out_of_range = initObj.dongle_out_of_range
      }
      else {
        this.dongle_out_of_range = false;
      }
      if (initObj.hasOwnProperty('dongle_corrections_unavailable')) {
        this.dongle_corrections_unavailable = initObj.dongle_corrections_unavailable
      }
      else {
        this.dongle_corrections_unavailable = false;
      }
      if (initObj.hasOwnProperty('gps_correction_latency')) {
        this.gps_correction_latency = initObj.gps_correction_latency
      }
      else {
        this.gps_correction_latency = 0.0;
      }
      if (initObj.hasOwnProperty('glonass_correction_latency')) {
        this.glonass_correction_latency = initObj.glonass_correction_latency
      }
      else {
        this.glonass_correction_latency = 0.0;
      }
      if (initObj.hasOwnProperty('galileo_correction_latency')) {
        this.galileo_correction_latency = initObj.galileo_correction_latency
      }
      else {
        this.galileo_correction_latency = 0.0;
      }
      if (initObj.hasOwnProperty('beidou_correction_latency')) {
        this.beidou_correction_latency = initObj.beidou_correction_latency
      }
      else {
        this.beidou_correction_latency = 0.0;
      }
      if (initObj.hasOwnProperty('raw_status_flags')) {
        this.raw_status_flags = initObj.raw_status_flags
      }
      else {
        this.raw_status_flags = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RTKStatus
    // Serialize message field [gps_tow]
    bufferOffset = _serializer.float64(obj.gps_tow, buffer, bufferOffset);
    // Serialize message field [gps_week]
    bufferOffset = _serializer.uint16(obj.gps_week, buffer, bufferOffset);
    // Serialize message field [epoch_status]
    bufferOffset = _serializer.uint16(obj.epoch_status, buffer, bufferOffset);
    // Serialize message field [dongle_version]
    bufferOffset = _serializer.uint8(obj.dongle_version, buffer, bufferOffset);
    // Serialize message field [dongle_modem_state]
    bufferOffset = _serializer.uint8(obj.dongle_modem_state, buffer, bufferOffset);
    // Serialize message field [dongle_connection_type]
    bufferOffset = _serializer.uint8(obj.dongle_connection_type, buffer, bufferOffset);
    // Serialize message field [dongle_rssi]
    bufferOffset = _serializer.int8(obj.dongle_rssi, buffer, bufferOffset);
    // Serialize message field [dongle_signal_quality]
    bufferOffset = _serializer.uint8(obj.dongle_signal_quality, buffer, bufferOffset);
    // Serialize message field [dongle_tower_change_indicator]
    bufferOffset = _serializer.uint8(obj.dongle_tower_change_indicator, buffer, bufferOffset);
    // Serialize message field [dongle_nmea_timeout]
    bufferOffset = _serializer.bool(obj.dongle_nmea_timeout, buffer, bufferOffset);
    // Serialize message field [dongle_server_timeout]
    bufferOffset = _serializer.bool(obj.dongle_server_timeout, buffer, bufferOffset);
    // Serialize message field [dongle_rtcm_timeout]
    bufferOffset = _serializer.bool(obj.dongle_rtcm_timeout, buffer, bufferOffset);
    // Serialize message field [dongle_out_of_range]
    bufferOffset = _serializer.bool(obj.dongle_out_of_range, buffer, bufferOffset);
    // Serialize message field [dongle_corrections_unavailable]
    bufferOffset = _serializer.bool(obj.dongle_corrections_unavailable, buffer, bufferOffset);
    // Serialize message field [gps_correction_latency]
    bufferOffset = _serializer.float32(obj.gps_correction_latency, buffer, bufferOffset);
    // Serialize message field [glonass_correction_latency]
    bufferOffset = _serializer.float32(obj.glonass_correction_latency, buffer, bufferOffset);
    // Serialize message field [galileo_correction_latency]
    bufferOffset = _serializer.float32(obj.galileo_correction_latency, buffer, bufferOffset);
    // Serialize message field [beidou_correction_latency]
    bufferOffset = _serializer.float32(obj.beidou_correction_latency, buffer, bufferOffset);
    // Serialize message field [raw_status_flags]
    bufferOffset = _serializer.uint32(obj.raw_status_flags, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RTKStatus
    let len;
    let data = new RTKStatus(null);
    // Deserialize message field [gps_tow]
    data.gps_tow = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [gps_week]
    data.gps_week = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [epoch_status]
    data.epoch_status = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [dongle_version]
    data.dongle_version = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_modem_state]
    data.dongle_modem_state = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_connection_type]
    data.dongle_connection_type = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_rssi]
    data.dongle_rssi = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [dongle_signal_quality]
    data.dongle_signal_quality = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_tower_change_indicator]
    data.dongle_tower_change_indicator = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dongle_nmea_timeout]
    data.dongle_nmea_timeout = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [dongle_server_timeout]
    data.dongle_server_timeout = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [dongle_rtcm_timeout]
    data.dongle_rtcm_timeout = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [dongle_out_of_range]
    data.dongle_out_of_range = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [dongle_corrections_unavailable]
    data.dongle_corrections_unavailable = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [gps_correction_latency]
    data.gps_correction_latency = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [glonass_correction_latency]
    data.glonass_correction_latency = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [galileo_correction_latency]
    data.galileo_correction_latency = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [beidou_correction_latency]
    data.beidou_correction_latency = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [raw_status_flags]
    data.raw_status_flags = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 43;
  }

  static datatype() {
    // Returns string type for a message object
    return 'microstrain_inertial_msgs/RTKStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'da5543a2118eca78b75d2cf97686be1d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Possible values for dongle_modem_state
    uint8   MODEM_STATE_OFF = 0
    uint8   MODEM_STATE_NO_NETWORK = 1
    uint8   MODEM_STATE_NETWORK_CONNECTED = 2
    uint8   MODEM_STATE_CONFIGURING_DATA_CONTEXT = 3
    uint8   MODEM_STATE_ACTIVATING_DATA_CONTEXT = 4
    uint8   MODEM_STATE_CONFIGURING_SOCKET = 5
    uint8   MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE = 6
    uint8   MODEM_STATE_CONNECTED_AND_IDLE = 7
    uint8   MODEM_STATE_CONNECTED_AND_STREAMING = 8
    
    # Possible values for dongle_connection_type
    uint8   CONNECTION_TYPE_NO_CONNECTION = 0
    uint8   CONNECTION_TYPE_CONNECTION_2G = 2
    uint8   CONNECTION_TYPE_CONNECTION_3G = 3
    uint8   CONNECTION_TYPE_CONNECTION_4G = 4
    uint8   CONNECTION_TYPE_CONNECTION_5G = 5
    
    float64 gps_tow
    uint16  gps_week
    uint16  epoch_status
    
    uint8   dongle_version
    uint8   dongle_modem_state      # Use in conjunction with MODEM_STATE_* values
    uint8   dongle_connection_type  # Use in conjunction with CONNECTION_TYPE_* values
    int8    dongle_rssi             # RSSI values are negative
    uint8   dongle_signal_quality
    uint8   dongle_tower_change_indicator
    bool    dongle_nmea_timeout
    bool    dongle_server_timeout
    bool    dongle_rtcm_timeout
    bool    dongle_out_of_range
    bool    dongle_corrections_unavailable
    
    float32 gps_correction_latency
    float32 glonass_correction_latency
    float32 galileo_correction_latency
    float32 beidou_correction_latency
    
    
    uint32  raw_status_flags        # Raw status flags value
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RTKStatus(null);
    if (msg.gps_tow !== undefined) {
      resolved.gps_tow = msg.gps_tow;
    }
    else {
      resolved.gps_tow = 0.0
    }

    if (msg.gps_week !== undefined) {
      resolved.gps_week = msg.gps_week;
    }
    else {
      resolved.gps_week = 0
    }

    if (msg.epoch_status !== undefined) {
      resolved.epoch_status = msg.epoch_status;
    }
    else {
      resolved.epoch_status = 0
    }

    if (msg.dongle_version !== undefined) {
      resolved.dongle_version = msg.dongle_version;
    }
    else {
      resolved.dongle_version = 0
    }

    if (msg.dongle_modem_state !== undefined) {
      resolved.dongle_modem_state = msg.dongle_modem_state;
    }
    else {
      resolved.dongle_modem_state = 0
    }

    if (msg.dongle_connection_type !== undefined) {
      resolved.dongle_connection_type = msg.dongle_connection_type;
    }
    else {
      resolved.dongle_connection_type = 0
    }

    if (msg.dongle_rssi !== undefined) {
      resolved.dongle_rssi = msg.dongle_rssi;
    }
    else {
      resolved.dongle_rssi = 0
    }

    if (msg.dongle_signal_quality !== undefined) {
      resolved.dongle_signal_quality = msg.dongle_signal_quality;
    }
    else {
      resolved.dongle_signal_quality = 0
    }

    if (msg.dongle_tower_change_indicator !== undefined) {
      resolved.dongle_tower_change_indicator = msg.dongle_tower_change_indicator;
    }
    else {
      resolved.dongle_tower_change_indicator = 0
    }

    if (msg.dongle_nmea_timeout !== undefined) {
      resolved.dongle_nmea_timeout = msg.dongle_nmea_timeout;
    }
    else {
      resolved.dongle_nmea_timeout = false
    }

    if (msg.dongle_server_timeout !== undefined) {
      resolved.dongle_server_timeout = msg.dongle_server_timeout;
    }
    else {
      resolved.dongle_server_timeout = false
    }

    if (msg.dongle_rtcm_timeout !== undefined) {
      resolved.dongle_rtcm_timeout = msg.dongle_rtcm_timeout;
    }
    else {
      resolved.dongle_rtcm_timeout = false
    }

    if (msg.dongle_out_of_range !== undefined) {
      resolved.dongle_out_of_range = msg.dongle_out_of_range;
    }
    else {
      resolved.dongle_out_of_range = false
    }

    if (msg.dongle_corrections_unavailable !== undefined) {
      resolved.dongle_corrections_unavailable = msg.dongle_corrections_unavailable;
    }
    else {
      resolved.dongle_corrections_unavailable = false
    }

    if (msg.gps_correction_latency !== undefined) {
      resolved.gps_correction_latency = msg.gps_correction_latency;
    }
    else {
      resolved.gps_correction_latency = 0.0
    }

    if (msg.glonass_correction_latency !== undefined) {
      resolved.glonass_correction_latency = msg.glonass_correction_latency;
    }
    else {
      resolved.glonass_correction_latency = 0.0
    }

    if (msg.galileo_correction_latency !== undefined) {
      resolved.galileo_correction_latency = msg.galileo_correction_latency;
    }
    else {
      resolved.galileo_correction_latency = 0.0
    }

    if (msg.beidou_correction_latency !== undefined) {
      resolved.beidou_correction_latency = msg.beidou_correction_latency;
    }
    else {
      resolved.beidou_correction_latency = 0.0
    }

    if (msg.raw_status_flags !== undefined) {
      resolved.raw_status_flags = msg.raw_status_flags;
    }
    else {
      resolved.raw_status_flags = 0
    }

    return resolved;
    }
};

// Constants for message
RTKStatus.Constants = {
  MODEM_STATE_OFF: 0,
  MODEM_STATE_NO_NETWORK: 1,
  MODEM_STATE_NETWORK_CONNECTED: 2,
  MODEM_STATE_CONFIGURING_DATA_CONTEXT: 3,
  MODEM_STATE_ACTIVATING_DATA_CONTEXT: 4,
  MODEM_STATE_CONFIGURING_SOCKET: 5,
  MODEM_STATE_WAITING_ON_SERVER_HANDSHAKE: 6,
  MODEM_STATE_CONNECTED_AND_IDLE: 7,
  MODEM_STATE_CONNECTED_AND_STREAMING: 8,
  CONNECTION_TYPE_NO_CONNECTION: 0,
  CONNECTION_TYPE_CONNECTION_2G: 2,
  CONNECTION_TYPE_CONNECTION_3G: 3,
  CONNECTION_TYPE_CONNECTION_4G: 4,
  CONNECTION_TYPE_CONNECTION_5G: 5,
}

module.exports = RTKStatus;
