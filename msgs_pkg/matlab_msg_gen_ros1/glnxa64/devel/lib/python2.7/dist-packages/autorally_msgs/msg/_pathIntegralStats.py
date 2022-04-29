# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from autorally_msgs/pathIntegralStats.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import autorally_msgs.msg
import std_msgs.msg

class pathIntegralStats(genpy.Message):
  _md5sum = "cfb6f9017ebb92f4695492c3201de3c3"
  _type = "autorally_msgs/pathIntegralStats"
  _has_header = True #flag to mark the presence of a Header object
  _full_text = """Header header
string tag

pathIntegralParams params
lapStats stats

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
MSG: autorally_msgs/pathIntegralParams
int64 hz
int64 num_timesteps
int64 num_iters
float64 gamma
float64 init_steering
float64 init_throttle
float64 steering_var
float64 throttle_var
float64 max_throttle
float64 speed_coefficient
float64 track_coefficient
float64 max_slip_angle
float64 track_slop
float64 crash_coeff
string map_path
float64 desired_speed
================================================================================
MSG: autorally_msgs/lapStats
int64 lap_number
float64 lap_time
float64 max_speed
float64 max_slip
"""
  __slots__ = ['header','tag','params','stats']
  _slot_types = ['std_msgs/Header','string','autorally_msgs/pathIntegralParams','autorally_msgs/lapStats']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,tag,params,stats

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(pathIntegralStats, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.tag is None:
        self.tag = ''
      if self.params is None:
        self.params = autorally_msgs.msg.pathIntegralParams()
      if self.stats is None:
        self.stats = autorally_msgs.msg.lapStats()
    else:
      self.header = std_msgs.msg.Header()
      self.tag = ''
      self.params = autorally_msgs.msg.pathIntegralParams()
      self.stats = autorally_msgs.msg.lapStats()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.tag
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_3q11d().pack(_x.params.hz, _x.params.num_timesteps, _x.params.num_iters, _x.params.gamma, _x.params.init_steering, _x.params.init_throttle, _x.params.steering_var, _x.params.throttle_var, _x.params.max_throttle, _x.params.speed_coefficient, _x.params.track_coefficient, _x.params.max_slip_angle, _x.params.track_slop, _x.params.crash_coeff))
      _x = self.params.map_path
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_dq3d().pack(_x.params.desired_speed, _x.stats.lap_number, _x.stats.lap_time, _x.stats.max_speed, _x.stats.max_slip))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.params is None:
        self.params = autorally_msgs.msg.pathIntegralParams()
      if self.stats is None:
        self.stats = autorally_msgs.msg.lapStats()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.tag = str[start:end].decode('utf-8')
      else:
        self.tag = str[start:end]
      _x = self
      start = end
      end += 112
      (_x.params.hz, _x.params.num_timesteps, _x.params.num_iters, _x.params.gamma, _x.params.init_steering, _x.params.init_throttle, _x.params.steering_var, _x.params.throttle_var, _x.params.max_throttle, _x.params.speed_coefficient, _x.params.track_coefficient, _x.params.max_slip_angle, _x.params.track_slop, _x.params.crash_coeff,) = _get_struct_3q11d().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.params.map_path = str[start:end].decode('utf-8')
      else:
        self.params.map_path = str[start:end]
      _x = self
      start = end
      end += 40
      (_x.params.desired_speed, _x.stats.lap_number, _x.stats.lap_time, _x.stats.max_speed, _x.stats.max_slip,) = _get_struct_dq3d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.tag
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_3q11d().pack(_x.params.hz, _x.params.num_timesteps, _x.params.num_iters, _x.params.gamma, _x.params.init_steering, _x.params.init_throttle, _x.params.steering_var, _x.params.throttle_var, _x.params.max_throttle, _x.params.speed_coefficient, _x.params.track_coefficient, _x.params.max_slip_angle, _x.params.track_slop, _x.params.crash_coeff))
      _x = self.params.map_path
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_dq3d().pack(_x.params.desired_speed, _x.stats.lap_number, _x.stats.lap_time, _x.stats.max_speed, _x.stats.max_slip))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.params is None:
        self.params = autorally_msgs.msg.pathIntegralParams()
      if self.stats is None:
        self.stats = autorally_msgs.msg.lapStats()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.tag = str[start:end].decode('utf-8')
      else:
        self.tag = str[start:end]
      _x = self
      start = end
      end += 112
      (_x.params.hz, _x.params.num_timesteps, _x.params.num_iters, _x.params.gamma, _x.params.init_steering, _x.params.init_throttle, _x.params.steering_var, _x.params.throttle_var, _x.params.max_throttle, _x.params.speed_coefficient, _x.params.track_coefficient, _x.params.max_slip_angle, _x.params.track_slop, _x.params.crash_coeff,) = _get_struct_3q11d().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.params.map_path = str[start:end].decode('utf-8')
      else:
        self.params.map_path = str[start:end]
      _x = self
      start = end
      end += 40
      (_x.params.desired_speed, _x.stats.lap_number, _x.stats.lap_time, _x.stats.max_speed, _x.stats.max_slip,) = _get_struct_dq3d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
_struct_dq3d = None
def _get_struct_dq3d():
    global _struct_dq3d
    if _struct_dq3d is None:
        _struct_dq3d = struct.Struct("<dq3d")
    return _struct_dq3d
_struct_3q11d = None
def _get_struct_3q11d():
    global _struct_3q11d
    if _struct_3q11d is None:
        _struct_3q11d = struct.Struct("<3q11d")
    return _struct_3q11d
