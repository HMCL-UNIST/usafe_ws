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

class SmartADAS {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.persistent_on_off = null;
      this.volume_level = null;
      this.hmw_level = null;
      this.ldw_volume_level = null;
      this.hmw_volume_level = null;
      this.ldw_level = null;
      this.pedestrian_warning_level = null;
      this.sli_warning_level = null;
      this.blinker_reminder_level = null;
      this.virtual_bumper_level = null;
      this.hw_repeatable_level = null;
      this.buzzer_min_volume = null;
      this.buzzer_max_volume = null;
      this.buzzer_hmw_min_volume = null;
      this.buzzer_hmw_max_volume = null;
      this.buzzer_ldw_min_volume = null;
      this.buzzer_ldw_max_volume = null;
      this.ewiii_speed_indication = null;
      this.disable_system_off = null;
      this.calibration_source = null;
      this.ldw_min_value = null;
      this.ldw_max_value = null;
      this.ldw_speed = null;
      this.ped_min_value = null;
      this.ped_max_value = null;
      this.speed_for_high_low_beam_control = null;
      this.virtual_bumper_min_value = null;
      this.virtual_bumper_max_value = null;
      this.blinker_reminder_min_value = null;
      this.blinker_reminder_max_value = null;
      this.hmw_min_value = null;
      this.hmw_max_value = null;
      this.hmw_repeatable_min_value = null;
      this.hmw_repeatable_max_value = null;
      this.sli_min_value = null;
      this.sli_max_value = null;
      this.sli_delta_round_step = null;
      this.sli_delta_round_upwards = null;
      this.country_code = null;
      this.sli_unit_speed = null;
      this.tamper_alert_on_frames = null;
      this.tamper_alert_off_frames = null;
      this.tamper_alert_enable_j1939 = null;
      this.menu_ticks = null;
      this.advanced_menu_ticks = null;
    }
    else {
      if (initObj.hasOwnProperty('persistent_on_off')) {
        this.persistent_on_off = initObj.persistent_on_off
      }
      else {
        this.persistent_on_off = 0;
      }
      if (initObj.hasOwnProperty('volume_level')) {
        this.volume_level = initObj.volume_level
      }
      else {
        this.volume_level = 0;
      }
      if (initObj.hasOwnProperty('hmw_level')) {
        this.hmw_level = initObj.hmw_level
      }
      else {
        this.hmw_level = 0;
      }
      if (initObj.hasOwnProperty('ldw_volume_level')) {
        this.ldw_volume_level = initObj.ldw_volume_level
      }
      else {
        this.ldw_volume_level = 0;
      }
      if (initObj.hasOwnProperty('hmw_volume_level')) {
        this.hmw_volume_level = initObj.hmw_volume_level
      }
      else {
        this.hmw_volume_level = 0;
      }
      if (initObj.hasOwnProperty('ldw_level')) {
        this.ldw_level = initObj.ldw_level
      }
      else {
        this.ldw_level = 0;
      }
      if (initObj.hasOwnProperty('pedestrian_warning_level')) {
        this.pedestrian_warning_level = initObj.pedestrian_warning_level
      }
      else {
        this.pedestrian_warning_level = 0;
      }
      if (initObj.hasOwnProperty('sli_warning_level')) {
        this.sli_warning_level = initObj.sli_warning_level
      }
      else {
        this.sli_warning_level = 0;
      }
      if (initObj.hasOwnProperty('blinker_reminder_level')) {
        this.blinker_reminder_level = initObj.blinker_reminder_level
      }
      else {
        this.blinker_reminder_level = 0;
      }
      if (initObj.hasOwnProperty('virtual_bumper_level')) {
        this.virtual_bumper_level = initObj.virtual_bumper_level
      }
      else {
        this.virtual_bumper_level = 0;
      }
      if (initObj.hasOwnProperty('hw_repeatable_level')) {
        this.hw_repeatable_level = initObj.hw_repeatable_level
      }
      else {
        this.hw_repeatable_level = 0;
      }
      if (initObj.hasOwnProperty('buzzer_min_volume')) {
        this.buzzer_min_volume = initObj.buzzer_min_volume
      }
      else {
        this.buzzer_min_volume = 0;
      }
      if (initObj.hasOwnProperty('buzzer_max_volume')) {
        this.buzzer_max_volume = initObj.buzzer_max_volume
      }
      else {
        this.buzzer_max_volume = 0;
      }
      if (initObj.hasOwnProperty('buzzer_hmw_min_volume')) {
        this.buzzer_hmw_min_volume = initObj.buzzer_hmw_min_volume
      }
      else {
        this.buzzer_hmw_min_volume = 0;
      }
      if (initObj.hasOwnProperty('buzzer_hmw_max_volume')) {
        this.buzzer_hmw_max_volume = initObj.buzzer_hmw_max_volume
      }
      else {
        this.buzzer_hmw_max_volume = 0;
      }
      if (initObj.hasOwnProperty('buzzer_ldw_min_volume')) {
        this.buzzer_ldw_min_volume = initObj.buzzer_ldw_min_volume
      }
      else {
        this.buzzer_ldw_min_volume = 0;
      }
      if (initObj.hasOwnProperty('buzzer_ldw_max_volume')) {
        this.buzzer_ldw_max_volume = initObj.buzzer_ldw_max_volume
      }
      else {
        this.buzzer_ldw_max_volume = 0;
      }
      if (initObj.hasOwnProperty('ewiii_speed_indication')) {
        this.ewiii_speed_indication = initObj.ewiii_speed_indication
      }
      else {
        this.ewiii_speed_indication = 0;
      }
      if (initObj.hasOwnProperty('disable_system_off')) {
        this.disable_system_off = initObj.disable_system_off
      }
      else {
        this.disable_system_off = 0;
      }
      if (initObj.hasOwnProperty('calibration_source')) {
        this.calibration_source = initObj.calibration_source
      }
      else {
        this.calibration_source = 0;
      }
      if (initObj.hasOwnProperty('ldw_min_value')) {
        this.ldw_min_value = initObj.ldw_min_value
      }
      else {
        this.ldw_min_value = 0;
      }
      if (initObj.hasOwnProperty('ldw_max_value')) {
        this.ldw_max_value = initObj.ldw_max_value
      }
      else {
        this.ldw_max_value = 0;
      }
      if (initObj.hasOwnProperty('ldw_speed')) {
        this.ldw_speed = initObj.ldw_speed
      }
      else {
        this.ldw_speed = 0;
      }
      if (initObj.hasOwnProperty('ped_min_value')) {
        this.ped_min_value = initObj.ped_min_value
      }
      else {
        this.ped_min_value = 0;
      }
      if (initObj.hasOwnProperty('ped_max_value')) {
        this.ped_max_value = initObj.ped_max_value
      }
      else {
        this.ped_max_value = 0;
      }
      if (initObj.hasOwnProperty('speed_for_high_low_beam_control')) {
        this.speed_for_high_low_beam_control = initObj.speed_for_high_low_beam_control
      }
      else {
        this.speed_for_high_low_beam_control = 0;
      }
      if (initObj.hasOwnProperty('virtual_bumper_min_value')) {
        this.virtual_bumper_min_value = initObj.virtual_bumper_min_value
      }
      else {
        this.virtual_bumper_min_value = 0;
      }
      if (initObj.hasOwnProperty('virtual_bumper_max_value')) {
        this.virtual_bumper_max_value = initObj.virtual_bumper_max_value
      }
      else {
        this.virtual_bumper_max_value = 0;
      }
      if (initObj.hasOwnProperty('blinker_reminder_min_value')) {
        this.blinker_reminder_min_value = initObj.blinker_reminder_min_value
      }
      else {
        this.blinker_reminder_min_value = 0;
      }
      if (initObj.hasOwnProperty('blinker_reminder_max_value')) {
        this.blinker_reminder_max_value = initObj.blinker_reminder_max_value
      }
      else {
        this.blinker_reminder_max_value = 0;
      }
      if (initObj.hasOwnProperty('hmw_min_value')) {
        this.hmw_min_value = initObj.hmw_min_value
      }
      else {
        this.hmw_min_value = 0;
      }
      if (initObj.hasOwnProperty('hmw_max_value')) {
        this.hmw_max_value = initObj.hmw_max_value
      }
      else {
        this.hmw_max_value = 0;
      }
      if (initObj.hasOwnProperty('hmw_repeatable_min_value')) {
        this.hmw_repeatable_min_value = initObj.hmw_repeatable_min_value
      }
      else {
        this.hmw_repeatable_min_value = 0;
      }
      if (initObj.hasOwnProperty('hmw_repeatable_max_value')) {
        this.hmw_repeatable_max_value = initObj.hmw_repeatable_max_value
      }
      else {
        this.hmw_repeatable_max_value = 0;
      }
      if (initObj.hasOwnProperty('sli_min_value')) {
        this.sli_min_value = initObj.sli_min_value
      }
      else {
        this.sli_min_value = 0;
      }
      if (initObj.hasOwnProperty('sli_max_value')) {
        this.sli_max_value = initObj.sli_max_value
      }
      else {
        this.sli_max_value = 0;
      }
      if (initObj.hasOwnProperty('sli_delta_round_step')) {
        this.sli_delta_round_step = initObj.sli_delta_round_step
      }
      else {
        this.sli_delta_round_step = 0;
      }
      if (initObj.hasOwnProperty('sli_delta_round_upwards')) {
        this.sli_delta_round_upwards = initObj.sli_delta_round_upwards
      }
      else {
        this.sli_delta_round_upwards = 0;
      }
      if (initObj.hasOwnProperty('country_code')) {
        this.country_code = initObj.country_code
      }
      else {
        this.country_code = 0;
      }
      if (initObj.hasOwnProperty('sli_unit_speed')) {
        this.sli_unit_speed = initObj.sli_unit_speed
      }
      else {
        this.sli_unit_speed = 0;
      }
      if (initObj.hasOwnProperty('tamper_alert_on_frames')) {
        this.tamper_alert_on_frames = initObj.tamper_alert_on_frames
      }
      else {
        this.tamper_alert_on_frames = 0;
      }
      if (initObj.hasOwnProperty('tamper_alert_off_frames')) {
        this.tamper_alert_off_frames = initObj.tamper_alert_off_frames
      }
      else {
        this.tamper_alert_off_frames = 0;
      }
      if (initObj.hasOwnProperty('tamper_alert_enable_j1939')) {
        this.tamper_alert_enable_j1939 = initObj.tamper_alert_enable_j1939
      }
      else {
        this.tamper_alert_enable_j1939 = 0;
      }
      if (initObj.hasOwnProperty('menu_ticks')) {
        this.menu_ticks = initObj.menu_ticks
      }
      else {
        this.menu_ticks = new Array(16).fill(0);
      }
      if (initObj.hasOwnProperty('advanced_menu_ticks')) {
        this.advanced_menu_ticks = initObj.advanced_menu_ticks
      }
      else {
        this.advanced_menu_ticks = new Array(16).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SmartADAS
    // Serialize message field [persistent_on_off]
    bufferOffset = _serializer.uint8(obj.persistent_on_off, buffer, bufferOffset);
    // Serialize message field [volume_level]
    bufferOffset = _serializer.uint8(obj.volume_level, buffer, bufferOffset);
    // Serialize message field [hmw_level]
    bufferOffset = _serializer.uint8(obj.hmw_level, buffer, bufferOffset);
    // Serialize message field [ldw_volume_level]
    bufferOffset = _serializer.uint8(obj.ldw_volume_level, buffer, bufferOffset);
    // Serialize message field [hmw_volume_level]
    bufferOffset = _serializer.uint8(obj.hmw_volume_level, buffer, bufferOffset);
    // Serialize message field [ldw_level]
    bufferOffset = _serializer.uint8(obj.ldw_level, buffer, bufferOffset);
    // Serialize message field [pedestrian_warning_level]
    bufferOffset = _serializer.uint8(obj.pedestrian_warning_level, buffer, bufferOffset);
    // Serialize message field [sli_warning_level]
    bufferOffset = _serializer.uint8(obj.sli_warning_level, buffer, bufferOffset);
    // Serialize message field [blinker_reminder_level]
    bufferOffset = _serializer.uint8(obj.blinker_reminder_level, buffer, bufferOffset);
    // Serialize message field [virtual_bumper_level]
    bufferOffset = _serializer.uint8(obj.virtual_bumper_level, buffer, bufferOffset);
    // Serialize message field [hw_repeatable_level]
    bufferOffset = _serializer.uint8(obj.hw_repeatable_level, buffer, bufferOffset);
    // Serialize message field [buzzer_min_volume]
    bufferOffset = _serializer.uint8(obj.buzzer_min_volume, buffer, bufferOffset);
    // Serialize message field [buzzer_max_volume]
    bufferOffset = _serializer.uint8(obj.buzzer_max_volume, buffer, bufferOffset);
    // Serialize message field [buzzer_hmw_min_volume]
    bufferOffset = _serializer.uint8(obj.buzzer_hmw_min_volume, buffer, bufferOffset);
    // Serialize message field [buzzer_hmw_max_volume]
    bufferOffset = _serializer.uint8(obj.buzzer_hmw_max_volume, buffer, bufferOffset);
    // Serialize message field [buzzer_ldw_min_volume]
    bufferOffset = _serializer.uint8(obj.buzzer_ldw_min_volume, buffer, bufferOffset);
    // Serialize message field [buzzer_ldw_max_volume]
    bufferOffset = _serializer.uint8(obj.buzzer_ldw_max_volume, buffer, bufferOffset);
    // Serialize message field [ewiii_speed_indication]
    bufferOffset = _serializer.uint8(obj.ewiii_speed_indication, buffer, bufferOffset);
    // Serialize message field [disable_system_off]
    bufferOffset = _serializer.uint8(obj.disable_system_off, buffer, bufferOffset);
    // Serialize message field [calibration_source]
    bufferOffset = _serializer.uint8(obj.calibration_source, buffer, bufferOffset);
    // Serialize message field [ldw_min_value]
    bufferOffset = _serializer.uint8(obj.ldw_min_value, buffer, bufferOffset);
    // Serialize message field [ldw_max_value]
    bufferOffset = _serializer.uint8(obj.ldw_max_value, buffer, bufferOffset);
    // Serialize message field [ldw_speed]
    bufferOffset = _serializer.uint8(obj.ldw_speed, buffer, bufferOffset);
    // Serialize message field [ped_min_value]
    bufferOffset = _serializer.uint8(obj.ped_min_value, buffer, bufferOffset);
    // Serialize message field [ped_max_value]
    bufferOffset = _serializer.uint8(obj.ped_max_value, buffer, bufferOffset);
    // Serialize message field [speed_for_high_low_beam_control]
    bufferOffset = _serializer.uint8(obj.speed_for_high_low_beam_control, buffer, bufferOffset);
    // Serialize message field [virtual_bumper_min_value]
    bufferOffset = _serializer.uint8(obj.virtual_bumper_min_value, buffer, bufferOffset);
    // Serialize message field [virtual_bumper_max_value]
    bufferOffset = _serializer.uint8(obj.virtual_bumper_max_value, buffer, bufferOffset);
    // Serialize message field [blinker_reminder_min_value]
    bufferOffset = _serializer.uint8(obj.blinker_reminder_min_value, buffer, bufferOffset);
    // Serialize message field [blinker_reminder_max_value]
    bufferOffset = _serializer.uint8(obj.blinker_reminder_max_value, buffer, bufferOffset);
    // Serialize message field [hmw_min_value]
    bufferOffset = _serializer.uint8(obj.hmw_min_value, buffer, bufferOffset);
    // Serialize message field [hmw_max_value]
    bufferOffset = _serializer.uint8(obj.hmw_max_value, buffer, bufferOffset);
    // Serialize message field [hmw_repeatable_min_value]
    bufferOffset = _serializer.uint8(obj.hmw_repeatable_min_value, buffer, bufferOffset);
    // Serialize message field [hmw_repeatable_max_value]
    bufferOffset = _serializer.uint8(obj.hmw_repeatable_max_value, buffer, bufferOffset);
    // Serialize message field [sli_min_value]
    bufferOffset = _serializer.uint8(obj.sli_min_value, buffer, bufferOffset);
    // Serialize message field [sli_max_value]
    bufferOffset = _serializer.uint8(obj.sli_max_value, buffer, bufferOffset);
    // Serialize message field [sli_delta_round_step]
    bufferOffset = _serializer.uint8(obj.sli_delta_round_step, buffer, bufferOffset);
    // Serialize message field [sli_delta_round_upwards]
    bufferOffset = _serializer.uint8(obj.sli_delta_round_upwards, buffer, bufferOffset);
    // Serialize message field [country_code]
    bufferOffset = _serializer.uint8(obj.country_code, buffer, bufferOffset);
    // Serialize message field [sli_unit_speed]
    bufferOffset = _serializer.uint8(obj.sli_unit_speed, buffer, bufferOffset);
    // Serialize message field [tamper_alert_on_frames]
    bufferOffset = _serializer.uint8(obj.tamper_alert_on_frames, buffer, bufferOffset);
    // Serialize message field [tamper_alert_off_frames]
    bufferOffset = _serializer.uint8(obj.tamper_alert_off_frames, buffer, bufferOffset);
    // Serialize message field [tamper_alert_enable_j1939]
    bufferOffset = _serializer.uint8(obj.tamper_alert_enable_j1939, buffer, bufferOffset);
    // Check that the constant length array field [menu_ticks] has the right length
    if (obj.menu_ticks.length !== 16) {
      throw new Error('Unable to serialize array field menu_ticks - length must be 16')
    }
    // Serialize message field [menu_ticks]
    bufferOffset = _arraySerializer.bool(obj.menu_ticks, buffer, bufferOffset, 16);
    // Check that the constant length array field [advanced_menu_ticks] has the right length
    if (obj.advanced_menu_ticks.length !== 16) {
      throw new Error('Unable to serialize array field advanced_menu_ticks - length must be 16')
    }
    // Serialize message field [advanced_menu_ticks]
    bufferOffset = _arraySerializer.bool(obj.advanced_menu_ticks, buffer, bufferOffset, 16);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SmartADAS
    let len;
    let data = new SmartADAS(null);
    // Deserialize message field [persistent_on_off]
    data.persistent_on_off = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [volume_level]
    data.volume_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hmw_level]
    data.hmw_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ldw_volume_level]
    data.ldw_volume_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hmw_volume_level]
    data.hmw_volume_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ldw_level]
    data.ldw_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [pedestrian_warning_level]
    data.pedestrian_warning_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sli_warning_level]
    data.sli_warning_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [blinker_reminder_level]
    data.blinker_reminder_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [virtual_bumper_level]
    data.virtual_bumper_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hw_repeatable_level]
    data.hw_repeatable_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [buzzer_min_volume]
    data.buzzer_min_volume = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [buzzer_max_volume]
    data.buzzer_max_volume = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [buzzer_hmw_min_volume]
    data.buzzer_hmw_min_volume = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [buzzer_hmw_max_volume]
    data.buzzer_hmw_max_volume = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [buzzer_ldw_min_volume]
    data.buzzer_ldw_min_volume = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [buzzer_ldw_max_volume]
    data.buzzer_ldw_max_volume = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ewiii_speed_indication]
    data.ewiii_speed_indication = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [disable_system_off]
    data.disable_system_off = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [calibration_source]
    data.calibration_source = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ldw_min_value]
    data.ldw_min_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ldw_max_value]
    data.ldw_max_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ldw_speed]
    data.ldw_speed = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ped_min_value]
    data.ped_min_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ped_max_value]
    data.ped_max_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [speed_for_high_low_beam_control]
    data.speed_for_high_low_beam_control = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [virtual_bumper_min_value]
    data.virtual_bumper_min_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [virtual_bumper_max_value]
    data.virtual_bumper_max_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [blinker_reminder_min_value]
    data.blinker_reminder_min_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [blinker_reminder_max_value]
    data.blinker_reminder_max_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hmw_min_value]
    data.hmw_min_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hmw_max_value]
    data.hmw_max_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hmw_repeatable_min_value]
    data.hmw_repeatable_min_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [hmw_repeatable_max_value]
    data.hmw_repeatable_max_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sli_min_value]
    data.sli_min_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sli_max_value]
    data.sli_max_value = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sli_delta_round_step]
    data.sli_delta_round_step = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sli_delta_round_upwards]
    data.sli_delta_round_upwards = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [country_code]
    data.country_code = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sli_unit_speed]
    data.sli_unit_speed = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [tamper_alert_on_frames]
    data.tamper_alert_on_frames = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [tamper_alert_off_frames]
    data.tamper_alert_off_frames = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [tamper_alert_enable_j1939]
    data.tamper_alert_enable_j1939 = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [menu_ticks]
    data.menu_ticks = _arrayDeserializer.bool(buffer, bufferOffset, 16)
    // Deserialize message field [advanced_menu_ticks]
    data.advanced_menu_ticks = _arrayDeserializer.bool(buffer, bufferOffset, 16)
    return data;
  }

  static getMessageSize(object) {
    return 75;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/SmartADAS';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2234fe7679b621d841bd2d8b34cf58ad';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new SmartADAS(null);
    if (msg.persistent_on_off !== undefined) {
      resolved.persistent_on_off = msg.persistent_on_off;
    }
    else {
      resolved.persistent_on_off = 0
    }

    if (msg.volume_level !== undefined) {
      resolved.volume_level = msg.volume_level;
    }
    else {
      resolved.volume_level = 0
    }

    if (msg.hmw_level !== undefined) {
      resolved.hmw_level = msg.hmw_level;
    }
    else {
      resolved.hmw_level = 0
    }

    if (msg.ldw_volume_level !== undefined) {
      resolved.ldw_volume_level = msg.ldw_volume_level;
    }
    else {
      resolved.ldw_volume_level = 0
    }

    if (msg.hmw_volume_level !== undefined) {
      resolved.hmw_volume_level = msg.hmw_volume_level;
    }
    else {
      resolved.hmw_volume_level = 0
    }

    if (msg.ldw_level !== undefined) {
      resolved.ldw_level = msg.ldw_level;
    }
    else {
      resolved.ldw_level = 0
    }

    if (msg.pedestrian_warning_level !== undefined) {
      resolved.pedestrian_warning_level = msg.pedestrian_warning_level;
    }
    else {
      resolved.pedestrian_warning_level = 0
    }

    if (msg.sli_warning_level !== undefined) {
      resolved.sli_warning_level = msg.sli_warning_level;
    }
    else {
      resolved.sli_warning_level = 0
    }

    if (msg.blinker_reminder_level !== undefined) {
      resolved.blinker_reminder_level = msg.blinker_reminder_level;
    }
    else {
      resolved.blinker_reminder_level = 0
    }

    if (msg.virtual_bumper_level !== undefined) {
      resolved.virtual_bumper_level = msg.virtual_bumper_level;
    }
    else {
      resolved.virtual_bumper_level = 0
    }

    if (msg.hw_repeatable_level !== undefined) {
      resolved.hw_repeatable_level = msg.hw_repeatable_level;
    }
    else {
      resolved.hw_repeatable_level = 0
    }

    if (msg.buzzer_min_volume !== undefined) {
      resolved.buzzer_min_volume = msg.buzzer_min_volume;
    }
    else {
      resolved.buzzer_min_volume = 0
    }

    if (msg.buzzer_max_volume !== undefined) {
      resolved.buzzer_max_volume = msg.buzzer_max_volume;
    }
    else {
      resolved.buzzer_max_volume = 0
    }

    if (msg.buzzer_hmw_min_volume !== undefined) {
      resolved.buzzer_hmw_min_volume = msg.buzzer_hmw_min_volume;
    }
    else {
      resolved.buzzer_hmw_min_volume = 0
    }

    if (msg.buzzer_hmw_max_volume !== undefined) {
      resolved.buzzer_hmw_max_volume = msg.buzzer_hmw_max_volume;
    }
    else {
      resolved.buzzer_hmw_max_volume = 0
    }

    if (msg.buzzer_ldw_min_volume !== undefined) {
      resolved.buzzer_ldw_min_volume = msg.buzzer_ldw_min_volume;
    }
    else {
      resolved.buzzer_ldw_min_volume = 0
    }

    if (msg.buzzer_ldw_max_volume !== undefined) {
      resolved.buzzer_ldw_max_volume = msg.buzzer_ldw_max_volume;
    }
    else {
      resolved.buzzer_ldw_max_volume = 0
    }

    if (msg.ewiii_speed_indication !== undefined) {
      resolved.ewiii_speed_indication = msg.ewiii_speed_indication;
    }
    else {
      resolved.ewiii_speed_indication = 0
    }

    if (msg.disable_system_off !== undefined) {
      resolved.disable_system_off = msg.disable_system_off;
    }
    else {
      resolved.disable_system_off = 0
    }

    if (msg.calibration_source !== undefined) {
      resolved.calibration_source = msg.calibration_source;
    }
    else {
      resolved.calibration_source = 0
    }

    if (msg.ldw_min_value !== undefined) {
      resolved.ldw_min_value = msg.ldw_min_value;
    }
    else {
      resolved.ldw_min_value = 0
    }

    if (msg.ldw_max_value !== undefined) {
      resolved.ldw_max_value = msg.ldw_max_value;
    }
    else {
      resolved.ldw_max_value = 0
    }

    if (msg.ldw_speed !== undefined) {
      resolved.ldw_speed = msg.ldw_speed;
    }
    else {
      resolved.ldw_speed = 0
    }

    if (msg.ped_min_value !== undefined) {
      resolved.ped_min_value = msg.ped_min_value;
    }
    else {
      resolved.ped_min_value = 0
    }

    if (msg.ped_max_value !== undefined) {
      resolved.ped_max_value = msg.ped_max_value;
    }
    else {
      resolved.ped_max_value = 0
    }

    if (msg.speed_for_high_low_beam_control !== undefined) {
      resolved.speed_for_high_low_beam_control = msg.speed_for_high_low_beam_control;
    }
    else {
      resolved.speed_for_high_low_beam_control = 0
    }

    if (msg.virtual_bumper_min_value !== undefined) {
      resolved.virtual_bumper_min_value = msg.virtual_bumper_min_value;
    }
    else {
      resolved.virtual_bumper_min_value = 0
    }

    if (msg.virtual_bumper_max_value !== undefined) {
      resolved.virtual_bumper_max_value = msg.virtual_bumper_max_value;
    }
    else {
      resolved.virtual_bumper_max_value = 0
    }

    if (msg.blinker_reminder_min_value !== undefined) {
      resolved.blinker_reminder_min_value = msg.blinker_reminder_min_value;
    }
    else {
      resolved.blinker_reminder_min_value = 0
    }

    if (msg.blinker_reminder_max_value !== undefined) {
      resolved.blinker_reminder_max_value = msg.blinker_reminder_max_value;
    }
    else {
      resolved.blinker_reminder_max_value = 0
    }

    if (msg.hmw_min_value !== undefined) {
      resolved.hmw_min_value = msg.hmw_min_value;
    }
    else {
      resolved.hmw_min_value = 0
    }

    if (msg.hmw_max_value !== undefined) {
      resolved.hmw_max_value = msg.hmw_max_value;
    }
    else {
      resolved.hmw_max_value = 0
    }

    if (msg.hmw_repeatable_min_value !== undefined) {
      resolved.hmw_repeatable_min_value = msg.hmw_repeatable_min_value;
    }
    else {
      resolved.hmw_repeatable_min_value = 0
    }

    if (msg.hmw_repeatable_max_value !== undefined) {
      resolved.hmw_repeatable_max_value = msg.hmw_repeatable_max_value;
    }
    else {
      resolved.hmw_repeatable_max_value = 0
    }

    if (msg.sli_min_value !== undefined) {
      resolved.sli_min_value = msg.sli_min_value;
    }
    else {
      resolved.sli_min_value = 0
    }

    if (msg.sli_max_value !== undefined) {
      resolved.sli_max_value = msg.sli_max_value;
    }
    else {
      resolved.sli_max_value = 0
    }

    if (msg.sli_delta_round_step !== undefined) {
      resolved.sli_delta_round_step = msg.sli_delta_round_step;
    }
    else {
      resolved.sli_delta_round_step = 0
    }

    if (msg.sli_delta_round_upwards !== undefined) {
      resolved.sli_delta_round_upwards = msg.sli_delta_round_upwards;
    }
    else {
      resolved.sli_delta_round_upwards = 0
    }

    if (msg.country_code !== undefined) {
      resolved.country_code = msg.country_code;
    }
    else {
      resolved.country_code = 0
    }

    if (msg.sli_unit_speed !== undefined) {
      resolved.sli_unit_speed = msg.sli_unit_speed;
    }
    else {
      resolved.sli_unit_speed = 0
    }

    if (msg.tamper_alert_on_frames !== undefined) {
      resolved.tamper_alert_on_frames = msg.tamper_alert_on_frames;
    }
    else {
      resolved.tamper_alert_on_frames = 0
    }

    if (msg.tamper_alert_off_frames !== undefined) {
      resolved.tamper_alert_off_frames = msg.tamper_alert_off_frames;
    }
    else {
      resolved.tamper_alert_off_frames = 0
    }

    if (msg.tamper_alert_enable_j1939 !== undefined) {
      resolved.tamper_alert_enable_j1939 = msg.tamper_alert_enable_j1939;
    }
    else {
      resolved.tamper_alert_enable_j1939 = 0
    }

    if (msg.menu_ticks !== undefined) {
      resolved.menu_ticks = msg.menu_ticks;
    }
    else {
      resolved.menu_ticks = new Array(16).fill(0)
    }

    if (msg.advanced_menu_ticks !== undefined) {
      resolved.advanced_menu_ticks = msg.advanced_menu_ticks;
    }
    else {
      resolved.advanced_menu_ticks = new Array(16).fill(0)
    }

    return resolved;
    }
};

module.exports = SmartADAS;
