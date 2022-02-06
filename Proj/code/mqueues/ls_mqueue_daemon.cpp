/**
 * @file ls_mqueue_daemon.cpp
 * @author Jose Pires
 * @date 2022-02-06
 *
 * @brief This program must be runned first to create the message queues
 *
 * detailed
 */

#include <cstring>
#include <iostream>
#include <mqueue.h>
#include <pthread.h>
#include <unistd.h>

#define MSGQ_PATH "/distance"
#define MAX_MSG_LEN 64
#define MAX_MSGS 64

mqd_t msgq_path;

void create_mqueues() {
  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_MSG_LEN;
  attr.mq_curmsgs = 0;

  mq_unlink(MSGQ_PATH);

  msgq_path = mq_open(MSGQ_PATH, O_RDWR | O_CREAT | O_NONBLOCK,
                      S_IRWXU | S_IRWXG, &attr);

  if (msgq_path == (mqd_t)-1) {
      perror("In mq_open()");
    mq_close(msgq_path);
    exit(1);
  }

  std::cout << "msgq_path " << msgq_path << std::endl;
}

void receive_msgq() {
  char buffer[MAX_MSG_LEN];
  while (1) {
    if (mq_receive(msgq_path, buffer, MAX_MSG_LEN, NULL) == -1) {
      // get error from errno
      int err = errno;
      // is the queue empty?
      if (err == EAGAIN)
        continue; // no more to read
      perror("In mq_receive()");
      mq_close(msgq_path);
      exit(1);
    }
    std::string buf(buffer);
    std::cout << buffer << std::endl;
  }
}

int main() {
  create_mqueues();

  //char message[] = "Hello CRLH!!!\0";
  /* sending the message      --  mq_send() */

  char c;
  int i = 0;
  int aux = 0;
  #define MAX_ITER 120
  
  while (1) {

    i++;
    aux = ((i % MAX_ITER) > ((MAX_ITER/2) - 1));
    c = aux + '0';
    std::cout << c << std::endl;
    if (mq_send(msgq_path, &c, 2, 1) == -1)
        perror("send error: ");
//        std::cout << "ERROR!!" << std::endl;
    // receive_msgq();
    sleep(1);
  }

  return 0;
}
