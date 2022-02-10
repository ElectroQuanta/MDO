/**
 * @file sensors.h
 * @author Hugo Freitas
 * @date 2022-02-04
 *
 * @brief Device Driver for Ultrassonic sensors
 */

#pragma once

#include <iostream>
#include <string>

namespace DeviceDriver{

    class Sensor{
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
            Sensor(int trig, int echo, int timeout);
            ~Sensor();
           int Read();
           bool Open();
           void Close();
        
    };
    
};

    
