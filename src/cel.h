#define TRUE  1
#define FALSE 0

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
  TOKEN_IDENTIFIER,
  TOKEN_COLON,
  TOKEN_EQUALS,
  TOKEN_END_OF_STATEMENT,
  TOKEN_START_OF_BLOCK,
  TOKEN_END_OF_BLOCK,
  TOKEN_WHITESPACE,
  TOKEN_ADD,
  TOKEN_NEWLINE
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

int classify_lexchar(int);
int classify_token(char *);
char *display_tokentype(int);
int is_whitespace(char *);
int lexify(struct sourcefile_t *);
int loadfile(struct sourcefile_t *);
int parse(struct sourcefile_t *);
int tokenize(struct sourcefile_t *);
