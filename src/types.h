enum tokentype_t {
  TOKTYPE_NONE,
  TOKTYPE_ALPHA_UPPER,
  TOKTYPE_ALPHA_LOWER,
  TOKTYPE_NUMERIC,
  TOKTYPE_WHITESPACE,
  TOKTYPE_DOT,
  TOKTYPE_NEWLINE,
  TOKTYPE_COLON,
  TOKTYPE_EQUALS,
  TOKTYPE_SEMICOLON,
  TOKTYPE_PLUS,
  TOKTYPE_LEFT_BRACE,
  TOKTYPE_RIGHT_BRACE
};

typedef struct token_t {
  char label;
  enum tokentype_t type;
} token_t;

typedef struct tokens_t {
  int count;
  token_t **token;
} tokens_t;

typedef struct sourcefile_t {
  char *name;
  char *data;
  tokens_t *tokens;
} sourcefile_t;
