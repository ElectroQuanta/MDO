#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#define MSG_SIZE       256

// This handler will be called when the queue 
// becomes non-empty.

void handler (int sig_num) {
    printf ("Received sig %d.\n", sig_num);
}
    
void main () {

  struct mq_attr attr, old_attr;   // To store queue attributes
  struct sigevent sigevent;        // For notification
  mqd_t mqdes, mqdes2;             // Message queue descriptors
  char buf[MSG_SIZE];              // A good-sized buffer
  unsigned int prio;               // Priority 
    
  // First we need to set up the attribute structure
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MSG_SIZE;
  attr.mq_flags = 0;
  attr.mq_curmsgs = 0;

  // Open a queue with the attribute structure
  mqdes = mq_open ("/sideshowbob", O_RDWR | O_CREAT, 
                   0664, &attr);

  // Now open a queue with the default attribute structure
  mqdes2 = mq_open ("troy-mcclure", O_RDWR | O_CREAT, 
                    0664, 0);
    
  // This will now be a temporary queue...as soon as it's closed,
  // it will be removed
  mq_unlink ("troy-mcclure");
  printf("%d\n", mqdes);
  // Get the attributes for Sideshow Bob
  mq_getattr (mqdes, &attr);
  printf ("%d messages are currently on the queue.\n", 
          attr.mq_curmsgs);

  if (attr.mq_curmsgs != 0) {
    
    // First set the queue to not block any calls     
    attr.mq_flags = O_NONBLOCK;
    mq_setattr (mqdes, &attr, &old_attr);    
        
    // Now eat all of the messages
    printf("Success 1\n");
    while (mq_receive (mqdes, &buf[0], MSG_SIZE, &prio) != -1) 
      printf ("Received a message with priority %d.\n", prio);
    printf("Success 2\n");        
    // The call failed.  Make sure errno is EAGAIN
    if (errno != EAGAIN) { 
      perror ("mq_receive()");
      _exit (EXIT_FAILURE);
    }
    printf("Success 3\n");    
    // Now restore the attributes
    mq_setattr (mqdes, &old_attr, 0);            
  }
    
  // We want to be notified when something is there 
  signal (SIGUSR1, handler);
  sigevent.sigev_signo = SIGUSR1;
    
  if (mq_notify (mqdes, &sigevent) == -1) {
    if (errno == EBUSY) 
      printf (
        "Another process has registered for notification.\n");
    _exit (EXIT_FAILURE);
  }
  #define MQ_PRIO_MAX 4096
  for (prio = 0; prio <= MQ_PRIO_MAX; prio += 8) {
    printf ("Writing a message with priority %d.\n", prio);    
    if (mq_send (mqdes, "I8-)", 4, prio) == -1)
      perror ("mq_send()");
  }

  // Close all open message queue descriptors    
  mq_close (mqdes);
  mq_close (mqdes2);

}
/*
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <iostream>

#define QUEUE_NAME "/example"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main() {
    mqd_t qdes;

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if(qdes = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr) == -1) {
        perror("Error on mq_open(1st)");
        exit (1);
    }
    char in_buffer[MSG_BUFFER_SIZE];

    while(1) {
        if(mq_receive(qdes, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror("Error on mq_receive(1st)");
            exit (1);
        }

        std::cout << in_buffer << std::endl;
    }
}
*/