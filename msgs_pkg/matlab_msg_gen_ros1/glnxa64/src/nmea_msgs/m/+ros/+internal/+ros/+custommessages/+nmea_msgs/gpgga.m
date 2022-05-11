function [data, info] = gpgga
%Gpgga gives an empty data for nmea_msgs/Gpgga
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.message_id, info.message_id] = ros.internal.ros.messages.ros.char('string',0);
[data.utc_seconds, info.utc_seconds] = ros.internal.ros.messages.ros.default_type('double',1);
[data.lat, info.lat] = ros.internal.ros.messages.ros.default_type('double',1);
[data.lon, info.lon] = ros.internal.ros.messages.ros.default_type('double',1);
[data.lat_dir, info.lat_dir] = ros.internal.ros.messages.ros.char('string',0);
[data.lon_dir, info.lon_dir] = ros.internal.ros.messages.ros.char('string',0);
[data.gps_qual, info.gps_qual] = ros.internal.ros.messages.ros.default_type('uint32',1);
[data.num_sats, info.num_sats] = ros.internal.ros.messages.ros.default_type('uint32',1);
[data.hdop, info.hdop] = ros.internal.ros.messages.ros.default_type('single',1);
[data.alt, info.alt] = ros.internal.ros.messages.ros.default_type('single',1);
[data.altitude_units, info.altitude_units] = ros.internal.ros.messages.ros.char('string',0);
[data.undulation, info.undulation] = ros.internal.ros.messages.ros.default_type('single',1);
[data.undulation_units, info.undulation_units] = ros.internal.ros.messages.ros.char('string',0);
[data.diff_age, info.diff_age] = ros.internal.ros.messages.ros.default_type('uint32',1);
[data.station_id, info.station_id] = ros.internal.ros.messages.ros.char('string',0);
info.MessageType = 'nmea_msgs/Gpgga';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,21);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'message_id';
info.MatPath{8} = 'utc_seconds';
info.MatPath{9} = 'lat';
info.MatPath{10} = 'lon';
info.MatPath{11} = 'lat_dir';
info.MatPath{12} = 'lon_dir';
info.MatPath{13} = 'gps_qual';
info.MatPath{14} = 'num_sats';
info.MatPath{15} = 'hdop';
info.MatPath{16} = 'alt';
info.MatPath{17} = 'altitude_units';
info.MatPath{18} = 'undulation';
info.MatPath{19} = 'undulation_units';
info.MatPath{20} = 'diff_age';
info.MatPath{21} = 'station_id';