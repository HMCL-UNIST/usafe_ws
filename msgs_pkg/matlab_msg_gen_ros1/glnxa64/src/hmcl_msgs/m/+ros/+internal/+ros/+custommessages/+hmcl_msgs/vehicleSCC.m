function [data, info] = vehicleSCC
%VehicleSCC gives an empty data for hmcl_msgs/VehicleSCC
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.scc_mode, info.scc_mode] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.scc_takeover, info.scc_takeover] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.acceleration, info.acceleration] = ros.internal.ros.messages.ros.default_type('double',1);
info.MessageType = 'hmcl_msgs/VehicleSCC';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,9);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'scc_mode';
info.MatPath{8} = 'scc_takeover';
info.MatPath{9} = 'acceleration';
