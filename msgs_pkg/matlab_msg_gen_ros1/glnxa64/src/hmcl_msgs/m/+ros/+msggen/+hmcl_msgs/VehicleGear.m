
classdef VehicleGear < ros.Message
    %VehicleGear MATLAB implementation of hmcl_msgs/VehicleGear
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'hmcl_msgs/VehicleGear' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = '8bb854d7dfa42e038a119fb419a368ec' % The MD5 Checksum of the message definition
        PropertyList = { 'Gear' } % List of non-constant message properties
        ROSPropertyList = { 'gear' } % List of non-constant ROS message properties
        PropertyMessageTypes = { '' ...
			 } % Types of contained nested messages
    end
    properties (Constant)
    end
    properties
        Gear
    end
    methods
        function set.Gear(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'VehicleGear', 'Gear');
            obj.Gear = uint8(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.hmcl_msgs.VehicleGear.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.hmcl_msgs.VehicleGear;
            obj.reload(strObj);
        end
    end
end