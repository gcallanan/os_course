// Program for OS Course. Demonstrates the system calls required to write to
// file.
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS
//
// To build and run the program from the terminal:
//  build with "cc ch2p3_syscalls_3.c -o ch2p3_syscalls_3"
//  run with: "./ch2p3_syscalls_3"
//
// To view the system calls in this program run "strace ./ch2p3_syscalls_3" from
// the terminal. Look up what the openat, fstat, write and close system calls do
// using the linux man pages
//
// To find out information on a specific system call produced from strace run
// "man <system call name>"

#include <stdio.h>

int main() {
  FILE *fileHandle;
  fileHandle = fopen("ch2p3_syscalls_3_out.txt", "w");
  fprintf(fileHandle, "Hello world!");
  fclose(fileHandle);
  return 0;
}