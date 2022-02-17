/**
 * @file msgqueue.cpp
 * @author Jose Pires
 * @date 2022-02-06
 *
 * @brief Implementation class for Message queue
 *
 */

#include "msgqueue.h"

msgQueue::msgQueue(std::string path, int size){
    _path = path;
    _sz = size;
    _buff = new char[size];
    _fd = -1;
}
msgQueue::~msgQueue(){
    mq_close(_fd);
    mq_unlink(_path.c_str());
    delete [] _buff;
}
 
/**< Non blocking */  
//bool msgQueue::Open(){
//    _fd = mq_open(_path.c_str(), O_RDWR | O_NONBLOCK);
//    if(_fd == (mqd_t)-1) {
//        mq_close(_fd);
//        return false;
//    }
//
//    return true;
//}
//
//int msgQueue::Receive(){
//
//    if(_fd < 0)
//        return _fd;
//    
//    if(mq_receive(_fd, _buff, _sz, NULL) == -1) {
//            //get error from errno
//        int err = errno;
//        //is the queue empty?
//        if(err == EAGAIN)
//            return err; //no more to read
//
//        //perror("In mq_receive()");
//        //mq_close(_fd);
//        //exit(1); 
//    }
//
//    /**< Return char read */
//    return _buff[0];
//} 

/**< Blocking */

bool msgQueue::Open(){
    _fd = mq_open(_path.c_str(), O_RDWR);
    if(_fd == (mqd_t)-1) {
        mq_close(_fd);
        return false;
    }

    return true;
}
int msgQueue::Receive(){

    #define FD_INVALID -1
    #define READ_ERROR -2

    if(_fd < 0)
        return FD_INVALID;
    
    if(mq_receive(_fd, _buff, _sz, NULL) == -1) {
            //get error from errno
        //int err = errno;
        ////is the queue empty?
        //if(err == EAGAIN)

        return READ_ERROR;
        //return errno; //no more to read

        //perror("In mq_receive()");
        //mq_close(_fd);
        //exit(1); 
    }

    /**< Return char read */
    return _buff[0];
}
