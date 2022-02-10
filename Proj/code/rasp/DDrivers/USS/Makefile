obj-m += hc-sro4.o

BUILDROOT=/home/zmpl/OneDrive-UM/Univ/MI_Electro/Sem7/SEC/2021-22/Buildroot/buildroot-2021.08.1
GCC_CRO=$(BUILDROOT)/output/host/bin/aarch64-buildroot-linux-gnu-
KDIR := "$(BUILDROOT)/output/build/linux-custom"
ARCH ?= arm64
CROSS_COMPILE ?= ${GCC_CRO}

KERNEL_DIR := "$(BUILDROOT)/output/build/linux-custom"
# KERNEL_DIR=../linux
# CC=arm-linux-gnueabihf-gcc

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
