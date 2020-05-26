#ifndef _HOME_STUDENT_HEADERS_UTILS_H_
#define _HOME_STUDENT_HEADERS_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct casuta {
	int x;
	int y;
} casuta;

#ifndef NODE
#define NODE

typedef struct Node {
	casuta value;
	struct Node *next;
} Node;

#endif

typedef struct Queue {
	int size;
	Node *front;
	Node *rear;
} Queue;

void init_queue(Queue **q);

int is_empty_queue(Queue *q);

void enqueue(Queue *q, casuta x);

void dequeue(Queue *q);

int size_queue(Queue *q);

casuta front(Queue *q);

#endif  // _HOME_STUDENT_HEADERS_UTILS_H_

