function [data, info] = recognizeLightStateResponse
%RecognizeLightState gives an empty data for hmcl_msgs/RecognizeLightStateResponse
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.class_id, info.class_id] = ros.internal.ros.messages.ros.default_type('uint8',1);
[data.confidence, info.confidence] = ros.internal.ros.messages.ros.default_type('single',1);
info.MessageType = 'hmcl_msgs/RecognizeLightStateResponse';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,2);
info.MatPath{1} = 'class_id';
info.MatPath{2} = 'confidence';
