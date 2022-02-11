obj-m:=frag.o
frag-objs:=fragmodule.o utils.o
KDIR := /home/hugof37/Desktop/ESRG/buildroot/buildroot-2021.02.5/output/build/linux-custom
ARCH ?= arm64
CROSS_COMPILE ?= /home/hugof37/Desktop/ESRG/buildroot/buildroot-2021.02.5/output/host/bin/aarch64-buildroot-linux-gnu-

export ARCH CROSS_COMPILE


KBUILD_TARGETS	:= clean help modules modules_install

.PHONY: all $(KBUILD_TARGETS)

all: modules
$(KBUILD_TARGETS):
	$(MAKE) -C $(KDIR) M=$(shell pwd) $@
