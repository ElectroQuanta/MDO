obj-m += hc-sro4.o


HOME=/home/zmpl
BUILDROOT_DIR=$(HOME)/OneDrive-UM/Univ/MI_Electro/Sem7/SEC/2021-22/Buildroot/buildroot-2021.11.1
BUILD_PATH=$(BUILDROOT_DIR)/output/build
HOST_PATH=$(BUILDROOT_DIR)/output/host
TOOLCHAIN_PATH=$(HOST_PATH)/bin

#TOOLS_PREFIX=arm-buildroot-linux-uclibcgnueabihf
TOOLS_PREFIX=arm-buildroot-linux-gnueabihf


KDIR := $(BUILD_PATH)/linux-custom
ARCH ?= arm
CROSS_COMPILE ?= $(TOOLCHAIN_PATH)/$(TOOLS_PREFIX)-

all:
	make -C $(KDIR) M=$(PWD) modules ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	make -C $(KDIR) M=$(PWD) clean ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
