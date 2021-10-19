%% IMPORTANT: 
% Before running this script, open the scenario in VREP, e.g
% Do not run simulation!
%
%% Last change: Estela Bicho Erlhagen, 18/10/2018
%% run this with scenario MobileRobotDyn_TarObs.ttt

% Try to connect to simulator and initialize robot class:
vehicle = RobDyn_robot();

%get time step, dt, value (normally dt=50ms):
timestep = vehicle.get_simulation_timestep();  

%Get robot physical characteristics:
[Rrobot,Theta_obs] = vehicle.get_RobotCharacteristics();

% Set initial velocity vrobot = 0 (linear velocity) and wrobot = 0 (angular velocity)
% and get robot's inicial pose
wrobot = 0.01; %rad/s
vrobot = 10; %cm/s
[xrobot, yrobot, phirobot] = vehicle.set_velocity(wrobot, vrobot); 

% Define the (first) Target
ntarget=1; %initialize first target 

%% 1. set global parameter values
% obstacles: beta1, beta2, delta_theta, Q
TOO_FAR = 75; % defines a radius for repulsive forces (cm)
N = 11; % nr of sensors
beta2 = 20; % flexible
delta_theta = Theta_obs(2) - Theta_obs(1);
Q = 0; % pre-factor of stochastic force, Q
   
%% 1.2 create vectors for psi_obs, lambda_obs, sigma
psi_obs = zeros(N,1);
lambda_obs = zeros(N,1);
sigma  = zeros(N,1);
fobs = zeros(N,1);

%%%---------------------- Start Robot Motion Behavior -------------------
%%%-----------------------------------------------------------------------
while ntarget<=vehicle.TARGET_Number % until robot goes to target ntarget
   
   %% Robot interface
   % set and get information to/from vrep
   % avoid do processing in between ensure_all_data and trigger_simulation
   vehicle.ensure_all_data();
   
   % Get vehicle's pose: (xrobot,yrobot) in cm, phirobot in rad
   [xrobot, yrobot, phirobot] = vehicle.get_vehicle_pose();
   
   %Sensorial information: get distance from obstacles (11 infrared obstacles - distance between
   %0-80cm):
   [d] = vehicle.get_DistanceSensorAquisition();  %distance in cm
   
   %get simulation time
   sim_time = vehicle.get_simulation_time();
   
   %trigger simulation step
   vehicle.trigger_simulation();
  
   %% Processing step
   %%----------- BEGIN YOUR CODE HERE ----------- %
   dt = timestep;
   tau_obs_min = 5 * dt; % flexible
   beta1 = 1/tau_obs_min; %  = lambda_obs_max = 1/tau_obs_min
   Fobs = 0;

   for i=1:N
   %% 2. for each sector compute the contribution of the repulsive forcelet
   % 2.1. compute repeller value
   psi_obs(i) = phirobot + Theta_obs(i);
   % 2.2 compute magnitude of repulsion
   if d(i) < TOO_FAR
       lambda_obs(i) = beta1 * exp( -d(i)/beta2 );
   else
       lambda_obs(i) = 0;
   end
   
   %2.3. Compute range of repulsion
   sigma(i) = atan( tan(delta_theta/2) + Rrobot / (Rrobot + d(i)) );
   % 2.4. Compute f_obs_i
   fobs(i) = lambda_obs(i) * (-Theta_obs(i)) * exp( - Theta_obs(i)^2 / (2 * sigma(i)^2 ));
   Fobs = Fobs + fobs(i); % get all contributions
   end
   
   %% 4. compute stochastic force, stoch
   fstoch = sqrt(Q)* randn(1,1);
   
   %% 5. Compute resultante vector field
   f_total = Fobs + fstoch;
   
   %% 6. Compute angular velocity
   wrobot = f_total;
   
   %% 7. Set linear velocity
   vrobot = 20; % cm/s
   
   %% 8. Stop Criterion
   
   %% view dynamics
   % visualization of the dynamics (target acquisition)
   phi_plot = (0:10:360)*pi/180;
   lphi = length(phi_plot);
   fstoch_plot = sqrt(Q) * randn(lphi, 1);
   f = figure(1);
   f.Name = 'Obstacle Avoidance dynamics';
   f.ToolBar = 'none'; f.MenuBar = 'figure';
   clf;
   hold on
   fobs_plot_all = 0;
   for j = 1:N
       % plot
       fobs_plot = lambda_obs(j) .* (phi_plot - psi_obs(j)) .* ...
           exp(- (phi_plot - psi_obs(j)).^2/(2 * sigma(j) ^2));
       p = plot(phi_plot * 180/pi, fobs_plot);
       p.LineWidth = 2; 
       legStr{j} = ["$f_{obs, " + num2str(j) + "}$"];
       % accumulate
       fobs_plot_all = fobs_plot_all + fobs_plot;
   end
   legStr{N+1} = ["$f_{obs,all}$"];
   p = plot(phi_plot * 180/pi, fobs_plot_all);
   p(1).LineWidth = 3; 
   p(1).Color = 'k'; 
   % axes customization
   ax = gca;
   yl = ax.YLim; % get current axis y-axis limits
   ax.XLim = [0, 360];
   ax.XTick = ax.XLim(1) : 45 : ax.XLim(2);
   ax.Title.String = 'Obstacle avoidance dynamics: $F_{obs} (\phi)$';
   ax.XLabel.String = 'Heading direction - $\phi (^{\circ})$';
   ax.YLabel.String = 'Magnitude'; 
   ax.Title.Interpreter = 'latex';
   ax.YLabel.Interpreter = 'latex';
   ax.XLabel.Interpreter = 'latex';
   ax.Title.FontSize = 14;
   ax.YLabel.FontSize = 14;
   % Line 
   phi_robot_plot = phirobot;
   if(phirobot < 0)
       phi_robot_plot = phirobot + 2*pi;
   end
   line([ phi_robot_plot * 180/pi, phi_robot_plot * 180/pi], [yl(1), yl(2)]);    
   % Legend
   lgd = legend(legStr);
   lgd.Location = 'southeast';
   lgd.Interpreter = 'latex';
   lgd.FontSize = 10;
   hold off
   %%------------- END OF YOUR CODE ------------- 
   % set robot angular velocity (rad/s) and robot linear velocity (cm/s) 
   vehicle.set_velocity(wrobot, vrobot);  
   %-------------------------------------------------------------------------------
end
vehicle.terminate();
    
    