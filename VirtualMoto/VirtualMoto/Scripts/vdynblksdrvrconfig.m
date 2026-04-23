function [varargout]= vdynblksdrvrconfig(varargin)
%
%   Copyright 2018-2024 The MathWorks, Inc.
    block = varargin{1};    
    varargout{1} = {};
    simStopped = autoblkschecksimstopped(block) && ~(strcmp(get_param(bdroot(block),'SimulationStatus'),'initializing'));
    driverType = get_param(block,'driverType');    
    if simStopped
        switch driverType
            case 'Open Loop' 
                set_param(block,'TorqueControlType','No torque control'); 
                autoblksenableparameters(block,[],[],[],{'TorqueControlGroup','TorqueControlType'});
            case 'Longitudinal Rider'
                set_param(block,'TorqueControlType','No torque control');                
                autoblksenableparameters(block,[],[],[],{'TorqueControlGroup','TorqueControlType'});
            case 'Target trajectory following'
                set_param(block,'TorqueControlType','Look ahead point model');                
                autoblksenableparameters(block,[],[],[],{'TorqueControlGroup'},{'TorqueControlType'},'true');
            case 'Roll angle control'
                set_param(block,'TorqueControlType','PID Control');                
                autoblksenableparameters(block,[],[],[],{'TorqueControlGroup'},{'TorqueControlType'},'true');
            otherwise
                set_param(block,'TorqueControlType','Torque PID control');                                
                autoblksenableparameters(block,[],[],{'TorqueControlGroup'},{'TorqueControlType'},'true');
        end
    end
end