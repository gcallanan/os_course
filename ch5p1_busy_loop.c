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
#include <time.h>

#define LOOP_ITERATIONS 6400000000

int main() {
  clock_t begin = clock();

  printf("Process %ld starting a loop to keep process busy.\n", (long)getpid());
  for (unsigned long i = 0; i < LOOP_ITERATIONS; i++) {
    __asm__ __volatile__("" : "+g"(i) : :);
  }

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Process %ld - Busy loop complete after %.2f s.\n", (long)getpid(), time_spent);

  // 4. Process terminates now and is cleaned up by OS
  return 0;
}
