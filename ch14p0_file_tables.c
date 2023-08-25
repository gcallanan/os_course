// Program for OS Course. Opens a file and then directs the user on how to find
// the per-process open file table from the terminal.
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS
//
// To build and run the program from the terminal:
//  build with "cc ch14p0_file_tables.c -o ch14p0_file_tables"
//  run with: "./ch14p0_file_tables"

#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Process ID: %ld. Per-process open-file table location /proc/%ld/fd\n", (long)getpid(), (long)getpid());
  printf("View the file table by running 'cd /proc/%ld/fd' in the terminal followed by 'ls -latr'\n", (long)getpid());
  // When you view the file table you may find the following files:
  // lrwx------ 1 gareth gareth 64 aug 25 10:11 2 -> /dev/pts/0
  // lrwx------ 1 gareth gareth 64 aug 25 10:11 1 -> /dev/pts/0
  // lrwx------ 1 gareth gareth 64 aug 25 10:11 0 -> /dev/pts/0
  // These symbolic links 0,1,2 represent stdin, stdout, stderr. They link to
  // /dev/pts/0 which is the terminal output (everything in Linux is a file).

  // 1. Open the file ch14p0_temp_file.txt, it should now appear in /proc/%ld/fd
  printf("Opening file: ch14p0_temp_file.txt\n");
  FILE *fileHandle;
  fileHandle = fopen("ch14p0_temp_file.txt", "r");
  if (fileHandle == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  // 2. sleep(120) will result in a system call that suspends the process for
  // 120 seconds . This will give you time to examine the files in the proc
  // directory
  printf("Sleep for 120 second in Linux.\n");
  sleep(120);
  printf("Sleep complete.\n");

  // 3. Close the file safetly - we dont expect anything bad to happen in this
  // instance as we did not write to the file, but its good practice anyway
  fclose(fileHandle);

  printf("Process Terminating.\n");
  // 4. Process terminates now and is cleaned up by OS
  return 0;
}