#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cel.h"

int parse(sourcefile_t *src) {
  if(src->tokens == NULL || src->tokens->count == 0) {
    printf("no tokens available\n");
    return 0;
  }

  int curr = 0;
  while(curr != src->tokens->count) {
    int next = curr + 1;
    int prev = curr - 1;

    printf("curr: %d, next: %d, prev: %d\n", curr, next, prev);

    curr++;
  }

  return 1;
}
