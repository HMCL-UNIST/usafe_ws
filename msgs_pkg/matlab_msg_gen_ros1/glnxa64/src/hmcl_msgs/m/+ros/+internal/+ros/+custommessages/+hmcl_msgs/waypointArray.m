function [data, info] = waypointArray
%WaypointArray gives an empty data for hmcl_msgs/WaypointArray
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.x, info.x] = ros.internal.ros.messages.ros.default_type('double',NaN);
[data.y, info.y] = ros.internal.ros.messages.ros.default_type('double',NaN);
info.MessageType = 'hmcl_msgs/WaypointArray';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,2);
info.MatPath{1} = 'x';
info.MatPath{2} = 'y';
