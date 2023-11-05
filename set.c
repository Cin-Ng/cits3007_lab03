#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  uid_t ruid = getuid();
  uid_t euid = geteuid();
  printf("real uid is: %d\n", ruid);
  printf("effective uid is: %d\n", euid);

  return EXIT_SUCCESS;
}