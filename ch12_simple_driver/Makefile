# Define which object files to build as loadable kernel modules
# obj-m tells the kernel build system that these are external modules
obj-m += simple_char.o

# Default rule: build the module
all:
	# The -C option changes directory to the kernel source directory
	# $(shell uname -r) gets the current kernel version (e.g., 5.15.0-58-generic)
	# M=$(PWD) specifies where the source files and output should be
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Clean up build files
clean:
	# Similar to the build command, but runs the clean target instead
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean