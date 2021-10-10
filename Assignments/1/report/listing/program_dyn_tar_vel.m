%%----------- BEGIN YOUR CODE HERE ----------- %
%% 1. set parameter values
dt = timestep;
% phi
tau_tar = 10 * dt;
lambda_tar = 1/tau_tar;
% velocities
tau_v = 5*tau_tar;
lambda_v = - 1/tau_v;
Q = 0.01; % factor of stochastic force
          %k_v = 1/5; 
vrobot_max = 80; % cm/s
tau_vdes = 150*tau_v; %1500 * tau_tar;
Rtar = 20; % target radius
d_min = Rrobot + Rtar + 5; % minimum distance to target

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
dist_tar = sqrt( (YTARGET - yrobot)^2 + (XTARGET - xrobot)^2 )
if(dist_tar < d_min)
    v_des = 0;
else
    %v_des = k_v * abs( (dist_tar - d_min) ) % linear
    v_des = vrobot_max * (1 - exp(- (dist_tar - d_min) / tau_vdes) )
end

g_v = lambda_v * (vrobot - v_des)
vrobot = vrobot + dt * g_v; % cm/s

%Linear threshold
%if(vrobot > vrobot_max)
%    vrobot = vrobot_max;
%end

%% 8. Stop Criterion

%%% view dynamics
%% visualization of the dynamics (target acquisition)
phi_plot = (0:10:360)*pi/180;
lphi = length(phi_plot);
ftar_plot = -lambda_tar * sin(phi_plot - psi_tar);
fstoch_plot = sqrt(Q) * randn(lphi, 1);
ftotal_plot = ftar_plot; %+ fstoch_plot;
                         % figure customization
f = figure(1);
f.Name = 'Target Acquisition dynamics';
f.ToolBar = 'none'; f.MenuBar = 'figure';
clf;
% plot
p = plot(phi_plot * 180/pi, ftotal_plot, phi_plot * 180/pi, ftar_plot, ...
         phi_plot * 180/pi, fstoch_plot);
p(1).LineWidth = 2; p(1).LineStyle = '--';
% axes customization
ax = gca;
yl = ax.YLim; % get current axis y-axis limits
ax.XLim(2) = 360;
ax.XTick = ax.XLim(1) : 45 : ax.XLim(2);
ax.Title.String = 'Target Acquisition dynamics';
ax.XLabel.Interpreter = 'latex';
ax.XLabel.String = 'Heading direction - $\phi \quad (^{\circ}$)';
ax.YLabel.String = 'Magnitude'; 
hold on
% line customization
phi_robot_plot = phirobot;
if(phirobot < 0)
    phi_robot_plot = phirobot + 2*pi;
end
l = line([ phi_robot_plot * 180/pi, phi_robot_plot * 180/pi], [yl(1), yl(2)]);    
l.Color = 'black';
% legend customization
lgd = legend('Total', 'Target', 'Stochastic');
lgd.Location = 'southeast';
hold off

%% V_des(d)
f = figure(2);
f.Name = 'V_des(d)';
f.ToolBar = 'none'; f.MenuBar = 'figure';
clf;
%
ax = gca;
ax.YLim = [0, vrobot_max + 20];
ax.XLim = [0, 600];
yl = ax.YLim; % get current axis y-axis limits
xl = ax.XLim; % get current axis y-axis limits
hold on

d = d_min:0.1:600;
vdes_plot = vrobot_max .* (1 - exp(- (d - d_min) / tau_vdes) );
p = plot(d, vdes_plot, 'LineWidth', 2, 'LineStyle', '-');
l = line([dist_tar, dist_tar], [yl(1), yl(2)]);    
l.Color = 'black';
l = line([xl(1), xl(2)], [v_des, v_des]);    
l.Color = 'black';
ax.Title.String = '$V_{des} (d) $';
ax.Title.FontSize = 14;
ax.Title.Interpreter = 'latex';
ax.XLabel.String = 'Distance to target (cm/s)';
ax.YLabel.String = '$V_{des} (cm/s) $';
ax.YLabel.Interpreter = 'latex';
ax.YLabel.FontSize = 14;
hold off

%% g(v)
f = figure(3);
f.Name = 'g(v)';
f.ToolBar = 'none'; f.MenuBar = 'figure';
clf;
hold on

vrobot_plot = 0:0.1:vrobot_max;
g_v_plot = lambda_v * (vrobot_plot - v_des);
p = plot(vrobot_plot, g_v_plot, 'LineWidth', 2, 'LineStyle', '-');

ax = gca;
yl = ax.YLim; % get current axis y-axis limits
xl = ax.XLim; % get current axis y-axis limits
l = line([vrobot, vrobot], [yl(1), yl(2)]);    
l.Color = 'black';
l = line([xl(1), xl(2)], [0, 0]);    
l.LineStyle = '--';
l.Color = 'black';
ax.Title.String = 'Linear velocity dynamics: g(v)';
ax.Title.FontSize = 12;
ax.XLabel.String = 'Velocity (cm/s)';
ax.YLabel.String = 'Magnitude';
hold off
%%------------- END OF YOUR CODE ------------- 

% set robot angular velocity (rad/s) and robot linear velocity (cm/s) 
vehicle.set_velocity(wrobot, vrobot);  
%-------------------------------------------------------------------------------