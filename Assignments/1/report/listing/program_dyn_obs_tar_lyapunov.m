   %%----------- BEGIN YOUR CODE HERE ----------- %
  %% 1. set parameter values
   dt = timestep;
   % hierarchy of relaxation rates
   % lambda_tar << c_v_tar
   % lambda_obs << c_v_obs
   % lambda_tar << lambda_obs
   
   TOO_FAR = 75; % defines a radius for repulsive forces (cm)
   N = 11; % nr of sensors
   beta2 = 20; % flexible
   delta_theta = Theta_obs(2) - Theta_obs(1);
   Q = 0.05; % pre-factor of stochastic force, Q
   % obstacle
   tau_obs_min = 3.5 * dt; % flexible
   beta1 = 1/tau_obs_min; %  = lambda_obs_max = 1/tau_obs_min
   % target
   tau_tar = 20*tau_obs_min; % relaxation time for attractor
   lambda_tar = 1/tau_tar; % attraction magnitude
   % accumulators
   Fobs = 0; % accumulator for obstacle force
   Upot = 0; % accumulator for Lyapunov´s function
   % Lyapunov
   Rtar = 20; % target radius
   d_min = Rrobot + Rtar + 5; % minimum distance to target
   C = 100; % potential constant
   d_obs = d_min; % minimum distance to obstacle
   d_tar = d_min; % minimum distance to target
   psi_max = pi/12; % maximum rate of fixed points shift
   sigma_v = pi/6; % angular range for velocity
   % velocity
   c_v_obs = 10 * beta1; % obstacle contribution to velocity
   c_v_tar = 100 * lambda_tar; % target contribution to velocity
   Vobs = d_obs * psi_max; % maximum velocity for obstacle avoidance behavior
   Vtar = d_tar * psi_max; % maximum velocity for target acquisition behavior

   %% 2. for each sector compute the contribution of the repulsive forcelet
   for i=1:N
       lambda_obs(i) = 0;
       % 2.1. compute repeller value
       psi_obs(i) = phirobot + Theta_obs(i);
       % 2.2 compute magnitude of repulsion
       if d(i) < TOO_FAR
           lambda_obs(i) = beta1 * exp( -d(i)/beta2 );
       end
       %2.3. Compute range of repulsion
       sigma(i) = atan( tan(delta_theta/2) + Rrobot / (Rrobot + d(i)) );
       % 2.4. Compute f_obs_i
       aux = lambda_obs(i) * exp( - Theta_obs(i)^2 / (2 * sigma(i)^2 ));
       fobs(i) = aux * (-Theta_obs(i));
       % 2.5. Compute Lyapunov Function
       k_i = lambda_obs(i) * sigma(i)^2 / sqrt(exp(1));
       upot(i) = aux * sigma(i)^2 - k_i;
       % 2.6. Compute all obstacles contributions
       Upot = Upot + upot(i);
       Fobs = Fobs + fobs(i);
   end
   %% 3. compute psi_tar
   psi_tar = atan2(YTARGET - yrobot, XTARGET - xrobot);
   %% 4. compute ftar
   ftar = -lambda_tar * sin(phirobot - psi_tar);
   %% 5. compute stochastic force, stoch
   fstoch = sqrt(Q)* randn(1,1);
   %% 6. Compute resultante vector field for planning dynamics
   f_total = Fobs + ftar + fstoch;
   %% 7. Compute angular velocity
   wrobot = f_total;
   %% Compute linear velocity vector field
   % 8. Compute range of repulsion created by an obstacle
   alpha = atan(C * Upot)/pi;
   % compute velocity contributions
   c_obs = c_v_obs * (1/2 + alpha);
   c_tar = c_v_tar * (1/2 - alpha);
   cv1 = -c_obs *( vrobot - Vobs) * exp(- (vrobot - Vobs)^2/(2*sigma_v ^2) );
   cv2 = -c_tar *( vrobot - Vtar) * exp(- (vrobot - Vtar)^2/(2*sigma_v ^2) ); 
   % compute dynamic field
   g_v = cv1 + cv2;
   %% 9. Set linear velocity
   if( alpha ) % if Thresholded potential is triggered
       vrobot = vrobot + dt * g_v; % cm/s
   else % run at a constant speed
       vrobot = 30;
   end
   %% 10. Stop Criterion
   
   %% view dynamics
   % visualization of the dynamics 
   phi_plot = (0:10:360)*pi/180;
   lphi = length(phi_plot);
   % figure customization
   f = figure(1);
   f.Name = 'Obstacle Avoidance dynamics';
   f.ToolBar = 'none'; f.MenuBar = 'figure';
   clf;
   hold on
   % for Obstacle Avoidance dynamics
   fobs_plot_all = 0;
   upot_plot_all = 0;
   for j = 1:N
       % 2.4. Compute f_obs_i
       aux = lambda_obs(j) .* exp(- (phi_plot - psi_obs(j)).^2/(2 * sigma(j) ^2));
       fobs_plot = aux .* (phi_plot - psi_obs(j));
       % 2.5. Compute Lyapunov Function
       k_i = lambda_obs(j) .* sigma(j)^2 / sqrt(exp(1));
       upot_plot = aux .* sigma(j)^2 - k_i;
      % accumulate
       fobs_plot_all = fobs_plot_all + fobs_plot;
       upot_plot_all = upot_plot_all + upot_plot;
   end
   ftar_plot=-lambda_tar*sin(phi_plot -psi_tar); % target
   f_total_plot=ftar_plot+fobs_plot_all; % overall
   alpha_plot = atan(C * upot_plot_all)/pi; % thresholded potential
   %plots
   legStr = {'$f_{obs}$';'$f_{tar}$';'$f_{obs} + f_{tar}$';'$U(\phi)$'; '$\alpha(\phi)$'};
   p = plot(phi_plot * 180/pi, fobs_plot_all);
   p.LineWidth = 2; p.LineStyle = '--';
   p = plot(phi_plot*180/pi,ftar_plot);
   p.LineWidth = 2; p.LineStyle = '--';
   p = plot(phi_plot*180/pi,f_total_plot);
   p.LineWidth = 3;
   p = plot(phi_plot*180/pi,upot_plot_all);
   p.LineWidth = 2;
   p = plot(phi_plot*180/pi,alpha_plot);
   p.LineWidth = 3;
   % axis
   ax = gca; yl = ax.YLim; ax.XLim = [0, 360];
   ax.XTick = ax.XLim(1) : 45 : ax.XLim(2);
   ax.Title.String = 'Behavioral dynamics';
   ax.XLabel.String = 'Heading direction - $\phi (^{\circ})$';
   ax.YLabel.String = 'Magnitude'; 
   ax.Title.Interpreter = 'latex';
   ax.YLabel.Interpreter = 'latex';
   ax.XLabel.Interpreter = 'latex';
   ax.Title.FontSize = 14; ax.YLabel.FontSize = 14;
   % line
   phi_robot_plot = phirobot;
   if(phirobot < 0)
       phi_robot_plot = phirobot + 2*pi;
   end
   l = line([ phi_robot_plot * 180/pi, phi_robot_plot * 180/pi], [yl(1), yl(2)]);    
   l.Color = 'black';
   % Legend
   lgd = legend(legStr);
   lgd.Location = 'southeast';
   lgd.Interpreter = 'latex';
   lgd.FontSize = 10;
   hold off
   %%------------- END OF YOUR CODE ------------- 
   % set robot angular velocity (rad/s) and robot linear velocity (cm/s) 
   vehicle.set_velocity(wrobot, vrobot);  