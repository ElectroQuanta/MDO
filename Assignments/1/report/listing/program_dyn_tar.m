%% IMPORTANT: 
% Before running this script, open the scenario in VREP, e.g
% Do not run simulation!
%% Last change: Estela Bicho Erlhagen, 18/10/2018
%% run this with scenario MobileRobotDyn_Tar.ttt

% Try to connect to simulator and initialize robot class:
vehicle = RobDyn_robot();

%get time step, dt, value (normally dt=50ms):
timestep = vehicle.get_simulation_timestep();  

%Get robot physical characteristics:
[Rrobot,Theta_obs] = vehicle.get_RobotCharacteristics();
%Rrobot - robot radius (in cm)
%Theta_obs - Vector with angular position of each sensor i (i = 1, ..., 11) relative to the
%frontal direction (in rad)

% Set initial velocity vrobot = 0 (linear velocity) and wrobot = 0 (angular velocity)
% and get robot's initial pose
wrobot = 0.01; %rad/s
vrobot = 0; %cm/s
[xrobot, yrobot, phirobot] = vehicle.set_velocity(wrobot, vrobot); 

% Define the (first) Target
ntarget=1; %initialize first target 

%%%---------------------- Start Robot Motion Behavior -------------------
%%%-----------------------------------------------------------------------
while ntarget<=vehicle.TARGET_Number % until robot goes to target ntarget
   
   %% Robot interface
   % set and get information to/from vrep
   % avoid do processing in between ensure_all_data and trigger_simulation
   vehicle.ensure_all_data();
   
   % Get vehicle's pose (position in cm, phirobot in rad):
   [xrobot, yrobot, phirobot] = vehicle.get_vehicle_pose();
   
   %Get target position for selected Target (Target 1 or 2 - in cm):
   [XTARGET,YTARGET] = vehicle.get_TargetPosition(ntarget); 
   
   %get simulation time
   sim_time = vehicle.get_simulation_time();
   
   %trigger simulation step
   vehicle.trigger_simulation();
  
   %% Processing step
   % Implement the dynamic systems that govern vehicle's behavior and
   % compute new angular and linear velocities...
   % The simulation timestep, dt, is stored in timestep (value is not changed
   % while simulation is running)
   % the simulation time is stored in sim_time.
   
   %%----------- BEGIN YOUR CODE HERE ----------- %
   %% 1. set parameter values
   % relation between timestep and euler step: tau_tar >> timestep
   % magnitude of attraction, lambda_tar
   % pre-factor of stochastic force, Q
   dt = timestep;
   tau_tar = 5 * dt;
   lambda_tar = 1/tau_tar;
   Q = 0.01;
   
   %% 2. compute psi_tar
   psi_tar = atan2(YTARGET - yrobot, XTARGET - xrobot);
   
   %% 3. compute ftar
   ftar = -lambda_tar * sin(phirobot - psi_tar);
   
   %% 4. compute stochastic force, stoch
   fstoch = sqrt(Q)* randn(1,1);
   
   %% 5. Compute resultant vector field
   f_total = ftar + fstoch;
   
   %% 6. Compute angular velocity
   wrobot = f_total;
   
   %% 7. Set linear velocity
   vrobot = 30; % cm/s
   
   %% 8. Stop Criterion
   
   %% view dynamics
   % visualization of the dynamics (target acquisition)
   phi_plot = (0:10:360)*pi/180;
   lphi = length(phi_plot);
   ftar_plot = -lambda_tar * sin(phi_plot - psi_tar);
   fstoch_plot = sqrt(Q) * randn(lphi, 1);
   ftotal_plot = ftar_plot;% + fstoch_plot;
   figure(1);
   clf;
   plot(phi_plot * 180/pi, ftotal_plot);
   yl = ylim; % get current axis y-axis limits
   hold on
   phi_robot_plot = phirobot;
   if(phirobot < 0)
       phi_robot_plot = phirobot + 2*pi;
   end
   line([ phi_robot_plot * 180/pi, phi_robot_plot * 180/pi], [yl(1), yl(2)]);    
   %plot(phirobot, f_total);
   hold off
   
   %%------------- END OF YOUR CODE ------------- 
   
   % set robot angular velocity (rad/s) and robot linear velocity (cm/s) 
   vehicle.set_velocity(wrobot, vrobot);  
   %-------------------------------------------------------------------------------
end
% cleanup
vehicle.terminate();