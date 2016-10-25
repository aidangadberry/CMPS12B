#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>


char *name = NULL;
int exit_status = EXIT_SUCCESS;

int main(int argc, char **argv){

   exit_status = EXIT_SUCCESS;
   name = basename (argv[0]);

   if (argc == 1){
      l9stat(".");
   }else {
      for (int i = 1; i < argc; i++) {
         char *filename = argv[i];
         l9stat(filename);
      }
   }   
}

void l9stat(char *filename){
   struct stat buffer;
   int errstat = lstat(filename, &buffer);
   if (errstat != 0){
      fflush (NULL);
      fprintf (stderr, "%s: %s: %s\n", name,
               filename, strerror (errno));
      fflush (NULL);
      exit_status = EXIT_FAILURE;
   }else {
      int size = (int)buffer.st_size;
      int mode = (int)buffer.st_mode;
      
      printf("%06o\t%d ", mode, size);
      
      struct tm *tm = localtime(&buffer.st_mtime);
      time_t currtime;
      time(&currtime);
      double diff = difftime(buffer.st_mtime, currtime);
      char *format = NULL;
      if (diff < 0){
         diff = -diff;
      }
      if (diff > 15552000){
         format = "%b %d %y";
      }else {
         format = "%b %d %X";
      }
      char timebuffer[1024];
      strftime(timebuffer, sizeof(timebuffer), format, tm);
      printf("%s %s", timebuffer, filename);
      
      char *link = NULL;
      link = malloc(buffer.st_size + 1);
      assert(link != NULL);
      int wantlink = readlink(filename, link, buffer.st_size + 1);

      if (wantlink != -1){
         link[buffer.st_size] = '\0';
         printf(" --> %s", link);
      }
      printf("\n");
      free(link);
   }
}
