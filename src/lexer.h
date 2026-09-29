#ifndef LEXER_H
#define LEXER_H

typedef enum {
  TOKENTYPE_EOF = 0,
  TOKENTYPE_ILLEGAL,

  TOKENTYPE_COMMA,
  TOKENTYPE_SEMICOLON,

  TOKENTYPE_RBRACKET,
  TOKENTYPE_LBRACKET,

  TOKENTYPE_RBRACE,
  TOKENTYPE_LBRACE,

  TOKENTYPE_RPAREN,
  TOKENTYPE_LPAREN,

  TOKENTYPE_FUNC,
  TOKENTYPE_PLOT,

} TokenType;

typedef struct SToken {
  TokenType type;
  char *literal;
} Token;

typedef struct SLexer Lexer;

Lexer *lexer_create(char* input);
Token *lexer_next_token(Lexer* lex);
void lexer_destroy(Lexer *lex);

Token *token_create(TokenType type, char *lit);
void token_destroy(Token *t);

#endif // LEXER_C
