// $Id: spellchk.c,v 1.2 2012-02-22 19:50:19-08 - - $

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "debugf.h"
#include "hashset.h"
#include "yyextern.h"

#define STDIN_NAME       "-"
#define DEFAULT_DICTNAME "/usr/share/dict/words"
#define DEFAULT_DICT_POS 0
#define EXTRA_DICT_POS   1
#define NUMBER_DICTS     2

char *execname = NULL;
hashset_ref hashset = NULL;
bool show_clusters = false;
bool show_hashset = false;
int exit_status = EXIT_SUCCESS;

void print_error (char *object, char *message) {
   fflush (NULL);
   fprintf (stderr, "%s: %s: %s\n", execname, object, message);
   fflush (NULL);
   exit_status = 2;
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
      
      if (!has_hashset (hashset, yytext)) {
         // convert yytext to lowercase
         char *lower = strdup(yytext);
         
         for (int i=0 ; lower[i] != '\0' ; i++)
            // LINTED
            lower[i] = tolower(lower[i]);
         
         if (!has_hashset (hashset, lower)) {
            if (exit_status < 1) exit_status = 1;
            printf ("%s is misspelled.\n", yytext);
         }
         free (lower);
      }
      DEBUGF ('m', "line %d, yytext = \"%s\"\n", yylineno, yytext);
   }
}

void load_dictionary (char *dictionary_name, hashset_ref hashset) {
   if (dictionary_name == NULL) return;
   DEBUGF ('m', "dictionary_name = \"%s\", hashset = %p\n",
           dictionary_name, hashset);

   FILE *file = fopen (dictionary_name, "r");

   char buffer[256];
   int linenr;
   for (linenr = 1; ; ++linenr) {
       char *gotline = fgets (buffer, sizeof buffer, file);
       if (gotline == NULL) break;

       char *nlpos = strchr (buffer, '\n');
       if (nlpos != NULL) {
           *nlpos = '\0';
       }else {
           print_error(buffer, "unterminated line\n");
       };
       char *word = strdup (buffer);

       put_hashset(hashset, word);
  }
   
   fclose(file);
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
      int option = getopt (argc, argv, "nyxd:@:");
      if (option == EOF) break;
      switch (option) {
         char optopt_string[16]; // used in default:
         case 'd': user_dictionary = optarg;
                   break;
         case 'n': default_dictionary = NULL;
                   break;
         case 'x': if (show_clusters) show_hashset = true;
                   show_clusters = true;
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

   if (show_clusters) print_hashset_clusters(hashset);
   if (show_hashset) print_hashset(hashset);

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
   
   free_hashset (hashset);
   yycleanup ();
   return exit_status;
}

