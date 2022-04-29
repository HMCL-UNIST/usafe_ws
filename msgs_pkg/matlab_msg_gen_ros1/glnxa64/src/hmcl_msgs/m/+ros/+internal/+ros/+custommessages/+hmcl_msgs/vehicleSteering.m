function [data, info] = vehicleSteering
%VehicleSteering gives an empty data for hmcl_msgs/VehicleSteering
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.takeover, info.takeover] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.mode, info.mode] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.steering_angle, info.steering_angle] = ros.internal.ros.messages.ros.default_type('single',1);
info.MessageType = 'hmcl_msgs/VehicleSteering';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'takeover';
info.MatPath{2} = 'mode';
info.MatPath{3} = 'steering_angle';
