function [data, info] = trafficlight
%Trafficlight gives an empty data for hmcl_msgs/Trafficlight
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.id, info.id] = ros.internal.ros.messages.ros.default_type('int32',1);
[data.pose, info.pose] = ros.internal.ros.messages.geometry_msgs.point32;
info.pose.MLdataType = 'struct';
[data.valid_stop_line, info.valid_stop_line] = ros.internal.ros.messages.ros.default_type('logical',1);
[data.stop_line, info.stop_line] = ros.internal.ros.messages.geometry_msgs.point32;
info.stop_line.MLdataType = 'struct';
info.MessageType = 'hmcl_msgs/Trafficlight';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,16);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'id';
info.MatPath{8} = 'pose';
info.MatPath{9} = 'pose.x';
info.MatPath{10} = 'pose.y';
info.MatPath{11} = 'pose.z';
info.MatPath{12} = 'valid_stop_line';
info.MatPath{13} = 'stop_line';
info.MatPath{14} = 'stop_line.x';
info.MatPath{15} = 'stop_line.y';
info.MatPath{16} = 'stop_line.z';
