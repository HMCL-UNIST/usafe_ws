function [data, info] = ackermannDrive
%AckermannDrive gives an empty data for ackermann_msgs/AckermannDrive
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.steering_angle, info.steering_angle] = ros.internal.ros.messages.ros.default_type('single',1);
[data.steering_angle_velocity, info.steering_angle_velocity] = ros.internal.ros.messages.ros.default_type('single',1);
[data.speed, info.speed] = ros.internal.ros.messages.ros.default_type('single',1);
[data.acceleration, info.acceleration] = ros.internal.ros.messages.ros.default_type('single',1);
[data.jerk, info.jerk] = ros.internal.ros.messages.ros.default_type('single',1);
info.MessageType = 'ackermann_msgs/AckermannDrive';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,5);
info.MatPath{1} = 'steering_angle';
info.MatPath{2} = 'steering_angle_velocity';
info.MatPath{3} = 'speed';
info.MatPath{4} = 'acceleration';
info.MatPath{5} = 'jerk';
