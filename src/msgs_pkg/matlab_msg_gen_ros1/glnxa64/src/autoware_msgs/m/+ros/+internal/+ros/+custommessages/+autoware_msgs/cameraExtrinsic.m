function [data, info] = cameraExtrinsic
%CameraExtrinsic gives an empty data for autoware_msgs/CameraExtrinsic
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.xsize, info.xsize] = ros.internal.ros.messages.ros.default_type('uint32',1, 4);
[data.ysize, info.ysize] = ros.internal.ros.messages.ros.default_type('uint32',1, 4);
[data.calibration, info.calibration] = ros.internal.ros.messages.ros.default_type('double',NaN);
info.MessageType = 'autoware_msgs/CameraExtrinsic';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,9);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'xsize';
info.MatPath{8} = 'ysize';
info.MatPath{9} = 'calibration';
