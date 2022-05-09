function [data, info] = neuralNetLayer
%neuralNetLayer gives an empty data for autorally_msgs/neuralNetLayer
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.name, info.name] = ros.internal.ros.messages.ros.char('string',0);
[data.weight, info.weight] = ros.internal.ros.messages.ros.default_type('single',NaN);
[data.bias, info.bias] = ros.internal.ros.messages.ros.default_type('single',NaN);
info.MessageType = 'autorally_msgs/neuralNetLayer';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'name';
info.MatPath{2} = 'weight';
info.MatPath{3} = 'bias';
