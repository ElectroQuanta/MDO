pid_t pid;
// create a new process

pid = fork();
if (pid < 0) { // error trying to execute fork
	ERROR("fork failure");
	exit(EXIT_FAILURE);
}

if (pid > 0) // parent process (exit)
	exit(EXIT_SUCCESS);
// child process continues the execution
...

pid_t sid;
sid = setsid(); // create a new session
if (sid < 0) {
	ERROR("setsid failure");
	exit(EXIT_FAILURE);
}

// make '/' the root directory
if (chdir("/") < 0) {
	ERROR("chdir failure");
	exit(EXIT_FAILURE);
}

// continue executing the child process
...

// resetting umask to 0
umask(0);

// continue executing the child process
...

// close unneeded file descriptors
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

// continue executing the child process
...

#include <syslog.h>

void openlog(char *ident, int option, int facility);
void closelog(void);
void syslog(int priority, chat *format, ...);
