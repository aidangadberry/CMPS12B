#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

typedef struct options {
   int ignore_case;
   int filenames_only;
   int number_lines;
} options;

void cmatch (FILE *input, char *filename, char *match, options *opts) {
   char buffer[1024];
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL) break;
      if (opts->filenames_only){
         printf ("%s\n", filename);
         break;
      }
      if (opts->ignore_case){
         if (opts->number_lines){
            if (strcasestr (buf, match) != NULL){
               printf ("%s:%d:%s", filename, linenr, buf);
            }
         } else{
            if (strcasestr (buf, match) != NULL){
               printf ("%s:%s", filename, buf);
            }
         }
      } else{
         if (opts->number_lines){
            if (strstr (buf, match) != NULL){
               printf ("%s:%d:%s", filename, linenr, buf);
            }
         } else{
            if (strstr (buf, match) != NULL){
               printf ("%s:%s", filename, buf);
            }
         }
      }
   }
}

void scan_options (int argc, char **argv, options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'n':
            opts->number_lines = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                             program_name, opt);
            break;
      }
   }
}

int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   char *match = NULL;
   int start = 2;
   options *opts = NULL;

   scan_options (argc, argv, opts);
   if (argc == 1) {
      exit_status = EXIT_FAILURE;
      fflush (NULL);
      fprintf (stderr, "Usage: %s [-iln] string [ﬁlename ...]\n",
               program_name);
      fflush (NULL);
   }else {
      if (argv[1][0] == '-') {
         scan_options (argc, argv, opts);
         if (argc >= 3){
            match = argv[2];
            start = 3;
         }else {
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "Usage: %s [-iln] string [ﬁlename ...]\n",
                     program_name);
            fflush (NULL);
         }
      }else {
         if (argc >= 2){
            match = argv[1];
         }
      }
      for (int argi = start; argi < argc; ++argi) {
         char *filename = argv[argi];
         FILE *input = fopen (filename, "r");
         if (input != NULL) {
            cmatch (input, filename, match, opts);
            fclose (input);
         }else {
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: %s: %s\n", program_name,
                     filename, strerror (errno));
            fflush (NULL);
         }
      }
   }
   return exit_status;
}