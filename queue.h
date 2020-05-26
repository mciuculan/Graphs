#ifndef _HOME_STUDENT_HEADERS_QUEUE_H_
#define _HOME_STUDENT_HEADERS_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Queue {
    int size;
    Node *front;
    Node *rear;
} Queue;

void init_queue(Queue **q);

int is_empty_queue(Queue *q);

void enqueue(Queue *q, int x);

void dequeue(Queue *q);

int size_queue(Queue *q);

int front(Queue *q);

void print_queue(Queue *q);

#endif  // _HOME_STUDENT_HEADERS_QUEUE_H_
