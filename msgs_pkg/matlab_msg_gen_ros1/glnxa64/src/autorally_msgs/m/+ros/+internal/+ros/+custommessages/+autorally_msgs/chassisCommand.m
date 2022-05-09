function [data, info] = chassisCommand
%chassisCommand gives an empty data for autorally_msgs/chassisCommand
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.sender, info.sender] = ros.internal.ros.messages.ros.char('string',0);
[data.throttle, info.throttle] = ros.internal.ros.messages.ros.default_type('double',1);
[data.steering, info.steering] = ros.internal.ros.messages.ros.default_type('double',1);
[data.frontBrake, info.frontBrake] = ros.internal.ros.messages.ros.default_type('double',1);
info.MessageType = 'autorally_msgs/chassisCommand';
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
info.MatPath{7} = 'sender';
info.MatPath{8} = 'throttle';
info.MatPath{9} = 'steering';
info.MatPath{10} = 'frontBrake';
