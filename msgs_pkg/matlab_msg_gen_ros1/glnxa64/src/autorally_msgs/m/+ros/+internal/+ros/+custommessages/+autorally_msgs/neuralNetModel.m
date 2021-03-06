function [data, info] = neuralNetModel
%neuralNetModel gives an empty data for autorally_msgs/neuralNetModel
% Copyright 2019-2020 The MathWorks, Inc.
data = struct();
[data.header, info.header] = ros.internal.ros.messages.std_msgs.header;
info.header.MLdataType = 'struct';
[data.network, info.network] = ros.internal.ros.custommessages.autorally_msgs.neuralNetLayer;
info.network.MLdataType = 'struct';
info.network.MaxLen = NaN;
info.network.MinLen = 0;
data.network = data.network([],1);
[data.numLayers, info.numLayers] = ros.internal.ros.messages.ros.default_type('int32',1);
[data.structure, info.structure] = ros.internal.ros.messages.ros.default_type('int32',NaN);
info.MessageType = 'autorally_msgs/neuralNetModel';
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
info.MatPath{7} = 'network';
info.MatPath{8} = 'network.name';
info.MatPath{9} = 'network.weight';
info.MatPath{10} = 'network.bias';
info.MatPath{11} = 'numLayers';
info.MatPath{12} = 'structure';
