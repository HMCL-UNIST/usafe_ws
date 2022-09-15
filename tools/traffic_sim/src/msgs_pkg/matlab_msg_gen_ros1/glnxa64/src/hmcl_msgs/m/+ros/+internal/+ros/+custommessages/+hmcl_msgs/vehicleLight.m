function [data, info] = vehicleLight
%VehicleLight gives an empty data for hmcl_msgs/VehicleLight
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.left_light, info.left_light] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.right_light, info.right_light] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.hazard_light, info.hazard_light] = ros.internal.ros.messages.ros.default_type('uint8',1);
info.MessageType = 'hmcl_msgs/VehicleLight';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'left_light';
info.MatPath{2} = 'right_light';
info.MatPath{3} = 'hazard_light';
