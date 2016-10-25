// $Id: lsort.c,v 1.1 2011-04-29 19:46:42-07 - - $

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
struct node {
   char *item;
   node *link;
};

int main (int argc, char **argv) {

    (void) argc; // : unused parameter 'argc'
    int dflag = 0;
    int exitstatus = 0;
    char *progname = basename (argv[0]);
    char buffer[82];
    node *head = NULL;
    int linenr;

    if (getopt (argc, argv, "d") != -1) {
        dflag = 1;
    }

    for (linenr = 1; ; linenr++) {

        char *gotline = fgets (buffer, sizeof buffer, stdin);
        if (gotline == NULL) break;

        char *nlpos = strchr (buffer, '\n');
        if (nlpos != NULL) {
            *nlpos = '\0';
        }else {
            fprintf (stderr, "%s: %d: unterminated line: %s\n",
                     progname, linenr, buffer);
        };

        node *prev = malloc (sizeof (struct node));
        node *curr = malloc (sizeof (struct node));
        assert (prev != NULL);
        assert (curr != NULL);

        if (head == NULL) {
            curr->item = strdup (buffer);
            assert (curr->item != NULL);
            curr->link = head;
            head = curr;
        }else {
            prev = NULL;
            curr = head;

            // Find the insertion position.
            while (curr != NULL) {
                if (strcmp(curr->item, strdup (buffer)) > 0) break;
                prev = curr;
                curr = curr->link;
            }

            // Do the insertion.
            node *temp = malloc (sizeof (struct node));
            assert (temp != NULL);
            temp->item = strdup (buffer);
            assert (temp->item != NULL);
            temp->link = curr;
            if (prev == NULL) {
                head = temp;
            }else {
                prev->link = temp;
            }
        }
    };

    if (dflag == 1){
        printf ("&head= %p\n", &head);
        printf ("head= %p\n", head);
        for (node *curr = head; curr != NULL; curr = curr->link) {
            printf ("%p -> struct node {item= %s, link= %p}\n",
                    curr, curr->item, curr->link);
        }
        printf ("NULL= %p\n", NULL);
    }else {
        for (node *curr = head; curr != NULL; curr = curr->link) {
            printf ("%s\n", curr->item);
        }
    }

    while (head != NULL) {
        node *old = head;
        head = head->link;
        free (old);
    }

    return exitstatus;
}
