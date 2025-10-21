// Enhanced container implementation demonstrating Linux namespaces and cgroups
// Build with: gcc container_with_cgroup.c -o container_with_cgroup
// Run with: sudo ./container_with_cgroup
// NOTES:
//     1. You need to run this program as root to create cgroups or else they
//        will not be created.
//     2. You can test if this is working by running "stress -c 20" inside
//        the container, which will attempt to use 20 CPU cores but should be
//        limited by the cgroup settings we apply.

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

// Function prototype for creating and configuring cgroups
static void create_cgroup_and_add(pid_t pid);

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
  // This ensures commands like 'ps' will only show processes inside the
  // container
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
              CLONE_NEWNS | // Create a new mount namespace: isolates filesystem
                            // mount points
              SIGCHLD;      // Signal to send when child terminates

  // Create the child process with isolated namespaces
  // Note: stack pointer is at the high address because stack grows downward
  pid_t child_pid = clone(child_main, stack + STACK_SIZE, flags, NULL);
  if (child_pid == -1) {
    perror("clone");
    exit(EXIT_FAILURE);
  }

  // Parent process continues here
  printf("Child created with PID %d\n", child_pid);

  // Create a cgroup and add the child process to it to limit CPU usage
  // This demonstrates resource control, a key container feature
  create_cgroup_and_add(child_pid);

  // Parent waits for child to finish
  waitpid(child_pid, NULL, 0);
  printf("Child finished. Exiting.\n");

  // Clean up allocated memory
  free(stack);
  return 0;
}

/**
 * Creates a CPU cgroup and adds the container process to it
 * Cgroups (Control Groups) provide resource limiting, accounting, and isolation
 * This is how Docker limits container resources like CPU, memory, etc.
 */
static void create_cgroup_and_add(pid_t pid) {
  // Path to the cgroup directory we'll create
  const char *cgdir = "/sys/fs/cgroup/cpu/demo";

  // Create the cgroup directory
  mkdir(cgdir, 0755);

  char path[256];
  int fd;

  // Set CPU period (total time window in microseconds)
  // Here we set it to 200000 microseconds (200ms)
  // The period defines the time window over which CPU usage is measured
  snprintf(path, sizeof(path), "%s/cpu.cfs_period_us", cgdir);
  fd = open(path, O_WRONLY | O_CREAT, 0644);
  if (fd >= 0) {
    write(fd, "200000", 6);
    close(fd);
  } else {
    perror("write cpu.cfs_period_us");
  }

  // Set CPU quota (allowed CPU time within the period)
  // Here we set it to 50000 microseconds (50ms)
  // This means the process can use 50ms out of each 200ms period (25% CPU)
  snprintf(path, sizeof(path), "%s/cpu.cfs_quota_us", cgdir);
  fd = open(path, O_WRONLY | O_CREAT, 0644);
  if (fd >= 0) {
    write(fd, "50000", 5);
    close(fd);
  } else {
    perror("write cpu.cfs_quota_us");
  }

  // Add the container process to this cgroup by writing its PID
  // to the tasks file of the cgroup
  snprintf(path, sizeof(path), "%s/tasks", cgdir);
  fd = open(path, O_WRONLY);
  if (fd >= 0) {
    dprintf(fd, "%d\n", pid);
    close(fd);
  } else {
    perror("write tasks");
  }

  printf("Child %d limited to 25%% CPU in '%s'\n", pid, cgdir);
}
