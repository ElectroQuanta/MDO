/**
 * @file ddDigitalOut.cpp
 * @author Jose Pires
 * @date 2022-02-04
 *
 * @brief Implementation file for Digital output driver
 *
 */

#include "ddDigitalOut.h"
//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

namespace DeviceDriver{
    const std::string DigitalOutput::devPath = "/dev/";
    const std::string DigitalOutput::modulePath = "/etc/";

    DigitalOutput::DigitalOutput(std::string devName, int id){
        _id = id;
        _devPath = devPath + devName + std::to_string(id);
        _modulePath = modulePath + devName + ".ko"; 
    }

    DigitalOutput::~DigitalOutput(){
        /**< Close device */
        Close();
        
        std::string remove_cmd = "rmmod " + _modulePath;
        /**< Insert the module */
        system( remove_cmd.c_str() );
    }

    bool DigitalOutput::Open(){

        std::string insert_cmd = "insmod " + _modulePath;
        /**< Insert the module */
        //system( insert_cmd.c_str() );
        
        _fd = open( _devPath.c_str(), O_WRONLY);
        if(_fd < 0)
            return false;

        return true;
    }

    void DigitalOutput::Close(){
        close(_fd);
    }

    void DigitalOutput::Write(bool enable){
        char c = enable + '0';
        write(_fd, &c, sizeof(c));
    }
    
};
