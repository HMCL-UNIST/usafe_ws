function [data, info] = point2D
%point2D gives an empty data for autorally_msgs/point2D
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.x, info.x] = ros.internal.ros.messages.ros.default_type('uint16',1);
[data.y, info.y] = ros.internal.ros.messages.ros.default_type('uint16',1);
info.MessageType = 'autorally_msgs/point2D';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,2);
info.MatPath{1} = 'x';
info.MatPath{2} = 'y';
