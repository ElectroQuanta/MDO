#include <mqueue.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

#define MSGQ_PATH "/zekinha"
    #define MAX_MSG_LEN 64

mqd_t msgq_path;

void create_mqueues() {
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = MAX_MSG_LEN;
    attr.mq_curmsgs = 0;

    msgq_path = mq_open(MSGQ_PATH, O_RDWR | O_CREAT | O_NONBLOCK, S_IRWXU | S_IRWXG, &attr);

    if (msgq_path == (mqd_t)-1) {
        perr("In mq_open()");
        mq_close(msgq_path);
        exit(1);
    }

    std::cout << "msgq_path " << msgq_path << std::endl;

}

int main() {
    create_mqueues();

    char message[] = "Hello CRLH!!!\0";
    /* sending the message      --  mq_send() */
    while(1) {
        if(mq_send(msgq_path, &message[0], strlen(message)+1, 1) == -1)
        perr("In mq_send()");
        sleep(1);
    }

    return 0;
}