#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"

#define MAX_LINE_SIZE 1024

void print_tokens_from_input(Lexer *lex, char *input);

int main(void) {

  char input[MAX_LINE_SIZE] = {0};

  printf("MathGraph REPL\n");
  printf("type exit to close the REPL\n");

  Lexer *lexer;

  bool running = true;
  while (running) {
    printf("> ");

    if (fgets(input, (sizeof input), stdin) != NULL) {

      if (strcmp(input, "exit\n") == 0) {
        running = false;
        break;
      }
      lexer = lexer_create(input);
      print_tokens_from_input(lexer, input);
      lexer_destroy(lexer);
    }
  }
}

void print_tokens_from_input(Lexer *lex, char *input) {

  Lexer *lexer = lexer_create(input);

  Token *tok;
  while ((tok = lexer_next_token(lexer))->type != TOKENTYPE_EOF) {
    token_destroy(tok);
  };
}
