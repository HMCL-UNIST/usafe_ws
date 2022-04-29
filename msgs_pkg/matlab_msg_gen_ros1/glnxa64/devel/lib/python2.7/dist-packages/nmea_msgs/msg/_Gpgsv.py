# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from nmea_msgs/Gpgsv.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import nmea_msgs.msg
import std_msgs.msg

class Gpgsv(genpy.Message):
  _md5sum = "6f34bebc32fe085313c942a96fd39c77"
  _type = "nmea_msgs/Gpgsv"
  _has_header = True #flag to mark the presence of a Header object
  _full_text = """# Total number of satellites in view and data about satellites
# Because the NMEA sentence is limited to 4 satellites per message, several
# of these messages may need to be synthesized to get data about all visible
# satellites.

Header header

string message_id

# Number of messages in this sequence
uint8 n_msgs
# This messages number in its sequence. The first message is number 1.
uint8 msg_number

# Number of satellites currently visible
uint8 n_satellites

# Up to 4 satellites are described in each message
GpgsvSatellite[] satellites

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
MSG: nmea_msgs/GpgsvSatellite
# Satellite data structure used in GPGSV messages

# PRN number of the satellite
# GPS = 1..32
# SBAS = 33..64
# GLO = 65..96
uint8 prn

# Elevation, degrees. Maximum 90
uint8 elevation

# Azimuth, True North degrees. [0, 359]
uint16 azimuth

# Signal to noise ratio, 0-99 dB. -1 when null in NMEA sentence (not tracking)
int8 snr
"""
  __slots__ = ['header','message_id','n_msgs','msg_number','n_satellites','satellites']
  _slot_types = ['std_msgs/Header','string','uint8','uint8','uint8','nmea_msgs/GpgsvSatellite[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,message_id,n_msgs,msg_number,n_satellites,satellites

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Gpgsv, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.message_id is None:
        self.message_id = ''
      if self.n_msgs is None:
        self.n_msgs = 0
      if self.msg_number is None:
        self.msg_number = 0
      if self.n_satellites is None:
        self.n_satellites = 0
      if self.satellites is None:
        self.satellites = []
    else:
      self.header = std_msgs.msg.Header()
      self.message_id = ''
      self.n_msgs = 0
      self.msg_number = 0
      self.n_satellites = 0
      self.satellites = []

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
      _x = self.message_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_3B().pack(_x.n_msgs, _x.msg_number, _x.n_satellites))
      length = len(self.satellites)
      buff.write(_struct_I.pack(length))
      for val1 in self.satellites:
        _x = val1
        buff.write(_get_struct_2BHb().pack(_x.prn, _x.elevation, _x.azimuth, _x.snr))
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
      if self.satellites is None:
        self.satellites = None
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
        self.message_id = str[start:end].decode('utf-8')
      else:
        self.message_id = str[start:end]
      _x = self
      start = end
      end += 3
      (_x.n_msgs, _x.msg_number, _x.n_satellites,) = _get_struct_3B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.satellites = []
      for i in range(0, length):
        val1 = nmea_msgs.msg.GpgsvSatellite()
        _x = val1
        start = end
        end += 5
        (_x.prn, _x.elevation, _x.azimuth, _x.snr,) = _get_struct_2BHb().unpack(str[start:end])
        self.satellites.append(val1)
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
      _x = self.message_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_3B().pack(_x.n_msgs, _x.msg_number, _x.n_satellites))
      length = len(self.satellites)
      buff.write(_struct_I.pack(length))
      for val1 in self.satellites:
        _x = val1
        buff.write(_get_struct_2BHb().pack(_x.prn, _x.elevation, _x.azimuth, _x.snr))
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
      if self.satellites is None:
        self.satellites = None
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
        self.message_id = str[start:end].decode('utf-8')
      else:
        self.message_id = str[start:end]
      _x = self
      start = end
      end += 3
      (_x.n_msgs, _x.msg_number, _x.n_satellites,) = _get_struct_3B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.satellites = []
      for i in range(0, length):
        val1 = nmea_msgs.msg.GpgsvSatellite()
        _x = val1
        start = end
        end += 5
        (_x.prn, _x.elevation, _x.azimuth, _x.snr,) = _get_struct_2BHb().unpack(str[start:end])
        self.satellites.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_3B = None
def _get_struct_3B():
    global _struct_3B
    if _struct_3B is None:
        _struct_3B = struct.Struct("<3B")
    return _struct_3B
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
_struct_2BHb = None
def _get_struct_2BHb():
    global _struct_2BHb
    if _struct_2BHb is None:
        _struct_2BHb = struct.Struct("<2BHb")
    return _struct_2BHb
