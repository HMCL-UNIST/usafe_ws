
classdef Gpgst < ros.Message
    %Gpgst MATLAB implementation of nmea_msgs/Gpgst
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'nmea_msgs/Gpgst' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = 'e4b77f6f4c211629ab0307177f71dcee' % The MD5 Checksum of the message definition
        PropertyList = { 'Header' 'MessageId' 'UtcSeconds' 'Rms' 'SemiMajorDev' 'SemiMinorDev' 'Orientation' 'LatDev' 'LonDev' 'AltDev' } % List of non-constant message properties
        ROSPropertyList = { 'header' 'message_id' 'utc_seconds' 'rms' 'semi_major_dev' 'semi_minor_dev' 'orientation' 'lat_dev' 'lon_dev' 'alt_dev' } % List of non-constant ROS message properties
        PropertyMessageTypes = { 'ros.msggen.std_msgs.Header' ...
			 '' ...
			 '' ...
			 '' ...
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
        MessageId
        UtcSeconds
        Rms
        SemiMajorDev
        SemiMinorDev
        Orientation
        LatDev
        LonDev
        AltDev
    end
    methods
        function set.Header(obj, val)
            validAttributes = {'nonempty', 'scalar'};
            validClasses = {'ros.msggen.std_msgs.Header'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'Header')
            obj.Header = val;
        end
        function set.MessageId(obj, val)
            val = convertStringsToChars(val);
            validClasses = {'char', 'string'};
            validAttributes = {};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'MessageId');
            obj.MessageId = char(val);
        end
        function set.UtcSeconds(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'UtcSeconds');
            obj.UtcSeconds = double(val);
        end
        function set.Rms(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'Rms');
            obj.Rms = single(val);
        end
        function set.SemiMajorDev(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'SemiMajorDev');
            obj.SemiMajorDev = single(val);
        end
        function set.SemiMinorDev(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'SemiMinorDev');
            obj.SemiMinorDev = single(val);
        end
        function set.Orientation(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'Orientation');
            obj.Orientation = single(val);
        end
        function set.LatDev(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'LatDev');
            obj.LatDev = single(val);
        end
        function set.LonDev(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'LonDev');
            obj.LonDev = single(val);
        end
        function set.AltDev(obj, val)
            validClasses = {'numeric'};
            validAttributes = {'nonempty', 'scalar'};
            validateattributes(val, validClasses, validAttributes, 'Gpgst', 'AltDev');
            obj.AltDev = single(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.nmea_msgs.Gpgst.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.nmea_msgs.Gpgst;
            obj.reload(strObj);
        end
    end
end
