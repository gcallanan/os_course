# A simple character driver

A character driver is a type of Linux kernel module that allows byte-by-byte communication between user space applications and either hardware devices or kernel functionality. This example creates a simple character driver that doesn't communicate with any hardware - it just writes and reads to a memory buffer.

The [simple_char.c](simple_char.c) is the actual driver code. [Makefile](Makefile) builds the driver for your current kernel version.

**NOTE:** The following operations require sudo permissions to install and manage the driver.

## Build the driver

```bash
make
```

## Insert the module (sudo permissions required):

```bash
sudo insmod simple_char.ko
```

## Check if it exists:

Two ways to verify the driver is loaded:
1. `lsmod | grep simple_char` - check kernel modules list
2. `ls -l /dev/simple_char` - check if driver file exists in device filesystem

## Give it read and write permissions

By default, device files are only accessible by root. To allow user access:

```bash
sudo chmod 666 /dev/simple_char
```

## Read and write to the device

Write to driver:
```bash
echo "hello world" > /dev/simple_char
```

Read from device:
```bash
cat /dev/simple_char
```

## Examine kernel logs

View driver messages in kernel logs:
```bash
dmesg
```

## Remove the driver

When finished experimenting:
```bash
sudo rmmod simple_char
```