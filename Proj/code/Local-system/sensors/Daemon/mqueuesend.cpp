#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

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
        
    // First we need to set up the attribute structure
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    if(mqdes = mq_open(QUEUE_NAME, O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &attr) == -1) {
        perror("Error on mq_open()");
        exit (1);
    }

    // Get the attributes
    mq_getattr (mqdes, &attr);

    // First set the queue to not block any calls     
    attr.mq_flags = O_NONBLOCK;
    mq_setattr (mqdes, &attr, &old_attr);

    

   // Now restore the attributes
    mq_setattr (mqdes, &old_attr, 0);
    
    #define MQ_PRIO_MAX 80
    for (prio = 0; prio <= MQ_PRIO_MAX; prio += 8) {
        printf ("Writing a message with priority %d.\n", prio);    
        if (mq_send (mqdes, "I8-)", 4, prio) == -1)
            perror ("mq_send()");
    }

    // Close all open message queue descriptors    
    mq_close (mqdes);
}