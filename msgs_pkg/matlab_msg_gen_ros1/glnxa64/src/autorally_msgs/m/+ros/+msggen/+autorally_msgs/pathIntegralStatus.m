
classdef pathIntegralStatus < ros.Message
    %pathIntegralStatus MATLAB implementation of autorally_msgs/pathIntegralStatus
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'autorally_msgs/pathIntegralStatus' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = '02d521c9eb95ab130c6fffe5772d2229' % The MD5 Checksum of the message definition
        PropertyList = { 'Header' 'Info' 'Status' } % List of non-constant message properties
        ROSPropertyList = { 'header' 'info' 'status' } % List of non-constant ROS message properties
        PropertyMessageTypes = { 'ros.msggen.std_msgs.Header' ...
			 '' ...
			 '' ...
			 } % Types of contained nested messages
    end
    properties (Constant)
    end
    properties
        Header
        Info
        Status
    end
    methods
        function set.Header(obj, val)
            validAttributes = {'nonempty', 'scalar'};
            validClasses = {'ros.msggen.std_msgs.Header'};
            validateattributes(val, validClasses, validAttributes, 'pathIntegralStatus', 'Header')
            obj.Header = val;
        end
        function set.Info(obj, val)
            val = convertStringsToChars(val);
            validClasses = {'char', 'string'};
            validAttributes = {};
            validateattributes(val, validClasses, validAttributes, 'pathIntegralStatus', 'Info');
            obj.Info = char(val);
        end
        function set.Status(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'pathIntegralStatus', 'Status');
            obj.Status = int32(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.autorally_msgs.pathIntegralStatus.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.autorally_msgs.pathIntegralStatus;
            obj.reload(strObj);
        end
    end
end
