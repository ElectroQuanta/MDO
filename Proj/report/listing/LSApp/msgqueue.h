/**
 * @file msgqueue.h
 * @author Jose Pires
 * @date 2022-02-06
 *
 * @brief Message queue wrapper class
 */
#ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_
#include <mqueue.h>
#include <string>
class msgQueue{
private:
    mqd_t _fd; /**< Msg queue file descriptor */
    std::string _path;
    char *_buff;
    int _sz;
public:
    msgQueue(std::string path, int size);
    ~msgQueue();
    bool Open();
    int Receive();
};
#endif // _MSGQUEUE_H__H
