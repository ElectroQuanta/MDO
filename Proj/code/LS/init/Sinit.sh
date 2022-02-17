#!/bin/sh

# create and installing message queues
rm -rf /dev/mqueue
mkdir /dev/mqueue
mount -t mqueue distance /dev/mqueue

# Insert device drivers kernel modules
insmod /etc/LS/DDrivers/Frag/frag.ko
insmod /etc/LS/DDrivers/USS/hc-sro4.ko

# starting daemon
/etc/LS/Daemon/daemon

# CD into folder
#cd /etc/LS/App/bin/LSApp

# starting application
/etc/LS/App/bin/LSApp -platform linuxfb
