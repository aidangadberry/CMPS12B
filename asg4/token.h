#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdbool.h>

#define NUMBER 256

typedef struct token token;

token *new_token (FILE*);

void free_token (token*);

int scan_token (token*);

char *peek_token (token*);

void show_token (token*);

#endif
