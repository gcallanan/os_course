// Simple container implementation to demonstrate Linux namespace concepts
// Build with: gcc container.c -o container

// _GNU_SOURCE needed for clone() with namespace flags
#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h> // clone(), CLONE_NEWPID, etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/wait.h> // waitpid()
#include <unistd.h>   // exec, sleep

// Stack size for the child process - child will have its own execution stack
#define STACK_SIZE (8 * 1024 * 1024) // 8MB stack for child

/**
 * Function that will run in the new container environment
 * This function becomes the "init" process (PID 1) in the new PID namespace
 */
static int child_main(void *arg) {
  // This will show PID 1 inside the container, but a different PID in the host
  printf("Inside child process! PID: %d\n", getpid());

  // Set hostname for the container
  // This is isolated due to the UTS namespace
  int ret = sethostname("container", strlen("container"));
  if (ret != 0)
    perror("sethostname failed");

  // Mount a new /proc filesystem instance for this namespace
  // This ensures commands like 'ps' will only show processes inside the container
  if (mount("proc", "/proc", "proc", 0, "") != 0)
    perror("mount /proc failed");

  // Execute bash as the main container process
  // This replaces the current process image with bash
  execl("/bin/bash", "bash", NULL);
  perror("execl failed");
  return 1;
}

int main(void) {
  printf("Parent PID: %d\n", getpid());

  // Allocate stack for child process
  // In a real container runtime, this would be handled differently
  char *stack = malloc(STACK_SIZE);
  if (!stack) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  // Define namespace flags for our container
  int flags = CLONE_NEWUSER | // Create a new user namespace: allowing
                              // unprivileged users to act as "root". This is a
                              // hack so we do not need sudo
              CLONE_NEWUTS |  // Create a new UTS namespace: isolates hostname
                              // and domain name
              CLONE_NEWPID |  // Create a new PID namespace: child becomes PID 1
                              // inside its namespace
              CLONE_NEWNS |   // Create a new mount namespace: isolates filesystem
                              // mount points
              SIGCHLD;        // Signal to send when child terminates

  // Create the child process with isolated namespaces
  // Note: clone is the system call that is made when you call fork(), we
  //       call it here as we need to pass in the specialized flags above.
  //       Unlike fork(), clone will launch the child_main() function in the
  //       child thread.
  pid_t child_pid = clone(child_main, stack + STACK_SIZE, flags, NULL);
  if (child_pid == -1) {
    perror("clone");
    exit(EXIT_FAILURE);
  }

  // Parent process continues here
  printf("Child created with PID %d\n", child_pid);

  // Parent waits for child to finish
  waitpid(child_pid, NULL, 0);
  printf("Child finished. Exiting.\n");

  // Clean up allocated memory
  free(stack);
  return 0;
}
