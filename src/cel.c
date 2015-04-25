#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "lexer.h"
#include "parser.h"

#define TRUE  1
#define FALSE 0

const int MAJOR = 0;
const int MINOR = 1;

int loadfile(sourcefile_t *src) {
  printf("about to load file '%s'\n", src->name);
  
  FILE *fp = NULL;
  fp = fopen(src->name, "r");

  if(fp == NULL) {
    printf("failed to open file '%s'\n", src->name);
    return 0;
  }

  fseek(fp, 0, SEEK_END);
  long filesize = ftell(fp);
  rewind(fp);

  src->data = (char *)malloc(sizeof(char) * filesize);
  if(src->data == NULL) {
    printf("unable to allocate %ld bytes of memory", (sizeof(char) * filesize));
    return 0;
  }

  size_t readsize = fread(src->data, 1, filesize, fp);
  if(readsize != filesize) {
    printf("unable to read enough bytes\n");
    return 0;
  }

  fclose(fp);

  printf("loaded file '%s'\n", src->name);

  return 1;
}

int main(int argc, char **argv) {
  printf("cel v.%d.%d.0\n", MAJOR, MINOR);

  for(int i = 1; i < argc; i++) {
    printf("arg %d: %s\n", i, argv[i]);

    sourcefile_t *srcfile = (sourcefile_t *)malloc(sizeof(sourcefile_t));
    srcfile->name = argv[i];

    if(!loadfile(srcfile)) {
      printf("failed to load '%s'\n", srcfile->name);
      return 1;
    }

    if(!lexify_chars(srcfile)) {
      printf("failed to lexify characters '%s'\n", srcfile->name);
      return 2;
    }

    for(int i = 0; i < srcfile->lexchars->count; i++) {
      lexchar_t lexchar = srcfile->lexchars->lexchar[i];
      printf("%d: lexchar: %c: %d (%d,%d)\n", i, lexchar.label, lexchar.type, lexchar.position.row, lexchar.position.col);
    }

    if(!tokenize(srcfile)) {
      printf("failed to tokenize '%s'\n", srcfile->name);
      return 3;
    }

    for(int i =0; i < srcfile->tokens->count; i++) {
      token_t token = srcfile->tokens->token[i];
      printf("%d: token: %s\n", i, token.label);
    }

    free(srcfile->tokens);
    free(srcfile->lexchars);
    free(srcfile->data);
    free(srcfile);
  }

  return 0;
}
