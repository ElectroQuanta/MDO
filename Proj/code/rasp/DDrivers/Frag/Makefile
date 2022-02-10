obj-m:=frag.o
frag-objs:=fragmodule.o utils.o
BUILDROOT=/home/zmpl/OneDrive-UM/Univ/MI_Electro/Sem7/SEC/2021-22/Buildroot/buildroot-2021.08.1
GCC_CRO=$(BUILDROOT)/output/host/bin/aarch64-buildroot-linux-gnu-
KDIR := "$(BUILDROOT)/output/build/linux-custom"
ARCH ?= arm64
CROSS_COMPILE ?= ${GCC_CRO}

#ECHO="echo" 
#
#echo:
#	$(ECHO) $(KDIR)

export ARCH CROSS_COMPILE


KBUILD_TARGETS	:= clean help modules modules_install

.PHONY: all $(KBUILD_TARGETS)

all: modules
$(KBUILD_TARGETS):
	$(MAKE) -C $(KDIR) M=$(shell pwd) $@
