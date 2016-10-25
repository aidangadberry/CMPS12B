#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

typedef struct queue_node queue_node;
struct queue_node {
   queue_item_t item;
   queue_node *link;
};

struct queue {
   queue_node *front;
   queue_node *rear;
};

queue *new_queue (void) {
   queue *this = malloc (sizeof (struct queue));
   assert (this != NULL);
   return this;
}

void free_queue (queue *this) {
   assert (isempty_queue (this));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
   queue_node *temp = malloc (sizeof (struct queue_node));
   assert (temp != NULL);
   temp->item = item;
   if(isempty_queue (this)){
      this->front = temp;
      this->rear = temp;
   }else {
      this->rear->link = temp;
      this->rear = temp;
   }
}

queue_item_t remove_queue (queue *this) {
   assert (! isempty_queue (this));
   queue_node *temp = this->front;
   this->front = temp->link;
   queue_item_t item = temp->item;
   free (temp);
   return item;
}

bool isempty_queue (queue *this) {
   return this->front == NULL;
}
