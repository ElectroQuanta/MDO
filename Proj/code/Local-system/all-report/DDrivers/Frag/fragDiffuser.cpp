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
#include "frag.h"
#include <type_traits>

#define DIFF_DEBUG 0
#if DIFF_DEBUG == 1
#include <iostream>
#endif

namespace Frag {

    int Diffuser::Instances = 0;
    
    Diffuser::Diffuser(Fragrance &f) {
        pthread_mutex_init(&_mutex, NULL);
        _frag = f;
        _id = Instances;

        /**< Instanciate the device driver */
        _dd = new DeviceDriver::DigitalOutput("frag", Instances);

        /**< Open it */
        _ddWorking = _dd->Open();

        /**< Increment nr of instances */
        Instances++;

        _enabled = false;
    }

    Diffuser::~Diffuser(){
        pthread_mutex_destroy(&_mutex);

        /**< Release memory */
        delete _dd;
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
        if(_ddWorking)
            _dd->Write(enable);
    }

    void Diffuser::fragrance(Fragrance &f){
      pthread_mutex_lock(&_mutex);
      f = _frag;
      pthread_mutex_unlock(&_mutex);
    }

    void Diffuser::setFragrance(const Fragrance &f){
        /**< Update state */
      pthread_mutex_lock(&_mutex);
      _frag = f;
      pthread_mutex_unlock(&_mutex);
    }
    }; // namespace Frag
