function [data, info] = pathIntegralStats
%pathIntegralStats gives an empty data for autorally_msgs/pathIntegralStats
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.tag, info.tag] = ros.internal.ros.messages.ros.char('string',0);
[data.params, info.params] = ros.internal.ros.custommessages.autorally_msgs.pathIntegralParams;
info.params.MLdataType = 'struct';
[data.stats, info.stats] = ros.internal.ros.custommessages.autorally_msgs.lapStats;
info.stats.MLdataType = 'struct';
info.MessageType = 'autorally_msgs/pathIntegralStats';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,29);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'tag';
info.MatPath{8} = 'params';
info.MatPath{9} = 'params.hz';
info.MatPath{10} = 'params.num_timesteps';
info.MatPath{11} = 'params.num_iters';
info.MatPath{12} = 'params.gamma';
info.MatPath{13} = 'params.init_steering';
info.MatPath{14} = 'params.init_throttle';
info.MatPath{15} = 'params.steering_var';
info.MatPath{16} = 'params.throttle_var';
info.MatPath{17} = 'params.max_throttle';
info.MatPath{18} = 'params.speed_coefficient';
info.MatPath{19} = 'params.track_coefficient';
info.MatPath{20} = 'params.max_slip_angle';
info.MatPath{21} = 'params.track_slop';
info.MatPath{22} = 'params.crash_coeff';
info.MatPath{23} = 'params.map_path';
info.MatPath{24} = 'params.desired_speed';
info.MatPath{25} = 'stats';
info.MatPath{26} = 'stats.lap_number';
info.MatPath{27} = 'stats.lap_time';
info.MatPath{28} = 'stats.max_speed';
info.MatPath{29} = 'stats.max_slip';
