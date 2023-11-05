#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/** Return true when the sum of dirlen, filelen, extlen and 3
 * would exceed the maximum possible value of a size_t; otherwise,
 * return false.
 */
bool would_wrap_around(size_t dirlen, size_t filelen, size_t extlen) {
  size_t res = dirlen;
  res += filelen;
  if (res < dirlen || res < filelen)
    return true;
  size_t old_res = res;
  res += extlen;
  if (res < old_res || res < extlen)
    return true;
  old_res = res;
  res += 3;
  if (res < old_res || res < extlen)
    return true;
  return false;
}

char* make_pathname(const char *dir, const char *fname, const char *ext) {
  size_t dirlen = strlen(dir);
  size_t filelen = strlen(fname);
  size_t extlen = strlen(ext);

  if (would_wrap_around(dirlen, filelen, extlen))
    return NULL;

  // include terminating NUL
  size_t pathbuf_size = dirlen + filelen + extlen + 3;

  char *path = malloc (pathbuf_size);
  if (!path)
      return NULL;

  memcpy (path, dir, dirlen);
  path[dirlen] = '/';

  memcpy (path + dirlen + 1, fname, filelen);
  path[dirlen + filelen + 1] = '.';

  memcpy(path + dirlen + filelen + 2, ext, extlen + 1);

  return path;
}

int main(int argc, char **argv) {
  // skip program name
  argc--;
  argv++;

  if (argc != 3) {
    fprintf(stderr, "Expected 3 args\n");
    exit(EXIT_FAILURE);
  }

  // See note: poor validation!
  char* dir = argv[0];
  char* fname = argv[1];
  char* ext = argv[2];

  char* path = make_pathname(dir, fname, ext);

  if (path != NULL) {
    printf("path is: '%s'\n", path);
    free(path);
  }
  else
    printf("couldn't allocate enough memory\n");

  return EXIT_SUCCESS;
}