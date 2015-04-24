#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

const int MAJOR = 0;
const int MINOR = 1;

int loadfile(sourcefile_t *src) {
  printf("about to load file '%s'\n", src->name);
  
  FILE *fp = NULL;
  fp = fopen(src->name, "r");

  if(fp == NULL) {
    printf("failed to open file '%s'\n", src->name);
    return 1;
  }

  fseek(fp, 0, SEEK_END);
  long filesize = ftell(fp);
  rewind(fp);

  src->data = (char *)malloc(sizeof(char) * filesize);
  if(src->data == NULL) {
    printf("unable to allocate %ld bytes of memory", (sizeof(char) * filesize));
    return 2;
  }

  size_t readsize = fread(src->data, 1, filesize, fp);
  if(readsize != filesize) {
    printf("unable to read enough bytes\n");
    return 3;
  }

  fclose(fp);

  printf("loaded file '%s'\n", src->name);

  return 0;
}

int classify_token(int token) {
  if(token > 47 && token < 58) {
    return TOKTYPE_NUMERIC;
  } else if(token > 64 && token < 91) {
    return TOKTYPE_ALPHA_UPPER;
  } else if(token > 96 && token < 123) {
    return TOKTYPE_ALPHA_LOWER;
  }

  switch(token) {
  case ' ':
  case '\t':
    return TOKTYPE_WHITESPACE;
  case '\n':
    return TOKTYPE_NEWLINE;
  case '.':
    return TOKTYPE_DOT;
  case ':':
    return TOKTYPE_COLON;
  case '=':
    return TOKTYPE_EQUALS;
  case ';':
    return TOKTYPE_SEMICOLON;
  case '+':
    return TOKTYPE_PLUS;
  case '{':
    return TOKTYPE_LEFT_BRACE;
  case '}':
    return TOKTYPE_RIGHT_BRACE;
  default:
    return TOKTYPE_NONE;
  }
}

int tokenize(sourcefile_t *src) {
  if(src->data == NULL) {
    printf("filedata for '%s' is null\n", src->name);
    return 1;
  }

  tokens_t *tokens = (tokens_t *)malloc(sizeof(tokens_t));
  tokens->count = strlen(src->data);
  
  for(int i = 0; i < tokens->count; i++) {
    tokens->token[i] = (token_t *)malloc(sizeof(token_t));
    enum tokentype_t token_type = classify_token(src->data[i]);

    tokens->token[i]->label = (char)src->data[i];
    tokens->token[i]->type = token_type;

    //printf("%c: %d\n", (char)src->data[i], token_type);
    //printf("%c: %d\n", tokens->token[i]->label, tokens->token[i]->type);
  }

  src->tokens = tokens;
  
  return 0;
}

int main(int argc, char **argv) {
  printf("cel v.%d.%d.0\n", MAJOR, MINOR);

  for(int i = 1; i < argc; i++) {
    printf("arg %d: %s\n", i, argv[i]);

    sourcefile_t *srcfile = (sourcefile_t *)malloc(sizeof(sourcefile_t));
    srcfile->name = argv[i];

    if(loadfile(srcfile)) {
      printf("failed to load '%s'\n", srcfile->name);
    }

    if(tokenize(srcfile)) {
      printf("failed to tokenize '%s'\n", srcfile->name);
    }

    printf("available tokens: %d\n", srcfile->tokens->count);

    free(srcfile->tokens);
    free(srcfile->data);
    free(srcfile);
  }

  return 0;
}
