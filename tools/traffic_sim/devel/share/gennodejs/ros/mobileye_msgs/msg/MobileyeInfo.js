// Auto-generated. Do not edit!

// (in-package mobileye_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let LKAlane = require('./LKAlane.js');
let ReferencePoints = require('./ReferencePoints.js');
let Lane = require('./Lane.js');
let ObstacleStatus = require('./ObstacleStatus.js');
let ObstacleData = require('./ObstacleData.js');
let SystemWarnings = require('./SystemWarnings.js');
let CarInfo = require('./CarInfo.js');
let TSR = require('./TSR.js');
let TSRVisionOnlySign = require('./TSRVisionOnlySign.js');
let Gyro = require('./Gyro.js');
let SmartADAS = require('./SmartADAS.js');
let SeeQ = require('./SeeQ.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class MobileyeInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.left_lane = null;
      this.right_lane = null;
      this.reference_points = null;
      this.number_of_next_lane_markers = null;
      this.next_lane = null;
      this.lane = null;
      this.obstacle_status = null;
      this.obstacle_data = null;
      this.system_warnings = null;
      this.car_info = null;
      this.tsr = null;
      this.tsr_vision_only = null;
      this.gyro = null;
      this.smart_adas = null;
      this.seeq = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('left_lane')) {
        this.left_lane = initObj.left_lane
      }
      else {
        this.left_lane = new LKAlane();
      }
      if (initObj.hasOwnProperty('right_lane')) {
        this.right_lane = initObj.right_lane
      }
      else {
        this.right_lane = new LKAlane();
      }
      if (initObj.hasOwnProperty('reference_points')) {
        this.reference_points = initObj.reference_points
      }
      else {
        this.reference_points = new ReferencePoints();
      }
      if (initObj.hasOwnProperty('number_of_next_lane_markers')) {
        this.number_of_next_lane_markers = initObj.number_of_next_lane_markers
      }
      else {
        this.number_of_next_lane_markers = 0;
      }
      if (initObj.hasOwnProperty('next_lane')) {
        this.next_lane = initObj.next_lane
      }
      else {
        this.next_lane = [];
      }
      if (initObj.hasOwnProperty('lane')) {
        this.lane = initObj.lane
      }
      else {
        this.lane = new Lane();
      }
      if (initObj.hasOwnProperty('obstacle_status')) {
        this.obstacle_status = initObj.obstacle_status
      }
      else {
        this.obstacle_status = new ObstacleStatus();
      }
      if (initObj.hasOwnProperty('obstacle_data')) {
        this.obstacle_data = initObj.obstacle_data
      }
      else {
        this.obstacle_data = [];
      }
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
    // Serializes a message object of type MobileyeInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [left_lane]
    bufferOffset = LKAlane.serialize(obj.left_lane, buffer, bufferOffset);
    // Serialize message field [right_lane]
    bufferOffset = LKAlane.serialize(obj.right_lane, buffer, bufferOffset);
    // Serialize message field [reference_points]
    bufferOffset = ReferencePoints.serialize(obj.reference_points, buffer, bufferOffset);
    // Serialize message field [number_of_next_lane_markers]
    bufferOffset = _serializer.uint8(obj.number_of_next_lane_markers, buffer, bufferOffset);
    // Serialize message field [next_lane]
    // Serialize the length for message field [next_lane]
    bufferOffset = _serializer.uint32(obj.next_lane.length, buffer, bufferOffset);
    obj.next_lane.forEach((val) => {
      bufferOffset = LKAlane.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [lane]
    bufferOffset = Lane.serialize(obj.lane, buffer, bufferOffset);
    // Serialize message field [obstacle_status]
    bufferOffset = ObstacleStatus.serialize(obj.obstacle_status, buffer, bufferOffset);
    // Serialize message field [obstacle_data]
    // Serialize the length for message field [obstacle_data]
    bufferOffset = _serializer.uint32(obj.obstacle_data.length, buffer, bufferOffset);
    obj.obstacle_data.forEach((val) => {
      bufferOffset = ObstacleData.serialize(val, buffer, bufferOffset);
    });
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
    //deserializes a message object of type MobileyeInfo
    let len;
    let data = new MobileyeInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [left_lane]
    data.left_lane = LKAlane.deserialize(buffer, bufferOffset);
    // Deserialize message field [right_lane]
    data.right_lane = LKAlane.deserialize(buffer, bufferOffset);
    // Deserialize message field [reference_points]
    data.reference_points = ReferencePoints.deserialize(buffer, bufferOffset);
    // Deserialize message field [number_of_next_lane_markers]
    data.number_of_next_lane_markers = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [next_lane]
    // Deserialize array length for message field [next_lane]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.next_lane = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.next_lane[i] = LKAlane.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [lane]
    data.lane = Lane.deserialize(buffer, bufferOffset);
    // Deserialize message field [obstacle_status]
    data.obstacle_status = ObstacleStatus.deserialize(buffer, bufferOffset);
    // Deserialize message field [obstacle_data]
    // Deserialize array length for message field [obstacle_data]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.obstacle_data = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.obstacle_data[i] = ObstacleData.deserialize(buffer, bufferOffset)
    }
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
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 28 * object.next_lane.length;
    length += 57 * object.obstacle_data.length;
    length += 15 * object.tsr.length;
    return length + 257;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mobileye_msgs/MobileyeInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f347fd8c2960b4f7e8d7a1b937971d62';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    LKAlane left_lane
    LKAlane right_lane
    
    ReferencePoints reference_points
    
    uint8 number_of_next_lane_markers
    
    LKAlane[] next_lane
    
    Lane lane
    
    ObstacleStatus obstacle_status
    ObstacleData[] obstacle_data
    
    SystemWarnings system_warnings
    CarInfo car_info
    TSR[] tsr
    TSRVisionOnlySign tsr_vision_only
    Gyro gyro
    SmartADAS smart_adas
    SeeQ seeq
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
    MSG: mobileye_msgs/LKAlane
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
    
    ================================================================================
    MSG: mobileye_msgs/ReferencePoints
    float32 ref_point1_position
    float32 ref_point1_distance
    bool ref_point1_validity
    float32 ref_point2_position
    float32 ref_point2_distance
    bool ref_point2_validity
    ================================================================================
    MSG: mobileye_msgs/Lane
    float32 lane_curvature
    float32 lane_heading
    
    bool ca
    float32 pitch_angle
    float32 yaw_angle
    
    bool right_ldw_availability
    bool left_ldw_availability
    
    ================================================================================
    MSG: mobileye_msgs/ObstacleStatus
    uint8 number_of_obstacles
    uint8 timestamp
    
    bool left_close_rang_cut_in
    bool right_close_rang_cut_in
    
    uint8 go
    bool close_car
    uint8 failsafe
    
    ================================================================================
    MSG: mobileye_msgs/ObstacleData
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
    const resolved = new MobileyeInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.left_lane !== undefined) {
      resolved.left_lane = LKAlane.Resolve(msg.left_lane)
    }
    else {
      resolved.left_lane = new LKAlane()
    }

    if (msg.right_lane !== undefined) {
      resolved.right_lane = LKAlane.Resolve(msg.right_lane)
    }
    else {
      resolved.right_lane = new LKAlane()
    }

    if (msg.reference_points !== undefined) {
      resolved.reference_points = ReferencePoints.Resolve(msg.reference_points)
    }
    else {
      resolved.reference_points = new ReferencePoints()
    }

    if (msg.number_of_next_lane_markers !== undefined) {
      resolved.number_of_next_lane_markers = msg.number_of_next_lane_markers;
    }
    else {
      resolved.number_of_next_lane_markers = 0
    }

    if (msg.next_lane !== undefined) {
      resolved.next_lane = new Array(msg.next_lane.length);
      for (let i = 0; i < resolved.next_lane.length; ++i) {
        resolved.next_lane[i] = LKAlane.Resolve(msg.next_lane[i]);
      }
    }
    else {
      resolved.next_lane = []
    }

    if (msg.lane !== undefined) {
      resolved.lane = Lane.Resolve(msg.lane)
    }
    else {
      resolved.lane = new Lane()
    }

    if (msg.obstacle_status !== undefined) {
      resolved.obstacle_status = ObstacleStatus.Resolve(msg.obstacle_status)
    }
    else {
      resolved.obstacle_status = new ObstacleStatus()
    }

    if (msg.obstacle_data !== undefined) {
      resolved.obstacle_data = new Array(msg.obstacle_data.length);
      for (let i = 0; i < resolved.obstacle_data.length; ++i) {
        resolved.obstacle_data[i] = ObstacleData.Resolve(msg.obstacle_data[i]);
      }
    }
    else {
      resolved.obstacle_data = []
    }

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

module.exports = MobileyeInfo;
