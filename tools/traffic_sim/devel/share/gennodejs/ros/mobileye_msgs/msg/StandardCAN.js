// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let SystemWarnings = require('./SystemWarnings.js');
let CarInfo = require('./CarInfo.js');
let TSR = require('./TSR.js');
let TSRVisionOnlySign = require('./TSRVisionOnlySign.js');
let Gyro = require('./Gyro.js');
let SmartADAS = require('./SmartADAS.js');
let SeeQ = require('./SeeQ.js');

//-----------------------------------------------------------

class StandardCAN {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.system_warnings = null;
      this.car_info = null;
      this.tsr = null;
      this.tsr_vision_only = null;
      this.gyro = null;
      this.smart_adas = null;
      this.seeq = null;
    }
    else {
      if (initObj.hasOwnProperty('system_warnings')) {
        this.system_warnings = initObj.system_warnings
      }
      else {
        this.system_warnings = new SystemWarnings();
      }
      if (initObj.hasOwnProperty('car_info')) {
        this.car_info = initObj.car_info
      }
      else {
        this.car_info = new CarInfo();
      }
      if (initObj.hasOwnProperty('tsr')) {
        this.tsr = initObj.tsr
      }
      else {
        this.tsr = [];
      }
      if (initObj.hasOwnProperty('tsr_vision_only')) {
        this.tsr_vision_only = initObj.tsr_vision_only
      }
      else {
        this.tsr_vision_only = new TSRVisionOnlySign();
      }
      if (initObj.hasOwnProperty('gyro')) {
        this.gyro = initObj.gyro
      }
      else {
        this.gyro = new Gyro();
      }
      if (initObj.hasOwnProperty('smart_adas')) {
        this.smart_adas = initObj.smart_adas
      }
      else {
        this.smart_adas = new SmartADAS();
      }
      if (initObj.hasOwnProperty('seeq')) {
        this.seeq = initObj.seeq
      }
      else {
        this.seeq = new SeeQ();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type StandardCAN
    // Serialize message field [system_warnings]
    bufferOffset = SystemWarnings.serialize(obj.system_warnings, buffer, bufferOffset);
    // Serialize message field [car_info]
    bufferOffset = CarInfo.serialize(obj.car_info, buffer, bufferOffset);
    // Serialize message field [tsr]
    // Serialize the length for message field [tsr]
    bufferOffset = _serializer.uint32(obj.tsr.length, buffer, bufferOffset);
    obj.tsr.forEach((val) => {
      bufferOffset = TSR.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [tsr_vision_only]
    bufferOffset = TSRVisionOnlySign.serialize(obj.tsr_vision_only, buffer, bufferOffset);
    // Serialize message field [gyro]
    bufferOffset = Gyro.serialize(obj.gyro, buffer, bufferOffset);
    // Serialize message field [smart_adas]
    bufferOffset = SmartADAS.serialize(obj.smart_adas, buffer, bufferOffset);
    // Serialize message field [seeq]
    bufferOffset = SeeQ.serialize(obj.seeq, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type StandardCAN
    let len;
    let data = new StandardCAN(null);
    // Deserialize message field [system_warnings]
    data.system_warnings = SystemWarnings.deserialize(buffer, bufferOffset);
    // Deserialize message field [car_info]
    data.car_info = CarInfo.deserialize(buffer, bufferOffset);
    // Deserialize message field [tsr]
    // Deserialize array length for message field [tsr]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.tsr = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.tsr[i] = TSR.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [tsr_vision_only]
    data.tsr_vision_only = TSRVisionOnlySign.deserialize(buffer, bufferOffset);
    // Deserialize message field [gyro]
    data.gyro = Gyro.deserialize(buffer, bufferOffset);
    // Deserialize message field [smart_adas]
    data.smart_adas = SmartADAS.deserialize(buffer, bufferOffset);
    // Deserialize message field [seeq]
    data.seeq = SeeQ.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 15 * object.tsr.length;
    return length + 148;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/StandardCAN';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '54e4cfc9bd8b43c069770d7bbb9295cd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    SystemWarnings system_warnings
    CarInfo car_info
    TSR[] tsr
    TSRVisionOnlySign tsr_vision_only
    Gyro gyro
    SmartADAS smart_adas
    SeeQ seeq
    ================================================================================
    MSG: mobileye_msgs/SystemWarnings
    uint8 sound_type
    bool peds_in_dz
    bool peds_fcw
    uint8 time_indicator
    
    bool error_valid
    uint8 error_code
    bool zero_speed
    bool headway_valid
    float32 headway_measurement
    
    bool ldw_off
    bool left_ldw_on
    bool right_ldw_on
    bool fcw_on
    bool maintenance
    bool failsafe
    
    bool tsr_enabled
    bool hw_repeatable_enabled
    uint8 headway_warning_level
    uint8 tsr_warning_level
    bool tamper_alert
    ================================================================================
    MSG: mobileye_msgs/CarInfo
    bool high_beam
    bool low_beam
    bool wipers
    bool right_signal
    bool left_signal
    bool brake_signal
    bool wipers_available
    bool low_beam_available
    bool high_beam_available
    bool right_blink_available
    bool left_blink_available
    bool brake_available
    bool speed_available
    uint8 speed
    uint8 shield_plus_settings
    ================================================================================
    MSG: mobileye_msgs/TSR
    uint8 vision_only_sign_type
    uint8 supplementary_sign_type
    float32 sign_position_x
    float32 sign_position_y
    float32 sign_position_z
    uint8 filter_type
    ================================================================================
    MSG: mobileye_msgs/TSRVisionOnlySign
    uint8 vision_only_sign_type_display_1
    uint8 vision_only_sign_type_display_2
    uint8 vision_only_sign_type_display_3
    uint8 vision_only_sign_type_display_4
    
    uint8 supplementary_sign_type_display_1
    uint8 supplementary_sign_type_display_2
    uint8 supplementary_sign_type_display_3
    uint8 supplementary_sign_type_display_4
    ================================================================================
    MSG: mobileye_msgs/Gyro
    bool gyro_sensor_data_available
    float32 x_axis_data
    ================================================================================
    MSG: mobileye_msgs/SmartADAS
    uint8 persistent_on_off
    uint8 volume_level
    uint8 hmw_level
    uint8 ldw_volume_level
    uint8 hmw_volume_level
    uint8 ldw_level
    uint8 pedestrian_warning_level
    uint8 sli_warning_level
    uint8 blinker_reminder_level
    uint8 virtual_bumper_level
    uint8 hw_repeatable_level
    
    uint8 buzzer_min_volume
    uint8 buzzer_max_volume
    uint8 buzzer_hmw_min_volume
    uint8 buzzer_hmw_max_volume
    uint8 buzzer_ldw_min_volume
    uint8 buzzer_ldw_max_volume
    uint8 ewiii_speed_indication
    uint8 disable_system_off
    uint8 calibration_source
    uint8 ldw_min_value
    uint8 ldw_max_value
    uint8 ldw_speed
    uint8 ped_min_value
    uint8 ped_max_value
    uint8 speed_for_high_low_beam_control
    uint8 virtual_bumper_min_value
    uint8 virtual_bumper_max_value
    uint8 blinker_reminder_min_value
    uint8 blinker_reminder_max_value
    
    uint8 hmw_min_value
    uint8 hmw_max_value
    uint8 hmw_repeatable_min_value
    uint8 hmw_repeatable_max_value
    uint8 sli_min_value
    uint8 sli_max_value
    uint8 sli_delta_round_step
    uint8 sli_delta_round_upwards
    uint8 country_code
    uint8 sli_unit_speed
    uint8 tamper_alert_on_frames
    uint8 tamper_alert_off_frames
    uint8 tamper_alert_enable_j1939
    
    bool[16] menu_ticks
    
    bool[16] advanced_menu_ticks
    ================================================================================
    MSG: mobileye_msgs/SeeQ
    uint32 serial_number
    uint64 production_date
    
    uint8 brain_version_major
    uint8 brain_version_minor
    uint8 mest_version_major
    uint8 mest_version_minor
    uint8 mest_version_subminor
    uint8 mest_version_patch_number
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new StandardCAN(null);
    if (msg.system_warnings !== undefined) {
      resolved.system_warnings = SystemWarnings.Resolve(msg.system_warnings)
    }
    else {
      resolved.system_warnings = new SystemWarnings()
    }

    if (msg.car_info !== undefined) {
      resolved.car_info = CarInfo.Resolve(msg.car_info)
    }
    else {
      resolved.car_info = new CarInfo()
    }

    if (msg.tsr !== undefined) {
      resolved.tsr = new Array(msg.tsr.length);
      for (let i = 0; i < resolved.tsr.length; ++i) {
        resolved.tsr[i] = TSR.Resolve(msg.tsr[i]);
      }
    }
    else {
      resolved.tsr = []
    }

    if (msg.tsr_vision_only !== undefined) {
      resolved.tsr_vision_only = TSRVisionOnlySign.Resolve(msg.tsr_vision_only)
    }
    else {
      resolved.tsr_vision_only = new TSRVisionOnlySign()
    }

    if (msg.gyro !== undefined) {
      resolved.gyro = Gyro.Resolve(msg.gyro)
    }
    else {
      resolved.gyro = new Gyro()
    }

    if (msg.smart_adas !== undefined) {
      resolved.smart_adas = SmartADAS.Resolve(msg.smart_adas)
    }
    else {
      resolved.smart_adas = new SmartADAS()
    }

    if (msg.seeq !== undefined) {
      resolved.seeq = SeeQ.Resolve(msg.seeq)
    }
    else {
      resolved.seeq = new SeeQ()
    }

    return resolved;
    }
};

module.exports = StandardCAN;
