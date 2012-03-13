// $Id: token.h,v 1.2 2012-03-05 20:19:38-08 - - $

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdbool.h>

#define NUMBER 256

typedef struct token *token_ref;

token_ref new_token (FILE*);

void free_token (token_ref);

int scan_token (token_ref);

char *peek_token (token_ref);

bool is_token (token_ref);

#endif

