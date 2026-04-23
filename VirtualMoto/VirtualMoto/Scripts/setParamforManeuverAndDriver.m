function out = setParamforManeuverAndDriver(Model, Maneuver, ManeuverOption, Rider, TestID, in,configfile,licStatus)

%   Copyright 2021-2022 The MathWorks, Inc.

% Setup Mask Parameters
ManeuverType = 'manType';
if strcmp(Maneuver, 'Steady Turning') || strcmp(Maneuver, 'Handle Hit')
    Maneuver = 'Manual Maneuver Design';
elseif strcmp(Maneuver, 'Wide Open Throttle')
    Maneuver = 'Drive Cycle';
end


ManeuverMaskPath = [Model,'/Reference Generator for Motorcycle'];
RiderTypePath = [Model,'/Rider Commands'];
RiderType = 'driverType';

in=in.setBlockParameter(ManeuverMaskPath,'manOverride','off',...
    ManeuverMaskPath,'defaultPos','User-specified',...
    RiderTypePath,RiderType,Rider, ...
    ManeuverMaskPath,ManeuverType,Maneuver);


if strcmp(Maneuver,'Drive Cycle')
    in=in.setBlockParameter(ManeuverMaskPath,'cycleVar',ManeuverOption);

    try
        cyclename=VirtualAssembly.getcyclename(ManeuverOption);
        cycle=load(cyclename);
        simTime=cycle.(cyclename).Time(end);
    catch
        if strcmp(ManeuverOption,'Wide Open Throttle (WOT)')
            simTime = 40;
        else
            simTime=0;
        end
    end
elseif contains(Maneuver,'Wide Open Throttle')
    in=in.setBlockParameter(ManeuverMaskPath,'cycleVar',ManeuverOption);
    simTime=40;

else
    in=in.setBlockParameter(ManeuverMaskPath,'engine3D',ManeuverOption);

    switch Maneuver
        case 'Double Lane Change'
            simTime = 25;
            in=in.setBlockParameter(ManeuverMaskPath,'SceneDesc','Double lane change');
        case 'Increasing Steer'
            simTime = 60;
            in=in.setBlockParameter(ManeuverMaskPath,'SceneDesc','Open surface');
        case 'Swept Sine'
            simTime = 40;
            in=in.setBlockParameter(ManeuverMaskPath,'SceneDesc','Open surface');
        case 'Sine with Dwell'
            simTime = 25;
            in=in.setBlockParameter(ManeuverMaskPath,'SceneDesc','Open surface');
        case 'Constant Radius'
            simTime = 60;
            in=in.setBlockParameter(ManeuverMaskPath,'SceneDesc','Open surface');
        case 'Fishhook'
            simTime = 40;
            in=in.setBlockParameter(ManeuverMaskPath,'SceneDesc','Open surface');
        otherwise
            in=in.setBlockParameter(ManeuverMaskPath,'OverrideType','Steering torque override');
            in=in.setBlockParameter(ManeuverMaskPath,'ActType','Time-based activation');
            simTime = 15;
            in=in.setBlockParameter(ManeuverMaskPath,'SceneDesc','Open surface');
    end
end

in=in.setVariable("TestID",TestID);
in=in.setModelParameter('StopTime',num2str(simTime));

% Update simulation test data parameters

maskparamap={'ScnSteerDir','steerDir';...
    'ScnLongVelUnit','xdotUnit';...
    'ScnISLatAccStop','ay_stop';...
    };


run(configfile);
testdata=ConfigInfos.TestPlan{TestID}.Data;
if ~isempty(testdata)
    for i = 1 : size(testdata,1)

        index=find(strcmp(testdata{i,1},maskparamap(:,1)),1);

        if ~isempty(index)
            if licStatus~=1
                in=in.setBlockParameter(ManeuverMaskPath,maskparamap{index,2},testdata{i,2});
            end
        else
            if strcmp(testdata{i,1},'ScnSimTime')
                in=in.setModelParameter('StopTime',testdata{i,2});
            else
                newvalue=str2num(testdata{i,2});
                if isempty(newvalue)
                    in=in.setVariable(testdata{i,1},testdata{i,2});
                else
                    in=in.setVariable(testdata{i,1},newvalue);
                end
            end
        end
    end
end

out = in;

end


