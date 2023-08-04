// Program for OS Course. Demonstrates how to call specific system calls from C.
// We write to a file using the function calls instead of the build in functions.
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS
//
// To build and run the program from the terminal:
//  build with "cc ch2p4_syscalls_4.c -o ch2p4_syscalls_4"
//  run with: "./ch2p4_syscalls_4"
//
// To view the system calls in this program run "strace ./ch2p4_syscalls_4" from
// the terminal.
//
// To find out information on a specific system call produced from strace run
// "man <system call name>"


#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{   
    int fd = syscall(SYS_openat, AT_FDCWD, "ch2p4_syscalls_4_out.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
    syscall(SYS_write, fd, "Hello world 2!", 14);
    syscall(SYS_close, fd);
    return 0;
}