function [data, info] = stateEstimatorStatus
%stateEstimatorStatus gives an empty data for autorally_msgs/stateEstimatorStatus
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.OK, info.OK] = ros.internal.ros.messages.ros.default_type('int8',1, 0);
[data.WARN, info.WARN] = ros.internal.ros.messages.ros.default_type('int8',1, 1);
[data.ERROR, info.ERROR] = ros.internal.ros.messages.ros.default_type('int8',1, 2);
[data.status, info.status] = ros.internal.ros.messages.ros.default_type('int8',1);
info.MessageType = 'autorally_msgs/stateEstimatorStatus';
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
info.MatPath{7} = 'OK';
info.MatPath{8} = 'WARN';
info.MatPath{9} = 'ERROR';
info.MatPath{10} = 'status';
