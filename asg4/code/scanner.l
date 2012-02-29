%{
// $Id: scanner.l,v 1.1 2012-02-21 20:36:10-08 - - $

#include <stdlib.h>

#include "yyextern.h"

%}

%option 8bit
%option debug
%option ecs
%option interactive
%option nodefault
%option noyywrap
%option yylineno

NUMBER  ([[:digit:]]+([-:.][[:digit:]]+)*)
WORD    ([[:alnum:]]+([-&'.][[:alnum:]]+)*)
OTHER   (.|\n)

%%

{NUMBER}        { }
{WORD}          { return 1;  }
{OTHER}         { }

%%

void yycleanup (void) {
   yy_delete_buffer (YY_CURRENT_BUFFER);
}

