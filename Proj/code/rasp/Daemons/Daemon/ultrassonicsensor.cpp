/**
 * @file ddDigitalOut.cpp
 * @author Hugo Freitas
 * @date 2022-02-04
 *
 * @brief Implementation file for Sensors driver
 *
 */
#include "ultrassonicsensor.h"
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

namespace DeviceDriver{
    const std::string UltrassonicSensor::writePath = "/sys/class/distance-sensor/sysfs_configure";
    const std::string UltrassonicSensor::readPath = "/sys/class/distance-sensor/distance_";

    UltrassonicSensor::UltrassonicSensor(int trig, int echo, int timeout) {
        /**< Attribute variables */
        this->trig = trig;
        this->echo = echo;
        this->timeout = timeout;
        /**< Build commands */
        writeCmd = std::to_string(trig) + " " + 
                    std::to_string(echo) + " " + 
                    std::to_string(timeout);

        readCmd = readPath + std::to_string(trig) +
                    "_" + std::to_string(echo) + "/measure";

        deleteCmd = "-" + std::to_string(trig) +
                    " " + std::to_string(echo);
        std::cout << writeCmd << std::endl;
        std::cout << readCmd << std::endl;
        std::cout << deleteCmd << std::endl;
    }

    UltrassonicSensor::~UltrassonicSensor(){
        /**< Close device */
        Close();
    }

    int UltrassonicSensor::Read(){
        int fd0 = open(readCmd.c_str(), O_RDONLY);
        if(fd0 < 0)
            return -1;
        #define BUFF_SIZE 64
        char distance[BUFF_SIZE];

        read(fd0, &distance, BUFF_SIZE);
        close(fd0);
        return (175*atoi(distance)/10000);
    }

    void UltrassonicSensor::Close(){
        int fd = open(writePath.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0600);
        if(fd < 0)
            return;
        char buffer[64];
        strcpy(buffer, deleteCmd.c_str());
        write(fd, buffer, 64);
        close(fd);
    }

    bool UltrassonicSensor::Open(){
        //system(writeCmd.c_str());
        int fd = open(writePath.c_str(),	O_CREAT | O_WRONLY | O_APPEND, 0600);
        if(fd < 0)
            return false;
        char buffer[64];
        strcpy(buffer, writeCmd.c_str());
        write(fd, buffer, 64);
        close(fd);
        return true;
    }
    
};
