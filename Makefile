obj-m += my_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
