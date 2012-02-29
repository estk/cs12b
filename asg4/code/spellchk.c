// $Id: spellchk.c,v 1.2 2012-02-22 19:50:19-08 - - $

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debugf.h"
#include "hashset.h"
#include "yyextern.h"

#define STDIN_NAME       "-"
#define DEFAULT_DICTNAME "/usr/share/dict/words"
#define DEFAULT_DICT_POS 0
#define EXTRA_DICT_POS   1
#define NUMBER_DICTS     2

char *execname = NULL;
int exit_status = EXIT_SUCCESS;

void print_error (char *object, char *message) {
   fflush (NULL);
   fprintf (stderr, "%s: %s: %s\n", execname, object, message);
   fflush (NULL);
   exit_status = EXIT_FAILURE;
}

FILE *open_infile (char *filename) {
   FILE *file = fopen (filename, "r");
   if (file == NULL) print_error (filename, strerror (errno));
   DEBUGF ('m', "filename = \"%s\", file = 0x%p\n", filename, file);
   return file;
}

void spellcheck (char *filename, hashset_ref hashset) {
   yylineno = 1;
   DEBUGF ('m', "filename = \"%s\", hashset = 0x%p\n",
                filename, hashset);
   for (;;) {
      int token = yylex ();
      if (token == 0) break;
      DEBUGF ('m', "line %d, yytext = \"%s\"\n", yylineno, yytext);
      STUBPRINTF ("%s: %d: %s\n", filename, yylineno, yytext);
   }
}

void load_dictionary (char *dictionary_name, hashset_ref hashset) {
   if (dictionary_name == NULL) return;
   DEBUGF ('m', "dictionary_name = \"%s\", hashset = %p\n",
           dictionary_name, hashset);
   STUBPRINTF ("Open dictionary, load it, close it\n");
}

int main (int argc, char **argv) {
   execname = basename (argv[0]);
   set_execname (execname);
   char *default_dictionary = DEFAULT_DICTNAME;
   char *user_dictionary = NULL;
   hashset_ref hashset = new_hashset ();
   yy_flex_debug = false;

   // Scan the arguments and set flags.
   opterr = false;
   for (;;) {
      int option = getopt (argc, argv, "nxyd:@:");
      if (option == EOF) break;
      switch (option) {
         char optopt_string[16]; // used in default:
         case 'd': user_dictionary = optarg;
                   break;
         case 'n': default_dictionary = NULL;
                   break;
         case 'x': STUBPRINTF ("-x\n");
                   break;
         case 'y': yy_flex_debug = true;
                   break;
         case '@': set_debugflags (optarg);
                   if (strpbrk (optarg, "@y")) yy_flex_debug = true;
                   break;
         default : sprintf (optopt_string, "-%c", optopt);
                   print_error (optopt_string, "invalid option");
                   break;
      }
   }

   // Load the dictionaries into the hash table.
   load_dictionary (default_dictionary, hashset);
   load_dictionary (user_dictionary, hashset);

   // Read and do spell checking on each of the files.
   if (optind >= argc) {
      yyin = stdin;
      spellcheck (STDIN_NAME, hashset);
   }else {
      int fileix = optind;
      for (; fileix < argc; ++fileix) {
         DEBUGF ('m', "argv[%d] = \"%s\"\n", fileix, argv[fileix]);
         char *filename = argv[fileix];
         if (strcmp (filename, STDIN_NAME) == 0) {
            yyin = stdin;
            spellcheck (STDIN_NAME, hashset);
         }else {
            yyin = open_infile (filename);
            if (yyin == NULL) continue;
            spellcheck (filename, hashset);
            fclose (yyin);
         }
      }
   }
   
   yycleanup ();
   return exit_status;
}

