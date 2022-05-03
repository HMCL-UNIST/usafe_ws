
classdef VehicleSteering < ros.Message
    %VehicleSteering MATLAB implementation of hmcl_msgs/VehicleSteering
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'hmcl_msgs/VehicleSteering' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = '5fb428b383c979ad23048575d907b4bf' % The MD5 Checksum of the message definition
        PropertyList = { 'Header' 'Takeover' 'Mode' 'SteeringAngle' } % List of non-constant message properties
        ROSPropertyList = { 'header' 'takeover' 'mode' 'steering_angle' } % List of non-constant ROS message properties
        PropertyMessageTypes = { 'ros.msggen.std_msgs.Header' ...
			 '' ...
			 '' ...
			 '' ...
			 } % Types of contained nested messages
    end
    properties (Constant)
    end
    properties
        Header
        Takeover
        Mode
        SteeringAngle
    end
    methods
        function set.Header(obj, val)
            validAttributes = {'nonempty', 'scalar'};
            validClasses = {'ros.msggen.std_msgs.Header'};
            validateattributes(val, validClasses, validAttributes, 'VehicleSteering', 'Header')
            obj.Header = val;
        end
        function set.Takeover(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'VehicleSteering', 'Takeover');
            obj.Takeover = uint8(val);
        end
        function set.Mode(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'VehicleSteering', 'Mode');
            obj.Mode = uint8(val);
        end
        function set.SteeringAngle(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'VehicleSteering', 'SteeringAngle');
            obj.SteeringAngle = single(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.hmcl_msgs.VehicleSteering.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.hmcl_msgs.VehicleSteering;
            obj.reload(strObj);
        end
    end
end
