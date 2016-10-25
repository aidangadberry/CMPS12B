// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
   double item;
   node *link;
};

int main (int argc, char **argv) {

    (void) argc; // : unused parameter 'argc'
    int dflag = 0;
    int exitstatus = 0;
    char *progname = basename (argv[0]);
    char err_buffer [256];
    char err_buf_fmt[16];
    node *head = NULL;

    if (getopt (argc, argv, "d") != -1) {
        dflag = 1;
    }

    for (;;) {

        // Try to read a double number.  Print an error message if a
        // word is not recognized as a number.  Stop at end of file.

        double number;
        int scancount = scanf ("%lg", &number);

        if (scancount == EOF) {
            printf ("%s: EOF\n", progname);
            break;
        }else if (scancount == 1) {
            node *prev = malloc (sizeof (struct node));
            node *curr = malloc (sizeof (struct node));
            assert (prev != NULL);
            assert (curr != NULL);

            if (head == NULL) {
                curr->item = number;
                curr->link = head;
                head = curr;
            }else {
                prev = NULL;
                curr = head;

                // Find the insertion position.
                while (curr != NULL) {
                    if (curr->item > number) break;
                    prev = curr;
                    curr = curr->link;
                }

                // Do the insertion.
                node *temp = malloc (sizeof (struct node));
                assert (temp != NULL);
                temp->item = number;
                temp->link = curr;
                if (prev == NULL) {
                    head = temp;
                }else {
                    prev->link = temp;
                }
            }
        }else {
            scancount = scanf (err_buf_fmt, err_buffer);
            assert (scancount == 1);
            printf ("%s: bad number \"%s\"\n", progname, err_buffer);
            exitstatus = 1;
        };
    };

    if (dflag == 1){
        printf ("&head= %p\n", &head);
        printf ("head= %p\n", head);
        for (node *curr = head; curr != NULL; curr = curr->link) {
            printf ("%p -> struct node {item= %.15g, link= %p}\n",
                    curr, curr->item, curr->link);
        }
        printf ("NULL= %p\n", NULL);
    }else {
        for (node *curr = head; curr != NULL; curr = curr->link) {
            printf ("%24.15g\n", curr->item);
        }
    }

    while (head != NULL) {
        node *old = head;
        head = head->link;
        free (old);
    }

    return exitstatus;
}
