/**
 * @file ultrassonicsensor.h
 * @author Hugo Freitas
 * @date 2022-02-04
 *
 * @brief Device Driver for Ultrassonic sensors
 */


//#pragma once

#ifndef ULTRASSONICSENSOR_H
#define ULTRASSONICSENSOR_H

#include <iostream>
#include <string>

namespace DeviceDriver{

    class UltrassonicSensor{
        private:
            static const std::string writePath;
            static const std::string readPath;
    
            int trig; /**< trigger Pin */
            int echo; /**< echo Pin */
            int timeout; /**< timeout to read */
            std::string writeCmd;
            std::string readCmd;
            std::string deleteCmd;
        public:
            UltrassonicSensor(int trig, int echo, int timeout);
            ~UltrassonicSensor();
           int Read();
           bool Open();
           void Close();
        
    };
    
};

    
#endif