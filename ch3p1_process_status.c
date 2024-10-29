// Program for OS Course. Demonstrates how the process state changes.
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS
//
// To build and run the program from the terminal:
//  build with "cc ch3p1_process_status.c -o ch3p1_process_status"
//  run with: "./ch3p1_process_status"
//
// When the program runs it will output a pid <PID>. All process information is
// stored in the temporary location "/proc/<PID>/". You can access this from
// another terminal with "cd /proc/<PID>"". As soon as the process terminates,
// this folder will be deleted. The file "status" in  "/proc/<PID>/" has shows
// information about the process. View it with "cat status" in the terminal when
// you are in the "/proc/<PID>/" directory. If you want the command to keep
// running every 2 seconds to see how it changes run "watch cat status".
//
// The status file has a "State" field which should show the process status.
// This field should change as the program runs.
//
// If the process executes faster than you can type the commands, consider
// making the process sleep for longer than 30 seconds to give you time to
// navigate the command line. Remember to rebuild the file if you do!

#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Process ID: %ld. Process information files location /proc/%ld\n", (long)getpid(), (long)getpid());

  // 1. sleep(30) will result in a system call that suspends the process for
  // 30 seconds . The process should be in a "Sleep" state
  printf("Sleep for 30 second in Linux.\n");
  sleep(30);
  printf("Sleep complete.\n");

  // 2. Run a loop that keeps the CPU busy for a few seconds. The process
  // should be in a running state again
  printf("Run a loop to keep process busy:\n");
  for (unsigned long i = 0; i < 3200000000; i++) {
    __asm__ __volatile__("" : "+g"(i) : :);
  }
  printf("Busy loop complete\n");

  // 3. sleep() for 20 seconds again. Process in "Sleep" state again
  printf("Sleep for 20 second in Linux.\n");
  sleep(20);
  printf("Sleep Complete.\n");

  printf("Process Terminating.\n");
  // 4. Process terminates now and is cleaned up by OS
  return 0;
}
