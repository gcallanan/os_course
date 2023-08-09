// Copied from from https://www.geeksforgeeks.org/use-posix-semaphores-c/ and
// modified by Gareth Callanan. This is intended for use in the operating
// systems course.
//
// Tested using Ubuntu 20.04.6 LTS OS
//
// To build and run the program from the terminal:
//  build with "cc ch6p1_synchronisation.c -o ch6p1_synchronisation -lpthread"
//  run with: "./ch6p1_synchronisation"
//
// This program aims to demonstrate synchronisation in a multithreading
// application. It has four threads in total (3 child threads and 1 parent
// thread). 3 of these threads (child 2 and 3 and the main thread) all modify
// the value of a single variable called sum. As such modifying sum is part of
// the critical section of the code and needs to be protected using
// syncrhonisation mechanisms. We use the the pthreads library and posix
// semaphores. In the textbook semaphores have wait(S) and signal(S) functions.
// In the POSIX standard these are known as sem_wait(&mutex) and
// sem_post(&mutex) respectively.
//
// Try answer some questions.
// QUESTION 1: What do you expect the value of sum to be at the end of
// execution?
//
// QUESTION 2: Thread 1 will signal to the other threads that the
// semaphor is available. Which of the other threads (thread 2, thread 3 or the
// main thread). Will grab the semaphore first? Is this something we can know?
// Try run the program a few times to see if a pattern emerges.
//
// QUESTION 3: Comment out sem_wait(&mutex) in thread 2, thread 3 and the main
// thread. Recompile the program and run it again. What do you expect the value
// of sum to be now? Try run the program a few times. Have we introduced a race
// condition into the program.
//
// QUESTION 4: Run strace ./ch6p1_synchronisation. This will show the system
// calls made by the main thread (not the child threads). What system call is
// made to access wait on the semaphore? What system call signals the semaphore?
// The output of strace may not be clear. COmment out the print statements to
// make this clearer.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define LOOP_ITERATIONS 3000000000

sem_t mutex;

// This sum variable is modified by all threads and thus needs to be accessed
// only in a critical section.
long int sum = 0;

// Thread 1 signals the semaphore indicating to other threads that it is now
// available for grabbing.
void *thread_1(void *arg) {
  sleep(4);
  printf("Thread 1 Running: Sending signal to semaphore. Other threads may now "
         "execute.\n");
  sem_post(&mutex);
}

void *thread_2(void *arg) {
  // wait
  printf("Thread 2 waiting on semaphore.\n");
  sem_wait(&mutex);
  printf("Thread 2 grabbed semaphore and is entering the critical section\n");

  // critical section
  for (size_t i = 0; i < LOOP_ITERATIONS; i++) {
    sum = sum + 1;
  }

  // signal
  printf("Thread 2 critical section done, signaling semaphore\n");
  sem_post(&mutex);
}

void *thread_3(void *arg) {
  // wait
  printf("Thread 3 waiting on semaphore.\n");
  sem_wait(&mutex);
  printf("Thread 3 grabbed semaphore and is entering the critical section\n");

  // critical section
  for (size_t i = 0; i < LOOP_ITERATIONS; i++) {
    sum = sum + 1;
  }

  // signal
  printf("Thread 3 critical section done, signaling semaphore\n");
  sem_post(&mutex);
}

int main() {
  // 1. Initilise semaphore - set its value to zero. This means a signal
  // needs to be sent to the semaphore before threads waiting on it can proceed.
  sem_init(&mutex, 0, 0);

  // 2. Start 3 different threads
  // -- Thread 1 (t1) executes function thread_1()
  // -- Thread 2 (t2) executes function thread_2()
  // -- Thread 3 (t3) executes function thread_3()
  pthread_t t1, t2, t3;
  pthread_create(&t1, NULL, thread_1, NULL);
  pthread_create(&t2, NULL, thread_2, NULL);
  pthread_create(&t3, NULL, thread_3, NULL);

  // 3.1 The main thread in this program also does some processing in the
  // critical section. So it needs to wait on the mutex.
  printf("Main Thread waiting on semaphore.\n");
  sem_wait(&mutex);
  printf(
      "Main thread grabbed semaphore and is entering the critical section\n");

  // 3.2 We are now in the critical section, we can modify sum
  for (size_t i = 0; i < LOOP_ITERATIONS; i++) {
    sum = sum + 1;
  }

  // 3.3 We exit the critical section now, so signal the mutex
  printf("Main thread critical section done, signaling semaphore\n");
  sem_post(&mutex);

  // 4. Wait for all the threads to finish executing
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);

  // 5. Print out the value of sum and determine if its correct.
  printf("The value of sum is: %ld, we expected %ld\n", sum,
         3 * LOOP_ITERATIONS);
  if (sum != 3 * LOOP_ITERATIONS) {
    printf("ERROR: The sum value is incorrect. There must be a race condition "
           "in the program!");
  }

  // 6. Clean up the mutex and exit the program.
  sem_destroy(&mutex);
  return 0;
}
