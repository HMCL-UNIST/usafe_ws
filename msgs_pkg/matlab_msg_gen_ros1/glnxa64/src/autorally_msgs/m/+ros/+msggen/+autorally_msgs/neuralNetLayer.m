
classdef neuralNetLayer < ros.Message
    %neuralNetLayer MATLAB implementation of autorally_msgs/neuralNetLayer
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'autorally_msgs/neuralNetLayer' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = '5c7ae79f2ee4ffbb5044508aa41abced' % The MD5 Checksum of the message definition
        PropertyList = { 'Name' 'Weight' 'Bias' } % List of non-constant message properties
        ROSPropertyList = { 'name' 'weight' 'bias' } % List of non-constant ROS message properties
        PropertyMessageTypes = { '' ...
			 '' ...
			 '' ...
			 } % Types of contained nested messages
    end
    properties (Constant)
    end
    properties
        Name
        Weight
        Bias
    end
    methods
        function set.Name(obj, val)
            val = convertStringsToChars(val);
            validClasses = {'char', 'string'};
            validAttributes = {};
            validateattributes(val, validClasses, validAttributes, 'neuralNetLayer', 'Name');
            obj.Name = char(val);
        end
        function set.Weight(obj, val)
            validClasses = {'numeric'};
            if isempty(val)
                % Allow empty [] input
                val = single.empty(0, 1);
            end
            val = val(:);
            validAttributes = {'vector'};
            validateattributes(val, validClasses, validAttributes, 'neuralNetLayer', 'Weight');
            obj.Weight = single(val);
        end
        function set.Bias(obj, val)
            validClasses = {'numeric'};
            if isempty(val)
                % Allow empty [] input
                val = single.empty(0, 1);
            end
            val = val(:);
            validAttributes = {'vector'};
            validateattributes(val, validClasses, validAttributes, 'neuralNetLayer', 'Bias');
            obj.Bias = single(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.autorally_msgs.neuralNetLayer.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.autorally_msgs.neuralNetLayer;
            obj.reload(strObj);
        end
    end
end