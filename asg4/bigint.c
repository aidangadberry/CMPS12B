#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"
#include "debug.h"

#define MIN_CAPACITY 16

struct bigint {
   size_t capacity;
   size_t size;
   bool negative;
   char *digits;
};

static void trim_zeros (bigint *this) {
   while (this->size > 0) {
      size_t digitpos = this->size - 1;
      if (this->digits[digitpos] != 0) break;
      --this->size;
   }
}

bigint *new_bigint (size_t capacity) {
   bigint *this = malloc (sizeof (bigint));
   assert (this != NULL);
   this->capacity = capacity;
   this->size = 0;
   this->negative = false;
   this->digits = calloc (this->capacity, sizeof (char));
   assert (this->digits != NULL);
   DEBUGS ('b', show_bigint (this));
   return this;
}

bigint *new_string_bigint (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint *this = new_bigint (length > MIN_CAPACITY
                            ? length : MIN_CAPACITY);
   char *strdigit = &string[length - 1];
   if (*string == '_') {
      this->negative = true;
      ++string;
   }
   char *thisdigit = this->digits;
   while (strdigit >= string) {
      assert (isdigit (*strdigit));
      *thisdigit++ = *strdigit-- - '0';
   }
   this->size = thisdigit - this->digits;
   trim_zeros (this);
   DEBUGS ('b', show_bigint (this));
   return this;
}

int comp_bigint (bigint *this, bigint *that) {
   if (this->size > that->size){
      return 0;
   }
   if (this->size < that->size){
      return 1;
   }
   for (size_t i=0; i<this->size; i++){
      if (this->digits[i] > that->digits[i]){
         return 0;
      }
      if (this->digits[i] < that->digits[i]){
         return 1;
      }
   }
   return 0;
}

static bigint *do_add (bigint *this, bigint *that) {
   if (comp_bigint (this, that) == 0){
      bigint *temp = new_bigint (this->size + 1);
      int carry = 0;
      for (size_t i=0; i<that->size; i++){
         int digit = this->digits[i] + that->digits[i] + carry;
         temp->digits[i] = digit % 10;
         carry = digit / 10;
      }
      for (size_t i=that->size; i<this->size; i++){
         int digit = this->digits[i] + carry;
         temp->digits[i] = digit % 10;
         carry = digit / 10;
      }
      trim_zeros (temp);
      return (temp);
   }else {
      bigint *temp = new_bigint (that->size + 1);
      int carry = 0;
      for (size_t i=0; i<this->size; i++){
         int digit = this->digits[i] + that->digits[i] + carry;
         temp->digits[i] = digit % 10;
         carry = digit / 10;
      }
      for (size_t i=this->size; i<that->size; i++){
         int digit = that->digits[i] + carry;
         temp->digits[i] = digit % 10;
         carry = digit / 10;
      }
      trim_zeros (temp);
      return (temp);
   }
}

static bigint *do_sub (bigint *this, bigint *that) {
   bigint *temp = new_bigint (this->size);
   int borrow = 0;
   for (size_t i=0; i<that->size; i++){
      int digit = this->digits[i] - that->digits[i] - borrow + 10;
      temp->digits[i] = digit % 10;
      borrow = 1 - digit / 10;
   }
   for (size_t i=that->size; i<this->size; i++){
      int digit = this->digits[i] - borrow + 10;
      temp->digits[i] = digit % 10;
      borrow = 1 - digit / 10;
   }
   trim_zeros (temp);
   return (temp);
}

void free_bigint (bigint *this) {
   free (this->digits);
   free (this);
}

void print_bigint (bigint *this, FILE *file) {
   DEBUGS ('b', show_bigint (this));
}

bigint *add_bigint (bigint *this, bigint *that) {
   if (this->negative == that->negative){
      bigint *temp = do_add (this, that);
      temp->negative = this->negative;
      return (temp);
   }else {
      if (comp_bigint (this, that) == 0){
         bigint *temp = do_sub (this, that);
         temp->negative = this->negative;
         return (temp);
      }else {
         bigint *temp = do_sub (that, this);
         temp->negative = that->negative;
         return (temp);
      }
   }
}

bigint *sub_bigint (bigint *this, bigint *that) {
   if (this->negative == that->negative){
      bigint *temp = do_sub (this, that);
      return (temp);
   }else {
      bigint *temp = do_add (this, that);
      return (temp);
   }
}

bigint *mul_bigint (bigint *this, bigint *that) {
   bigint *temp = new_bigint (this->size + that->size);
   for (size_t i=0; i<this->size; i++){
      int c = 0;
      for (size_t j=0; j<that->size; j++){
         int d = temp->digits[i+j] + this->digits[i]*this->digits[j]
                 + c;
         temp->digits[i+j] = d%10;
         c = d/10;
      }
      temp->digits[i+that->size] = c;
   }
   return (temp);
}

void show_bigint (bigint *this) {
   fprintf (stderr, "bigint@%p->{%lu,%lu,%c,%p->", this,
            this->capacity, this->size, this->negative ? '-' : '+',
            this->digits);
   for (char *byte = &this->digits[this->size - 1];
        byte >= this->digits; --byte) {
      fprintf (stderr, "%d", *byte);
   }
   fprintf (stderr, "}\n");
}
