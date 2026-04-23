function [varargout]= vdynblksrefconfig(varargin)
%

%   Copyright 2018-2025 The MathWorks, Inc.

% Disable OpenGL warning for parsim

block = varargin{1};
maskMode = varargin{2};
varargout{1} = {};
simStopped = autoblkschecksimstopped(block);
manType = get_param(block,'manType');
prevType = get_param(block,'prevType');
TrajDataSource = get_param(block,'TrajDataSource');
vehSys = bdroot(block);
visPath = [vehSys '/Visualization'];
visHandle = getSimulinkBlockHandle(visPath);
manOverride = strcmp(get_param(block,'manOverride'),'on');
sim3dEnabled = strcmp(get_param(block,'engine3D'),'Enabled');
maskObj = Simulink.Mask.get(block);
% maskMode
% 0 = initialization
% 1 = manType mask visibilities and default time, scene and location specifications
% 2 = update model time button
% 3 = manual override mask visibilities
% 4 = graphics mask visibilities
% 5 = speed control override
% 6 = track data source menu
% 7 = plot trajectory button
% 8 = steering type visibility
% 9 = test activation type visibility
% 10 = ayStop mask visibility
% 11 = cr max ay mask visibility
% 12 = roll rate mask visibility
% 13 = WOT param visibilities


