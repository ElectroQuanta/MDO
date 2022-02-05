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
#include "../sensors.h"
#include <iostream>

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



int main(int argc, char *argv[]){
	pid_t pid, sid;
	int len, fd;
	Sensor s(17, 22, 1000), s2(17, 23, 1000);
	
	if(!s2.Open() || !s.Open())
        return -1;

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

	while (1) {
		//char *buf = malloc(sizeof(char) + len + 1);
		std::stringstream buffer;
		#define BUF_LEN 64;
		char buf[BUF_LEN];

		if (buf == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if ((fd = open("/var/log/example3.log",	O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		for(int i = 0; i < 10; i++) {
        buffer << s.Read() <<"," << s2.Read() << std::endl;
	    }
		strncpy(buf, buffer.c_str() , BUF_LEN);
		write(fd, buf, BUF_LEN);
		close(fd);
		sleep(5);
	}
exit(EXIT_SUCCESS);		
}
