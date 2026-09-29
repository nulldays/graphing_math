#include "lexer.h"

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

Lexer *lexer_create(char *input) {

  size_t len = sizeof(Lexer);
  Lexer *lex = malloc(len);
  memset(lex, 0, len);

  lex->input = input;
  lex->inputLen = strlen(input) + 1;

  _lexer_readch(lex);
  return lex;
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

void lexer_destroy(Lexer *lex) {
  if (lex) {
    free(lex);
  }
}

Token *lexer_next_token(Lexer *lex) {

  Token *tok = NULL;

  _lexer_read_whitespace(lex);

  switch (lex->ch) {
  case ',':
    DEBUG_PRINT("PRINTED COMMA\n");
    tok = token_create(TOKENTYPE_COMMA, NULL);
    break;
  case ';':
    DEBUG_PRINT("PRINTED SEMICOLON\n");
    tok = token_create(TOKENTYPE_SEMICOLON, NULL);
    break;
  case '\0':
    DEBUG_PRINT("PRINTED EOF\n");
    tok = token_create(TOKENTYPE_EOF, NULL);
    break;
  }

  // Check if is LETTER
  // Check if is a DIGIT

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
};
