// Program for OS Course. Demonstrates the system calls required to print to
// screen.
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS
//
// To build and run the program from the terminal:
//  build with "cc ch2p2_syscalls_2.c -o ch2p2_syscalls_2"
//  run with: "./ch2p2_syscalls_2"
//
// To view the system calls in this program run "strace ./ch2p2_syscalls_2" from
// the terminal. See how the "write" system call is called to write information
// to file.
//
// To find out information on a specific system call produced from strace run
// "man <system call name>"

#include <stdio.h>

int main() {
  printf("Hello World\n");
  return 0;
}