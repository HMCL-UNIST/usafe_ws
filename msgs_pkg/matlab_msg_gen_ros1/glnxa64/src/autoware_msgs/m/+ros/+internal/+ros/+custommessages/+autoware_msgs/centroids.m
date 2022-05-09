function [data, info] = centroids
%Centroids gives an empty data for autoware_msgs/Centroids
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.points, info.points] = ros.internal.ros.messages.geometry_msgs.point;
info.points.MLdataType = 'struct';
info.points.MaxLen = NaN;
info.points.MinLen = 0;
data.points = data.points([],1);
info.MessageType = 'autoware_msgs/Centroids';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,10);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'points';
info.MatPath{8} = 'points.x';
info.MatPath{9} = 'points.y';
info.MatPath{10} = 'points.z';
