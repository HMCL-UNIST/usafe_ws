
classdef Frame < ros.Message
    %Frame MATLAB implementation of can_msgs/Frame
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'can_msgs/Frame' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = '64ae5cebf967dc6aae4e78f5683a5b25' % The MD5 Checksum of the message definition
        PropertyList = { 'Header' 'Id' 'IsRtr' 'IsExtended' 'IsError' 'Dlc' 'Data' } % List of non-constant message properties
        ROSPropertyList = { 'header' 'id' 'is_rtr' 'is_extended' 'is_error' 'dlc' 'data' } % List of non-constant ROS message properties
        PropertyMessageTypes = { 'ros.msggen.std_msgs.Header' ...
			 '' ...
			 '' ...
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
        Id
        IsRtr
        IsExtended
        IsError
        Dlc
        Data
    end
    methods
        function set.Header(obj, val)
            validAttributes = {'nonempty', 'scalar'};
            validClasses = {'ros.msggen.std_msgs.Header'};
            validateattributes(val, validClasses, validAttributes, 'Frame', 'Header')
            obj.Header = val;
        end
        function set.Id(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Frame', 'Id');
            obj.Id = uint32(val);
        end
        function set.IsRtr(obj, val)
            validClasses = {'logical', 'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Frame', 'IsRtr');
            obj.IsRtr = logical(val);
        end
        function set.IsExtended(obj, val)
            validClasses = {'logical', 'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Frame', 'IsExtended');
            obj.IsExtended = logical(val);
        end
        function set.IsError(obj, val)
            validClasses = {'logical', 'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Frame', 'IsError');
            obj.IsError = logical(val);
        end
        function set.Dlc(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Frame', 'Dlc');
            obj.Dlc = uint8(val);
        end
        function set.Data(obj, val)
            validClasses = {'numeric'};
            val = val(:);
            validAttributes = {'vector', 'numel', 8};
            validateattributes(val, validClasses, validAttributes, 'Frame', 'Data');
            obj.Data = uint8(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.can_msgs.Frame.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.can_msgs.Frame;
            obj.reload(strObj);
        end
    end
end