function [data, info] = vehicleSteering
%VehicleSteering gives an empty data for hmcl_msgs/VehicleSteering
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.takeover, info.takeover] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.mode, info.mode] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.steering_angle, info.steering_angle] = ros.internal.ros.messages.ros.default_type('single',1);
info.MessageType = 'hmcl_msgs/VehicleSteering';
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
info.MatPath{7} = 'takeover';
info.MatPath{8} = 'mode';
info.MatPath{9} = 'steering_angle';
