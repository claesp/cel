#include <stdio.h>
#include <stdlib.h>

const int MAJOR = 0;
const int MINOR = 1;


int
loadfile(char *filename, char *data)
{
  printf("about to load '%s'\n", filename);

  return 0;
}

int
main(int argc, char **argv)
{
  printf("cel v.%d.%d.0\n", MAJOR, MINOR);
  char *data = (char *)malloc(4 * sizeof(char));
  for(int i = 1; i < argc; i++) {
    printf("arg %d: %s\n", i, argv[i]);
    loadfile(argv[i], data);
  }

  return 0;
}
