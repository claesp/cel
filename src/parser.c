#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cel.h"

int parse(sourcefile_t *src) {
  if(src->tokens == NULL || src->tokens->count == 0) {
    printf("no tokens available\n");
    return 0;
  }

  for(int i = 0; i < src->tokens->count; i++) {
    int curr = i;
    /*int prev = curr - 1;
      int next = curr + 1;*/
    token_t curr_token;
    /*
    token_t prev_token;
    token_t next_token;
    
    curr_token = src->tokens->token[curr];
    if(curr != 0) {
      prev_token = src->tokens->token[prev];
    }
    if(next != src->tokens->count) {
      next_token = src->tokens->token[next];
    }
    */

    curr_token = src->tokens->token[curr];
    
    if(curr_token.type == TOKEN_IDENTIFIER) {
    } else if(curr_token.type == TOKEN_WHITESPACE) {
    }
  }
  
  return 1;
}
