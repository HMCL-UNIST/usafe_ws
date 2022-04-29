function [data, info] = lane
%Lane gives an empty data for hmcl_msgs/Lane
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.lane_id, info.lane_id] = ros.internal.ros.messages.ros.default_type('int32',1);
[data.lane_change_flag, info.lane_change_flag] = ros.internal.ros.messages.ros.default_type('logical',1);
[data.speed_limit, info.speed_limit] = ros.internal.ros.messages.ros.default_type('single',1);
[data.waypoints, info.waypoints] = ros.internal.ros.custommessages.hmcl_msgs.waypoint;
info.waypoints.MLdataType = 'struct';
info.waypoints.MaxLen = NaN;
info.waypoints.MinLen = 0;
data.waypoints = data.waypoints([],1);
[data.trafficlights, info.trafficlights] = ros.internal.ros.custommessages.hmcl_msgs.trafficlight;
info.trafficlights.MLdataType = 'struct';
info.trafficlights.MaxLen = NaN;
info.trafficlights.MinLen = 0;
data.trafficlights = data.trafficlights([],1);
[data.speedbumps, info.speedbumps] = ros.internal.ros.custommessages.hmcl_msgs.waypoint;
info.speedbumps.MLdataType = 'struct';
info.speedbumps.MaxLen = NaN;
info.speedbumps.MinLen = 0;
data.speedbumps = data.speedbumps([],1);
info.MessageType = 'hmcl_msgs/Lane';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,100);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'lane_id';
info.MatPath{8} = 'lane_change_flag';
info.MatPath{9} = 'speed_limit';
info.MatPath{10} = 'waypoints';
info.MatPath{11} = 'waypoints.gid';
info.MatPath{12} = 'waypoints.lid';
info.MatPath{13} = 'waypoints.pose';
info.MatPath{14} = 'waypoints.pose.header';
info.MatPath{15} = 'waypoints.pose.header.seq';
info.MatPath{16} = 'waypoints.pose.header.stamp';
info.MatPath{17} = 'waypoints.pose.header.stamp.sec';
info.MatPath{18} = 'waypoints.pose.header.stamp.nsec';
info.MatPath{19} = 'waypoints.pose.header.frame_id';
info.MatPath{20} = 'waypoints.pose.pose';
info.MatPath{21} = 'waypoints.pose.pose.position';
info.MatPath{22} = 'waypoints.pose.pose.position.x';
info.MatPath{23} = 'waypoints.pose.pose.position.y';
info.MatPath{24} = 'waypoints.pose.pose.position.z';
info.MatPath{25} = 'waypoints.pose.pose.orientation';
info.MatPath{26} = 'waypoints.pose.pose.orientation.x';
info.MatPath{27} = 'waypoints.pose.pose.orientation.y';
info.MatPath{28} = 'waypoints.pose.pose.orientation.z';
info.MatPath{29} = 'waypoints.pose.pose.orientation.w';
info.MatPath{30} = 'waypoints.twist';
info.MatPath{31} = 'waypoints.twist.header';
info.MatPath{32} = 'waypoints.twist.header.seq';
info.MatPath{33} = 'waypoints.twist.header.stamp';
info.MatPath{34} = 'waypoints.twist.header.stamp.sec';
info.MatPath{35} = 'waypoints.twist.header.stamp.nsec';
info.MatPath{36} = 'waypoints.twist.header.frame_id';
info.MatPath{37} = 'waypoints.twist.twist';
info.MatPath{38} = 'waypoints.twist.twist.linear';
info.MatPath{39} = 'waypoints.twist.twist.linear.x';
info.MatPath{40} = 'waypoints.twist.twist.linear.y';
info.MatPath{41} = 'waypoints.twist.twist.linear.z';
info.MatPath{42} = 'waypoints.twist.twist.angular';
info.MatPath{43} = 'waypoints.twist.twist.angular.x';
info.MatPath{44} = 'waypoints.twist.twist.angular.y';
info.MatPath{45} = 'waypoints.twist.twist.angular.z';
info.MatPath{46} = 'waypoints.lane_id';
info.MatPath{47} = 'trafficlights';
info.MatPath{48} = 'trafficlights.header';
info.MatPath{49} = 'trafficlights.header.seq';
info.MatPath{50} = 'trafficlights.header.stamp';
info.MatPath{51} = 'trafficlights.header.stamp.sec';
info.MatPath{52} = 'trafficlights.header.stamp.nsec';
info.MatPath{53} = 'trafficlights.header.frame_id';
info.MatPath{54} = 'trafficlights.id';
info.MatPath{55} = 'trafficlights.pose';
info.MatPath{56} = 'trafficlights.pose.x';
info.MatPath{57} = 'trafficlights.pose.y';
info.MatPath{58} = 'trafficlights.pose.z';
info.MatPath{59} = 'trafficlights.valid_stop_line';
info.MatPath{60} = 'trafficlights.stop_line';
info.MatPath{61} = 'trafficlights.stop_line.x';
info.MatPath{62} = 'trafficlights.stop_line.y';
info.MatPath{63} = 'trafficlights.stop_line.z';
info.MatPath{64} = 'speedbumps';
info.MatPath{65} = 'speedbumps.gid';
info.MatPath{66} = 'speedbumps.lid';
info.MatPath{67} = 'speedbumps.pose';
info.MatPath{68} = 'speedbumps.pose.header';
info.MatPath{69} = 'speedbumps.pose.header.seq';
info.MatPath{70} = 'speedbumps.pose.header.stamp';
info.MatPath{71} = 'speedbumps.pose.header.stamp.sec';
info.MatPath{72} = 'speedbumps.pose.header.stamp.nsec';
info.MatPath{73} = 'speedbumps.pose.header.frame_id';
info.MatPath{74} = 'speedbumps.pose.pose';
info.MatPath{75} = 'speedbumps.pose.pose.position';
info.MatPath{76} = 'speedbumps.pose.pose.position.x';
info.MatPath{77} = 'speedbumps.pose.pose.position.y';
info.MatPath{78} = 'speedbumps.pose.pose.position.z';
info.MatPath{79} = 'speedbumps.pose.pose.orientation';
info.MatPath{80} = 'speedbumps.pose.pose.orientation.x';
info.MatPath{81} = 'speedbumps.pose.pose.orientation.y';
info.MatPath{82} = 'speedbumps.pose.pose.orientation.z';
info.MatPath{83} = 'speedbumps.pose.pose.orientation.w';
info.MatPath{84} = 'speedbumps.twist';
info.MatPath{85} = 'speedbumps.twist.header';
info.MatPath{86} = 'speedbumps.twist.header.seq';
info.MatPath{87} = 'speedbumps.twist.header.stamp';
info.MatPath{88} = 'speedbumps.twist.header.stamp.sec';
info.MatPath{89} = 'speedbumps.twist.header.stamp.nsec';
info.MatPath{90} = 'speedbumps.twist.header.frame_id';
info.MatPath{91} = 'speedbumps.twist.twist';
info.MatPath{92} = 'speedbumps.twist.twist.linear';
info.MatPath{93} = 'speedbumps.twist.twist.linear.x';
info.MatPath{94} = 'speedbumps.twist.twist.linear.y';
info.MatPath{95} = 'speedbumps.twist.twist.linear.z';
info.MatPath{96} = 'speedbumps.twist.twist.angular';
info.MatPath{97} = 'speedbumps.twist.twist.angular.x';
info.MatPath{98} = 'speedbumps.twist.twist.angular.y';
info.MatPath{99} = 'speedbumps.twist.twist.angular.z';
info.MatPath{100} = 'speedbumps.lane_id';
