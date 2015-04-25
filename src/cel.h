enum lextype_t {
  LEXTYPE_NONE,
  LEXTYPE_ALPHANUMERIC,
  LEXTYPE_WHITESPACE,
  LEXTYPE_DOT,
  LEXTYPE_NEWLINE,
  LEXTYPE_COLON,
  LEXTYPE_EQUALS,
  LEXTYPE_SEMICOLON,
  LEXTYPE_PLUS,
  LEXTYPE_LEFT_BRACE,
  LEXTYPE_RIGHT_BRACE
};

enum tokentype_t {
  TOKEN_NONE,
  TOKEN_IDENTIFIER
};

typedef struct pos_t {
  int col;
  int row;
} pos_t;

typedef struct token_t {
  char *label;
  enum tokentype_t type;
  pos_t start;
  pos_t end;
} token_t;

typedef struct tokens_t {
  int count;
  token_t *token;
} tokens_t;

typedef struct lexchar_t {
  char label;
  enum lextype_t type;
  pos_t position;
} lexchar_t;

typedef struct lexchars_t {
  int count;
  lexchar_t *lexchar;
} lexchars_t;

typedef struct sourcefile_t {
  char *name;
  char *data;
  lexchars_t *lexchars;
  tokens_t *tokens;
} sourcefile_t;

int classify_lexchar(int character);
int lexify_chars(sourcefile_t *src);
int tokenize(sourcefile_t *src);
int parse(sourcefile_t *src);
