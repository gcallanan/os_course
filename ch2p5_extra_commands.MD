# Kernel Logs and Modules

This file shows some interesting terminal commands to view the kernel modules and debug information.

This file was written by Gareth Callanan and is intended for use in the operating systems course. Everything here has been tested on a system running the "Ubuntu 20.04.6 LTS" Operating System. Ubuntu is distribution of the Linux OS. All these commands are intended to be run from the terminal.

# Kernel Logs

To view the logs in the linux system do the following:
1. Open a terminal
2. Navigate to the logs directory with 'cd /var/log'
3. View all logs in the directory by typing "ls" in the terminal. Interesting logs include:
  1. dmesg - a fixed size circular buffer for kernel diagnostic messages. Mostly recieves information on system boot.
  2. syslog - destination for most log messages from services running on the system.
  3. auth.log - shows all attempts to log in to the system
4. View any of these files by running 'cat FILENAME'

NOTE: You do not need to understand many or any of the messages in these log files. As you progress in your career developing software you will encounter bugs and issues. Knowing to check kernel logs is just one of the many tools you can use to understand and debug these issues.

Here is an example of how to trigger an event that updates the auth.log file.
1. Run 'cat auth.log' from the /var/log directory in the terminal to view the current contents of the auth.log file.
2. Run 'sudo ls'. The 'sudo' command will enter the root user mode and run the 'ls' command from there. If you do not have sudo priviledges on the system. Do not worry, the log file will be updated anyway
3. Run 'cat auth.log' again. You should see an entry in the file logged at the time you ran the command above.

# Kernel Modules

This example was copied from: https://www.tecmint.com/load-and-unload-kernel-modules-in-linux/

1. To view all loaded kernel modules run 'lsmod'
2. View information on a specific kernel module using 'modinfo MODULE_NAME'. example: 'modinfo speedstep-lib'. speedstep-lib is a driver that allows the OS to scale the CPU frequency up and down to save power.
3. To load a kernel module run 'sudo modprobe MODULE_NAME' (you need root permissions to do this). Example: 'sudo modprobe speedstep-lib'. Run lsmod again, does this module appear?
4. Remove the module with 'sudo modprobe -r speedstep-lib'. Run lsmod again, has this module disappeared?