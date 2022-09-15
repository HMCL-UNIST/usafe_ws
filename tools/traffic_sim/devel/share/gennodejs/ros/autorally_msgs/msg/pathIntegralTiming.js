// Auto-generated. Do not edit!

// (in-package autorally_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class pathIntegralTiming {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.averageTimeBetweenPoses = null;
      this.averageOptimizationCycleTime = null;
      this.averageSleepTime = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('averageTimeBetweenPoses')) {
        this.averageTimeBetweenPoses = initObj.averageTimeBetweenPoses
      }
      else {
        this.averageTimeBetweenPoses = 0.0;
      }
      if (initObj.hasOwnProperty('averageOptimizationCycleTime')) {
        this.averageOptimizationCycleTime = initObj.averageOptimizationCycleTime
      }
      else {
        this.averageOptimizationCycleTime = 0.0;
      }
      if (initObj.hasOwnProperty('averageSleepTime')) {
        this.averageSleepTime = initObj.averageSleepTime
      }
      else {
        this.averageSleepTime = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pathIntegralTiming
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [averageTimeBetweenPoses]
    bufferOffset = _serializer.float64(obj.averageTimeBetweenPoses, buffer, bufferOffset);
    // Serialize message field [averageOptimizationCycleTime]
    bufferOffset = _serializer.float64(obj.averageOptimizationCycleTime, buffer, bufferOffset);
    // Serialize message field [averageSleepTime]
    bufferOffset = _serializer.float64(obj.averageSleepTime, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pathIntegralTiming
    let len;
    let data = new pathIntegralTiming(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [averageTimeBetweenPoses]
    data.averageTimeBetweenPoses = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [averageOptimizationCycleTime]
    data.averageOptimizationCycleTime = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [averageSleepTime]
    data.averageSleepTime = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autorally_msgs/pathIntegralTiming';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3b1cf4994787687384fe2dcbe9c92b69';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    float64 averageTimeBetweenPoses
    float64 averageOptimizationCycleTime
    float64 averageSleepTime
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pathIntegralTiming(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.averageTimeBetweenPoses !== undefined) {
      resolved.averageTimeBetweenPoses = msg.averageTimeBetweenPoses;
    }
    else {
      resolved.averageTimeBetweenPoses = 0.0
    }

    if (msg.averageOptimizationCycleTime !== undefined) {
      resolved.averageOptimizationCycleTime = msg.averageOptimizationCycleTime;
    }
    else {
      resolved.averageOptimizationCycleTime = 0.0
    }

    if (msg.averageSleepTime !== undefined) {
      resolved.averageSleepTime = msg.averageSleepTime;
    }
    else {
      resolved.averageSleepTime = 0.0
    }

    return resolved;
    }
};

module.exports = pathIntegralTiming;
