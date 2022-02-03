/**
 * @file pEvent.cpp
 * @author Jose Pires
 * @date 2022-02-02
 *
 * @brief Implementation file for pEvent class
 *
 */
#include "pEvent.h"

pEvent::pEvent() {
  signalled = false;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
}

pEvent::~pEvent() {
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
}

void pEvent::WaitForSignal() {
  pthread_mutex_lock(&mutex);
  while (!signalled) {
    pthread_cond_wait(&cond, &mutex);
  }
  signalled = false;
  pthread_mutex_unlock(&mutex);
}

void pEvent::Signal() {
  pthread_mutex_lock(&mutex);
  signalled = true;
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond);
}
