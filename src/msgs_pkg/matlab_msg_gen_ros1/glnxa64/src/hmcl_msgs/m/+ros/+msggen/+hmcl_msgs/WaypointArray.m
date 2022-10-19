
classdef WaypointArray < ros.Message
    %WaypointArray MATLAB implementation of hmcl_msgs/WaypointArray
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'hmcl_msgs/WaypointArray' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = '796182af49bd48aa8ba60ed21519725c' % The MD5 Checksum of the message definition
        PropertyList = { 'X' 'Y' } % List of non-constant message properties
        ROSPropertyList = { 'x' 'y' } % List of non-constant ROS message properties
        PropertyMessageTypes = { '' ...
			 '' ...
			 } % Types of contained nested messages
    end
    properties (Constant)
    end
    properties
        X
        Y
    end
    methods
        function set.X(obj, val)
            validClasses = {'numeric'};
            if isempty(val)
                % Allow empty [] input
                val = double.empty(0, 1);
            end
            val = val(:);
            validAttributes = {'vector'};
            validateattributes(val, validClasses, validAttributes, 'WaypointArray', 'X');
            obj.X = double(val);
        end
        function set.Y(obj, val)
            validClasses = {'numeric'};
            if isempty(val)
                % Allow empty [] input
                val = double.empty(0, 1);
            end
            val = val(:);
            validAttributes = {'vector'};
            validateattributes(val, validClasses, validAttributes, 'WaypointArray', 'Y');
            obj.Y = double(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.hmcl_msgs.WaypointArray.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.hmcl_msgs.WaypointArray;
            obj.reload(strObj);
        end
    end
end
