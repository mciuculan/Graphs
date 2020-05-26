#include "headers/utils.h"

void init_queue(Queue **q) {
	*q = (Queue *)malloc(sizeof(Queue));
	(*q)->front = (*q)->rear = NULL;
	(*q)->size = 0;
}

int is_empty_queue(Queue *q) {
	return q->front == NULL ? 1 : 0;
}

void enqueue(Queue *q, casuta x) {
	Node *new = (Node *)malloc(sizeof(Node));
	new->value.x = x.x;
	new->value.y = x.y;
	new->next = NULL;

	if (is_empty_queue(q)) {
		q->front = q->rear = new;
		q->size = 1;
		return;
	}

	q->rear->next = new;
	q->rear = new;
	q->size++;
}

int size_queue(Queue *q) {
	return q->size;
}

void dequeue(Queue *q) {
	if (is_empty_queue(q) == 1)
		return;

	Node *del = q->front;
	q->front = q->front->next;
	free(del);
	q->size--;

	if (q->front == NULL)
		q->rear = NULL;
}

casuta front(Queue *q) {
	return q->front->value;
}

