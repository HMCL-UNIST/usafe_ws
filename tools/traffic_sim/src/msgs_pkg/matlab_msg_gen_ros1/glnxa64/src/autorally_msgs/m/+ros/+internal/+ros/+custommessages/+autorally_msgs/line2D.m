function [data, info] = line2D
%line2D gives an empty data for autorally_msgs/line2D
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.start, info.start] = ros.internal.ros.custommessages.autorally_msgs.point2D;
info.start.MLdataType = 'struct';
[data.end, info.end] = ros.internal.ros.custommessages.autorally_msgs.point2D;
info.end.MLdataType = 'struct';
info.MessageType = 'autorally_msgs/line2D';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,6);
info.MatPath{1} = 'start';
info.MatPath{2} = 'start.x';
info.MatPath{3} = 'start.y';
info.MatPath{4} = 'end';
info.MatPath{5} = 'end.x';
info.MatPath{6} = 'end.y';
