%% IMPORTANT: 
% Before running this script, open the scenario in VREP, e.g
% Do not run simulation!
%
%% Last change: Estela Bicho Erlhagen, 18/11/2020
 
 
% Try to connect to simulator and initialize robot class:
vehicle = RobDyn_robot();
 
%get time step, dt, value (normally dt=50ms):
timestep = vehicle.get_simulation_timestep();  
 
%Get robot physical characteristics:
[Rrobot,Theta_obs] = vehicle.get_RobotCharacteristics();
%Rrobot - robot radius (in cm)
%Theta_obs - Vector with angular position of each sensor i (i = 1, . . . , 11) relative to the
%frontal direction (in rad)
 
%------------------------------------------------------------------------------
%for future
%param = dyn_tar_parameters(timestep,Rrobot,theta_obs);
%param = dyn_obs_parameters(timestep,Rrobot,theta_obs);
%param = dyn_obstar_parameters(timestep,Rrobot,theta_obs);
%------------------------------------------------------------------------------
 
% Set initial velocity vrobot = 0 (linear velocity) and wrobot = 0 (angular velocity)
% and get robot's inicial pose
wrobot = 0.01; %rad/s
vrobot = 10; %cm/s
[xrobot, yrobot, phirobot] = vehicle.set_velocity(wrobot, vrobot); 
N=11;
% Define the (first) Target
ntarget=1; %initialize first target 
%ntarget = 2; %For the U scenario
 
 
 
%%%---------------------- Start Robot Motion Behavior -------------------
%%%-----------------------------------------------------------------------
while ntarget<=vehicle.TARGET_Number % until robot goes to target ntarget
 
   %% Robot interface
   % set and get information to/from vrep
   % avoid do processing in between ensure_all_data and trigger_simulation
   vehicle.ensure_all_data();
 
   % Get vehicle's pose:
   [xrobot, yrobot, phirobot] = vehicle.get_vehicle_pose();
   %position (xrobot,yrobot) in cm
   % phirobot in rad
 
   %Sensorial information: get distance from obstacles (11 infrared obstacles - distance between
   %0-80cm):
   [d] = vehicle.get_DistanceSensorAquisition();  %distance in cm
 
   %Get target position for selected Target (Target 1 or 2 ):
   [XTARGET,YTARGET] = vehicle.get_TargetPosition(ntarget); 
  %XTARGET=0;
  %YTARGET=0;
   %position (XTARGET,YTARGET) in cm
 
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
   %% 1. set parameteres values
   dt=timestep;
   Tau_tar=20*dt;
   lamda_tar=1/Tau_tar;
 
   TOO_FAR=80;
   Tau_obs_min = 0.5*dt;
   beta1=1/Tau_obs_min;
   beta2=50;
   Dtheta=Theta_obs(2)-Theta_obs(1);
   Q=0;
   vrobot_max=30;
 
   tau_v = 5*Tau_tar;
   lambda_v = - 1/tau_v;
   tau_vdes = 200*tau_v; %1500 * tau_tar;
   Rtar = 20; % target radius
   d_min = Rrobot + Rtar + 5; % minimum distance to target
 
   %% 1.2 create vectors for psi_obs, lambda_obs, sigma
   psi_obs=zeros(N,1);
   Lambda_obs=zeros(N,1);
   Sigma=zeros(N,1);
   fobs=zeros(N,1);
   legStr=zeros(N,1);
 
   %% 2. Compute psi_tar
   psi_tar=atan2((YTARGET-yrobot),(XTARGET-xrobot));

   %% 3. Compute ftar
 
   ftar=-lamda_tar*sin(phirobot-psi_tar); %%nonlinear
   %ftar=-lamda_tar*(phirobot-psi_tar);   %%linear

   %% 3. Compute Fobs
   Fobs=0;
   for i=1:N
 
   %2.1 compute repeller value
   psi_obs(i)=phirobot+Theta_obs(i);
 
   %2.2 compute magnitude os repulsion
   if(d(i) < TOO_FAR)
       Lambda_obs(i)=beta1*exp(-d(i)/beta2);
   else
       Lambda_obs(i)=0;
   end
 
   %2.3 compute range of repulsion
 
   Sigma(i)= atan(tan(Dtheta/2)+Rrobot/(Rrobot+d(i)));
 
   %2.4 compute f_obs_i
 
  % fobs(i)= Lambda_obs(i)*(phirobot-psi_obs(i))*exp(-((phirobot-psi_obs(i))^2/(2*sigma(i)^2)));
   fobs(i)=Lambda_obs(i)*(-Theta_obs(i))*exp(-Theta_obs(i)^2/(2*Sigma(i)^2));
 
      Fobs=Fobs+fobs(i); 
   end
 
 
 
   %% 7. Set linear velocity
   dist_tar = sqrt( (YTARGET - yrobot)^2 + (XTARGET - xrobot)^2 );
   %  v_des = k_v * dist_tar; % linear
   if(dist_tar < d_min)
       v_des = 0;
   else
       v_des = vrobot_max * (1 - exp(- (dist_tar - d_min) / tau_vdes) );
   end
 
   g_v = lambda_v * (vrobot - v_des);
   vrobot = vrobot + dt * g_v; % cm/s
 
     %% Complete vector field
     Ftotal=Fobs+ftar;
     wrobot=Ftotal;
 
 
   %% view dynamics
   % visualization of the dynamics 
   phi_plot = (0:10:360)*pi/180;
   lphi = length(phi_plot);
   f = figure(1);
   %f = figure(1);
   f.Name = 'Obstacle Avoidance dynamics';
   f.ToolBar = 'none'; f.MenuBar = 'figure';
   clf;
   grid('on');
   hold on
   % for Obstacle Avoidance dynamics
   fobs_plot_all = 0;
   legStr = {'fobs';'ftar';'fobs & ftar'};
   for j = 1:N
       % plot
       fobs_plot = Lambda_obs(j) .* (phi_plot - psi_obs(j)) .* ...
           exp(- (phi_plot - psi_obs(j)).^2/(2 * Sigma(j) ^2));
      % accumulate
       fobs_plot_all = fobs_plot_all + fobs_plot;
   end
    p = plot(phi_plot * 180/pi, fobs_plot_all);
    phi_plot=(0:10:360)*pi/180;
    lphi=length(phi_plot);
    % for Target Acquisition dynamics
    ftar_plot=-lamda_tar*sin(phi_plot -psi_tar);
    % for system dynamics
    f_total_plot=ftar_plot+fobs_plot_all;
    %plots
    plot(phi_plot*180/pi,ftar_plot);
    plot(phi_plot*180/pi,f_total_plot);
    
    if(phirobot<0)
    line([(phirobot+2*pi)*180/pi,(phirobot+2*pi)*180/pi],[-1,1]);
    else
    line([phirobot*180/pi,phirobot*180/pi],[-1,1]);
    end
   ax = gca;
   yl = ax.YLim; % get current axis y-axis limits
   ax.XLim = [0, 360];
   ax.XTick = ax.XLim(1) : 45 : ax.XLim(2);
   ax.Title.String = 'Behavioral dynamics';
   ax.XLabel.String = 'Heading direction';
   ax.YLabel.String = 'Magnitude'; 
   ax.Title.Interpreter = 'latex';
   ax.YLabel.Interpreter = 'latex';
   ax.XLabel.Interpreter = 'latex';
   ax.Title.FontSize = 14;
   ax.YLabel.FontSize = 14;
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
    
    