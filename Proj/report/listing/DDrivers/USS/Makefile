obj-m += hc-sro4.o

ARCH=arm
CROSS_COMPILE=/home/hugof37/Desktop/ESRG/buildroot/buildroot-2021.02.5/output/host/bin/arm-buildroot-linux-gnueabihf-
# KERNEL_DIR=/lib/modules/3.18.0-trunk-rpi/build
KERNEL_DIR=/home/hugof37/Desktop/ESRG/buildroot/buildroot-2021.02.5/output/build/linux-custom
# KERNEL_DIR=../linux
# CC=arm-linux-gnueabihf-gcc

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
