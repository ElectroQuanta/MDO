
void MainWindow::onCheckModeTimerElapsed(){
#define PERIODIC_LIMIT_MS ((int)3600000)    
#define CNT_RELOAD ((int)( PERIODIC_LIMIT_MS / MODE_PERIOD_MS ) )
    static int cnt = CNT_RELOAD; /**< define ratio between normal and interaction mode checks: interaction mode is checked cnt times more than normal */
    AppMode_t mode;
    cnt--;
    Ad ad;
    if (!cnt) {
      /**< Update reload */
      cnt = CNT_RELOAD;
      /**< Check Normal Mode */
      /* If current Ad timeslot == time timeslot */
      if(curAd.timeslot() == _timeslot)
          onNormalMode_pressed();
    } else {
      /**< Check Interaction mode */
      mode = _appmode;
      /**< If User detected on Welcome or Normal modes */
      if (detectUser()) {
        if ((mode == AppMode::WELCOME) || (mode == AppMode::NORMAL))  {
            updateStatusBar("User detected");
            onInter_mode_pressed();
          }
      } else{
          curAd(ad);
              if( ad.enabled() )
                  onNormalMode_pressed();
              else
                  onHome_pressed();
      }
      /**< Check Remote connection */
      if (!_remoteConnected)
        connectToRemote();
      else {
        const QString str = "Hello from LS";
        _remoteConnected = true;
        _remoteSock->write(str.toLocal8Bit());
        std::cout << "Write: " << str.toStdString() << std::endl;
      }
    }
}
