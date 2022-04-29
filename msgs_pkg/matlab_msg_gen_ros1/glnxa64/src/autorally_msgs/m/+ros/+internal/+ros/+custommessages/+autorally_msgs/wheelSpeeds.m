function [data, info] = wheelSpeeds
%wheelSpeeds gives an empty data for autorally_msgs/wheelSpeeds
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.lfSpeed, info.lfSpeed] = ros.internal.ros.messages.ros.default_type('double',1);
[data.rfSpeed, info.rfSpeed] = ros.internal.ros.messages.ros.default_type('double',1);
[data.lbSpeed, info.lbSpeed] = ros.internal.ros.messages.ros.default_type('double',1);
[data.rbSpeed, info.rbSpeed] = ros.internal.ros.messages.ros.default_type('double',1);
info.MessageType = 'autorally_msgs/wheelSpeeds';
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
info.MatPath{7} = 'lfSpeed';
info.MatPath{8} = 'rfSpeed';
info.MatPath{9} = 'lbSpeed';
info.MatPath{10} = 'rbSpeed';
