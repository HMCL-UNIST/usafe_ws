function [data, info] = remoteButton
%RemoteButton gives an empty data for hmcl_msgs/RemoteButton
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.button1, info.button1] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.button2, info.button2] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.button3, info.button3] = ros.internal.ros.messages.ros.default_type('uint8',1);
info.MessageType = 'hmcl_msgs/RemoteButton';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'button1';
info.MatPath{2} = 'button2';
info.MatPath{3} = 'button3';
