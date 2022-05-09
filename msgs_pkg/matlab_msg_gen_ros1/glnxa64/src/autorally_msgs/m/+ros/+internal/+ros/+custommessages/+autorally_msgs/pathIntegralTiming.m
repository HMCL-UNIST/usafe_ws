function [data, info] = pathIntegralTiming
%pathIntegralTiming gives an empty data for autorally_msgs/pathIntegralTiming
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.averageTimeBetweenPoses, info.averageTimeBetweenPoses] = ros.internal.ros.messages.ros.default_type('double',1);
[data.averageOptimizationCycleTime, info.averageOptimizationCycleTime] = ros.internal.ros.messages.ros.default_type('double',1);
[data.averageSleepTime, info.averageSleepTime] = ros.internal.ros.messages.ros.default_type('double',1);
info.MessageType = 'autorally_msgs/pathIntegralTiming';
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
info.MatPath{7} = 'averageTimeBetweenPoses';
info.MatPath{8} = 'averageOptimizationCycleTime';
info.MatPath{9} = 'averageSleepTime';