switch maskMode
    case 0
        if simStopped %&& ~strcmp(prevType,manType)
            switch manType
                case 'Double Lane Change'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Double Lane Change');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');
                        updateScopes(vehSys,visHandle,'1','1');
                    end
                    simTime = 25;
                case 'Increasing Steer'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Increasing Steer');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');
                        updateScopes(vehSys,visHandle,'0','0');
                    end
                    simTime = 60;
                case 'Swept Sine'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Swept Sine');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if  manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');
                        updateScopes(vehSys,visHandle,'0','0');
                    end

                    simTime = 40;
                case 'Sine with Dwell'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Sine with Dwell');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if  manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');
                        updateScopes(vehSys,visHandle,'0','0');
                    end
                    simTime = 25;
                case 'Constant Radius'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Constant Radius');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');  % this in turn will also update the driver params if needed
                        updateScopes(vehSys,visHandle,'2','1');
                    end

                    simTime = 60;
                case 'Constant Radius RCP'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Constant Radius RCP');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');  % this in turn will also update the driver params if needed
                        updateScopes(vehSys,visHandle,'2','1');
                    end

                    simTime = 60;
                case 'Oval Track'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Moto Target Trajectory');
                    set_param([block '/Reference Generator/Moto Target Trajectory'],'manType','Oval Track');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if  manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');  % this in turn will also update the driver params if needed
                        updateScopes(vehSys,visHandle,'2','1');
                    end
                    simTime = 60;
                case 'User Defined Track'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Moto Target Trajectory');
                    set_param([block '/Reference Generator/Moto Target Trajectory'],'manType','User Defined Track');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if  manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');  % this in turn will also update the driver params if needed
                        updateScopes(vehSys,visHandle,'2','1');
                    end
                    simTime = 60;
                case 'Fishhook'
                    set_param([block '/Reference Generator'],'LabelModeActiveChoice','Fishhook');
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if  manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Predictive Rider');
                        updateScopes(vehSys,visHandle,'0','0');
                    end
                    simTime = 40;
                case 'Drive Cycle'
                    cycleVar = get_param(block,'cycleVar');
                    if ~strcmp(cycleVar,'Wide Open Throttle (WOT)')
                        set_param([block '/Reference Generator'],'LabelModeActiveChoice','Drive Cycle'); 
                        loadedCycle = get_param([block '/Reference Generator/Drive Cycle/Drive Cycle Source'],'UserData');
                    else
                        set_param([block '/Reference Generator'],'LabelModeActiveChoice','WOT');
                        loadedCycle = get_param([block '/Reference Generator/WOT/Drive Cycle Source'],'UserData');                        
                    end
                    set_param([block '/Reference Router'],'LabelModeActiveChoice','Maneuver Tracking');
                    if manOverride
                        set_param([vehSys '/Rider Commands'],'driverType','Longitudinal Rider');
                        set_param(block,'engine3D','Disabled');
                        updateScopes(vehSys,visHandle,'0','2');
                    end
                    
                    if ~isempty(loadedCycle)
                        %if workspace variable or other sources are selected
                        timeVec = loadedCycle.Time;
                        simTime = timeVec(end);
                    else
                        simTime = 0;
                    end
                otherwise
                    if simStopped
                        SpdCtrlOverride = get_param(block,'SpdCtrlOverride');
                        if strcmp(SpdCtrlOverride, 'on')
                            set_param([block '/Reference Generator'],'LabelModeActiveChoice','Manual Maneuver Design');
                            set_param([block '/Reference Router'],'LabelModeActiveChoice','Steering and Accel and Brk Command Override');
                            % VarLabel = '/Reference Router/Steering and Accel and Brk Command Override/Control Signals';
                        else
                            set_param([block '/Reference Generator'],'LabelModeActiveChoice','Longitudinal Maneuver Tracking');
                            set_param([block '/Reference Router'],'LabelModeActiveChoice','Steering Command Override');
                            %VarLabel = '/Reference Router/Steering Command Override/Control Signals';
                        end
                        % OverrideType = get_param(block,'OverrideType');
                        % ActType = get_param(block,'ActType');
                        % if strcmp(OverrideType, 'Steering torque override')
                        %     ManOverType = "T";
                        % else
                        %     ManOverType = "A";
                        % end
                        % if strcmp(ActType, 'Time-based activation')
                        %     ManOverType = append(ManOverType,"T");
                        % else
                        %     ManOverType = append(ManOverType,"P");
                        % end
                        % switch ManOverType
                        %     case "TT"
                        %         set_param([block VarLabel],'LabelModeActiveChoice','Time-Based Torque');
                        %     case "TP"
                        %         set_param([block VarLabel],'LabelModeActiveChoice','Position-Based Torque');
                        %     case "AT"
                        %         set_param([block VarLabel],'LabelModeActiveChoice','Time-Based Angle');
                        %     otherwise
                        %         set_param([block VarLabel],'LabelModeActiveChoice','Position-Based Angle');
                        % end
                    end
                    if manOverride
                        updateScopes(vehSys,visHandle,'0','0');
                    end
                    simTime = setTimeForManeuverOverride(block);
            end
            % update driver sldd, and 3D initial positions
            if simStopped && manOverride && ~strcmp(prevType,manType)
                update3DScene(block,manType);
                [~] = vdynblksmdlWSconfig(block,false);
                dictionaryObj = Simulink.data.dictionary.open('VirtualMotoTemplate.sldd');
                dDataSectObj = getSection(dictionaryObj,'Design Data');
                list=VirtualAssemblyScenarioParaList(manType);
                for i=1:length(list)
                    ddObj = getEntry(dDataSectObj,list{i}{1});
                    setValue(ddObj,str2double(list{i}{2}));
                end
                saveChanges(dictionaryObj);
            end
            if manOverride
                set_param(block,'simTime',num2str(simTime));
                set_param(vehSys,'StopTime',num2str(simTime));
            end
            set_param(block,'prevType',manType)
        end
    case 1
        switch manType
            case 'Double Lane Change'
                autoblksenableparameters(block, [], [],{'DLCGroup'},{'ISGroup';'CRGroup';'SSGroup';'SDGroup';'FHGroup';'DCGroup';'MOGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,{'t_start','xdot_r','xdotUnit'},{'steerDir'},{'SpdCtrlOverride'},[],true);
            case 'Increasing Steer'
                autoblksenableparameters(block, [], [],{'ISGroup'},{'DLCGroup';'CRGroup';'SSGroup';'SDGroup';'FHGroup';'DCGroup';'MOGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,{'steerDir','t_start','xdot_r','xdotUnit'},{'SpdCtrlOverride'},[],[],true);
            case 'Swept Sine'
                autoblksenableparameters(block, [], [],{'SSGroup'},{'ISGroup';'DLCGroup';'CRGroup';'SDGroup';'FHGroup';'DCGroup';'MOGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,[],{'steerDir','t_start','xdot_r','xdotUnit'},{'SpdCtrlOverride'},[],true);
            case 'Sine with Dwell'
                autoblksenableparameters(block, [], [],{'SDGroup'},{'ISGroup';'DLCGroup';'CRGroup';'SSGroup';'FHGroup';'DCGroup';'MOGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,{'steerDir','t_start','xdot_r','xdotUnit'},{'SpdCtrlOverride'},[],[],true);
            case 'Constant Radius'
                autoblksenableparameters(block, [], [],{'CRGroup'},{'DLCGroup';'ISGroup';'SSGroup';'SDGroup';'FHGroup';'DCGroup';'MOGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,{'steerDir','t_start','xdot_r','xdotUnit'},{'SpdCtrlOverride'},[],[],true);
            case 'Constant Radius RCP'
                maskObj.getParameter('SpdCtrlOverride').Enabled = 'off';
                maskObj.getParameter('SpdCtrlOverride').Value = 'off';
                autoblksenableparameters(block, [], [],{'CRGroup'},{'DLCGroup';'ISGroup';'SSGroup';'SDGroup';'FHGroup';'DCGroup';'MOGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,{'steerDir','t_start','xdot_r','xdotUnit'},{'SpdCtrlOverride'},[],[],true);
            case 'Oval Track'
                autoblksenableparameters(block,{'steerDir','t_start','xdot_r','xdotUnit'},[],[],[],true);
                autoblksenableparameters(block, [], [],{'TPOvalGroup';'RidTrajContGl'},{'CRGroup';'DLCGroup';'ISGroup';'SSGroup';'SDGroup';'FHGroup';'DCGroup';'MOGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,{'steerDir','t_start','xdot_r','xdotUnit'},{'SpdCtrlOverride'},[],[],true);
            case 'User Defined Track'
                f = @(panel) maskObj.getDialogControl(panel);
                [MATmsk,CSVmsk,Varmsk] = deal(f('MATFilePannel'),f('CSVFilePannel'),f('VariablePannel'));
                % On Off & variable setting
                OnOff = {'off','off','off'}; % {'MAT','CSV','Variable'}
                % get data source
                DatSrc = maskObj.getParameter('TrajDataSource').Value;
                switch DatSrc
                    case 'MAT File'
                        OnOff{1} = 'on';
                    case 'CSV File'
                        OnOff{2} = 'on';
                    case 'Variable'
                        OnOff{3} = 'on';
                end
                [MATmsk.Visible,CSVmsk.Visible,Varmsk.Visible] = deal(OnOff{:});
                autoblksenableparameters(block, [], [], {'TPUserDefGroup';'RidTrajContGl'},{'DLCGroup';'CRGroup';'ISGroup';'SSGroup';'SDGroup';'FHGroup';'DCGroup';'MOGroup';'TPOvalGroup'});
                autoblksenableparameters(block,{'steerDir','t_start','xdot_r','xdotUnit'},{'SpdCtrlOverride','steerDir'},[],[],true);
            case 'Fishhook'
                autoblksenableparameters(block, [], [],{'FHGroup'},{'ISGroup';'DLCGroup';'CRGroup';'SDGroup';'SSGroup';'DCGroup';'MOGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,{'steerDir','t_start','xdot_r','xdotUnit'},{'SpdCtrlOverride'},[],[],true);
                pFdbkChk = get_param(block,'pFdbk');
                if strcmp(pFdbkChk,'off')
                    autoblksenableparameters(block,{'tDwell1'},{'pZero'},[],[],'false')
                else
                    autoblksenableparameters(block,{'pZero'},{'tDwell1'},[],[],'false')
                end
            case 'Drive Cycle'
                autoblksenableparameters(block, [], [],{'DCGroup'},{'ISGroup';'CRGroup';'SSGroup';'SDGroup';'FHGroup';'DLCGroup';'MOGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block,{'xdotUnit'},{'SpdCtrlOverride','steerDir','t_start','xdot_r'},[],[],true);
            otherwise
                autoblksenableparameters(block, {'SpdCtrlOverride'}, {'OverrideType'},{'MOGroup'},{'ISGroup';'DLCGroup';'CRGroup';'SDGroup';'SSGroup';'DCGroup';'FHGroup';'TPOvalGroup';'TPUserDefGroup';'RidTrajContGl'});
                autoblksenableparameters(block, [], {'OverrideType'},[],[]);
                [~]=vdynblksrefconfig(gcb,5);
                [~]=vdynblksrefconfig(gcb,8);
                [~]=vdynblksrefconfig(gcb,9);
                [~]=vdynblksrefconfig(gcb,3);
        end
    case 2  % update time button
        if simStopped
            simTime = get_param(block,'simTime');
            set_param(vehSys,'StopTime',num2str(simTime));
        end
    case 3 % manual override
        if manOverride
            autoblksenableparameters(block,[],[],[],{'simTimeGroup'},true);
            [~]=vdynblksrefconfig(gcb,0);
        else
            autoblksenableparameters(block,[],[],{'simTimeGroup'},[],true);
        end
    case 4 % mask update for graphics enabling
        if sim3dEnabled
            autoblksenableparameters(block,[],[],{'engine3DSettingsGroup'},[],true);
        else
            autoblksenableparameters(block,[],[],[],{'engine3DSettingsGroup'},true);
        end

    case 5
        SpdCtrlOverride = get_param(block,'SpdCtrlOverride');
        if strcmp(SpdCtrlOverride, 'on') || strcmp(manType,'Drive Cycle')
            autoblksenableparameters(block,{'xdotUnit'},{'t_start','xdot_r'},[],[],true);
            autoblksenableparameters(block,{'AccTbl','BrkTbl'},[],[],[]);
        else
            autoblksenableparameters(block,{'t_start','xdot_r','xdotUnit'},[],[],[],true);
            autoblksenableparameters(block,[],{'AccTbl','BrkTbl'},[],[]);
        end

    case 6 % Track data source menu control
        % get mask values
        % Get dialog control
        f = @(panel) maskObj.getDialogControl(panel);
        [MATmsk,CSVmsk,Varmsk] = deal(f('MATFilePannel'),f('CSVFilePannel'),f('VariablePannel'));
        % Visible On Off & variable setting
        OnOff = {'off','off','off'}; % {'MAT','CSV','Variable'}
        switch TrajDataSource
            case 'MAT File'
                OnOff{1} = 'on';

            case 'CSV File'
                OnOff{2} = 'on';

            case 'Variable'
                OnOff{3} = 'on';

        end
        [MATmsk.Visible,CSVmsk.Visible,Varmsk.Visible] = deal(OnOff{:});


    case 7 % Push button control for drawing trajectory
        vehdynicon('vedhynsmtovalmaneuver',gcb,3);
    case 8
        OverrideType = get_param(block,'OverrideType');
        if strcmp(OverrideType, 'Steering torque override')
            autoblksenableparameters(block,{'StrgTrqTbl'},{'StrgAngTbl'},[],[]);
        else
            autoblksenableparameters(block,{'StrgAngTbl'},{'StrgTrqTbl'},[],[]);
        end
    case 9
        ActType = get_param(block,'ActType');
        if strcmp(ActType, 'Time-based activation')
            autoblksenableparameters(block,{'TimeBpts'},{'LongPosBpts'},[],[]);
        else
            autoblksenableparameters(block,{'LongPosBpts'},{'TimeBpts'},[],[]);
        end
    case 10
        if strcmp(get_param(gcb,'ay_stop'),'off')
            autoblksenableparameters(gcb, [], {'ay_max'},[],[],true);
        else
            autoblksenableparameters(gcb,{'ay_max'},[],[],[],true);
        end
    case 11
        if strcmp(get_param(gcb,'cr_ay_stop'),'off')
            autoblksenableparameters(gcb, [], {'cr_ay_max'},[],[],true);
        else
            autoblksenableparameters(gcb,{'cr_ay_max'},[],[],[],true);
        end
    case 12
        pFdbkChk = get_param(block,'pFdbk');
        if strcmp(pFdbkChk,'off')
            autoblksenableparameters(block,{'tDwell1'},{'pZero'},[],[],'false')
        else
            autoblksenableparameters(block,{'pZero'},{'tDwell1'},[],[],'false')
        end
    case 13
        if simStopped
            cycleVar = get_param(block,'cycleVar');
            if ~strcmp(cycleVar,'Wide Open Throttle (WOT)')
                autoblksenableparameters(block,[],{'t_wot2';'t_wotend';'xdot_wot1';'srcUnit'},[],[])
            else
                autoblksenableparameters(block,{'t_wot2';'t_wotend';'xdot_wot1';'srcUnit'},[],[],[])
            end
        end
end
end
function simTime = setTimeForManeuverOverride(block)
dictionaryObj = Simulink.data.dictionary.open('VirtualMotoTemplate.sldd');
dDataSectObj = getSection(dictionaryObj,'Design Data');
TimeBpts = getValue(getEntry(dDataSectObj,'ScnTimeBpts'));
t_start = getValue(getEntry(dDataSectObj,'ScnStartTime'));
LongPosBpts = getValue(getEntry(dDataSectObj,'ScnLongPosBpts'));
xdot_r = getValue(getEntry(dDataSectObj,'ScnLongVelRef'));

ActType = get_param(block,'ActType');
if strcmp(ActType, 'Time-based activation')
    simTime = max(TimeBpts);
else
    simTime = t_start + max(LongPosBpts)/xdot_r;
end
end
function update3DScene(block,manType)
sim3DBlkPath = block;
if strcmp(manType,'Double Lane Change')
    set_param(sim3DBlkPath,'SceneDesc','Double lane change');
else
    set_param(sim3DBlkPath,'SceneDesc','Open surface');
end
end
function updateScopes(vehSys,visHandle,scopeType,XYPlotterType)
if visHandle ~= -1
    set_param([vehSys '/Visualization/Scope Type'],'LabelModeActiveChoice',scopeType);
    set_param([vehSys '/Visualization/Vehicle XY Plotter'],'LabelModeActiveChoice',XYPlotterType);
else
    disp('Warning: Visualization subsystem not found. Model scopes and visualizaiton aids may not function as expected.')
end
end
