// Auto-generated. Do not edit!

// (in-package hmcl_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Trafficlight {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.id = null;
      this.pose = null;
      this.valid_stop_line = null;
      this.stop_line = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('pose')) {
        this.pose = initObj.pose
      }
      else {
        this.pose = new geometry_msgs.msg.Point32();
      }
      if (initObj.hasOwnProperty('valid_stop_line')) {
        this.valid_stop_line = initObj.valid_stop_line
      }
      else {
        this.valid_stop_line = false;
      }
      if (initObj.hasOwnProperty('stop_line')) {
        this.stop_line = initObj.stop_line
      }
      else {
        this.stop_line = new geometry_msgs.msg.Point32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Trafficlight
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [id]
    bufferOffset = _serializer.int32(obj.id, buffer, bufferOffset);
    // Serialize message field [pose]
    bufferOffset = geometry_msgs.msg.Point32.serialize(obj.pose, buffer, bufferOffset);
    // Serialize message field [valid_stop_line]
    bufferOffset = _serializer.bool(obj.valid_stop_line, buffer, bufferOffset);
    // Serialize message field [stop_line]
    bufferOffset = geometry_msgs.msg.Point32.serialize(obj.stop_line, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Trafficlight
    let len;
    let data = new Trafficlight(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [id]
    data.id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [pose]
    data.pose = geometry_msgs.msg.Point32.deserialize(buffer, bufferOffset);
    // Deserialize message field [valid_stop_line]
    data.valid_stop_line = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [stop_line]
    data.stop_line = geometry_msgs.msg.Point32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 29;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hmcl_msgs/Trafficlight';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fcbbb59b45f60bd6eaff4eb294691b13';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    int32 id
    geometry_msgs/Point32 pose
    bool valid_stop_line
    geometry_msgs/Point32 stop_line
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
    MSG: geometry_msgs/Point32
    # This contains the position of a point in free space(with 32 bits of precision).
    # It is recommeded to use Point wherever possible instead of Point32.  
    # 
    # This recommendation is to promote interoperability.  
    #
    # This message is designed to take up less space when sending
    # lots of points at once, as in the case of a PointCloud.  
    
    float32 x
    float32 y
    float32 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Trafficlight(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.pose !== undefined) {
      resolved.pose = geometry_msgs.msg.Point32.Resolve(msg.pose)
    }
    else {
      resolved.pose = new geometry_msgs.msg.Point32()
    }

    if (msg.valid_stop_line !== undefined) {
      resolved.valid_stop_line = msg.valid_stop_line;
    }
    else {
      resolved.valid_stop_line = false
    }

    if (msg.stop_line !== undefined) {
      resolved.stop_line = geometry_msgs.msg.Point32.Resolve(msg.stop_line)
    }
    else {
      resolved.stop_line = new geometry_msgs.msg.Point32()
    }

    return resolved;
    }
};

module.exports = Trafficlight;
