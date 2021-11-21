#include <pthread.h>
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start)(void*), void *arg);

#include <pthread.h>
void pthread_exit(void *retval);

#include <pthread.h>
int pthread_join(pthread_t thread , void ** retval);

#include <pthread.h>
int pthread_detach(pthread_t thread);
