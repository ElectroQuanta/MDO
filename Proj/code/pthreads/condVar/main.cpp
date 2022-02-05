#include "pEvent.h"
#include <bits/stdc++.h>
#include <iostream>


void *functionCount1(void *arg);
void *functionCount2(void *arg);
#define MAX_INT (65536-1)
#define MAX_ITER 10000

pEvent p;
pEvent p2;
pthread_mutex_t mut;

int main(void){

   pthread_t thread1, thread2;

   pthread_mutex_init(&mut, NULL);

   std::vector<pEvent *> pEvents;

   pEvents.push_back(&p);
   pEvents.push_back(&p2);

   pthread_create( &thread1, NULL, &functionCount1, &pEvents);
   pthread_create( &thread2, NULL, &functionCount2, &pEvents);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

    return 0;
}


void *functionCount1(void *arg){
    std::vector<pEvent *> *pEvents = (std::vector<pEvent *> *)arg;
    //pEvent *p = (pEvent *) arg;

    while(1){
        std::cout << "Thread 1: starting" << std::endl;
        pEvents->at(0)->Signal();
        std::cout << "Thread 1: Signaling" << std::endl;
        pEvents->at(1)->WaitForSignal();
        std::cout << "Thread 1: Received" << std::endl;
        for(int j = 0; j < MAX_INT; j++)
            for(int k = 0; k < MAX_ITER; k++)
                ;
    }

    return NULL;
}

void *functionCount2(void *arg){
    //pEvent *p = (pEvent *) arg;
    std::vector<pEvent *> *pEvents = (std::vector<pEvent *> *)arg;

    while(1){
        std::cout << "Thread 2: starting" << std::endl;
        pEvents->at(0)->WaitForSignal();
        std::cout << "Thread 2: Received" << std::endl;
        for(int j = 0; j < MAX_INT; j++)
            for(int k = 0; k < MAX_ITER; k++)
                ;

        pEvents->at(1)->Signal();
        std::cout << "Thread 2: Signaling" << std::endl;
    }

    return NULL;
}
