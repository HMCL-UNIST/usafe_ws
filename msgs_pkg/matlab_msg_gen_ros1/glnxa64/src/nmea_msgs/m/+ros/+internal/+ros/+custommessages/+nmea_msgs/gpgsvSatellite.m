function [data, info] = gpgsvSatellite
%GpgsvSatellite gives an empty data for nmea_msgs/GpgsvSatellite
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.prn, info.prn] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.elevation, info.elevation] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.azimuth, info.azimuth] = ros.internal.ros.messages.ros.default_type('uint16',1);
[data.snr, info.snr] = ros.internal.ros.messages.ros.default_type('int8',1);
info.MessageType = 'nmea_msgs/GpgsvSatellite';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,4);
info.MatPath{1} = 'prn';
info.MatPath{2} = 'elevation';
info.MatPath{3} = 'azimuth';
info.MatPath{4} = 'snr';
