// $id$

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "debugf.h"

#define BUFFER_LENGTH 16

static char *token_tag = "struct token";

struct token {
   char *tag;
   FILE *file;
   int token;
   size_t length;
   size_t chars;
   char *buffer;
};

token_ref new_token (FILE *file) {
   token_ref new = malloc (sizeof (struct token));
   assert (new != NULL);
   new->tag = token_tag;
   new->file = file;
   new->token = 0;
   new->length = BUFFER_LENGTH;
   new->buffer = malloc (new->length);
   assert (new->buffer != NULL);
   new->buffer[0] = '\0';
   new->chars = 0;
   DEBUGF ('t', "token_ref=%p\n", new);
   return new;
}

void free_token (token_ref token) {
   assert (is_token (token));
   free (token->buffer);
   memset (token, 0, sizeof (struct token));
   free (token);
}

char *peek_token (token_ref token) {
   DEBUGF ('t', "peek %p [%d] \"%s\"\n", token, token->chars,
           token->buffer);
   return token->buffer;
}


int scan_token (token_ref token) {
   token->chars = 0;
   token->buffer[token->chars] = '\0';
   int result = EOF;
   int nextchar = 0;
   do {
      nextchar = fgetc (token->file);
   } while (isspace (nextchar));
   if (nextchar == EOF) {
      result = EOF;
   }else if (nextchar == '_' || isdigit (nextchar)) {
      do {
         // LINTED (assignment of 32-bit integer to 8-bit integer)
         token->buffer[token->chars++] = nextchar;
         if (token->chars == token->length) {
            token->length *= 2;
            token->buffer = realloc (token->buffer, token->length);
            assert (token->buffer);
         }
         nextchar = fgetc (token->file);
      } while (isdigit (nextchar));
      token->buffer[token->chars] = '\0';
      int ungetchar = ungetc (nextchar, token->file);
      assert (ungetchar == nextchar);
      result = NUMBER;
   }else {
      result = nextchar;
   }
   DEBUGF ('t', "scan %p [%d] \"%s\" %d\n", token, token->chars,
           token->buffer, result);
   return result;
}

bool is_token (token_ref token) {
   // LINTED (assignment of 32-bit integer to 8-bit integer)
   return token != NULL && token->tag == token_tag;
}
