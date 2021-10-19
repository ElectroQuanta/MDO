% Set initial angular and linear velocities of the robot and get its initial pose
wrobot = 0.01; %rad/s
vrobot = 0; %cm/s
[xrobot, yrobot, phirobot] = vehicle.set_velocity(wrobot, vrobot); 

   %% 1. set parameter values
   dt = timestep;
   tau_tar = 5 * dt;
   lambda_tar = 1/tau_tar;
   Q = 0.01;
   %% 7. Set linear velocity
   vrobot = 0; % cm/s