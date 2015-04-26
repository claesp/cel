#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cel.h"

int classify_lexchar(int character) {
  if(character > 47 && character < 58) {         /* numbers */
    return LEXTYPE_ALPHANUMERIC;
  } else if(character > 64 && character < 91) {  /* uppercase */
    return LEXTYPE_ALPHANUMERIC;
  } else if(character > 96 && character < 123) { /* lowercase */
    return LEXTYPE_ALPHANUMERIC;
  }

  switch(character) {
  case ' ':
  case '\t':
    return LEXTYPE_WHITESPACE;
  case '\n':
    return LEXTYPE_NEWLINE;
  case '.':
    return LEXTYPE_DOT;
  case ':':
    return LEXTYPE_COLON;
  case '=':
    return LEXTYPE_EQUALS;
  case ';':
    return LEXTYPE_SEMICOLON;
  case '+':
    return LEXTYPE_PLUS;
  case '{':
    return LEXTYPE_LEFT_BRACE;
  case '}':
    return LEXTYPE_RIGHT_BRACE;
  default:
    return LEXTYPE_NONE;
  }
}

int lexify(sourcefile_t *src) {
  if(src->data == NULL) {
    printf("filedata for '%s' is null\n", src->name);
    return FALSE;
  }

  int character_size_bytes = sizeof(lexchar_t) * strlen(src->data);
  
  printf("allocating memory for lexchars (%d bytes)\n", character_size_bytes);
  lexchars_t *lexchars = (lexchars_t *)malloc(sizeof(lexchars_t));
  lexchars->lexchar = (lexchar_t *)malloc(character_size_bytes);
  lexchars->count = strlen(src->data);

  int pos = 1;
  int row = 1;
  
  for(int i = 0; i < lexchars->count; i++) {
    char current = (char)src->data[i];
        
    lexchar_t lexchar;
    lexchar.label = current;
    lexchar.type = classify_lexchar(lexchar.label);
    pos_t lexchar_position;
    lexchar_position.col = pos;
    lexchar_position.row = row;
    lexchar.position = lexchar_position;
    lexchars->lexchar[i] = lexchar;

    pos++;

    if(current == '\n') {
      row++;
      pos = 1;
    }
  }

  src->lexchars = lexchars;
  
  return TRUE;
}

int classify_token(char *label) {
  if(strcmp(label, ":") == 0) {
    return TOKEN_COLON;
  } else if(strcmp(label, "=") == 0) {
    return TOKEN_EQUALS;
  } else if(strcmp(label, ";") == 0) {
    return TOKEN_END_OF_STATEMENT;
  } else {
    return TOKEN_NONE;
  }
}

int tokenize(sourcefile_t *src) {
  if(src->lexchars->count == 0) {
    printf("no available tokens in '%s'\n", src->name);
    return FALSE;
  }

  tokens_t *tokens = (tokens_t *)malloc(sizeof(tokens_t));
  size_t token_size_bytes = sizeof(token_t);
  tokens->token = (token_t *)malloc(token_size_bytes);

  int token_count = 0;
  int token_start = 0;
  int token_end = 0;
  lexchar_t previous;

  for(int i = 1; i <= src->lexchars->count; i++) {
    previous = src->lexchars->lexchar[i-1];
    lexchar_t current = src->lexchars->lexchar[i];

    if(current.type != previous.type) {
      token_end = i - 1;
      
      int token_size = token_end - token_start;
      token_t token;
      token.label = (char *)malloc((sizeof(char) * token_size) + 1);

      for(int j = 0; j <= token_size; j++) {
	lexchar_t lexchar = src->lexchars->lexchar[token_start + j];
	token.label[j] = lexchar.label;
      }
      token.label[token_size + 1] = '\0';
      token.type = classify_token(token.label);

      lexchar_t lexchar_start = src->lexchars->lexchar[token_start];
      lexchar_t lexchar_end = src->lexchars->lexchar[token_end];
      token.start = lexchar_start.position;
      token.end = lexchar_end.position;

      token_size_bytes = sizeof(token_t) * (token_count + 1);
      token_t *ext_token = (token_t *)realloc(tokens->token, token_size_bytes);
      if(ext_token != NULL) {
	tokens->token = ext_token;
	tokens->token[token_count] = token;
      }

      token_start = i;
      token_count++;
    }
  }

  tokens->count = token_count;
  src->tokens = tokens;
    
  return TRUE;
}
