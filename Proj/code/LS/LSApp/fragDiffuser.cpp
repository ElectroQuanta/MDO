/**
 * @file fragDiffuser.cpp
 * @author Jose Pires
 * @date 2022-02-04
 *
 * @brief Implementation for the Fragrance diffuser class
 *
 * It interfaces with the Fragrance diffuser device through device drivers
 * and a daemon
 */

#include "fragDiffuser.h"

#define DIFF_DEBUG 1
#if DIFF_DEBUG == 1
#include <iostream>
#endif

namespace Frag {

    #define HW_PIN_DEFAULT 26
    #define FRAG_DEFAULT 0

    Diffuser::Diffuser(Fragrance &f, int pin = HW_PIN_DEFAULT) {
        pthread_mutex_init(&_mutex, NULL);
        _pin = pin;
        _frag = f;
        _enabled = false;
    }

    Diffuser::~Diffuser(){
        pthread_mutex_destroy(&_mutex);
    }

    bool Diffuser::enabled(){
      bool enabled = false;
      pthread_mutex_lock(&_mutex);
      enabled = this->_enabled;
      pthread_mutex_unlock(&_mutex);

      return enabled;
    }

    void Diffuser::enable(bool enable){
        bool prev_state;
        /**< Check if actuation is required */
        pthread_mutex_lock(&_mutex);
        prev_state = _enabled;
        _enabled = enable; /**< Update state */
        pthread_mutex_unlock(&_mutex);

        if(prev_state == enable) /**< No change of state, return */
            return;
        
        /**< TODO: Actuate */
#if DIFF_DEBUG == 1
        std::cout << "Diffuser Enabled" << std::endl;
#endif

    }

    void Diffuser::fragrance(Fragrance &f){
      pthread_mutex_lock(&_mutex);
      f = _frag;
      pthread_mutex_unlock(&_mutex);
    }

    int Diffuser::pin(){
      int pin = -1;
      pthread_mutex_lock(&_mutex);
      pin = _pin;
      pthread_mutex_unlock(&_mutex);
      return pin;
    }

    void Diffuser::setFragrance(const Fragrance &f){
        /**< Update state */
      pthread_mutex_lock(&_mutex);
      _frag = f;
      pthread_mutex_unlock(&_mutex);
    }
    void Diffuser::setPin(const int pin){
      pthread_mutex_lock(&_mutex);
      _pin = pin;
      pthread_mutex_unlock(&_mutex);
        
    }
};
