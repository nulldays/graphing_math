#include "lexer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DEBUG
#ifdef _DEBUG
#define DEBUG_PRINT(s) printf(s)
#else
#define DEBUG_PRINT(s)
#endif // _DEBUG

struct SLexer {
  char *input;
  unsigned int inputLen;
  long position;
  long next_position;
  int ch;
};

void _lexer_readch(Lexer *lex);
void _lexer_read_whitespace(Lexer *lex);
bool _is_digit(char c);
bool _is_letter(char c);
const char *_lexer_read_integer(Lexer *lex, size_t *len);
const char *_lexer_read_identifier(Lexer *lex, size_t *len);

Lexer *lexer_create(char *input) {

  size_t len = sizeof(Lexer);
  Lexer *lex = malloc(len);
  memset(lex, 0, len);

  lex->input = input;
  lex->inputLen = strlen(input) + 1;

  _lexer_readch(lex);
  return lex;
}

void lexer_destroy(Lexer *lex) {
  if (lex) {
    free(lex);
  }
}

Token *lexer_next_token(Lexer *lex) {

  Token *tok = NULL;

  _lexer_read_whitespace(lex);

  switch (lex->ch) {
  case '\0':
    DEBUG_PRINT("PRINTED EOF\n");
    tok = token_create(TOKENTYPE_EOF, NULL);
    break;
  case ',':
    DEBUG_PRINT("PRINTED COMMA\n");
    tok = token_create(TOKENTYPE_COMMA, NULL);
    break;
  case ';':
    DEBUG_PRINT("PRINTED SEMICOLON\n");
    tok = token_create(TOKENTYPE_SEMICOLON, NULL);
    break;
  case '[':
    DEBUG_PRINT("PRINTED RBRACKET\n");
    tok = token_create(TOKENTYPE_RBRACKET, NULL);
    break;
  case ']':
    DEBUG_PRINT("PRINTED LBRACKET\n");
    tok = token_create(TOKENTYPE_LBRACKET, NULL);
    break;
  case '{':
    DEBUG_PRINT("PRINTED LBRACE\n");
    tok = token_create(TOKENTYPE_LBRACE, NULL);
    break;
  case '}':
    DEBUG_PRINT("PRINTED RBRACE\n");
    tok = token_create(TOKENTYPE_RBRACE, NULL);
    break;
  case '(':
    DEBUG_PRINT("PRINTED LPAREN\n");
    tok = token_create(TOKENTYPE_LBRACE, NULL);
    break;
  case ')':
    DEBUG_PRINT("PRINTED RPAREN\n");
    tok = token_create(TOKENTYPE_RPAREN, NULL);
    break;
  case '+':
    DEBUG_PRINT("PRINTED PLUS\n");
    tok = token_create(TOKENTYPE_PLUS, NULL);
    break;
  case '-':
    DEBUG_PRINT("PRINTED MINUS\n");
    tok = token_create(TOKENTYPE_MINUS, NULL);
    break;
  case '/':
    DEBUG_PRINT("PRINTED SLASH\n");
    tok = token_create(TOKENTYPE_SLASH, NULL);
    break;
  case '*':
    DEBUG_PRINT("PRINTED STAR\n");
    tok = token_create(TOKENTYPE_STAR, NULL);
    break;
  }

  if (_is_digit(lex->ch)) {
    size_t len = 0;
    char *literal = NULL;
    const char *ident = _lexer_read_integer(lex, &len);

    DEBUG_PRINT("PRINTED NUMBER\n");
    literal = strndup(ident, len);
    tok = token_create(TOKENTYPE_NUMBER, literal);
    return tok;
  } else if (_is_letter(lex->ch)) {
      // TODO: implement custom identifiers and known keywords
  }

  // ILLEGAL
  if (tok == NULL) {
    DEBUG_PRINT("ILLEGAL CHAR\n");
    tok = token_create(TOKENTYPE_ILLEGAL, NULL);
  }

  _lexer_readch(lex);
  return tok;
}

Token *token_create(TokenType type, char *lit) {

  int sz = sizeof(Token);
  Token *tok = malloc(sz);
  if (!tok) {
    perror("Error allocating Token");
    exit(EXIT_FAILURE);
  }

  tok->type = type;
  tok->literal = lit;

  return tok;
}

void token_destroy(Token *tok) {
  if (tok && tok->literal) {
    free(tok->literal);
  }
  if (tok) {
    free(tok);
  }
}

bool _is_digit(char ch) { return '0' <= ch && ch <= '9'; }

bool _is_letter(char ch) {
  return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

void _lexer_readch(Lexer *lex) {
  if (lex->next_position >= lex->inputLen) {
    lex->ch = 0;
  } else {
    lex->ch = lex->input[lex->next_position];
  }
  lex->position = lex->next_position;
  lex->next_position += 1;
}

void _lexer_read_whitespace(Lexer *lex) {

  char ch = lex->ch;
  while (ch == ' ' || ch == '\n' || ch == '\t') {
    _lexer_readch(lex);
    ch = lex->ch;
  }
}

const char *_lexer_read_integer(Lexer *lex, size_t *len) {

  char *res = NULL;
  size_t position = lex->position;

  while (_is_digit(lex->ch)) {
    _lexer_readch(lex);
  }

  if (len) {
    *len = lex->position - position;
  }

  return lex->input + position;
}

const char *_lexer_read_identifier(Lexer *lex, size_t *len) {

  char *res = NULL;
  size_t position = lex->position;

  while (_is_letter(lex->ch)) {
    _lexer_readch(lex);
  }

  if (len) {
    *len = lex->position - position;
  }

  return lex->input + position;
}
