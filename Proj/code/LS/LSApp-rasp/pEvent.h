/**
 * @file pEvent.h
 * @author Jose Pires
 * @date 2022-02-02
 *
 * @brief Pthread event: Provides an abstraction over the pthread condition variables synchronization mechanism
 *
 * 
 */

#ifndef _SYNCOBJECT_H_
#define _SYNCOBJECT_H_

#include <pthread.h>

class pEvent
{
private:

    bool signalled;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

public:

    pEvent();
    ~pEvent();
    void WaitForSignal();
    void Signal();
};

#endif // _SYNCOBJECT_H__H
