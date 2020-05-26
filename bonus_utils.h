#ifndef _HOME_STUDENT_HEADERS_BONUS_UTILS_H_
#define _HOME_STUDENT_HEADERS_BONUS_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Query {
    int a;
    int b;
    int answer;
} Query;

typedef struct Edge {
    int a;
    int b;
    int weight;
} Edge;

int checkQueries(Query* queries, int start, int queries_count);
void writeAnswers(Query* queries, int queries_count, FILE* wp);

int find(int* parent, int node);
void merge(int* parent, int root1, int root2);

#endif  // _HOME_STUDENT_HEADERS_BONUS_UTILS_H_
