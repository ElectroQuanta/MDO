#!/bin/sh

# add Video for Linux modules to kernel
modprobe bcm2835-v4l2

# Creating and installing message queues
mkdir /dev/mqueue
mount -t mqueue distance /dev/mqueue

# Inserting device drivers kernel modules into Linux Kernel
insmod /etc/LS/frag.ko
insmod /etc/LS/uss.ko

# starting the daemon associated with the Ultrasonic sensor
/etc/LS/uss_daemon.elf

# Rotating screen view
xrandr -o right

# Starting main process
/etc/LS/LSApp
