#include "ultrassonicsensor.h"
#include <fcntl.h>
#include <iostream>
#include <mqueue.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

using namespace DeviceDriver;

void signal_handler(int sig) {
  switch (sig) {
  case SIGHUP:
    syslog(LOG_INFO, "Hangup signal catched");
    break;
  case SIGTERM:
    syslog(LOG_INFO, "Terminate signal catched");
    exit(0);
    break;
  }
}

#define MSGQ_PATH "/distance"
#define MAX_MSG_LEN 64

mqd_t create_mqueues() {
  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = 1;
  attr.mq_msgsize = MAX_MSG_LEN;
  attr.mq_curmsgs = 0;

  mqd_t msgq_path = mq_open(MSGQ_PATH, O_RDWR | O_CREAT | O_NONBLOCK,
                            S_IRWXU | S_IRWXG, &attr);

  if (msgq_path == (mqd_t)-1) {
    std::cerr << "In mq_open()" << std::endl;
    mq_close(msgq_path);
    exit(1);
  }

  return msgq_path;
}

bool checkDistance(int dist) {
#define MIN_TH 2
#define MAX_TH 30
  return (dist > MIN_TH && dist < MAX_TH);
}

int main(int argc, char *argv[]) {
  pid_t pid, sid;
  int len, fd;
  time_t timebuf;

  pid = fork(); // create a new process

  if (pid < 0) { // on error exit
    syslog(LOG_ERR, "%s\n", "fork");
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    printf("Deamon PID: %d\n", pid);
    exit(EXIT_SUCCESS); // parent process (exit)
  }
  sid = setsid(); // create a new session

  if (sid < 0) { // on error exit
    syslog(LOG_ERR, "%s\n", "setsid");
    exit(EXIT_FAILURE);
  }
  // make '/' the root directory
  if (chdir("/") < 0) { // on error exit
    syslog(LOG_ERR, "%s\n", "chdir");
    exit(EXIT_FAILURE);
  }
  umask(0);
  close(STDIN_FILENO);  // close standard input file descriptor
  close(STDOUT_FILENO); // close standard output file descriptor
  close(STDERR_FILENO); // close standard error file descriptor

  signal(SIGHUP, signal_handler);  /* catch hangup signal */
  signal(SIGTERM, signal_handler); /* catch kill signal */

#define TIMEOUT_S 1
#define ITER 8
#define S1_ECHO 22
#define S2_ECHO 23
#define S_TRIG 17
#define S_TIMEOUT 1000
#define LOGFILE "/var/log/distance.log"
  int _delay = 1000 / ITER;

  /**< Instantiaion sensors */
  UltrassonicSensor s1(S_TRIG, S1_ECHO, S_TIMEOUT);
  UltrassonicSensor s2(S_TRIG, S2_ECHO, S_TIMEOUT);
  /**< Open them */
  if (!s2.Open() || !s1.Open()) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  /**< Unlink the message queue if it already created */
  mq_unlink(MSGQ_PATH);
  /**< Create msg queues */
  mqd_t msgq_path = create_mqueues();
  /**< Perform sliding window on both sensors readings */
  while (1) {
    int count = 0;
    for (int j = 0; j < ITER * TIMEOUT_S; j++) {
      count = count + (checkDistance(s1.Read()) & checkDistance(s2.Read()));
      usleep(_delay * 1000);
    }
    char c = (count > (TIMEOUT_S * ITER / 2)) ? '1' : '0';
    /**< Flush the result to the associated message queue */
    mq_send(msgq_path, &c, 2, 1);
  }
  exit(EXIT_SUCCESS);
}
