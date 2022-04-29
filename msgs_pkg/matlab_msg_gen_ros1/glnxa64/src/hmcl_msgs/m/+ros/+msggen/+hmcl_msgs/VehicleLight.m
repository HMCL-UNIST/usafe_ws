
classdef VehicleLight < ros.Message
    %VehicleLight MATLAB implementation of hmcl_msgs/VehicleLight
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'hmcl_msgs/VehicleLight' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = 'b381125a33d115f19eb1624e1387eaae' % The MD5 Checksum of the message definition
        PropertyList = { 'LeftLight' 'RightLight' 'HazardLight' } % List of non-constant message properties
        ROSPropertyList = { 'left_light' 'right_light' 'hazard_light' } % List of non-constant ROS message properties
        PropertyMessageTypes = { '' ...
			 '' ...
			 '' ...
			 } % Types of contained nested messages
    end
    properties (Constant)
    end
    properties
        LeftLight
        RightLight
        HazardLight
    end
    methods
        function set.LeftLight(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'VehicleLight', 'LeftLight');
            obj.LeftLight = uint8(val);
        end
        function set.RightLight(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'VehicleLight', 'RightLight');
            obj.RightLight = uint8(val);
        end
        function set.HazardLight(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'VehicleLight', 'HazardLight');
            obj.HazardLight = uint8(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.hmcl_msgs.VehicleLight.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.hmcl_msgs.VehicleLight;
            obj.reload(strObj);
        end
    end
end
