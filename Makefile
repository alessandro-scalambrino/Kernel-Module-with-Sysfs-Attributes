obj-m := kmt.o

# Define variables
KDIR := /lib/modules/$(shell uname -r)/build
MODULE_PATH := /lib/modules/$(shell uname -r)/kernel/drivers/char
MODULE_NAME := kmt.ko

all:
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules
	cp $(MODULE_NAME) $(MODULE_PATH)/ || { echo "Failed to copy module"; exit 1; }

clean:
	$(MAKE) -C $(KDIR) M=$(shell pwd) clean
	rm -f $(MODULE_PATH)/$(MODULE_NAME) || { echo "Failed to remove module"; exit 1; }

help:
	$(MAKE) -C $(KDIR) M=$(shell pwd) help


