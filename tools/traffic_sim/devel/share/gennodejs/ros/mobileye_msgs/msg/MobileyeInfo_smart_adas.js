// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let SmartADAS = require('./SmartADAS.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class MobileyeInfo_smart_adas {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.smart_adas = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('smart_adas')) {
        this.smart_adas = initObj.smart_adas
      }
      else {
        this.smart_adas = new SmartADAS();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MobileyeInfo_smart_adas
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [smart_adas]
    bufferOffset = SmartADAS.serialize(obj.smart_adas, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MobileyeInfo_smart_adas
    let len;
    let data = new MobileyeInfo_smart_adas(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [smart_adas]
    data.smart_adas = SmartADAS.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 75;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/MobileyeInfo_smart_adas';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1b63fad4adb86b289d19be4eadb354a3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    SmartADAS smart_adas
    
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MobileyeInfo_smart_adas(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.smart_adas !== undefined) {
      resolved.smart_adas = SmartADAS.Resolve(msg.smart_adas)
    }
    else {
      resolved.smart_adas = new SmartADAS()
    }

    return resolved;
    }
};

module.exports = MobileyeInfo_smart_adas;
