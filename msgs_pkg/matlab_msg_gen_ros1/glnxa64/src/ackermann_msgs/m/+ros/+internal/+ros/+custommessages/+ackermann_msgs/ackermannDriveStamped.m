function [data, info] = ackermannDriveStamped
%AckermannDriveStamped gives an empty data for ackermann_msgs/AckermannDriveStamped
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.drive, info.drive] = ros.internal.ros.messages.ackermann_msgs.ackermannDrive;
info.drive.MLdataType = 'struct';
info.MessageType = 'ackermann_msgs/AckermannDriveStamped';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,12);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'drive';
info.MatPath{8} = 'drive.steering_angle';
info.MatPath{9} = 'drive.steering_angle_velocity';
info.MatPath{10} = 'drive.speed';
info.MatPath{11} = 'drive.acceleration';
info.MatPath{12} = 'drive.jerk';
