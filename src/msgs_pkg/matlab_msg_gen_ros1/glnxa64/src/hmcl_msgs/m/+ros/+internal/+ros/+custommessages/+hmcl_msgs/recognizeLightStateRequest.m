function [data, info] = recognizeLightStateRequest
%RecognizeLightState gives an empty data for hmcl_msgs/RecognizeLightStateRequest
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.roi_image, info.roi_image] = ros.internal.ros.messages.sensor_msgs.image;
info.roi_image.MLdataType = 'struct';
info.MessageType = 'hmcl_msgs/RecognizeLightStateRequest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,13);
info.MatPath{1} = 'roi_image';
info.MatPath{2} = 'roi_image.header';
info.MatPath{3} = 'roi_image.header.seq';
info.MatPath{4} = 'roi_image.header.stamp';
info.MatPath{5} = 'roi_image.header.stamp.sec';
info.MatPath{6} = 'roi_image.header.stamp.nsec';
info.MatPath{7} = 'roi_image.header.frame_id';
info.MatPath{8} = 'roi_image.height';
info.MatPath{9} = 'roi_image.width';
info.MatPath{10} = 'roi_image.encoding';
info.MatPath{11} = 'roi_image.is_bigendian';
info.MatPath{12} = 'roi_image.step';
info.MatPath{13} = 'roi_image.data';
