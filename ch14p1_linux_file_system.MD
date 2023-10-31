# Linux File System

## Introduction

This file shows the commands used to explore the linux files system.

This file was written by Gareth Callanan and is intended for use in the operating systems course. Everything here has been tested on a system running the "Ubuntu 20.04.6 LTS" Operating System. Ubuntu is distribution of the Linux OS. All these commands are intended to be run from the terminal.

The Linux FCB is known as an **inode**. It is described in Section 14.4.3: Indexed Allocation of the Operating System Concepts textbook. Here is a nice video going into the detail of an inode: https://www.youtube.com/watch?v=tMVj22EWg6A.

## Exploring the Linux File System

The Linux file system contains many mounted volumes viewed as a single file system. You can view all mounted volumes by running the command `df` from the terminal. Sometimes the file system has very strange volumes mounted. Can you find your main volume where all your documents are stored (it should be mounted on "/"!)? It should look something like this:

    Filesystem     1K-blocks     Used Available Use% Mounted on
    ...
    /dev/nvme0n1p5  88505288 65206980  18756512  78% /

Once you have found your volume, you can find more information it by running the command: `sudo dumpe2fs -h /dev/nvme0n1p5` replacing "/dev/nvme0n1p5" with the name of your primary volume. How many free inodes are there? How many free blocks? Does the number of free blocks multiplied by the block size match the number of free space left on your drive?

Now lets examine the the inodes of specific files:
1. Navigate to the top level of the file system: `cd /`.
2. View all the files in the top level directory: `ls -latr`. This direcory should mostly consists of directories but you should also see a very large file called "swapfile" (Swapping is discussed in chapter 9.5 of the operating system concepts book. This is the file that primary memory is swapped to):

        ...
        drwxr-xr-x  14 root root       4096 apr 23  2020 var
        ...
        -rw-------   1 root root 2147483648 maj 11  2021 swapfile
        ...
3. "var" above folder. Notice how "var" has a size equal to 4096 bytes (1 block size). Why is this? (a quick google can answer your question) Remember that all folders in Linux are files.
4. If you want to get more file system information about a specific file run "stat filename" eg: `stat /swapfile`. Then you can see the number of blocks the file is allocated and the inode of the blocks
