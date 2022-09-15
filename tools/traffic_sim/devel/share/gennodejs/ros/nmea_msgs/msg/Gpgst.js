// Auto-generated. Do not edit!

// (in-package nmea_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Gpgst {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.message_id = null;
      this.utc_seconds = null;
      this.rms = null;
      this.semi_major_dev = null;
      this.semi_minor_dev = null;
      this.orientation = null;
      this.lat_dev = null;
      this.lon_dev = null;
      this.alt_dev = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('message_id')) {
        this.message_id = initObj.message_id
      }
      else {
        this.message_id = '';
      }
      if (initObj.hasOwnProperty('utc_seconds')) {
        this.utc_seconds = initObj.utc_seconds
      }
      else {
        this.utc_seconds = 0.0;
      }
      if (initObj.hasOwnProperty('rms')) {
        this.rms = initObj.rms
      }
      else {
        this.rms = 0.0;
      }
      if (initObj.hasOwnProperty('semi_major_dev')) {
        this.semi_major_dev = initObj.semi_major_dev
      }
      else {
        this.semi_major_dev = 0.0;
      }
      if (initObj.hasOwnProperty('semi_minor_dev')) {
        this.semi_minor_dev = initObj.semi_minor_dev
      }
      else {
        this.semi_minor_dev = 0.0;
      }
      if (initObj.hasOwnProperty('orientation')) {
        this.orientation = initObj.orientation
      }
      else {
        this.orientation = 0.0;
      }
      if (initObj.hasOwnProperty('lat_dev')) {
        this.lat_dev = initObj.lat_dev
      }
      else {
        this.lat_dev = 0.0;
      }
      if (initObj.hasOwnProperty('lon_dev')) {
        this.lon_dev = initObj.lon_dev
      }
      else {
        this.lon_dev = 0.0;
      }
      if (initObj.hasOwnProperty('alt_dev')) {
        this.alt_dev = initObj.alt_dev
      }
      else {
        this.alt_dev = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Gpgst
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [message_id]
    bufferOffset = _serializer.string(obj.message_id, buffer, bufferOffset);
    // Serialize message field [utc_seconds]
    bufferOffset = _serializer.float64(obj.utc_seconds, buffer, bufferOffset);
    // Serialize message field [rms]
    bufferOffset = _serializer.float32(obj.rms, buffer, bufferOffset);
    // Serialize message field [semi_major_dev]
    bufferOffset = _serializer.float32(obj.semi_major_dev, buffer, bufferOffset);
    // Serialize message field [semi_minor_dev]
    bufferOffset = _serializer.float32(obj.semi_minor_dev, buffer, bufferOffset);
    // Serialize message field [orientation]
    bufferOffset = _serializer.float32(obj.orientation, buffer, bufferOffset);
    // Serialize message field [lat_dev]
    bufferOffset = _serializer.float32(obj.lat_dev, buffer, bufferOffset);
    // Serialize message field [lon_dev]
    bufferOffset = _serializer.float32(obj.lon_dev, buffer, bufferOffset);
    // Serialize message field [alt_dev]
    bufferOffset = _serializer.float32(obj.alt_dev, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Gpgst
    let len;
    let data = new Gpgst(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [message_id]
    data.message_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [utc_seconds]
    data.utc_seconds = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rms]
    data.rms = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [semi_major_dev]
    data.semi_major_dev = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [semi_minor_dev]
    data.semi_minor_dev = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [orientation]
    data.orientation = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [lat_dev]
    data.lat_dev = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [lon_dev]
    data.lon_dev = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [alt_dev]
    data.alt_dev = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += object.message_id.length;
    return length + 40;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nmea_msgs/Gpgst';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e4b77f6f4c211629ab0307177f71dcee';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Message from GPGST NMEA String
    Header header
    
    string message_id
    
    # UTC seconds from midnight
    float64 utc_seconds
    
    # Root-Mean-Squared value of standard deviation of range inputs
    float32 rms
    
    # Standard Deviations of semi-major and minor axes of error ellipse
    float32 semi_major_dev
    float32 semi_minor_dev
    
    # Orientation of the semi-major axis of error ellipse with respect to true north
    float32 orientation
    
    # Standard Deviations of latitude, longitude, and altitude measurements
    float32 lat_dev
    float32 lon_dev
    float32 alt_dev
    
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
    const resolved = new Gpgst(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.message_id !== undefined) {
      resolved.message_id = msg.message_id;
    }
    else {
      resolved.message_id = ''
    }

    if (msg.utc_seconds !== undefined) {
      resolved.utc_seconds = msg.utc_seconds;
    }
    else {
      resolved.utc_seconds = 0.0
    }

    if (msg.rms !== undefined) {
      resolved.rms = msg.rms;
    }
    else {
      resolved.rms = 0.0
    }

    if (msg.semi_major_dev !== undefined) {
      resolved.semi_major_dev = msg.semi_major_dev;
    }
    else {
      resolved.semi_major_dev = 0.0
    }

    if (msg.semi_minor_dev !== undefined) {
      resolved.semi_minor_dev = msg.semi_minor_dev;
    }
    else {
      resolved.semi_minor_dev = 0.0
    }

    if (msg.orientation !== undefined) {
      resolved.orientation = msg.orientation;
    }
    else {
      resolved.orientation = 0.0
    }

    if (msg.lat_dev !== undefined) {
      resolved.lat_dev = msg.lat_dev;
    }
    else {
      resolved.lat_dev = 0.0
    }

    if (msg.lon_dev !== undefined) {
      resolved.lon_dev = msg.lon_dev;
    }
    else {
      resolved.lon_dev = 0.0
    }

    if (msg.alt_dev !== undefined) {
      resolved.alt_dev = msg.alt_dev;
    }
    else {
      resolved.alt_dev = 0.0
    }

    return resolved;
    }
};

module.exports = Gpgst;
