// Program for OS Course. Demonstrates how the process state changes.
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS
//
// To build and run the program from the terminal:
//  build with "cc ch5p1_busy_loop.c -o ch5p1_busy_loop"
//  run with: "./ch5p1_busy_loop"
//
// A program that keeps the process in a running state for a specific amount of
// time. On an Intel(R) Core(TM) i7-10750H CPU @ 2.60GHz CPU, this takes about
// 10 seconds to execute. Adjust the value of LOOP_ITERATIONS if you want this
// loop to take longer or quicker to execute.

#include <stdio.h>
#include <unistd.h>

#define LOOP_ITERATIONS 6400000000

int main() {

  printf("Run a loop to keep process busy:\n");
  for (unsigned long i = 0; i < LOOP_ITERATIONS; i++) {
    __asm__ __volatile__("" : "+g"(i) : :);
  }
  printf("Busy loop complete\n");

  // 4. Process terminates now and is cleaned up by OS
  return 0;
}
