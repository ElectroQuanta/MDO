#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <iostream>

#define QUEUE_NAME "/TEST"
#define QUEUE_PERMISSIONS 0664
#define MAX_MESSAGES 10
#define MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

void handler (int sig_num) {
    printf ("Received sig %d.\n", sig_num);
}

int main() {
    struct mq_attr attr, old_attr;   // To store queue attributes
    struct sigevent sigevent;        // For notification
    mqd_t mqdes, mqdes2;             // Message queue descriptors
    char buf[MSG_SIZE];              // A good-sized buffer
    unsigned int prio;               // Priority 
    //mq_unlink (QUEUE_NAME);
   
   // First we need to set up the attribute structure
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Open a queue with the attribute structure
    if(mqdes = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr) == -1) {
        perror("Error on mq_open()");
        exit (1);
    }

    // Get the attributes for Sideshow Bob
    mq_getattr (mqdes, &attr);
    printf ("%d messages are currently on the queue.\n", 
          attr.mq_curmsgs);
    
    while(1) {
        if(attr.mq_curmsgs != 0) {
            // First set the queue to not block any calls 
            attr.mq_flags = O_NONBLOCK;
            mq_setattr(mqdes, &attr, &old_attr); 

            if(mq_receive(mqdes, &buf[0], MSG_SIZE, &prio) == -1) {
                perror("Error on mq_receive()");
                exit (1);
            }
            if (errno != EAGAIN) { 
                perror ("mq_receive()");
                exit (EXIT_FAILURE);
            }
            // Now restore the attributes
            mq_setattr (mqdes, &old_attr, 0);   
        }
        // We want to be notified when something is there 
        //signal (SIGUSR1, handler);
        //sigevent.sigev_signo = SIGUSR1;

        /*if (mq_notify (mqdes, &sigevent) == -1) {
            if (errno == EBUSY) 
            printf (
                "Another process has registered for notification.\n");
            exit (EXIT_FAILURE);
            }*/
    }
    // Close all open message queue descriptors    
    mq_close (mqdes);
}