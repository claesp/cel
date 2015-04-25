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
