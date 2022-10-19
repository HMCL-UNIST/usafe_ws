
classdef wheelSpeeds < ros.Message
    %wheelSpeeds MATLAB implementation of autorally_msgs/wheelSpeeds
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'autorally_msgs/wheelSpeeds' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = 'c5c4a96a4e17d91e72a2f7397af4d720' % The MD5 Checksum of the message definition
        PropertyList = { 'Header' 'LfSpeed' 'RfSpeed' 'LbSpeed' 'RbSpeed' } % List of non-constant message properties
        ROSPropertyList = { 'header' 'lfSpeed' 'rfSpeed' 'lbSpeed' 'rbSpeed' } % List of non-constant ROS message properties
        PropertyMessageTypes = { 'ros.msggen.std_msgs.Header' ...
			 '' ...
			 '' ...
			 '' ...
			 '' ...
			 } % Types of contained nested messages
    end
    properties (Constant)
    end
    properties
        Header
        LfSpeed
        RfSpeed
        LbSpeed
        RbSpeed
    end
    methods
        function set.Header(obj, val)
            validAttributes = {'nonempty', 'scalar'};
            validClasses = {'ros.msggen.std_msgs.Header'};
            validateattributes(val, validClasses, validAttributes, 'wheelSpeeds', 'Header')
            obj.Header = val;
        end
        function set.LfSpeed(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'wheelSpeeds', 'LfSpeed');
            obj.LfSpeed = double(val);
        end
        function set.RfSpeed(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'wheelSpeeds', 'RfSpeed');
            obj.RfSpeed = double(val);
        end
        function set.LbSpeed(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'wheelSpeeds', 'LbSpeed');
            obj.LbSpeed = double(val);
        end
        function set.RbSpeed(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'wheelSpeeds', 'RbSpeed');
            obj.RbSpeed = double(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.autorally_msgs.wheelSpeeds.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.autorally_msgs.wheelSpeeds;
            obj.reload(strObj);
        end
    end
end
