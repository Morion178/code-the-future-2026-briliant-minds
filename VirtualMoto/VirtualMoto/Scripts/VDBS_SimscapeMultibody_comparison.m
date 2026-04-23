%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% VDBS - Simscape Multibody COMPARISON SCRIPT
%
% Copyright 2021 The MathWorks, Inc.
%
% validate numerical model by comparing SSMB result
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear;close all;Simulink.sdi.clear;

model  = 'MotoLongBTReferenceApplication';
ov_ori = Simulink.SimulationData.ModelLoggingInfo(model);
mi = Simulink.SimulationData.ModelLoggingInfo.createFromModel(model);
% Target signals
VDBSvehInfo = [model,'/Motorcycle Vehicle/Body, Suspension, Wheels/Longitudinal/Chassis&Tires/Motorcycle Body Longitudinal In-Plane1'];
VEBStirInfo = [model,'/Motorcycle Vehicle/Body, Suspension, Wheels/Longitudinal/Chassis&Tires/Bus Creator7'];
SSMBvehInfo = [model, '/Motorcycle Vehicle/Body, Suspension, Wheels/Simscape Multibody/Simscape Multibody model/Motorcycle Body Longitudinal In-Plane (Simscape Multibody)/Signal routine'];
SSMBtirInfo = [model, '/Motorcycle Vehicle/Body, Suspension, Wheels/Simscape Multibody/Simscape Multibody model/Bus Creator7'];

% Create new logging info
N = 1;
for n = 1:length(mi.Signals)
    if contains(mi.Signals(n).BlockPath.convertToCell(),VDBSvehInfo)
    elseif contains(mi.Signals(n).BlockPath.convertToCell(),VEBStirInfo)
    elseif contains(mi.Signals(n).BlockPath.convertToCell(),SSMBvehInfo)
    elseif contains(mi.Signals(n).BlockPath.convertToCell(),SSMBtirInfo)
    else
        ov_ori.Signals(N) = mi.Signals(n);
        N = N + 1;
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% RUN
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
set_param([model,'/Controllers/Brake Pressure Control'], 'LabelModeActiveChoice', num2str(0));
for m = 1:2
    % Log setting
    switch m
        case 1
            ov = ov_ori;
            so1 = Simulink.SimulationData.SignalLoggingInfo(VDBSvehInfo,1);
            so2 = Simulink.SimulationData.SignalLoggingInfo(VEBStirInfo,1);
            ov.Signals(N)   = so1;
            ov.Signals(N+1) = so2;
            set_param(model,'DataLoggingOverride',ov);
        case 2
            ov = ov_ori;
            so1 = Simulink.SimulationData.SignalLoggingInfo(SSMBvehInfo,1);
            so2 = Simulink.SimulationData.SignalLoggingInfo(SSMBtirInfo,1);
            ov.Signals(N)   = so1;
            ov.Signals(N+1) = so2;
            set_param(model,'DataLoggingOverride',ov);
    end
    % execute the model
    set_param([model,'/Motorcycle Vehicle/Body, Suspension, Wheels'], 'LabelModeActiveChoice', num2str(m-1));
    sim([model,'.slx'],'Solver','ode23','maxstep','1e-3','RelTol','1e-3');
end
set_param(model,'DataLoggingOverride',ov_ori); % turn off the logging
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DRAWING
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%--- setting ---%
fontN  = 'times new roman';
fontS  = 12;
linwid = 1.5;
%--- draw list ---%
DrawList = {'ChassisInfo.Whl.Genrl.Rear.Cp.Acc.xddot',...
            'ChassisInfo.Whl.Genrl.Rear.Cp.Acc.zddot',...
            'ChassisInfo.RearArm.Genrl.AngAcc.thetaraddot',...
            'ChassisInfo.Frame.Genrl.AngAcc.thetafrmddot',...
            'ChassisInfo.Fork.Genrl.Lwr.Acc.dfddot',...
            'TireFrame.Omegafdot',...
            'TireFrame.Omegardot'};
NamList  = {'d^2\itx\rm/dt^2 [m/s^2]',...
            'd^2\itz\rm/dt^2 [m/s^2]',...
            'd^2\it\theta_r_a\rm/dt^2 [rad/s^2]',...
            'd^2\it\theta_f_r_m\rm/dt^2 [rad/s^2]',...
            'd^2\itd_f\rm/dt^2 [m/s^2]',...
            'd\it\omega_f\rm/dt [rad/s^2]',...
            'd\it\omega_r\rm/dt [rad/s^2]'};
%--- get signals ---%
runIndex     = Simulink.sdi.getRunCount;
    % VDBS
    VDBS.runID   = Simulink.sdi.getRunIDByIndex(runIndex-1);
    VDBS.Run     = Simulink.sdi.getRun(VDBS.runID);
    VDBS.SigList = cell(VDBS.Run.SignalCount,1);
    % Simscape Multibody
    SSMB.runID   = Simulink.sdi.getRunIDByIndex(runIndex);
    SSMB.Run     = Simulink.sdi.getRun(SSMB.runID);
    SSMB.SigList = cell(SSMB.Run.SignalCount,1);
%--- signal list ---%
for n = 1:VDBS.Run.SignalCount
    eval(char(['VDBS.SigNamList{',num2str(n),'} = VDBS.Run.getSignalByIndex(',num2str(n),').Name;']));
    eval(char(['VDBS.SigList{',num2str(n),'} = VDBS.Run.getSignalByIndex(',num2str(n),');']));
end
for n = 1:SSMB.Run.SignalCount
    eval(char(['SSMB.SigNamList{',num2str(n),'} = SSMB.Run.getSignalByIndex(',num2str(n),').Name;']));
    eval(char(['SSMB.SigList{',num2str(n),'} = SSMB.Run.getSignalByIndex(',num2str(n),');']));
end
%--- drawing ---%
for m = 1:length(DrawList)
    VDBS.Index = find(contains(VDBS.SigNamList,DrawList{m}));
    VDBS.sig = getSignalByIndex(VDBS.Run,VDBS.Index);
    
    SSMB.Index = find(contains(SSMB.SigNamList,DrawList{m}));
    SSMB.sig = getSignalByIndex(SSMB.Run,SSMB.Index);
    
%     Simulink.sdi.view;
    
    SSMB_interp = interp1(SSMB.sig.Values.Time, SSMB.sig.Values.Data, VDBS.sig.Values.Time,'nearest');
    Error.Data = VDBS.sig.Values.Data - SSMB_interp;
    Error.Time = VDBS.sig.Values.Time;
    
    figure(1);
    set(gcf,'color','w','position',[10 10 1300 800],'Name','Generalized coordinates');
    set(figure(1),'defaultAxesColorOrder',[[0 0 0]; [0 0 0]]);
    subplot(3,3,m);
    % left
    yyaxis left;
    plot(VDBS.sig.Values.Time, VDBS.sig.Values.Data,'b-',...
         SSMB.sig.Values.Time, SSMB.sig.Values.Data,'r--','linewidth',linwid);
    ylabel(NamList{m},'fontname',fontN,'fontsize',fontS);
    % right
    yyaxis right;
    plot(Error.Time, Error.Data,'g-','linewidth',1);
    ylabel('Error','fontname',fontN,'fontsize',fontS);
    
    if m == 1
        h = legend('VDBS','Simscape Multibody','Error');
    end
    set(h,'fontname',fontN,'fontsize',fontS,'linewidth',linwid,'location','best');
    grid on;
    set(gca,'fontname',fontN,'fontsize',fontS,'linewidth',linwid);
    xlabel('Time [s]','fontname',fontN,'fontsize',fontS);
end
