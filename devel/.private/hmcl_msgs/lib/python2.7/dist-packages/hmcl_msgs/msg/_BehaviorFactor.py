# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from hmcl_msgs/BehaviorFactor.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import hmcl_msgs.msg
import std_msgs.msg

class BehaviorFactor(genpy.Message):
  _md5sum = "007955b848a31590079e09deb110b6e6"
  _type = "hmcl_msgs/BehaviorFactor"
  _has_header = True  # flag to mark the presence of a Header object
  _full_text = """Header header
hmcl_msgs/TransitionCondition transition_condition
int16 front_id
bool stop_line_stop
float32 front_dist

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
MSG: hmcl_msgs/TransitionCondition
bool missionStart
bool approachToStartPos
bool startArrivalCheck
bool startArrivalSuccess
bool frontCar
bool stationaryFrontCar
bool approachToCrosswalk
bool crosswalkPass
bool pedestrianOnCrosswalk
bool leftTurn
bool rightTurn
bool turn
bool trafficLightStop
bool stopCheck
bool luggageDrop
bool brokenFrontCar
bool laneChangeDone
bool essentialLaneChange
bool speedBumpSign
bool speedBumpPass
bool approachToGoalPos
bool goalArrivalCheck"""
  __slots__ = ['header','transition_condition','front_id','stop_line_stop','front_dist']
  _slot_types = ['std_msgs/Header','hmcl_msgs/TransitionCondition','int16','bool','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,transition_condition,front_id,stop_line_stop,front_dist

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(BehaviorFactor, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.transition_condition is None:
        self.transition_condition = hmcl_msgs.msg.TransitionCondition()
      if self.front_id is None:
        self.front_id = 0
      if self.stop_line_stop is None:
        self.stop_line_stop = False
      if self.front_dist is None:
        self.front_dist = 0.
    else:
      self.header = std_msgs.msg.Header()
      self.transition_condition = hmcl_msgs.msg.TransitionCondition()
      self.front_id = 0
      self.stop_line_stop = False
      self.front_dist = 0.

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
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_22BhBf().pack(_x.transition_condition.missionStart, _x.transition_condition.approachToStartPos, _x.transition_condition.startArrivalCheck, _x.transition_condition.startArrivalSuccess, _x.transition_condition.frontCar, _x.transition_condition.stationaryFrontCar, _x.transition_condition.approachToCrosswalk, _x.transition_condition.crosswalkPass, _x.transition_condition.pedestrianOnCrosswalk, _x.transition_condition.leftTurn, _x.transition_condition.rightTurn, _x.transition_condition.turn, _x.transition_condition.trafficLightStop, _x.transition_condition.stopCheck, _x.transition_condition.luggageDrop, _x.transition_condition.brokenFrontCar, _x.transition_condition.laneChangeDone, _x.transition_condition.essentialLaneChange, _x.transition_condition.speedBumpSign, _x.transition_condition.speedBumpPass, _x.transition_condition.approachToGoalPos, _x.transition_condition.goalArrivalCheck, _x.front_id, _x.stop_line_stop, _x.front_dist))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.transition_condition is None:
        self.transition_condition = hmcl_msgs.msg.TransitionCondition()
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
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 29
      (_x.transition_condition.missionStart, _x.transition_condition.approachToStartPos, _x.transition_condition.startArrivalCheck, _x.transition_condition.startArrivalSuccess, _x.transition_condition.frontCar, _x.transition_condition.stationaryFrontCar, _x.transition_condition.approachToCrosswalk, _x.transition_condition.crosswalkPass, _x.transition_condition.pedestrianOnCrosswalk, _x.transition_condition.leftTurn, _x.transition_condition.rightTurn, _x.transition_condition.turn, _x.transition_condition.trafficLightStop, _x.transition_condition.stopCheck, _x.transition_condition.luggageDrop, _x.transition_condition.brokenFrontCar, _x.transition_condition.laneChangeDone, _x.transition_condition.essentialLaneChange, _x.transition_condition.speedBumpSign, _x.transition_condition.speedBumpPass, _x.transition_condition.approachToGoalPos, _x.transition_condition.goalArrivalCheck, _x.front_id, _x.stop_line_stop, _x.front_dist,) = _get_struct_22BhBf().unpack(str[start:end])
      self.transition_condition.missionStart = bool(self.transition_condition.missionStart)
      self.transition_condition.approachToStartPos = bool(self.transition_condition.approachToStartPos)
      self.transition_condition.startArrivalCheck = bool(self.transition_condition.startArrivalCheck)
      self.transition_condition.startArrivalSuccess = bool(self.transition_condition.startArrivalSuccess)
      self.transition_condition.frontCar = bool(self.transition_condition.frontCar)
      self.transition_condition.stationaryFrontCar = bool(self.transition_condition.stationaryFrontCar)
      self.transition_condition.approachToCrosswalk = bool(self.transition_condition.approachToCrosswalk)
      self.transition_condition.crosswalkPass = bool(self.transition_condition.crosswalkPass)
      self.transition_condition.pedestrianOnCrosswalk = bool(self.transition_condition.pedestrianOnCrosswalk)
      self.transition_condition.leftTurn = bool(self.transition_condition.leftTurn)
      self.transition_condition.rightTurn = bool(self.transition_condition.rightTurn)
      self.transition_condition.turn = bool(self.transition_condition.turn)
      self.transition_condition.trafficLightStop = bool(self.transition_condition.trafficLightStop)
      self.transition_condition.stopCheck = bool(self.transition_condition.stopCheck)
      self.transition_condition.luggageDrop = bool(self.transition_condition.luggageDrop)
      self.transition_condition.brokenFrontCar = bool(self.transition_condition.brokenFrontCar)
      self.transition_condition.laneChangeDone = bool(self.transition_condition.laneChangeDone)
      self.transition_condition.essentialLaneChange = bool(self.transition_condition.essentialLaneChange)
      self.transition_condition.speedBumpSign = bool(self.transition_condition.speedBumpSign)
      self.transition_condition.speedBumpPass = bool(self.transition_condition.speedBumpPass)
      self.transition_condition.approachToGoalPos = bool(self.transition_condition.approachToGoalPos)
      self.transition_condition.goalArrivalCheck = bool(self.transition_condition.goalArrivalCheck)
      self.stop_line_stop = bool(self.stop_line_stop)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


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
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_22BhBf().pack(_x.transition_condition.missionStart, _x.transition_condition.approachToStartPos, _x.transition_condition.startArrivalCheck, _x.transition_condition.startArrivalSuccess, _x.transition_condition.frontCar, _x.transition_condition.stationaryFrontCar, _x.transition_condition.approachToCrosswalk, _x.transition_condition.crosswalkPass, _x.transition_condition.pedestrianOnCrosswalk, _x.transition_condition.leftTurn, _x.transition_condition.rightTurn, _x.transition_condition.turn, _x.transition_condition.trafficLightStop, _x.transition_condition.stopCheck, _x.transition_condition.luggageDrop, _x.transition_condition.brokenFrontCar, _x.transition_condition.laneChangeDone, _x.transition_condition.essentialLaneChange, _x.transition_condition.speedBumpSign, _x.transition_condition.speedBumpPass, _x.transition_condition.approachToGoalPos, _x.transition_condition.goalArrivalCheck, _x.front_id, _x.stop_line_stop, _x.front_dist))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.transition_condition is None:
        self.transition_condition = hmcl_msgs.msg.TransitionCondition()
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
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 29
      (_x.transition_condition.missionStart, _x.transition_condition.approachToStartPos, _x.transition_condition.startArrivalCheck, _x.transition_condition.startArrivalSuccess, _x.transition_condition.frontCar, _x.transition_condition.stationaryFrontCar, _x.transition_condition.approachToCrosswalk, _x.transition_condition.crosswalkPass, _x.transition_condition.pedestrianOnCrosswalk, _x.transition_condition.leftTurn, _x.transition_condition.rightTurn, _x.transition_condition.turn, _x.transition_condition.trafficLightStop, _x.transition_condition.stopCheck, _x.transition_condition.luggageDrop, _x.transition_condition.brokenFrontCar, _x.transition_condition.laneChangeDone, _x.transition_condition.essentialLaneChange, _x.transition_condition.speedBumpSign, _x.transition_condition.speedBumpPass, _x.transition_condition.approachToGoalPos, _x.transition_condition.goalArrivalCheck, _x.front_id, _x.stop_line_stop, _x.front_dist,) = _get_struct_22BhBf().unpack(str[start:end])
      self.transition_condition.missionStart = bool(self.transition_condition.missionStart)
      self.transition_condition.approachToStartPos = bool(self.transition_condition.approachToStartPos)
      self.transition_condition.startArrivalCheck = bool(self.transition_condition.startArrivalCheck)
      self.transition_condition.startArrivalSuccess = bool(self.transition_condition.startArrivalSuccess)
      self.transition_condition.frontCar = bool(self.transition_condition.frontCar)
      self.transition_condition.stationaryFrontCar = bool(self.transition_condition.stationaryFrontCar)
      self.transition_condition.approachToCrosswalk = bool(self.transition_condition.approachToCrosswalk)
      self.transition_condition.crosswalkPass = bool(self.transition_condition.crosswalkPass)
      self.transition_condition.pedestrianOnCrosswalk = bool(self.transition_condition.pedestrianOnCrosswalk)
      self.transition_condition.leftTurn = bool(self.transition_condition.leftTurn)
      self.transition_condition.rightTurn = bool(self.transition_condition.rightTurn)
      self.transition_condition.turn = bool(self.transition_condition.turn)
      self.transition_condition.trafficLightStop = bool(self.transition_condition.trafficLightStop)
      self.transition_condition.stopCheck = bool(self.transition_condition.stopCheck)
      self.transition_condition.luggageDrop = bool(self.transition_condition.luggageDrop)
      self.transition_condition.brokenFrontCar = bool(self.transition_condition.brokenFrontCar)
      self.transition_condition.laneChangeDone = bool(self.transition_condition.laneChangeDone)
      self.transition_condition.essentialLaneChange = bool(self.transition_condition.essentialLaneChange)
      self.transition_condition.speedBumpSign = bool(self.transition_condition.speedBumpSign)
      self.transition_condition.speedBumpPass = bool(self.transition_condition.speedBumpPass)
      self.transition_condition.approachToGoalPos = bool(self.transition_condition.approachToGoalPos)
      self.transition_condition.goalArrivalCheck = bool(self.transition_condition.goalArrivalCheck)
      self.stop_line_stop = bool(self.stop_line_stop)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_22BhBf = None
def _get_struct_22BhBf():
    global _struct_22BhBf
    if _struct_22BhBf is None:
        _struct_22BhBf = struct.Struct("<22BhBf")
    return _struct_22BhBf
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
