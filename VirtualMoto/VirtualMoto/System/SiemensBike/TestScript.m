mdl = 'ConfiguredVirtualVehicleModel';
open_system(mdl);

%%

%Test 1 
in(1) = Simulink.SimulationInput(mdl); 
in(1) = setParamforManeuverAndDriver('ConfiguredVirtualVehicleModel','Drive Cycle', 'FTP75', 'Longitudinal Rider',1, in(1), 'SiemensBike',1);
simout = sim(in, 'ShowSimulationManager', 'on');
save('simout.mat','simout','-v7.3');
