#include "headers/queue.h"

void init_queue(Queue **q) {
    *q = (Queue *) malloc(sizeof(Queue));
    (*q)->front = (*q)->rear = NULL;
    (*q)->size = 0;
}

int is_empty_queue(Queue *q) {
    return q->front == NULL ? 1 : 0;
}

void enqueue(Queue *q, int x) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->value = x;
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

int front(Queue *q) {
    return q->front->value;
}

void print_queue(Queue *q) {
    Node *it;

    for (it = q->front; it != NULL; it = it->next) {
        printf("%d ", it->value);
    }
    printf("\n");
}
