#include  <sys/syslog.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <string>
#include <sstream>
#include "ultrassonicsensor.h"
#include <iostream>

using namespace DeviceDriver;

void signal_handler(int sig) {
	switch(sig) {
		case SIGHUP:
			syslog(LOG_INFO,"Hangup signal catched");
			break;
		case SIGTERM:
			syslog(LOG_INFO,"Terminate signal catched");
			exit(0);
			break;
	}
}

bool checkDistance(int dist) {
        #define MIN_TH 2
        #define MAX_TH 30
        return (dist > MIN_TH && dist < MAX_TH);
    }


int main(int argc, char *argv[]){
	pid_t pid, sid;
	int len, fd;
	time_t timebuf;
	
	pid = fork(); // create a new process

	if (pid < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "fork");
		exit(EXIT_FAILURE);
	}

	if (pid > 0){  
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

	signal(SIGHUP,signal_handler); /* catch hangup signal */
	signal(SIGTERM,signal_handler); /* catch kill signal */

	#define TIMEOUT_S 1
    #define ITER 8
	#define S1_ECHO 22
	#define S2_ECHO 23
	#define S_TRIG 17
	#define S_TIMEOUT 1000
	#define LOGFILE "/var/log/distance.log"
    int _delay = 1000/ITER;

	UltrassonicSensor s1(S_TRIG, S1_ECHO, S_TIMEOUT);
	UltrassonicSensor s2(S_TRIG, S2_ECHO, S_TIMEOUT);
	if(!s2.Open() || !s1.Open()) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	while (1) {
		int count = 0;
		for(int j = 0; j < ITER*TIMEOUT_S; j++) {
        	count = count + ( checkDistance(s1.Read()) & checkDistance(s2.Read()));
        	usleep(_delay*1000);
        }
		
		if ((fd = open(LOGFILE,	O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0) {
			perror("open");
			exit(EXIT_FAILURE);
		}

		char c = (count > (TIMEOUT_S*ITER/2))?'1' : '0';
		write(fd, &c, 1);
		c = '\n';
		write(fd, &c, 1);


		close(fd);
	}
exit(EXIT_SUCCESS);		
}
