// Example taken from Taken from Silberschatz Operating System Concepts code
// examples: https://github.com/greggagne/osc10e/blob/master/ch4/thrd-posix.c
// and modified by Gareth Callanan for the OS programming course.
//
// To build and run the program from the terminal:
//    build with "gcc -o ch4_pthreads  ch4_pthreads.c -lpthread"
//    run with "./ch4_pthreads"
//
// --- Below I try explain how the pthread library is implimented in Linux ---
//
// Pthreads refers to the POSIX "standard" for implimenting threads. We
// make use of the pthread "library" in Linux which is an implementation of the
// standard for linux. Linux implements this standard by calling the "clone"
// system call within the  pthread_create function.
//
// If you run "strace ./ch4_pthreads" you can see the "clone" system call being
// made. It looks something like this:
//
// "clone(child_stack=0x7ff26eeb6fb0,
// flags=CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID,
// parent_tid=[17786], tls=0x7ff26eeb7700, child_tidptr=0x7ff26eeb79d0)"
//
// The CLONE_VM flag means that the address space is shared between the parent
// and child threads when clone is called. As such the "sum" variable should
// refer to the same memory location in both threads, unlike when we used fork
// in ch3_fork_process_2 where each process has the sum variable pointing in
// different memory locations. What do we expect the value of the sum variable
// to be at each point in the code?
//
// Each thread in linux is treated as a process when using the pthreads library,
// however when using pthreads_create, the new process keeps the same process id
// as the parent but has a different thread id instead. In the clone call above,
// the argument parent_tid=[17786] overrides the new child process's PID so that
// it appears as a thread to the user. A new thread with thread ID 17787 is
// created in the child process. The similarities between threads and processes
// in linux can be confusing. It would be good for your general knowledge if you
// were familiar on the nuances here.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sum; /* this data is shared by the thread(s) */

void *runner(void *param); /* the thread */

/**
 * The thread will begin control in this function
 */
void *runner(void *param) {
  printf("Thread Process ID: %ld. Thread ID: %ld\n", (long)getpid(),
         (long)gettid());
  sum += 30;
  // Question 1: What do you expect the value of sum to be here?
  // a) 10
  // b) 30
  // c) 40
  // d) 60
  printf("2. Sum Value: %i\n", sum);
  sleep(10);
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  sum = 10;
  printf("1. Sum Value: %i\n", sum);

  printf("Main Process ID: %ld. Thread ID: %ld\n", (long)getpid(),
         (long)gettid());

  pthread_t tid;       /* the thread identifier */
  pthread_attr_t attr; /* set of attributes for the thread */

  /* get the default attributes */
  pthread_attr_init(&attr);

  /* create the thread */
  pthread_create(&tid, &attr, runner, NULL);

  // Unlike with fork, everything below here is only part of the original
  // process

  /* now wait for the thread to exit */
  pthread_join(tid, NULL);

  sum += 20;
  // Question 2: What do you expect the value of sum to be here?
  // a) 10
  // b) 30
  // c) 40
  // d) 60
  printf("3. Sum Value: %i\n", sum);
}