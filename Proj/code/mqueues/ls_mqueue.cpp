#include <mqueue.h>
#include <iostream>
#include <cstring>

#define MSGQ_PATH "/zekinha"
    #define MAX_MSG_LEN 64

void create_mqueues() {
    char buffer[MAX_MSG_LEN];

    mqd_t msgq = mq_open(MSGQ_PATH, O_RDWR | O_NONBLOCK);
    if(msgq == (mqd_t)-1) {
        perror("In mq_open()");
        mq_close(msgq);
        exit(1);
    }

    while(1) {
        if(mq_receive(msgq, buffer, MAX_MSG_LEN, NULL) == -1) {
            //get error from errno
            int err = errno;
            //is the queue empty?
            if(err == EAGAIN)
                continue; //no more to read
            perror("In mq_receive()");
            mq_close(msgq);
            exit(1); 
        }
        std::cout << buffer[0] << std::endl;
    }
}

int main() {
    create_mqueues();
}
