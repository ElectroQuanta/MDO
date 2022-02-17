/**
 * @file ddDigitalOut.h
 * @author Jose Pires
 * @date 2022-02-04
 *
 * @brief Device Driver for Digital Output
 */

#pragma once

#include <string>

namespace DeviceDriver{

    class DigitalOutput{
    private:
        static const std::string devPath;
        static const std::string modulePath;

        int _id; /**< Device id */
        int _fd; /**< File descriptor to manage the device */
        std::string _devPath;
        std::string _modulePath;
    public:
        DigitalOutput(std::string devName, int id);
        ~DigitalOutput();
       bool Open();
       void Write(bool enable);
       void Close();
        
    };
    
};

    
