   %% 1. set parameter values
   dt = timestep;
   tau_tar = 5 * dt;
   lambda_tar = 1/tau_tar;
   Q = 0.01;
   %% 7. Set linear velocity
   vrobot = 30; % cm/s