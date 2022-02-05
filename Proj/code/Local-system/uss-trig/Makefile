obj-m:=uss.o
uss-objs:=ussmodule.o utils.o
KDIR := /home/hugof37/Desktop/ESRG/buildroot/buildroot-2021.02.5/output/build/linux-custom
ARCH ?= arm
CROSS_COMPILE ?= /home/hugof37/Desktop/ESRG/buildroot/buildroot-2021.02.5/output/host/bin/arm-buildroot-linux-gnueabihf-

export ARCH CROSS_COMPILE


KBUILD_TARGETS	:= clean help modules modules_install

.PHONY: all $(KBUILD_TARGETS)

all: modules
$(KBUILD_TARGETS):
	$(MAKE) -C $(KDIR) M=$(shell pwd) $@
