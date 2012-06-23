MODULE_NAME := timer_kernel

obj-m += $(MODULE_NAME).o

SUBARCH := $(shell uname -m | sed -e s/i.86/i386/)
ARCH := $(SUBARCH)
CROSS_COMPILE =
KVER := $(shell uname -r)
KSRC = /lib/modules/$(KVER)/build


all: modules strip
	@echo $(SUBARCH)

modules:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KSRC) M=$(shell pwd) modules

strip:
	$(CROSS_COMPILE)strip $(MODULE_NAME).ko --strip-unneeded

clean:
	rm -rf .tmp_versions *.mod.* *.o *.ko *.order *.symvers .*.cmd 
