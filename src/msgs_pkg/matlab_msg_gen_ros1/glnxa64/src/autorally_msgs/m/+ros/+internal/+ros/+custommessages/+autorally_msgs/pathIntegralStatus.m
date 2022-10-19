function [data, info] = pathIntegralStatus
%pathIntegralStatus gives an empty data for autorally_msgs/pathIntegralStatus
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.info, info.info] = ros.internal.ros.messages.ros.char('string',0);
[data.status, info.status] = ros.internal.ros.messages.ros.default_type('int32',1);
info.MessageType = 'autorally_msgs/pathIntegralStatus';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,8);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'info';
info.MatPath{8} = 'status';
