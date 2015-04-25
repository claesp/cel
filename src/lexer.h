int classify_lexchar(int character);
int lexify_chars(sourcefile_t *src);

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
