function [data, info] = lapStats
%lapStats gives an empty data for autorally_msgs/lapStats
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.lap_number, info.lap_number] = ros.internal.ros.messages.ros.default_type('int64',1);
[data.lap_time, info.lap_time] = ros.internal.ros.messages.ros.default_type('double',1);
[data.max_speed, info.max_speed] = ros.internal.ros.messages.ros.default_type('double',1);
[data.max_slip, info.max_slip] = ros.internal.ros.messages.ros.default_type('double',1);
info.MessageType = 'autorally_msgs/lapStats';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,4);
info.MatPath{1} = 'lap_number';
info.MatPath{2} = 'lap_time';
info.MatPath{3} = 'max_speed';
info.MatPath{4} = 'max_slip';
