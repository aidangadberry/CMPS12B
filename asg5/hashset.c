#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "debug.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

typedef struct hashnode hashnode;
struct hashnode {
   char *word;
   hashnode *link;
};

struct hashset {
   size_t size;
   size_t load;
   hashnode **chains;
};

void arraydouble (hashset *this){
   size_t leng = this->size;
   this->size = (leng*2)+1;
   hashnode **arr = malloc (this->size * sizeof(char*));
   for (size_t i=0; i<this->size; i++){
      arr[i] = NULL;
   }
   for (size_t i=0; i<leng; i++){
      if (this->chains[i] != NULL){
         int hash_index = strhash(this->chains[i]->word) % this->size;
         while (arr[hash_index]->word != '\0') {
            if (strcmp(arr[hash_index]->word, this->chains[i]->word) == 0){
               break;
            }
            hash_index = (hash_index + 1) % this->size;
         }
         arr[hash_index] = this->chains[i];
      }
   }

   hashnode **temparr = this->chains;
   this->chains = arr;
   free (temparr);
}

hashset *new_hashset (void) {
   hashset *this = malloc (sizeof (struct hashset));
   assert (this != NULL);
   this->size = HASH_NEW_SIZE;
   this->load = 0;
   size_t sizeof_chains = this->size * sizeof (hashnode *);
   this->chains = malloc (sizeof_chains);
   assert (this->chains != NULL);
   memset (this->chains, 0, sizeof_chains);
   DEBUGF ('h', "%p -> struct hashset {size = %zd, chains=%p}\n",
                this, this->size, this->chains);
   return this;
}

void free_hashset (hashset *this) {
   DEBUGF ('h', "free (%p)\n", this);
   for (size_t i=0; i<this->size; i++){
      free (this->chains[i]);
   }
}

void put_hashset (hashset *this, const char *item) {
   if (this->size < this->load*2){
      arraydouble (this);
   }
   size_t i = strhash (item) % this->size;
   while (this->chains[i] != NULL){
      if (strcmp (this->chains[i]->word, item) == 0){
         break;
      }
      i = (i + 1) % this->size;
   }
   if (this->chains[i] == NULL){
      this->chains[i] = malloc ( sizeof (hashnode *));
      this->chains[i]->word = strdup (item);
   }else {
      this->chains[i]->word = strdup (item);
      this->load++;
   }
}

bool has_hashset (hashset *this, const char *item) {
   size_t i = strhash (item) % this->size;
   while (this->chains[i] != NULL){
      if (strcmp (this->chains[i]->word, item) == 0){
         return true;
      }
      i = (i + 1) % this->size;
   }
   //convert it all to lower and recheck it
   char *lowercase = item;
   int j = 0;
   while (item[j] != '\0'){
      lowercase[j] = tolower (item[j]);
      j++;
   }
   i = strhash (lowercase) % this->size;
   while (this->chains[i] != NULL){
      if (strcmp (this->chains[i]->word, lowercase) == 0){
         return true;
      }
      i = (i + 1) % this->size;
   }
   return false;
}
