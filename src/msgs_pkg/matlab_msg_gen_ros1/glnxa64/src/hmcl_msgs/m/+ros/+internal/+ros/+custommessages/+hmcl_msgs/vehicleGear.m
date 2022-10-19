function [data, info] = vehicleGear
%VehicleGear gives an empty data for hmcl_msgs/VehicleGear
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.gear, info.gear] = ros.internal.ros.messages.ros.default_type('uint8',1);
info.MessageType = 'hmcl_msgs/VehicleGear';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'gear';
